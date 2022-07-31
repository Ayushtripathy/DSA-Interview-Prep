//Dynamic Programming
//Dynamic programming works by storing the result of subproblems so that
//when their solutions are required, they are at hand and we do not need
//to recalculate them. This technique of storing the value of subproblems
//is called memoization.

//Fibonacci Numbers
class Fibonacci {
    public:
    //Recursive Method
    //T.C - O(2^N)  S.C - O(N)
    int fibonacci(int n){
        if(n == 0) return 0;
        if(n == 1) return 1;
        else return fibonacci(n - 1) + fibonacci(n - 2);
    }

    //Memoization Method
    //T.C - O(N)  S.C - O(N)
    int fibonacci(int n){
        // we will make a call if an element in array dp is -1
        if(dp[n] == -1){//Number is not in array dp 
        if(n <= 1) dp[n] = n;
        //call to n-1  and n-2 as we haven't called them yet
        else dp[n] = fibonacci(n-1)+fibonacci(n-2);
        }
        return dp[n];//If we have already saved the value then return
    }
    
    //Dynamic Programming
    //T.C - O(N)  S.C - O(N)
    int fibonacci(int n){
        // dp[] for storing values of Fibonacci numbers
        int dp[n+1];
        // initialize zeroth and first element
        dp[0]=0;
        dp[1]=1;
        
        for(int i=2;i<=n;i++){
            // add previous two numbers to get the next term in series
            dp[i]=dp[i-1]+dp[i-2];
            }
        return dp[n];//Nth block in dp array contains the fib number
    }
};


// 0-1 Knapsack Problem
class Knapsack {
    public:
    //Recursive Method
    //T.C - O(2^N)  S.C - O(N)
    int maxProfit(vector<int> &values, vector<int> &weights, int n, int W){
        //Base Condition
        if(n == 0 || W == 0) return 0;//Array is empty or can't carry anything in sack
        
        //Recursive call
        //We're checking from last of array so [n-1]
        if(weights[n-1] > W){//Item wt exceeds the max capacity so don't pick this
        return maxProfit(values, weights, n-1, W);
        }
        
        else if(weights[n-1] <= W){//Item wt is in range of max capacity so we can pick this
        //Get the max from these two : 
        //1.Add the item value and recurse for the rest of items and also reduce the max weight capacity
        //2.Skip the item and don't get the profit
        int includeItem = values[n-1] + maxProfit(values, weights, n-1, W - weights[n-1]);
        int excludeItem = maxProfit(values, weights, n-1, W);
        return max(includeItem, excludeItem);
        }
    }

    //Memoization Method
    //T.C - O(N*W)  S.C - O(N*W)
    int dp[n+1][W+1];//memset(dp, -1, sizeof(dp))
    int maxProfit(vector<int> &values, vector<int> &weights, int n, int W){
        //Base Condition
        if(n == 0 || W == 0) return 0;//Array is empty or can't carry anything in sack
        
        //If we have already computed and stored the value in dp array 
        if(dp[n][W] != -1) return dp[n][W];
        
        //Haven't calculated and stored the value yet
        if(weights[n-1] <= W){//If we can pick this item
        int includeItem = values[n-1] + maxProfit(values, weights, n-1, W - weights[n-1]);//Can pick and pick it
        int excludeItem = maxProfit(values, weights, n-1, W);//Can pick but won't pick it
        return dp[n][W] = max(includeItem,excludeItem);
        } 
        
        else if(weights[n-1] > W){//If we can't pick this item
        return dp[n][W] = maxProfit(values, weights, n-1, W);
        }
    }

    //Dynamic Programming
    //T.C - O(N*W)  S.C - O(N*W)
    int maxProfit(vector<int> &values, vector<int> &weights, int n, int W){
        int dp[n+1][W+1];//Dp matrix to store values for each combo
        
        //Here n->i and W->j
        for(int i=0;i<=n;i++){//For each item in item array
           for(int j=0;j<=W;j++){//For all ranges of Wt of knapsack
              if(i == 0 || j == 0) dp[i][j] = 0;//Initialization
              
              else if(weights[i-1] <= j){//Can pick the item
               int includeItem = values[i-1] + dp[i-1][j-weights[i-1]];//Add the val of item picked and reduce the capacity of sack
               int excludeItem =  dp[i-1][j];//i(element) changes but j(weight of sack) remains same
               dp[i][j] = max(includeItem,excludeItem);
               }

              //Can't pick the item
              else if(weights[i-1] > j) dp[i][j] = dp[i-1][j];
            }
        }
        return dp[n][W];
    }
};


// Subset Sum Problem
class SubsetSum {
    public:
    // Recursive Method
    // T.C - O(2^N)  S.C - O(N)
    bool isSubsetSum(int arr[], int n, int sum){
    //Base Condition
    if(sum == 0) return true;//Found subset with sum
    if(n == 0) return false;//Exhausted the array

    //Recursive call
    //If curr element is greater than req sum
    if(arr[n-1] > sum)  return isSubsetSum(arr, n-1, sum);//Not picking

    else if(arr[n-1] <= sum){//Can pick the element
        int includeElement = isSubsetSum(arr,n-1,sum - arr[n-1]);//Can pick and reduce the sum
        int excludeElement = isSubsetSum(arr,n-1,sum);//Can pick but won't pick
        //If question says count subset sum -> return includeElement + excludeElement
        return includeElement || excludeElement;//Return whichever gives the right ans
        }
    }
    
    // Memoization Method
    // T.C - O(N*sum)  S.C - O(N*sum)
    int dp[n+1][sum+1];//memset(dp, -1, sizeof(dp));
    int isSubsetSum(int arr[], int n, int sum){
    //Base Condition
    if(sum == 0) return 1;//Found subset with sum
    if(n == 0 && sum != 0) return 0;//Exhausted the array

    if(dp[n][sum] != -1) return dp[n][sum];//Already computed and stored

    //Recursive call
    //If curr element is greater than req sum
    if(arr[n-1] > sum)  return dp[n][sum] = isSubsetSum(arr, n-1, sum);//Not picking

    // else if(arr[n-1] <= sum){//Can pick the element
    int includeElement = isSubsetSum(arr,n-1,sum - arr[n-1]);//Can pick and reduce the sum
    int excludeElement = isSubsetSum(arr,n-1,sum);//Can pick but won't pick
    //If question says count subset sum -> return dp[n][sum] includeElement + excludeElement
    return dp[n][sum] = includeElement || excludeElement;//Return whichever gives the right ans
    // }
    }
    
    //  Dynamic Programming
    // T.C - O(N*sum)  S.C - O(N*sum)
    bool isSubsetSum(int arr[], int n, int sum){
    bool dp[n+1][sum+1];

    //Initialize the dp array with base condition
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= sum; j++){
            if(i == 0) dp[i][j] = false;//Array is exhausted
            if(j == 0) dp[i][j] = true;//Sum is exhausted
        }
    }
    
    // start from 1 since 1st row and column is already considered 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= sum; j++){
            if(arr[i-1] <= j){//Can pick the element
                int includeElement = dp[i-1][j-arr[i-1]];//Reduce the sum after picking
                int excludeElement = dp[i-1][j];//Here j(sum) is not changed because not picking
                //If question says count subset sum -> dp[i][j] = includeElement + excludeElement
                dp[i][j] = includeElement || excludeElement;
            }
            //Can't pick the element
            else dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][sum];
    }
};


// Partition Equal Subset Sum
class EqualPartition {
    public:
    // Recursive Method
    //T.C - O(2^N)  S.C - O(N)
    bool canPartition(vector<int>& nums) {
    //Calculate the total sum of all elements
    int sum = accumulate(nums.begin(), nums.end(),0);

    //If sum is odd then it can't have two equal partitions
    if(sum % 2 != 0) return false;

    //Find if there is subset with sum equal to half of total sum
    return isSubsetSum(nums,nums.size(),sum/2);
    }
    
