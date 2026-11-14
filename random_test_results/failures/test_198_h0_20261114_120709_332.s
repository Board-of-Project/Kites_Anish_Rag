# rand_gen seed=198 length=100
li s11, 1024
li t0, 2147483647
li t1, -1
li t2, 1
li s0, 1
li s1, 2147483647
li a1, -139675004
li a2, 0
li a3, 2147483647
xor s0, a3, t2
lwu t1, 232(s11)
xor t1, t0, zero
bltu t2, t1, L0
srl a3, s1, t0
sub a3, t1, zero
lw s0, 0(s11)
L0:
sra t0, t0, t0
mv a2, a2
sh a2, 56(s11)
sll s0, s1, s0
li a1, 2147483647
bgeu a1, a1, L1
lw s0, 220(s11)
slt a1, t1, s1
L1:
xor a3, a1, t2
srl a1, a2, a1
bne s1, t1, L2
xori t0, a1, 808
sub s1, a1, a2
L2:
bge t1, a2, L3
slti s1, a3, -522
L3:
sub t2, t0, a3
sltiu a3, a1, -1813
li t0, -1125225315
beq a1, a3, L4
bltu t1, zero, L5
lhu t1, 70(s11)
sra s1, a3, t1
L4:
sub t0, s0, s1
L5:
beq s0, t2, L6
mv a3, t1
or s1, a2, s0
li a2, 149366448
L6:
blt t1, s0, L7
lw t2, 212(s11)
sll a3, t2, a2
lbu a2, 71(s11)
L7:
bge a3, a1, L8
sll t2, t2, a2
lhu a3, 246(s11)
L8:
srl s0, s1, a1
ld t0, 240(s11)
xor t1, zero, s1
li t0, -216860949
sltiu t1, zero, 1972
sh a2, 116(s11)
lh a1, 90(s11)
add s0, t2, s1
slti s0, a3, 1359
slti t2, a3, 1742
xor s1, t1, t2
sw s1, 132(s11)
add s0, t0, zero
sltiu a3, s0, -443
add t2, t0, a2
li t1, 20558039
sra t0, t2, a2
slt a1, a1, t2
and a1, zero, a2
slli a2, t0, 13
bne s1, a3, L9
srai a3, a1, 5
L9:
sh t2, 224(s11)
mv a2, s1
bge a2, s0, L10
blt s0, a2, L11
beq t1, t2, L12
L10:
slt s0, a2, a2
L11:
sra s0, a1, a2
bne zero, a1, L13
L12:
bge s1, a2, L14
L13:
srl t1, t0, a1
L14:
slti t1, t1, -1796
and t0, a2, s1
sltu t0, s0, s0
srl t1, a1, a3
sb t1, 184(s11)
bgeu t2, a1, L15
slti t1, t2, 1439
L15:
andi s1, t1, 207
sw a2, 124(s11)
add a3, s1, t0
sra t1, s0, s0
slli t1, t0, 11
sll s0, a2, a3
or t1, a1, t0
bltu s0, s0, L16
andi s1, t2, -170
sw s1, 216(s11)
L16:
bne a3, s0, L17
sltu a2, t1, s1
L17:
srli t0, s1, 0
add s1, s0, s1
addi a1, a1, 855
mv t2, a1
bne a1, a2, L18
xori a2, a3, 1929
li a1, -469716796
bltu a2, a3, L19
L18:
L19:
nop
