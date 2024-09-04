clc

data=load('data.mat');
data1=data.data1;
data2=data.data2;
data3=data.data3;

k=3; %聚类数目
[average_dist1]=kmeans(data1,k);
[average_dist2]=kmeans(data2,k); 
[average_dist3]=kmeans(data3,k);

% average_dist=zeros(1,6);
% for i=2:7
%      [average_dist(i-1)]= kmeans(data2, i);
% end
% figure;
% x=2:7;
% hold on
% plot(x,average_dist);
% plot(x,average_dist,'r+')
% xlabel('类别个数k');
% ylabel('Average distance');
