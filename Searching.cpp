// Binary Search
// T.C - O(logN)
int binarySearch(int arr[], int size, int target){
    int low = 0;
    int high = size - 1;
    while (low <= high){
        int mid = low + (high - low) / 2;
        if (arr[mid] == target){
            return mid;
        }
        else if (arr[mid] > target){
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return -1;
}


// Order Agnostic Search
// T.C - O(logN)
int orderAgnosticSearch(int arr[], int start, int end, int target){
    // Check if Asc of Desc
    bool isAsc = arr[start] < arr[end];
    while (start <= end){
        int mid = (start + end) / 2;

        if (arr[mid] == target)
            return mid;

        if (isAsc){
            if (arr[mid] < target)
                start = mid + 1;

            else
                end = mid - 1;
        }
        else{
            if (arr[mid] > target)
                start = mid + 1;

            else
                end = mid - 1;
        }
    }
}


// First and Last Occurrence
// T.C - O(logN)
int firstOcc(vector<int> &nums, int target){
    int low = 0, high = nums.size() - 1, res = -1;
    while (low <= high){
        int mid = (low + high) / 2;
        if (nums[mid] > target){
            high = mid - 1;
        }
        else if (nums[mid] < target){
            low = mid + 1;
        }
        else{
            // If element is found
            res = mid; // Store the ans
            high = mid - 1; // Check in left whether
                            // it has occurred previously
        }
    }
    return res;
}
int lastOcc(vector<int> &nums, int target){
    int low = 0, high = nums.size() - 1, res = -1;
    while (low <= high){
        int mid = (low + high) / 2;
        if (nums[mid] > target){
            high = mid - 1;
        }
        else if (nums[mid] < target){
            low = mid + 1;
        }
        else {
            // If element is found
            res = mid; // Store the ans

            low = mid + 1; // Check in right whether
                           // it has occurred after
        }
    }
    return res;
}


// Count Occurrence of an Element
// T.C- O(logN)
return firstOcc - lastOcc + 1


// Times a sorted Array is Rotated
// T.C- O(logN)
int countRotations(int arr[], int size){
    int start = 0;
    int end = size - 1;

    while (start <= end){
        int mid = (start + end) / 2;
        // To avoid negatives-size is added
        int prev = (mid + size - 1) % size;
        int next = (mid + 1) % size;

        if (arr[mid] <= arr[prev] && arr[mid] <= arr[next])
            return mid;
        else if (arr[mid] <= arr[end])
            end = mid - 1;
        else if (arr[mid] >= arr[start])
            start = mid + 1;
    }
}


//Search in Rotated Sorted Array
// T.C - O(logN)
int searchRotatedSortedArray(int arr[],int size, int target){
    int start = 0;
    int end = size - 1;

    while (start <= end){
        int mid = (start + end) >> 1;
       
       if(arr[mid] == target) return mid;
       //In case of duplicates
        // if(nums[low] == nums[mid] && nums[mid] == nums[high]){
        //         low++;
        //         high--;
        //     }

       //If left half is sorted
        if(arr[start] <= arr[mid]){
            //Check whether target exists in range
            if(target>=arr[start] && target<= arr[mid]) end= mid-1;
            else start = mid+1;
        }

        //If right half is sorted
        else{
            if(target>=arr[mid] && target<= arr[end]) start= mid+1;
            else end = mid-1;
        }
        return -1;
    }
}


//Search in Nearly Sorted Array
//T.C - O(logN)
int nearlySortedSearch(int arr[], int size, int target){
    int low = 0;
    int high = size - 1;
    while (low <= high){
        int mid = low + (high - low) / 2;

        if (arr[mid] == target){
            return mid;
        }
        //If element exists at left
         if (mid>=low && arr[mid-1] == target){
            return mid - 1;
        }
        //If element exists at right
         if (mid<=low && arr[mid+1] == target){
            return mid + 1;
        }

        //If element not found at i-1,i,i+1
         if (arr[mid] < target){
            low =  mid + 2;
        }
        else
            high = mid - 2;
    }
    return -1;
}


//Floor and Ceil of an element
//T.C - O(logN)
int findFloor(int arr[], int size, int target){
    int start = 0;
    int end = size - 1;
    int res = -1;

    while (start <= end){
        int mid = start + (end - start) / 2;
        if (arr[mid] == target){
            return mid;
        }
        //Found a smaller element
        else if (arr[mid] < target){
            res = mid;
            //Now search for the greater one
            start = mid + 1;
        }
         else if (arr[mid] > target)
            end = mid - 1;
    }
    return res;
}
int findCeil(int arr[], int size, int target){
    int start = 0;
    int end = size - 1;
    int res = -1;

    while (start <= end){
        int mid = start + (end - start) / 2;
        if (arr[mid] == target){
            return mid;
        }
        //Found a greater element
        else if (arr[mid] > target){
            res = mid;
            //Now search for a lesser one
            end = mid - 1;
        }
         else if (arr[mid] < target)
            start = mid + 1;
    }
    return res;
}


//Next Alphabetical Element
 //T.C - O(logN)
 int nextAlphabet(char arr[], int size, char target){
    int start = 0;
    int end = size - 1;
    char res = -1;

    while (start <= end){
        int mid = start + (end - start) / 2;
        if (arr[mid] > target){
            res = mid;
            //Now search for a lesser one
            end = mid - 1;
        }
         else 
            start = mid + 1;
    }

       if(res==' ') return arr[0];

    return arr[res];
}


//Search in Infinite Sorted Array
//T.C - O(logi), i = pos of element
int searchInfiniteSortedArray(int arr[],int size,int key){
    int left = 0;
    int right = 1;
    //While key is out of range
    while(arr[right] < key){
        left = right;
        right = 2*right;
    }

    return binarySearch(arr,size,left,right,key);
}


//Index of First Occurrence of element in a Sorted Infinite Array
//T.C - O(logN)
int firstOneInfiniteArray(int arr[],int size,int key){
    int left = 0;
    int right = 1;
    //While key is out of range
    while(arr[right] < key){
        left = right;
        right = 2*right;
    }

    return first_occ(arr,size,left,right,key);
}


//Minimum Difference Element in a Sorted Array
//T.C - O(logN)
int minDifferenceElement(int arr[],int size,int key){
     int low = 0;
    int high = size - 1;
    while (low <= high){
        int mid = low + (high - low) / 2;
        if (arr[mid] == target){
            return arr[mid];
        }
        else if (arr[mid] > key){
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    
    if((arr[low] - key) < (key - arr[high])) return arr[low];

    return arr[high];
}


//Find Min in Rotated Sorted Array
//T.C - O(logN)
int findMinInRotatedSortedArray(vector<int>num){
    int start=0,end=num.size()-1;
        
        while (start<end) {
            int mid = (start+end)/2;
            if (num[start]<num[end]) return num[start];
            //In case of duplicates
            // if(nums[left] == nums[mid ] && nums[right] == nums[mid]) left ++, right -- ;
            if (num[mid]>=num[start]) start = mid+1;//Left half is sorted go right half
            else end = mid;
        }
        return num[start];
}


//Binary Search on Unsorted Array

//Peak Element
//T.C - O(logN) && O(N) for finding max of peak elements
int peakElement(int arr[], int size){
    int low = 0, high = size-1;
    while(low < high){//Didn't use low<=high because mid can be the ans itself
    int mid = (low+high)/2;
    if(arr[mid] > arr[mid+1]){
        high = mid; //Because mid can be the ans itself
        }
        else low = mid + 1;
        }
        return arr[low];
}


//Find Maximum in Bitonic Array
//T.C - O(logN)
int findMaxBitonicArray(int arr[],int size, int low, int high){
    //If only one element is present
    if (low == high) 
        return arr[low]; 
        //If there're 2 elements & 1st is greater then the 1st element is max
        if ((high == low + 1) && arr[low] >= arr[high]) 
        return arr[low]; 
        //If second is greater then the second element is max
        if ((high == low + 1) && arr[low] < arr[high])
        return arr[high]; 

 return peakElement(arr,size,low,high)

}


//Search in Bitonic Array
//T.C - O(3logN)
int searchBitonicArray(int arr[],int size,int low, int high,int target){
    int idx = findMaxBitonicArray(arr,size,low,high);

    int asc = binarySearch(arr,size,0,idx-1);
    int desc = binarySearch(arr,size,idx,size-1);

    if(asc && !desc) return asc;
    else return desc;

    return -1;
}


//Search in Row wise And Column wise Sorted Array
//T.C - O(n+m)
int searchSortedMatrix(int arr[][],int size,int key){
    if(size==0) return -1;

    if(key < arr[0][0] || key > arr[size-1][size-1]) return -1;

    int row = 0,col = size-1;
    while(row < size && col >= 0){
        if(arr[row][col] == key) return 1;
        if(arr[row][col] > key) col--;
        else row++;
    }
    return -1;
}


//Allocate Minimum Number of Pages
//T.C - O(NlogN)
bool isAllocationPossible(int arr[], int size,int students,int barrier){
    int allocatedStudents = 0;
    int pages = 0;

    for(int i = 0; i < size ;i++){
        //If min pages are greater than barrier
        if(barrier < arr[i]) return false;
        
        if(pages + arr[i] > barrier){
            //Increase the students count
            allocatedStudents++;
            pages = arr[i];
        }
        else pages += arr[i];
    }

    if(allocatedStudents > students) return false;

    return true;
}
int minPageAllocation(int arr[], int size,int students){
    if(students > size) return -1;

    //For Lower and  Upper Boundaries
      int low = arr[0];
      int high = 0;
      for (int i = 0; i < n; i++){
          low = max(low,arr[i]);
           high += arr[i];
      }

    int res = -1;

    while(low <= high) {
        int mid = (low + high) >> 1;

        //If allocation is possible
        if(isAllocationPossible(arr,size,students,mid)){
            //Go to left to find slightly lower value
            res = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return res;
}


//Aggressive Cows
// T.C - O(NlogN)
bool canPlaceCows(int arr[], int size,int cows,int distance){
   int cowCoordinate = arr[0];
   int cowCount = 1;

   for(int i = 1; i < size; i++){
       if(arr[i] - cowCoordinate >= dist){
           count++;
           cowCoordinate = arr[i];
       }
       if(cows == cowCount) return true;
   } 
   return false;
}
int aggressiveCows(int arr[], int size,int cows){
    if(cows>size) return -1;

    int low = 1;
    int high = arr[size-1] - arr[0];
    int res = -1;

    while(low <= high){
        int mid = (low + high) >> 1;

        if(canPlaceCows(arr,size,cows,mid)){
            res = mid;
            low = mid + 1;
        }
        else high = mid - 1;
    }
    return res;
}


//Painter Partition
//T.C - O(NlogN)
int isPartitionPossible(){
     int allotedPainters = 1;
    int sum = 0;

    for(int i = 0; i < size ;i++){
        sum += arr[i];
        if(sum > limit){
            allocatedStudents++;
            sum = arr[i];
        }
    }

    return allotedPainters;
}
int paintersPartition(int arr[], int size,int painters){
    if(painters > size) return -1;

    //For Upper Bound
      int sum = 0;
      int minBound = 0;
      for (int i = 0; i < n; i++){
          minBound = max(minBound,arr[i]);
          sum += arr[i];
      }

      //For Lower Bound
    int low = minBound;
    int high = sum;

    while(low <= high) {
        int mid = (low + high) >> 1;

        int minPainters = isPartitionPossible(arr,size,painters,mid);
            if(minPainters <= painters){
            //Go to left to find slightly lower value
            high = mid - 1;
            }
        else low = mid + 1;
    }
    return low;
}


//Min Size Subarray Sum(Greater than or equal to target)
//T.C - O(NlogN)
//Check if there's an array of size k which has sum >= target
bool blackBox(int arr[], int size,int target,int k){
    //Sum of 1st k size subarray sum
    int sum = 0;
    for(int i=0;i<k;i++) sum += arr[i];

    //Sliding window
    int maxi = sum;
    int left = 0;
    int right = k-1;
    //Moving the slider
    while(right != size-1){
        sum -= arr[left];
        left++;

        sum += arr[right];
        right++;

        maxi = max(maxi,sum);
    }
    return maxi >= target;
}
int minSubarraySum(int arr[], int size,int target){
    int low = 1;
    int high = size;
    bool ansPossible = false;
    while(low < high){
        int mid = (low+high) >> 1;
        if(blackBox(arr,size,target,mid)){
            ansPossible = true;
            high = mid;
        }
        else low = mid + 1;
    }
    if(ansPossible) return low;
    return 0;
}


//Split Array Largest Sum
//T.C - O(N*log(sum-max+1))
bool blackBox(int arr[], int size,int limit,int m){
    int count = 1;
    int sum = 0;
    for(int i = 0; i < size;++i){
        if(arr[i] > limit) return false;

        if(sum + arr[i] > limit){
            count++;
            sum = arr[i];
        }
        else{
            sum += arr[i];
        }
    }
    return count <= m;
}
int splitArraySum(int arr[], int size,int m){
    int low = *max_element(arr,arr+size);
     int high  = accumulate(arr, arr+size, high);

    int ans = high;
     while(low <= high){
        int mid = (low+high) >> 1;
        if(!blackBox(arr,size,mid,m)){
            low = mid + 1;
        }
        else{
            ans= mid;
            high = mid - 1;
        }
    }
    return ans;
}


//Divide Chocolates
//T.C - O(NlogN)
int canGetMoreThanKSubarrays(int arr[], int size,int limit, int k){
     int count = 0;
    int sum = 0;
    for(int i = 0; i < size;++i){
        sum += arr[i];
        if(sum >= limit){
            count++;
            sum = 0;
        }
    }
    return count >= k;
}
int divideChocolates(int arr[], int size,int k){
    int low = 1;
     int high  = accumulate(arr, arr+size, high);
     int ans = 1;
     while(low <= high){
         int mid = low + (high - low) / 2;
         if(canGetMoreThanKSubarrays(arr,size,mid,k)){
             ans = mid;
             low = mid + 1; //Because we need Max
         }
         else{
             high = mid - 1;
         }
     }
     return ans;
}


//Capacity to ship within 'd' days
//T.C - O(NlogN)
bool canTakeWeight(vector<int> &weights, int capacity,int days){
    int d = 1;
    int totalWeight = 0;

    for(int i = 0; i < weights.size();i++){
        totalWeight += weights[i];
        if(totalWeight > capacity){
            d++;
            totalWeight = weights[i];
        }
    }
    return d <= days;   
}
int shipWithinDays(vector<int>& weights, int days) {
    int low = -1;
    int high = 0;
    for(int i = 0; i < weights.size(); i++){
        low = max(low,weights[i]);
        high += weights[i];
    }    

    if(weights.size() == days) return low;

    int res = -1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(canTakeWeight(weights,mid,days)){
            res = mid
            high = mid - 1;;
        }
        else low = mid + 1;
    }
    return res;
}


//Minimized Maximum of Products Distributed to Any Store
//T.C - O(NlogN)
int minimizedMaximum(int n, vector<int>& quantities) {
    int m=quantities.size(), l=1,r=0;
    for(auto quantity: quantities) r=max(r,quantity);
        
    int mid=0, ans=0;
    while(l<=r){
        mid=(l+r)/2;
        int count=0;
        for(auto quantity: quantities){
            count+=quantity/mid;
            if(quantity%mid) count++;
        }

        if(count<=n) ans=mid,r=mid-1;
        else l=mid+1;
        }
    return ans;
}


//Koko Eating Bananas
//T.C - O(NlogN)
int minEatingSpeed(vector<int>& piles, int h) {
        int m=piles.size(), l=1,r=0;
        for(auto bananas: piles) r=max(r,bananas);
        
        int mid=0, ans=0;
        while(l<=r){
            mid=(l+r)/2;
            int count=0;
            for(auto bananas: piles){
                count+=bananas/mid;
                if(bananas%mid) count++;
            }
            if(count<=h) ans=mid,r=mid-1;
            else l=mid+1;
        }
        return ans;
}


//Nth Root of a Number
//T.C - O(Nlog(M*10^d))
double multiply(int number, int n){
    double res = 1.0;
    for(int i = 1; i<=n; i++) res = res * number;
    return ans;
}
pair<int,int> getNthRoot(int num,int root){
    double low = 1;
    double high = root;
    double eps = 1e-6;

    while((high - low) > eps){
        double mid = (high + low) / 2.0;
        if(multiply(mid,num) < root) low = mid;
        else high = mid;
    }

    return make_pair({low,high});
}


//Single Element in a Sorted Array
//T.C - O(logN)
int singleNonDuplicate(vector<int>& nums) {
    int low = 0, high = nums.size() - 2;
    while(low<=high){
        int mid = (low+high) >> 1;
        if(nums[mid] == nums[mid^1]){//Compare the odd and even instance
        low = mid + 1;
        } 
        else high = mid - 1;
        }
        return nums[low];
}


//Median of 2 sorted Arrays
//T.C - O(log(min(n1,n2)))
double findMedianSortedArrays(vector<int>& nums1,vector<int>& nums2){
    if(nums1.size() > nums2.size()) return findMedianSortedArrays(nums2,nums1);
    int n1 = nums1.size();
    int n2 = nums2.size();
    int low = 0, high = n1;

    while(low <= high){
        int cut1 = (low + high) >> 1;
        int cut2 = (n1 + n2 + 1) / 2 - cut1;

        int left1 = cut1 == 0 ? INT_MIN : nums1[cut1-1];
        int left2 = cut2 == 0 ? INT_MIN : nums2[cut2-1];
        int right1 = cut1 == n1 ? INT_MAX : nums1[cut1];
        int right2 = cut1 == n2 ? INT_MAX : nums1[cut2];

        if(left1 <= right2 && left2 <= right1){
            //For even array size
            if((n1 + n2) % 2 == 0) return (max(left1,left2) + min(right1,right2)) / 2.0;
            //For odd array size
            else return (max(left1,left2));
        }
        else if(left1 > right2) high = cut1 - 1;
        else low = cut1 + 1;
    }
    return 0.0;
}


//K-th element of two sorted Arrays
//T.C - O(log(min(n,m)))
int kthElementSortedArray(int arr1[], int size1,int arr2[], int size2,int k){
    if(size1 > size2) return kthElementSortedArray(arr2,size2,arr1,size1,k);
    int low = max(0,k-size2);
    int high = min(k,size1);

    while(low <= high){
        int cut1 = (low + high) >> 1;//Cut on arr1
        int cut2 = (k - cut1);//Cut for remaining elements

        int left1 = cut1 == 0 ? INT_MIN : arr1[cut1 - 1];
        int left2 = cut2 == 0 ? INT_MIN : arr1[cut2 - 1];
        int right1 = cut1 == size1 ? INT_MAX : arr1[cut1];
        int right2 = cut2 == size2 ? INT_MAX : arr1[cut2];

        if(left1 <= right2 && left2 <= right1) return max(left1,left2);
        else if(left1 > right2) high = cut1 - 1;
        else low = cut + 1;
    }
    return 1;
}


//Minimum Speed to Arrive on Time
//T.C - O(NlogN)
double totalTime(vector<int>&dist, int speed){
    double time = 0.0;
    for(int i = 0; i<dist.size()-1; i++){
            time+= ceil((double)dist[i]/(double)speed); //taking ceil for first n-1 elements because we can take only integer intervals
            }
            time+= ((double)dist[dist.size()-1]/(double)speed); // for the last distance only decimal time needs to be taken to avoid miscalculation
            return time;
}
int minSpeedOnTime(vector<int>& dist, double hour) {
        int lo = 1, hi = 1e7;
        int mid;
        int ans = -1;
        while(lo<=hi){
            mid = (lo+((hi-lo)>>1));
            double time = totalTime(dist,mid);
            if(time<=hour){
                ans = mid;
                hi = mid-1;
            }
            else lo = mid+1;
        }
        return ans;
}


//Ugly Number III
//T.C - O(logN)
lcm(ll a, ll b) {
    return a*b / __gcd(a, b);
}
int nthUglyNumber(int n, int a, int b, int c) {
    int N = n;
    int A = a;
    int B = b;
    int C = c;
    int low = 1;
    int high = 2000000;
    int ans;
    //Increment count with  formula (AUBUC)
    while(low <= high){
        int mid = (low + high) / 2;
        int count = 0;
        count += mid/A;
        count += mid/B;
        count += mid/C;
        count -= mid/lcm(A,B);
        count -= mid/lcm(B,C);
        count -= mid/lcm(C,A);
        count += mid/lcm(A,lcm(B,C));

        if(count >= N){
            ans = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return ans;
}


//Equilibrium Index
//T.C - O(N)
int equilibrium(int arr[], int n){
    int sum = 0; // initialize sum of whole array
    int leftsum = 0; // initialize leftsum
 
     for (int i = 0; i < n; ++i) sum += arr[i];
     
     for (int i = 0; i < n; ++i){
         sum -= arr[i]; // sum is now right sum for index i
        if (leftsum == sum) return i;
        leftsum += arr[i];
    }
    return -1;
}


// Search insert position of K in a sorted array
// T.C - O(logN)  S.C - O(1)
int insertPosK(int arr[], int n, int K){
    int start = 0;
    int end = n - 1;
 
    while (start <= end) {
        int mid = (start + end) / 2;
 
        // If K is found
        if (arr[mid] == K) return mid;
 
        else if (arr[mid] < K) start = mid + 1;
 
        else end = mid - 1;
    }
 
    // Didn'y find the element but inserting here will keep array sorted
    return end + 1;
}


// Binary Search in forest
// T.C - O(NlogN)  S.C - O(1)
int woodCollected(int height[],int n,int cut){
    int sum = 0;
    for(int i=n-1;i>=0;i--){
        if(height[i] - cut < 0) break;
        sum += (height[i] - cut);
    }
    return sum;
}
int collectKWood(int height[], int n, int k){
    sort(arr,arr+n);
    int low = 0;
    int high = height[n-1];//We can cut upto size of max tree

    while(low <= high){
        int mid = low + (high - low) / 2;

        //The amount of wood collected  when cut is made at the mid
        int collected = woodCollected(height,n,mid);

        if(collected == k) return mid;//Currently collected wood is enough
        //If it's more than req amt then the cut needs to be made at a
        // height higher than the current height
        if(collected > k) low = mid + 1;
        else high = mid -1;
    } 
    return -1;
}


//Minimize maximum array element possible by at most K splits on the given array
// T.C - O(NlogM) where M is max element  S.C - O(1)
int canReduceToMidByKSplit(int arr[],int N,int  id,int K){
    int count = 0;
    for(int i=0;i<N;i++){
        count += (arr[i]-1)/mid;//arr[i] can be split into count parts by mid
    }
    return count <= K;//can reduce to mid 
}
int minimumMaximum(int arr[], int N, int K){
    int lo = 1;
    int hi = *max_element(A, A + N);
 
    while (lo < hi) {
         int mid = (lo + hi) / 2;
 
        //If all elements can be reduced to at most
        // mid by at most K splits
        if (canReduceToMidByKSplit(A, N, mid, K)) {//Kya sbko mid bna skte h K split krke
            //Jb mid tk kr skte h to usse km tk bhi kr skte h
             hi = mid;//mid itself can be the ans
        }
         else lo = mid + 1;
    }
    return hi;
}


// Matrix Median
// T.C - O(32*N*logM)  S.C - O(1)
int countSmallerThanMid(vector<int>&row,int mid){
    int l = 0;
    int h = row.size();
    //Row are sorted so if we find mid in row,left side will have all smaller elements
    while(l <= h){
        int middle = (l + h) >> 1;
        if(row[middle] <= mid){
            l = middle + 1;
        }
        else{
            h = middle - 1;
        }
    }
    return l;
}
int findMedian(vector<vector<int>>&arr) {
    int low = 1;//Search space is 1 to 10^9
    int high = 1e9;

    int row = arr.size();
    int col = arr[0].size();

    while(low <= high) {
        int mid = (low + high) >> 1;//Calculate the mid
        int count = 0;
        //Count elements smaller than equal to mid in each row;
        for(int i = 0; i < row;i++) count += countSmallerThanMid(arr[i],mid);

        //Count is less than half the elements in matrix
        if(count <= (n*m)/2) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}