    //Memoization Method
    //T.C - O(N*sum)  S.C - O(N*sum)
    bool canPartition(vector<int>& nums) {
    //Calculate the total sum of all elements
    int sum = accumulate(nums.begin(), nums.end(),0);

    //If sum is odd then it can't have two equal partitions
    if(sum % 2 != 0) return false;

    //To store the overlappping problems
    vector<vector<int>>dp(nums.size()+1,vector<int>(sum+1,-1));

    //Find if there is subset with sum equal to half of total sum
    return isSubsetSum(nums,nums.size(),sum/2,dp);
    }
    
    // Dynamic Programming
    //T.C - O(N*sum)  S.C - O(N*sum)
    bool canPartition(vector<int>& nums) {
    //Calculate the total sum of all elements
    int sum = accumulate(nums.begin(), nums.end(),0);

    //If sum is odd then it can't have two equal partitions
    if(sum % 2 != 0) return false;

    //Find if there is subset with sum equal to half of total sum
    return isSubsetSum(nums,nums.size(),sum/2);
    }
};


// Minimum Subset Sum Difference(Only works for positive)
class MinSubsetSumDiff {
    public:
    //Dynamic Programming
    //T.C - O(N*range)  S.C - O(N*range)
    vector<int> isSubsetPossible(vector<int>& nums,int size,int sum){
        bool dp[size+1][sum+1];

        //Initialization
        for(int i=0;i<=size;i++){
            for(int j=0;j<=sum;j++){
                if(i == 0) dp[i][j] = false;
                if(j == 0) dp[i][j] = true;
            }
        }

        for(int i=1;i<=size;i++){
            for(int j=1;j<=sum;j++){
                if(nums[i-1] <= j){//Can pick
                    int include = dp[i-1][j-nums[i-1]];
                    int exclude = dp[i-1][j];
                    dp[i][j] = include || exclude;
                }
                else dp[i][j] = dp[i-1][j];//Can't pick
            }
        }
        //The question requires a vector from fn having subset elements that form the sum
        vector<int> temp;
        //The last row tells whether a subset sum for sum(i) exists or not
        //Range of sums can be from 0 to sum of arr
        for(int i=0; i<=sum;i++){//But we can't form all the sums in range from arr elements so we check
            //dp[size][i] being true means we were able to form this sum(j) from arr element
            if(dp[size][i] == true) temp.push_back(i);//Store that subset sum
        }
        return temp;
    }

    int minimumDifference(vector<int>& nums) {
        int range = accumulate(nums.begin(), nums.end(),0);

        //Vec has Sum1(sums for part 1)
        vector<int>vec = isSubsetPossible(nums,nums.size()-1,range);

        int minDiff = INT_MAX;
        for(int i=0;i<vec.size();i++){//vec has all possible subset sums in range
            minDiff = min(minDiff,abs(range - 2*vec[i]));//Derived formula
        }
        return minDiff;
    }
};


//Count the number of subset with a given difference(Target Sum)
class CountSubsetDiff {
    // Let sum of subset 1 be s1 and subset 2 with s2
    // s1 - s2 = diff (given)
    // s1 + s2=sum of array (logical)
    // Therefore adding both eq we get :
    // 2s1 = diff + sum of array
    // s1 = (diff + sum of array)/2;
    // Problem reduces to find no of subsets with given sum
    public:
    //T.C - O(N*sum)  S.C - O(N*sum)
    int subsetSum(int arr[],int n,int sum){
        int dp[n+1][sum+1];

        for(int i=0;i<=n;i++){
            for(int j=0;j<=sum;j++){
                if(i == 0) dp[i][j] = 0;//Exhausted the array
                if(j == 0) dp[i][j] = 1;//Exhausted the sum
            }
        }

        for(int i=0;i<=n;i++){
            for(int j = 0; j <= sum; j++){
                if(arr[i-1] <= j){//Can pick
                int include = dp[i-1][j-arr[i-1]];
                int exclude = dp[i-1][j];
                dp[i][j] = include + exclude;
                }
                //Can't pick
                else dp[i][j] = dp[i-1][j];
            }
        }
        return dp[n][sum];
    }

    int countWithGivenDiff(int arr[], int n, int diff){   
    int sum = accumulate(arr,arr+n,0);//Sum of array 
	//reqSum=(diff+sum)/2 -> Derived from equation
    if((diff + sum)%2 != 0) return 0;//Can't be broken into pairs
	return subsetSum(arr,n,(sum + diff)/2);//Prev solution to count subset sum
    }
};


// Target Sum
class TargetSum {
    public:
    //Dynamic Programming
    //T.C - O(N*sum)  S.C - O(N*sum)
    int findTargetSumWays(vector<int> &nums, int target) {
        //Solution 1
        int sum = 0;
        for(int x : nums) sum += x;

        // base cases , sum should be greater then target and difference should always be even for equal subsets
        if(((sum - target) % 2 == 1) || (target > sum)) return 0;
        
        int n = nums.size();
        int s2 = (sum - target)/2;
        int dp[n + 1][s2 + 1];//Dp array
        dp[0][0] = 1;// 0 elements required to get 0 sum
        
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= s2; j++) {
                if(nums[i - 1] <= j){//Can pick
                    dp[i][j] = dp[i-1][j] + dp[i - 1][j - nums[i - 1]];
                }
                //Can't pick'
                else dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[n][s2];
    }
};


// Unbounded Knapsack(Rod cutting problem)
class UnboundedKnapsack {
    // Diff is we can pick an item again and again wherever there is n-1/i-1 make it n/i for pick case
    public:
    //Recursive Method
    //T.C - O(2^N)  S.C - O(N)
    int maxProfit(vector<int> &values, vector<int> &weights, int n, int W){
        //Base Condition
        if(n == 0 || W == 0) return 0;//Array is empty or can't carry anything in sack
        
        //Recursive call
        //We're checking from last of array so [n-1]
        if(weights[n-1] > W){//Item wt exceeds the max capacity so don't pick this
        return maxProfit(values, weights, n-1, W);//fIf not picking then go to prev item(n-1)
        }
        
        else if(weights[n-1] <= W){//Item wt is in range of max capacity so we can pick this
        //Get the max from these two : 
        //1.Add the item value and recurse for the rest of items and also reduce the max weight capacity
        //2.Skip the item and don't get the profit
        //If picking then you can pick again so fn(n) not fn(n-1)
        int includeItem = values[n-1] + maxProfit(values, weights, n, W - weights[n-1]);
        int excludeItem = maxProfit(values, weights, n-1, W);
        return max(includeItem, excludeItem);
        }
    }

    //Memoization Method
    //T.C - O(N*W)  S.C - O(N*W)
    int dp[n+1][W+1];//memset(dp, -1, sizeof(dp))
    int maxProfit(vector<int> &values, vector<int> &weights, int n, int W){
        //Base Condition
        if(n == 0 || W == 0) return 0;//Array is empty or can't carry anything in sack
        
        //If we have already computed and stored the value in dp array 
        if(dp[n][W] != -1) return dp[n][W];
        
        //Haven't calculated and stored the value yet
        if(weights[n-1] <= W){//If we can pick this item
        //If picking then you can pick again so fn(n) not fn(n-1)
        int includeItem = values[n-1] + maxProfit(values, weights, n, W - weights[n-1]);//Can pick and pick it
        int excludeItem = maxProfit(values, weights, n-1, W);//Can pick but won't pick it
        return dp[n][W] = max(includeItem,excludeItem);
        } 
        
        else if(weights[n-1] > W){//If we can't pick this item
        return dp[n][W] = maxProfit(values, weights, n-1, W);
        }
    }

