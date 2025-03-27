	.text
main:	li	$s0, 0		# $s0 as accumulated sum
loop:	li	$v0, 5		# input from console
	syscall			#
	beq 	$v0, $0, out	# leave loop if getting 0
	add	$s0, $s0, $v0	# add the number to accumulated sum
	j	loop		#
out:	add	$a0, $s0, $0	# write the result
	li	$v0, 1		#
	syscall			#
exit:	li	$v0, 10		# end of program
	syscall			#
