.data
  array: .word 5, 0, 1, 1, 2, 3
  newline: .asciiz "\n"

.text
main:
  li $s0, 0  # initialize index = 0
  la $t0, array   # load array's address to $t0

loop:
  beq $s0, 5, exit # if index == 5, then exit
  
  lw $t1, 4($t0)   # load word from address $t0 + 4

  li $v0, 1
  move $a0, $t1  # move $t1 to printing register
  syscall

  li $v0, 4      # print a newline
  la $a0, newline
  syscall

  addi $t0, $t0, 4 # move to next address
  addi $s0, $s0, 1 # increase index

  j loop    # jump loop

exit:
  li $v0, 10
  syscall
