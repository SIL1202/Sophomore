	.data
input:	.word 5
	.word 3
	.word 8
	.word 4
	.word 7
	.word 0	
result:	.word 0
	.text
main:	li	$s0, 0		# $s0 as accumulated sum
	la	$s1, input	# $s1 as memory pointer
loop:	lw	$t0, 0($s1)	# get number from memory
	beq	$t0, $0, out	# leave loop if getting 0
	add	$s0, $s0, $t0	# add the number to accumulated sum
	addi	$s1, $s1, 4	# memory pointer to next location
	j	loop		#
out:	la	$s2, result	# write the result
	sw	$s0, 0($s2)	#
exit:	li	$v0, 10		# end of program
	syscall			#
