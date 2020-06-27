nn = 0 : (8-1) ;
%xx= exp(1i*nn/3) ;
xx= [1 0 0 0 0 0 0 0];
XX =fft(xx) ;
kk = nn ;
subplot(421)
stem (kk , real(xx ))
title( 'REAL PART of x[n] ' ) , xlabel( 'n'), ylabel('Re{x[n]}')
subplot(422)
stem(kk , imag(xx))
title( ' IMAG PART of x[n] ' ) , xlabel( 'n' ), ylabel('Im{x[n]}')
subplot(423)
stem(kk , real(XX))
title( ' REAL PART of DFT ' ) , xlabel( 'k' ), ylabel('Re{X[k]}')
subplot ( 424)
stem(kk , imag(XX))
title( ' IMAG PART of DFT ' ) , xlabel( 'k' ), ylabel('Im{X[k]}')

M_x=abs(xx);
Ph_x=angle(xx);
subplot ( 425)
stem(nn , M_x)
title( ' Magnitude of x[n] ' ) , xlabel( 'n' ), ylabel('abs{x[n]}')

subplot ( 426)
stem(nn , Ph_x)
title( ' Phase of x[n] ' ) , xlabel( 'n' ), ylabel('Phase{x[n]}')

M_X=abs(XX);
Ph_X=angle(XX);


subplot ( 427)
stem(kk , M_X)
title( ' Magnitude of X[k] ' ) , xlabel( 'k' ), ylabel('abs{X[k]}')

subplot ( 428)
stem(kk , Ph_X)
title( ' Phase of X[k] ' ) , xlabel( 'k' ), ylabel('Phase{X[k]}')