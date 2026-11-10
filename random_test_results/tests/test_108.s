# rand_gen seed=108 length=300
li s11, 1024
li t0, -653440560
li t1, -141
li t2, -224738220
li s0, -1
li s1, -1
li a1, -1223492814
li a2, -1214
li a3, 560915037
add a2, a2, a3
xor t1, t0, s0
srai t2, zero, 7
slti a3, a1, -284
li t2, 1
ori s0, a3, -665
xor t0, t0, s1
addi s0, zero, 1970
xori a3, a1, -1965
xor a2, a3, t1
andi a3, s1, -1311
beq zero, a1, L0
and t0, a1, a2
L0:
bne a2, s0, L1
lwu t2, 0(s11)
and t1, s1, t0
L1:
xor t1, a3, t0
ld t0, 216(s11)
li t2, -399430196
sltiu a1, t1, 1110
mv a3, s1
bgeu t2, t1, L2
slt t1, a2, s0
sb t1, 71(s11)
L2:
and t0, t2, a3
or t0, a3, t2
sd s0, 88(s11)
xor t2, a1, zero
slt t2, t1, a2
beq a1, a1, L3
or s1, s0, a1
sw s0, 204(s11)
L3:
sra a3, a2, zero
sb a2, 157(s11)
ori s1, s1, 460
bltu t0, t2, L4
beq s0, s0, L5
L4:
sub t1, s0, a3
bne a1, a3, L6
L5:
slti s0, t1, 119
L6:
slt a2, s0, t1
add t2, s0, s1
addi t0, a3, 595
slli t1, t0, 29
srl a1, zero, t0
bne s1, zero, L7
sra a3, t0, a1
ori a1, a2, 1300
L7:
and a3, t2, a1
sra t2, a2, t1
blt a3, s0, L8
sra a1, s0, a1
sltu s0, t1, zero
L8:
srl a3, s0, t2
srl a3, t1, s0
lh t1, 46(s11)
xori a1, t0, 1808
beq a1, t0, L9
sra a3, a1, t2
L9:
li a2, 0
andi a3, t1, -386
ori t1, t2, 954
sltu a2, s1, t1
sd s1, 192(s11)
xor a3, a3, s0
ori a3, s1, -384
sb t2, 206(s11)
lh a2, 232(s11)
sra s1, t0, t1
or s1, t1, t0
srai t0, a1, 24
beq t0, t2, L10
lhu t2, 218(s11)
bgeu a3, a2, L11
bgeu a3, t0, L12
L10:
ori s0, s0, -72
bgeu t1, a1, L13
L11:
or t0, s0, s0
L12:
li a2, 201842158
L13:
bge a3, t2, L14
lw t1, 124(s11)
sltiu s0, a1, -1531
xori t0, s0, 60
L14:
li a2, 2147483647
add t1, t2, a3
lw t1, 140(s11)
bne t0, t0, L15
and t1, s1, a1
L15:
bne t0, zero, L16
sub t2, t2, t1
xor a1, s0, t0
L16:
mv s0, a2
sw zero, 32(s11)
sb t2, 211(s11)
xor a1, t0, s0
blt s0, zero, L17
bgeu t1, a2, L18
L17:
xori a2, t0, -1115
sll t0, t0, t1
L18:
sra a3, s0, a2
sltiu a3, a2, 1857
andi t2, zero, -1396
blt t2, a3, L19
bltu a1, a2, L20
bltu a2, s0, L21
L19:
li a3, 0
L20:
sb t0, 248(s11)
srli a3, a1, 31
L21:
sll s1, a1, zero
sltu s0, t1, s1
lw t1, 156(s11)
srai t2, t2, 3
add a3, s1, s0
slti a2, t0, 71
slt t2, t0, zero
addi t2, t0, -798
sub t0, t1, t2
slt t1, a3, a2
beq a3, s1, L22
bne a1, zero, L23
bgeu s0, t0, L24
L22:
L23:
srl a3, a3, s0
mv t1, a2
L24:
sh a3, 102(s11)
ori s1, t0, -977
sb t0, 188(s11)
xori s1, t2, -1800
and t0, a3, a2
add s1, a3, a3
xori a2, a2, 1964
srli t2, a2, 27
slli a3, a2, 8
sw s0, 12(s11)
add t2, t0, a3
slt s0, a1, a3
xori t2, a2, 722
xor t1, t2, a3
sb a3, 250(s11)
srai a1, s0, 25
sltiu a3, s1, 613
xori s0, a1, -1470
srai t2, t0, 19
bge t1, a2, L25
slli a2, a1, 15
blt t0, t0, L26
srli s1, s0, 14
L25:
xori t0, t0, -586
L26:
slt t2, t1, t0
ori t2, s0, -218
and s1, zero, t0
srli s0, t2, 20
sb t2, 140(s11)
srai t1, s1, 20
or a1, t0, a1
li a1, 1
sb s1, 41(s11)
bge t2, a1, L27
li a3, 1748
bltu a1, t2, L28
mv s1, s1
L27:
bltu t0, s1, L29
srai a1, t1, 15
L28:
li s1, 0
L29:
srli t0, a1, 28
sw t2, 124(s11)
li a1, 1
sltu t1, a3, s1
and t1, t1, a2
lw s0, 112(s11)
bne t0, s1, L30
beq s0, t1, L31
lwu t0, 80(s11)
L30:
L31:
srl a1, a3, t0
or a2, t1, a2
srl t0, zero, t1
add t1, t2, s1
xor t2, a1, a2
mv a2, t1
blt a1, s1, L32
lwu t2, 196(s11)
mv s0, t2
L32:
bltu a1, a3, L33
sltiu a1, a3, -987
L33:
bltu s0, t2, L34
sltiu a2, s1, 223
L34:
bne t1, t1, L35
and a1, t0, s0
L35:
add s0, t2, a1
li a2, -1
lbu a2, 166(s11)
sd a2, 16(s11)
beq t2, t2, L36
sltu a3, t0, s1
sra s1, a2, a1
sltiu t1, s1, 1619
L36:
sd a2, 88(s11)
lbu s1, 147(s11)
srl a2, a2, t1
bgeu a2, a1, L37
and a3, a2, a2
xori a1, s1, -1013
bltu zero, zero, L38
L37:
mv a2, s0
slti a1, s0, -361
bge s0, a3, L39
L38:
sltu s0, s1, a3
L39:
xori s0, a1, -999
sltiu s0, t1, 1646
srl t1, t0, t1
bne t2, t0, L40
sw t0, 176(s11)
srai t1, t1, 9
add t0, t0, t2
L40:
ori a3, s1, -1406
sub s1, zero, s0
slt s0, s0, t2
srl a2, zero, a2
addi a2, t0, -1561
sw a1, 52(s11)
bge t1, t0, L41
sub t0, s1, s0
slti t0, t0, 1417
ori s1, t2, 247
L41:
andi t1, s0, -1722
or s1, s0, t0
sw s1, 200(s11)
sub a3, a1, s1
ori t2, a1, 2018
add a1, t0, t0
li t2, -1
bne t1, s0, L42
srli a1, s0, 11
L42:
xori a2, t2, -1847
slti t0, s1, 504
slli t0, a2, 16
li a3, -1461629169
li a3, 52046684
andi t1, t0, 707
srl a2, t1, a3
bgeu a3, a1, L43
addi t0, a1, 930
srli a3, a3, 17
L43:
beq t2, a3, L44
li t2, 1
L44:
srai t2, a3, 9
andi a3, a1, 1395
li s0, -2147483648
li s1, -1
li t2, 1286472528
srli t2, s0, 8
beq t2, t2, L45
or t1, a3, a3
L45:
bgeu a3, zero, L46
mv t2, zero
andi a1, s0, -1498
xor a1, s1, a1
L46:
srl t2, a2, zero
sra a2, a2, a2
slt t0, a3, s0
andi t0, a3, -1041
mv t1, s1
bltu s1, s0, L47
xor s1, zero, a1
sub t1, s1, s1
L47:
or a3, t2, s1
mv a3, s1
and t1, a1, a2
andi t2, zero, -1413
or a1, a2, a3
sb t2, 248(s11)
slli a1, s0, 22
slli a2, a2, 22
blt t1, s0, L48
bgeu a1, t2, L49
L48:
sltu s1, s0, a3
ori t0, a3, -1132
and t1, a2, t1
L49:
slli a1, t2, 10
mv a2, s0
and s1, t2, t1
li t0, -2147483648
addi s1, s0, 120
li a2, -191577645
bltu a2, a1, L50
xori t1, a1, -1235
bne zero, t2, L51
sh t1, 212(s11)
L50:
mv t0, s1
L51:
andi a3, t0, 981
addi t2, a1, 1619
slt a1, s0, t1
sltu a2, a1, a3
bgeu t0, a3, L52
beq s0, a2, L53
sb t0, 97(s11)
sltu t1, a3, zero
L52:
addi t1, a1, 561
L53:
li t0, 321104312
xori s0, a3, -803
sll t2, t2, a1
