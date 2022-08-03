void print(int n){ //Function to print from 1 to n
    if(n == 1){
        cout<<n<<endl;
        return;//Base Condition
    } 

    print(n-1);//Recursive/Hypothesis Step

    cout<<n<<endl;//Induction Step
}

// Reverse an array
// T.C - O(N)
void reverseArray(int idx = 0,int arr[],int size){
    if(idx >= size/2) return;//Reached equal or beyond half of array

    swap(arr[idx],arr[idx - size - 1]);//Swap idx with idxes from last of array

    reverseArray(idx+1,arr,size);
}

// Check if string is palindrome
//T.C - O(N)
bool isPalindrome(string str,int idx){
    //We've reached past half of the string and haven;t return false yet
    if(idx >= str.length()/2) return true;

    if(str[idx] != str[str.length() - idx -1]) return false;

    return isPalindrome(str,idx+1);
}

// Program for Fibonacci numbers
//T.C - O(2^N)
int fib(int n){
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}


TypesOfSub{
    // Consider an array:
    //  {1,2,3,4}
    //  Subarray: contiguous sequence in an array i.e.
    //  {1,2},{1,2,3}
    //  Subsequence: Need not to be contiguous, but maintains order i.e.
    //  {1,2,4}
    //  Subset: Same as subsequence except it has empty set i.e.
    //  {1,3},{}
    //  Given an array/sequence of size n, possible
    //  Subarray = n*(n+1)/2
    //  Subsequence = (2^n) -1 (non-empty subsequences)
    //  Subset = 2^n
}
// Find all subarrays of array
//T.C - O(N^3)  S.C - O(1)
void printSubarrays(int arr[],int size){
    for(int start=0;start<size;start++){
        for(int end=start;end<size;end++){
            for(int i=start;i<=end;i++) cout<<arr[i]; 
        }
        cout<<endl;
    }
}


// Find all subsequences of string
//T.C - O(2^N) S.C - O(2^N)
void printSubsequence(string input, string output){
    // Base Case
    if (input.empty()) {//Reached the end of input string
        cout << output << endl;
        return;
    }
 
    //Output is passed with including the Ist character of input string
    printSubsequence(input.substr(1), output + input[0]);
 
    //Output is passed without including the Ist character of Input string
    printSubsequence(input.substr(1), output);
}


// Find all subsequences with sum equals to K
//T.C - O(2^N)  S.C - O(2^N)
void subsequenceEqualToK(int idx,vector<int>&ds,int s,int sum,int arr[],int n){
    if(idx == n){//Recursed until the end of array
       if(s == sum){//Sum in recursion path equals to given sum
       for(auto it:ds) cout<<it<<" ";
       }
       return;
    }
    //If we include the no at current idx for sum path
    ds.push_back(arr[idx]);
    s += arr[idx];
    subsequenceEqualToK(idx+1,ds,s,sum,arr,n);
    
    //Now to remove from ds and sum for the case of not including
    s -= arr[idx];
    ds.pop_back();
    subsequenceEqualToK(idx+1,ds,s,sum,arr,n);
}
// Find one subsequences with sum equals to K
bool subsequenceEqualToK(int idx,vector<int>&ds,int s,int sum,int arr[],int n){
    if(idx == n){//Recursed until the end of array
       if(s == sum){//Sum in recursion path equals to given sum
          for(auto it:ds){
           cout<<it<<" ";
           return true;
          } 
       }
       return false;
    }
    //If we include the no at current idx for sum path
    ds.push_back(arr[idx]);
    s += arr[idx];
    //If we get a subsequence from including case
    if(subsequenceEqualToK(idx+1,ds,s,sum,arr,n)) return true;
    
    //Now to remove from ds and sum for the case of not including
    s -= arr[idx];
    ds.pop_back();
    //If we get a subsequence from not including case
    if(subsequenceEqualToK(idx+1,ds,s,sum,arr,n)) return true;

    return false;//Did not find any subsequence equal to k sum
}
// Count the subsequences with sum K
// T.C - O(2^N)  S.C - O(2^N)
int countSubsequences(int arr[],int size,int sum,int idx,int s){
    if(s > sum) return 0;//If sum of recursive path exceeds given sum

    if(idx == size){//Recursed until the end of array
       //Sum in recursion path equals to given sum
       if(s == sum) return 1;
       else return 0;
    }
    //If we include the no at current idx for sum path
    s += arr[idx];
    //If we get a count of subsequence from including case
    int leftCount = countSubsequences(arr,size,sum,idx+1,s);
    
    //Now to remove from sum for the case of not including
    s -= arr[idx];
    //If we get a count of subsequence from not including case
    int rightCount = countSubsequences(arr,size,k,idx+1,s)

    return leftCount + rightCount;//Return count from both cases
}


