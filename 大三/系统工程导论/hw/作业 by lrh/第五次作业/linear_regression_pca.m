function linear_regression_pca(data, alpha, rerr)
fprintf("alpha=%f,rerr=%f情况下",alpha, rerr); 
[N,n] = size(data);
n = n-1;
X = data(:,1:n);
Y = data(:,n+1:n+1);
[pcs, cprs_data, cprs_c] = pca_compress(data, rerr);
E = cprs_c{1};
Sa = cprs_c{2};
data_bar = cprs_c{3};
Vm = cprs_c{4};
m = size(Vm,1);
fprintf("压缩数据为%d维\n",m); 
Vm = diag(Vm);
d = (Vm)^(-1) * cprs_data' * data_bar(:,n+1:n+1);
c = pcs * d;
%去归一化
beta = zeros(1,n+1);
beta(1,n+1) = E(n+1);
for i = 1:n
    beta(1,i) = c(i,1)/Sa(i) * Sa(n+1);
    beta(1,n+1) = beta(1,n+1) - beta(1,i) * E(i);
end

%检验
Y_pred = beta(1:n) * X' + beta(1,n+1);
TSS = sum((Y - E(n+1)).^2);
ESS = sum((Y_pred - mean(Y_pred)).^2);
RSS = TSS - ESS;
F = (ESS/m)/(RSS/(N-m-1));
Fa = finv(1 - alpha, m, N-m-1);
fprintf('Fα=%f,F=%f\n',Fa,F);
if(F>Fa)
    fprintf("F>Fα,x与y存在线性关系\n"); 
    %精度分析
    Sa = sqrt(RSS/(N-m-1));
    Z = norminv(1 - alpha/2, 0, 1);
    fprintf('回归方程为y = %f',beta(1,n+1));
    for i = 1:n
        fprintf('+%f*x%d',beta(1,i),i);
    end
    fprintf('\n');
    fprintf('置信区间为[y - %f,y + %f]\n',Sa*Z,Sa*Z);
else
    fprintf("F<=Fα,x与y不存在线性关系\n");
end
end
