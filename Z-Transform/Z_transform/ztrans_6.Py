"""Fórmula 4"""

A=r"\text{Fórmula 4 :}"
dlatex(A)
print("")

A=r"\delta[n-5] \; \leftrightarrow \;"

A+=latex(ztrans(
    DiracDelta(n-5)
  )
)
dlatex(
    A
)