// K-th Symbol in Grammar
// T.C - O(N)  S.C - O(N)
int kthGrammar(int n, int k) {
    if(n == 1 || k == 1) return 0;//Base Condition Given

    int  mid = pow(2,(n-1))/2;//Every time the length is inc by 2^n-1

    if(k <= mid) return kthGrammar(n-1,k-1);//For left half we can only check the prev row

    //We have to take !solve because the right half values are complement of prev row
    else return !kthGrammar(n-1,k-mid);//For right half the values for k changes
}


// All Possible Unique Subsets
// T.C - O(N*(2^N))  S.C - O(N*(2^N))
void printSubsets(int ind, vector<vector<int>> &ans, vector<int> &ds, vector<int> &nums){
    if(ind==nums.size()){//Index has reached to num size meaning we have traverse the no. of elements in array(whether include or not)
        ans.push_back(ds);//Found a subset so store it
        return;
    }
        
    ds.push_back(nums[ind]);//Include the current idx element in path of subset
    printSubsets(ind+1,ans,ds,nums);
    ds.pop_back();// Not include the current idx element in path of subset
    printSubsets(ind+1,ans,ds,nums);
}
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> ds;//Store the dfs/decision path
    printSubsets(0,ans,ds,nums);
    return ans;
}
// All Possible Unique Subsets(With Duplicates)
void helper(vector<int>& nums, vector<vector<int>>& ans, vector<int>& curr, int idx){
    ans.push_back(curr);   //we include current subset into final ans
    for(int i=idx;i<nums.size();i++){ //check for all possibilities
        if(i>idx &&  nums[i]==nums[i-1]) continue; //if duplicate then we continue
        curr.push_back(nums[i]);  //we include nums[i] in current subset
        helper(nums,ans,curr,i+1); 
        curr.pop_back();   //to get subset without nums[i]
    }
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> ans; //to store all subsets
    vector<int> curr;   //to store current individual subset (that we will build)
    sort(nums.begin(),nums.end());  //sort the array so that duplicates are adjacent 
    helper(nums,ans,curr,0);   //we start from index 0
    return ans;
        
}


// Generate all Balanced Parentheses
//T.C - O(2^n)  S.C - O(2^n)
void solve(int open ,int close,string temp,vector<string> &res){
    if(open == 0 && close == 0){//We've tried combos of all open and close braces
        res.push(temp);
        return;
    }

    //When we consider open braces
    //We can't start with close brace cuz then it can't be balanced
    if(open != 0) solve(open - 1,close,temp + "(",res);

    //When we consider close braces
    //More closed braces are there
    if(close > open) solve(open,close-1,temp + ")",res);
}
vector<string> generateParenthesis(int n) {
    vector<string> res;
    //Open and close braces will be equal to n
    int open = n;//Keep track of open braces
    int close = n;//Keep track of close braces
    solve(open,close,"",res);
    return res;
}


