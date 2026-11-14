# rand_gen seed=170 length=100
li s11, 1024
li t0, -573422670
li t1, -25699275
li t2, -1375428924
li s0, 1032395945
li s1, 1
li a1, 1016997904
li a2, 745149447
li a3, 2147483647
andi a3, s1, -1687
sb a1, 98(s11)
addi a1, a2, -521
sd t2, 136(s11)
li a1, 777586894
bltu a3, a3, L0
mv s1, s1
L0:
sll s0, s1, s1
beq s0, s0, L1
or s0, s1, s0
sub s1, s1, zero
L1:
li a2, 2147483647
sra a2, t1, t2
sub a3, a3, a1
beq a2, a2, L2
sd a1, 16(s11)
sw s1, 196(s11)
L2:
addi s0, a3, 583
sd s1, 144(s11)
slli s1, a2, 3
addi a1, s0, -1426
srl s1, t0, zero
sll t1, zero, s0
bltu t1, zero, L3
and a2, t2, zero
L3:
slt a2, s0, a1
slti s0, s1, 1861
bltu s0, a1, L4
lh a1, 102(s11)
L4:
srli t2, s0, 2
sub s1, a3, s1
sll s1, a3, zero
andi s0, s1, 1141
bltu zero, zero, L5
bgeu t0, s0, L6
add a3, t0, s1
L5:
add t2, zero, a1
li a3, -228511368
L6:
bge t0, a1, L7
li a1, 295429905
sltiu t0, t0, -102
L7:
or a3, a3, zero
andi s1, a2, -361
sub s1, a2, t2
sb t1, 100(s11)
lbu t2, 33(s11)
sltiu t1, t1, -1715
slt t2, s0, t1
mv s1, a3
xor a1, s1, s0
bltu t2, t1, L8
or a1, t0, t2
L8:
lh a1, 228(s11)
srai a2, s1, 19
sb a2, 135(s11)
sra t2, s1, a1
xori a1, a2, 1223
slt s0, a2, s0
add a3, t2, a3
sltiu t0, a1, -149
slli a1, a2, 29
sltu s1, s0, a2
li t0, 2147483647
bne s1, zero, L9
sltu s1, a3, a2
slti s0, t1, -94
L9:
beq a2, s1, L10
bne s0, zero, L11
sw t0, 36(s11)
L10:
L11:
sub t2, t0, t2
xor t2, t0, a3
bne a3, s0, L12
srl s0, s0, s1
slt a1, s0, t1
sb a3, 181(s11)
L12:
srai a3, t2, 23
bltu a2, zero, L13
lbu t2, 234(s11)
bgeu t0, a1, L14
L13:
xor a3, s0, t0
bltu s0, a1, L15
L14:
slt s0, a3, s1
srli a3, a2, 2
L15:
and t1, a2, t2
mv a3, a3
sra s0, a3, a2
sll s1, s1, t1
sh a3, 146(s11)
sltiu t2, s0, -87
lhu t2, 240(s11)
srl t1, s1, a3
sub s0, t0, s1
sltu a3, t2, a2
or s0, s1, a2
bge a3, a2, L16
bgeu a3, s1, L17
srl t1, a1, a3
L17:
lbu s1, 106(s11)
L16:
bgeu a3, a3, L18
xor s0, t0, t0
L18:
nop
