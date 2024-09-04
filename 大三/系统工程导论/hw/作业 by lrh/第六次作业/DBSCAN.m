function k = DBSCAN(data,eps,minpots)
[N,~]=size(data);
label = zeros(N,1);
visited = zeros(N,1);
k = 0;
%分类
for i = 1:N
    if visited(i) == 0 %抽取一个未访问点
        visited(i) = 1;
        dist = sqrt(((data(:,1)-data(i,1)) .* (data(:,1)-data(i,1)) + (data(:,2)-data(i,2)) .* (data(:,2)-data(i,2))));
        nearby_points = find(dist<=eps);
        if length(nearby_points) >= minpots
            k = k + 1;
            label(i) = k;
            [label, visited] = expand_cluster(data, nearby_points, label, visited, k, eps, minpots);
        end
    end
end


%显示聚类后的数据
figure;
cluster = data(label==0,:);
plot(cluster(:,1),cluster(:,2),'k.','MarkerFaceColor','k','MarkerSize',10);
hold on
for i = 1: k
    color = [rand(),rand(),rand()];
    cluster_i = data(label==i,:);
    plot(cluster_i(:,1),cluster_i(:,2),'.','Color',color,'MarkerFaceColor',color,'MarkerSize',10);
    hold on
end
hold on
grid on
daspect([1 1 1]);
xlabel('x');ylabel('y');
title('DBSCAN聚类结果');
