# rand_gen seed=105 length=300
li s11, 1024
li t0, 461
li t1, 0
li t2, -1
li s0, 769437884
li s1, 0
li a1, 2147483647
li a2, 2147483647
li a3, 2147483647
addi t1, zero, -696
bge s1, a1, L0
lwu t1, 84(s11)
or t1, t2, t1
L0:
sltiu t0, t0, 1833
sd s0, 104(s11)
slli t2, t0, 25
bltu t2, zero, L1
sltiu t1, s0, -408
bgeu a3, a3, L2
L1:
slt t0, s1, s0
L2:
slli s1, s1, 31
ori t2, a2, -757
add t2, a3, t1
addi t1, a2, -812
sh a1, 94(s11)
xor t0, a1, t2
sub a3, t0, t0
bne t2, zero, L3
sub t2, t2, zero
bgeu t2, t1, L4
or a2, a3, t2
L3:
L4:
xori t2, s1, -1079
li a2, -32084715
addi a2, a1, 911
sltu t2, t1, a3
sll a3, s0, a3
sb t0, 112(s11)
slli t2, s0, 9
andi t0, t1, 1904
sh t0, 180(s11)
li t0, 527025174
beq t0, s0, L5
addi s0, s0, -885
L5:
srai t2, zero, 26
slti t0, s1, -1920
andi a1, t0, 1667
xor s1, a1, a1
bltu zero, t0, L6
mv a2, a2
L6:
add a2, a1, t1
andi s1, a1, 406
slli t1, s1, 22
blt t0, s0, L7
mv s0, a2
mv s1, t1
L7:
beq s0, a1, L8
bltu t0, t0, L9
slli s0, s0, 31
or t2, s0, t0
L8:
mv a3, s1
L9:
bgeu t2, t1, L10
addi s1, s0, 1368
sltiu t0, t0, -1966
sra a1, t1, t2
L10:
addi s0, t0, 945
sll a2, a1, s1
sb t2, 218(s11)
li a3, 1
bne s1, s1, L11
lw t2, 28(s11)
li a1, -1
L11:
addi a1, t2, 26
or t0, a1, s0
sw a2, 116(s11)
xor t0, a2, t2
or t1, t1, s1
addi s1, a1, 1072
xor t2, t1, t2
lwu t1, 16(s11)
srai t0, t0, 22
sll a1, s0, t1
li a1, -503815950
and t0, s1, a2
or a1, zero, s0
slti t1, zero, 172
sub a2, t2, zero
bne s0, t1, L12
beq t1, t0, L13
L12:
add a2, a1, s0
srl t2, t1, t1
L13:
add a3, zero, a3
andi a3, a2, -161
lb t1, 10(s11)
sltiu a3, zero, -1139
slti s0, a2, 1619
xor t0, t2, a3
or s0, s0, t2
slti t2, s0, 188
bge a2, s0, L14
slti s1, a2, 822
bge t1, a1, L15
sh zero, 166(s11)
L14:
L15:
sw a3, 72(s11)
ori a3, t1, -1963
mv a1, a2
or a3, t0, a2
srai a2, s0, 31
sll s0, zero, t0
sll s0, zero, t2
srai s0, t1, 27
lbu s0, 51(s11)
slt t1, a1, t0
slt a3, a2, s0
srli t2, t0, 24
sll s1, s1, t1
andi a1, s0, -1152
slt s0, t0, t1
srai a2, t2, 27
bne a1, s0, L16
li s1, -1176
sltu a1, s1, s0
L16:
sb a1, 40(s11)
sltu s0, a3, t0
or s0, t2, t1
bge s1, a3, L17
sra t1, s1, s0
sd a3, 160(s11)
L17:
ori t0, s1, 1360
ld t0, 64(s11)
ori a2, s1, -373
or t2, s0, a3
sll t1, a1, s1
sll s0, t2, s1
bne s1, t2, L18
slti a2, t0, -1260
srli a1, s1, 5
bgeu a1, t1, L19
L18:
andi a2, a3, -334
L19:
li t1, -2147483648
bne a1, t0, L20
lb a3, 37(s11)
L20:
xori a3, t0, -1735
li a1, 577625275
bltu a3, s1, L21
slt t2, a2, t2
slli s0, a2, 10
L21:
addi a2, a1, -1217
xor s1, a3, a3
srai t2, s1, 7
and s0, t0, s0
slt t0, s0, zero
beq t1, t1, L22
li s0, -28832220
and t2, t0, t1
xor t0, t0, s0
L22:
and t1, t1, a3
sll s1, a2, s0
ori s0, t2, -185
slti a2, zero, -1381
sub a1, t0, t1
addi s0, zero, -1556
sh t2, 58(s11)
srli s0, a2, 3
xori t2, zero, 1666
or s0, t0, t0
sltu a2, s1, t0
bge s0, s1, L23
li t0, 0
L23:
xor a2, zero, a3
srl t1, a2, a2
srl s0, t1, t2
slti t0, a1, 71
or t2, t2, t1
andi s0, t0, 1258
sltu a2, s0, a3
sltiu t2, s0, 1555
beq a2, a3, L24
add t0, a1, a1
slti t2, s1, -1572
L24:
slti s1, a2, -1433
andi a3, zero, 1632
sltu a2, s0, s0
sw a1, 24(s11)
lw a2, 104(s11)
sub a3, s1, t0
srl a1, t0, s1
and a3, a2, a1
mv t0, s1
sra s1, zero, t2
bge a1, t0, L25
or s0, t2, s0
L25:
bltu t0, a2, L26
sltiu t1, t2, 1163
bgeu s0, t2, L27
L26:
sra a1, t0, a3
L27:
mv t0, t2
srai a2, t2, 25
sll a2, a1, t2
ld a2, 224(s11)
bge s0, t0, L28
bltu zero, s0, L29
xor a3, t1, s1
L28:
srai t0, a1, 2
L29:
sll a1, t0, t2
sra a1, a1, s1
sll s0, a1, t2
or t0, a3, t2
bne a3, t2, L30
srl t2, t0, a2
addi t0, a1, -1940
L30:
slt s0, t2, t2
bne a1, a3, L31
or a2, zero, a2
L31:
sltiu t2, t2, 817
sh a1, 92(s11)
and s1, t1, a1
lh a3, 10(s11)
slti s1, t2, 394
srl t2, t1, s0
addi a1, a3, -2
slt t0, s0, a1
lw t0, 96(s11)
lbu s0, 42(s11)
and t0, s1, s1
bgeu a3, s0, L32
sub t1, a3, zero
L32:
sltiu a1, a1, -1884
mv a1, t1
sub a1, s1, t0
or s1, a1, t2
bltu t1, a2, L33
srai t1, t2, 17
L33:
bge a2, a2, L34
sub t2, t1, s0
L34:
bltu t0, s0, L35
bne a3, t0, L36
slti a3, a1, 192
L35:
srai t1, zero, 22
slt a1, s0, t1
L36:
and t0, t2, s1
and t1, a3, a3
srli t1, s0, 24
slli a3, t0, 7
sra s0, a3, a2
srai s0, t0, 15
blt s0, a3, L37
sd t2, 224(s11)
L37:
beq s1, s1, L38
xor a2, a2, zero
blt a3, t1, L39
L38:
add t2, zero, s1
or a3, a2, s0
L39:
mv a2, t0
sltu a1, zero, zero
andi t2, a2, 879
or t2, t0, s1
xor t0, t0, t1
sll t2, t0, a1
slti s0, s0, 678
sll t0, a1, s0
xor a3, s1, t1
sltiu t2, t0, 922
lbu a1, 30(s11)
beq t2, t2, L40
bge s0, t2, L41
L40:
sw s0, 44(s11)
srai s0, t1, 12
srai t2, a3, 27
L41:
lh t1, 66(s11)
mv a2, s1
or s0, zero, t2
xor a1, a2, a2
sub t2, s0, t0
bne a1, s0, L42
sub t0, zero, a1
L42:
xori s0, t0, -496
sltiu s0, t1, -1967
xor t1, s1, s1
lh t1, 40(s11)
lb t0, 166(s11)
addi s0, t0, 1632
andi s1, s0, 1365
sll a1, t2, t0
blt t2, s1, L43
xor a2, a3, zero
L43:
and t0, a3, t1
sltu t2, a3, t0
andi a1, zero, 1504
sub t1, t0, t0
beq t2, t1, L44
bltu t2, zero, L45
xor t2, zero, s1
L44:
L45:
sub a2, a3, s1
xor t2, a2, s1
and t2, t0, s0
ld t0, 96(s11)
ld t0, 24(s11)
xori a3, t1, 388
sra s0, a2, a2
lh a1, 178(s11)
or a2, t1, a3
sra t2, zero, zero
slli t1, t2, 22
lb t1, 247(s11)
bge t1, s1, L46
sltu a1, t1, a1
L46:
beq a1, t2, L47
mv s1, t1
li s0, 1160
L47:
nop
