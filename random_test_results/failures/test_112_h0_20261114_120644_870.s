# rand_gen seed=112 length=100
li s11, 1024
li t0, 1527
li t1, 0
li t2, -2972550
li s0, 809441952
li s1, 2147483647
li a1, 232816368
li a2, 0
li a3, 594604855
blt s0, a2, L0
lwu s1, 196(s11)
slt t2, a3, t1
L0:
li a3, 943
slli t2, a2, 10
slli t0, t0, 28
sub t1, zero, t0
sd t0, 72(s11)
xor a3, t1, t2
srl a1, a1, s0
li t2, -49210331
andi a1, a1, 171
bne s1, a1, L1
blt a2, t2, L2
slti s0, t0, 0
L1:
L2:
srai t1, zero, 25
li a1, -1
and s1, t1, t2
ori t1, t2, 1855
beq t2, s1, L3
andi t0, a2, 802
L3:
lw t0, 156(s11)
srl a3, t2, s1
slli a2, a3, 13
bge t0, s0, L4
bgeu a3, t0, L5
addi t2, zero, -578
L4:
bge a3, t0, L6
L5:
ori s0, a3, 1987
lh a3, 174(s11)
L6:
li t1, -106434675
sll a2, a2, s0
bne s0, zero, L7
sra a3, t1, t2
sub t1, a1, t0
sd t0, 136(s11)
L7:
sltu a1, t1, s0
bge a2, s1, L8
bltu s0, zero, L9
or t0, s1, s0
L9:
xori a3, t2, -1520
L8:
add a1, s1, s0
add t2, a2, a2
or a1, s1, zero
li a1, 622342776
xor t1, t1, t0
bge t1, t0, L10
blt t1, s0, L11
bgeu t2, s0, L12
L11:
andi a3, a3, 753
L10:
bge a3, zero, L13
xori s1, t1, 255
L12:
L13:
and s1, t2, s0
slti t0, a3, 2024
li a3, 196781406
lwu t0, 168(s11)
sra t1, t1, s0
slli t1, t2, 7
bltu zero, t2, L14
mv t1, t1
or a3, a1, t2
or a1, t2, t0
L14:
xori a3, a2, -800
blt t0, a3, L15
bgeu t0, a1, L16
xor a1, s0, zero
L15:
L16:
and s0, a3, t1
xori s0, s1, 1780
xori s0, t2, -1055
slli s0, a1, 15
sll a3, a2, a3
slti s0, s0, 209
sltu s0, s0, t1
bltu s1, s0, L17
andi a1, t0, -631
bgeu a3, a1, L18
L17:
or s1, a3, s1
L18:
add a1, t0, t1
lw a2, 136(s11)
mv a3, s0
bne t0, t0, L19
add a3, a1, a2
L19:
bltu a1, a3, L20
srai a3, a2, 10
L20:
or s1, t0, s0
sd s0, 72(s11)
sltu a3, s0, t1
sll t1, a3, a2
sltu s1, zero, a2
srli a3, s1, 13
sll t0, s1, a2
srl s0, zero, t0
li s0, 0
li s1, 20
bltu t2, a1, L21
bltu a1, t1, L22
li s1, 1
L21:
sra t1, a3, t2
L22:
srli s0, s1, 10
add a3, s0, s0
