# rand_gen3 seed=822208946 length=50 baseAddr=3904
    li s11, 3904
    li a3, 22
    li t2, -21632223
    add a6, a3, t2
    li t0, 0
    li s4, 2147483647
    slli s5, t0, 15
    sh s5, 324(s11)
    sh t2, 326(s11)
    sh t0, 328(s11)
    sh a6, 330(s11)
    lhu a4, 324(s11)
    lh s1, 326(s11)
    lhu s8, 328(s11)
    ori s0, a4, -1464
    xori t3, s0, 1637
    slti t4, t3, 1818
    sh s1, 446(s11)
    sh t2, 448(s11)
    sh s8, 450(s11)
    sh s4, 452(s11)
    sd a6, 392(s11)
    sd a3, 400(s11)
    sd s5, 408(s11)
    sltu a2, s5, a4
    slli a3, a2, 9
    sltu t1, a3, a3
    or s7, t1, a4
    srl s3, s7, a4
    srai a4, s3, 27
    lw a5, 324(s11)
    srl a5, a5, s0
    sw a5, 324(s11)
    lwu t6, 172(s11)
    add t5, t6, a5
    xor s1, t5, t5
    sub a7, a5, t5
    slli s2, a4, 2
    and t4, a7, s2
    lhu a0, 344(s11)
    andi a0, a0, 1402
    sh a0, 344(s11)
    li s6, 0
    li s0, 2147483647
    sub a3, s6, s0
    sll t2, t5, s2
    srai s7, t2, 28
    or s8, s7, t5
    add a1, s7, a3
    sltu t6, s0, s6
    srli a4, a1, 1
