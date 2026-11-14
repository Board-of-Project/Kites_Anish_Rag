# rand_gen seed=126 length=100
li s11, 1024
li t0, 1
li t1, 0
li t2, 1
li s0, 2147483647
li s1, 2147483647
li a1, -1161510561
li a2, -1540853280
li a3, -1
slt t2, a2, t0
beq a1, a2, L0
sub s1, t1, s1
bltu a1, a1, L1
sra s1, a3, a1
L0:
lhu a2, 244(s11)
L1:
bne s1, t1, L2
bne t2, zero, L3
and a2, s1, a1
L3:
sb s1, 190(s11)
L2:
slti a2, s1, 1233
andi s1, a3, 79
bne s1, a1, L4
slt t1, t2, a2
L4:
li t1, -10406440
xori a2, s0, -816
slt t0, t1, t1
sltu a3, a2, a2
sub a3, t0, t1
blt t0, t1, L5
bgeu t1, a1, L6
sub s0, a3, a1
L5:
sb t2, 87(s11)
addi s0, zero, -334
L6:
srli t0, zero, 3
xor s0, s1, zero
lh a1, 12(s11)
xori a1, t2, 898
sb t2, 192(s11)
sra t0, a3, t0
sltiu s0, t0, 671
mv t2, s1
sll s0, s1, t0
ld s0, 192(s11)
blt s0, a1, L7
xori t2, a3, -1133
ori t0, a2, 1713
addi a3, a3, 106
L7:
xor t0, zero, s0
xor s1, t1, t1
slti s0, a2, 891
mv t2, s0
sub a3, t0, t1
beq s1, t0, L8
srl s0, zero, a1
slti s0, a2, -1628
bne a3, t1, L9
L8:
bltu a1, a2, L10
L9:
sub t0, t2, s1
L10:
sll a1, a3, t0
or s0, a1, s1
lhu t2, 230(s11)
addi a2, t0, -1768
slt t0, a1, a1
bgeu a1, a2, L11
beq s0, t1, L12
L11:
slt a2, s0, t2
L12:
lb a3, 49(s11)
sra s0, t2, t0
sltu a3, s1, a1
sltiu t2, a3, 212
sub a2, t0, t1
sub t2, t1, a2
sltiu a2, a1, -607
sw s0, 240(s11)
xori s1, t2, -1931
sltiu a2, s0, -1025
addi a3, t2, -409
slt t0, a1, zero
sh a1, 136(s11)
and t0, t0, t1
or a3, s1, zero
sltu a1, t2, zero
li s0, 179899230
srli s0, s1, 30
lbu s0, 246(s11)
mv t1, s0
sra t2, a1, a1
sb a1, 176(s11)
ori a1, t2, 1715
mv t1, t0
sw t1, 112(s11)
mv t1, t2
li s0, -2147483648
mv a2, s0
srli t2, s0, 14
bltu a2, t2, L13
beq a3, a1, L14
sltiu a1, t0, 135
L14:
ld t1, 216(s11)
L13:
xor t0, t1, s0
sltiu a1, a3, -37
bltu a3, t0, L15
add t1, a1, t0
lh a2, 206(s11)
sll a2, s1, a2
L15:
srl s1, t2, t1
addi s0, zero, -536
sra t1, t2, t1
sw s1, 160(s11)
