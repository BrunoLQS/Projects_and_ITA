"""Fórmula 10"""

A=r"\text{Fórmula 10 :}"
dlatex(A)
print("")

A=r"\sin(\omega_0 n)u[n] \; \leftrightarrow \;"

r_1=ztrans(
    (a**n-a**(-n))*u(n)*(1/2j)
  ).subs(a,exp(1j*ω_0))
A+=latex((r_1).simplify())
dlatex(A)