    //Dynamic Programming
    //T.C - O(N*W)  S.C - O(N*W)
    int maxProfit(vector<int> &values, vector<int> &weights, int n, int W){
        int dp[n+1][W+1];//Dp matrix to store values for each combo
        
        //Here n->i and W->j
        for(int i=0;i<=n;i++){//For each item in item array
           for(int j=0;j<=W;j++){//For all ranges of Wt of knapsack
              if(i == 0 || j == 0) dp[i][j] = 0;//Initialization
              
              else if(weights[i-1] <= j){//Can pick the item
              //If picking then you can pick again so dp(i) not dp(i-1)
               int includeItem = values[i-1] + dp[i][j-weights[i-1]];//Add the val of item picked and reduce the capacity of sack
               int excludeItem =  dp[i-1][j];//i(element) changes but j(weight of sack) remains same
               dp[i][j] = max(includeItem,excludeItem);
               }

              //Can't pick the item
              else if(weights[i-1] > j) dp[i][j] = dp[i-1][j];
            }
        }
        return dp[n][W];
    }
};


// Ways to make coin change
class WaysCoinChange {
    //Type of subset sum and unbounded knapsack
    public:
    // Recursive Method
    // T.C - O(2^N)  S.C - O(N)
    bool coinChange(int coins[], int n, int amount){
    //Base Condition
    if(amount == 0) return true;//Found subset with amount
    if(n == 0) return false;//Exhausted the array

    //Recursive call
    //If curr element is greater than req amount
    if(coins[n-1] > amount)  return coinChange(coins, n-1, amount);//Not picking

    else if(coins[n-1] <= amount){//Can pick the element
        int includeElement = coinChange(coins,n,amount - coins[n-1]);//Can pick and reduce the amount
        int excludeElement = coinChange(coins,n-1,amount);//Can pick but won't pick
        //If question says count coins -> return includeElement + excludeElement
        return includeElement + excludeElement;//Return whichever gives the right ans
        }
    }
    
    // Memoization Method
    // T.C - O(N*sum)  S.C - O(N*sum)
    int dp[n+1][amount+1];//memset(dp, -1, sizeof(dp));
    int coinChange(int coins[], int n, int amount){
    //Base Condition
    if(amount == 0) return 1;//Found subset with amount
    if(n == 0 && amount != 0) return 0;//Exhausted the array

    if(dp[n][amount] != -1) return dp[n][amount];//Already computed and stored

    //Recursive call
    //If curr element is greater than req amount
    if(coins[n-1] > amount)  return dp[n][amount] = coinChange(coins, n-1, amount);//Not picking

    // else if(coins[n-1] <= amount){//Can pick the element
    int includeElement = coinChange(coins,n,amount - coins[n-1]);//Can pick and reduce the amount
    int excludeElement = coinChange(coins,n-1,amount);//Can pick but won't pick
    //If question says count subset amount -> return dp[n][amount] includeElement + excludeElement
    return dp[n][amount] = includeElement + excludeElement;//Return whichever gives the right ans
    // }
    }
    
    //  Dynamic Programming
    // T.C - O(N*sum)  S.C - O(N*sum)
    int coinChange(int coins[], int n, int amount){
    int dp[n+1][amount+1];

    //Initialize the dp array with base condition
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= amount; j++){
            if(i == 0) dp[i][j] = 0;//coins are exhausted
            if(j == 0) dp[i][j] = 1;//amount is exhausted
        }
    }
    
    // start from 1 since 1st row and column is already considered 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= amount; j++){
            if(coins[i-1] <= j){//Can pick the element
                int includeElement = dp[i][j-coins[i-1]];//Reduce the amount after picking
                int excludeElement = dp[i-1][j];//Here j(amount) is not changed because not picking
                dp[i][j] = includeElement + excludeElement;
            }
            //Can't pick the element
            else dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][amount];
    }
};


// Minimum number of coins
class MinCoins {
    //  Dynamic Programming
    // T.C - O(N*amount)  S.C - O(N*amount)
    int coinChange(int coins[], int n, int amount){
    int dp[n+1][amount+1];

    //Initialize the dp array with base condition
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= amount; j++){
            if(i == 0) dp[i][j] = INT_MAX-1;//To form a amount without any coins we need infinite coins
            if(j == 0) dp[i][j] = 0;//To form amount 0 we don't need any coin
        }
    }
    
    // start from 1 since 1st row and column is already considered 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= amount; j++){
            if(coins[i-1] <= j){//Can pick the element
            //We take dp[i] and not dp[i-1] as we can take one coin again and again
                int includeElement = 1 + dp[i][j-coins[i-1]];//Reduce the amount after picking one coin
                int excludeElement = dp[i-1][j];//Here j(amount) is not changed because not picking
                dp[i][j] = min(includeElement,excludeElement);
            }
            //Can't pick the element
            else dp[i][j] = dp[i-1][j];
        }
    }
    //Check whether ans is not infinite
    return (dp[n][amount] == INT_MAX-1) ? -1 : dp[n][amount];
    }
};


// Longest Common Subsequence
class LCS {
    public:
    //Recursive Method
    //T.C - O(2^N)  S.C - O(N)
    int LCS(string X,string Y,int n,int m){
        //We'll  start from end of both strings in recursive approach
        if(n == 0 || m == 0) return 0;//If either of the string is exhausted

        //Choice Step
        if(X[n-1] == Y[m-1]){//When both string X and Y is having same last char
            return 1 + LCS(X, Y, n-1, m-1);//Count the number and decrement the both's string length
        }
        //When both string's last character is not same 
        else{ // Take one string full and leave another as it is and vice versa
            int pickX = LCS(X, Y, n-1, m);
            int pickY = LCS(X, Y, n, m-1);
            return max(pickX, pickY);//Store the max from both choices
        }
    }

    //Memoization Method
    //T.C - O(N*M)  S.C - O(N*M)
    int dp[n+1][m+1];//memset(dp, -1, sizeof(dp))
    int LCS(string X, string Y, int n, int m){
       //We'll  start from end of both strings in recursive approach
        if(n == 0 || m == 0) dp[n][m] = 0;//If either of the string is exhausted

        if(dp[n][m] != -1) return dp[n][m];//If already computed and stored

        //Choice Step
        if(X[n-1] == Y[m-1]){//When both string X and Y is having same last char
            //Count the number(Adding 1 because we found 1 common) and decrement the both's string length
            dp[n][m] = 1 + LCS(X, Y, n-1, m-1);
        }
        //When both string's last character is not same 
        else{ // Take one string full and leave another as it is and vice versa
            int pickX = LCS(X, Y, n-1, m);
            int pickY = LCS(X, Y, n, m-1);
            dp[n][m] = max(pickX, pickY);//Store the max from both choices
        }
        return dp[n][m]; 
    }

