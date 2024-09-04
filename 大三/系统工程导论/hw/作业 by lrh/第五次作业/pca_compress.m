function [pcs, cprs_data, cprs_c] = pca_compress(data, rerr)
n = size(data,2) - 1;
%归一化处理
E = mean(data, 1);
S = std(data, 0, 1);
data_bar = (data - E)./S;
%数据压缩
X_bar = data_bar(:,1:n);
A = X_bar'*X_bar;
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
pcs = Q(:,1:m);
Vm = V(1:m);
cprs_data =  (pcs' * X_bar')';
cprs_c = {E; S; data_bar; Vm};
