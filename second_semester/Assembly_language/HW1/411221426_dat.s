.data
    fib_array: .word 39       # n (number of Fibonacci numbers to generate)
             .space 400      # Reserve space for Fibonacci sequence (max 100 numbers)

.text
main:
    # Load address of array and get n
    la $t0, fib_array        # $t0 = base address of array
    lw $s0, 0($t0)           # $s0 = n (read from first word)
    
    # Check if n <= 0
    blez $s0, exit           # If n <= 0, terminate program

    # Initialize first two Fibonacci numbers
    li $t1, 0                # F(0) = 0
    li $t2, 1                # F(1) = 1

    # Store F(0) at second location (offset 4)
    sw $t1, 4($t0)           # array[1] = 0

    # Check if n == 1
    beq $s0, 1, exit         # If only 1 number needed, exit

    # Store F(1) at third location (offset 8)
    sw $t2, 8($t0)           # array[2] = 1
  
    # Check if n == 2
    beq $s0, 2, exit         # If only 2 numbers needed, exit

    # Initialize loop counter (we've already generated 2 numbers)
    li $t3, 2                # $t3 = current index (starts at 2)

loop:
    # Check if we've generated enough numbers
    bge $t3, $s0, exit       # If index >= n, exit loop

    # Calculate next Fibonacci number: F(i) = F(i-1) + F(i-2)
    add $t4, $t1, $t2        # $t4 = F(i-2) + F(i-1)

    # Calculate storage address (4 bytes per word)
    addi $t5, $t3, 1         # $t5 = i+1 (since array[0] is n)
    sll $t5, $t5, 2          # $t5 = (i+1)*4 (byte offset)
    add $t5, $t0, $t5        # $t5 = address of array[i+1]
    sw $t4, 0($t5)           # Store at array[i+1]

    # Update F(i-2) and F(i-1) for next iteration
    move $t1, $t2            # F(i-2) = previous F(i-1)
    move $t2, $t4            # F(i-1) = current F(i)

    # Increment counter
    addi $t3, $t3, 1         # i++
    j loop                   # Repeat loop

exit:
    # Terminate program
    li $v0, 10
    syscall
