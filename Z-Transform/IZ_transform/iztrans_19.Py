title="""Simétrico da Fórmula 8"""

N=6

X=Piecewise((a*z/(a**2 - 2*a*z + z**2), True), (-Sum(a**n*n*z**(-n), (n, -oo, -1)), True))
X=X.subs(a,2)
# a deve ser substituído por um INTEIRO !

#######
m=0.001
#######


results=[ iztrans(X,i,m) for i in nparange(-N,N+1)]

fig = figure()
ax1 = fig.add_subplot(111)
ax1.set_ylabel('Valor',fontsize=15)
ax1.set_xlabel('N',fontsize=15)
ax1.set_title(title,fontsize=18)
stem(nparange(-N,N+1),results, use_line_collection=True,linefmt=None, 
     markerfmt=None, basefmt=None)
show()