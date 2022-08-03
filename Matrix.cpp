// Rotate Image(Matrix)
// T.C - 2*O(N^2)  S.C - O(1)
void rotateImage(vector<vector<int>>& matrix) {
    //Transpose the matrix
    for(int i=0;i<matrix.size();i++){
        for(int j=i;j<matrix[0].size();j++){
            swap(matrix[i][j],matrix[j][i]);
        }
    }

    //Reverse every row
    for(int i=0;i<matrix.size();i++){
        int li = 0;
        int ri = matrix[i].size() - 1;
        while(li<ri){
            swap(matrix[i][li],matrix[i][ri]);
            li++;
            ri--;
        }
    }
}


// Set Matrix Zeroes
// Normal Approach
// T.C - O(N*M)  S.C - O(N+M)
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    int row[m];
    int col[n];
        
    for(int i=0;i<m;i++) row[i] = false;    
    for(int i=0;i<n;i++) col[i] = false;
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(matrix[i][j] == 0){
                row[i] = true;
                col[j] = true;
            }
        }
    }
        
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(row[i] || col[j]) matrix[i][j] = 0;
        }
    }
}
// Optimal Approach
// T.C - O(N*M)  S.C - O(1)
void setZeroes(vector<vector<int>>& a) {
    int n = a.size();
    int m = a[0].size();
    bool firstRow = false;  // do we need to set first row zero
    bool firstCol = false;  // do we need to ser first col zero
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
			if(a[i][j] == 0){   // store rows and cols state in first row and col
                if(i == 0) firstRow = true;
                if(j == 0) firstCol = true;

                a[i][0] = 0;
                a[0][j] = 0;
            }
        }
    }
    
    for(int i=1; i<n; i++){
        for(int j=1; j<m; j++){
            if(a[i][0] == 0 || a[0][j] == 0) a[i][j] = 0;
        }
    }
        
    if(firstRow){
        for(int i=0;i<m;i++) a[0][i] = 0;
    }
        
    if(firstCol){
        for(int i=0;i<n;i++) a[i][0] = 0;
    }
}


// Find min cost to reach the last cell
// Recursive Implementation
//T.C - O(2^N)  S.C - O(N)
int findCost(vector<vector<int>>& cost,int row,int col){
    if(row == 0 || col == 0) return INT_MAX;

    if(row == 1 && col == 1) return cost[0][0];

    return min(findCost(cost,row - 1,col) + 
    findCost(cost,row,col - 1)) + cost[row-1][col-1]; 
}
int minCost(vector<vector<int>>&cost){
    if(cost.size() == 0) return 0;

    int row = cost.size();
    int col = cost[0].size();

    return findCost(cost,row,col);
}
// Dynamic Programming
//T.C - O(N^2)  S.C - O(N^2)
int minCost(vector<vector<int>> &cost){
    if(cost.size() == 0) return 0;

    int row = cost.size();
    int col = cost[0].size();

    int dp[row][col];

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            dp[i][j] = cost[i][j];//Store the curr cost in dp

            //Only one way to reach first row(from left cell)
            if(i == 0 && j > 0) dp[0][j] += dp[0][j-1];

            //Only one way to reach first col(from top cell)
            else if(j == 0 && i > 0) dp[i][0] += dp[i-1][0];

            //Two ways to reach any other cell(from top or left)
            //Add the curr cost and take the min from either dirs
            else if(i > 0 && j > 0) dp[i][j] += min(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[row-1][col-1];
}


// Spiral Matrix
// T.C - O(N^2)  S.C - O(1)
vector<int> spiralOrder(vector<vector<int>>&matrix){
    int left = 0;//left upper corner
    int right = matrix[0].size() - 1;//right upper corner
    int top = 0;//moves from up to down(upper row)
    int bottom = matrix.size() - 1;//moves from right to left(right col)

    vector<int> res;

    while(left <= right && top <= bottom){
        //Go from left to right where row(top) is fixed
        for(int i=left;i<=right;i++) res.push_back(matrix[top][i]);
        top++;//Move top to a level below

        //Go from up to down where col(right) is fixed
        for(int i=top;i<=bottom;i++) res.push_back(matrix[i][right]);
        right--;//Move right to a level before

        if(left > right || top > bottom) break;

        //Go from right to left where row(bottom) is fixed
        for(int i=right;i>=left;i--) res.push_back(matrix[bottom][i]);
        bottom--;//Move bottom to a level above

        //Go from down to up where col(left) is fixed
        for(int i=bottom;i>=top;i--) res.push_back(matrix[i][left]);
        left++;//Move left to a level after
    }
    return res;
}


// Valid Sudoku
// T.C - O(9^2)  S.C - O(9^2)
bool isValidSudoku(vector<vector<char>>& board) {
    //Brute force  -> Iterate 3 times and check for row, col and box
    
    //Single iteration
    vector<set<int>> rows(9), cols(9), blocks(9);//Keeps track of nums
        
    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++) {
            //The cell must be filled to check further
            if (board[i][j] == '.') continue;
                
            int curr = board[i][j] - '0';//Extract the num from the cell

            //Check if duplicate is present in any case
            int rowDup = rows[i].count(curr);
            int colDup = cols[j].count(curr);
            int blockDup = blocks[(i/3)*3 + j/3].count(curr);

            if (rowDup || colDup || blockDup) return false;

            //Mark the nums as visited(push position in set) 
            rows[i].insert(curr);
            cols[j].insert(curr);
            blocks[(i/3)*3+j/3].insert(curr);
        }
    }
    return true;//No duplicate so valid sudoku
}


