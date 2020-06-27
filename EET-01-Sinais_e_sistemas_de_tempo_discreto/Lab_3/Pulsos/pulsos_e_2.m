nn = 0 : (8-1) ;

xb= [1 1 1 0 0 0 0 0];
Xb =fft(xb) ;
kk = nn ;

xbsy= [1 1 0 0 0 0 0 1];
Xbsy =fft(xbsy) ;
kk = nn ;

subplot(221)

stem (kk , abs(Xb),'b-')
title( ' Magnitude of DFT ' ) , xlabel( 'k' ), ylabel('abs{Xb[k]}')

subplot (222)
stem (kk , abs(Xbsy),'r-')
title( ' Magnitude of DFT ' ) , xlabel( 'k' ), ylabel('abs{Xbsy[k]}')


subplot(223)

stem (kk , angle(Xb),'b-')
title( ' Phase of DFT ' ) , xlabel( 'k' ), ylabel('phase{Xb[k]}')

subplot (224)
stem (kk , angle(Xbsy),'r-')
title( ' Phase of DFT ' ) , xlabel( 'k' ), ylabel('phase{Xbsy[k]}')
