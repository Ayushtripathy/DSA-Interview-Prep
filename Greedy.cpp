//Greedy Problems

//Job Sequencing Problem
//T.C - O(NlogN + N*M) S.C - O(M) (Deadline - M)
bool comparison(Job a,Job b){
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
bool comparator(struct Meeting a, struct Meeting b){
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
    int platforms = 1;
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
        if(platforms > maxPlat) maxPlat = platforms;
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
    returm make_pair(maxDiff,minDiff);
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