    //Dynamic Programming
    //T.C - O(N*M)  S.C - O(N*M)
    int LCS(string X, string Y, int n, int m){
        int dp[n+1][m+1];

        for(int i=0; i<=n; i++){
            for(int j=0; j<=m; j++){
                if(i == 0 || j == 0) dp[i][j] = 0;//Base condition

                //Found same char so add 1 and reduce both str
                else if(X[i-1] == Y[j-1]) dp[i][j] = 1 + dp[i-1][j-1];

                //If the question asks Longest repeated subsequence
                //We need repeated substr so when chars match make sure they are at diff idx
                //else if(X[i-1] == Y[j-1] && i != j) dp[i][j] = 1 + dp[i-1][j-1];

                //Take max by reducing one by one both str 
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[n][m];


            //To print the LCS
            string ans;
            int i = m, j = n;
            while(i > 0 && j > 0){
                // If current character in both the strings are same, then current character is part of LCS
                if(str1[i - 1] == str2[j - 1]){
                    ans.push_back(str1[i-1]);
                    i--,j--;
                    }
                // If current character in X and Y are different & we are moving upwards
                else if(dp[i - 1][j] > dp[i][j - 1]) i--;
                // If current character in X and Y are different & we are moving leftwards
                else j--;
            }
            reverse(ans.begin(), ans.end());
            cout<<ans;
    }
};


// Longest Common Substring
//Dynamic Programming
//T.C - O(N*M)  S.C - O(N*M)
int LCS(int X, int Y, int n, int m){
    //Substring needs to be continuos
    int dp[n+1][m+1];

    int maxSubstring = 0;

    for(int i=0; i<=n; i++){
        for(int j=0; j<=m; j++){
            if(i == 0 || j == 0) dp[i][j] = 0;//Base condition
            //Found same char so add 1 and reduce both str
            else if(X[i-1] == Y[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];//Store the substr
                maxSubstring = max(maxSubstring,dp[i][j]);//Keep storing the curr longest substring
            } 
            //If strings don't match reset length to 0 due to discontinuity of substring
            else dp[i][j] = 0;
        }
    }
    return dp[n][m];
}


//Shortest Common Supersequence
//Dynamic Programming
//  T.C - O(N*M)  S.C - O(N*M)
string shortestCommonSupersequence(string str1, string str2) {
    //Form a merged string that has both s1 and s2 as subsequences
    //Total merged string  - LCS to remove duplicates(common) in both strings
    int minSupSeq = str1.length() + str2.length() - LCS(str1,str2,str1.length(),str2.length());

    //Now printing the min supersequence
    string ans = "";
    int i = str1.length();
    int j = str2.length();
    while(i > 0 && j > 0){
        if(str1[i-1] == str2[j-1]){//We add to ans when found common
            ans += str1[i-1];
            i--,j--;//Tracing back our steps
        }
        //When str is diff include both in ans depending on max
        else if(dp[i][j-1] > dp[i-1][j]){//If we took max from col side
            ans += str2[j-1];//Take char from str2
            j--;//Decrement the side from which we took the max
        }
        else{//If we took max from row side
            ans += str1[i-1];
            i--;
        }
    }

    //We don't take this case in LCS because if 1 str gets empty we can't find common anymore
    while(i-- > 0) ans += str1[i-1];
    while(j-- > 0) ans += str2[j-1]; 

    reverse(ans.begin(), ans.end());
    return ans;
}


// Longest Palindromic Subsequence
// Dynamic Programming
//T.C - O(N*M)  S.C - O(N*M)
int longestPalindromeSubseq(string s) {
    string x = s;
    reverse(x.begin(), x.end());
    return LCS(s,x,s.length(),x.length());
}


// Longest Palindromic Substring
// Dynamic Programming
//T.C - O(N*M)  S.C - O(N*M)
string longestPalindrome(string s) {
    int n = s.length();
    if(n == 0) return s;// if there is no string the return empty string
    
    bool dp[n][n];// declaring boolean array to be false
    memset(dp, 0, sizeof(dp));
    
    // declaring all the substring with single letter be true because they all are palindromic
    for(int i = 0; i < n; i++) dp[i][i] = true;
        
    // this will store longest palindromic substring
    string ans = "";
    // if no palindromic substring found then the single letter will always be the answer
    ans += s[0];
        
    // now iterating the boolean matrix where the 
    //row and col are the start and end of the substring row == start and column == end
        
    for(int i = n-1; i >= 0; i--) {
        for(int j = i+1; j < n; j++) {
            // if the start and end are equal then look for next conditions
            if(s[i] == s[j]) {
                // whether the substring is of length 2 or the substring inside the extremist is palindromic or not if yes then the whole current substring is pallindromic
                if(j - i == 1 || dp[i+1][j-1]) {
                    dp[i][j] = true;        
                    // if the current substring size if greater then current then the previous ans stored then update the answer
                    if(ans.size() < j-i+1) ans = s.substr(i, j-i+1);
                    }
                }
            }
        }
    return ans;
}


// Count Palindromic substrings
// Dynamic Programming
//T.C - O(N^2/2)  S.C - O(N^2)
int countSubstrings(string s) {
    int n = s.length();
    bool dp[n][n];
    int cnt = 0;
    
    // only way is diagonal by diagonal filling as  we will access previous diagonal elements
    for(int gap=0;gap<n;gap++){// gap is len of substr in a cell
        // all diagonals start from 0th row and ends at (n-1)th coi
        for(int i=0,j=gap;j<n;i++,j++){
           
            // diagonal with gap 0 (all single character substrings are palindromes)
            if(gap == 0) dp[i][j] = true;

            else if(gap == 1){ // diagonal with gap 2
                if(s[i] == s[j]) dp[i][j] = true;//If chars are same then only its palindrome
                else dp[i][j] = false;
            }

            // all other diagonals
            else{
                //dp[i+1][j-1] means that middle of substr(except extreme pt) should also be palindrome
                if(s[i] == s[j] && dp[i+1][j-1] == true) dp[i][j] = true;
                else dp[i][j] = false;
                }
            // count all palindromes
            if(dp[i][j]) cnt++;
            //If asks max longest palindrome len
            // if(dp[i][j]) maxPal = gap+1;//Store the max palindrome

        }
    }
    return cnt;
}


// Delete Operation for Two Strings
// Dynamic Programming
//T.C - O(N*M) S.C - O(N*M)
int minDistance(string word1, string word2) {
    int lcs = LCS(word1,word2,word1.length(),word2.length());

    // Operations to make str palindrome
    // lps = LCS(word1,reverse(word1),word1.length(),word2.length());
    //ans = word1.length() - lps;

    //Now to make two strs same just leave the lcs and remove the rest chars
    int delete1 = word1.length() - lcs;
    int delete2 = word1.length() - lcs;

    return delete1 + delete2;
}


// Sequence Pattern Matching
// Dynamic Programming
// T.C - O(N*M)  S.C - O(N*M)
int seqMatch(string s,string t){
    return LCS(s,t,s.length(),t.length()) == min(s.length(),t.length());
}


// Edit Distance
// T.C - O(N*M)  S.C - O(N*M)
int minDistance(string word1, string word2) {
    int n = word1.size();
    int m = word2.size();
        
    int dp[n+1][m+1];
        
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i == 0) dp[i][j] = j;//word1 is null so insert word2 in dp
            if(j == 0) dp[i][j] = i;//word2 is null so insert word1 in dp
        }
    }
        
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            // if char match then check for rest of the string
            if(word1[i-1] == word2[j-1])
                dp[i][j] = dp[i-1][j-1];  
            // if char does not match, we have three options
            // 1. delete the unmatching char from word1. 
            // 2. insert the unmaching char in word1.
            // 3. replace the unmatching char with the char to be matched
            else dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    } 
    return dp[n][m];
}


// Matrix Chain Multiplication
class MCM {
    public:
    //Recursive Method
    // T.C - O(2^N) S.C - O(N)
    int matrixChainMultiplication(int arr[],int size,int i = 1,int j = size-1){
      if(i >= j) return 0;//We nee at least 2 values(dimensions)

      int minCost = INT_MAX;
      //Move k from i(1st element) to j(2nd last element)
      for(int k=i;k<=j-1;k++){
        //K just denotes the dividing bracket like (AB)*k*C and A*k*(BC)
        // recur for `M[i+1]…M[k]` to get an `i × k` matrix
        int cost = matrixChainMultiplication(arr, i, k);
 
        // recur for `M[k+1]…M[j]` to get an `k × j` matrix
        cost += matrixChainMultiplication(arr, k+1, j);
 
        // cost to multiply two `i × k` and `k × j` matrix
        cost +=    arr[i] * arr[k] * arr[j];

        minCost = min(cost, minCost);
      }
      return minCost;
    }

    //Memoization Method
    // T.C - O(N^3) S.C - O(N*N)
    int dp[1001][1001];//memset(dp, -1, sizeof(dp));
    int minCostMCM(int arr[],int size,int i,int j){
      //dp[i][j] denotes the mincost in each recursive step
      if(i >= j){
        dp[i][j] = 0;
        return 0;//We nee at least 2 values(dimensions)
      }

      if(dp[i][j] != -1) return dp[i][j];//If already computed and stored

      int  dp[i][j] = INT_MAX;
      //Move k from i(1st element) to j(2nd last element)
      for(int k=i;k<j;k++){
          //K just denotes the dividing bracket like (AB)*k*C and A*k*(BC)
          //temp ans stores the cost by placing k at each combo
          int temp = minCostMCM(arr,size,i,k) + minCostMCM(arr,size,k+1,j) + arr[i-1]*arr[k]*arr[j];
          dp[i][j] = min(dp[i][j],temp);
      }
      return dp[i][j];
    }

