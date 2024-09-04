function [average_dist] = kmeans(data,k)
[N,n]=size(data);
center = zeros(k,n);
for i = 1:n
    mindata = min(data(:,i));
    maxdata = max(data(:,i));
    center(:,i) = mindata + (maxdata - mindata) .* rand(k,1); 
end
init_center = center;
label = zeros(N,1);
%迭代求聚类中心
while true
    new_center = zeros(k,n);
    min_dist = 1./zeros(N,1);
    for i = 1:N
        for j = 1:k
            dist = norm(data(i,:)-center(j,:)); %向量到中心的欧式距离
            if dist < min_dist(i)
                min_dist(i) = dist;
                label(i) = j;
            end
        end
    end
    dist_center = zeros(k,1);
    for i = 1:k
        cluster_i = data(label==i,:);
        new_center(i,:) = mean(cluster_i,1);
        dist_center = norm(new_center(i,:)-center(i,:));
    end
    if isempty(find(dist_center > 0.001, 1))
        average_dist = sum(min_dist)/N;
        break
    else
        center = new_center;
    end
end

%显示聚类后的数据
figure;
hold on
for i = 1: k
    color = [rand(),rand(),rand()];
    center_color = [rand(),rand(),rand()];
    cluster_i = data(label==i,:);
    plot(cluster_i(:,1),cluster_i(:,2),'*','Color',color,'MarkerFaceColor',color);
    plot(init_center(i,1),init_center(i,2),'^','Color',center_color,'MarkerFaceColor',center_color);
    plot(center(i,1),center(i,2),'h','Color',center_color,'MarkerFaceColor',center_color);
    hold on
end
hold on
grid on
daspect([1 1 1]);
xlabel('x');ylabel('y');
title('kmeans聚类结果');
