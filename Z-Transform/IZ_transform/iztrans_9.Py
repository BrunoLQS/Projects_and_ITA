title="""Simétrico da Fórmula 3"""

N=20

X=Piecewise((z/(z - 1), True), (-Sum(z**(-n), (n, -oo, -1)), True))
m=0.01


results=[ iztrans(X,i,m) for i in nparange(-N,N+1)]

fig = figure()
ax1 = fig.add_subplot(111)
ax1.set_ylabel('Valor',fontsize=15)
ax1.set_xlabel('N',fontsize=15)
ax1.set_title(title,fontsize=18)
stem(nparange(-N,N+1),results, use_line_collection=True,linefmt=None, markerfmt=None, basefmt=None)
show()