N=16;
nn = 0 : (16-1) ;
w_0=6*pi/16;
y= exp(-1i*w_0*nn) ;
Y =fft(y) ;
kk = nn ;
SS=zeros(1,N);
% determination of fi_3,16 [k]
for k = 2:N
    SS((k-1)+ 1)=Y((N-(k-1))+1);
end
k=1;
SS(-(k-1)+1)=Y((k-1)+1); % SS[0] = SS(0 + 1)


SS=[ SS SS ];

S=zeros(1,N);
for k = 1:N
    S((k-1)+ 1)= -(1i/2)*( SS((k-1)+ 1) - SS((N-(k-1)) + 1));
end
subplot(221)
stem(kk,real(S))
title( 'REAL PART of S[k] ' ) , xlabel( 'k'), ylabel('Re{S[k]}')

subplot(222)
stem(kk,imag(S))
title( 'IMAG PART of S[k] ' ) , xlabel( 'k'), ylabel('Im{S[k]}')

subplot(223)
stem(kk,abs(S))
title( 'Magnitude of DFT ' ) , xlabel( 'k'), ylabel('Abs{S[k]}')

subplot(224)
stem(kk,angle(S))
title( 'Phase of DFT ' ) , xlabel( 'k'), ylabel('Phase{S[k]}')