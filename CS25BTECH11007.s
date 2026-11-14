# rand_gen seed=100 length=300
li s11, 1024
li t0, -686963904
li t1, 1
li t2, -15032144
li s0, 1286273108
li s1, -657522320
li a1, -2147483648
li a2, 492
li a3, 1
lwu t2, 204(s11)
sub s0, s0, t2
andi a3, a3, -1379
mv a3, a2
lh a3, 154(s11)
andi a1, a1, -1850
sub t1, a2, t0
li a3, -438166560
xor s0, s1, t1
addi t0, zero, 1834
andi t0, a2, 145
sb s0, 109(s11)
ori s1, s0, 987
blt t1, s0, L0
ori s1, s0, -1070
L0:
sltu s0, t0, t1
blt zero, s0, L1
bltu zero, s1, L2
and t0, a3, s0
L2:
slti s1, a3, 2031
L1:
sh a3, 22(s11)
sra t0, t2, t2
or s0, a1, s1
bltu t2, a3, L3
srli a1, a2, 22
L3:
sll a1, s1, a2
lw a2, 240(s11)
add s0, s0, a1
lw s1, 52(s11)
srai a3, a2, 4
xor t2, t1, t1
slli t1, a3, 21
blt a1, s1, L4
ori t0, a2, -301
L4:
sub t1, a1, t1
sltu a3, zero, a2
beq s1, s1, L5
li a2, 1
L5:
beq t1, t0, L6
ori a1, a2, -1648
lw t1, 48(s11)
L6:
andi s0, t1, 1217
xori a3, s1, 101
bge s1, t1, L7
bgeu zero, s1, L8
slti t2, a2, -700
L7:
L8:
sub a3, a3, a1
andi a2, a3, -272
slti a2, a1, -327
srai t2, s1, 5
xori a1, t0, 951
xor a1, a1, a3
xori t2, s0, 1973
and a1, s1, a3
sra a1, a2, t2
ori t2, a1, -500
sub t0, a2, zero
beq zero, a1, L9
bne t0, a3, L10
L9:
li a3, 0
L10:
bne s1, a3, L11
srai a2, zero, 18
srl s1, s1, t1
add t0, t0, a3
L11:
slli a3, a3, 2
andi a3, a2, 16
or t0, t0, t0
slti a1, a1, 1223
addi a2, a2, 440
xori a1, a2, 1923
sra s1, t1, s0
and a3, t0, zero
xor s0, s1, t0
lh s0, 26(s11)
xori a1, a3, 76
sltiu t0, a1, 1569
or a1, s0, t0
andi a2, t2, 1966
slli t1, a1, 29
beq a2, t1, L12
sd zero, 104(s11)
sub t2, s1, a3
L12:
lhu t2, 60(s11)
mv t1, t1
or t0, a3, zero
sub t1, s1, s0
addi s1, t1, -737
addi a3, t0, -1230
mv t0, t2
blt a2, t0, L13
mv s0, s1
sd t0, 224(s11)
bgeu s1, s0, L14
L13:
bge a3, t2, L15
slt a3, zero, s1
L15:
bge s1, a2, L16
L14:
add s0, a2, a2
L16:
add s1, zero, t1
xor s0, zero, s0
bne s0, a1, L17
srl t2, a1, s0
andi a2, a3, -818
and s0, t1, t2
L17:
srai t0, s1, 7
li a2, 27250215
xori a2, s0, 1153
srai s1, s0, 27
sltiu t2, t2, 1524
or a1, a1, t0
or t2, zero, a1
addi s0, a3, -1291
slli t0, zero, 6
and a2, s1, a3
bgeu t1, a3, L18
and t0, zero, a2
L18:
srl t2, s1, s1
sltiu t0, t0, 265
addi s0, a2, 50
bltu s1, a2, L19
sd t0, 64(s11)
bgeu a2, s1, L20
li t1, -333199200
L19:
xori s1, t1, -1481
bgeu t1, s0, L21
L20:
beq s0, s0, L22
add s0, zero, s1
L21:
sra t1, a2, a3
sw t2, 132(s11)
L22:
sll a2, a1, a3
xor s0, t0, t1
bne s1, s0, L23
bgeu t1, t0, L24
sra a3, zero, t1
bge a1, s1, L25
L23:
and s1, a3, a3
L24:
L25:
slti t0, a1, -2048
slti s1, a3, -1340
bne t1, a2, L26
sb t2, 103(s11)
L26:
xori t2, a1, 737
bgeu s0, t0, L27
xor s0, t2, t1
L27:
beq a2, zero, L28
mv a2, zero
L28:
sll s1, a3, t0
sltiu a2, t1, -429
xor t2, s0, a2
srl a3, a1, a3
xori a3, t1, -1525
slli t1, zero, 10
srli s1, s0, 0
ori s1, a1, 842
sra a3, t2, a1
sub a3, a3, t1
li t1, 1
slt s1, a3, s0
and a1, a2, t0
ori t2, a2, -1015
addi a1, a3, -1148
addi s1, t2, 828
sltu t2, a3, t0
srl a1, s1, s0
srl t2, t1, zero
bge a3, t2, L29
blt a2, t1, L30
srai s0, zero, 11
bltu t1, t1, L31
L29:
ori a3, t2, -1331
L30:
add a1, t2, s0
sub t2, a1, a2
L31:
sub t2, a3, s0
xor a2, zero, a3
srli t0, s1, 29
blt a3, s0, L32
ori t2, a1, -649
ori s0, a3, -535
srl a1, a3, a2
L32:
mv a3, t2
slli t1, s0, 24
sltu a2, a2, t2
slli s1, s1, 29
srli a1, s0, 11
srli s1, a1, 16
li a3, 2147483647
bltu t2, s1, L33
li t1, 385177050
L33:
bltu a3, a2, L34
slt s1, t1, a1
L34:
bne a3, a2, L35
xor a3, t0, a2
slt s0, s1, a2
lw t2, 156(s11)
L35:
ori a1, t2, -1422
xori t2, zero, 1670
xori a1, t2, -1478
beq t1, t1, L36
sub s0, t0, a1
sh a1, 232(s11)
slti a3, a2, 746
L36:
sltu a3, a3, a1
sb a2, 92(s11)
sub a2, t0, a2
sh t0, 46(s11)
beq s0, s1, L37
and t1, t2, t0
xor t2, t2, s0
L37:
sltu s0, a3, s1
bgeu a3, a3, L38
sltu t1, a1, zero
sh t1, 8(s11)
L38:
srai t2, t1, 19
andi a1, t1, 195
bltu t0, a1, L39
sub s1, a1, a3
srli t1, zero, 5
bge s0, t2, L40
L39:
sub s0, a3, s1
L40:
blt s0, s0, L41
sltiu a3, zero, 1949
srl s1, a2, a1
L41:
addi a2, a3, 1132
sub a1, t0, zero
mv t0, s1
sub a1, a1, t1
add a2, s0, t0
sub t1, a3, zero
addi t2, s1, 1185
sltu t0, t1, a1
mv t1, a1
li t1, -2147483648
bge t0, a2, L42
or t0, t1, s0
sltiu a2, s0, -214
srli t1, zero, 1
L42:
lw t0, 60(s11)
addi a2, a3, -494
xor a2, t2, a3
sb a3, 82(s11)
or t1, t0, a2
sll t1, t0, a3
or a2, a3, t0
mv t1, a1
sltu a3, t0, s1
sltiu a2, zero, -2002
srl t0, s1, a1
sb zero, 218(s11)
li s0, 1174700100
srai t0, a2, 29
addi t0, a3, -437
slt a1, a3, a1
beq t1, t2, L43
xor t2, a3, s0
L43:
xor a2, t1, s1
or a3, a3, s0
xor s0, s0, t2
slli s1, a2, 12
slt t2, t2, a2
slt a2, s0, a1
ori t0, t2, -1455
slt a3, zero, a1
slti t1, s0, 1419
slti a3, t1, -969
slt s0, t0, zero
lwu a1, 216(s11)
slt t2, a2, t0
srli a3, zero, 4
or t2, a3, s0
slti s1, s0, 860
slt a3, a2, a2
lb t1, 213(s11)
lh a1, 238(s11)
xori t2, a1, -1080
sltu t2, t1, t2
lbu s1, 99(s11)
sub a1, t2, t0
ld t1, 120(s11)
lhu t2, 134(s11)
add t0, t0, zero
and a3, a2, a2
and s1, a3, t1
or s1, t1, t1
or t1, zero, t1
ori t0, t2, -61
lhu a1, 198(s11)
mv a2, s0
slli a2, t1, 30
slt t1, a1, a2
xor t0, t0, a2
sd zero, 232(s11)
li a3, -530984295
add a3, a2, a3
or s1, a1, a1
beq s1, a3, L44
or t1, t1, t0
sltu s0, t2, t2
L44:
add t0, t2, t1
ld s0, 128(s11)
sw t0, 168(s11)
li a2, -763108971
sltiu a3, zero, -1613
