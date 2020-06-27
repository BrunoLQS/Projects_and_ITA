from IPython.display import (Image,
                             display,
                             Latex)
from sympy import (symbols, 
                   latex,              
                   DiracDelta,
                   Heaviside,
                   solve_poly_inequality,
                   Poly,
                   oo,Sum,symbols,Add,
                   Piecewise,cos,sin,exp,log)

n=symbols('n',integer=True)
a , N, z =symbols('a, N, z')
r, ω_0 =symbols('r, ω_0', real=True)

def dlatex(arg):
  display(Latex(arg))
  return None

def u(n):
  return(Heaviside(n,1))