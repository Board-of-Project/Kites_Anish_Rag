# rand_gen seed=145 length=100
li s11, 1024
li t0, 9681318
li t1, -41273076
li t2, 43265912
li s0, 687521667
li s1, 454633343
li a1, -457399368
li a2, 2147483647
li a3, 774
sra a3, a2, t1
bge a2, zero, L0
mv t2, a3
L0:
bgeu s1, a2, L1
sh s1, 194(s11)
L1:
li a1, 2147483647
slti t2, a1, -779
beq a1, s1, L2
sub t0, a2, t0
L2:
blt s0, s0, L3
slli a3, a2, 28
L3:
lbu a1, 56(s11)
andi t0, s0, -250
sll a2, s0, a1
bltu zero, t0, L4
xori t1, t1, 428
L4:
xori t0, t1, -1413
sw t1, 132(s11)
andi a3, a2, -1104
sub a1, a2, t2
or s1, s1, s1
addi a1, a3, -641
andi a2, t0, -1460
or a2, a1, a3
bne a2, a1, L5
slti t1, s1, -713
slti t0, s1, 715
li a1, 2147483647
L5:
sub a1, zero, t2
srai a3, s1, 11
beq t1, s1, L6
mv a3, s0
sb a3, 72(s11)
L6:
sub s0, a2, s0
or a2, zero, s1
and s0, s0, s0
li t2, -161266307
xori a3, zero, -1145
li s0, 614022696
addi a3, s1, -1933
slt a3, a1, s1
xori t2, t2, 1028
lw s1, 152(s11)
sh a1, 242(s11)
slli t1, t2, 26
xori t2, zero, -1778
sub s0, a3, t2
srl a3, a2, a1
sll s1, t0, t2
andi t0, s0, -1338
mv s0, t0
xor s1, a3, t0
sll s1, t0, s1
sh t1, 140(s11)
bltu t1, t0, L7
sltu a2, a1, a1
L7:
lh t2, 8(s11)
sll s1, a1, a1
srli t2, s1, 28
slli a3, t2, 3
xori t1, t1, 850
sra a3, zero, t1
ori a2, t1, -501
li t1, -416380150
srli a1, t1, 10
addi a2, a2, -1233
srai a3, t0, 20
andi t0, a3, -1312
and t2, a3, t0
sub t2, s1, a1
add a1, s0, s1
srai t0, s1, 27
mv a3, a2
sw t2, 248(s11)
sub t0, t1, a2
sltu a2, t0, t0
bgeu t2, t1, L8
sltiu t0, a2, -1600
sll t0, t0, t0
beq t2, a2, L9
L8:
or s1, s1, t1
sub t2, a1, s1
L9:
or a2, s0, s1
blt a3, a1, L10
bgeu t1, s0, L11
sra t0, t2, a3
L10:
and t1, t1, s1
sw t2, 184(s11)
L11:
blt t2, a1, L12
sra t2, a2, zero
L12:
add t2, t0, t1
srl a1, t2, s1
bltu t0, t2, L13
mv s0, zero
beq a1, s0, L14
slti a1, t0, 393
L13:
blt t0, t1, L15
sd t2, 232(s11)
L14:
sltiu t0, a3, 1496
lb t0, 188(s11)
L15:
nop
