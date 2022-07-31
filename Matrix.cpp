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
                if(i==0) firstRow = true;
                if(j==0) firstCol = true;
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