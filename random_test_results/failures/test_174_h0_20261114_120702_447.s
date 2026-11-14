# rand_gen seed=174 length=100
li s11, 1024
li t0, -344291332
li t1, 1
li t2, 247584421
li s0, -449889440
li s1, -2147483648
li a1, -2147483648
li a2, 1248101721
li a3, -784570141
srl a2, zero, s0
sd s1, 16(s11)
xor s0, t2, a2
ori t1, s1, -862
xori t0, t2, -409
bgeu a2, t0, L0
sub t2, t1, s0
srai a1, t1, 13
L0:
mv s1, t2
li a1, -2147483648
and t0, zero, s1
srai t2, a3, 19
ori a2, a1, -1786
mv s1, a1
blt a2, s0, L1
slti s1, a1, 557
sra a1, t2, t0
ori s0, t1, 3
L1:
slli a1, a2, 10
add t2, a1, a1
bge s0, s0, L2
bne a1, a3, L3
and s1, a2, t1
L2:
L3:
bltu a2, zero, L4
bge a3, s0, L5
L4:
beq s1, t1, L6
bltu a1, t1, L7
L5:
addi a1, t2, -1456
L6:
xor a1, a3, s1
and s1, a1, s0
L7:
bge s1, t0, L8
sltu s0, a3, a2
ori s0, t2, -252
srli s0, s0, 22
L8:
sltu s1, s1, t2
xori a1, t2, -451
lwu a2, 24(s11)
blt zero, t0, L9
beq t0, t0, L10
bgeu t1, t0, L11
L10:
addi s0, t2, 247
L9:
L11:
lwu t1, 136(s11)
lh a3, 188(s11)
bge t0, zero, L12
sll t1, t1, s0
sw t2, 12(s11)
L12:
sub a3, zero, zero
li a1, 2147483647
bltu a2, a3, L13
addi a1, t0, 300
srl t1, a3, a2
L13:
slti t2, zero, -836
and t0, a1, s0
li a1, 1020260745
blt a2, s1, L14
sd a3, 104(s11)
ori s0, s1, -911
srl t0, t1, a2
L14:
slt t2, s1, a1
sll s1, t2, zero
or t0, a2, t1
sra a1, t0, s0
xori a2, a2, 1591
bne a1, a1, L15
or t2, a1, a1
blt s0, a1, L16
sltu s1, t0, a1
L15:
L16:
sll t1, t2, zero
lb s0, 60(s11)
srl a3, a2, s1
add a2, s0, t1
li t2, -583349520
lhu a2, 228(s11)
slt s0, t0, zero
add t0, t2, zero
andi s0, t1, 1418
slli t0, t1, 14
mv s0, a2
sltu t2, s1, t1
sh s1, 30(s11)
li a1, -944871333
xor a3, zero, t0
li s0, -50013612
lh t1, 38(s11)
slli a2, t0, 10
xor a1, s1, a2
sub t2, s0, a3
srli s0, s1, 6
sra a3, a1, a3
bgeu t2, t1, L17
and s1, a3, s1
L17:
lw t0, 68(s11)
sll t0, a3, t0
sub t0, s1, a1
mv t2, t0
ori a1, t2, -246
sra a2, s0, s0
sra t0, a2, t0
xori s0, t1, 1935
xori s1, zero, -1692
