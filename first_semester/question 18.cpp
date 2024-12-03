#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 2
// maxinum number of data item each node can hold. Sample Output shows the
// result when MAX_ENTRIES is 2
#define MAX_NAME_LEN 50 // maxinum number of character for item name

typedef struct {
  double minX, minY;
  double maxX, maxY;
} BoundingBox;

typedef struct {
  double latitude, longitude;
  char name[MAX_NAME_LEN];
} DataItem;

typedef struct RTreeNode {
  int isLeaf;      // 是否為葉節點is leaf or not
  int count;       // number of node
  BoundingBox mbr; // minimum bounding rectangle
  struct RTreeNode *children[MAX_ENTRIES + 1];
  DataItem data[MAX_ENTRIES]; //
} RTreeNode;

typedef struct {
  DataItem item;
  double distance;
} SearchResult;

RTreeNode *createNode(int isleaf) {
  RTreeNode *node = (RTreeNode *)malloc(sizeof(RTreeNode));
  node->isLeaf = isleaf;
  node->count = 0;
  memset(&node->mbr, 0, sizeof(BoundingBox));
  for (int i = 0; i <= MAX_ENTRIES; i++) {
    node->children[i] = nullptr;
  }
  return node;
}
// insert data
void updateMBR(BoundingBox *mbr, DataItem item) {
  if (mbr->minX > item.longitude || mbr->minX == 0)
    mbr->minX = item.longitude;
  if (mbr->maxX < item.longitude || mbr->maxX == 0)
    mbr->maxX = item.longitude;
  if (mbr->minY > item.latitude || mbr->minY == 0)
    mbr->minY = item.latitude;
  if (mbr->maxY < item.latitude || mbr->maxY == 0)
    mbr->maxY = item.latitude;
}

void splitNode(RTreeNode **root, RTreeNode *node) {
  RTreeNode *newNode = createNode(node->isLeaf);
  int mid = node->count / 2;

  // Move second half of the data to the new node
  for (int i = mid; i < node->count; i++) {
    if (node->isLeaf) {
      newNode->data[newNode->count++] = node->data[i];
    } else {
      newNode->children[newNode->count++] = node->children[i];
    }
  }
  node->count = mid;

  // Create a new root if necessary
  if (*root == node) {
    RTreeNode *newRoot = createNode(0);
    newRoot->children[newRoot->count++] = *root;
    newRoot->children[newRoot->count++] = newNode;
    *root = newRoot;
  } else {
    RTreeNode *parent = (*root)->children[node->count];
    parent->children[parent->count++] = newNode;
  }
}

void insert(RTreeNode **root, DataItem item) {
  RTreeNode *current = *root;

  // Traverse to the correct leaf node
  while (!current->isLeaf) {
    int bestIndex = 0;
    double smallestAreaIncrease = DBL_MAX;

    for (int i = 0; i < current->count; i++) {
      BoundingBox tempMBR = current->children[i]->mbr;
      updateMBR(&tempMBR, item);

      double originalArea =
          (current->children[i]->mbr.maxX - current->children[i]->mbr.minX) *
          (current->children[i]->mbr.maxY - current->children[i]->mbr.minY);
      double newArea =
          (tempMBR.maxX - tempMBR.minX) * (tempMBR.maxY - tempMBR.minY);

      double areaIncrease = newArea - originalArea;
      if (areaIncrease < smallestAreaIncrease) {
        smallestAreaIncrease = areaIncrease;
        bestIndex = i;
      }
    }

    current = current->children[bestIndex];
  }

  // Insert into the leaf node
  if (current->count < MAX_ENTRIES) {
    current->data[current->count++] = item;
    updateMBR(&current->mbr, item);
  } else {
    // Split the node
    current->data[current->count++] = item;
    splitNode(root, current);
  }
}

// search data
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
  return sqrt(pow(lat1 - lat2, 2) + pow(lon1 - lon2, 2));
}

SearchResult *search(RTreeNode *root, double latitude, double longitude,
                     int n) {
  static SearchResult results[MAX_ENTRIES];
  int resultCount = 0;

  // Check if the node is a leaf
  if (root->isLeaf) {
    for (int i = 0; i < root->count && resultCount < n; i++) {
      double distance = calculateDistance(
          latitude, longitude, root->data[i].latitude, root->data[i].longitude);
      results[resultCount++] =
          (SearchResult){.item = root->data[i], .distance = distance};
    }
  } else {
    for (int i = 0; i < root->count; i++) {
      if (latitude >= root->children[i]->mbr.minY &&
          latitude <= root->children[i]->mbr.maxY &&
          longitude >= root->children[i]->mbr.minX &&
          longitude <= root->children[i]->mbr.maxX) {
        SearchResult *childResults =
            search(root->children[i], latitude, longitude, n - resultCount);
        for (int j = 0; j < n - resultCount && childResults[j].distance >= 0;
             j++) {
          results[resultCount++] = childResults[j];
        }
      }
    }
  }

  return results;
}
// print tree
void printTree(RTreeNode *root, int depth) {
  for (int i = 0; i < depth; i++)
    printf("  ");
  printf("Node (count=%d, isLeaf=%d):\n", root->count, root->isLeaf);
  for (int i = 0; i < root->count; i++) {
    if (root->isLeaf) {
      for (int j = 0; j < depth + 1; j++)
        printf("  ");
      printf("Data: %s (%.2f, %.2f)\n", root->data[i].name,
             root->data[i].latitude, root->data[i].longitude);
    } else {
      printTree(root->children[i], depth + 1);
    }
  }
}

int main() {
  RTreeNode *root = createNode(1);
  DataItem item;
  double latitude, longitude;
  SearchResult *results;

  char command[50];

  while (1) {
    scanf("%s", command);
    if (strcmp("insert", command) == 0) {
      scanf("%lf%lf%s", &item.latitude, &item.longitude, item.name);
      insert(&root, item);
    } else if (strcmp("print", command) == 0) {
      printTree(root, 0);
    } else if (strcmp("exit", command) == 0) {
      break;
    } else if (strcmp("search", command) == 0) {
      scanf("%lf%lf", &latitude, &longitude);
      results = search(root, latitude, longitude, 2);
      for (int i = 0; i < 2; i++) {
        printf("%s (%.2f, %.2f) - Distance: %.2f\n", results[i].item.name,
               results[i].item.latitude, results[i].item.longitude,
               results[i].distance);
      }
    } else {
      printf("Unknow command.\n");
    }
  }
  return 0;
}
