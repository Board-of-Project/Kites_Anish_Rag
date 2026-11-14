# rand_gen seed=190 length=100
li s11, 1024
li t0, -505539125
li t1, -1403
li t2, -2147483648
li s0, 2147483647
li s1, 2147483647
li a1, -1
li a2, 383727400
li a3, 28121430
ori t2, t2, 811
slti a1, s1, 670
slt s0, zero, zero
add a2, t0, a2
addi t0, zero, 93
slti s0, zero, -759
slli t0, s0, 3
beq a1, zero, L0
and s0, zero, a1
L0:
bgeu t2, s0, L1
bgeu a1, s1, L2
slti t2, a3, 1873
L2:
and t1, s0, t1
L1:
sltiu a3, a1, 753
lwu t2, 176(s11)
sh a1, 226(s11)
bne t1, a3, L3
and t1, a2, a3
L3:
sll a2, a2, a1
mv a1, t1
sra a2, a3, s0
sb a1, 199(s11)
sll s0, t0, a1
srl s1, t1, zero
slt a1, zero, a2
mv a1, zero
sub t2, s1, zero
bltu a1, a1, L4
mv t1, s0
L4:
andi s0, s0, -442
ori a1, a2, -787
sub a1, t1, t1
bne a2, a3, L5
ori a2, a2, 1936
L5:
bge s0, t0, L6
bge a3, t2, L7
or t0, a2, t1
L6:
bne t2, t2, L8
L7:
sra t1, t2, a3
L8:
bltu t1, s0, L9
andi a3, t2, 1716
blt a1, t0, L10
L9:
sra a2, a2, s0
bltu a3, s1, L11
bgeu t2, a3, L12
L10:
mv s0, a2
L11:
or s0, t1, t0
and a3, s1, a1
L12:
mv t0, t2
ori a3, s0, -1117
slt t1, s0, t1
sub a1, t0, t2
srai t1, s0, 19
sll t2, s1, s1
slti t2, t0, 1607
srai a3, zero, 27
add s0, s0, a1
sb a1, 202(s11)
srl t1, a2, a1
slt t2, a2, a2
slt a3, t1, a1
li a2, 21
bne t2, s1, L13
slti a3, s0, -1381
L13:
addi t2, s1, -91
bltu t0, a1, L14
ori s1, t2, -1836
sltu a1, a2, a3
L14:
xori a1, s0, -2033
addi s0, a1, -305
blt s1, t0, L15
srli a1, s1, 31
slt t2, t0, t2
L15:
li a1, 505177013
blt t2, s0, L16
sll a1, zero, t1
L16:
andi a3, s0, 1219
lw a2, 28(s11)
sub a1, t0, s0
sh t1, 192(s11)
sra a3, s0, s1
ld a2, 200(s11)
sd a1, 240(s11)
andi s0, t2, 1726
bgeu s0, a3, L17
bltu s1, t1, L18
ori s1, a1, 1102
L18:
sltiu a2, t0, -494
L17:
sll t0, a1, a3
sh t0, 104(s11)
sub t0, a3, zero
srli t2, a3, 23
mv t0, s0
add t2, t1, s1
addi a1, a3, -138
or a2, a3, a3
li a3, 0
sh s1, 48(s11)
lh t0, 26(s11)
xori a1, s1, -2022
