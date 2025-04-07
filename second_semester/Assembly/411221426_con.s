.data
    prompt: .asciiz "Enter the number of Fibonacci terms to display (n < 40): "
    newline: .asciiz "\n"
    error_msg: .asciiz "Invalid input! n must be between 1 and 39.\n"

.text
main:
    # Print prompt message
    li $v0, 4
    la $a0, prompt
    syscall
    
    # Read user input (n)
    li $v0, 5
    syscall
    move $t0, $v0       # $t0 = n
    
    # Validate input (1 <= n < 40)
    blez $t0, invalid_input  # If n <= 0, show error
    li $t1, 39
    bgt $t0, $t1, invalid_input  # If n > 39, show error
    
    # Initialize Fibonacci sequence
    li $s0, 0           # F(0) = 0
    li $s1, 1           # F(1) = 1
    
    # Print first number (F0)
    li $v0, 1
    move $a0, $s0
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    
    # Check if n == 1
    beq $t0, 1, exit    # If only 1 number needed, exit
    
    # Print second number (F1)
    li $v0, 1
    move $a0, $s1
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    
    # Check if n == 2
    beq $t0, 2, exit    # If only 2 numbers needed, exit
    
    # Initialize loop counter (we've printed 2 numbers already)
    li $t1, 2           # $t1 = counter (starts at 2)

loop:
    # Check if we've printed enough numbers
    bge $t1, $t0, exit  # If counter >= n, exit loop
    
    # Calculate next Fibonacci number
    add $t2, $s1, $s0   # $t2 = F(n-1) + F(n-2)
    
    # Print the number
    li $v0, 1
    move $a0, $t2
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    
    # Update values for next iteration
    move $s0, $s1       # F(n-2) = previous F(n-1)
    move $s1, $t2       # F(n-1) = current Fibonacci number
    
    # Increment counter
    addi $t1, $t1, 1
    
    j loop

invalid_input:
    # Print error message
    li $v0, 4
    la $a0, error_msg
    syscall
    j main  # Allow user to try again

exit:
    # Terminate program
    li $v0, 10
    syscall
