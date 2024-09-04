function [new_label, new_visited] = expand_cluster(data, nearby_points, label, visited, k, eps, minpots)
new_label = label;
new_visited = visited;
for i = 1:length(nearby_points)
    if new_visited(nearby_points(i)) == 0
        new_visited(nearby_points(i)) = 1;  
        dist = sqrt(((data(:,1)-data(nearby_points(i),1)) .* (data(:,1)-data(nearby_points(i),1)) + (data(:,2)-data(nearby_points(i),2)) .* (data(:,2)-data(nearby_points(i),2))));
        new_nearby_points = find(dist<=eps);
        if length(new_nearby_points) >= minpots
            new_label(nearby_points(i)) = k;
            [new_label, new_visited] = expand_cluster(data, new_nearby_points, new_label, new_visited, k, eps, minpots);
        end
    end
    if new_label(nearby_points(i)) == 0
       new_label(nearby_points(i)) = k;
    end
end
