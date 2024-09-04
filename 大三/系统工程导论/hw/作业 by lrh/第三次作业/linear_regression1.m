function [] = linear_regression1(data, alpha)
x = data(:,2);
y = data(:,1);
Lxx = sum((x - mean(x)).^2);
Lyy = sum((y - mean(y)).^2);
Lxy = sum((x - mean(x)).*(y - mean(y)));
b = Lxy/Lxx;
a = mean(y) - b*mean(x);
y_hat = a + b*x;    %一元线性回归方程
fprintf('一元线性回归方程为： \n');
fprintf('y = %f + %f * x  \n',a, b);

%F检验
fprintf('在显著性水平alpha=%f情况下： \n',alpha);
Fa = finv(1 - alpha, 1, length(x) - 2);
ESS = b * Lxy;
RSS = Lyy - ESS;
F = (length(x) - 2)*(ESS/RSS);
fprintf('Fα=%f, F=%f\n',Fa,F);

if(F>Fa)
    fprintf("F>Fα,x与y存在线性关系\n"); 
    %精度分析
    S = ((sum((y - y_hat).^2))/(length(x) - 2)).^0.5;
    Z = norminv(1 - alpha/2, 0, 1);
    fprintf('剩余均方差Sσ=%f\n', S);
    fprintf('Z_α/2=%f\n', Z);
    fprintf('置信区间为[y - %f,y + %f]\n',S*Z,S*Z);
    hold on
    plot(x,y,'o');
    xlabel('curedCount');
    ylabel('confirmedCount');
    title('us covid19 data2021')
    plot(x,y_hat,'linewidth',1);
    plot(x,y_hat - S*Z,'linewidth',1);
    plot(x,y_hat + S*Z,'linewidth',1);
    legend('raw data','regression line','lower limit line','upper limit line');
else
    fprintf("F<=Fα,x与y不存在线性关系\n");
end
end