    //Dynamic Programming
    // T.C - O() S.C - O()
};


// Palindrome Partitioning
class PalindromePartitioning {
    private:
    bool isPalindrome(string X, int i, int j) { // function to check either a string is palindrome or not 
        while (i <= j) {
            if (X[i] != X[j]) return false;
            i++, j--;
        }
	return true;
    }

    public:
    //Recursive Method
    // T.C - O(2^N) S.C - O(N)
    int palindromePartition(string arr,int i = 0,int j = size-1){
      if(i >= j || isPalindrome(arr,i,j)) return 0;//We nee at least 2 values(dimensions)

      int minPartition = INT_MAX;

       /* Instead of writing below standard line We will recurse for only right part
          Only when left part turns out to be palindrome
          int temp =  solve (s, i, k, dp, palindrome) + solve (s, k+1, j, dp, palindrome) + 1;*/
            

      for(int k=i;k<j;k++){
              int partition = 1 + palindromePartition(arr, i, k) + palindromePartition(arr, k+1, j);
              minPartition = min(partition, minPartition);//Store the min cost of partition
      }
      return minPartition;
    }


    //Memoization Method
    // T.C - O() S.C - O()
    vector<vector<int>> dp (n+1, vector<int> (n+1, -1));
    int palindromePartition(string arr,int i = 1,int j = size-1){
      if(i >= j || isPalindrome(arr,i,j)) return 0;

      /* Instead of writing below standard line We will recurse for only right part
          Only when left part turns out to be palindrome
          int temp =  solve (s, i, k, dp, palindrome) + solve (s, k+1, j, dp, palindrome) + 1;*/

      if(dp[i][j] != -1) return dp[i][j];//If already computed and stored

      int minPartition = INT_MAX;
      //Move k from i(1st element) to j(2nd last element)
      for(int k=i;k<j;k++){
          if(isPalindrome(arr,i,k)){
              int partition = 1 + palindromePartition(arr, k+1, j);
              minPartition = min(partition, minPartition);//Store the min cost of partition
          }
      }
      return dp[i][j] = minPartition;//Store in dp table as well as return ans
    }
};


// Boolean Parenthesization
class BooleanParenthesization {
    public:
    //Recursive Method
    //T.C - O(4^N)  S.C - O(N)
    int evaluateToTrue(string str, int i, int j, bool isTrue){
        if(i > j) return 0;//Invalid Case

        if(i == j){//If only one char is there
            // if isTrue==1 & str[i] ='T' it means we required a true and got it so return 1 else return 0
			// if isTrue==0 & str[i] ='F' it means we required a false and got it so return 1 else return 0
            if(isTrue) return str[i] == 'T';
            else return str[i] == 'F';
        }

        int ans = 0;//Store the no. of ways

        for(int k=i+1;k<=j-1;k+=2){
            //Calculate for the 4 cases
            int leftTrue = evaluateToTrue(str,i,k-1,true);
            int leftFalse = evaluateToTrue(str,i,k-1,false);
            int rightTrue = evaluateToTrue(str,k+1,j,true);
            int rightFalse = evaluateToTrue(str,k+1,j,false);

            //Now evaluate ans based on which operator k is at
            if(str[k] == '^'){
                if(isTrue) ans += (leftTrue*rightFalse) + (leftFalse*rightTrue);
                else ans += (leftTrue*rightTrue) + (leftFalse*rightFalse);
            }
            else if(str[k] == '&'){
                if(isTrue) ans += leftTrue*rightTrue;//We want exp to be true
                else ans += (leftTrue*rightFalse) + (leftFalse*rightTrue) + (leftFalse*rightFalse);
            }
            else if(str[k] == '|'){
                if(isTrue) ans += (leftTrue*rightFalse) + (leftFalse*rightTrue) + (leftFalse*rightFalse);
                else ans += (leftFalse*rightFalse);
            }
        }
        return ans;
    }

    //Memoization Method
    //T.C - O(N^2)  S.C - O(N^2)
    int dp[2][1001][1001];//memset(dp, -1, sizeof(dp))
    int evaluateToTrue(string str,int j,int j,int isTrue){
        if(i > j) return 0;//Invalid Case

        if(i == j){//If only one char is there
            // if isTrue==1 & str[i] ='T' it means we required a true and got it so return 1 else return 0
			// if isTrue==0 & str[i] ='F' it means we required a false and got it so return 1 else return 0
            if(isTrue) dp[1][i][j] = str[i] == 'T';
            else dp[0][i][j] = str[i] == 'F';

            return dp[isTrue][i][j];//Return based on true value
        }

        if(dp[isTrue][i][j] != -1) return dp[isTrue][i][j];//If already computed and stored

        int ans = 0;//Store the no. of ways
        for(int k=i+1;k<=j-1;k=k+2){
            //Calculate for the 4 cases
            int leftTrue = evaluateToTrue(str,i,k-1,true);
            int leftFalse = evaluateToTrue(str,i,k-1,false);
            int rightTrue = evaluateToTrue(str,k+1,j,true);
            int rightFalse = evaluateToTrue(str,k+1,j,false);

            //Now evaluate ans based on which operator k is at
            if(str[k] == '^'){
                if(isTrue) ans += (leftTrue*rightFalse) + (leftFalse*rightTrue);
                else ans += (leftTrue*rightTrue) + (leftFalse*rightFalse);
            }
            else if(str[k] == '&'){
                if(isTrue) ans += leftTrue*rightTrue;//We want exp to be true
                else ans += (leftTrue*rightFalse) + (leftFalse*rightTrue) + (leftFalse*rightFalse);
            }
            else if(str[k] == '|'){
                if(isTrue) ans += (leftTrue*rightFalse) + (leftFalse*rightTrue) + (leftFalse*rightFalse);
                else ans += (leftFalse*rightFalse);
            }
        }

        return dp[isTrue][i][j] = ans;
    }
};


// Scrambled String
class ScrambledString {
    public:
    //Recursive Method
    //T.C - O(2^N)  S.C - O(N)
    bool isScramble(string s1, string s2) {
        if(s1.compare(s2) == 0) return true;//If both strings are equal

        if(s1.length() <= 1) return false;//If length is less than 1(given in ques)

        int n = s1.length();
        int flag = false;
        // Check for every breakpoint(i)
        for(int i=1; i <= n-1; i++){
            //Swapped means check for left of str1 with right of str2 and left of str2 with right of str1
            int swapStr = isScramble(s1.substr(0,i),s2.substr(n-i,i)) && isScramble(s1.substr(i),s2.substr(0,n-i));
            //Not swapped means check for left of str1 with left2 and right of str1 with right of str2
            int notSwapStr = isScramble(s1.substr(0,i),s2.substr(0,i)) && isScramble(s1.substr(i),s2.substr(i));

            if(swapStr || notSwapStr){//Any one case gives scrambled string
                flag = true;
                break;
            }
        }
        return flag;
    }

    //Memoized Method
    //T.C - O(N^2)  S.C - O(N^2)
    unordered_map<string,bool>map;
    bool isScramble(string s1, string s2) {
        string key = s1 + " " + s2;
        if(map.find(key) != map.end()) return map[key];

        if(s1.compare(s2) == 0){
            map[key] = true;//If both strings are equal store in map
            return true;
        } 

        if(s1.length() <= 1){
            map[key] = false;//If length is less than 1(given in ques)
            return false;
        } 

        int n = s1.length();
        bool flag = false;
        for(int i=1; i <= n-1; i++){
            //Swapped means check for left of str with right of str and right of str with left
            int swapStr = isScramble(s1.substr(0,i),s2.substr(n-i,i)) && isScramble(s1.substr(i),s2.substr(0,n-i));
            //Not swapped means check for left of str with left and right of str with right
            int notSwapStr = isScramble(s1.substr(0,i),s2.substr(0,i)) && isScramble(s1.substr(i),s2.substr(i));

            if(swapStr || notSwapStr){//If any one case gives scrambled string
                flag = true;
                break;
            }
        }
        return map[key] = flag;//Store in map for further reference 
    }
};


