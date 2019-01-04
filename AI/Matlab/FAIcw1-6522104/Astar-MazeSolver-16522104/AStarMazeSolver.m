function AStarMazeSolver(maze)

OBSTACLE = [];
k = 1;
xNode = 0;
yNode = 0;
xTarget = 0;
yTarget = 0;
size_m = size(maze,1);
for i = 1 : size_m
    for j = 1 : size_m
        if(maze(i, j) == 0 || maze(i, j) == 8 )
            OBSTACLE(k, 1) = i;
            OBSTACLE(k, 2) = j;
            k = k + 1;  
        end
         if(maze(i,j) == 3)
                xNode = i;
                yNode = j;
         end
         if(maze(i,j) == 4)
                xTarget = i + 1;
                yTarget = j;
         end
    end
end
OBST_COUNT = size(OBSTACLE, 1);
OBST_COUNT = OBST_COUNT + 1;

xStart = xNode;
yStart = yNode;
path_cost = 0;
NoPath = 1;
goal_distance = distance(xNode, yNode, xTarget, yTarget);
PATH = [];
PATH_COUNT = 1;
PATH(PATH_COUNT, :) = insert(xNode, yNode, xNode, yNode, path_cost, goal_distance, goal_distance);
PATH(PATH_COUNT, 1) = 0;

while((xNode ~= xTarget || yNode ~= yTarget) && NoPath == 1)
    exp = expand(xNode, yNode, path_cost, xTarget, yTarget, OBSTACLE, size_m, size_m);
    exp_count  = size(exp, 1);
    % Update PATH with child nodes; exp: [X val, Y val, g(n), h(n), f(n)]
    for i = 1 : exp_count
        flag = 0;
        for j = 1 : PATH_COUNT
            if(exp(i, 1) == PATH(j, 2) && exp(i, 2) == PATH(j, 3))
                PATH(j, 8) = min(PATH(j, 8), exp(i, 5));
                if PATH(j, 8) == exp(i, 5)
                    % update parents, g(n) and h(n)
                    PATH(j, 4) = xNode;
                    PATH(j, 5) = yNode;
                    PATH(j, 6) = exp(i, 3);
                    PATH(j, 7) = exp(i, 4);
                    maze(xNode, yNode) = 5;
                end; % end of minimum f(n) check
                flag = 1;
            end;
        end;
        if flag == 0
            PATH_COUNT = PATH_COUNT + 1;
            PATH(PATH_COUNT, :) = insert(exp(i, 1), exp(i, 2), xNode, yNode, exp(i, 3), exp(i, 4), exp(i, 5));
            maze(PATH(PATH_COUNT,2), PATH(PATH_COUNT,3)) = 5;
        end; % end of insert new element into PATH
    end;
    dispMaze(maze);
    % A*: find the node in PATH with the smallest f(n), returned by min_fn
    index_min_node = min_fn(PATH, PATH_COUNT);
    if (index_min_node ~= -1)
        % set current node (xNode, yNode) to the node with minimum f(n)
        xNode = PATH(index_min_node, 2);
        yNode = PATH(index_min_node, 3);
        path_cost = PATH(index_min_node, 6); % cost g(n)
        % move the node to OBSTACLE
        OBST_COUNT = OBST_COUNT + 1;
        OBSTACLE(OBST_COUNT, 1) = xNode;
        OBSTACLE(OBST_COUNT, 2) = yNode;
        PATH(index_min_node, 1) = 0;
    else
        NoPath = 0; % there is no path!
    end;
end;

Optimal_path = [];
PATH_COUNT = size(PATH, 1);
xval = PATH(PATH_COUNT, 2);
yval = PATH(PATH_COUNT, 3);

temp = PATH_COUNT;         
while(((xval ~= xTarget) || (yval ~= yTarget)) && temp > 0)
    temp = temp - 1;
    xval = PATH(temp, 2);
    yval = PATH(temp, 3);
end

i = 1;
Optimal_path(i, 1) = xval;
Optimal_path(i, 2) = yval;

if ((xval == xTarget) && (yval == yTarget))
    inode = 0;
    % Traverse PATH and determine the parent nodes
    parent_x = PATH(index(PATH, xval, yval), 4);
    parent_y = PATH(index(PATH, xval, yval), 5);
   
    while(parent_x ~= xStart || parent_y ~= yStart)
        i = i + 1;
        Optimal_path(i, 1) = parent_x; % store nodes on the optimal path
        Optimal_path(i, 2) = parent_y;
        inode = index(PATH, parent_x, parent_y); % find the grandparents :)
        parent_x = PATH(inode, 4);
        parent_y = PATH(inode, 5);
    end;
    Optimal_path(i+1,1) = xStart;    % add start node to the optimal path  
    Optimal_path(i+1,2) = yStart;
    j = size(Optimal_path, 1);
    j = j - 1;
    for i = j: -1 : 1
        maze(Optimal_path(i, 1), Optimal_path(i, 2)) = 6;
        dispMaze(maze);
    end
        
end

