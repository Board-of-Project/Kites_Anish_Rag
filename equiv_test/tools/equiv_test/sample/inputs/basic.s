# sums 7 + 35, prints it, exits with code 0
li   t0, 7          # first operand
li   t1, 35         # second operand

mv   a0, t0
add  a0, a0, t1     # a0 = 42
li   a7, 1          # SYSCALL_PRINT_INT
ecall

li   a0, 0          # exit code
li   a7, 10         # SYSCALL_EXIT
ecall
