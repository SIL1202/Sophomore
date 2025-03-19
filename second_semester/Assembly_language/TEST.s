.data
num1: .word -77 #define var num1
num2: .word -12 #define var num2
prompt1: .asciiz "output:\n"
prompt2: .asciiz "quotient: "
prompt3: .asciiz "remainder: "
space: .asciiz " "
slash: .asciiz " / "
equal: .asciiz " = "
remain: .asciiz " ... " 
newline: .asciiz "\n"
 					# 45 / 5 = 9 ... 0
.text
.globl main
main:
	li $v0, 4       # output string
	la $a0, prompt1 # load address of prompt to $a0
	syscall

	la $t0, num1 	# load address of num1
	lw $t0, 0($t0) 	# read $t0 to $t1

## print num1:
	li $v0, 1	
	move $a0, $t0 	# copy $t0(45) to $a0	
	syscall
	
## print " / ":
	li $v0, 4	# output string
	la $a0, slash 	# load address of slash
	syscall 
 
	la $t1, num2 	# load address of num2
	lw $t1, 0($t1)	# read $t1 to $t1

## print num2:
	li $v0, 1
	move $a0, $t1 	# copy $t1(5) to $a0
	syscall 

## print " = "
	li $v0, 4
	la $a0, equal 	# load address of equal
	syscall

## dividing
	div $t0, $t1 	# $t0 over $t1
	mflo $t2	# move from lo
	mfhi $t3	# move from hi

## print num1/num2
	li $v0, 1
	move $a0, $t2  	# copy $t2 to $a0
	syscall

## print " ... "
	li $v0, 4
	la $a0, remain	# load address of remain
	syscall

## print num1%num2
	li $v0, 1
	move $a0, $t3	# copy $t3 to $a0
	syscall 

## print "\n"	
	li $v0, 4	# output string
	la $a0, newline # load address of newline to $a0
	syscall
	syscall		# double newline

## print "quotient: "
	li $v0, 4
	la $a0, prompt2 #load address of prompt2
	syscall

## print num1/num2
	li $v0, 1
	move $a0, $t2	# copy $t2 to $a0
	syscall 
	
## print "\n"	
	li $v0, 4	# output string
	la $a0, newline # load address of newline to $a0
	syscall
	syscall		# double newline

## print "remainder: "
	li $v0, 4	# output string
	la $a0, prompt3 # load address of prompt3
	syscall

## print num1%num2
	li $v0, 1
	move $a0, $t3 	# copy $t3 to $a0
	syscall		
