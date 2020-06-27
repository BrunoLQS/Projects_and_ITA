nn = 0 : (8-1) ;
%xx= exp(1i*nn/3) ;
xxv= [0 0 0 0 1 0 0 0];
XXV =fft(xxv) ;
kk = nn ;
subplot(421)
stem (kk , real(xxv ))
title( 'REAL PART of xv[n] ' ) , xlabel( 'n'), ylabel('Re{xv[n]}')
subplot(422)
stem(kk , imag(xxv))
title( ' IMAG PART of xv[n] ' ) , xlabel( 'n' ), ylabel('Im{xv[n]}')
subplot(423)
stem(kk , real(XXV))
title( ' REAL PART of DFT ' ) , xlabel( 'k' ), ylabel('Re{XV[k]}')
subplot ( 424)
stem(kk , imag(XXV))
title( ' IMAG PART of DFT ' ) , xlabel( 'k' ), ylabel('Im{XV[k]}')

M_x=abs(xxv);
Ph_x=angle(xxv);
subplot ( 425)
stem(nn , M_x)
title( ' Magnitude of xv[n] ' ) , xlabel( 'n' ), ylabel('abs{xv[n]}')

subplot ( 426)
stem(nn , Ph_x)
title( ' Phase of xv[n] ' ) , xlabel( 'n' ), ylabel('Phase{xv[n]}')

M_X=abs(XXV);
Ph_X=angle(XXV);


subplot ( 427)
stem(kk , M_X)
title( ' Magnitude of XV[k] ' ) , xlabel( 'k' ), ylabel('abs{XV[k]}')

subplot ( 428)
stem(kk , Ph_X)
title( ' Phase of XV[k] ' ) , xlabel( 'k' ), ylabel('Phase{XV[k]}')