title="""Simétrico da Fórmula 5"""

N=6

X=Piecewise((z/(-a+z), True), (Sum(a**n*z**(-n), (n, 0, oo)), True))
X=X.subs(a,2)
# a deve ser substituído por um INTEIRO !

m=1.0


results=[ iztrans(X,i,m) for i in nparange(-N,N+1)]

fig = figure()
ax1 = fig.add_subplot(111)
ax1.set_ylabel('Valor',fontsize=15)
ax1.set_xlabel('N',fontsize=15)
ax1.set_title(title,fontsize=18)
stem(nparange(-N,N+1),results, use_line_collection=True,linefmt=None, markerfmt=None, basefmt=None)
show()