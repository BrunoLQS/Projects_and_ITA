nn = 0 : (8-1) ;
%xx= exp(1i*nn/3) ;
xx= [1 1 0 0 0 0 0 1];
XX =fft(xx) ;
kk = nn ;
M_X=abs(XX);
Ph_X=angle(XX);


subplot ( 121 )
stem(kk , M_X)
title( ' Magnitude of Xbsy[k] ' ) , xlabel( 'k' ), ylabel('abs{Xbsy[k]}')

subplot ( 122 )
stem(kk , Ph_X)
title( ' Phase of Xbsy[k] ' ) , xlabel( 'k' ), ylabel('Phase{Xbsy[k]}')