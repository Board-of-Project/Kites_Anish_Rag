# rand_gen seed=184 length=100
li s11, 1024
li t0, 0
li t1, 1607819044
li t2, -272460024
li s0, 738172620
li s1, -1
li a1, 3983746
li a2, -1265566368
li a3, -1
sltu t2, s0, s0
slti s0, t0, 1125
ld s1, 120(s11)
li a2, -656592296
sw t0, 76(s11)
li a2, 187785280
andi s0, t1, 1403
sw t0, 136(s11)
sub s1, s0, a2
srai t0, t2, 25
bgeu a2, t0, L0
or t0, a3, a2
bge s1, a2, L1
slti t0, t0, 722
L0:
srl s1, t2, s0
L1:
addi a1, t0, 506
sra a1, a3, s1
slti t1, s0, -1398
slt a2, t2, s1
srl a2, t2, a3
bgeu zero, t2, L2
sltiu t2, t2, -1054
lw t0, 240(s11)
L2:
sll a3, s0, a3
slt t1, s0, t2
srl s1, a2, a3
bgeu t0, s1, L3
li a2, 0
sw a2, 108(s11)
L3:
sltiu a1, s1, -1896
lb s0, 129(s11)
lb a3, 72(s11)
sub s0, a1, t2
slti a3, a1, -362
sh a2, 206(s11)
andi s0, s1, -404
srl s0, zero, a2
sll t0, a3, t0
slli s0, a3, 20
xori s1, t0, 1646
srai t0, s0, 30
ori t2, t2, 1403
bltu t0, t0, L4
sll t2, t0, t0
L4:
bltu a2, t0, L5
bltu zero, t1, L6
blt a2, s1, L7
L5:
srl a1, t1, t2
L7:
li t2, 212351182
L6:
blt t2, s1, L8
srl a3, a3, a3
L8:
slt t0, t0, zero
ld s1, 224(s11)
sltiu t0, a1, -1374
slli t0, a3, 11
mv s0, t2
sll a2, t0, a2
bltu s0, a3, L9
xori a2, a2, -1489
or a1, t2, s0
L9:
blt t1, a3, L10
sltu a3, t1, t1
L10:
sra t1, t2, t1
bge a3, s0, L11
andi s0, t0, 158
srl a1, zero, s0
L11:
sll t2, t0, a3
andi s1, a3, -1791
lbu s1, 182(s11)
xori a3, a1, -898
add a3, t0, a1
sltu s0, s0, zero
lwu t2, 96(s11)
bge a3, a1, L12
addi a2, a3, -1471
mv s1, a3
L12:
slt a2, a3, a2
srai t0, a3, 15
lbu t2, 100(s11)
mv a3, zero
sll t2, zero, a3
sd t1, 112(s11)
and a1, t0, a2
xor a3, a3, a1
slt t0, s1, a3
or t0, t1, a1
or t0, t1, t2
sd s1, 48(s11)
lwu t1, 12(s11)
sh a3, 242(s11)
xor s0, a2, t0
slti a3, s1, 746
xor s0, s0, a3
bltu s0, zero, L13
bne a2, s0, L14
li t1, -600
blt a3, a2, L15
L13:
sra t1, t0, s0
L14:
blt a2, s1, L16
L15:
addi a2, t1, 215
L16:
nop
