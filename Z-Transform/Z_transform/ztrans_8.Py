"""Fórmula 6"""

A=r"\text{Fórmula 6 :}"
dlatex(A)
print("")

A=r"-a^{n}u[-n-1] \; \leftrightarrow \;"

A+=latex(ztrans(
    -a**n*u(-n-1)
  ).simplify().simplify()
)
dlatex(
    A
)