nn = 0 : (8-1) ;
%xx= exp(1i*nn/3) ;
xx= [1 1 1 1 0 0 0 0];
XX =fft(xx) ;
kk = nn ;
M_X=abs(XX);
Ph_X=angle(XX);


subplot ( 121 )
stem(kk , M_X)
title( ' Magnitude of Xb4[k] ' ) , xlabel( 'k' ), ylabel('abs{Xb4[k]}')

subplot ( 122 )
stem(kk , Ph_X)
title( ' Phase of Xb4[k] ' ) , xlabel( 'k' ), ylabel('Phase{xb4[k]}')