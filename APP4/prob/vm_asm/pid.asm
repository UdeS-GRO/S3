# PID avec P = -0.5, I = 0, D = 0, donc sans I ou D
LDC R1,     -0.5
STO $K_P,   R1
LDC R1,     1.0
STO $Q_DES, R1
LDA R1,     $Q
LDA R2,     $Q_DES
SUB R1,     R2
LDA R2,     $K_P
MUL R1,     R2
STO $CMD,   R1
