//Sliding Window Algorithm Template
void slidingWindow(){
    initialize i and j
    while(j<size){
        Calculate for j;
        if(winsize < k){
            j++
        }
        else if(winsize == k){
            calculate for ans
            remove calculation for i
            window size maintain
            slide the window(i++,j++)
        }
    }
}
// Variable Sliding Window Template
void variableSlidingWindow(){
    initialize i and j
    while(j < size){
        do calculation
        if(condition < k){
            increment j
        }
        else if(condition == k){
            calculate ans
            increment j
        }
        else if(condition > k){
            while(condition > k){
                remove calculation for i
                increment i
            }
            increment j
        }
    }
    return ans
}

//Sliding Window Maximum
//T.C - O(N) S.C - O(K)
vector<int> maxSlidingWindow(vector<int>& nums, int k){
    deque<int> dq;
    vector<int> ans;

    for(int i=0;i<nums.size();i++){
        //remove out of bounds of window before k
        if(!dq.empty() && dq.front() == i - k) dq.pop_front();
        //remove the min ones from queue
        while(!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        
        //push the element(curr max) in window
        dq.push_back(i);
        
        //insert the max from current window before moving to next
        if(i>=k-1) ans.push_back(nums[dq.front()]);
    }
    return ans;
}


// Maximum Sum Subarray of Size K
//T.C - O(N) S.C - O(1)
long maximumSumSubarray(int K, vector<int> &Arr , int N){
    long maxSum = INT_MIN;
    long sum = 0;
        
    int left = 0;
    int right = 0;
        
    while(right < N){
        sum += Arr[right];
            
        if(right - left + 1 == K){
            maxSum = max(sum,maxSum);
            sum -= Arr[left];
            left++;
        }
        right++;
    }
    return maxSum;
}


//Sum of minimum and maximum elements of all subarrays of size “k”.
//T.C - O(2N) S.C - O(2K)
int sumMinMaxSubarray(vector<int>arr,int k){
    deque<int>dq_max;
    deque<int>dq_min;
    int sum = 0;
    for(int i=0;i<arr.size();i++){
        if(!dq_max.empty() && dq_max.front() == i-k) dq_max.pop_front();
        if(!dq_min.empty() && dq_min.front() == i-k) dq_min.pop_front();

        while(!dq_max.empty && arr[dq_max.back()] < arr[i]) dq_max.pop_back();
        while(!dq_min.empty && arr[dq_min.back()] > arr[i]) dq_min.pop_back();

        dq_max.push_back(i);
        dq_min.push_back(i);

        if(i >= k-1){
            sum += arr[dq_max.front()] + arr[dq_min.front()];
        }
    }
    return sum;
}


//First negative integer in every window of size k 
//T.C - O(N) S.C - O(N)
vector<int> firstNegative(vector<int>& nums, int k){
    queue<int> q;
    vector<int> ans;
    int i=0,j=0;
    while(j < nums.size()){
        if(nums[j] < 0) q.push(nums[j]);//Push negative element to queue
        
        if(j - i + 1 == k){ //Reached the window  size
            if(q.empty()) ans.push_back(0);//No negative element for that window
            
            else{
                ans.push_back(q.front());//First negative integer is in front of queue for that window
                if(q.front() == nums[i]) q.pop();//Found an element which acted as min -ve but now is out of bounds
            }//Move the window slider
            i++;
        }
        j++;
    }
    return ans;
}


//Count Occurrences Of Anagrams
//T.C - O(N) S.C - O(K) where k = p.length()
int countOccurrence(string s, string p){
    unordered_map<char, int> mp;
    int ans = 0;
    //storing the occ. of string p in the map
    for (auto &x : p) mp[x]++;

    int count = mp.size();//No need to traverse the map
    int k = p.size();
    int i=0, j=0;

    while (j < s.size()){
        //Exhaust the chars in pattern to find an Anagram
        if (mp.find(s[j]) != mp.end()){
            mp[s[j]]--;
            if (mp[s[j]] == 0) count--;
        }

        //window length not achieved yet
        if (j-i+1 < k) j++;

        //window length achieved, find ans and slide the window
        else if (j-i+1 == k){
            //If pattern is completely exhausted in the window
            if (count == 0) ans++;//Anagram found
            //Increase the removed char count again before moving the slider
            if (mp.find(s[i]) != mp.end()){
                mp[s[i]]++;
                if (mp[s[i]] == 1) count++;
            }
            //slide the window
            i++;
            j++;
        }
    }
    return ans;
}


//Variable Size Sliding Window
//T.C - O(N) S.C - O(1)
int largestSubarraySumK(vector<int> arr,int k){
    //Not for negative integers
	int i = 0, j = 0, sum = 0;
	int maxWin = INT_MIN;

	while (j < arr.size()) {
		sum += A[j];
		if (sum == k) {
			maxWin = max(maxWin, j - i + 1);
		}
        else if (sum > k) {
			while (sum > k) {
				sum -= A[i];//Balancing the sum by subtracting
				i++;
			}
		}
		j++;
	}
	return maxWin;
}


//Smallest Subarray with a given sum(equal or greater)
//T.C - O(N) S.C - O(1)
int minSubArrayLen(int s, vector<int>& nums){
    int ans = INT_MAX;
    int left = 0;
    int sum = 0;
    for (int i = 0; i < nums.size();i++) {
        sum += nums[i];
        while (sum >= s) {//Reached the condition
            ans = min(ans, i - left + 1);//Calculate the ans
            sum -= nums[left];//Remove the left element from window
            left++;//Move slider
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}


//Longest Substring With K Unique Characters
//T.C - O(N) S.C - O(K)
int longestKSubstr(string s, int k) {
    unordered_map<char, int>map;
    int i = 0, j = 0;
    int maxLen = -1;
    //Store distinct chars in map
    while(j < s.length()) {
        map[s[j]]++;//Push in the map

        if(map.size() == k) maxLen = max(maxLen,j - i + 1);
    
        else if(map.size() > k){//More than required unique chars in map
            while(map.size() > k){
                map[s[i]]--;//Remove the chars from left in map
                if(map[s[i]] == 0) map.erase(s[i]);
                i++;
            }
        }
        j++;
    }
    return maxLen;
}


//Fruit into Baskets
//T.C - O(N) S.C - O(1)
int totalFruit(vector<int>& fruits) {
    if(fruits.size() == 0) return 0;

    int left = 0, right = 0, maxLen = 0;
    unordered_map<int,int> map;

    while(left < fruits.size()){
        map[fruits[i]]++;
        if(map.size() <= 2){
            maxLen = max(maxLen,right - left + 1);
            right++;
        }
        else{
            while(map.size() > 2){
                map[fruits[left]]--;
                if(map[fruits[left]] == 0) map.erase(fruits[left]);
                left++;
            }
            right++;
        }
    }
    return maxLen;
}


//Longest Substring with no repeating characters
//T.C - O(N) S.C - O(N)
int longestNonRepeatingSubstring(string s) {
    int i=0,j=0;
    int maxLen = 0;
    unordered_map<char,int>map;

    while(j < s.length()) {
        map[s[j]]++;
        if(map.size() == j - i + 1){//Window is equal to unique chars
            maxLen = max(maxLen,j - i + 1);
        }
        //Window size exceeds the unique chars num
        else if(map.size() < j - i + 1){//Found a duplicate char
            while(map.size() < j - i + 1){
                map[s[i]]--;
                if(map[s[i]] == 0) map.erase(s[i]);
                i++;
            }
        }
        j++;
    }
    return maxLen;
}


//Smallest Window containing Substring (Doubt)????
string minWindow(string s, string t) {
    unordered_map<char, int> map;
    int ans = INT_MAX; 
    int start = 0; 
        
    for(auto x : t) map[x]++;//Store t in map
    
    int count = map.size();
    int i = 0, j = 0;

    while (j < s.length()) {
        map[s[j]]--;//Reduce the char at j from map

        //Char completely removed then remove the count of chars to look for
        if (map[s[j]] == 0) count--;

        //Found all the str2 chars in str1
        if (count == 0) {
            while (count == 0) {
                if (ans > j - i + 1) {//Found min len
                    ans = j - i + 1;//Store min length
                    start = i;//start of that min substr
                }
                
                map[s[i]]++;//Add the char at i to map
                    
                if (map[s[i]] > 0) count++;//Num of chars increases
                i++;//Move window from left to right
            }
        }
        j++;//Move forward from right
    }
        
    if (ans != INT_MAX) return s.substr(start, ans);
    else return "";
}


//Permutation in a String(Same as anagram)
//T.C - O(N2) S.C - O(N1)
bool checkInclusion(string s1, string s2) {
    unordered_map<char,int>map;
    for(int i = 0; i < s1.length();++i) map[s1[i]]++;
    int i = 0,j = 0;
    int count = map.size();
    while(j < s2.length()){
        if(map.find(s2[j]) != map.end()){
            map[s2[j]]--;
            if(map[s2[j]] == 0) count--;
        }
        if(j - i + 1 == s1.length()){
            if(count == 0) return true;
            if(map.find(s2[i]) != map.end()){
                map[s2[i]]++;
                if(map[s2[i]] == 1) count++;
            }
            i++;
        }
        j++;
    }
    return false;
}


//Longest Subarray with Ones after Replacement
int longestOnes(vector<int>& nums, int k) {
    int count = 0;
    int maxLen = 0;
    int i = 0,j = 0;
    
    while(j < nums.size()){
        if(nums[j] == 0) count++;//Count the zeroes flipped

        if(count <= k) {//Zeroes flipped are less than window
            maxLen = max(maxLen,j-i+1);//Store the max len
            j++;
        }
        if(count > k) {//Zeroes flipped exceeds the window
            while(count > k) {
                if(nums[i] == 0) count--;//Discard the left zeroes that were flipped
                i++;//Move the slider
            }
            j++;
        }
    }
    return maxLen;
}


//Longest Substring with Same Letters after Replacement
//T.C - O(N) S.C - O(1)
int characterReplacement(string s, int k) {
    vector<int> letterCount(26, 0);
    int maxLen = 0;
    int start = 0, end = 0;
    int mostLetter = 0;
    
    while(end < s.size()) {
        letterCount[s[end]-'A']++;
        mostLetter = max(mostLetter, letterCount[s[end]-'A']);//Gives the count of most popular element in the window
        if(end - start + 1 - mostLetter > k){//Is window m most popular char ke alawa aur 'k' dusre element hi ho skte h kyuki m sirf unhi k ko flip kr skta hu
            letterCount[s[start]-'A']--;//Remove char count from left because window is moving to right
            start++;
        }
        maxLen = max(maxLen, end - start + 1);
        end++;
    }
    return maxLen;
}


//Subarray with Palindromic Concatenation (Doubt)?????
//T.C - O(N*N) S.C - O(1)
bool isPalindrome(int n){
    int temp = n,number = 0;

    while(temp > 0){
        number = number *10 + temp%10;
        temp = temp/10;
    }

    if(number == n) return true;
    return false;
}
int findPalindromicSubarray(vector<int>arr,int k){
    int num = 0;
    for(int i=0;i<k;++i) num = num*10 + arr[i];

    if(isPalindrome(num)) return 0;

    for(int j = k;j < arr.size();++j){
        num = (num%(int)pow(10,k-1))*10 + arr[i];
        if(isPalindrome(num)) return j - k + 1;
    }
    return -1;
}


//Form Number from Subarray Divisible by 3
//T.C - O(N) S.C - O(1)
void divisibleBy3(vector<int>arr,int k){
    pair<int,int> ans;
    int sum = 0;

    for(int i=0;i<k;i++) sum += arr[i];

    bool found = false;
    if(sum%3 == 0){
        ans = make_pair(0,k-1);
        found = true;
    }
    for(int j=k;i<arr.size();j++){
        if(found) break;
        sum += arr[j] - arr[j-k];
        if(sum%3 == 0){
            ans = make_pair(j-k+1,j);
            found = true;
        }
    }
    if(!found){
        ans = make_pair(-1,0);
    }
    if(ans.first == -1) cout<<"NO"<<endl;

    else{
        for(int i=ans.first;i<=ans.second;++i){
            cout<<arr[i]<<" ";
        }
    }
}


//Words Concatenation (Doubt)?????
//T.C - O() S.C - O()
vector<int> findSubstring(string s, vector<string>& words) {
    unordered_map<char, int> map;
    vector<int>ans;
    string p = "";
    for(int i =0;i<words.size();i++){
            string temp = words[i];
            p += temp;
    }

    for (auto &x : p) map[x]++;

    int count = map.size();//No need to traverse the map
    int k = p.size();
    int i=0, j=0;
        
    while(j < s.size()){
        if(map.find(s[j]) != map.end()){
            map[s[j]]--;
            if(map[s[j]] == 0) count--;
        }
                
        if(j - i + 1 == k){
            if(count == 0) ans.push_back(i);
            
            if(map.find(s[i]) != map.end()){
            map[s[i]]++;
            if(map[s[i]] == 1) count++;
            }
            
            i++;
        }
        j++;
    }
        
    return ans;
}


//Perfect Numbers in Subarrays size k
//T.C - O(N*sqrtN) S.C - O(1)
bool isPerfect(int n){
    int sum = 1;//stores proper divisors
    for(int i=2;i<sqrt(n);++i){
        if(n%i == 0){
            if(i == n/i) sum += i;
        }
        else sum += i + n/i;
    }
    if(sum == n && n != 1) return true;
    return false;
}
int maxSum(int arr[],int size,int k){
    if(n<k) return -1;
    int res = 0;
    for(int i=0;i<k;++i){
        res += arr[i];
    }
    int sum = res;
    for(int i=k;i<size;++i){
        sum += arr[i] - arr[i-k];
        res = max(sum,res);
    }
    return res;
}
int maxPerfectNumbers(int arr[],int size,int k){
    //Check for perfect numbers in array and replace with 0  or 1
    for(int i=0;i<size;i++){
        if(isPerfect(arr[i])) arr[i] = 1;
        else arr[i] = 0;
    }
    return maxSUm(arr,size,k);
}


// Subarrays with K Different Integers
//T.C - O(2N)  S.C - O(K)
int atMostK(vector<int>& arr, int K) {
    int i = 0, j = 0, substrings = 0;
    unordered_map<int, int> freq;
    const int N = arr.size();
        
    while(i < N) {
        // Expand the window
        if(K >= 0) {//If we have scope of finding more unique no.
            ++freq[arr[i]];//Inc count in map
            if(freq[arr[i]] == 1) --K;//Found an unique no. so decrement k
            ++i;//MOve window
        }
        // make the window valid
        while(K < 0) {
            --freq[arr[j]];//Now remove no. from left of window
            if(freq[arr[j]] == 0) ++K;//Completely remove the unique value so scope of unique(k) increases
            ++j;//Slide the window to right
        }
        // Each valid window adds the subarrays which satisfies the condition
        // For : 1,2,1, k=2
        // 1: [1] 
        // 2: [2], [1,2]
        // 3: [1,2], [2,1], [1,2,1]
        substrings += i - j + 1;//calculate the window size
    }
    return substrings;
}
int subarraysWithKDistinct(vector<int>& arr, int K) {
    return atmostK(arr, K) - atmostK(arr, K-1);
}


// Check If a String Contains All Binary Codes of Size K
// T.C - O(N)  S.C - O(N)
bool hasAllCodes(string s, int k) {
    f (k > s.size()) return false;
    int count = 0;
    int start = 0;
    set<int>hash;//sets doesn't allow duplicates'
    for(int i = 0; i <s.length(); i++) {
        count++;//Increase the window
        if(count == k){//We are in the req window
        hash.insert(s.substr(start,start+k));//Insert k size substr into set
        start++;
        count--;//Move the window
        }
    }
   return hash.size() == pow(2,k);
}


// Subarrays with Product Less than a Target
//T.C - O(N)  S.C - O(1)
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if(k <= 1) return 0;// Base case

    int prod = 1;//Store the product
    int subarrays = 0;//Number of subarrays

    //Sliding window
    int left = 0;
    int right = 0;

    while(right < nums.size()) {
        prod *= nums[right];
        //Exceed the window boundary
        while(prod >= k){//Until the product becomes less than k
            prod /= nums[left];//Divide the multiplied element from left
            left++;
        }
        subarrays += right - left + 1;//Window size
        right++;
    }
    return subarrays;
}


//Minimum Operations to Reduce X to Zero
//T.C - O(N) S.C - O(1)
int minOperations(vector<int>& nums, int x) {
    // example 
    // [1,1,4,2,3] , x=5
    // target = sum(nums)-x, which is => 6 in this case 
    // we will try to find longest subarray with given target
    // max length with target is 3 [1,1,4]
    // our ans is nums.size()-3 => 2
        
    int target = -x;
    for(int i:nums) target += i;
        
    if(target < 0) return -1;
        
    int j = 0;
    int sum = 0;
    int ans = INT_MIN;
    int n = nums.size();
        
    for(int i=0;i<n;i++){
        sum += nums[i]; 
        while(sum > target){
            sum -= nums[j];
            j++;
        }
            
        if(sum == target) ans = max(ans,i-j+1);
    }
    return ans == INT_MIN ? -1 : n - ans;
}