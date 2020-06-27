"""Fórmula 1"""


A=r"\text{Fórmula 1 :}"
dlatex(A)
print("")

A=r"\delta[n] \; \leftrightarrow \;"

A+=latex(ztrans(DiracDelta(n)))
dlatex(
    A
)