// Egg Dropping Problem
class EggDropping {
    public:
    //Recursive Method
    //T.C - O(2^N)  S.C - O(N)
    int superEggDrop(int eggs, int floors) {
        if(eggs == 1) return floors;//In worst case we drop the egg from every floor and reach the last floor
        if(floors == 0 || floors == 1) return floors;//Just drop the egg and see if it breaks

        int minAttempts = INT_MAX;
        //Try to drop from every floor
        for(int k = 1; k <= floors; k++){
            //Let's say we drop the egg from curr(k) floor
            int eggBroken = superEggDrop(eggs-1,k-1);//If egg breaks from curr floor then reduce the egg and go to lower floors
            int eggNotBroken = superEggDrop(eggs,floors-k);//If egg doesn't break keep using the egg and go to upper floors
            //Take the max worst case attempts and add 1 because one egg is dropped so 1 attempt is done
            int currAttempt = 1 + max(eggBroken,eggNotBroken);

            minAttempts = min(currAttempt,minAttempts);//Store the min attempts
        }
        return minAttempts;
    }

    //Memoized Method
    //T.C - O(N^2*k) S.C - O(N*k)
    int dp[1001][1001];//memset(dp, -1, sizeof(dp))
    int superEggDrop(int eggs, int floors) {
        if(dp[eggs][floors] != -1) return dp[eggs][floors];//If already computed and stored

        //In worst case we drop the egg from every floor and reach the last floor
        if(eggs == 1 || floors == 0 || floors == 1){
            dp[eggs][floors] = floors;
            return floors;//Just drop the egg and see if it breaks
        }

        int minAttempts = INT_MAX;
        //Try to drop from every floor
        for(int k = 1; k <= floors; k++){
            //Let's say we drop the egg from curr(k) floor
            int eggBroken = superEggDrop(eggs-1,k-1);//If egg breaks from curr floor then reduce the egg and go to lower floors
            int eggNotBroken = superEggDrop(eggs,floors-k);//If egg doesn't break keep using the egg and go to upper floors
            //Take the max worst case attempts and add 1 because one egg is dropped so 1 attempt is done
            int currAttempt = 1 + max(eggBroken,eggNotBroken);

            minAttempts = min(currAttempt,minAttempts);//Store the min attempts
        }
        return dp[eggs][floors] = minAttempts;
    }

    //Memoized + Binary Search Method
    //T.C - O(N*k*logN) S.C - O(N*k)
    int dp[1001][1001];//memset(dp, -1, sizeof(dp))
    int superEggDrop(int eggs, int floors) {
        if(dp[eggs][floors] != -1) return dp[eggs][floors];//If already computed and stored

        //In worst case we drop the egg from every floor and reach the last floor
        if(eggs == 1 || floors == 0 || floors == 1){
            // dp[eggs][floors] = floors;
            return floors;//Just drop the egg and see if it breaks
        }

        int minAttempts = INT_MAX;
        int low = 0;
        int high = floors;
        int currAttempt = 0;
        //Instead of dropping from every floor
        while(low <= high){
            //Try mid floors to drop egg
            int mid = (low + high)/2;
            //Let's say we drop the egg from curr(k) floor
            int eggBroken = superEggDrop(eggs-1,k-1);//If egg breaks from curr floor then reduce the egg and go to lower floors
            int eggNotBroken = superEggDrop(eggs,floors-k);//If egg doesn't break keep using the egg and go to upper floors
            //Take the max worst case attempts and add 1 because one egg is dropped so 1 attempt is done
            currAttempt = 1 + max(eggBroken,eggNotBroken);

            //We need more attempts in worst case so 
            if(eggBroken < eggNotBroken) low = mid + 1;//If not breaking egg has more attempts then go to upper floors
            else high = mid - 1;//If egg broken gives more attempts then go to lower floors

            minAttempts = min(currAttempt,minAttempts);//Store the min attempts
        }
        return dp[eggs][floors] = minAttempts;
    }
};


// Climbing Stairs
class ClimbingStairs {
    //Recursive Method
    //T.C - O(2^N)  S.C - O(1)
    int minSteps(int n){
        if(n == 0 || n == 1 || n == 2) return n;

        return (steps(n-1) + steps(n-2));
    }

    //Dynamic Programming
    //T.C - O(N) S.C - O(N)
    int climbStairs(int n) {
        if(n==1) return 1;//Base case
        int* dp = new int[n+1];//Dp array
        dp[0]= 1;//Initialization
        dp[1]= 1;

        for(int i=2;i<=n;i++){
            dp[i] = dp[i-1] + dp[i-2];//Store the ans for prev steps
        }
        return dp[n];
    }
};


// Min Cost Climbing Stairs
// T.C - O(N)  S.C - O(N)
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    int *dp = new int[n+1];
    dp[0] = cost[0];
    dp[1] = cost[1];
    for(int i = 2; i < n;i++){
        //Add curr stair cost with the prev(min cost) min step
        dp[i] = cost[i] + min(dp[i-1],dp[i-2]);
    }
    return min(dp[n],dp[n-1]);

    //T.C - O(N)  S.C - O(1)
     int n = cost.size();//We'll edit the cost array itself
     for(int i=2;i<n;i++){
         cost[i] = min(cost[i-1],cost[i-2]) + cost[i];
        }
    return min(cost[n-1],cost[n-2]);
}


// Frog Jump
class FrogJump {
    public:
    // Min Cost Frog Jump Energy
    // T.C - O(N)  S.C - O(N)
    int frogJump(int n, vector<int> &heights){
        vector<int>dp(n,0);
        dp[0] = 0;
        for(int i = 1; i < n;i++){
            //Take one step and store energy cost
            int firstStep = dp[i-1] + abs(heights[i] - heights[i-1]);
            int secondStep = INT_MAX;
            if(i > 1) secondStep = dp[i-2] + abs(heights[i] - heights[i-2]);

            dp[i] = min(firstStep, secondStep);//Store min energy cost
        }
        return dp[n-1];
    }

    // Frog Jump Leetcode
    //T.C - O(N*N)  S.C - O(N)
    unordered_map<int, bool> dp;
    bool canCross(vector<int>& stones) {
        int key = pos | k << 11;//Store the key
        
        if (dp.count(key) > 0) return dp[key];//Already the saw the pos
        
        for (int i = pos + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[pos];//Find the gap

            if (gap < k - 1) continue;//Gap is less than prev jump so skip

            if (gap > k + 1) return dp[key] = false;//Gap is greater than prev jump so return false

            if (canCross(stones, i, gap)) return dp[key] = true;
        }
        return dp[key] = (pos == stones.size() - 1);
    }


};


// House Robber
class HouseRobber {
    public:
    // House Robber 1
    // T.C - O(N)  S.C - O(N)
    int houseRobber(vector<int>& nums) {
        if(nums.size()==0) return 0;//No money in house
        
        if(nums.size()==1) return nums[0];//Only 1 house is there so loot it

        if(nums.size()==2) return max(nums[0],nums[1]);//Two houses are there so loot the one with max money(adj can't be looted)
        
        int n = nums.size();
        int dp[n];
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        
        for(int i=2;i<n;i++){
            int robHouse = dp[i] + dp[i-2];//Rob the house take the loot and move two houses(adj looting not allowed)
            int notRobHouse = dp[i-1];//Move to the next house
            dp[i] = max(robHouse,notRobHouse);
        }
        return dp[n-1];
    }

    // House Robber II
    //T.C - O(N)  S.C - O(N)
    int rob(vector<int>& nums) {//Houses are circular in nature
        // edge cases:
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);
        
        // either use first house and can't use last or last and not first:
        vector<int> v1(nums.begin(), nums.end()-1);
        vector<int> v2(nums.begin()+1, nums.end());
        return max(houseRobber(v1), houseRobber(v2));
    }

};