// Combination Sum I
//T.C - O(2^t*K) where k is time to push a subset of size k to ans  S.C - O(K*x) where x is no of combos
void findCombo(int index,int target,vector<int>& arr,vector<vector<int>> &ans,vector<int>&ds){
    //Found the sum on a recursive path
    if(index == arr.size()){
        if(target == 0) ans.push_back(ds);
        return;
    }
    //Now comes the choice step
    //We can only go to include case if curr element is not exceeding the target
    if(arr[index] <= target){
    //If we include the digit at curr idx for sum
    ds.push_back(arr[index]);
    //Decrease the target as we now only need to find rest of the target
    findCombo(index,target - arr[index],arr,ans,ds);
    ds.pop_back();//Backtracking
    }
        
    //If we don't take the current idx element for sum path
    findCombo(index+1,target,arr,ans,ds);//Skipping the digit at curr idx
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target){
    vector<vector<int>> ans;
    vector<int>ds;
    findCombo(0,target,candidates,ans,ds);
    return ans;
}


// Combination Sum II
//T.C - O(2^N * K)  S.C - O(K*x)
void findCombo(int index,int target,vector<int>& arr,vector<vector<int>> &ans,vector<int>&ds){
    if(target == 0){
        ans.push_back(ds);
        return;
    }
    //To try every element in array for recursive path
    for(int i=index;i<arr.size();i++){
        //Element is not duplicate and it is at a diff idx
        if(i>index && arr[i] == arr[i-1]) continue;
        if(arr[i] > target) break;//Exceeded the target bounds
        //Pass the curr pos of i as next index to pick and reduce the target sum 
        ds.push_back(arr[i]);
        findCombo(i+1,target-arr[i],arr,ans,ds);
        ds.pop_back();//Backtracking
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(),candidates.end());//To get all duplicates in adjacent form
    vector<vector<int>>ans;
    vector<int>ds;
    findCombo(0,target,candidates,ans,ds);
    return ans;
}


// Combination Sum III
// T.C - O(9Ck)  S.C - O(nK) where n is no. of combos and k is size of 1 subset
void comboSum(int idx,vector<int>&C,int target,vector<int>&sol,int k,vector<vector<int>>&ans){
    if(target == 0 && k == 0){//Found the sum by using exactly k no.
        ans.push_back(sol);//Store the subset
        return;
    }
    //Gone beyond the sum(-ve) or used more than k no.
    if(target < 0 || k < 0) return;
    //Exhausted all digits from 1 to 9;
    if(idx == C.size()) return;
        
    //Now comes the choice step

    //Not taking the digit means we can still use k digits and sum remains same
    comboSum(idx+1,C,target,sol,k,ans);//Skipping the digit at curr idx
        
    sol.push_back(C[idx]);//If we include the digit at curr idx for sum
        
    //Increase idx in both case as no digit should be repeated
    comboSum(idx+1,C,target-C[idx],sol,k-1,ans);
    //We used one digit now k-1 digits remain to select from
    sol.pop_back();//Backtracking
}
vector<vector<int>> combinationSum3(int k, int target) {
    vector<int> C = {1,2,3,4,5,6,7,8,9};//Candidate list for combo of sums
    vector<int> sol;
    vector<vector<int>>ans;
    comboSum(0,C,targer,sol,k,ans);
    return ans;
}


// Subsets Sums I
// T.C - O(2^N + 2^Nlog2^N)  S.C - O(2^N)
void findSum(int idx,int sum,vector<int>&arr,int size,vector<int>&sumSubset){
    // Store current subset
    if (idx == size) {
        sumSubset.push_back(sum);
        return;
    }
 
    // Subset including curr idx element
    findSum(idx+1,sum + arr[i],arr,size,sumSubset);//If curr element is part of subsetsum
 
    // Subset excluding curr idx element
    findSum(idx+1,sum,arr,size,sumSubset);
}
vector<int> subsetSums(vector<int> arr, int size) {
    vector<int>sumSubset;
    findSum(0,0,arr,size,sumSubset);
    sort(sumSubset.begin(),sumSubset.end());//To get all duplicates in adjacent form
    return sumSubset;
}


