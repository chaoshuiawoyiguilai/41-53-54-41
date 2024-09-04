function linear_regression_ill_cond(data, alpha, rerr)
fprintf("alpha=%f,rerr=%f情况下",alpha, rerr); 
[N,n] = size(data);
X = data(:,1:n-1);
Y = data(:,n:n);
n = n - 1;
%归一化处理
EX = mean(X, 1);
SX = std(X, 0, 1);
EY = mean(Y);
SY = std(Y);
X_bar = (X - EX)./SX;
Y_bar = (Y - EY)./SY;
%找出使逼近误差可接受的最小m
A = X_bar'*X_bar;
B = X_bar'*Y_bar;
[Q0,V0] = eig(A);
[V,index] = sort(diag(V0),'descend');
Q = Q0(:,index);
Lambda_sum = sum((V'));
Lambda_tempt = 0;
for m = 1:n
    Lambda_tempt = Lambda_tempt + V(m);
    if Lambda_tempt/Lambda_sum >= 1 - rerr
        break;
    end
end
%判断是否为病态问题
if m < n
    fprintf('存在病态问题, m=%d\n',m);
else
    fprintf('不存在病态问题');
end

%缩减后的特征值对角阵的逆和特征向量矩阵
V = V(1:m);
Vm = diag(V);
Qm = Q(:,1:m);
d = (Vm)^(-1) * Qm' * B;
c = Qm * d;
%去归一化
beta = zeros(1,n+1);
beta(1,n+1) = EY;
for i = 1:n
    beta(1,i) = c(i,1)/SX(i) * SY;
    beta(1,n+1) = beta(1,n+1) - beta(1,i) * EX(i);
end

%检验
Y_pred = beta(1:n) * X' + beta(1,n+1);
TSS = sum((Y - EY).^2);
ESS = sum((Y_pred - mean(Y_pred)).^2);
RSS = TSS - ESS;
F = (ESS/m)/(RSS/(N-m-1));
Fa = finv(1 - alpha, m, N-m-1);
fprintf('Fα=%f,F=%f\n',Fa,F);
if(F>Fa)
    fprintf("F>Fα,x与y存在线性关系\n"); 
    %精度分析
    S = sqrt(RSS/(N-m-1));
    Z = norminv(1 - alpha/2, 0, 1);
    fprintf('回归方程为y = %f',beta(1,n+1));
    for i = 1:n
        fprintf('+%f*x%d',beta(1,i),i);
    end
    fprintf('\n');
    fprintf('置信区间为 [y - %f,y + %f]\n',S*Z,S*Z);
else
    fprintf("F<=Fα,x与y不存在线性关系\n");
end
end
