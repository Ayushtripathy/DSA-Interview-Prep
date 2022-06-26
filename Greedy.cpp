//Greedy Problems

//Job Sequencing Problem
//T.C - O(NlogN + N*M) S.C - O(M) (Deadline - M)
static bool comparison(Job a,Job b){
    return (a.profit > b.profit);
}
pair<int,int> JobSequencing(Job arr[],int n){
    sort(arr,arr+n,comparison);//Sort the array acc to profit
    int maxDeadline = arr[0].dead;//Need max deadline to make array
    for(int i=1;i<n;i++) maxDeadline = max(maxDeadline,arr[i].dead);
    
    int slot[maxDeadline+1] = {-1};//Initially each slot is free
    int countJobs = 0,jobProfit = 0;

    for(int i=0;i<n;i++){
        for(int j = arr[i].dead;j>0;j--){//traverse the deadline array from ith deadline to 0
        if(slot[j] == -1){//Free slot is found
        slot[j] = i;
        countJobs++;
        jobProfit += arr[i].profit;
        break;
        }
        }
    }
    return make_pair(jobProfit, countJobs);
}


//Fractional Knapsack Problem
//T.C - O(NlogN + N) S.C - O(1)
bool compare(Item a,Item b) {
    double r1 = (double)a.value/(double)a.weight;
    double r2 = (double)b.value/(double)b.weight;
    return r1 > r2;
}
double fractionalKnapsack(Item arr[],int size,int W){
    sort(arr,arr+size,comp);//Sort acc to value/weight
    int curWeight = 0;
    double finalValue = 0.0;

    for(int i=0;i<size;i++){
        if(curWeight + arr[i].weight <= W){//There is space in bag
        curWeight += arr[i].weight;//Add item to bag
        finalValue += arr[i].value;//Store profit
        }
        else{//No whole item can be added
        int remainingWt = W - curWeight;
        finalValue += (arr[i].value/ (double)arr[i].weight) * (double)remainingWt;
        break;
        }
    }
    return finalValue;
}


//N Meetings in a room(N Activities)
//T.C - O(NlogN + N + N) S.C - O(N)
struct Meeting{
    int start;
    int end;
    int pos;
};
static bool comparator(struct Meeting a, struct Meeting b){
    if(a.end < b.end) return true; //a ends before b
    else if(a.end > b.end) return false;
    else if(a.pos < b.pos) return true;//If both have same time
    return false;
}
vector<int> maxMeetings(int start[],int end[],int n){
    struct Meeting meet[n];//Create custom data structure
    for(int i=0;i<n;i++){
        meet[i].start = start[i];
        meet[i].end = end[i];
        meet[i].pos = i+1;
    }

    sort(meet,meet+n,comparator);//Sort based on ending time
    vector<int>ans;
    int endLimit = meet[0].end;//Initial meeting end
    ans.push_back(meet[0].pos);

    for(int i=1;i<n;i++){
        if(meet[i].start > endLimit){//If new meeting start after prev ends
            endLimit = meet[i].end;//Store end time of curr meeting
            ans.push_back(meet[i].pos);
        }
    }
    return ans;
}


//Find minimum number of coins that make a given value
//T.C - O(V) S.C - O(1)
vector<int> minCoinsChange(int value){
    int coins[] = {1,2,5,10,20,50,100,500,1000};
    int n = 9;
    vector<int>ans;
    for(int i = n;i>=0;i--){
        while(value >= coins[i]){
            value -= coins[i];
            ans.push_back(coins[i]);
        }
    }
    return ans;
}


//Minimum Platforms Required
//T.C - O(2NlogN + 2N) S.C - O(1)
int minimumPlatforms(int arr[],int dept[],int N){
    sort(arr,arr+N);
    sort(dept,dept+N);
    int platforms = 1;//At least one train has to be there
    int maxPlat = 1;
    int i = 1;j = 0;

    while(i < n && j < n){
        if(arr[i] <= dept[j]){//Train arrives before the prev departs
            platforms++;//Increase platforms
            i++;
        }
        else if(arr[i] > dept[j]){//Train arrives after the prev departs
        platforms--;//Decrease platforms
        j++;
        }
        maxPlat = max(maxPlat,platforms);
    }
    return maxPlat;
}


//Optimal Pattern Merge
//T.C - O(N) S.C - O(N)
int optimalMerge(int arr[],int size){
    sort(arr,arr+size);
    priority_queue<int,vector<int>,greater<int>> minHeap;
    for(int i=0;i<size;i++) minHeap.push(arr[i]);

    int minCost = 0;
    while(minHeap.size() > 1){
        int e1 = minHeap.top();
        minHeap.pop();
        int e2 = minHeap.top();
        minHeap.pop();

        minCost += e1 + e2;
        minHeap.push(e1 + e2);
    }
    return minCost;
}


