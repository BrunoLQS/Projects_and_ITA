"""Fórmula 5"""

A=r"\text{Fórmula 5 :}"
dlatex(A)
print("")

A=r"a^{n}u[n] \; \leftrightarrow \;"

A+=latex(ztrans(
    a**n*u(n)
  ).simplify()
)
dlatex(
    A
)