// Print all Permutations of a String/Array
// T.C - O(N!*N)  S.C - O(N)
void recurPermute(int index,vector<int>&nums,vector<vector<int>>&ans){
    if(index==nums.size()){//Found a permutation
        ans.push_back(nums);//Store it
        return;
    }
    //Try out all elements of array for picking
    for(int i=index;i<nums.size();i++){
        //To have every element as starting of permutation
        swap(nums[index],nums[i]);//Swap every element with the curr idx pos
        recurPermute(index+1,nums,ans);//Now recur for next idx element
        swap(nums[index],nums[i]);//While backtracking return to original form for the next guy
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> ans;
    recurPermute(0,nums,ans);
    return ans;
}


// N-Queens
//T.C - O(N*N)  S.C - O(N*N)
bool isSafe(int row,int col,vector<string>&board,int n){
    int duprow = row;//Store duplicates for reuses
    int dupcol = col;
        
    //Check if any queen is present diagonally upwards before the curr one
    while(row>=0 && col>=0){
        if(board[row][col]=='Q') return false;
        row--;
        col--;
    }
        
    col = dupcol;
    row = duprow;
    while(col>=0){//If any queen is present in same line horizontally
        if(board[row][col]=='Q') return false;
        col--;
    }

    col = dupcol;
    row = duprow;
    //Check if any queen is present diagonally downwards before the curr one
    while(row<n && col >= 0){
        if(board[row][col] == 'Q') return false;
        row++;
        col--;
    }
    return true;//If we reach here means it's safe to place queen
}
void placeNQueens(int col,vector<string>&board,vector<vector<string>>&ans,int n){
    if(col == n){//We have placed n queens in all cols
        ans.push_back(board);//Push back the board to ans
        return;
    }
    //Now try placing the queen in every row for a given col
    for(int row = 0; row < n; row++){
        if(isSafe(row,col,board,n)){//If its safe to place the queen in that row
        board[row][col] = 'Q';//Place the queen at that pos
        placeNQueens(col+1,board,ans,n);//After placing one queen, recur further and place queens in rest of the cols
        board[row][col] = '.';//Restore to original form for any diff possibilities
        }
    }
}
vector<vector<string>> solveNQueens(int n){
    //[[board1],[board2],[board3]]
    vector<vector<string>> ans;//Store all the boards
    //board(n=3) = ["...","...","..."]
    vector<string> board(n);//Store a single board
    // Place of queen in one col "..."
    string s(n,'.');//All queen pos in a board

    for(int i=0;i<n;i++) board[i] = s;//Initially fill the board with empty strings
    placeNQueens(0,board,ans,n);//Initially start with 0th col
    return ans;
}


// Tower of Hanoi
//T.C - O(2^N)  S.C - O(1)
void towerOfHanoi(int n, char from_rod,char to_rod, char aux_rod){
    if (n == 0) return;//Out of disks
    //The original function has [from rod -> to rod (aux rod)]

    //Now for first recursive call [from rod -> aux rod (to rod)]
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);//Send on disc from from_rod to aux_rod

    cout << "Move disk " << n << " from rod " << from_rod <<" to rod " << to_rod << endl;

    //Now for second recursive call [aux rod -> to rod (from rod)]
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}


// Sudoku Solver
//T.C - O(9^(N*N))  S.C - O(N*N)
bool isValid(vector<vector<char>>&board,int row,int col,char c){
    for(int i=0;i<9;i++){
        if(board[i][col] == c) return false;//Found one in same col
        if(board[row][i] == c) return false;//Found one in same row
        if(board[3*(row/3)+i/3][3*(col/3)+i%3] == c) return false;
    }
    return true;
}
bool solveSudoku(vector<vector<char>>& board) {
    //Traverse the whole board
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            //find empty spot
            if(board[i][j] == '.'){
                //try every number
                for(char c= '1';c<='9';c++){
                    //if spot is valid
                    if(isValid(board,i,j,c)){
                        board[i][j] = c;
                        //After placing the char at i and j
                        if(solveSudoku(board)) return true;//Check if the rest of the sudoku can be solved
                        else board[i][j] = '.';//Remove the char and backtrack for some other possibilities
                    }
                }
                return false;//Couldn't place any number from 1 to 9 in board
            }
        }
    }
    return true;
}


