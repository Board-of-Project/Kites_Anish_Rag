# rand_gen seed=181 length=100
li s11, 1024
li t0, -447174464
li t1, -193796820
li t2, 1
li s0, -686261967
li s1, -2627284
li a1, -2147483648
li a2, -2147483648
li a3, 2147483647
addi s1, t2, -1809
sw s1, 84(s11)
srl t1, a3, a2
andi a3, a2, 1132
sltu t1, a2, a2
mv s0, t2
srl a1, a1, s0
sh a3, 98(s11)
sub t1, t1, s1
li a1, 0
mv s0, t2
xor t0, a2, s0
srl s1, a2, s1
slli t0, a3, 21
mv t2, t1
li a2, -2147483648
sltiu t1, s1, 1979
bge a1, s1, L0
sra a2, t0, t0
L0:
bne a1, a1, L1
sltu t1, s0, zero
L1:
srl t2, a1, t0
bge t0, t2, L2
ori a2, s0, -1134
L2:
slti t0, t2, 1519
and a2, zero, s1
or a2, s0, a3
sltiu a1, a2, 1166
li s1, 2147483647
bltu zero, s1, L3
sub a1, a1, a3
sd s1, 200(s11)
L3:
sra a3, s1, a3
srli a2, t1, 29
add t2, t0, a2
sltiu a2, a3, -1616
or t1, a1, a3
srli t2, a3, 0
sub a2, a2, a1
sltiu t1, a3, -1211
sll a3, t0, t0
bge t1, a2, L4
xori t2, a1, 1491
ori a2, t1, -766
L4:
mv t1, zero
srl t2, a2, a2
or a2, t1, a3
mv a1, a1
add a3, s0, t2
ori a1, a3, -885
andi a2, a3, -430
mv t1, t1
bge s0, a2, L5
lbu t2, 114(s11)
lhu t1, 92(s11)
xor t2, zero, t0
L5:
xor t0, t2, s0
andi a1, a2, -890
xor t2, a1, t2
srl a2, s1, zero
sltu t0, a2, a3
add a3, t0, zero
addi a3, a2, -1592
sltu t2, t2, s0
bltu a3, t1, L6
sw a2, 100(s11)
sll a3, zero, t0
li t0, -1594586523
L6:
lb s0, 2(s11)
beq s0, a2, L7
sltiu t1, a3, 948
L7:
sltu a2, a3, a2
sh a2, 88(s11)
li t2, 593399115
lw s1, 96(s11)
slti t0, t2, 799
sltiu a2, t2, -1855
sh zero, 56(s11)
li t0, -1154
slti s1, s1, -1983
li t2, 1291
bge s0, t2, L8
addi t1, a3, -1728
L8:
sltiu t1, a3, 413
sltiu a2, t0, 17
addi t1, t2, 1939
sra t2, a2, t0
srl a3, a3, s0
bltu t1, a2, L9
slti t2, a1, 637
sltiu t1, a3, -1408
L9:
andi a2, a1, -436
srl a1, a2, zero
sw a3, 24(s11)
lhu a1, 124(s11)
andi s0, zero, 1144
ori t1, t2, -600
sll t0, zero, t1
ori s1, a1, 586
srli t1, a3, 2
