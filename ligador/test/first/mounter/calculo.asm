CALC: LOAD RA A
      LOAD RB B
      MOVE RD RB
      SUB RA RD
      SB RB RC
      COMP RA RB
      BLZ L
      STORE C RA
      WRITE C
      RET
L:    STORE C RB
      WRITE C
      RET
C:    WORD 0
      END
