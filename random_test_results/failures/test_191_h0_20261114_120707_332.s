# rand_gen seed=191 length=100
li s11, 1024
li t0, -552932996
li t1, -1
li t2, 1
li s0, 2147483647
li s1, 2147483647
li a1, -1024786952
li a2, -325694584
li a3, 21553518
li a1, 472
sub a3, a1, zero
sh a1, 120(s11)
xor t1, t0, a1
addi t0, a3, -1525
and s0, t0, a3
add a2, a2, a2
srli s1, s1, 8
blt t1, s0, L0
sltu a3, t2, t1
L0:
slt s1, s1, t0
srl a2, zero, zero
sltu t2, t2, a3
andi a2, a1, -10
blt zero, a2, L1
srl a2, t0, s1
srli s0, s1, 1
L1:
beq s0, a1, L2
addi t2, s1, 1058
L2:
bge s1, a1, L3
sw a3, 12(s11)
L3:
and s1, t0, t1
bne t0, t1, L4
blt a1, a2, L5
sb a3, 51(s11)
L4:
L5:
lbu s0, 135(s11)
srl a1, a1, s0
sd zero, 192(s11)
xori s0, t1, -844
sltu s1, a3, t0
blt t2, t2, L6
add s0, t0, a3
slli a2, a1, 12
L6:
slti t0, a2, 976
lh t0, 246(s11)
slli a3, t0, 12
sll a3, a1, t2
sll t1, a2, t0
xor t2, a2, t1
srai t1, a1, 4
slt t0, t2, t1
add t2, a1, t0
bge t0, zero, L7
slli t0, t1, 6
lhu a3, 120(s11)
srai a2, a3, 28
L7:
xori a2, s1, -561
or s0, t0, s1
blt s0, a1, L8
addi s0, s1, -804
sra a3, s0, zero
slti t2, t0, -1300
L8:
xor t2, t0, s0
bltu a3, t0, L9
sll a1, a3, s0
xor a1, a3, a2
xori a2, s1, -1455
L9:
blt t0, t0, L10
ld s0, 224(s11)
blt a1, t1, L11
L10:
xori t2, a2, 1890
mv t1, t2
L11:
ld a2, 16(s11)
slt a3, s0, a1
li a1, -458706367
sd a2, 56(s11)
bne s0, s0, L12
li t0, 237742440
slti t1, a3, -269
bgeu t2, a3, L13
L12:
lbu a1, 104(s11)
bgeu t1, a3, L14
xor t1, a2, s0
L13:
mv s1, a2
L14:
blt t1, s1, L15
sw a3, 208(s11)
add a1, a3, t0
L15:
bltu t2, a1, L16
lbu a1, 88(s11)
L16:
sra a2, a2, t2
and s1, s1, a2
sltu t0, t2, s1
slt t0, a2, a3
andi a2, s1, 1838
slli t1, t2, 20
sub a2, t1, s1
srli t0, s0, 8
sra s1, a2, t0
sd t0, 192(s11)
li t0, -2147483648
bge s0, a2, L17
bltu a1, t1, L18
xor a3, a2, zero
L18:
slti a1, s1, 1150
L17:
sltu s1, a2, t1
sll a1, s1, s1
sh zero, 252(s11)
srli a1, a1, 25
sb s0, 30(s11)
sd s1, 168(s11)
