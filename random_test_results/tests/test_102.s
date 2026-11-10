# rand_gen seed=102 length=300
li s11, 1024
li t0, 1738385018
li t1, -817110372
li t2, 0
li s0, -891326368
li s1, -1010487434
li a1, 1774
li a2, -918612744
li a3, -1304703696
sub a3, a3, a3
sltiu a2, zero, -886
sub t0, s1, a3
srli s1, s0, 20
slti a3, s1, 1039
bne a1, t0, L0
lbu s0, 49(s11)
mv t1, a3
add a2, a1, t1
L0:
bne t1, a3, L1
bne t2, a2, L2
xori t1, s0, -1693
L1:
addi t2, s0, 852
L2:
sw a3, 152(s11)
andi s0, s1, -568
xori t0, t1, -925
li s0, 2147483647
sra t0, a3, a3
sh s1, 166(s11)
slli a2, a2, 20
blt a2, t0, L3
ld a2, 168(s11)
mv a3, a1
L3:
and t1, t1, s1
xori a3, t2, 1784
sh t1, 200(s11)
addi s1, s1, -1318
bgeu a1, a3, L4
bgeu a2, a1, L5
L4:
addi t0, a3, -1248
li a3, -77255640
L5:
blt t1, s1, L6
srai a2, t0, 21
L6:
li a1, -1033020000
srai a3, s0, 22
and t0, a1, s1
bge t1, a1, L7
bge t1, s1, L8
L7:
slti a3, s1, 1504
L8:
sw a2, 36(s11)
slti t1, t2, -979
sltiu t0, s1, 1137
andi s1, zero, -553
xori s1, t2, 2027
sub a3, a2, a3
xor a3, t1, s0
sra a3, a2, s0
sltiu t0, t1, 1065
mv a1, t1
bne zero, zero, L9
addi a1, s0, -363
sw a1, 192(s11)
L9:
slt t1, a3, t1
or s0, a1, a2
sd s0, 136(s11)
ori s0, t2, -928
mv t2, s1
or s0, s1, t0
bne a1, zero, L10
sra t1, s1, t0
L10:
or t1, t2, a1
lb s1, 190(s11)
ori t1, t1, 264
sub a2, a2, s1
bgeu s0, t0, L11
sra a1, s1, t0
L11:
srl s1, zero, a1
mv t2, a2
bltu zero, t1, L12
bgeu t1, t1, L13
L12:
sll a1, s1, a2
or a3, a1, t1
or t2, s1, a2
L13:
sltu a2, a2, a2
addi t2, a2, 1240
add s1, a3, t0
or a3, a2, a2
sra a1, a2, t0
ori a3, s1, -1756
mv t1, a1
sra t2, a1, s1
ld a3, 160(s11)
sll a2, s1, t0
slt t0, t2, t2
xor a2, s0, s0
or s0, a1, t2
sub s1, t0, t1
andi s1, a1, -139
sb t2, 254(s11)
xori t2, s0, 1946
sll t1, s1, t2
sub a3, t2, t0
bne a2, zero, L14
or a3, t1, t0
lbu s0, 153(s11)
L14:
bge a1, s0, L15
srl t0, a3, a2
xori s1, zero, 1727
L15:
slti t1, a1, 1140
ori t0, s1, -459
xor t1, s0, a1
slli t2, t1, 11
sltiu t1, t1, -1769
slli a3, a3, 15
add t0, a2, a1
ori t1, s0, -1673
srl t1, zero, s1
and s1, t2, t2
and t1, t2, t0
slt a3, zero, t1
sltu s0, s0, s1
sub t1, t0, a2
li t2, -863813715
sll a3, t1, a1
bltu s0, s1, L16
bne s1, a1, L17
L16:
bne a2, a2, L18
L17:
slti t1, a2, 139
beq s1, t2, L19
xori s0, a1, -1477
L18:
L19:
slt a3, s0, t2
sw a3, 188(s11)
bgeu t2, zero, L20
li a1, 2147483647
L20:
or a1, a2, a2
and s1, t2, s0
beq t0, s0, L21
sll a3, t2, t1
sltu a2, t1, a1
srai a2, t2, 9
L21:
slt t0, zero, s1
sub a3, a2, t1
sd s0, 224(s11)
sd s0, 160(s11)
sub t1, s1, a3
or t2, s1, a3
xori s0, s0, 495
addi t0, t0, -341
sra t1, a3, a3
beq t2, s0, L22
srai a3, t0, 19
L22:
sub s0, s0, t1
add a3, s1, s0
xor t1, s0, t0
sd t0, 136(s11)
mv t1, s1
lwu a2, 212(s11)
li s1, -1
sd t1, 176(s11)
addi a3, a3, 650
blt a2, t1, L23
beq a2, zero, L24
L23:
mv a1, s1
slli a2, a3, 15
srl t2, a1, t0
L24:
slti a2, a3, -1934
sltiu s0, t2, -969
lhu s1, 200(s11)
bge s0, t0, L25
sb a2, 22(s11)
L25:
beq a3, a1, L26
srli t1, t2, 22
L26:
ld t1, 104(s11)
li a1, 139669761
slti a1, t0, -1214
slt t2, t1, t2
lwu t2, 128(s11)
xori a1, t2, -1758
addi a1, s1, -961
sub s0, t1, s0
slt t1, t2, s0
add s1, t1, s1
srli a1, s0, 8
mv a2, zero
sll t0, a1, t1
bgeu t2, a1, L27
andi t2, t2, -1459
blt t1, a3, L28
L27:
andi a3, a1, 77
andi t1, s0, 1955
li t0, -219687258
L28:
beq a1, zero, L29
andi t0, t0, -1089
L29:
sd a3, 24(s11)
slli t0, a2, 17
and t1, a2, s1
sd t0, 240(s11)
xor a2, a3, a3
lwu t1, 32(s11)
or a1, a2, a3
ori s1, a2, 1153
lw t0, 136(s11)
sltiu a1, s0, -34
bgeu a1, s1, L30
bltu a3, t1, L31
blt t0, t2, L32
li t2, 2147483647
L30:
L31:
bgeu t1, s1, L33
L32:
sltiu s0, a1, 1473
andi t2, s1, 237
xori t1, a2, -274
L33:
bgeu a2, t2, L34
mv a2, a2
lw t0, 92(s11)
L34:
add s0, t2, t0
or s1, s1, a2
bne zero, a3, L35
sub a3, zero, a1
L35:
lh t2, 142(s11)
beq a2, a3, L36
blt a2, t2, L37
sub s0, s1, t1
L36:
sra s0, s0, s1
sll t0, t1, zero
L37:
sub t2, s1, a1
sltiu s0, s1, -188
slt s1, a2, s0
or a1, a1, a2
sd t2, 64(s11)
sra a1, s0, t1
and t0, a1, a3
srl s0, zero, s0
ori t0, a2, 85
li t0, -1495
sltu a2, t1, t1
slli t2, s1, 20
bne s1, a3, L38
srai t0, a3, 3
L38:
sra t0, s1, s1
sltu a1, a1, s1
sub t1, a1, t1
li s0, 293720526
bge a2, a2, L39
addi a2, a3, 939
L39:
sltu a1, t1, a3
ori a3, a3, -1613
sltiu t1, s1, 1564
andi t0, t2, -2034
add a2, t1, t2
lhu s0, 216(s11)
bltu a3, t2, L40
bltu a2, t2, L41
mv a1, t2
bge t0, t1, L42
L40:
L41:
bltu a1, a3, L43
L42:
lhu a3, 44(s11)
L43:
li a2, 0
andi t1, a1, 385
ori t2, zero, 214
sw s0, 60(s11)
sltu a2, t0, t2
or s1, t1, a1
sltu t2, s1, t0
slti t0, a2, -706
srli a3, t1, 8
blt t1, t0, L44
srli s1, t2, 8
srl a3, t0, a2
xor s1, t0, a2
L44:
slti t2, a1, 1717
li a2, 605397376
sra a3, t2, s1
sra s0, t0, t2
slt a1, a3, s1
bltu s1, a3, L45
sltu s1, a2, t1
L45:
ld t0, 240(s11)
sltu a1, s0, t2
and t0, s0, t0
andi a1, zero, -407
bltu t2, t0, L46
andi s0, s0, 812
or t1, a3, t1
L46:
sll t1, a1, t2
srl s1, t1, t0
lh a2, 92(s11)
add s0, t2, s1
sd a2, 152(s11)
slli s0, t2, 7
lhu s0, 226(s11)
srai t0, a2, 26
srai a1, a1, 18
ori a3, t1, 2003
bltu t1, t2, L47
srai s0, t1, 5
sll t2, t0, a3
xor a2, s1, zero
L47:
srl t2, t1, s1
bne a3, t1, L48
li s1, 1535272783
sw a3, 208(s11)
srai a2, t2, 17
L48:
xor a1, a1, a3
sub s0, a1, s1
and t1, t2, t2
sltiu s1, t2, -1898
slt t2, a1, t0
sub t2, a1, a1
sd t1, 40(s11)
and t1, a1, s0
