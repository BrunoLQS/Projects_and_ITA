"""Fórmula 7"""

A=r"\text{Fórmula 7 :}"
dlatex(A)
print("")

A=r"na^{n}u[n] \; \leftrightarrow \;"

A+=latex(ztrans(
    n*a**n*u(n)
  ).simplify()
)
dlatex(
    A
)