n=[0 1 2];
x=[2 1 -1];
p=polyfit(n,x,2);
x1 = linspace(-5,5);
y1 = polyval(p,x1);
figure
plot(x1,y1,'-')
