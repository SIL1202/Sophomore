# I use insertion sort here because it's easier to implement in MIPS.
# Basically, I go from i = 1 and insert the key into the left part of the array.
# The array is stored in 'buffer', and sorted inside the insert_sort procedure.
# Input stops when user types 0.

# insert_sort: handles the Insertion Sorting Algorithm
# sort_outer: is like the outer 'for' loop (for i = 1 to n)
# shift_loop: simulates the 'while' loop that shifts elements
# insert_key: finally inserts the key into the correct position

# Please enter one number per line to avoid syscall 5 crash.

.data
space: .asciiz " "
newline: .asciiz "\n"
buffer: .space 400

.text
main:
  la $s0, buffer              # load initialize address of the buffer to $s0
  li $s1, 0                   # initial count = 0

input_loop:
  li $v0, 5
  syscall
  beq $v0, $zero, sort_call    # if input is equal to 0(only one number), then jump to sort_call

  sll $t0, $s1, 2             # offset = shift left: $s1 x (2 ^ 2) = $s1 x 4
  add $t1, $s0, $t0           # add offset to the starting address of the array buffer
  sw $v0, 0($t1)              # store word into address of $s0 + $t0
  
  addi $s1, $s1, 1            # count ++
  j input_loop

sort_call:                    
  move $a0, $s0               # $a0 = arr[]
  move $a1, $s1               # $a1 = length
  jal insert_sort             # void insertion(int arr[], int length)

print_loop:
  li $t0, 0                   # initialize loop index

loop_start:
  bge $t0, $s1, exit          # if $t0(index) >= $s1(count), then exit

  sll $t1, $t0, 2             # offset = shift left: $s1 x (2 ^ 2) = $s1 x 4
  add $t2, $s0, $t1           # add offset to the starting address of the array buffer
  lw $a0, 0($t2)              # load word from $t2 to $a0
  
  li $v0, 1                   # print current number
  syscall 

  li $v0, 4
  la $a0, space               # print space 
  syscall

  addi $t0, $t0, 1            # index ++
  j loop_start

exit:
  li $v0, 4 
  la $a0, newline             # print newline
  syscall

  li $v0, 10                  # exit
  syscall

# ========= insertion sort =========
# $a0 = arr[]
# $a1 = length

insert_sort:
  li $t0, 1                   # int i = 1

sort_outer:                   ## begin with the for loop
  bge $t0, $a1, sort_done     # for(; i < n;) {  
  
  sll $t1, $t0, 2             #   offset = shift left $s1 x (2 ^ 2) = $s1 x 4
  add $t2, $a0, $t1           #   add offset to the starting address of the array buffer
  lw $t3, 0($t2)              #   key = A[i]

  addi $t4, $t0, -1           #   int j = i - 1

shift_loop:                   ##   while( j >= 0 && arr[j] > key )
  bltz $t4, insert_key        #   if (j < 0) ----> jump out of the while loop ----> arr[j+1] = key;
  sll $t5, $t4, 2             #  
  add $t6, $a0, $t5           # 
  lw $t7, 0($t6)              #   $t7 = arr[j]

  ble $t7, $t3, insert_key    #   if (arr[j] <= key) ----> jump out of the while loop ----> arr[j+1] = key;
  sw $t7, 4($t6)              #   arr[j+1] = arr[j]
  addi $t4, $t4, -1           #   j --
  j shift_loop

insert_key:
  addi $t4, $t4, 1            # j ++
  sll $t8, $t4, 2             
  add $t9, $a0, $t8
  sw $t3, 0($t9)

  addi $t0, $t0, 1            # i ++; }
  j sort_outer

sort_done:
  jr $ra
