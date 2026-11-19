# rand_gen3 seed=785932797 length=50 baseAddr=3904
    li s11, 3904
    li s5, 243
    li a2, 2147483647
    sub a4, s5, a2
    li a3, 1
    li s0, -2147483648
    and a1, a3, s0
    li s7, 1
    li s3, -2147483648
    xori t5, s7, 1670
    ld t1, 248(s11)
    xori t1, t1, 367
    sd t1, 248(s11)
    li s2, 0
    li t6, 12
    add s6, s2, t6
    srli a7, s6, 6
    sltu a5, a7, a7
    srl t2, a5, s6
    srl a3, t2, s6
    sll t3, a3, s6
    ld a6, 248(s11)
    slli a0, a6, 29
    ld s1, 176(s11)
    ld a4, 120(s11)
    sll s0, s1, a4
    addi s3, t3, -882
    and t4, s3, a3
    add a2, t4, t4
    sd t3, 208(s11)
    sd a2, 216(s11)
    sd a6, 224(s11)
    sd s3, 424(s11)
    sd s1, 432(s11)
    sd t4, 440(s11)
    andi t1, t4, -206
    sra t5, t3, a4
    add s6, t1, t5
    sll t2, t1, s1
    xori t6, t2, 1769
    or a5, t6, t6
    srai t0, a5, 13
    lwu s4, 272(s11)
    slt a3, s4, t0
    add s0, a3, a3
    srli a7, s0, 15
    srai s1, a7, 28
    lwu a0, 260(s11)
    lw s5, 392(s11)
    sra a0, a0, s5
    addi a0, a0, 324
