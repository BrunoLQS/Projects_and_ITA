"""Fórmula 8"""

A=r"\text{Fórmula 8 :}"
dlatex(A)
print("")

A=r"-na^{n}u[-n-1] \; \leftrightarrow \;"

A+=latex(ztrans(
    -n*a**n*u(-n-1)
  ).simplify()
)
dlatex(
    A
)