// M-Coloring Problem 
// T.C - O(N^M)  S.C - O(2N)
bool isSafe(int node,int color[],bool graph[101][101],int n,int color){
    for(int k=0;k<n;k++){
        //If any diff node has the same color as curr node
        if(k != node && graph[k][node] ==  1 && color[k] == color) return false;
    }
    return true;
}
bool placeColor(int node,int color[],int m,int n,bool graph[101][101]){
    if(node == n) return true;//Reached the end node(Able to color successfully)

    for(int i=1;i<=m;i++){//We'll try for all colors
    if(isSafe(node,color,graph,n,i)){
        color[node] = i;//Store the current color
        //After placing a color,check to place colors on rest of graph
        if(placeColor(node+1,color,m,n,graph)) return true;
        color[node] = 0;//Backtracking
    }
    }
    return false;//Wasn't able to place all colors
}
bool graphColoring(bool graph[101][101], int m, int n){
    int color[n] = {0};
    if(placeColor(0,color,m,n,graph)) return true;
    return false;
}


// Palindrome Partitioning
// T.C - O(2^N)  S.C - O(2^N)
bool isPalindrome(string s,int start,int end){
    while(start<=end){
        if(s[start++] != s[end--]) return false;
    }
    return true;
}
void palindromePartition(int index,string s,vector<string>&path,vector<vector<string>>&res){
    if(index == s.length()){
        res.push_back(path);
        return;
    }
    //For Every char in the string
    for(int i=index;i<s.length();i++){
        //Check if the partition from index to i is palindrome or not
        if(isPalindrome(s,index,i)){
            path.push_back(s.substr(index,i-index+1));//Include that palindromic path to path array
            palindromePartition(i+1,s,path,res);//Now recur for rest of the string
            path.pop_back();//Backtrack if and not found
        }
    }
}
vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string>path;
    palindromePartition(0,s,path,res);
    return res;
}
 

// Rat in A Maze
// T.C - O(4^(N*M))  S.C - O(M*N)
int dx[] = {1,0,0,-1};
int dy[] = {0,-1,1,0};
void findPath(int i,int j,vector<vector<int>>&a,int n,vector<string>&ans,string move,vector<vector<int>>&vis){
    if(i == n-1 && j == n-1){//We reached the destination point
        ans.push_back(move);
        return;
    }

    string dir = "DLRU"//Lexicographically ordered all possible dirs
    for(int idx = 0; idx < 4; idx++){
        int nx = i + dx[idx];//New dirs
        int ny = j + dy[idx];

        //If new dirs are in bound,haven't been visited yet and valid point
        if(nx >= 0 && ny >= 0 && nx < n && ny < n && !vis[nx][ny] && a[nx][ny] == 1){
            vis[i][j] = 1;//Mark the curr points as visited
            //Recur for rest of the grid with new dirs 
            findPath(nx,ny,a,n,ans,move + dir[idx],vis);
            vis[i][j] = 0;//Restore to original for other paths
        }
    }

}
vector<string> ratInMaze(vector<vector<int>> &m, int n) {
    vector<string>ans;
    vector<vector<int>>vis(n,0);
    
    //If starting coordinate is zero then we can't start
    if(m[0][0] == 1) findPath(0,0,m,n,ans,"",vis);
    return ans;
}


