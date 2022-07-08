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


// Maximum Sum Subarray(Kadane's Algo)
// T.C - O(N)  S.C - O(1)
int maxSubArray(vector<int>& nums) {
    int csum = nums[0];//Let the first num be max sum subarray
    int osum = nums[0];
        
    for(int i=1;i<nums.size();i++){
        if(csum >= 0) csum += nums[i];//If csum is worth it
        else csum = nums[i];//Else create a new csum
        //Store he max sum
        osum = max(csum,osum);
    }
    return osum;
}


// Sort Colors(sort 0 1 2)
// T.C - O(N)  S.C - O(1)
void sortColors(vector<int>& nums) {
    int low = 0;
    int mid = 0;
    int high = nums.size() - 1;

    while (mid <= h){
        //Swap to push 0 to left side(sorted side)
        if (nums[mid] == 0) swap(nums[mid++], nums[l++]);
        else if (nums[mid] == 1) mid++;
        //IN this case mid is not moved because we're not sure it's still sorted
        else  swap(nums[mid], nums[h--]);
    }
}


// Next Permutation
//T.C - O(3N)  S.C - O(1)
void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int idx1, idx2;

    //1. Traverse from back and find idx such that
    for(idx1=n-2;idx1>=0;idx1--){
        //nums[i] > num[i-1] Breakpoint idx1
        if(nums[idx1] < nums[idx1+1]) break;
    }

    // No breakpoint found
    if(idx1 < 0) reverse(nums.begin(),nums.end());
    
    //2. Now find another idx2 such that
    else {
        for(idx2=n-1;idx2>idx1;idx2--){
            if(nums[idx2] > nums[idx1]) break;
        }
        swap(nums[idx1],nums[idx2]);
        reverse(nums.begin() + idx1 + 1,nums.end());
    }
}


// Pascal's Triangle
// T.C - O(N)  S.C - O(1)
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> pascal;
    //Traverse given amt of rows
	for (int i = 0; i < numRows; i++) {
		vector<int> row(i + 1, 1);//Create the row array with initial value 1
        //j = 0 and j = i have 1 value
		for (int j = 1; j < i; j++) {//Traverse the row
        //take upper and upper left value sum
			row[j] = pascal[i - 1][j] + pascal[i - 1][j - 1];
		}
		pascal.push_back(row);
	}
	return pascal;
}


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


// Merge Overlapping Intervals
// T.C - O(NlogN + N)  S.C - O(1)
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>>mergeIntervals;

    if(intervals.size() == 0) return mergeIntervals;//Base case

    sort(intervals.begin(), intervals.end());//Sort

    vector<int>temp = intervals[0];//Store the 1st interval
    for(auto interval : intervals) {//Traverse each interval
        //If intervals are merged
        if(temp[1] >= interval[0]) temp[1] = max(temp[1], interval[1]);
        else {//Not merged
            mergeIntervals.push_back(temp);
            temp = interval;
        }
    }
    mergeIntervals.push_back(temp);//For the last interval
    return mergeIntervals;
}


// Rotate an array
// T.C - O(2N)  S.C - O(1)
void rotate(vector<int>& nums, int k) {
    k %= nums.size();
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin()+k);
    reverse(nums.begin()+k, nums.end());
}


// Find missing and repeating
// T.C - O(2N)  S.C - O(N)
vector<int> find_missing_repeating(vector<int> nums){
    int n = nums.size() + 1;
    vector<int> hash(n, 0);
    vector<int> ans;

    for(int i=0;i<n-1;i++) hash[nums[i]]++;

    for (int i=1;i<=nums.size();i++){
        if (hash[i] == 0 || hash[i] > 1) ans.push_back(i);
    }
    return ans;
}


// Merge Two sorted arrays
// T.C - O(N+M)  S.C - O(N+M)
vector<int> merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> v;
    int i = 0,j = 0;
    while(i < m && j < n){
        if(nums1[i] > nums2[j]) v.push_back(nums2[j++]);
        else if(nums1[i] <= nums2[j]) v.push_back(nums1[i++]);
    }
        
    while(i < m) v.push_back(nums1[i++]);  
    while(j < n) v.push_back(nums2[k]);

    return v;
}


