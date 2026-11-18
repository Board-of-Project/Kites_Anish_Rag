# rand_gen seed=968315605 length=100 baseAddr=4544
li s11, 4544
li t0, -2147483648
li t1, 1
li t2, 2147483647
li s0, -1111218468
li s1, -1358093520
li a1, 2147483647
li a2, 1
li a3, -2147483648
add t0, a1, s1
srl a1, t0, a2
ld a2, 56(s11)
sltiu t0, a2, -11
li a2, 20129950
slti t2, t1, 381
mv s1, a1
sub t1, s0, a2
or a3, t0, a1
add s0, t1, a3
andi t2, a1, 239
srai t1, s1, 8
li s0, 1
addi a2, t1, 1870
mv s1, a2
li s1, 2147483647
add t1, t1, s0
sub t2, a3, t1
sll t1, zero, s0
ori a1, s1, 139
srl s0, t1, s1
xori t2, t1, -703
mv t0, s0
srai t2, t2, 3
sb s1, 86(s11)
lh s1, 204(s11)
srai s1, zero, 16
xori a2, t2, 281
srai a1, a2, 6
li a1, -279666082
li a2, 0
sltu s1, s1, a2
lb a3, 250(s11)
lh t0, 162(s11)
andi t1, a3, -372
mv s1, a2
andi s1, t2, 573
and a1, t1, a3
mv a3, t2
or t0, zero, s0
slli a1, t0, 8
sh s1, 242(s11)
sra s1, s1, a1
slt s0, s0, a1
lbu s1, 81(s11)
sd t0, 48(s11)
or t1, s0, s1
lb s0, 76(s11)
slt t0, t0, t2
li t0, 2147483647
srli t2, s1, 11
sll a3, t1, s1
slt s0, t0, s0
srl s0, t2, a1
sll t2, s0, s1
sra t0, a2, a3
li s1, -2147483648
lhu a3, 164(s11)
xori a2, a2, -1497
sltu a2, s0, a2
srai s0, a2, 7
li s1, 1
lh t0, 76(s11)
srai s1, s1, 3
sb t2, 183(s11)
sw s1, 96(s11)
sb a2, 129(s11)
sltu a1, s0, a3
andi t1, t1, -2020
srli t2, a3, 10
sltiu s0, t0, -1984
li s1, 1
andi a1, t1, 967
or s0, a3, t0
ori s0, t1, -499
and t0, s1, s1
andi s0, t2, 1272
sltiu t1, a2, 1072
lwu t2, 152(s11)
ori t2, a2, 514
andi s1, zero, 1302
and t0, t2, s0
lwu s0, 212(s11)
ori t1, s0, -498
srli t0, a1, 25
slti a1, s0, 1184
sh a1, 154(s11)
slli t0, a3, 5
sh s1, 70(s11)
sh t2, 232(s11)
mv a3, s0
li s1, 105279460
slt a3, t2, s1
slt a1, a1, s1
sd t0, 128(s11)
slli s0, s1, 25
lh t0, 138(s11)
andi t0, a3, -1554
and a1, zero, zero
lw t0, 224(s11)