// Goldmine problem
//T.C - O(3^(N*M))  S.C - O(N*M)
int collectGold(vector<vector<int>>gold,int row,int col,int n,int m){
    if(row < 0 || row == n || col == m) return 0;//Invalid cases

    //Collect the gold from all the dirs he's able to move
    int rightUpperDiagonal = collectCold(gold,row-1,col+1,int n,int m);
    int rightStraight = collectCold(gold,row,col+1,int n,int m);
    int rightLowerDiagonal = collectCold(gold,row+1,col+1,int n,int m);

    //We only need to return the max gold from either dirs
    return gold[row][col] + max(max(rightUpperDiagonal,rightLowerDiagonal),rightStraight);
}
int getMaxGold(vector<vector<int>>gold,int n,int m){
    int maxGold = 0;
    //He's at first col but can be at any row so try all rows
    for(int i=0;i<n;i++){
        //Find the gold collected for every row and store max
        int goldCollected = collectGold(gold,i,0,n,m);
        maxGold = max(maxGold,goldCollected);
    }
    return maxGold;
}


// Josephus problem
//T.C - O(N)  S.C - O(N)
int josephus(int n, int k){
    //If only one person remains 
    if(n == 1) return 0;
    //Modding n because of the circle
    //The subproblem has relation f(n-1,k) + k(subproblem + k)
    else return (josephus(n-1,k) + k)%n;
}


// T.C - O(4^N)  S.C - O(N^2 + Stack space)
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int getMaxGold(vector<vector<int>>&grid,int i,int j,int row,int col,vector<vector<bool>> &vis){
    //Covers all invalid conditions
    if(i < 0 || i >= row || j < 0 || j >= col || grid[i][j] == 0 || vis[i][j]) return 0;

    int maxGoldPath = 0;
    vis[i][j] = true;//Mark the cell visited

    for(int k=0;k<4;k++){//Traverse in all 4 dirs
        //Store the max gold path from all 4 dirs
        maxGoldPath = max(maxGoldPath,getMaxGold(grid,i+dx[k],j+dy[k],row,col,vis));
    }
    vis[i][j] = false;//Set false for using other paths
    
    //Return the curr gold in cell plus the further path with max gold
    return grid[i][j] + maxGoldPath; 
}
int getMaximumGold(vector<vector<int>>& grid) {
    int maxGold = 0;
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<bool>>vis(row,vector<bool>(col,false));//One cell visited once

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(grid[i][j] != 0){
                //Store max gold
                maxGold = max(maxGold,getMaxGold(grid,i,j,row,col,vis));
            }
        }
    }
    return maxGold;
}


// Find K-th Permutation Sequence
// T.C - O(N!*N) + O(N!logN)  S.C - O(N!)
void solve(string & s, int index, vector < string > & res) {
    if (index == s.size()) {
        res.push_back(s);
        return;
    }
    for (int i = index; i < s.size(); i++) {
        swap(s[i], s[index]);
        solve(s, index + 1, res);
        swap(s[i], s[index]);
    }
}
string getPermutation(int n, int k) {
    string s;
    vector < string > res;
    //create string
    for (int i = 1; i <= n; i++) s.push_back(i + '0');

    solve(s, 0, res);
    //sort the generated permutations
    sort(res.begin(), res.end());

    //make k 0-based indexed to point to kth sequence
    auto it = res.begin() + (k - 1);
    return *it;
}


