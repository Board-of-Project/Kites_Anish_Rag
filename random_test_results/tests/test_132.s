# rand_gen seed=132 length=100
li s11, 1024
li t0, 1087
li t1, -1
li t2, 365013565
li s0, 1
li s1, -2147483648
li a1, -29
li a2, 1576
li a3, -2147483648
sltiu a1, a2, -1698
add t0, t2, t1
li s0, 2147483647
sh t2, 128(s11)
srai s0, t1, 11
li a2, 82061125
srl a3, a2, zero
ori a2, t1, 950
sh s1, 42(s11)
sb t0, 50(s11)
addi a1, t1, 1702
slt a3, s1, t1
lw s1, 92(s11)
blt a1, a2, L0
add a3, t2, zero
bne zero, t0, L1
srl t0, a1, a3
L0:
slti s1, t2, 1320
L1:
li a3, -665888513
sll a3, a1, a3
srai s0, t1, 2
mv t1, a2
blt a2, a1, L2
add t1, a3, a2
sltu s0, zero, t0
slti s0, a1, 1873
L2:
slt a2, s1, a3
li t1, 427790592
ori a1, a2, 1027
addi s0, t1, 1696
bge a3, t2, L3
sltiu t2, s0, -797
bne t0, a3, L4
add s0, a1, t0
L3:
L4:
li s0, -2147483648
slli t2, t0, 7
or t0, a1, a1
bgeu t2, s1, L5
slli a1, t2, 30
bne a3, t2, L6
L5:
ld t0, 152(s11)
bgeu t1, a2, L7
L6:
sltu s0, a1, a2
L7:
sb s1, 52(s11)
sw t0, 68(s11)
bltu a2, a3, L8
andi a1, a3, 2004
xor a3, t0, t0
L8:
srai t1, a2, 31
blt t2, t0, L9
sra t2, t2, t1
slt t2, t1, t2
lw t1, 112(s11)
L9:
or t0, t1, t2
sb zero, 39(s11)
bge t1, zero, L10
sub a3, s1, a2
L10:
li t0, -20566524
add t1, zero, s0
sltiu a1, s0, 1829
bge t2, a2, L11
addi t0, t0, 187
lw t2, 0(s11)
L11:
or a1, t2, t2
srli a2, t1, 8
sub t0, a2, a2
sd a1, 232(s11)
beq s1, a2, L12
lh a1, 220(s11)
L12:
andi a3, t2, 1661
sra t1, t1, a2
li a1, 355133104
sb s0, 0(s11)
sltiu t1, a1, 1918
blt s0, a2, L13
lwu a2, 120(s11)
mv s1, t2
L13:
andi t0, a2, -505
slti t2, s0, 283
sub t0, t2, s1
li t0, -1
li s1, 287942264
or t2, t1, s1
slt t2, zero, t1
ld a2, 184(s11)
srai a2, a2, 19
sh t1, 226(s11)
srai t2, a1, 14
sltiu a1, a3, -1580
or t2, s0, a1
sra a1, s1, t1
bgeu a1, t2, L14
sub s1, s0, a3
lwu s0, 96(s11)
L14:
sltu a3, t2, s1
sltiu s0, t1, -44
mv s0, a3
sb a3, 12(s11)
add a3, s0, s0
bge s0, a3, L15
L15:
nop
