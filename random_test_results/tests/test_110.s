# rand_gen seed=110 length=100
li s11, 1024
li t0, 0
li t1, -436035698
li t2, 399198932
li s0, -1
li s1, -1
li a1, 1
li a2, 0
li a3, -2147483648
or t0, t2, s1
sll a2, s1, a1
slt t1, a3, a3
and t1, a1, s0
srl t1, a2, s0
sltiu s1, a1, 690
blt t1, t0, L0
mv a1, s0
L0:
bge t1, t0, L1
lb t1, 241(s11)
xor a1, a2, s1
sd s0, 40(s11)
L1:
srl a1, t1, t0
mv a2, a1
andi a3, a2, 1677
beq t1, a1, L2
sub s0, a3, a3
L2:
beq a3, s0, L3
blt a3, s0, L4
beq t0, a2, L5
xor s1, s1, a2
L3:
L4:
L5:
bge s0, t2, L6
sw t0, 184(s11)
and s1, a3, t1
L6:
srl t2, t2, s1
add s1, zero, t1
ori s1, t0, 787
lb t2, 88(s11)
sh a2, 2(s11)
slti t1, t2, 1466
or t1, t1, s1
bltu zero, a3, L7
sh zero, 232(s11)
slt a2, a3, s1
L7:
mv a2, s0
lhu a2, 166(s11)
sb a2, 141(s11)
sll a1, t1, zero
bgeu s0, a3, L8
beq a3, t1, L9
xori t1, t1, -1064
sra a2, a1, t1
L8:
L9:
lhu a3, 234(s11)
bgeu a1, t0, L10
srl s0, t2, t2
srl s1, a3, s0
L10:
srai t1, t2, 13
blt s0, a2, L11
sd zero, 48(s11)
slli a1, t2, 27
sltu a2, a1, zero
L11:
sltiu t1, a1, 1666
sub a2, t1, a2
addi a3, t1, -1784
add a2, t0, a1
andi a2, a3, 581
andi t0, t0, -1081
or t2, s1, t1
li t0, 1623266814
andi s1, s0, -359
lbu s0, 155(s11)
sw s0, 8(s11)
xori s0, a3, 301
and s0, s0, s0
mv s1, s0
sll a3, a1, a1
lwu t0, 116(s11)
srai t0, a2, 1
bge t2, t2, L12
srli s0, t1, 19
slti a3, s0, -1442
li s1, -2147483648
L12:
bltu s0, zero, L13
li t1, -95268944
beq s1, t1, L14
lw a3, 200(s11)
L13:
sb s0, 186(s11)
bge t1, s1, L15
L14:
sltu t2, t0, zero
bltu s1, a3, L16
L15:
xor a3, a2, a1
addi s0, a2, -1362
lbu t0, 239(s11)
L16:
xor t2, zero, s1
and s0, a1, t1
xor a3, s0, zero
li s0, -1366837560
or t2, s0, a2
beq a2, a2, L17
srl a2, zero, t2
sltu a2, a3, a1
ori a3, t1, 1823
L17:
and s1, a1, a3
lbu a1, 12(s11)
sltiu s1, s0, -26
xori t1, s0, -289
xor t2, t1, s1
and a1, a3, a1
slli a2, a3, 29
slli a2, t1, 1
