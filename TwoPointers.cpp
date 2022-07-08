// Pair with Target Sum
// T.C - O(NlogN)  S.C - O(1)
pair<int,int> pairSum(vector<int>&nums,int target){
    sort(nums.begin(),nums.end());
    int i = 0;
    int j = nums.size()-1;
    while(i<j){
        if(nums[i] + nums[j] == target) return {nums[i],nums[j]};
        else if(nums[i] + nums[j] < target) i++;
        else j--;
    }
    return -1;
}


// Dutch National Flag Problem
//T.C - O(N)  S.C - O(1)
void sortColors(vector<int>& nums) {
    int l= 0 , mid = 0, h = nums.size() - 1;
    while (mid <= h){
        //If we encounter a 0, we know that it will be on the low end of the array so swap
        if (nums[mid] == 0) swap(nums[mid++], nums[l++]);
        else if (nums[mid] == 1) mid++;//Just increment mid and do nothing
        //if we encounter a 2, we know it will be on the high end of the array
        else  swap(nums[mid], nums[h--]);
    }
}


// Remove Duplicates
//T.C - O(N)  S.C - O(1)
int removeDuplicates(vector<int>& nums) {
    // if(nums.size() == 0) return 0;
    int left = 0;
    for(int right = 1; right< nums.size(); right++){
        //Found a different element
        if(nums[left] != nums[right]) left++;
        //Replace the diff element
        nums[left] = nums[right];
    }
    return left+1;
}


// Triplet Sum to Zero
//T.C - O(N^2 + NlogN)  S.C - O(1)
vector<vector<int>> threeSum(vector<int>& nums) {
    //Brute force - Run three loops and check if sum  is 0,Time O(N^3logN) Space O(Triplets)
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;

    //We need at least 3 elements so run loop till 3rd last guy
    for(int i=0;i<nums.size()-2;i++){
        //Its the 1st element or its not a duplicate
        if(i == 0 || (i > 0 && nums[i] != nums[i-1])){
            //Do the 2 pointer approach
            int low = i+1;//b
            int high = nums.size() - 1;//c
            int sum = 0 - nums[i];//-a
            //Eqn. is  b+c = -a
            while(low < high){
                //Found a triplet
                if(nums[low]  + nums[high] == sum){
                    res.push_back({nums[i] , nums[low] , nums[high]});
                    //Now move low and high to a non-duplicate value
                    while(low < high && nums[low] == nums[low+1]) low++;
                    while(low < high && nums[high] == nums[high-1]) high--;

                    low++;
                    high--;
                }
                else if(nums[low] + nums[high] < sum) low++;//Increase the value
                else high--;//Decrease the value
            }
        }
    }
    return ans;
}


// Four Sum Pairs Problem
//T.C - O(N^2 + NlogN)  S.C - O(1)
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> result;
	int n = nums.size();
	if (n < 4) return result;

	sort(nums.begin(), nums.end());
	for (int i = 0; i < n-3; ++i) {
		/* Conditions for pruning */
		// target too small, no point in continuing
		if (target <= 0 and nums[i] > 0) break;
		// nums[i] has become too large, no point in continuing
		if ((long long)(nums[i] + nums[i+1] + nums[i+2] + nums[i+3]) > (long long)target) break;
		// nums[i] is so small, even the largest elements cannot help reach the sum
		if ((long long)(nums[i] + nums[n-3] + nums[n-2] + nums[n-1]) < (long long)target) continue; 
		 // skip duplicates
		if (i > 0 and nums[i] == nums[i-1]) continue;

		/* Now explore further */
		for (int j = i+1; j < n - 2; ++j) {
			/* Some more pruning */
			// nums[j] has become too large, no point in continuing
			if ((long long)(nums[i] + nums[j] + nums[j+1] + nums[j+2]) > target) break;
			// nums[j] is so small, even the largest elements cannot help reach the sum
			if ((long long)(nums[i] + nums[j] + nums[n-2] + nums[n-1]) < target) continue; 
			if (j > i+1 and nums[j] == nums[j-1]) continue; // skip duplicates

			/* Explore the solution space */
			int left = j+1, right = n-1;
			while (left < right) {
				long long sum = nums[i] + nums[j] + nums[left] + nums[right];
				if (sum == target) {
					result.push_back({nums[i], nums[j], nums[left], nums[right]});
					int last_left = nums[left], last_right = nums[right];
					while (left < right and nums[left] == last_left) ++left;
					while (left < right and nums[right] == last_right) --right;
				}
                else if (sum < target) ++left;
				else --right;
			}
		}
	}
	return result;
}


