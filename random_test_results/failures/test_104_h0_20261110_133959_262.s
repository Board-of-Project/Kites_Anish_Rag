# rand_gen seed=104 length=300
li s11, 1024
li t0, -1109260649
li t1, 1
li t2, -1148031000
li s0, -75267040
li s1, -326106496
li a1, 283337640
li a2, 1
li a3, -638706912
sltiu t1, s1, -1874
andi s0, a2, 344
or a2, zero, s1
sltu t2, a3, s0
xori a1, s0, -78
sltu t1, t2, t1
bgeu a2, a1, L0
sd zero, 16(s11)
sltiu a1, a3, -939
L0:
sltu t2, t1, s1
sh s1, 174(s11)
add s1, s1, s0
li a1, -2147483648
sub a2, a1, t2
slt a3, t2, t1
ori s1, a3, 524
sh t1, 186(s11)
srl t2, s0, a1
srai a3, t1, 28
sltu a3, zero, t0
sll s1, a3, a1
blt s1, a1, L1
bltu t0, t1, L2
L1:
srai a1, a1, 3
srai t1, t0, 15
slti s0, t0, -652
L2:
sltu s0, t2, zero
or t0, t1, zero
xori a1, a1, -1895
add a1, a1, a1
xor a3, t2, a1
sll t0, a1, a3
add a1, t0, t2
blt s0, s0, L3
blt a2, a3, L4
L3:
bgeu a2, s1, L5
L4:
or s0, s1, a3
L5:
addi t2, s0, -1865
ori s0, a2, -512
addi a2, t1, -346
sltu a2, s1, t1
sra t0, t0, t1
sh t0, 124(s11)
add t2, zero, a3
lw t1, 100(s11)
or s0, t2, a2
srai s1, zero, 22
ori s0, a3, 291
xori t0, t0, 890
srl a1, a2, s0
or t2, a2, s0
beq a2, s1, L6
mv t0, a2
L6:
sltu t2, a2, a3
mv s1, a1
ori a2, a2, -1988
mv t1, s0
sltu a3, t0, zero
sh a2, 122(s11)
ori t0, t2, 823
sll t2, s0, s1
sra a1, t0, s1
slli a1, t1, 17
lhu a3, 172(s11)
sltiu a1, a3, -1578
xori s1, zero, 1018
sh zero, 160(s11)
bge s0, s0, L7
xori t1, a3, -492
blt t2, s1, L8
L7:
sltiu a3, zero, -1991
L8:
mv t2, s1
sb a2, 204(s11)
slti a1, a3, -1250
srl t0, t1, s1
slti s0, t0, 1464
and s1, zero, a2
xor t2, s0, s0
sltu t1, zero, a2
lh a2, 214(s11)
slt t0, a2, s1
sub a1, a3, s0
slti a1, s1, 251
sra s1, a2, a1
ori t2, s1, 977
bltu a3, a3, L9
srai a1, s1, 15
add t2, a2, t0
blt t0, t0, L10
L9:
addi a2, s1, 1065
slli s1, a2, 6
add t1, s0, zero
L10:
sub a2, s1, zero
sra a3, t0, s1
xor t0, t1, t2
slli a2, a2, 4
srai a1, a1, 23
and t1, s1, s0
sub a2, t1, s1
sltu t1, a2, t1
bge t0, t2, L11
sltiu t2, s1, -462
sra a3, t2, s0
L11:
srli t2, s0, 17
xor t2, t0, t1
lb s0, 182(s11)
and s0, t1, a1
sll t0, a2, t0
bge zero, t0, L12
sw a3, 248(s11)
L12:
blt zero, t2, L13
sh s1, 170(s11)
and s1, zero, s1
sh s1, 138(s11)
L13:
sh zero, 8(s11)
sub t1, a1, s1
bltu t2, t1, L14
add a3, s0, a2
li t1, -1
L14:
sub s0, a1, t0
andi t1, t2, 181
or a1, t2, t2
or s1, a1, s0
and a1, s0, a1
or a3, s0, a1
sltu s0, s1, a1
srl t0, a2, t0
or s0, a1, s0
srli a2, t1, 4
sra s1, a2, t2
sra a1, t2, s0
bne s0, a1, L15
xor a2, a3, t2
L15:
sltiu t1, a3, -1292
mv a3, s0
sub t2, t1, a1
srl t2, t1, t0
beq t1, t1, L16
sltiu a1, zero, 408
add a1, t0, t2
mv t1, a2
L16:
bge a2, a1, L17
bne t0, a3, L18
L17:
xori t1, t1, -231
L18:
bltu a3, a2, L19
sub t0, a2, a1
L19:
li t1, 1
beq s0, t1, L20
srli t1, a2, 23
lbu a1, 226(s11)
L20:
srli a3, t1, 26
sub a3, s0, a1
slti a2, t0, 793
slti t2, s1, 1912
ori a3, t2, 1329
xori a2, s1, -682
lwu s1, 52(s11)
slli t1, s1, 6
lhu a2, 10(s11)
sltiu t1, s1, 1852
xori s1, a2, 1005
sb t0, 33(s11)
slti s0, t2, 602
ori t1, a3, -42
mv a2, t0
sw s0, 80(s11)
slt s0, t1, t0
sll s0, s1, s1
sd t1, 120(s11)
sub a3, a2, a2
sltu t0, t1, s0
xori s0, a1, -1951
sll a3, t2, t0
mv t0, s1
or a2, s0, a1
mv a1, a1
sll a3, t1, t1
sll t0, a3, t0
mv t1, a3
blt t2, t2, L21
bne s0, s1, L22
L21:
xori a3, zero, -221
L22:
addi a2, t1, 749
blt a2, a2, L23
bgeu a1, s1, L24
and a2, s1, a2
L23:
slt a2, t0, t1
L24:
lh a1, 102(s11)
ori s1, t0, 2026
bge t2, t1, L25
or s1, t1, s0
bge t1, a1, L26
L25:
srli a1, a1, 10
L26:
sb a2, 11(s11)
blt t0, t0, L27
sll t2, s1, a1
srl t2, zero, t1
L27:
ori t2, t1, 555
sll a1, t2, s0
srai t2, s1, 29
add a2, s0, t0
ori t1, s1, 1574
sd zero, 120(s11)
lwu a2, 140(s11)
xor a3, a2, s0
and s0, t0, zero
sltu s1, t1, a3
or a1, t0, zero
xor s0, zero, t1
li s1, 463376384
sub a3, t1, t0
addi s0, t0, -345
beq a1, a2, L28
addi t2, t0, 817
sra s0, a2, t1
L28:
bne a1, s1, L29
or s1, s0, t2
L29:
bne s1, a2, L30
andi t2, a1, 461
add a2, a1, a2
lwu a3, 208(s11)
L30:
slt s0, a2, t2
addi a1, a1, 1908
mv a3, a2
srl s0, a2, s1
lh t0, 94(s11)
li t0, 654588000
sd t1, 8(s11)
bge s0, s1, L31
add t2, zero, s0
bgeu a2, s1, L32
L31:
bltu t0, t2, L33
L32:
andi t1, s0, 207
sltu s1, a1, t2
L33:
addi a1, s0, -992
and t0, t1, s0
sra a2, t2, t2
and t1, t2, a2
srl t1, s0, s0
slti s0, t2, -810
add s0, s0, t1
and a1, t1, a1
sb t2, 236(s11)
or t0, s1, s0
srli s1, a2, 19
addi a1, a3, 1816
andi a1, t2, -960
slli s1, zero, 16
lwu t2, 208(s11)
lwu t0, 136(s11)
srl t1, t0, t1
beq a3, a3, L34
and s0, a3, a3
xor a1, zero, a3
L34:
xori t2, s0, -1697
sra a2, a2, a3
bge t2, s1, L35
sub a3, t1, t1
bne a1, zero, L36
L35:
li t1, 2147483647
ld a2, 56(s11)
ld s0, 56(s11)
L36:
beq a3, t0, L37
slt a2, a1, t2
L37:
andi a3, a3, -871
bne s1, zero, L38
lbu a3, 74(s11)
L38:
sll a2, a2, s1
slt a2, a2, s1
and t2, a3, s1
srli s1, a3, 6
srai t0, t0, 14
bgeu zero, s1, L39
xori a2, t2, -1569
sll t2, t1, a1
L39:
or t1, t1, t1
slti t0, a2, 321
srai a2, t2, 24
bltu s0, t0, L40
sra a3, t2, t2
L40:
addi a2, s0, -31
lbu a2, 34(s11)
bne a3, s0, L41
blt zero, zero, L42
L41:
bne s1, zero, L43
L42:
sra a1, t1, a2
slti a1, t1, 1955
xori a1, zero, 1403
L43:
bge s1, s0, L44
bltu a3, t2, L45
sd t2, 88(s11)
slli a3, t2, 22
L44:
L45:
srli s1, s1, 26
mv a3, a1
sd a3, 112(s11)
and s1, t1, s1
sltiu a2, a2, -1876
bgeu t2, t0, L46
bge a1, a2, L47
li s1, -2147483648
L46:
L47:
nop
