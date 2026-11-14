# rand_gen seed=143 length=100
li s11, 1024
li t0, 2010
li t1, 3107698
li t2, -536399864
li s0, -93611100
li s1, -2147483648
li a1, -1
li a2, -201873694
li a3, 796534755
and t2, t0, a1
sra s0, t0, t0
bge a3, zero, L0
srl t0, s0, t2
li t1, 0
slli a1, s0, 2
L0:
or t2, a1, t2
or t0, t2, t2
srai s0, zero, 25
srli a3, a2, 11
srl a3, t1, t1
beq t0, zero, L1
lbu t2, 172(s11)
L1:
sll t1, a3, t2
li a1, 422703151
addi s0, t0, 866
sw t1, 88(s11)
li a1, -851827488
slt t1, zero, t1
and t1, t1, s0
slt t1, a3, a1
bltu a2, t1, L2
bge a1, t0, L3
ori t0, a1, 1757
L2:
L3:
lb a2, 17(s11)
sd t1, 120(s11)
sra s1, a3, a2
blt s0, a2, L4
slti a1, t2, -152
L4:
sll s0, t0, t0
and t2, s0, s1
sub t1, t2, a2
sll s1, t1, t0
sw s1, 212(s11)
srli t0, t2, 6
bltu s1, t0, L5
xori t1, t2, 1515
slli t2, t2, 16
srli a1, t0, 12
L5:
slti a1, t2, 1080
xor a2, t2, a2
srai a2, a1, 0
srai s0, t2, 4
li t1, -97
sub t1, s0, s1
li s0, -1
slli s0, s1, 11
bltu a3, a3, L6
bltu t0, t2, L7
xori a1, t2, 1541
L6:
lbu t2, 255(s11)
ori a3, zero, -2044
L7:
srl a2, a2, a2
xor a2, t0, s1
bltu zero, a2, L8
and s0, t2, t1
add t0, t1, t1
lbu a2, 29(s11)
L8:
mv s0, t0
bltu t0, s1, L9
xor t0, s1, t2
sll t2, s1, zero
L9:
bgeu t2, t1, L10
mv t1, t2
bne a2, s1, L11
addi t1, a1, -990
L10:
lwu t2, 108(s11)
add a1, a1, zero
L11:
sltu t2, s0, a2
srl t2, s1, a1
slli s1, t1, 21
ld a1, 144(s11)
sltu s1, t1, a1
bltu zero, t2, L12
slti t1, t1, 116
sub s0, s1, a3
L12:
xor a3, a2, a2
mv s0, t0
sb s1, 12(s11)
sltiu a2, s1, 1004
bge zero, a1, L13
srai s1, a3, 17
L13:
sltu a1, t1, zero
addi a1, t0, 1317
xor s0, t0, t0
sub a3, a3, t1
slti a1, t0, 1624
srli a2, t1, 22
andi s0, s1, 938
li s0, 164866592
xori t0, s0, -1212
mv s0, t2
or t2, t0, s1
ori a2, a1, -1760
add a1, t2, s1
sll a3, a3, zero
andi t0, a2, -1885
mv s0, a3
andi t1, s0, -1707
sd t1, 24(s11)
