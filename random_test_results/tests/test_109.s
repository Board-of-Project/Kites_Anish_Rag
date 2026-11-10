# rand_gen seed=109 length=300
li s11, 1024
li t0, -2147483648
li t1, -81683132
li t2, -1
li s0, 0
li s1, -2147483648
li a1, 2147483647
li a2, -1
li a3, -708222312
sra t0, t2, s0
sd a1, 200(s11)
xori a1, zero, -534
li t1, 22312992
srli s1, t2, 8
sltiu t1, zero, 310
bgeu t0, a3, L0
and a1, t2, t0
bgeu a1, zero, L1
sltu s1, t1, s1
L0:
L1:
blt a2, t2, L2
bge a2, t0, L3
sub a2, t0, a2
and a3, zero, a1
L2:
sh s0, 228(s11)
L3:
sltu a2, s0, a2
li a2, -1912
blt a2, zero, L4
bge t2, a2, L5
sll s1, a2, t2
L4:
andi s1, a2, -1619
L5:
beq t1, t1, L6
srli t1, s1, 20
L6:
or a1, zero, t2
bgeu s0, a1, L7
sd s0, 240(s11)
L7:
sra a1, a1, t2
mv t1, a3
bge a3, a3, L8
li t2, -2147483648
lw a2, 72(s11)
L8:
slli s0, t0, 8
bgeu a2, s0, L9
srai a1, a3, 27
lb t1, 118(s11)
or t1, s0, t1
L9:
li a2, 2147483647
sd zero, 16(s11)
blt s1, a3, L10
slti t2, a3, 1080
L10:
sb zero, 222(s11)
bge s0, t1, L11
blt zero, a3, L12
L11:
ld s1, 192(s11)
L12:
sb t0, 19(s11)
bge a1, s0, L13
and a1, a1, t1
L13:
sra a1, t0, s0
sltiu t2, t0, 1716
sh a1, 192(s11)
andi a3, t1, 1059
blt a2, zero, L14
li t1, 1
bge t2, t1, L15
lb t0, 156(s11)
L14:
L15:
and s0, t0, t1
sra s0, a1, a1
srai s1, zero, 0
xori a3, a1, -1587
sh s0, 56(s11)
xor a3, s1, t0
srli t1, a3, 15
sltiu s1, s1, 418
xor a1, s1, a1
xori a3, a3, 352
sub a3, t1, t2
sb s1, 3(s11)
lbu t2, 200(s11)
addi s1, s0, 817
bne s0, t0, L16
lbu t1, 171(s11)
L16:
andi a2, t1, 1574
xori s0, t1, 1186
ori a1, s0, 1445
srli s0, t1, 16
or s0, t1, s1
and t2, t0, zero
sltu t0, s1, t1
sll a2, s1, t0
slt s0, a2, a2
xor t1, s0, a1
srl t1, a3, a3
sub a1, t1, a2
bne t1, s1, L17
beq t2, a2, L18
L17:
beq s1, s1, L19
ld s1, 144(s11)
L18:
blt a3, a2, L20
bgeu a1, s1, L21
L19:
li a3, 0
li s0, -1370
L20:
L21:
addi s0, s0, 1467
sub t1, t1, s0
sltiu a1, t2, -1796
xori a3, t1, 1310
sb s0, 220(s11)
or a3, s0, s0
slt a3, a3, s0
beq a2, s1, L22
slli t0, t1, 26
srli s1, s0, 11
L22:
bne a3, t0, L23
beq t0, a1, L24
L23:
sh t1, 28(s11)
L24:
sra t1, s0, a2
or s0, s1, t1
slli s1, s1, 3
slti t1, a2, 826
bgeu t1, s0, L25
slt t0, a1, s1
and a2, zero, a1
ori t2, t2, -299
L25:
srl t0, s0, t1
lbu a2, 127(s11)
and t1, t1, s0
beq a1, a2, L26
xor a2, a1, a3
andi t1, a3, 694
L26:
mv a1, s1
sra t1, t1, a3
sra a2, s0, a2
addi a2, s1, -1111
lbu a3, 243(s11)
sb s1, 143(s11)
li a1, -1269
add a2, t1, s0
xor s0, a2, a3
lhu a3, 222(s11)
sltu s0, a3, a2
sh a1, 220(s11)
srai a2, a2, 12
bge t2, s0, L27
lb a2, 219(s11)
L27:
slli a3, zero, 28
xor t2, s0, a2
and a1, a2, t0
xor a1, a1, t0
sub s0, a1, s1
add t1, a1, t0
mv a1, t2
lw s0, 140(s11)
ori t0, a2, 1434
lwu a1, 152(s11)
beq a2, s1, L28
and a1, a2, t1
li t0, 84329826
bgeu a2, a1, L29
L28:
slt a3, s1, t1
L29:
srli t0, t0, 7
addi a2, s0, 265
sltu t0, a3, a1
slt a1, s0, s0
slti s1, a3, 1497
slt a3, t0, t1
and t1, zero, t2
xori a3, zero, 184
bgeu t2, s0, L30
and a1, a1, s1
xor s0, s1, a3
L30:
sw a2, 64(s11)
srai a3, t1, 8
ori t2, t0, -179
bltu t2, a1, L31
bne s0, t0, L32
addi t1, s0, 369
L31:
mv t0, a1
mv a1, s1
L32:
beq a2, t2, L33
sltiu t1, t0, -875
lbu a3, 117(s11)
srai a2, a3, 4
L33:
sltiu t0, a2, 1560
lhu t0, 62(s11)
srai s0, a1, 1
add a2, t2, a1
addi s0, s1, 265
slt t0, a3, a2
xori s1, s1, 1048
bgeu s1, zero, L34
lhu a3, 170(s11)
and t2, a1, zero
li t1, 0
L34:
sw a3, 48(s11)
slti s0, t2, -1177
lb s1, 109(s11)
xori a1, t0, -623
li t1, -2147483648
bge a3, a2, L35
slli a2, s1, 22
xor t1, t1, zero
L35:
and a2, s0, a3
slli a1, s1, 1
srl t0, t2, t0
sltu a1, zero, t0
and t2, a1, s0
lb a3, 82(s11)
srli t1, a3, 6
mv t1, a2
mv a1, a3
add a3, a1, a1
bltu s1, t2, L36
mv t2, s0
and a2, t1, a3
sra s1, t1, a2
L36:
sltu t1, t0, t1
add t1, t2, zero
bne a3, a2, L37
sub s0, t2, zero
L37:
srli a1, s1, 24
lw a2, 104(s11)
slti a2, t1, 1715
sub s1, s0, a3
sltu s1, t1, t0
xori t1, a2, -1269
bge a1, s1, L38
bne t1, a2, L39
bltu zero, s0, L40
L38:
L39:
or a2, t1, t2
or s1, t1, t2
L40:
slti s0, s1, -1067
lbu a2, 82(s11)
li t1, 92103716
sub s0, t0, s0
beq s1, s0, L41
sltu s1, a1, s0
add a2, s1, s0
slt t2, s1, s0
L41:
blt s1, t1, L42
add a2, t0, a1
L42:
ori t1, t2, 2033
mv s1, t0
add a2, t0, t1
lw a3, 164(s11)
mv t0, a2
xori s0, zero, 1993
lhu a3, 38(s11)
xori t0, s0, 87
sb s1, 122(s11)
slti a2, t2, -1526
sltu t0, t0, s0
mv t1, a2
bgeu a2, t1, L43
slt a2, s1, s1
bgeu a3, a1, L44
L43:
sd s1, 40(s11)
L44:
bgeu t2, s0, L45
lhu s0, 48(s11)
L45:
slti s0, a2, -1601
li t0, -1
sltu s0, t0, s0
srai s0, a2, 23
lh s0, 216(s11)
add s0, zero, s0
sltiu a1, t1, 418
and t1, s1, t2
li a1, 0
add t0, t0, t0
srli a3, a2, 19
sra t1, a1, a3
and t1, t1, a2
sltiu t1, t0, 1639
sub a3, a2, t0
ori s1, s0, 656
srai a1, a3, 24
sd a2, 56(s11)
li t0, 0
or s1, s0, t1
addi t1, t1, 1814
bne s0, a2, L46
or s1, a2, t2
L46:
srai t2, zero, 7
srl t0, a1, zero
blt t1, a2, L47
slli a1, a2, 3
L47:
slt s0, a2, t2
li a1, 1274190928
mv t2, s1
sd s1, 248(s11)
sra a3, t0, zero
slt s0, t0, t0
sltiu s1, t0, -1502
and s0, a3, a1
sh s0, 30(s11)
xori a3, a3, -1386
srli t2, a1, 27
sra a2, t0, s0
ori a1, t2, 1811
ld a2, 176(s11)
slli t2, s0, 16
sltiu t0, zero, -1759
sll s1, a1, a2
srai t2, t2, 9
slt a3, t2, t1
lwu a2, 192(s11)
or t1, a2, t1
ori a1, t1, -1991
sltiu s0, a3, 283
srl t2, a2, s0
sltiu a1, t2, 374
srai t1, t0, 6
