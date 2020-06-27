nn = 0 : (16-1) ;
w_0=6*pi/16;
%s=-1j*(exp(-1i*w_0*nn)-exp(1i*w_0*nn)/2) ;
s=sin(1.0*w_0*nn);
S =fft(s) ;
kk = nn ;

subplot(221)
stem(nn,real(s))
title( 'REAL PART of s[n] ' ) , xlabel( 'n'), ylabel('Re{s[n]}')

subplot(222)
stem(nn,imag(s))
title( 'IMAG PART of s[n] ' ) , xlabel( 'n'), ylabel('Im{s[n]}')

subplot(223)
stem(kk,real(S))
title( 'REAL PART of DFT ' ) , xlabel( 'k'), ylabel('Re{S[k]}')

subplot(224)
stem(kk,imag(S))
title( 'IMAG PART of DFT ' ) , xlabel( 'k'), ylabel('Im{S[k]}')