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
        return dp[n];//If we have already saved the valuethen return
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
    // 2s1= diff + sum of array
    // s1= (diff + sum of array)/2;
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