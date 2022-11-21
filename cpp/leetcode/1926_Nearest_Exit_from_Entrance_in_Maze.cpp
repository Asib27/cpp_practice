class Solution {
    int inRange(int c, int a, int b){
        return c >= a & c < b;
    }
    
public:
    
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        const int dirx[] = {0, 0, 1, -1};
        const int diry[] = {1, -1, 0, 0};
        
        int m = maze.size(), n = maze[0].size();
            
        queue<pair<int, int>> qu;
        set<pair<int, int>> seen;
        
        qu.push({entrance[0], entrance[1]});
        seen.insert({entrance[0], entrance[1]});
        
        int step = 0;
        
        while(!qu.empty()){
            int sz = qu.size();
            for(int i = 0; i < sz; i++){
                auto cx = qu.front().first, cy = qu.front().second;
                qu.pop();
                
                if(cx == 0 || cx == m-1 || cy == 0 || cy == n-1)
                   if(step != 0)  return step;
            
                for(int i = 0; i < 4; i++){
                    auto nx = cx + dirx[i], ny = cy + diry[i];
                
                    if(inRange(nx, 0, m) && inRange(ny, 0, n) && 
                       maze[nx][ny] == '.' && !seen.count({nx, ny})){
                        seen.insert({nx, ny});
                        qu.push({nx, ny});
                    }
                }    
            }
            
            step++;
        }
        
        return -1;
    }
};