// Ninja Training
class NinjaTraining {
    public:
    // Memoized Method
    // T.C - O(N*12)  S.C - O(N + N*4)
    int fn(int day,int lastTask,vector<vector<int>>&points,vector<vector<int>>&dp){
        //Base case
        if(day == 0){//It's the last day remaining
        int maxi = 0;
        //Traverse the task array
        for(int task=0;task<3;task++){//Only 3 tasks are there
        //Can't perform two tasks in consecutive days
        if(task != lastTask) maxi = max(maxi,points[0][task]);//Take the max points
        }
        return maxi;
        }

        //Already computed and stored
        if(dp[day][lastTask] != -1) return dp[day][lastTask];

        int maxi = 0;
        for(int task = 0;task<3;task++){//Only 3 tasks are there
        if(task != lastTask){
            //Store the points for doing that task on that day and recursively calculate the points for rest days
            int point = points[day][task] + fn(day-1,task,points,dp);
            maxi = max(maxi,point);
        }
        }
        return dp[day][lastTask] = maxi;
    }
    int ninjaTraining(int n, vector<vector<int>> &points){
        //Treat days as index
        vector<vector<int>>dp(n,vector<int>(4,-1));//Dp array
        return fn(n-1,3,points,dp);
    }


    // Dynamic Programming
    // T.C - O(N*12)  S.C - O(N*4)
    int ninjaTraining(int n, vector<vector<int>> &points){
        vector<vector<int>>dp(n,vector<int>(4,0));//Dp array

        //Base cases(0th day)
        dp[0][0] = max(points[0][1],points[0][2]);
        dp[0][1] = max(points[0][0],points[0][2]);
        dp[0][2] = max(points[0][0],points[0][1]);
        dp[0][3] = max(points[0][0],max(points[0][1],points[0][2]));

        for(int day=1;day<n;day++){
            for(int lastTask=0;lastTask<4;lastTask++){
                int dp[day][lastTask] = 0;
                for(int task = 0;task<3;task++){//Only 3 tasks are there
                   if(task != lastTask){
                    //Store the points for doing that task on that day plus the points for rest days
                    int point = points[day][task] + dp[day-1][task];
                    dp[day][lastTask] = max(dp[day][lastTask],point);
                    }
                }
            }
        }
        return dp[n-1][3];
    }
};


// Grid unique paths
class UniquePath {
    public:
    //Recursive Method
    //T.C - O(2^(M*N))  S.C - O(m-1 + n-1)
    int uniquePaths(int m, int n) {
        if(m == 1 && n == 1) return 1;//Count the path

        if(m < 0 || n < 0) return 0;//Not count path
        
        int up = uniquePaths(m-1,n);
        int left = uniquePaths(m,n-1);

        return up + left;//Return sum of all possible paths
    }

    //Dynamic Programming
    //T.C - O(N*M)  S.C - O(N*M)
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int> (n));//Dp array
        
        for(int i = 0; i < m; i++){//Traverse each cell
            for(int j = 0; j < n; j++){
                // if(mat[i][j] == -1) dp[i][j] = 0;//If matrix has obstacles
                if(i == 0 && j == 0) dp[i][j] = 1;//Reached destination
                else {
                    //Go in left dir
                    int leftSide = 0;
                    if(i-1 >= 0) leftSide = dp[i-1][j];//Find paths in left

                    //Go in upward dir
                    int upSide = 0;
                    if(j-1 >= 0) upSide = dp[i][j-1];//Find paths in up
                    
                    dp[i][j] = leftSide + upSide;//Store total paths
                }
            }
        }
        return dp[m-1][n-1];
    }
};


// Minimum Path Sum
// T.C - O(N*M)  S.C - O(N*M)
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> dp(m, vector<int> (n,0));
        
    //Traverse the matrix
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            //Base case - Add the sum to path(0,0 is part of path)
            if(i == 0 && j == 0) dp[i][j] = grid[i][j];
                
            else {                    
                int leftSide = grid[i][j];
                if(i-1 >= 0) leftSide += dp[i-1][j];//Store the path sum if we go left
                else leftSide += 1e9;//Out of bounds
                    
                int upSide = grid[i][j];
                if(j-1 >= 0) upSide += dp[i][j-1]; //Store the path sum if we go up           
                else upSide += 1e9;//Out of bounds
                        
                dp[i][j] = min(leftSide,upSide);//Store the min of the two path sums
            }
        }
    }
    return dp[m-1][n-1];
}


// Dungeon Game
// Recursive Method
// T.C - O(2^N)  S.C - O(N)
int getValRecursive(vector<vector<int>> &mat, int i=0, int j=0,vector<vector<int>>& dp){
    int n = mat.size();
    int m = mat[0].size();
    // Base case : we have crossed the matrix, ie. out of bound
    // if current row crosses then my row is below the princess or 
    // if current column crosses then my column is ahead the column of princess
    // and because we can go only down and right so we wont be able reach princess
    if(i == n || j == m) return 1e9; 
        
	// Base Case : we have reached our destination ie. last cell
    // we reached princess , cheers return this cost;
    if(i == n-1 and j == m-1) return (mat[i][j] <= 0) ? -mat[i][j] + 1 : 1;

    // if we know the answer for this cell then no need to recalculate those, simply return those values 
    if( dp[i][j] != 1e9) return dp[i][j];
        
    // now we must try all possible paths , we ask our right and and down cell
    int IfWeGoRight = getValRecursive(mat , i , j+1);
    int IfWeGoDown = getValRecursive(mat , i+1 , j);
    
    // min of either values and then cost of this cell
    int minHealthRequired =  min(IfWeGoRight , IfWeGoDown) - mat[i][j];
    
    // point 2 as explained 
    dp[i][j] = ( minHealthRequired <= 0 ) ? 1 : minHealthRequired; 
    return dp[i][j];     
}
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    //vector<vector<int> > dp(n + 1, vector<int>(m + 1, 1e9));
    // return getValRecursive(dungeon,dp);
    int n = dungeon.size();
    int m = dungeon[0].size();

    vector<vector<int> > dp(n + 1, vector<int>(m + 1, 1e9));
    dp[n][m - 1] = 1;//Min req health is 1 to travel the grid
    dp[n - 1][m] = 1;
    
    //Move from last grid towards the starting point
    for (int i = n - 1; i >= 0; i--){
        for (int j = m - 1; j >= 0; j--) {
            int goDown = dp[i + 1][j];//Health req to go down
            int goRight = dp[i][j + 1];//Health req to go right
            int need = min(goDown,goRight) - dungeon[i][j];//Store the HP needed
            dp[i][j] = need <= 0 ? 1 : need;// store this value
        }
    }
    return dp[0][0];
}


// Triangle Problem
// T.C - O(N*N)  S.C - O(N*N)
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n,vector<int> (n,0));

    for(int i=n-1;i>=0;i--){
        for(int j=triangle[i].size()-1;j>=0;j--){
            int down = 0;
            if(i+1 < n) down = triangle[i][j] + dp[i+1][j];
            
            int diagonal = 0;
            if(i+1 < n && j+1 < triangle[i+1].size()) diagonal = triangle[i][j] + dp[i+1][j+1];
            
            
            dp[i][j] = min(down,diagonal);
        }
    }
    return dp[0][0];
}


// Wildcard Matching
class WildcardMatch {
    //Recursive Method
    //T.C - O(Exponential)  S.C - O(N+M)
    bool func(int i, int j, string &t, string &s){
        //Base case
        if(i < 0 && j < 0) return true;
        if(i < 0 && j >= 0) return false;
        
        if(j < 0 && i >= 0){
            for(int k=0;k<=i;k++){
                if(t[k] != '*') return false;
            }
            return true;
        }
        
        //if they matched or equal to ?(any 1 char)
        if(t[i] == s[j] || t[i]=='?') return func(i-1,j-1,t,s);
        
        //if They DO NOT match
        if(t[i] == '*'){
            return func(i-1,j,t,s) || func(i,j-1,t,s);
        }
        return false;// (a == b) no   thats why false;
    }
    bool isMatch(string s, string t) {
        return func(t.size()-1,s.size()-1,t,s);
    }