// Triplet Sum to value
// T.C - O(N^2 + NlogN)  S.C - O(1)
void find3Numbers(int arr[], int size, int target){
    sort(arr,arr+size);
    //Upto size -2 because we need at least 3 values
    for(int i=0;i<size-2;i++){
        int left = i+1;
        int right = size-1;
        while(left < right){
            if(arr[i] + arr[left] + arr[right] == sum){
                cout<<arr[i]<<" "<<arr[left]<<" "<<arr[right]<<endl;
            }
            else if(arr[i] + arr[left] + arr[right] < sum) left++;
            else right--;
        }
    }
}


// Count inversions
// T.C - O(NlogN)  S.C - O(N)
int mergeArray(int arr[],int temp[],int left,int mid,int right){
    int i = left;
    int j = mid;
    int k = left;//For the new array idx
    int invCount = 0;

    //What we usually do in merge sort
    while((i <= mid-1) && (j <= right)){
        if(arr[i] <= arr[j]) temp[k++] = arr[i++];
        else{
            temp[k++] = arr[j++];
            // Only different step(i to mid all wil form pairs)
            invCount += mid - i;//Once sorted,the nxt elements will also be part of ans
        } 
    }

    //Merge the remaining elements and restore to original array
    while(i <= mid - 1) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];
    for(i=left; i <= right;i++) arr[i] = temp[i];

    return invCount;
}
int mergeSort(int arr[],int temp[],int left,int right){
    int invCount = 0;

    if(right > left){
        int mid = (right + left) / 2;///Find mid just like merge sort
        //Store the inversion count in recursive step for left and right side
        invCount += mergeSort(arr,temp,left,mid);
        invCount += mergeSort(arr,temp,mid+1,right);

        //Store the inversion counts in merge step
        invCount += mergeArray(arr,temp,left,mid+1,right);
    }
}
int countInversions(int arr[], int n){
    int temp[n];
    return mergeSort(arr,temp,0,n-1);
}


// Implement Pow function
// T.C - O(logN)  S.C - O(1)
double myPow(double x, int n) {
    double res = 1;
    while (n) {//Power exists
        if (n % 2) res = n > 0 ? res * x : res / x;
        x = x * x;//Square the num
        n /= 2;//Reduce the power
    }
    return res;
}


// Majority Element (n/2,n/3,n/k)
// Brute force
// T.C - O(N)  S.C - O(N)
int majorityElement(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> map;
        
    for(int i=0;i<n;i++){
        map[nums[i]]++;//Push in map
        //If count of that num is more than n/2
        if(map[nums[i]] > n/2)  return nums[i];
    }
    return 0;
}
// Boyer-Moore Voting Algo
//T.C - O(2N)  S.C - O(1)
vector<int> majorityElement(vector<int>& nums) {
    int size = nums.size();
    int num1 = -1, num2 = -1, count1 = 0, count2 = 0;

    for (int i = 0; i < size; i++){
        //Keep the counts of two leading nums
        if (nums[i] == num1) count1++;
        else if (nums[i] == num2) count2++;
        else if (count1 == 0){//New num gets majority
            num1 = nums[i];
            count1 = 1;
        }
        else if (count2 == 0){//New num gets majority
            num2 = nums[i];
            count2 = 1;
        }
        else{//New num reduces the leading nums majority
            count1--;
            count2--;
        }
    }
    
    vector<int> ans;
    count1 = count2 = 0;//Store count of majority nums
    for (i = 0; i < size; i++){
        if (nums[i] == num1) count1++;
        else if (nums[i] == num2) count2++;
    }
    //If condition is satisfied
    if (count1 > size/3) ans.push_back(num1);
    if (count2 > size/3) ans.push_back(num2);
    return ans;
}


//Equilibrium Index
//T.C - O(N)
int equilibrium(int arr[], int n){
    int sum = 0; // initialize sum of whole array
    int leftSum = 0; // initialize leftSum
 
     for (int i = 0; i < n; ++i) sum += arr[i];
     
     for (int i = 0; i < n; ++i){
         sum -= arr[i]; // sum is now right sum for index i
        if (leftSum == sum) return i;
        leftSum += arr[i];
    }
    return -1;
}