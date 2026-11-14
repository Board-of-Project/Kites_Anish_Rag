# rand_gen seed=176 length=100
li s11, 1024
li t0, 1
li t1, -1773
li t2, 195
li s0, 311
li s1, 60001779
li a1, 228482400
li a2, 2147483647
li a3, 0
li t0, 0
xori t2, a2, -563
srl s1, a1, t1
xor t0, s1, s1
srl s1, t1, t1
or t2, a2, t0
slt t1, s1, zero
sw t1, 12(s11)
or s0, a2, t0
sll a3, a2, a3
sll a1, t1, a1
sll t0, a3, a3
xor s0, a1, t1
slti t1, a2, 400
sh t1, 42(s11)
slli s0, t1, 23
and t0, t2, a2
ori t2, t2, -1693
addi a1, s1, 487
srli t2, a1, 21
or a1, zero, t1
srai t0, s0, 7
lbu a3, 241(s11)
bltu a1, a2, L0
li s1, 192285816
sw t2, 104(s11)
addi t1, t0, 324
L0:
sra a2, s1, t0
ld s1, 104(s11)
add a1, t2, s0
add t1, t1, s1
add t2, t0, a2
beq t1, zero, L1
slti t1, a2, -926
sltiu a2, t1, 847
slti a2, a2, -1123
L1:
bge a2, a1, L2
mv s0, t1
L2:
sw t2, 28(s11)
bltu t1, s1, L3
sd zero, 32(s11)
sltiu t1, a3, -80
L3:
lw t2, 212(s11)
lb t2, 107(s11)
sltu a3, zero, a1
srai t0, a1, 13
srai a3, s0, 26
andi a3, a3, -1078
srli s0, zero, 23
blt s0, s0, L4
sw t1, 248(s11)
xori t0, s0, 389
xori s0, a3, -1134
L4:
add s1, zero, t1
lw a2, 164(s11)
srl t0, t1, a1
mv t2, t0
lwu t2, 116(s11)
srl a1, s1, s1
srli t1, zero, 14
beq s1, t2, L5
li t0, 2147483647
slti a1, t2, -581
sub t0, a3, t0
L5:
srai a1, s0, 31
slli t2, zero, 7
xori t1, t1, 2045
slli a1, zero, 17
bgeu s1, a1, L6
addi s0, s0, 683
and t0, a2, a3
L6:
srl s1, t0, a1
srli a2, zero, 3
addi t0, a3, 62
mv s1, t0
add t0, a2, s0
srl a2, a2, s1
xori a2, a3, 644
mv a3, s1
sll t1, s0, s0
addi t1, zero, 264
bne zero, zero, L7
sub a2, s0, a1
addi s0, s1, -438
xor a3, t0, a3
L7:
and t2, a2, a1
slli t2, a2, 21
addi t2, t1, -1571
mv t0, s0
or a2, zero, a3
sltiu t1, t2, 1760
or t1, t0, a1
sub t2, t0, a3
li t0, 794433046
add a2, a2, s0
mv s0, s0
add s0, s1, s0
slli a3, a1, 1
sra s0, s0, t1
addi t0, s1, -690
