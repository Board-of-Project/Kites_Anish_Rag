# rand_gen seed=2459447664 length=95 baseAddr=4416
li s11, 4416
li t0, -396954268
li t1, 1289668850
li t2, -105470100
li s0, 0
li s1, 868
li a1, -19420128
li a2, -1
li a3, 1044760791
mv t2, a3
beq s0, s1, L0
bgeu a1, t2, L1
slti t1, t0, 1347
L0:
L1:
srai t2, s1, 4
slti a3, a3, -228
lb a3, 196(s11)
li s1, -1
beq s1, t0, L2
andi t2, a1, 747
bltu a3, zero, L3
L2:
slt t0, t2, a3
L3:
slt a1, a1, s1
slt t0, a2, a3
lhu t2, 220(s11)
sd zero, 208(s11)
lw a3, 76(s11)
xori s0, a2, -212
slli a2, a3, 1
xori a2, a1, 849
mv a1, a2
srl s1, zero, s1
beq zero, s1, L4
sltu t1, a3, s1
L4:
bne t1, s0, L5
mv t0, zero
L5:
sub a3, s1, s1
and a3, t1, zero
blt s1, zero, L6
bge a3, s1, L7
slt a3, s1, s0
L6:
sra a3, s1, s1
L7:
andi a2, s1, 974
or t0, t1, zero
bne a1, t0, L8
sltu a2, a3, t2
beq s1, s1, L9
L8:
sltiu t1, s0, -883
sltiu t1, zero, 244
L9:
add t1, t0, zero
ori a1, a3, -547
slli s1, t2, 31
addi a3, s1, -599
sub s1, t2, a3
srai s0, t1, 19
srai a2, t1, 29
sd s0, 144(s11)
li t0, 497144040
andi t2, s0, 697
blt t2, t2, L10
slt s0, a2, t2
sra a3, s0, a1
L10:
add t2, zero, a1
srai a1, a2, 28
li s1, 1
li s0, 779600320
sll a1, t0, a3
bgeu s1, t0, L11
slli a1, t0, 18
ori s0, t1, -1500
L11:
srli t2, t1, 1
xori s0, s1, -275
xor a3, a3, a3
ori t2, t2, -606
li s0, -735
or s1, a2, t2
xori a2, s0, 234
xori s1, zero, -265
mv t1, zero
xori t1, a1, -261
sd t2, 144(s11)
sub t2, t2, a1
lbu a1, 34(s11)
sltu t0, a1, t2
xor t1, s0, s0
sra t1, t0, s1
slt t2, s0, a1
srai s0, t2, 26
slt a2, a1, t0
bgeu s0, a1, L12
slli s0, zero, 31
slt s1, t2, a2
L12:
beq a1, a1, L13
ld s1, 136(s11)
sub t0, a2, zero
slti a2, a1, 444
L13:
add s0, a1, a2
li a3, -1
bge a2, a2, L14
mv a2, a1
or t1, t1, t2
L14:
li s1, 0
xori t1, t2, -1987
or a1, s0, t0
ori t0, a2, 161