// 0 1 Matrix
// T.C - O(N*M)  S.C - O(N*M)
vector<int> dirs = {0, 1, 0, -1, 0};
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    int row = matrix.size();
    int col = matrix[0].size();
    
    queue<pair<int, int>> q;//DO BFS
    
    //Extract the cell coordinates of 0
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            if (matrix[i][j] == 0) q.push({i, j});
            else matrix[i][j] = -1; // Marked as not processed yet!
        }
    }

    while(!q.empty()){//Now queue has some cells which are 0
        int x = q.front().first;//Extract the coordinates
        int y = q.front().second;
        q.pop();
            
        //Check in all 4 dirs
        for(int i=0;i<4;++i) {
            int nx = x + dirs[i];
            int ny = y + dirs[i+1];

            //Invalid conditions so skip
            if (nx < 0 || nx == row || ny < 0 || ny == col || matrix[nx][ny] != -1) continue;
            
            matrix[nx][ny] = matrix[x][y] + 1;//Add 1 to prev val in cell
            q.push({nx, ny});//After updating add the new neighbor cell to queue
        }
    }
    return matrix;
}


//Shortest path in a maze – Lee Algorithm
//T.C - O(N*M)  S.C - O(N*M)
class Node{
    public:
    int x,
    int y,
    int dist
};
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };
int shortestPath(vector<vector<int>>& maze, int sr, int sc, int er, int ec){
    if(maze.size() == 0 || maze[sr][sc] == 0 || maze[er][ec] == 0) return -1;
    
    int row = maze.size();
    int col = maze[0].size();
    
    //Create a 2D array to mark the visited cells
    vector<vector<bool>> vis(row, vector<int>(col));
    
    queue<Node> q;//Create a queue
    vis[sr][sc] = true;//Mark the src visited
    q.push({sr, sc, 0});//Push in queue the coordinates for BFS
    int minDist = INT_MAX;
    
    while(!q.empty()){
        Node node = q.front();//Extract the node and its data
        q.pop();
        int i = node.x;
        int j = node.y;
        int dist = node.dist;
        
        if(i == er && j == ec){//REached the destination node
            minDist = dist;//Update the minDist
            break;
        }

        //Check in all 4 dirs
        for(int k=0;k<4;++k) {
            //New coordinates
            int nx = i + dx[k];
            int ny = j + dy[k];

            if(isValid(maze,vis,nx,ny)){
                vis[nx][ny] = true;//Mark the cell as visited
                q.push({nx, ny, dist+1});//Push in queue the coordinates for BFS
            }
        }
    }
    return minDist != INT_MAX ? minDist : -1;//Return the minDist or -1 if not found
}