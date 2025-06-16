// Import all classes and interfaces from the java.util package of the Java Standard Library
import java.util.*;

// Main class to represent family relationships
public class FamilyRelations2 {
    // Define sets of male and female names
    //Set<String> is a data structure that does not repeat elements
    static Set<String> males = new HashSet<>(List.of("Andy", "Bob", "Cecil", "Dennis", "Edward", "Felix", "Martin", "Oscar", "Quinn"));
    static Set<String> females = new HashSet<>(List.of("Gigi", "Helen", "Iris", "Jane", "Kate", "Liz", "Nancy", "Pattie", "Rebecca"));

    // Store spouse relationships (bidirectional)
    static final Map<String, String> spouse = new HashMap<>();

    // Map from child to their parents
    static final Map<String, Set<String>> parents = new HashMap<>();

    // Map from parent to list of their children
    static final Map<String, List<String>> children = new HashMap<>();

    static {
        // Define married couples
        spouse.put("Bob", "Helen");
        spouse.put("Helen", "Bob");

        spouse.put("Dennis", "Pattie");
        spouse.put("Pattie", "Dennis");

        spouse.put("Gigi", "Martin");
        spouse.put("Martin", "Gigi");

        // Add known parent relationships
        // Relation #1: If one parent is known and married, derive the second parent
        addParent("Bob", "Andy");
        addParent("Cecil", "Bob");
        addParent("Dennis", "Cecil");
        addParent("Edward", "Dennis");
        addParent("Felix", "Edward");

        addParent("Helen", "Gigi");
        addParent("Iris", "Helen");
        addParent("Jane", "Iris");
        addParent("Kate", "Jane");
        addParent("Liz", "Kate");

        addParent("Nancy", "Martin");
        addParent("Oscar", "Nancy");
        addParent("Pattie", "Oscar");
        addParent("Quinn", "Pattie");
        addParent("Rebecca", "Quinn");
    }

    // Add parent-child relation and derive second parent through marriage
    static void addParent(String child, String parentName) {
        //computeIfAbsent: a special method of Map, used to ensure that a key must have a corresponding value
        //If there is no key in the map, the following lambda (creating an empty collection) is executed to put it in.
        parents.computeIfAbsent(child, k -> new HashSet<>()).add(parentName);
        children.computeIfAbsent(parentName, k -> new ArrayList<>()).add(child);

        // Derive second parent from marriage (Relation #1)
        String spouseName = spouse.get(parentName);
        if (spouseName != null) {
            parents.get(child).add(spouseName);
            children.computeIfAbsent(spouseName, k -> new ArrayList<>()).add(child);
        }
    }

    // Get siblings of a person (Relation #2)
    static List<String> getSiblings(String person) {
        Set<String> parentSet = parents.get(person);

        // parentSet == null means the key "person" is not registered at all
        // parentSet.isEmpty() means the person has no known parents
        if (parentSet == null || parentSet.isEmpty()) return List.of();

        // Get the first parent
        //iterator(): returns iterator<string> object.
        //next() → gets the next element
        String firstParent = parentSet.iterator().next();
        List<String> siblings = new ArrayList<>(children.get(firstParent));
        siblings.remove(person);
        return siblings;
    }

    /**********************************************************************/

    // Check if two people are cousins (Relation #5)
    public static boolean areCousins(String a, String b) {
        Set<String> aParents = parents.getOrDefault(a, Set.of());
        Set<String> bParents = parents.getOrDefault(b, Set.of());

        for (String ap : aParents) {
            for (String bp : bParents) {
                if (getSiblings(ap).contains(bp)) return true;
            }
        }
        return false;
    }
    
    // Check if X is the parent of Y
    public static boolean areParent(String parentName, String childName) {
        return parents.getOrDefault(childName, Set.of()).contains(parentName);
    }

    public static boolean areSibling(String a, String b) {
        return getSiblings(a).contains(b);
    }

    public static boolean areBrother(String a, String b) {
        return areSibling(a,b) && males.contains(a) && males.contains(b);
    }

    public static boolean areSister(String a, String b) {
        return areSibling(a,b) && females.contains(a) && females.contains(b);
    }

    /**********************************************************************/

    // Main function to test relationships
    public static void main(String[] args) {
        System.out.println(areParent("Iris", "Jane"));           //true
        System.out.println(areParent("Jane", "Iris"));           //false
        System.out.println(areParent("Iris", "Kate"));           //false
        
        System.out.println(areCousins("Iris", "Oscar"));                          //true
        System.out.println(areCousins("Oscar", "Iris"));                          //true
        System.out.println(areCousins("Oscar", "Cecil"));                         //true
        System.out.println(areCousins("Dennis", "Jane"));                         //true
        System.out.println(areCousins("Felix", "Rebecca"));                       //true
        
        System.out.println(areSibling("Cecil", "Iris"));                          //true
        System.out.println(areSibling("Edward", "Quinn"));                        //true
        System.out.println(areBrother("Edward", "Quinn"));                        //true
        System.out.println(areSister("Nancy", "Helen"));                          //true
    }
}