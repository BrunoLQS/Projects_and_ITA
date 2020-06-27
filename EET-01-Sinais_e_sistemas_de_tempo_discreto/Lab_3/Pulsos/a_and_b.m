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
subplot(425)
stem(kk , real(XX))
title( ' REAL PART of DFT X[k]' ) , xlabel( 'k' ), ylabel('Re{X[k]}')
subplot ( 426)
stem(kk , imag(XX))
title( ' IMAG PART of DFT X[k]' ) , xlabel( 'k' ), ylabel('Im{X[k]}')


subplot(423)
stem (kk , real(x1 ))
title( 'REAL PART of x1[n] ' ) , xlabel( 'n'), ylabel('Re{x1[n]}')
subplot(424)
stem(kk , imag(x1))
title( ' IMAG PART of x1[n] ' ) , xlabel( 'n' ), ylabel('Im{x1[n]}')

subplot(427)
stem(kk , real(XX1))
title( ' REAL PART of DFT X1[k]' ) , xlabel( 'k' ), ylabel('Re{X1[k]}')
subplot ( 428)
stem(kk , imag(XX1))
title( ' IMAG PART of DFT X1[k]' ) , xlabel( 'k' ), ylabel('Im{X1[k]}')
