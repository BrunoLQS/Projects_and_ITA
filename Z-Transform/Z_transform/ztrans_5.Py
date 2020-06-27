"""Fórmula 3"""

A=r"\text{Fórmula 3 :}"
dlatex(A)
print("")

A=r"-u[-n-1] \; \leftrightarrow \;"

A+=latex(ztrans(
    -u(-n-1)
  ).simplify()
)
dlatex(
    A
)