title="""Simétrico da Fórmula 2"""
N=20
X_z=Piecewise((z/(z - 1), True), (Sum(z**(-n), (n, 0, oo)), True))
results=[ iztrans(X_z,i) for i in nparange(-N,N+1)]

fig = figure()
ax1 = fig.add_subplot(111)
ax1.set_ylabel('Valor',fontsize=15)
ax1.set_xlabel('N',fontsize=15)
ax1.set_title(title,fontsize=18)
stem(nparange(-N,N+1),results, use_line_collection=True,linefmt=None, 
     markerfmt=None, basefmt=None)
show()