// Trapping Rain water
// Brute force
// T.C - O(N^2)  S.C - O(1)
int maxWater(int arr[], int n){
    // To store the maximum water that can be stored
    int res = 0;
     
    // For every element of the array
    for (int i = 1; i < n-1; i++) {
        // Find the maximum element on its left
        int left = arr[i];
        for (int j=0; j<i; j++) left = max(left, arr[j]);
         
        // Find the maximum element on its right  
        int right = arr[i];
        for (int j=i+1; j<n; j++) right = max(right, arr[j]);
        
       // Update the maximum water   
       res = res + (min(left, right) - arr[i]);  
    }
    return res;
}
// Optimized Solution
// T.C - O(N)  S.C - O(1)
int trappingWater(vector<int>& height) {
    int left = 0, right = height.size()-1;
    int leftMax = 0, rightMax = 0;
    int res = 0;
    while(left<=right){
        //If the height of right building is greater
        if(height[left]<=height[right]){
            //If the curr height at left is greater than prev max height at left
            if(height[left] > leftMax) leftMax = height[left];//Update the max height at left
            else res += leftMax - height[left];//Else store the water amount
            left++;//Move to next building to right
        }
        else{ //If the height of left building is greater
            if(height[right] > rightMax) rightMax = height[right];
            else res += rightMax - height[right];//Else store the water amount
            right--;//Move to next building to left
        }
    }
    return res;
}


// Triplet Sum Close to Target
//T.C - O(N^2 + NlogN)  S.C - O(1)
int threeSumClosest(vector<int>& nums, int target) {
    if(nums.size() < 3) return 0;//Need at least 3 elements
    int closest = nums[0]+nums[1]+nums[2];//Initial closest sum to target
    sort(nums.begin(), nums.end());//Sort the array

    for(int first = 0 ; first < nums.size()-2 ; ++first) {
        //In case of duplicates
        if(first > 0 && nums[first] == nums[first-1]) continue;
        int second = first+1;
        int third = nums.size()-1; 

        while(second < third) {
            int curSum = nums[first]+nums[second]+nums[third];
            //If req target sum is found
            if(curSum == target) return curSum;
            //Check if curr sum that we found is more closer to target than prev
            if(abs(target-curSum)<abs(target-closest)) {
                closest = curSum;
            }
            if(curSum > target) --third;
            else ++second;
        }
    }
    return closest;
}


// Squaring a Sorted Array
//T.C - O(N)  S.C - O(1)
vector<int> sortedSquares(vector<int>& A) {
    vector<int> res(A.size());
    int l = 0, r = A.size() - 1;
    for (int k = A.size() - 1; k >= 0; k--) {
        if (abs(A[r]) > abs(A[l])){//If right num is greater than left num
            res[k] = A[r] * A[r];//So store the square of that from the end
            r--;
        } 
        else{
            res[k] = A[l] * A[l];
            l++;
        }
    }
    return res;
}


// Shortest Unsorted Continuous Subarray
//T.C - O(N)  S.C - O(1)
int findUnsortedSubarray(vector<int>& nums) {
    int start = -1, end = -1,  max = INT_MIN;
    for(int i=0; i<nums.size();i++){
        if(max > nums[i]){//If the curr num is small
        //If seeing the discrepancy for first time
            if(start == -1) start = i-1;//Move the prev element where the discrepancy is
            while(start-1>=0 && nums[start-1]>nums[i]) start--;
            end = i+1;//Mark the subarray end
            }
        else max = nums[i];//Found a larger number than max
    }
    return end - start;   
}


