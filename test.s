# rand_gen3 seed=587455322 length=50 baseAddr=3904
    li s11, 3904
    li s8, -1
    li s2, 165
    slli a4, s8, 10
    li t5, 1284
    li t1, 1
    or a0, t5, t1
    lw s1, 432(s11)
    xori s7, s1, -723
    add s3, s7, s7
    addi a1, s3, 1077
    add s4, s3, a0
    andi t2, s4, 617
    slt s6, t2, s3
    addi t6, s6, -1671
    and s0, t6, t6
    srai s3, s0, 12
    lw a5, 144(s11)
    slli s5, a5, 1
    sra t0, s5, s5
    slt s8, t0, s0
    sw s5, 196(s11)
    sw s8, 200(s11)
    li t1, 0
    li a4, 0
    xori t3, t1, -1335
    lh a3, 22(s11)
    lhu a2, 334(s11)
    sltu a0, a3, a2
    or a0, a0, s3
    lw t6, 284(s11)
    lw s1, 452(s11)
    xor s0, t6, s1
    sh a0, 416(s11)
    sh s8, 418(s11)
    sh s0, 124(s11)
    sh a4, 126(s11)
    sh a0, 128(s11)
    sh s8, 130(s11)
    sh t3, 78(s11)
    sh t6, 80(s11)
    sh t1, 82(s11)
    lh s4, 276(s11)
    lb a6, 112(s11)
    xor s4, s4, a6
    lh t2, 362(s11)
    lw s3, 184(s11)
    add s8, t2, s3
    sw a0, 472(s11)
    sw s0, 476(s11)
    sw a3, 480(s11)
    sw s4, 484(s11)
