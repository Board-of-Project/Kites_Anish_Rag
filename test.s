# rand_gen3 seed=561392739 length=5 baseAddr=2496
    li s11, 2496
    li s6, -3463020
    li s5, 0
    sltiu a6, s6, 72
    li t4, 0
    li t2, 138
    srli t6, t4, 24
    li s2, 1
    li t0, 2147483647
    slt a7, s2, t0
    sh s2, 168(s11)
    sh t6, 170(s11)
    sh s6, 172(s11)
    lb s7, 466(s11)
    lw t1, 92(s11)
    add a0, s7, t1
