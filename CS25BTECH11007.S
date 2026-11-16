# rand_gen seed=694094546 length=66 baseAddr=3456
li s11, 3456
li t0, -167214788
li t1, -930380626
li t2, 562667924
li s0, 0
li s1, -584784526
li a1, 1
li a2, -1
li a3, -1
slli s0, zero, 9
sra a3, a2, s0
bge s0, s1, L0
sub a2, zero, zero
li t2, -1
L0:
slt s1, a2, s1
sra s1, a3, a2
xori t2, a2, 412
xori s1, zero, -287
sw s0, 96(s11)
sra s1, zero, s0
bltu t0, s0, L1
slli t0, t1, 7
L1:
beq s1, a3, L2
addi s1, t0, 602
L2:
sra t0, a1, t0
xori a2, s1, 1765
mv a3, a3
blt t1, t1, L3
sll t0, t1, a3
or t2, t0, a3
bne a2, s0, L4
L3:
li a1, 1
bgeu t1, a1, L5
L4:
srl a3, t0, t0
xori s0, a1, -1760
slt a2, a3, t1
L5:
mv s1, t0
add s0, t0, zero
li t2, -241139563
blt t0, s0, L6
addi t1, t2, -1059
L6:
blt t0, s0, L7
slti a3, t2, 432
srai t2, a1, 29
L7:
and s1, a1, t1
sw zero, 168(s11)
srli s0, a3, 2
sltu a3, s1, s1
li s1, 16867895
mv t2, a3
slt s1, t1, a2
xor s1, a3, a1
lb s0, 185(s11)
bltu s0, s1, L8
andi s1, a1, -726
li s0, 0
L8:
sltu t2, s1, s1
sh t0, 130(s11)
mv t2, a1
blt t2, s0, L9
bgeu s0, t1, L10
lw s1, 164(s11)
sra a3, t2, a2
L9:
L10:
sra t2, t0, a2
lwu s1, 200(s11)
sltu t2, t1, a1
sll a1, a2, zero
ld s1, 168(s11)
slli s1, t0, 12
slli t1, s1, 10
slli t1, a1, 16
sub t0, a1, t2
li s1, -2147483648
add a1, a2, a1
srl a2, t0, zero