//Maximum and Minimum Array Difference
//T.C - O(NlogN + N) S.C - O(1)
pair<int,int> maxMinDiff(int arr[],int size){
    sort(arr,arr+size);
    int maxDiff = 0;
    int minDiff = 0;
    for(int i=0;i<size/2;++i){
        maxDiff += (arr[i+size/2] - arr[i]);//Diff of max and min nodes to maximise
        minDiff += (arr[2*i+1] - arr[2*i]);//Diff of adjacent nodes to minimise
    }
    return make_pair(maxDiff,minDiff);
}


// Best Time to Buy and Sell Stock(N transactions)
//T.C - O(N) S.C - O(1)
int stockProblem(int arr[],int size){
    int maxProfit = 0;
    for(int i=1;i<size;i++){
        if(arr[i] > arr[i-1]) maxProfit = arr[i] - arr[i-1];
    }
    return maxProfit;
}


// Chocolate Distribution Problem
//T.C - O(NlogN + N) S.C - O(1)
int findMinDiffChocolate(vector<int>choco,int students){
    int minDiff = INT_MAX;
    sort(choco.begin(),choco.end());
    //Since there are n packets, and m children
    //Number of maximum set possible will be n-m.
    for(int i=0;i<choco.size() - students;i++){
        maxChocolate = choco[i+students-1];
        minChocolate = choco[i];

        int gap = maxChocolate - minChocolate;
        minDiff = min(minDiff,gap);
    }
    return minDiff;
}


// Maximize Toys Count
//T.C - O(NlogN + N) S.C - O(1)
int toyCount(int arr[],int N,int K){
    sort(arr,arr+N);
    int count = 0;
    int sum = 0;

    for(int i=0;i<N;i++){
        if(arr[i] + sum <= K){//We have money to buy the toy
            sum += arr[i];
            count++;
        }
    }
    return count;
}


// First circular tour to visit all Petrol Pumps
//T.C - O(N) S.C - O(1)
int circularTour(petrolPump p[],int n){
    int deficit = 0;
    int reservePetrol = 0;
    int start = 0;
    for(int i=0;i<n;i++){
        reservePetrol += p[i].petrol - p[i].distance;
        if(reservePetrol < 0){ //Can't reach the next pump from here
        deficit += reservePetrol;//Store the deficit petrol amount
        start = i + 1;//Jump to pump next to the current(failure) one
        reservePetrol = 0;//Start from new petrol pump
        }
    }
    if(deficit + reservePetrol >= 0) return start;//Circular tour is possible
    else return -1;
}


// Shop in Candy Store
//T.C - O(NlogN ) S.C - O(1)
pair<int,int> findMinMaxCandies(int arr[],int n,int k){
    int minCost = 0;
    int maxCost = 0;

    sort(arr,arr+n);
    for(int i=0;i<n;i++){
        minCost += arr[i];//Buying the candy with min amt so add the cost
        n = n - k;//Remove k candies from n as every purchase gives k candies for free
    }
    
    int index = 0;//Move idx from front when taking candies
    for(int i=n - 1;i>index;i--){
        maxCost += arr[i];//Buy the candy with max amt
        index = index + k;//Remove k candies from start as every purchase gives k candies for free
    }
    return make_pair(minCost,maxCost);
}


// Minimize the heights
//T.C - O(NlogN + N) S.C - O(1)
int getMinDiffHeight(int arr[],int n,int k){
    sort(arr,arr+n);
    int minHeight = arr[0];
    int maxHeight = arr[n-1];
    int ans = maxHeight - minHeight;
    // Ex. a c b d sorted array
    // d is max and a is min
    // add k to a and subtract k from d
    // in case of adj elements increase c and decrease d


    for(int i = 1; i < n; i++){
        maxHeight = max((arr[i-1] + k),(arr[n-1] - k));//max from c and d
        minHeight = min((arr[i] - k),(arr[0] + k));//min from b and a

        ans = min(ans,(maxHeight - minHeight));
    }
    return ans;
}


// Minimize the sum of product
//T.C - O(2NlogN + N) S.C - O(1)
long long int minValue(int a[], int b[], int n){
    //Sort both the arrays and multiply smallest of a to largest of b
    sort(a,a+n);
    sort(b,b+n);

    long long int res = 0;
    for(int i = 0; i < n; i++){
        res += (a[i] * b[n-i-1]);
    }
    return res;
}


