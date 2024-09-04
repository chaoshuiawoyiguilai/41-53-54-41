filename = 'data.txt';
delimiterIn = ',';
A = importdata(filename,delimiterIn);
[M,N]=size(A);
X = A(1:M,1:N-1);
Y = A(1:M,N:N);
alpha=0.05;
linear_regression(Y,X,alpha);