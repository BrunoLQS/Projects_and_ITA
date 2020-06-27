def iztrans(F,n,m=1.0):
  # m = |(z/a)|
  from sympy import symbols
  z,t=symbols('z,t')
  from numpy import pi as npi
  from sympy import pi as spi
  from sympy import (limit,
                     integrate)
  from sympy import (log,cos,sin)
  from numpy import log as nplog
  from numpy import cos as npcos
  from numpy import sin as npsin
  from numpy import exp as npexp
  from sympy import Heaviside 

  func=F

 # GAMBIARRA
  """Corrigindo Bugs de integrate"""
  if(abs(m)<1):
    #n=n+1
    n=-1*n
    func=-F*z**(n-1)
  else:
    func=F*z**(n-1)

  m=1
  """Corrigindo Bugs de integrate"""
  # GAMBIARRA

  #func=func.subs(z,m*cos(t)+m*1j*sin(t))
  #func=func*(-sin(t)+1j*cos(t))*m
  integral_result=integrate(func,z)
  
  
  int_param=integral_result.subs(z,abs(m)*(cos(t)+1j*sin(t)) )
  result=(int_param.subs(t,npi)-int_param.subs(t,-npi)).simplify()
  result=(spi/npi)*result.simplify()
  result=result/(2*spi*1j).simplify()

  """Corrigindo Bugs de integrate"""
  if(abs(m)<1):
    result=result*Heaviside(-n-1,1)
  """Corrigindo Bugs de integrate"""
  
  return(result.simplify())