# rand_gen seed=101 length=300
li s11, 1024
li t0, 0
li t1, 0
li t2, 2101362
li s0, 0
li s1, -26912056
li a1, 0
li a2, 1
li a3, 1
add a3, t2, a3
li a1, 0
andi t2, t2, 1779
blt a1, t0, L0
xori s1, a1, -1217
srai t2, a3, 6
L0:
slti s1, t2, -1096
lbu t1, 180(s11)
sll t2, s1, t1
sb t2, 38(s11)
sra a3, t2, t1
sub a2, a3, a1
bltu a3, t1, L1
slt s0, zero, t1
L1:
srai t0, a3, 0
ori s1, t2, -1542
bge a2, s1, L2
add t1, s1, t2
addi t2, zero, 693
L2:
srli a3, a3, 2
sb t1, 181(s11)
sw zero, 180(s11)
add a1, t1, t1
slt a1, s1, s0
sll a2, a2, a3
add a1, s1, t2
slt a1, t1, zero
sltiu a3, t2, 717
sd s1, 16(s11)
sltu a2, t0, s1
ori t0, t0, 896
slli t1, s1, 27
ld s0, 24(s11)
slt a2, zero, s1
mv t1, a3
sltiu s0, a3, 1968
or s1, zero, zero
and t2, s1, s1
bne zero, a3, L3
mv a2, s1
andi a1, a1, 232
L3:
sltu a2, t2, t2
ori t1, a1, 782
beq a2, t0, L4
slti t1, t2, -1614
blt t1, a1, L5
srli a2, s0, 5
L4:
L5:
sh s0, 76(s11)
li a3, 130483122
bge zero, t2, L6
xor s1, t0, t2
L6:
xor a3, s0, a3
sw t1, 12(s11)
sra a2, s0, s1
ori a3, s1, -1307
sll a3, t2, t1
slt t1, a1, s0
bgeu t2, a3, L7
slti a1, a2, 1221
andi a2, a3, -78
sb a2, 229(s11)
L7:
xori t2, t0, 1771
sra t1, t0, s0
xori t0, t1, 597
lh a1, 96(s11)
sll t2, a3, t1
ld t2, 144(s11)
li s1, 648639606
sltiu t0, s0, 906
addi a3, zero, -1184
and t1, a3, t1
sd zero, 248(s11)
lwu a3, 212(s11)
srl t1, s0, zero
sra s0, t2, s0
sltiu a3, a2, 1287
sd t2, 184(s11)
slt s1, t2, zero
bgeu t2, s0, L8
slli a1, t0, 31
lh t0, 118(s11)
sll a2, t2, a1
L8:
mv a2, zero
add a2, t0, a3
xor s1, a3, zero
slt t0, a1, s1
or a3, a2, t2
lhu t2, 252(s11)
mv t2, zero
blt a2, s0, L9
srl s0, s1, s1
L9:
slt a3, a3, t0
or s0, zero, s0
mv a3, t0
srl t1, s0, a1
ld t2, 192(s11)
and t1, t1, t0
mv t1, s0
ori t0, a3, 1863
slli s0, zero, 8
xor a3, s0, s1
slli t1, zero, 17
xor s1, a2, s1
and t0, s0, t1
li t0, 2147483647
bne t0, t0, L10
or t1, zero, t2
or t2, t0, t0
L10:
mv a1, s0
ld t0, 248(s11)
sub t0, t2, a3
addi s1, a1, -142
sub s0, s0, a1
srli a1, t0, 27
and s1, a1, s0
and t1, zero, t0
slli s1, t2, 23
ld t2, 16(s11)
bne a1, s1, L11
slti s1, s0, -967
L11:
srli a1, t0, 17
or s1, t2, zero
sra s0, s1, t1
slt t0, t0, t2
sltu t2, t0, a3
bltu a1, s0, L12
slli a1, t2, 11
lb s0, 247(s11)
L12:
sll s1, a3, zero
xori t2, a1, -922
srai t1, s0, 0
addi s0, t1, -753
slli s0, s1, 31
sll t2, t0, a2
andi a1, t1, 401
slti a3, t1, 1910
sw a1, 32(s11)
beq a3, a1, L13
srai a1, t2, 11
sra a3, s1, t2
L13:
add a3, a2, a3
slli a3, s1, 7
srl a2, t0, s0
andi a1, t2, 134
slli a3, t1, 28
srli s1, t2, 12
bge t2, t2, L14
blt a1, t1, L15
L14:
sra t2, t0, t2
L15:
bge t2, t1, L16
lw s1, 96(s11)
L16:
add a2, s1, s0
bne a2, a1, L17
lh t2, 34(s11)
sra s0, a2, a2
ori t0, t1, 952
L17:
add a1, t1, a1
sh s1, 66(s11)
add t2, zero, t0
lb s1, 1(s11)
sltiu t2, t2, -1879
srl t0, zero, zero
sh s0, 114(s11)
addi a2, zero, 693
srl a2, t0, a3
mv a1, a2
ori a2, a2, -681
sub a1, a2, t2
xor a3, zero, a2
xori a2, t1, -2032
blt a2, s0, L18
slt a2, t2, t1
bgeu a3, t0, L19
mv a2, t1
L18:
sb s1, 88(s11)
L19:
slt t0, s1, t1
addi s1, s1, -1479
sra s1, a1, t0
mv t2, t1
sltu a3, a2, zero
sub t0, t1, a3
sub t0, t1, t2
bne t2, t2, L20
xor s1, zero, s1
ori s1, a2, -1720
slli t1, s1, 11
L20:
xor t0, t2, t2
slli s0, t2, 18
addi s0, t2, -655
andi t2, a2, -1755
bltu t2, s0, L21
sw s1, 160(s11)
addi a2, a1, -1228
lw a3, 168(s11)
L21:
sd t1, 144(s11)
sll s0, a3, t0
xori a1, s0, -956
bge a1, zero, L22
bgeu zero, a2, L23
bge t2, a2, L24
L22:
L23:
and a1, t1, a3
addi a2, a1, 1530
L24:
mv a2, s0
li s0, 1
bgeu a3, t1, L25
sltiu a1, t2, 1766
L25:
and s0, t2, a3
sh s1, 12(s11)
bltu a2, a3, L26
slli a3, a1, 8
L26:
and s1, t0, a2
beq t0, t1, L27
bge a3, t0, L28
L27:
add t2, s1, s0
li t2, 1
L28:
sh t2, 232(s11)
sub a1, a2, t1
sub t2, t2, t1
sltiu t2, a3, -1862
xori t2, t1, -1460
sra s0, t2, a2
mv a2, s1
bne t0, t1, L29
andi t2, zero, -964
L29:
slli a1, t1, 9
or t2, t1, t2
slli t0, a1, 22
mv s1, s0
addi t2, a1, -1450
sh zero, 152(s11)
sra t1, s0, t0
bgeu a2, s1, L30
or s1, s0, s0
andi t2, t1, 1766
mv a3, t2
L30:
addi a1, a1, 1771
beq s1, t1, L31
sw a3, 44(s11)
srli a3, s0, 3
add a1, s1, a2
L31:
slt t2, t0, s0
add a1, t0, s1
xor a3, t2, s0
lw s1, 208(s11)
andi a1, t0, -976
li a2, -2147483648
srli t1, t1, 28
lbu a3, 210(s11)
andi t0, t0, 516
srli a2, s0, 28
srai t1, t0, 23
xori s0, t1, -1342
lb s0, 241(s11)
slli t0, zero, 0
sd t0, 128(s11)
xori t2, t2, 380
bge s1, s0, L32
sra s0, zero, s1
add t2, t2, t0
L32:
sll a1, a3, a1
srl a2, s0, s0
lhu a2, 210(s11)
bgeu a3, zero, L33
or s1, t0, t0
bgeu t0, s0, L34
slli a3, t1, 6
L33:
lb t1, 197(s11)
L34:
ori t1, zero, 1885
add t1, t0, t1
srli t2, zero, 12
bgeu t1, s1, L35
srl s1, zero, s1
xori t0, a2, -1618
L35:
xor s0, a2, a1
srl t0, a2, a3
sra t0, t1, t0
slt a3, zero, t1
xor t2, s0, s0
sb t1, 162(s11)
sub a2, s0, t1
add a3, s0, zero
li s1, 254704610
and a3, s0, a1
sh a2, 166(s11)
bge zero, s0, L36
li a1, 0
L36:
bltu a2, t2, L37
ori a3, a1, -1870
slti s1, a3, -582
L37:
and t1, a3, s1
lbu s0, 37(s11)
addi a2, a2, -1604
addi a3, a2, 125
lb a2, 228(s11)
addi a2, s0, 976
lh a1, 244(s11)
slli a2, a3, 29
bge t0, t2, L38
li a2, 54423650
srli t2, s1, 8
L38:
nop
