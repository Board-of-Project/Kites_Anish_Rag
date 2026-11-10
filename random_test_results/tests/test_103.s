# rand_gen seed=103 length=300
li s11, 1024
li t0, -350
li t1, -2147483648
li t2, -53083405
li s0, -2147483648
li s1, 1
li a1, 523241490
li a2, -2147483648
li a3, 351
bltu s1, t1, L0
xor s0, t1, t2
li a1, -2147483648
sltu t1, s0, a3
L0:
lh s0, 16(s11)
add a3, a2, a2
sll t2, a1, zero
srl s0, a2, t1
sltu a2, a1, s0
srl s1, t1, a2
xor t2, s1, s0
mv t2, a2
slti s0, s0, 1362
sltu a1, s1, t1
andi t0, t2, -1742
andi s0, a2, 372
andi s1, zero, -29
li a2, -1
or t1, t2, t1
addi s1, t1, 547
xori s1, s0, 340
slt s1, a1, a2
sra s1, s0, s0
sll a2, s0, t0
srli a1, a3, 19
sd zero, 240(s11)
slti s1, t2, -1934
lbu a1, 99(s11)
li t0, 0
bge t2, t1, L1
andi a2, a2, -1946
or s1, t1, a3
slli a2, s1, 6
L1:
sltu s0, a2, s1
beq t2, a1, L2
lh s1, 252(s11)
L2:
sra t0, a3, t2
sb s1, 90(s11)
andi t2, t0, 271
srai t0, s0, 2
andi s1, t2, -486
slli s1, a3, 24
bne s0, a1, L3
add s1, a1, a2
and t2, zero, s1
L3:
slt a3, a3, t0
sltu s0, t0, s0
xor a2, a2, s1
sra a2, s1, s1
beq t2, a3, L4
sra a3, t1, a2
ori a2, t1, 1624
L4:
and s0, s0, a2
or t0, s1, a1
mv a1, zero
andi a2, a2, 619
sw s1, 144(s11)
slt a1, s1, zero
add a3, s1, t1
blt a3, s1, L5
add a1, t2, zero
L5:
sub s0, t2, zero
sltiu t0, t0, -1941
beq a3, a1, L6
sb s1, 188(s11)
addi t1, s1, 706
srai a2, s1, 1
L6:
or a1, t1, a1
addi t1, t1, 910
sltu a2, s0, a1
andi a1, t2, 851
lb a1, 84(s11)
slli s0, s0, 10
and s1, t0, s1
sra t0, a2, zero
sltu a1, t0, a3
bne t1, a2, L7
or a2, a2, t0
L7:
li a1, 1
xor a2, a2, t0
beq zero, t1, L8
srli a3, s0, 31
L8:
li t0, -1
sw t0, 104(s11)
bltu t1, a2, L9
sltiu a3, a2, -1888
L9:
and t1, s1, s0
sb a2, 162(s11)
beq a2, a1, L10
addi a3, a3, 189
slti a2, t1, 1670
L10:
sub t0, t1, a1
srli a3, zero, 1
slli s0, a1, 7
sra t0, zero, t0
ori t1, s0, 23
slli t0, a2, 31
xor a2, a1, t2
lb a2, 184(s11)
beq t1, a3, L11
sltu a1, t2, t1
L11:
sltiu t0, s1, 2025
slli t2, a1, 21
mv t1, a2
sltu s1, a1, t1
sltiu a3, t0, -1060
bne a3, t0, L12
and t2, t1, t0
L12:
and t1, s1, a3
and a1, s0, a3
sltu a2, t1, t0
andi a1, a2, 1902
and s0, t0, a1
bgeu a1, s0, L13
and a3, a3, zero
sra t2, s1, a3
L13:
xor t2, s1, zero
or a1, a1, a2
or t0, zero, zero
ori t1, s1, -289
li a1, 1344834981
bne t2, a2, L14
sub s0, a2, t1
sh zero, 234(s11)
L14:
andi s0, a3, 1210
slli t0, t1, 18
add a3, a1, zero
bne s0, t0, L15
sltu a1, a1, t1
L15:
xori s0, a1, -10
bgeu t1, a3, L16
sltiu a1, t1, -799
L16:
xor s1, s0, a3
bge t0, t2, L17
xori a3, s1, -1067
L17:
sw a3, 124(s11)
lw t2, 20(s11)
slt s1, a3, a3
xor t2, t0, s1
sltiu a3, s1, 1374
xori t1, s0, 570
sra s1, t1, a1
srai a1, t0, 16
ld a2, 96(s11)
blt t2, t0, L18
xor t0, t0, t2
sll a3, a1, a2
addi a3, t2, -1973
L18:
and a2, a1, t1
xor a1, s1, a3
sub a3, s1, zero
sub t2, a1, t0
xor s1, a3, a2
sra t2, t2, a2
sll t2, a1, a1
sltu t1, s0, t0
beq t0, t1, L19
bne t1, a1, L20
slli s0, s1, 2
L19:
L20:
lb t0, 22(s11)
and s0, a2, a2
slli a1, s1, 19
sltu a2, t2, s1
or s1, t1, t2
bne a3, a2, L21
xori t1, t1, 884
sh a3, 106(s11)
L21:
sra a3, t1, t0
bne s1, a3, L22
bge a3, t1, L23
sd a1, 56(s11)
L22:
L23:
slti s0, t2, 1932
xor s1, t2, t1
sltiu s0, a2, 194
ld t0, 224(s11)
mv s0, zero
xori a3, a1, 1808
srli a3, t2, 19
or s1, a3, t0
or a1, t2, s0
sltiu t2, t2, -222
xor s0, a1, zero
srli t0, a2, 20
slt a1, s0, s0
add t0, t0, t1
ori s0, s0, 178
mv a3, t2
bne s1, a2, L24
sltu t1, zero, a3
mv t1, s0
L24:
andi s0, s0, -1226
blt t2, s1, L25
lhu a1, 32(s11)
L25:
blt a2, t0, L26
xor t1, zero, t2
L26:
bgeu t0, t1, L27
sra s0, a1, t0
L27:
bne a2, t0, L28
bltu t0, a2, L29
li t0, -1
L28:
sd t2, 200(s11)
sub t2, s0, a2
L29:
bgeu a2, s0, L30
ld a1, 176(s11)
lhu a3, 172(s11)
L30:
sra a2, t1, t0
and t2, zero, a3
bgeu zero, zero, L31
slt t1, zero, zero
L31:
sltiu t2, zero, 430
srli a3, a2, 23
lwu s1, 168(s11)
slli t1, t2, 18
li t1, 2147483647
xori a1, s1, -798
or a1, a1, a3
mv s0, t1
ld t1, 112(s11)
and s1, a1, a2
beq a3, a3, L32
li t2, -2147483648
and a3, a1, t0
L32:
li t0, 1
andi t0, a1, -1903
sll s0, a3, a3
sd a3, 168(s11)
sra t2, a1, t1
srl s1, t1, a2
bne t1, t1, L33
and t0, t1, a2
L33:
sub s1, a3, a1
ld a2, 192(s11)
slti t2, s0, -720
srl t2, a3, a3
srli a3, t0, 18
andi s1, t1, 787
mv a1, t0
bge zero, zero, L34
beq s0, t2, L35
L34:
xor a2, s0, zero
slt a3, a1, s1
L35:
bne t1, s1, L36
bgeu a1, s1, L37
srl s0, t1, a1
L36:
sltiu t1, t2, 12
addi a1, a3, 886
L37:
slli s1, a1, 24
bgeu a2, a3, L38
addi s1, s1, 639
L38:
or t2, zero, a2
sd s0, 104(s11)
andi t1, t1, -1720
sub t1, t0, a2
mv s1, a3
blt s1, a2, L39
beq t1, zero, L40
L39:
slli t0, s0, 27
lbu s1, 25(s11)
L40:
sltiu s1, a2, -1406
sh s1, 56(s11)
beq t2, a2, L41
mv a1, a2
add t1, s0, s0
L41:
add s1, t1, t1
add s0, a2, s1
lwu s1, 68(s11)
or s1, zero, t1
blt s1, s0, L42
sltiu s0, s0, 1935
L42:
xor t2, a2, a2
lb a3, 53(s11)
addi t0, a2, -1422
sw s0, 60(s11)
xori a1, a1, 2007
sw zero, 192(s11)
bgeu zero, s0, L43
lwu s1, 236(s11)
xor a1, s0, s1
L43:
xor s1, t1, a1
ori a3, s0, 1879
xor a2, a1, s0
sh s1, 244(s11)
add t2, s0, a2
sltiu s0, zero, -1457
slli s0, s0, 4
sw a3, 172(s11)
sd t0, 96(s11)
li s0, -1
sltiu t2, a1, -359
srl a1, zero, t1
srai t0, s0, 1
and a3, t1, a3
mv t2, t0
or a3, a1, s0
li a1, 2147483647
or t1, t1, a1
sltiu t2, t2, -1420
and a1, t2, zero
xori s0, t2, -256
srl t0, a1, t2
