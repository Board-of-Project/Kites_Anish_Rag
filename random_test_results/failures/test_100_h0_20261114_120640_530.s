# rand_gen seed=100 length=100
li s11, 1024
li t0, -686963904
li t1, 1
li t2, -15032144
li s0, 1286273108
li s1, -657522320
li a1, -2147483648
li a2, 492
li a3, 1
lhu a1, 106(s11)
sb zero, 84(s11)
andi a1, a2, -208
sltiu a2, t0, 171
sub t2, a2, a2
li s0, 1
addi a2, a2, -531
sub a3, t2, a2
add s1, t0, t2
sra s0, a1, s1
lw a3, 48(s11)
slli a1, a1, 20
bne s0, s1, L0
srl s1, t0, t2
srli s1, a2, 2
bgeu s0, t1, L1
L0:
bge a2, a1, L2
add t0, a3, t2
xor t1, a2, t1
L1:
mv a3, a2
L2:
lh a3, 154(s11)
andi a1, a1, -1850
sub t1, a2, t0
li a3, -438166560
xor s0, s1, t1
addi t0, zero, 1834
andi t0, a2, 145
sb s0, 109(s11)
ori s1, s0, 987
blt t1, s0, L3
ori s1, s0, -1070
L3:
sltu s0, t0, t1
blt zero, s0, L4
bltu zero, s1, L5
and t0, a3, s0
L5:
slti s1, a3, 2031
L4:
sh a3, 22(s11)
sra t0, t2, t2
or s0, a1, s1
bltu t2, a3, L6
srli a1, a2, 22
L6:
sll a1, s1, a2
lw a2, 240(s11)
add s0, s0, a1
lw s1, 52(s11)
srai a3, a2, 4
xor t2, t1, t1
slli t1, a3, 21
blt a1, s1, L7
ori t0, a2, -301
L7:
sub t1, a1, t1
sltu a3, zero, a2
beq s1, s1, L8
li a2, 1
L8:
beq t1, t0, L9
ori a1, a2, -1648
bltu s1, t1, L10
L9:
xor t0, a2, a1
bge s1, s1, L11
L10:
slli t1, a3, 28
sub s1, s0, t2
L11:
sh a3, 8(s11)
bgeu a1, t1, L12
sltu s0, a1, s0
li s0, 351404091
srli t1, s1, 23
L12:
add a1, s0, t1
li a1, 1574724
sh a3, 200(s11)
and a1, s1, a3
sra a1, a2, t2
ori t2, a1, -500
sub t0, a2, zero
beq zero, a1, L13
bne t0, a3, L14
L13:
li a3, 0
L14:
bne s1, a3, L15
srai a2, zero, 18
srl s1, s1, t1
add t0, t0, a3
L15:
slli a3, a3, 2
andi a3, a2, 16
or t0, t0, t0
slti a1, a1, 1223
addi a2, a2, 440
xori a1, a2, 1923
sra s1, t1, s0
and a3, t0, zero
xor s0, s1, t0
lh s0, 26(s11)
xori a1, a3, 76
sltiu t0, a1, 1569
or a1, s0, t0
andi a2, t2, 1966
slli t1, a1, 29
beq a2, t1, L16
sd zero, 104(s11)
sub t2, s1, a3
L16:
lhu t2, 60(s11)
mv t1, t1