// Largest number possible
//T.C - O(d) S.C - O(d)
vector<int>largestDigitArray(int sum,int digits){
    vector<int> ans;
    if(sum == 0){
        if(digits == 1) ans.push_back(0);
        else return ans;
    }
    if(sum > 9*digits) return ans;//Sum is greater than max possible sum of digits

    for(int i=0;i<digits;i++){
        if(sum >= 9){//Fill 9 to make largest digit 
            ans.push_back(9);
            sum -= 9;
        }
        else{
            ans.push_back(sum);
            sum = 0;
        }
    }
    return ans;
}


// Jumping Game I
//T.C - O(N) S.C - O(1)
bool canJump(vector<int>nums){
    int lastIndex = nums.size() - 1;
    for(int i = nums.size() - 1; i >= 0; i--){
        //i is curr pos and nums[i] is distance that i can jump from that pos 
        //if we can reach to end from that index then make it the last index
        //and check whether we can reach that or not
        if(i + nums[i] >= lastIndex) lastIndex = i;
    }
    return lastIndex == 0;//lastIndex gets 0 only if we can reach the end
}


// Jumping Game II
//T.C - O(N) S.C - O(1)
int countJumps(vector<int>& nums) {
    int jump = 0;
    int i = 0;
    int end = nums.size()-1;
    while(i < nums.size() && end != 0){
        if(nums[i] + i >= end){//If we can reach end from that idx
            end = i;//Make that index the end
            i=0;//reset i and now figure out how to reach end
            jump++;
            }
            else i++;//Can't be reached from that idx
        }
    return jump;
}


// Coin Piles
//T.C - O(2N) S.C - O(1)
int minimumCoins(int arr[],int n,int k){
    int count = 0;
    int minVal = *min_element(arr,arr+n);//find min element

    for(int i = 0; i < n; i++){
        int diff = arr[i] - minVal;
        // If diff between the current pile and the min  pile is greater than k
        if(diff > k) count += (diff - k);
    }
    return count;
}


// Page Faults in LRU
// T.C - O(N*C) S.C - O(C)
int pageFaults(int pages[],int n,int capacity){
    int pageFault = 0;
    vector<int>v;//To store elements in size of cap
    for(int i=0;i<=n-1;++i){
        //Find if the curr element is already present in memory
        auto it = find(v.begin(),v.end(),pages[i]);
        if(it == v.end()){//If element is not present in memory
        //If memory is full then remove the first element from memory as its LRU
        if(v.size() == capacity) v.erase(v.begin());
        v.push_back(pages[i]);//Add recent to memory
        pageFault++;
        }
        else{
            v.erase(it);//Remove the element from memory
            v.push_back(pages[i]);//Add it again to make it MRU
        }
    }
    return pageFault;
}


// Police and Thieves
//T.C - O(N) S.C - O(N)
int catchThieves(char arr[], int n, int k){
    int maxThief = 0;
    vector<int>police;
    vector<int>thief;

    for(int i=0; i<n; i++){//Store the indices of police and thieves
        if(arr[i] == 'P') police.push_back(i);
        else if(arr[i] == 'T') thief.push_back(i);
    }

    int policeIndex = 0 , thiefIndex = 0;//Curr pos of police and thief
    while(thiefIndex < thief.size() && policeIndex < police.size()){
        if(abs(thief[thiefIndex] - police[policeIndex]) <= k){//Can be caught
            thiefIndex++;//move to the next thief as a thief can't get caught more than once
            policeIndex++;
            maxThief++;
        }
        else if(thief[thiefIndex] < police[policeIndex]){
            //thief is far away so check for next thief
            thiefIndex++;
        }
        else policeIndex++;//Police is far away find another one
    }
    return maxThief;
}


// Minimum Number of Taps to Open to Water a Garden
// T.C - O(N*N)  S.C - O(1)
int minTaps(int n, vector<int>& ranges) {
    //As i tap can go from i+ranges[i] to i-ranges[i]
    int minRange = 0;
    int maxRange = 0;
    int minOpenTap = 0;
    int index = 0;

    while(maxRange < n){//In range
    //This loop gives the range of tap that satisfies the cond.
       for(int i=index;i<ranges.size();i++){
           //Store the ranges of the taps from left to right
           if((i - ranges[i]) <= minRange && (i + ranges[i]) > maxRange){
               maxRange = i + ranges[i];
               index = i;
           }
           if(minRange == maxRange) return -1;
           minOpenTap++;//Found one tap

           minRange = maxRange;//Now max range is min for next slot range
       }
    }
    return minOpenTap;
}