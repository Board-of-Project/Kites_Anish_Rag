# rand_gen seed=1360966198 length=200 baseAddr=7744
li s11, 7744
li t0, 2147483647
li t1, -1
li t2, 0
li s0, 1679597546
li s1, -1181018902
li a1, -84279016
li a2, 0
li a3, -1
li t2, 2147483647
slti s1, t0, 729
sub a1, t2, a1
xori s0, a2, -405
blt a1, s1, L0
sll a1, a1, t1
xori t0, t0, 1073
L0:
ori s1, a1, 1131
sub s0, a2, a2
mv a3, a3
slli t0, a2, 20
sub t2, zero, t0
blt s0, t2, L1
andi s0, s0, 78
or s1, a2, a2
sll t1, a3, s0
L1:
sll t2, a3, a3
blt t1, t0, L2
mv a1, t2
L2:
add a2, a2, a2
slt a3, t2, a3
blt a2, a2, L3
srl t0, s0, a2
L3:
mv s0, zero
sltu a3, a2, s0
sltiu t1, t1, -175
add s1, t1, a2
slt s1, t2, a1
bne zero, s0, L4
sh zero, 170(s11)
srli a2, a3, 29
and t0, t2, s1
L4:
beq s1, t0, L5
lw a1, 192(s11)
mv t2, s1
sra t0, a3, t0
L5:
sh s1, 196(s11)
add a1, zero, a3
slti t2, t2, 184
and t0, a3, t1
xori t2, t2, 177
slli a2, a3, 11
bge a3, a3, L6
srl a1, s1, s0
lwu s1, 172(s11)
L6:
sra s0, t0, zero
sltu t2, a1, a2
addi a1, a1, 775
beq a3, s0, L7
bne a3, zero, L8
sltu s0, s0, a2
L7:
L8:
slt s0, s1, t2
add s0, a1, a2
ori a2, s1, -1715
srl a1, t2, a3
sra t2, a2, a2
mv t1, t0
addi t1, t2, -395
lw a3, 224(s11)
or a1, t1, t2
xor t2, s0, s0
ld t0, 240(s11)
or t0, zero, a2
ori t1, a3, 857
lwu t0, 72(s11)
li t1, 1
sw t1, 240(s11)
xori s0, zero, 1671
addi a3, a2, -1344
srai t2, a3, 4
blt t2, t0, L9
xor a1, a2, s0
sh s1, 224(s11)
sll a1, t1, a1
L9:
srl t0, a3, t2
sub t1, s0, t2
or t2, a2, t1
sub t0, t1, a1
bltu a2, zero, L10
slti t1, t2, -1438
addi s1, t2, -1606
bge a2, zero, L11
L10:
add a3, a1, zero
sb a3, 185(s11)
L11:
beq t0, a1, L12
lw t2, 204(s11)
bne t0, a2, L13
L12:
bne s0, t2, L14
srai s1, t0, 29
sb t0, 71(s11)
L13:
sub s0, t1, a1
L14:
addi t1, t2, 1825
li t2, 2147483647
sw t0, 132(s11)
add s1, a1, s1
or s1, t2, t1
sub a2, s1, a3
and a2, t2, s1
bltu s1, zero, L15
mv a1, s0
sub s1, a2, t0
L15:
ld a2, 216(s11)
sub a2, s0, zero
andi s1, s0, -2047
ori t0, t2, -179
sub t0, zero, a1
slt t2, a3, a3
slli a3, a2, 17
srli s0, a3, 0
srl s0, s0, a3
and a1, a3, s0
ori s1, t1, -1377
sub a1, t0, s1
sb s0, 91(s11)
lw t1, 132(s11)
li a1, -1
and s0, t0, a2
xor t2, t0, t1
srli a2, s1, 0
sltiu a3, a1, -1279
addi t0, a1, -190
xori t0, s0, -376
xor a3, t0, a2
bgeu t0, t1, L16
xor s0, t1, t2
L16:
ori s0, a3, -1711
and t1, a2, a1
bgeu a1, s1, L17
sltiu t2, t1, 485
lhu t2, 90(s11)
L17:
lb t0, 113(s11)
li t0, 2147483647
add s1, a1, t0
andi a3, s0, -340
xori t1, a3, 710
addi a3, t0, -1310
ori t0, t2, -635
bltu a2, t0, L18
or t0, a3, zero
sub a3, a2, t0
slt s1, a1, a2
L18:
andi a3, s0, 1165
bne t0, t0, L19
sw t0, 40(s11)
ori t0, s1, -141
srli t2, t1, 24
L19:
sra s1, a2, t2
sra t0, zero, a2
bltu s1, t2, L20
lw t0, 208(s11)
L20:
blt s1, t2, L21
bge s0, t0, L22
L21:
lhu a3, 46(s11)
sh s1, 178(s11)
mv a1, s0
L22:
add t2, a2, s1
andi s0, s0, -482
li a3, 773025010
srl t1, a3, s0
lbu s1, 157(s11)
sltiu t2, t1, 1249
bne t2, t2, L23
blt t2, t1, L24
lb t0, 21(s11)
slli t0, a3, 9
L23:
L24:
slti a2, t0, 569
lh s0, 48(s11)
mv t0, t2
sltu a2, t1, t2
srl t0, t0, s0
and t2, a2, s1
addi t2, t0, 1382
sll s0, s0, t0
sll a3, s1, s0
beq t1, a3, L25
li t2, 0
L25:
blt t1, a2, L26
add a2, a2, t2
sltiu t1, s1, 283
li a2, 0
L26:
or a2, t1, t2
sll t0, a1, a1
mv a1, zero
sub t0, a1, t0
sltu s0, zero, t0
or t0, t0, a1
sltu a2, t1, t1
sd t1, 144(s11)
sh zero, 80(s11)
andi s1, s1, 1855
bne s0, s0, L27
srai a3, t1, 14
sd a2, 136(s11)
L27:
srai s0, t0, 14
sltiu a2, s1, -1367
sra t0, zero, t0
srl s0, zero, a2
blt s0, a1, L28
lb t1, 219(s11)
srli a1, t2, 29
L28:
nop
