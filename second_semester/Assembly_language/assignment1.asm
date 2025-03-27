.data
input: .word 0 # input for user
newline_: .asciiz "\n"

.text
main:
  li $v0, 5 # input command for 5
  syscall 
  move $t0, $v0 # store v0 into t0

# -- unaccepted condition
  beq $t0, 0, exit # if input == 0, then exit

# -- base case
  li $s0, 0
  li $s1, 1
  # j debug

# -- output first value
  li $v0, 1 
  move $a0, $s0
  syscall           # print first value
  beq $t0, 1, exit  # if input == 1, then exit

  li $v0, 4
  la $a0, newline_
  syscall 

# -- output second value
  li $v0, 1 
  move $a0, $s1 
  syscall           # print second value
  beq $t0, 2, exit  # if input == 2, then exit

  li $v0, 4
  la $a0, newline_
  syscall 

  li $t1, 2 # initialize index = 2

loop:
  beq $t1, $t0, exit # if $t1(index) == $t0(input), then exit
  add $t2, $s1, $s0  # $t2(ans) = $s1(temp2) + $s0(temp1)
  li $v0, 1 
  move $a0, $t2      # move $t2(ans) to $a0
  syscall            # output ans

# -- print newline
  li $v0, 4
  la $a0, newline_
  syscall


# -- swap
  move $s0, $s1      # move $s1 value to $s0 value
  move $s1, $t2      # move $t2 value to $s1 value
  addi $t1, $t1, 1   # $t1(index)++
 
  j loop 
 
exit:
  li $v0, 10
  syscall
