nn = 0 : (8-1) ;
%xx= exp(1i*nn/3) ;
x1= [1 1 1 1 1 1 1 1];
XX1 =fft(x1) ;
kk = nn ;
subplot(421)
stem (kk , real(x1 ))
title( 'REAL PART of x1[n] ' ) , xlabel( 'n'), ylabel('Re{x1[n]}')
subplot(422)
stem(kk , imag(x1))
title( ' IMAG PART of x1[n] ' ) , xlabel( 'n' ), ylabel('Im{x1[n]}')
subplot(423)
stem(kk , real(XX1))
title( ' REAL PART of DFT ' ) , xlabel( 'k' ), ylabel('Re{X1[k]}')
subplot ( 424)
stem(kk , imag(XX1))
title( ' IMAG PART of DFT ' ) , xlabel( 'k' ), ylabel('Im{X1[k]}')

M_x=abs(x1);
Ph_x=angle(x1);
subplot ( 425)
stem(nn , M_x)
title( ' Magnitude of x1[n] ' ) , xlabel( 'n' ), ylabel('abs{x1[n]}')

subplot ( 426)
stem(nn , Ph_x)
title( ' Phase of x1[n] ' ) , xlabel( 'n' ), ylabel('Phase{x1[n]}')

M_X=abs(XX1);
Ph_X=angle(XX1);


subplot ( 427)
stem(kk , M_X)
title( ' Magnitude of X1[k] ' ) , xlabel( 'k' ), ylabel('abs{X1[k]}')

subplot ( 428)
stem(kk , Ph_X)
title( ' Phase of X1[k] ' ) , xlabel( 'k' ), ylabel('Phase{x1[k]}')