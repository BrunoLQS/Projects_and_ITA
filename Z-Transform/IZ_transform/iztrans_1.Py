from IPython.display import (Image,
                             display,
                             Latex)
from sympy import (symbols, 
                   latex,              
                   DiracDelta,
                   Heaviside,
                   solve_poly_inequality,
                   Poly,
                   oo,Sum,Add,
                   Piecewise)

from sympy import (pi,
                   integrate,
                   cos,sin,Abs)

def dlatex(arg):
  display(Latex(arg))
  return None