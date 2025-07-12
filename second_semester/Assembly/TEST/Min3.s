main:
  li $a0, 5
  li $a1, 6
  li $a2, 4

  jal min3

  add $a0, $0, $v0
  li $v0, 1
  syscall
  jr $ra

  li $v0, 10
  syscall

min3:
  addi $sp, $sp, -8        # 多開一格，存 $ra 和 $a2
  sw $ra, 4($sp)
  sw $a2, 0($sp)           # 存起 $a2

  move $a0, $a1            # min(a1, a2)
  move $a1, $a2
  jal min2                 # $v0 = min(a1, a2)

  lw $a2, 0($sp)           # 還原 $a2（因為剛剛被蓋掉）
  move $a1, $v0
  move $a0, $a0            # $a0 原本沒被動過可以不用處理
  jal min2                 # min(a0, min(a1, a2))

  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra

min2:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $a0, 0($sp)

  slt $v0, $a0, $a1
  beq $v0, $zero, ELSE
  move $v0, $a0
  j done

ELSE:
  move $v0, $a1

done:
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra
