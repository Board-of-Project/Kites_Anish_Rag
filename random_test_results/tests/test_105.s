# rand_gen seed=105 length=100
li s11, 1024
li t0, 461
li t1, 0
li t2, -1
li s0, 769437884
li s1, 0
li a1, 2147483647
li a2, 2147483647
li a3, 2147483647
andi s0, a1, -1560
slt s1, t1, s0
or a2, t0, t1
sub s1, zero, s1
sra a3, a2, t1
mv t1, a1
xori t2, s1, 515
beq s0, s1, L0
srli a2, a2, 0
slti t2, s1, 311
sra s0, a1, t1
L0:
li t0, 2147483647
sltiu t1, t1, -378
sll s1, s1, t1
xori t2, a3, -1975
add t0, a1, s1
srl s0, zero, t0
sltu s1, s1, a1
slti s0, t2, -1086
or t1, t2, t1
sltiu t0, t0, 1833
sd s0, 104(s11)
slli t2, t0, 25
bltu t2, zero, L1
sltiu t1, s0, -408
bgeu a3, a3, L2
L1:
slt t0, s1, s0
L2:
slli s1, s1, 31
ori t2, a2, -757
add t2, a3, t1
addi t1, a2, -812
sh a1, 94(s11)
xor t0, a1, t2
sub a3, t0, t0
bne t2, zero, L3
sub t2, t2, zero
bgeu t2, t1, L4
or a2, a3, t2
L3:
L4:
bge t2, s1, L5
sw t2, 200(s11)
L5:
or t1, t0, a1
sltu t2, t1, a3
sll a3, s0, a3
sb t0, 112(s11)
slli t2, s0, 9
andi t0, t1, 1904
sh t0, 180(s11)
li t0, 527025174
beq t0, s0, L6
addi s0, s0, -885
L6:
srai t2, zero, 26
slti t0, s1, -1920
andi a1, t0, 1667
lbu s1, 120(s11)
li a1, 2147483647
sd t0, 8(s11)
sra a2, a2, t0
sw s0, 24(s11)
sll s1, s1, t2
srl s1, a3, s0
xor s0, a1, s0
sw a3, 204(s11)
xor s0, a1, a3
mv a1, zero
addi a3, t1, -293
xor a3, t2, a2
andi t0, a3, -106
srai a2, t2, 20
slt s0, s1, s0
ld t1, 0(s11)
add t0, a1, t1
or s0, s0, t0
lhu a2, 204(s11)
sw t0, 184(s11)
bltu a1, t1, L7
and s1, s1, a1
slti t0, a1, 855
sll t1, a2, s1
L7:
or t0, a1, s0
sw a2, 116(s11)
xor t0, a2, t2
or t1, t1, s1
addi s1, a1, 1072
xor t2, t1, t2
lwu t1, 16(s11)
srai t0, t0, 22
sll a1, s0, t1
li a1, -503815950
and t0, s1, a2
or a1, zero, s0
slti t1, zero, 172
sub a2, t2, zero
bne s0, t1, L8
beq t1, t0, L9
L8:
add a2, a1, s0
srl t2, t1, t1
L9:
add a3, zero, a3
andi a3, a2, -161
lb t1, 10(s11)
sltiu a3, zero, -1139
