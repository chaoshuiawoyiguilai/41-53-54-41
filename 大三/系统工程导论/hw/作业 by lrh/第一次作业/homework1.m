load('data.mat', 'data');

% 可视化
x = 0:30:2613*30;   %定义x坐标
y = data.';    %列向量转置
figure(1), plot(x,y);   %输出图像
grid on;
title('某高速路车流量变化');     %定义标题、x轴、y轴
xlabel('时间(s)');
ylabel('流量(辆/h)');

% 移动平均法
% N = 5
y1 = cell(1);
len = length(y);
for i = 6:len
    y1{1}(i) = sum(y(i-5:i-1))/5;     %利用前5个数据求平均预测下一数据
end
x1 = 0:30:2613*30;
y1 = cell2mat(y1);
figure(2), plot(x1,y1);
grid on;
title('移动平均法，N=5');
xlabel('时间(s)');
ylabel('流量(辆/h)');

% N = 25
y2 = cell(1);
len = length(y);
for i = 26:len
    y2{1}(i) = sum(y(i-25:i-1))/25;       %利用前25个数据求平均预测下一数据
end
x1 = 0*30:30:2613*30;
y2 = cell2mat(y2);
figure(3), plot(x1,y2);
grid on;
title('移动平均法，N=25');
xlabel('时间(s)');
ylabel('流量(辆/h)');

% 指数平滑法
% alpha = 0.2
y3 = cell(1);
y3{1}(1) = y(1);
for i = 2:len
    y3{1}(i) = 0.2*y(i-1)+(1-0.2)*y3{1}(i-1);       %一次指数平滑预测S_t=a*y_(t-1)+(1-a)*S_(t-1),a=0.2
end
x3 = 0:30:2613*30;
y3 = cell2mat(y3);
figure(4), plot(x3, y3);
grid on;
title('指数平滑法，alpha=0.2');
xlabel('时间(s)');
ylabel('流量(辆/h)');

% alpha = 0.04
y4 = cell(1);
y4{1}(1) = y(1);
for i = 2:len
    y4{1}(i) = 0.04*y(i-1)+(1-0.04)*y4{1}(i-1);     %一次指数平滑预测S_t=a*y_(t-1)+(1-a)*S_(t-1),a=0.04
end
x3 = 0:30:2613*30;
y4 = cell2mat(y4);
figure(5), plot(x3, y4);
grid on;
title('指数平滑法，alpha=0.04');
xlabel('时间(s)');
ylabel('流量(辆/h)');