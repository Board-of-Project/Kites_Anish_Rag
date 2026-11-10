# rand_gen seed=106 length=300
li s11, 1024
li t0, 1521712360
li t1, -1
li t2, -770616910
li s0, 2147483647
li s1, -2005
li a1, -1
li a2, 661
li a3, 597289488
bge t1, t0, L0
xori a2, s0, -1929
L0:
sra t2, t0, zero
beq t2, a2, L1
bne zero, t1, L2
and s1, s0, t2
L2:
blt s0, t2, L3
L1:
lh t0, 36(s11)
L3:
and s0, t0, s0
or s1, t1, s0
or a2, t2, t2
sub a1, s0, s1
mv s1, t2
mv t1, zero
bgeu a1, zero, L4
sub a2, t0, a2
slt s1, t1, zero
xori t2, a2, -461
L4:
sll t1, a3, t2
slt t2, a2, s0
sb t1, 175(s11)
li t1, 1583
lb t0, 118(s11)
sltu s1, zero, a2
bge a2, t1, L5
lbu s1, 99(s11)
blt a1, s1, L6
and a1, t2, s1
L5:
ori t2, t1, -149
slt s1, a3, t0
L6:
sub t2, a1, t2
sltiu t2, t1, -1406
mv a3, s0
sub a3, a2, a3
sub t1, t0, s1
ori a3, a1, 157
add t2, a3, a2
xor t2, a1, t1
srai a2, a1, 29
slt t0, a2, t0
sub a3, s0, t2
ori t2, t0, 1756
sra a2, a1, a1
slt t0, t0, t0
li a1, -313795773
srli a1, t0, 23
blt s0, s1, L7
xor s1, a1, t1
beq t1, a2, L8
L7:
srli a2, a1, 25
L8:
xor s1, s0, t1
and s1, t0, s1
sub t2, a2, t1
srli t2, t0, 28
slti a1, s0, 631
sw s0, 40(s11)
bne s0, a1, L9
bltu a3, t1, L10
xor a2, t0, a1
li a1, -570422468
L9:
bne t1, t2, L11
L10:
beq t1, s0, L12
L11:
beq t2, t2, L13
L12:
lw t0, 232(s11)
slti a3, t2, 558
L13:
bgeu a1, s1, L14
sh t2, 136(s11)
sra t2, a1, t0
sb s1, 247(s11)
L14:
mv s1, s0
sub a1, a3, t2
mv a1, a2
andi a1, a3, 1528
lbu a2, 212(s11)
andi t0, zero, 1138
srli a1, a1, 26
sltiu a3, a1, 74
mv a2, a1
and a2, a3, a2
sh t2, 132(s11)
bne a1, a1, L15
sltu t2, a2, a2
slti t2, t0, 1721
lhu a3, 206(s11)
L15:
lwu a3, 48(s11)
or a2, s0, zero
or t0, s1, s1
sltu a3, t0, zero
addi a3, a3, 389
sltiu a2, t0, 655
xor s0, t1, a1
or t2, a1, zero
sll a3, t1, t2
bltu a3, zero, L16
xor s0, s1, a2
L16:
sltu a2, t2, zero
addi t0, t0, -812
xor t2, zero, s1
sltu a1, s0, s1
sll t0, t1, t2
andi t0, t2, 468
bne t2, t0, L17
sltiu a1, s0, 700
sw a2, 176(s11)
mv t1, s1
L17:
or a2, a1, s1
bge t1, a1, L18
lh a2, 208(s11)
sltu t1, t1, a2
slt a3, s1, t1
L18:
or t1, t1, t1
srai s1, a1, 3
and t0, a3, t0
srli t1, t2, 13
lhu t0, 174(s11)
bgeu a1, t0, L19
sd a1, 112(s11)
L19:
mv a3, s1
ori t1, s1, 1851
addi t2, a2, -581
mv t2, a3
slti t1, t0, 1142
mv a1, t1
sra s1, s0, t0
sub a1, a1, a1
slli s1, t0, 10
bltu s0, t0, L20
beq a1, a1, L21
mv t1, a1
addi a1, a3, -569
L20:
L21:
mv a2, a3
bge t2, t0, L22
sltu t2, t2, s0
L22:
ld t0, 72(s11)
andi s0, s0, -800
addi a3, a1, 1544
xori t2, s1, -100
add a2, zero, a2
xori a3, s1, -1731
and t0, a3, zero
blt a3, a1, L23
bgeu a1, a1, L24
L23:
sltu t0, t2, a2
sltu t2, a3, t1
L24:
mv a1, a2
add a2, a1, s0
andi a1, t0, -1380
lh t2, 164(s11)
bltu a3, a3, L25
lwu a1, 60(s11)
L25:
ori t0, s1, 1970
ori s0, t0, -1068
sra t2, t2, a1
lbu a1, 29(s11)
srli a1, a2, 5
andi s1, s0, -1499
mv a2, zero
bltu t1, a1, L26
ld a3, 208(s11)
sb t1, 241(s11)
srl a2, a1, a1
L26:
addi a1, zero, -284
srli t0, t0, 27
bltu a3, zero, L27
sll t0, a3, a3
bgeu a3, t1, L28
li t2, -2147483648
L27:
or t0, t1, s1
L28:
sltiu a1, t1, 1447
addi a1, t1, -366
sll a2, t0, a3
li s0, 0
sra a3, a3, s0
sltiu s0, zero, 1984
slli s1, s0, 22
blt s0, s1, L29
li s1, 0
L29:
addi a1, a2, 982
mv s0, t1
srli s0, zero, 13
srli t1, t2, 5
lw a3, 168(s11)
xori t1, t1, -1862
xor t2, a2, a1
srl t1, a3, a2
addi s0, t2, -1499
slli t2, a3, 10
xori s0, a2, -1557
ori s1, t2, 1656
sub t1, t1, a3
sra s0, a3, a2
and t0, t1, t2
sll t0, t2, a2
bltu a2, t1, L30
li s1, 0
sltu a3, t1, a2
L30:
ori s1, a2, 896
andi t0, s1, 1986
sh zero, 188(s11)
slti s1, a1, 1809
srl a2, s1, s1
sll a3, a2, s1
sltiu t0, a3, -1838
slti a3, t0, 1606
slt a3, a2, t2
lwu t2, 0(s11)
mv a1, t2
bgeu s0, t1, L31
srli t2, a1, 13
xori s1, zero, -4
L31:
slt a3, a2, t1
lh a1, 154(s11)
srl s1, s1, zero
sub s0, a2, s1
or t0, s0, t1
sub t2, zero, a1
ld t1, 240(s11)
sll t2, t2, s1
blt a3, a3, L32
bne zero, zero, L33
or a1, t0, a1
L32:
L33:
sub t2, zero, a2
ori t0, a2, -1459
sub s1, a2, t0
mv a1, a1
sd t2, 40(s11)
srai s1, a2, 31
li t2, -1
sub t1, t2, a3
bltu t2, a1, L34
bge t0, a1, L35
L34:
xori t2, a3, -89
ori a3, s1, 599
L35:
srl a3, t0, a3
sltiu s0, s0, -1554
bgeu t0, t1, L36
sra s1, a2, t1
beq zero, t2, L37
xori s0, a3, -1347
L36:
add a1, s0, s0
ori t1, zero, -823
L37:
srl t1, s1, t0
and t1, a3, t0
lbu a1, 245(s11)
xor s0, t0, zero
sra a1, zero, t0
sub t1, a1, s1
slli a2, a1, 31
sra t2, a2, t1
addi a2, t2, 1410
srl a2, zero, a2
sll t2, s1, a1
lhu t2, 92(s11)
sd s0, 200(s11)
bgeu a2, s1, L38
mv a2, a2
L38:
and t1, a1, s0
slt a2, s1, s0
bgeu s1, a2, L39
srl a1, a1, t1
blt zero, a2, L40
sub t1, s0, a2
L39:
sub s0, t0, s0
beq a1, a2, L41
L40:
slt a1, a3, a3
srli a2, s1, 16
add t1, t1, s0
L41:
and a2, t1, a1
srai a3, t1, 13
mv s1, a2
add a2, a2, s1
xori s1, t2, 1421
or t1, a1, s1
sra s1, t1, a3
sltiu a3, t2, 193
bge s0, t0, L42
lh a1, 4(s11)
L42:
srai a2, t2, 9
lbu t1, 156(s11)
beq t2, t1, L43
sd t2, 16(s11)
L43:
xori a1, t0, -344
addi t2, t2, 222
andi t1, s1, 663
lwu a3, 180(s11)
lb a3, 112(s11)
or a1, a2, a1
sb t0, 250(s11)
sll a1, t1, t2
add s1, s1, t0
bltu s1, s0, L44
sw a2, 84(s11)
L44:
add s1, t1, t1
bge t2, a1, L45
sll a2, a1, t0
lb a2, 56(s11)
L45:
lwu t2, 140(s11)
and s1, a1, t1
sra a1, s1, a3
srli t0, a2, 15
