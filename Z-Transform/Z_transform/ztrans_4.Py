"""Fórmula 2"""

A=r"\text{Fórmula 2 :}"
dlatex(A)
print("")

A=r"u[n] \; \leftrightarrow \;"

A+=latex(ztrans(
    u(n)
  ).simplify()
)
dlatex(
    A
)