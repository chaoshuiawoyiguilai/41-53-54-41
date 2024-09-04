clc

data=load('data.mat');
data1=data.data1;
data2=data.data2;
data3=data.data3;
k1 = DBSCAN(data1,0.2,10);
k2 = DBSCAN(data2,0.4,10);
k3 = DBSCAN(data3,0.2,10);