    // Dynamic Programming
    //T.C - O(N*M)  S.C - O(N*M)
    bool isMatch(string s, string t) {
        int m = s.size();
        int n = t.size();
        vector<vector<bool>> dp(n+1, vector<bool> (m+1,0));
        
        dp[0][0] = 1;// base case - 1st cell
        // base case - 2
        for(int j=1;j<=m;j++) dp[0][j] = false;//last row
        // base case - 3
        for(int i=1;i<=n;i++){//last col
            int flag = true;
            for(int k=1;k<=i;k++){
                if(t[k-1] != '*'){
                    flag = false;
                    break;
                }
            }
            dp[i][0] = flag;//found a *
        }
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                //if chars matched or found a ?
                if(t[i-1] == s[j-1] || t[i-1]=='?') dp[i][j] = dp[i-1][j-1];
                
                // if found a *
                else if(t[i-1] == '*') dp[i][j] = dp[i-1][j] || dp[i][j-1];
                
                else dp[i][j] = false;//Chars did not match
            }
        }
        return dp[n][m];
    }
};


// Longest Increasing Subsequence
// Tabulation Method
// T.C - O(N*N)  S.C - O(N*N)
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    //Make  n+1*n+1 dp array. Why n+1? -> we're doing ind+1
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));
        
    //Start from bottom of array
    for(int ind = n-1;ind>=0;ind--){
        //Prev for initial element will be -1
        for(int prev = ind-1;prev>=-1;prev--){
            //Doing prev+1 for shifting coordinate
            int len = 0 + dp[ind+1][prev+1];//We don't pick the num to be part of LIS
            if(prev == -1 || nums[ind] > nums[prev]){//Valid condn. for LIS
                //Pass curr index(ind) as pre idx
                len = max(len,1 + dp[ind+1][ind+1]);//We pick the num to be part of LIS 
            }
            dp[ind][prev] = len;//Store in dp after taking max len
        }
    }
    return dp[0][-1+1];
}
// Binary Search Method
// T.C - O(N*logN)  S.C - O(N)
int lengthOfLIS(vector<int>& nums) {
    vector<int>temp;
    temp.push_back(nums[0]);

    for(int i=1; i<nums.size();i++){//Traverse the vector
        //Incoming num is greater than already existing
        if(nums[i] > temp.back()) temp.push_back(nums[i]);
        //Found a smaller num so overwrite it
        else{
            int idx = lower_bound(temp.begin(), temp.end(),nums[i]) - temp.begin();
            temp[idx] = nums[i];//Overwrite the new num
        }
    }
    return temp.size();//Length of LIS
}


// Word Break
class WordBreak {
 public:
 // Recursive Method
 // T.C - O(2^N)  S.C - O(N)
 bool wordBreak(String s, int curIndex, List<String> wordDict) {
     // Reached the end of str means found the str in dictionary
     if (curIndex == s.length()) return true;
     
     // Ex -> fix 'l' and recur for 'eetcode'
     for (int end = curIndex+1; end <= s.length(); end++) {
         string split = s.substring(curIndex, end);//Split and store the later part of str
         if (wordDict.contains(split)) {//Dictionary has the splitted str(use set to check)
             //Recur and check for rest of the string
             if(recur(s, end, wordDict)) return true;
         }
     }    
     return false;
 }

 // Dynamic dictionary
 // T.C - O(N^3)  S.C - O(N)
 unordered_map<string, bool> dp;
 bool wordBreakHelp(string word, unordered_map<string, bool>& dict){
    //if present in dict
    if(dict.find(word) != dict.end()) return true;
        
    //if present in dp, no need to call 
    if(dp.find(word) != dp.end()) return dp[word];    
    
    for(int i=0; i<word.length(); i++){
        string left = word.substr(0, i+1); //always starts from beginning
        string right = word.substr(i+1); //remaining string till the last letter;
            
        if(dict.find(left) != dict.end()){//Found the left part in dict
            bool res = wordBreakHelp(right, dict); //rest of the string is recursed for right part
                
            if(res == true){
                dp[word] = true; //entire word exists
                return true;
            }
        }
    }
    //if no prefix is found to be matching, word does not exist
    dp[word] = false;
    return false;      
 }
 bool wordBreak(string s, vector<string>& wordDict) {
    unordered_map<string, bool> dict;
    //Push in map which makes it easy to search
    for(string s : wordDict) dict[s] = true;
    return wordBreakHelp(s, dict);
 }
};

// Buy and Sell Stock
class BuySellStock {
    public:
    // At most 2 Transactions
    //Greedy Method
    //T.C - O(N)  S.C - O(1)
    int maxProfit(vector<int>& prices) {
        int minPrice1 = INT_MAX;
        int minPrice2 = INT_MAX;
        int profit1 = 0;
        int profit2 = 0;
        for(int i=0;i<prices.size();i++){
            //Min Price on that day for 1st transaction
            minPrice1 = min(minPrice1,prices[i]);
            profit1 = max(profit1,prices[i] - minPrice1);
            //Min Price on that day for 2nd transaction after 1st profit
            minPrice2 = min(minPrice2,prices[i] - profit1);
            profit2 = max(profit2 , prices[i] - minPrice2);
        }
        return profit2;
    }

    // At most k transactions
    //Dynamic Programming
    //T.C - O(N*k)  S.C - O(2*k)
    int maxProfit(int k, vector<int>& prices) {
        //Now we need to store k min prices and profits instead of 2
        if(k == 0) return 0;
        int minPrice[k];
        int maxProf[k];
        for(int i = 0; i < k; i++){
            minPrice[i] = INT_MAX;
            maxProf[i] = 0;
        }

        for(int i=0;i<prices.size();i++){
            //Min Price on that day for k transactions
            for(int j=0;j<k;j++){
                //Calculate minPrice after the prev transaction
                minPrice[j] = min(minPrice[j],prices[i] - (j > 0 ? maxProf[j-1] : 0));
                maxProf[j] = max(maxProf[j],prices[i] - minPrice[j]);
            }
        }
        return maxProf[k-1];
    }
};


// Paint the Fence
//T.C - O(N)  S.C - O(1)
long long countWays(int n, int k){
    if(n == 0) return 0 ;//No fence is there
    if(n == 1) return k;//For one fence any color can be used

    //In case of two fences
    long long same = k;//Same color on both fence(choose any from k)
    long long diff = (k*(k-1));//Diff color on fences(choose from k and then k-1)

    for(long long i=3;i<=n;i++){
        long long prev = diff;
        diff = ((same+diff)*(k-1));
        same = prev;
    }
    return (same+diff);
}


// Longest Increasing Path in Matrix
// T.C - O(M*N)  S.C - O(M*N)
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
int dfs(vector<vector<int>> &matrix,int i,int j,vector<vector<int>> &dp){
    if(dp[i][j] != -1) return dp[i][j]; // return if result is already calculated
	dp[i][j] = 1;  // minimum path from each cell is always atleast 1

    for(int i=0;i<4;i++){//Check all 4 directions whether curr orange can rot anyone
        int new_i = i + dx[i];
        int new_j = j + dy[j];
        //Cell is in bound and next cell has greater value than curr
        if(x>=0 && y>=0 && x<m && y<n && matrix[x][y] > matrix[i][j]){
            //Store the max while exploring the further path
            // max( current optimal, select current + optimal solution after moves[k] from current cell
            dp[i][j] = max(dp[i][j], 1 + solve(matrix, new_i, new_j,dp));
        }
    }
    return dp[i][j];
}
int longestIncreasingPath(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    int longestPath = 0;
    vector<vector<int>> dp(m, vector<int>(n,-1));//dp memo

    //Go to each cell and calculate the longest path using dfs
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            dp[i][j] = dfs(matrix,i,j,dp);
            longestPath = max(longestPath,dp[i][j]);
        }
    }
    return longestPath;
}


//Minimum Characters For Palindrome
// T.C - O()  S.C - O()
int minCharsPalindrome(string str) {}