// Backspace String Compare
//T.C - O(N)  S.C - O(1)
bool backspaceCompare(string S, string T) {
    int l = S.length()-1;
    int r = T.length()-1;
    int c = 0;
    int c1 = 0;
    while(l  >= 0 || r >= 0){
		//look for first pos where can compare for S
        while(l >= 0 && (S[l]=='#' || c > 0)){
            if(S[l]=='#') ++c;
            else --c;
            --l;
        }
        
		//look for first pos where can compare for T
        while(r >= 0 && (T[r]=='#' || c1 > 0)){
            if(T[r]=='#')++c1;
            else --c1;
            --r;
        }

		//both finished
        if(l < 0 && r < 0) return true;
		//Just one finished
        if(l < 0) return false;
        if(r < 0) return false;
		//Both not ending, can compare
        if(S[l]!=T[r]) return false;

        --l;
        --r;
    }
    return true;
}


// Reverse Pairs
//T.C - O(NlogN) S.C - O(N)
void checkCount(vector<int>& nums, int start, int mid, int end,int &count) {
    int l = start, r = mid + 1;
    while (l <= mid && r <= end){
        if ((long) nums[l] > (long) 2 * nums[r]){
            count += (mid - l + 1);
            r++;
        }
        else l++;
    }
    
    int a[end - start + 1], t = 0;
    l = start, r = mid + 1;
    while (l <= mid and r <= end) {
        if (l <= mid and nums[l] < nums[r]) a[t++] = nums[l++];
        else a[t++] = nums[r++];
    }
    
    while (l <= mid) a[t++] = nums[l++];
    while (r <= end) a[t++] = nums[r++];

    for (int i = 0; i < end - start + 1; i++) {
        nums[start + i] = a[i];
    }
    return;
}
void mergeSort(vector<int>& nums, int start, int end,int &count){
    if(start == end) return;
        
    int mid = (start + end)/2;
    mergeSort(nums,start, mid,count);
    mergeSort(nums,mid+1,end,count);
        
    checkCount(nums,start,mid,end,count);
    return;
        
}
int reversePairs(vector<int>& nums) {
    // We need pairs such that a[i] > 2*a[j]
    if(!nums.size()) return 0;
    int count = 0;
    mergeSort(nums,0,nums.size()-1,count);
    return count;
}


// Sorted Squares Array
// T.C - O(N)  S.C - O(N)
vector<int> sortedSquares(vector<int>&nums){
    int n = nums.size();
    int start = 0;
    int end = n-1;
    int pos = n-1;
    vector<int>res(n);

    while(start <= end){
        if(abs(nums[start]) < abs(nums[end])){
            res[pos--] = nums[end]*nums[end];
            end--;
        }
        else{
            res[pos--] = nums[start]*nums[start];
            start++;
        }
    }
    return res;
}


// Celebrity Problem
// T.C - O(N)  S.C - O(1)
int findCelebrity(int n){
    int firstPerson = 0;
    int lastPerson = n-1;

    while(firstPerson < lastPerson){
        if(knows(firstPerson,lastPerson)){
            firstPerson++;//can't be celebrity
        }
        else lastPerson--;//can't be celebrity'
    }

    // Finally we reach one person which can be celebrity
    int celebrity = firstPerson;//Acc to us he/she is the celeb

    //Now let's verify this
    bool knowsAny = false;
    bool knownToAll = true;

    //Check if the celeb knows anyone
    for(int i=0;i<n;i++){
        if(knows(celebrity,i)){
            knowsAny = true;
            break;
        }
    }

    //Check if some person doesn't know celeb
    for(int i=0;i<n;i++){
        if(i != celebrity && !knows(i,celebrity)){
            knownToAll = false;
            break;
        }
    }

    if(!knownToAll && knowsAny) celebrity = -1;//No celeb is there
    return celebrity;
}