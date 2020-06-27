"""Fórmula 11"""

A=r"\text{Fórmula 11 :}"
dlatex(A)
print("")

A=r"r^{n}\cos(\omega_0 n)u[n] \; \leftrightarrow \;"

r_1=ztrans(
    r**n*(a**n+a**(-n))*u(n)*(1/2)
  ).subs(a,exp(1j*ω_0))
A+=latex((r_1).simplify())
dlatex(A)