# rand_gen seed=194 length=100
li s11, 1024
li t0, -1
li t1, -1
li t2, 1
li s0, 0
li s1, 135797458
li a1, -586266090
li a2, 11420280
li a3, -1
sltu t2, t0, s0
bne a3, a2, L0
mv a3, a2
L0:
sub s1, a3, t0
sw t1, 244(s11)
xori t1, a3, 790
sh s1, 108(s11)
sltiu a1, a1, -236
bgeu a3, t2, L1
bgeu t2, t1, L2
xor s0, a1, t1
lh a1, 60(s11)
L1:
L2:
lhu a3, 50(s11)
lb a2, 11(s11)
sd s0, 160(s11)
sltu t1, s1, t2
li s1, 1544136804
andi a3, s0, 1479
and s0, a1, t2
lh a2, 230(s11)
srai t1, t0, 8
or t1, a3, t0
bge t2, a2, L3
blt a2, s0, L4
and t0, t0, a2
L3:
bge a3, a3, L5
lbu a3, 19(s11)
L4:
srai t0, t0, 28
L5:
sltiu t1, t1, 1304
add t1, zero, a1
sub a3, t2, a1
add a1, t2, a2
srli a1, a3, 24
add t0, s0, a2
srli s0, s0, 2
or t1, t2, t2
srai t0, a2, 27
sub a3, a2, a3
slt a3, a1, t2
ori t0, a1, -592
ld a1, 160(s11)
ori t0, zero, -794
sd a3, 80(s11)
srl a1, a2, t2
srl a2, a2, t1
bltu s0, t0, L6
beq t1, s0, L7
lhu t1, 186(s11)
L6:
L7:
addi t0, a1, -1183
and a2, a3, zero
mv t0, t1
ori t0, s0, -48
beq t1, t2, L8
xori t0, zero, 893
L8:
bltu a1, s0, L9
srai t2, a1, 3
sub t1, a3, s1
L9:
add s1, t0, a1
srl t0, t1, s0
sra t1, t1, a2
srli a2, t0, 5
slti s0, t0, -1205
sb t0, 209(s11)
srl t1, s1, a2
xori s1, t2, -919
sub t1, s1, zero
li t0, 7079868
beq s1, zero, L10
ori s0, t0, 1887
add t1, a1, a3
li a1, 2147483647
L10:
srl t2, s0, t0
sll a1, a3, s0
add a1, s0, t1
bge s1, a2, L11
xor t1, s1, t2
bge a2, zero, L12
li t0, -1
L11:
L12:
and t2, a3, t0
blt s0, a2, L13
bgeu a2, t2, L14
sltu t0, t1, s0
bge t1, a3, L15
L13:
lw t1, 132(s11)
L14:
mv t0, a1
ori t2, t2, -1273
L15:
sra t2, a2, zero
xori s0, zero, 1868
srl s0, a2, t2
lhu t2, 76(s11)
sw t1, 252(s11)
bge a1, a2, L16
sltiu a2, s1, -848
bne t2, a1, L17
L16:
srli a3, a2, 21
andi s0, a3, 1576
L17:
slt a1, a2, a1
sw t0, 148(s11)
sb t0, 163(s11)
sw s1, 0(s11)
