nn = 0 : (8-1) ;
%xx= exp(1i*nn/3) ;
xx= [0 0 0 1 0 0 0 0];
XX =fft(xx) ;
kk = nn ;
M_X=abs(XX);
Ph_X=angle(XX);


subplot ( 121 )
stem(kk , M_X)
title( ' Magnitude of Xish[k] ' ) , xlabel( 'k' ), ylabel('abs{Xish[k]}')

subplot ( 122 )
stem(kk , Ph_X)
title( ' Phase of Xish[k] ' ) , xlabel( 'k' ), ylabel('Phase{xish[k]}')