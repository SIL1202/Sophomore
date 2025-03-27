.data
  num1: .word 0
  num2: .word 0
  input1: .asciiz "input number a: "
  input2: .asciiz "input number b: "
  output1: .asciiz "a == b\n"
  output2: .asciiz "a < b\n"
  output3: .asciiz "a > b\n"

.text
.globl main
main:
loop: 
  li $v0, 4   # ouput string input2
  la $a0, input1 
  syscall

  li $v0, 5 # read value from user
  syscall

  la $t0, num1 # load address of num1
  sw $v0, 0($t0) # store value to address of $t0

  li $v0, 4   # ouput string input2
  la $a0, input2 
  syscall
  
  li $v0, 5
  syscall   # read value from user

  la $t1, num2 # load address of num2
  sw $v0, 0($t1) # store value to address of $t0

  lw $s0, 0($t0) #load value from $t0
  lw $s1, 0($t1) #load calue from $t1
  
  beq $s0, $s1, if_equal
  blt $s0, $s1, if_less
  bgt $s0, $s1, if_greater

if_equal:
  li $v0, 4
  la $a0, output1
  syscall
  j loop

if_less:
  li $v0, 4
  la $a0, output2 # a < b
  syscall
  j loop

if_greater:
  li $v0, 4
  la $a0, output3 # a > b
  syscall
  j loop
