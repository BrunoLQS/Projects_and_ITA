
A=2.0;
f_0=1/21;
nn=0:20;
fi=pi/2;

s1=A*cos(2*pi*f_0*nn + fi);

S1=fft(s1);


s2=A*sin(2*pi*f_0*nn + 0);

S2=fft(s2);

s3=A*sin(2*pi*f_0*nn + pi/4);

S3=fft(s3);

kk=nn;

subplot(321)
stem(kk,abs(S1))
title( 'Magnitude of S1[k] ' ) , xlabel( 'k'), ylabel('abs{S1[k]}')

subplot(322)
stem(kk,angle(S1))
title( 'Phase of S1[k] ' ) , xlabel( 'k'), ylabel('phase{S1[k]}')

subplot(323)
stem(kk,abs(S2))
title( 'Magnitude of S2[k] ' ) , xlabel( 'k'), ylabel('abs{S2[k]}')

subplot(324)
stem(kk,angle(S2))
title( 'Phase of S2[k] ' ) , xlabel( 'k'), ylabel('phase{S2[k]}')

subplot(325)
stem(kk,abs(S3))
title( 'Magnitude of S3[k] ' ) , xlabel( 'k'), ylabel('abs{S3[k]}')

subplot(326)
stem(kk,angle(S3))
title( 'Phase of S3[k] ' ) , xlabel( 'k'), ylabel('phase{S3[k]}')


