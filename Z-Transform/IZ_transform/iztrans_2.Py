def zztrans(x_n, args):
  z=symbols('z')
  x_t, u_t = x_n.as_independent(args)
  arg_1=u_t.args[0] # Linear equation (polinomial)
  n_t=u_t.free_symbols # N is the only one variable. 
  # All the rest of coefficients are constant.
  solve_p=solve_poly_inequality
  if(args == Heaviside ):
    interval=solve_p(Poly(arg_1, n_t, domain='ZZ'), '>')
    MIN=interval[0].left
    MAX=interval[0].right
  if(args == DiracDelta ):
    interval=solve_p(Poly(arg_1, n_t, domain='ZZ'), '==')
    MIN=interval[0].args[0]
    MAX=interval[0].args[0]
  return(Sum(x_t*(z**-n),(n_t,MIN,MAX)).doit())

def ztransf(x_n):
  if(x_n.has(Heaviside)):
    return(
        zztrans(x_n,Heaviside)
    )

  if(x_n.has(DiracDelta)):
    return(
        zztrans(x_n,DiracDelta)
    )
def ztrans(x_n):
  """
    Input is x[n]
  """
  ztransformation=0
  for x_term in Add.make_args(x_n):
    ztransformation+=ztransf(x_term)
  return (ztransformation.doit())#.simplify().simplify())
  #return (ztransformation.doit().simplify().simplify())

def u(n):
  return(Heaviside(n,1))