// The Knight’s tour
// T.C - O(8^N*N)  S.C - O(N*N)
int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2, 2 };
int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1, 1 };
bool isValid(int x,int y,int N){
    if(x < 0 || y < 0 || x >= N || y >= N) return false;
    return true;
}
void solveKnightTour(int visited[N][N],int x=0,int y=0,int pos=1,int N){
    vis[x][y] = pos;//Store the pos when visiting the curr cell

    if(pos >= N*N){//We have vis all the cells
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<vis[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    vis[x][y] = 0;//Backtracking
    return;
    }

    //We come here if we haven't vis all cells
    for(int k=0;k<8;k++){//Check in all directions for knight
    int nx = x + dx[k];
    int ny = y + dy[k];

    if(isValid(nx,ny) && !vis[nx,ny]) solveKnightTour(vis,,nx,ny,pos+1,N);
    
    }
    vis[x][y] = 0;
}


// Word Search
// T.C - O(4^N*N)  S.C - O(N*N)
bool wordSearch(vector<vector<char>>& board,string &word,int i,int j,int index){
    if(index == word.size()) return true;//We reach the end of word meaning we found it

    //If we're out of bounds
    if(i < 0 || i > board.size()-1 || j < 0 || j > board[0].size()-1) return false;

    //If the curr cell doesn't have the alphabet of word at index pos
    if(board[i][j] != word[index]) return false;

    //If we found the char match in matrix
    board[i][j] = '*';//Change the value to avoid duplicates

    //After finding one char , traverse in 4 dirs to find rest of the word
    bool furtherSearch =  wordSearch(board, word, i+1, j, index+1) || // up
    wordSearch(board, word, i-1, j, index+1) || // down
    wordSearch(board, word, i, j-1, index+1) || // left
    wordSearch(board, word, i, j+1, index+1);   // right

    board[i][j] = word[index];//change it back to original to explore other possibilities
    return furtherSearch;
}
bool exist(vector<vector<char>>& board, string word) {
    if(word.length() == 0) return false;

    //Traverse the whole matrix to find the word
    for(int i = 0; i < board.size();i++){
        for(int j = 0; j < board[0].size();j++){
            //If we find the given word in matrix
            if(wordSearch(board,word,i,j,0)) return true;
        }
    }
    return false;
}


// Tug of War
// T.C - O(2^N)  S.C - O(1)
void tugOfWar(vector<int>arr,int idx,vector<int>&set1,vector<int>&set2,int sos1,int sos2,int &ans=INT_MAX,string &division = ""){
    if(idx == arr.size()){
        int minDiff = abs(sos1 - sos2);
        ans = min(ans,minDiff);
        division = set1 + " " + set2;
        return;
    }

    //This if handles the case for subsets being odd or even length
    if(set1.size() < (arr.size() + 1)/2){
    set1.push_back(arr[idx]);//Consider curr element at idx to be a part of set1
    tugOfWar(arr,idx+1,set1,set2,sos1+arr[idx],sos2);//Recur for rest of the array and add to sum of set1
    set1.pop_back();//Remove the element from set while backtracking
    }

    //This if handles the case for subsets being odd or even length
    if(set2.size() < (arr.size() + 1)/2){
    set2.push_back(arr[idx]);//Consider curr element at idx to be a part of set2
    tugOfWar(arr,idx+1,set1,set2,sos1,sos2+arr[idx]);//Recur for rest of the array and add to sum of set2
    set2.pop_back();//Remove the element from set while backtracking
    }
}


// Number of Dice Rolls With Target Sum
// T.C - O(6^N) S.C - O(1)
void targetDice(string path = "", int target) {
    if(target == 0){//We managed to make target from dice numbers
        cout<<p<<endl;
        return;
    }

    //Loop for all the dice numbers and pick only the ones that are less than target
    for(int i=1; i<6 && i <= target; i++){
        targetDice(path + i,target - i);//Recursive call with reduced target and increased path
    }
}


// Letter Combinations of a Phone Number
// T.C - O(9^N) S.C - O(1)
const vector<string> keypad = {"", "", "abc", "def", "ghi", "jkl","mno", "pqrs", "tuv", "wxyz"};
void letterCombo(string digits,string output,int idx,vector<string>&keypadCombo){
    if(idx >= digits.length()){//Base case
        keypadCombo.push_back(output);
        return;
    }

    //Extract the int digit at which we're currently at
    int number = digits[idx] - '0';
    string mapping = keypad[number];//Store the char mapping for that digit

    for(int i=0;i<mapping.length();i++){
        output.push_back(mapping[i]);//Store the combo
        letterCombo(digits,output,idx + 1,keypadCombo);//Recur for further combos
        output.pop_back();//Backtrack for different possibilities
    }
}
vector<string> letterCombinations(string digits){
    vector<string> keypadCombo;
    if(digits.length() == 0) return keypadCombo;
    string output;
    int idx = 0;
    letterCombo(digits,output,idx,keypadCombo);
    return keypadCombo;
}