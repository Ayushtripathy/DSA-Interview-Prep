// Design Hashmap
// T.C - O(N)  S.C - O(N)
class MyHashMap {//Not for a fixed range and solves collisions
    public:
    vector<list<pair<int,int>>>map;
    int size;
    MyHashMap() {
        size = 1e6+1;//Take the max allowed size
        map.resize(size);
    }

    int hash(int key){
        return key%size;
    }

    list<pair<int,int>> :: iterator search(int key){
        int i = hash(key);
        list<pair<int,int>>::iterator it = map[i].begin();
        while(it != map[i].end()){
            if(it->first == key) return it;
            it++;
        }
        return it;
    }

    void put(int key, int value) {
        int i = hash(key);//Find the idx
        remove(key);//If already present
        map[i].push_back({key, value});
    }
    
    int get(int key) {
      int i = hash(key);//Find the idx
      list<pair<int,int>> ::iterator it = search(key);
      if(it == map[i].end()) return -1;
      else return it->second;
    }
    
    void remove(int key) {
        int i = hash(key);//Find the idx
        list<pair<int,int>> ::iterator it = search(key);
        if(it != map[i].end()) map[i].erase(it);//Remove the searched key from map
    }
};
//Design HashSet(Troll implementation->limited size)
// T.C - O(1)  S.C - O(N)
class MyHashSet {
    private:
	vector<bool> set;
    public:
	MyHashSet() : set(1e6 + 1, false) {}
	
	void add(int key) {
		set[key] = true;
	}
	
	void remove(int key) {
		set[key] = false;
	}
	
	bool contains(int key) {
		return set[key];
	}
};


// Find first repeated character
// T.C - O(N) S.C - O(N)
char firstRepeating(string &str) {
    unordered_set<char> h;
    // Traverse the input array from left to right
    for (int i=0; i<str.length(); i++){
        // If element is already in hash set,it's the first repeating
        if (h.find(str[i]) != h.end()) return str[i];
        // Else add element to hash set
        else  h.insert(str[i]);
    }
    // If there was no repeated character
    return '\0';
}


// Subarray Sum Equals K
//T.C - O(N)  S.C - O(N)
int subarraySum(vector<int>& nums, int k) {
    int sum = 0;
    int count = 0;
       
    unordered_map<int, int>map;
        
    for(int i=0;i<nums.size();i++){
        sum += nums[i];//Add curr num to sum
            
        if(sum == k) count++;//If the sum gets equal to k then found subarray
            
        //If sum - k is found in map means another subarray equal to k is found
        //So increase count by times sum - k was encountered in map 
        if(map.find(sum - k) != map.end()) count += map[sum - k]; //doesn't work with count++ {[0,0,0,0,0,0,0,0,0,0] 0}
            
        map[sum]++;//Inc the count of this sum in map
    } 
    return count;
}


// Check if two arrays are equal or not
//T.C - O(N) S.C - O(N)
bool areEqual(int arr1[], int arr2[], int n, int m){
    // If lengths of arrays are not equal
    if (n != m) return false;
 
    // Store arr1[] elements and their counts in hash map
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++) mp[arr1[i]]++;
 
    // Traverse arr2[] elements and check if all
    // elements of arr2[] are present same number
    // of times or not.
    for (int i = 0; i < n; i++) {
        // If there is an element in arr2[], but not in arr1[]
        if (mp.find(arr2[i]) == mp.end()) return false;
 
        // If an element of arr2[] appears more times than it appears in arr1[]
        if (mp[arr2[i]] == 0) return false;
 
        mp[arr2[i]]--;
    }
    return true;
}


// Zero Sum Subarrays
// T.C - O(N)  S.C - O(N)
bool hasZeroSumSubarray(int nums[], int n){
    // create an empty set to store the sum of elements of each
    // subarray `nums[0…i]`, where `0 <= i < n`
    unordered_set<int> set;
 
    // insert 0 into the set to handle the case when subarray with
    // zero-sum starts from index 0
    set.insert(0);
    int sum = 0;

    // traverse the given array
    for (int i = 0; i < n; i++){
        // sum of elements so far
        sum += nums[i];
        // if the sum is seen before, we have found a subarray with zero-sum
        if (set.find(sum) != set.end()) return true;
        else set.insert(sum); // insert sum so far into the set
    }
    // we reach here when no subarray with zero-sum exists
    return false;
}
//Largest Subarray with zero-sum
//T.C - O(N)  S.C - O(N)
int largestZeroSum(vector<int>&arr){
    //Brute-force -> find all subarrays and store the max length subarray with zero sum
    unordered_map<int,int>map;//Map stores the prefix sum and idx upto the sum

    int sum = 0;
    int maxLen = 0;

    for(int i=0; i<arr.size();i++){
        sum += arr[i];

        if(sum == 0) maxLen = i + 1;

        else{//Sum is not zero but we find the same sum again
            if(map.find(sum) != map.end()){//Sum is present in map
            //Found a zero sum subarray
            //i - map[sum] means curr idx - the last pos we saw this sum
            maxLen = max(maxLen,i - map[sum]);
            }
            else{//Haven't seen the sum before
            map[sum] = i;//Push the sum and idx
            }
        }
    }
    return maxLen;
}


// First element to occur k times
//T.C - O(N) S.C - O(N)
int firstElement(int arr[], int n, int k){
    // unordered_map to count occurrences of each element
    unordered_map<int, int> count_map;
    for (int i=0; i<n; i++) count_map[arr[i]]++;
      
    for (int i=0; i<n; i++){
        // if count of element == k ,then it is the required first element 
        if (count_map[arr[i]] == k) return arr[i];
    }         
    // no element occurs k times
    return -1;
}


// Intersection of two arrays
//T.C - O(N)  S.C - O(N)
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ans; // Initialize an empty vector to hold the result
    set s = set(nums1.begin(), nums1.end()); // Storing elements of first array into a set, so we can get rid of duplicity
        
    for(int x: nums2){ // Iterate through the elements of second array
        if(s.find(x) != s.end()){ // Check if the element of second array is present in the set created from first array
            ans.push_back(x); // push matched element into result
            s.erase(x); // remove element from the set, so we will not face any duplicity in the next iteration
        }
    }
    return ans;
}


// Print Anagrams Together
// T.C - O(N*MlogM) S.C - O(N)
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string,vector<string>> map;
    for(string s:strs){
        string temp = s;
        sort(temp.begin(),temp.end());
        map[temp].push_back(s);
    }
        
    vector<vector<string>> ans;
    for(auto it:map) ans.push_back(it.second);
    
    return ans;
}


// Find the character in first string that is present at minimum index in second string
// T.C - O(M+N) S.C - O(d) where d is distinct chars in str
char printMinIndexChar(string str, string patt){
    // unordered_map 'um' implemented as hash table
    unordered_map<char, int> um;
 
    // to store the index of character having minimum index
    int minIndex = INT_MAX;
 
    // lengths of the two strings
    int m = str.size();
    int n = patt.size();-
 
    // store the first index of each character of 'str'
    for (int i = 0; i < m; i++){
        //Insert if only seeing the char first time
        if (um.find(str[i]) == um.end()) um[str[i]] = i;
    }
 
    // traverse the string 'patt'
    for (int i = 0; i < n; i++){
        //If patt[i] is found in 'um', check if it has the minimum index or not accordingly
        if (um.find(patt[i]) != um.end() && um[patt[i]] < minIndex){
            // update 'minIndex'
            minIndex = um[patt[i]];
        }
    }

    // print the minimum index character
    if (minIndex != INT_MAX) return str[minIndex];
    // if no character of 'patt' is present in 'str'
    else return '0';
}
vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
    //Finding common interest restaurants
    vector<string> res;
    int indexSum = INT_MAX;
        
    unordered_map<string, int> mp;

    //Push all the restaurantsin list 1 to map
    for(int i=0; i<list1.size(); i++) mp[list1[i]] = i;
    //Traverse the list 2
    for(int i=0; i<list2.size(); i++){
        //If found a common interest restaurant
        if(mp.find(list2[i]) != mp.end()){
            //And this restaurant has min idx
            if(mp[list2[i]] + i < indexSum){
                indexSum = mp[list2[i]] + i;//Update idx sum
                res.clear();
                res.push_back(list2[i]);//Push in ans
            }
            //If sum is same then don't update idx sum
            else if(mp[list2[i]] + i == indexSum) res.push_back(list2[i]);
        }    
    }
        return res;
}


// Array Subset of another array
//T.C - O(NlogN)  S.C - O(N)
bool isSubset(int arr1[], int m,int arr2[], int n){
    set<int> hashset;
 
    // hashset stores all the values of arr1
    for (int i = 0; i < m; i++) hashset.insert(arr1[i]);
 
    // loop to check if all elements of arr2 also lies in arr1
    for (int i = 0; i < n; i++) {//If any elements is not found
        if (hashset.find(arr2[i]) == hashset.end()) return false;
    }
    return true;
}


// Uncommon characters
// T.C - O(M+N)  S.C - O(1)
void findAndPrintUncommonChars(string str1, string str2){
    // mark presence of each character as 0 in the hash table 'present[]'
    int present[MAX_CHAR];
    for (int i=0; i<MAX_CHAR; i++) present[i] = 0;
 
    int l1 = str1.size();
    int l2 = str2.size();
 
    // for each character of str1, mark its presence as 1 in 'present[]'
    for (int i=0; i<l1; i++) present[str1[i] - 'a'] = 1;
 
    // for each character of str2
    for (int i=0; i<l2; i++){
        //If a character of str2 is also present in str1, then mark its presence as -1
        if (present[str2[i] - 'a'] == 1) present[str2[i] - 'a'] = -1;
        // else mark its presence as 2
        else present[str2[i] - 'a'] = 2;
    }
 
    // print all the uncommon characters
    for (int i=0; i<MAX_CHAR; i++){
        if (present[i] == 1 || present[i] == 2 )
        cout << (char(i + 'a')) << " ";
    }
}


// Encode and Decode TinyUrl
// T.C - O(N)  S.C - O(N)
class TinyUrl {
    public:
    map<string,string>map;//tinyurl,longurl
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string sb = "";//To store the shorturl
        sb += ((char)((int)rand()*100));//Add a random char to short url

        while(map.find(sb) != map.end()) {//This way we can cover all random chars
            sb += ((char)((int)rand()*100));//Keep adding a random char until seen a char 
        }

        map[sb] = longUrl;//Store the shorturl->longurl in map

        return sb;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return map[shortUrl];//Returns the longurl which corresponds to shorturl
    }
};


// Longest Consecutive Subsequence
//T.C - O(3N)  S.C - O(N)
int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int>map;
    for(auto n : nums) map[n]++;//Insert all elements of nums in map
        
    int ans = 0;//It will store the longest consecutive seq size

    for(auto n : nums){
        //If we find the prev num in map then we should start from that prev num na
        if(map.find(n-1) != map.end()) continue;//Do nothing
        
        else{//If we encounter a new element
            int size = 1;//Store the size of curr longest consecutive seq
            int curr = n+1;//Next element
            //As long as we find the next element in map
            while(map.find(curr) != map.end()) {
                curr++;//Increment the next element
                size++;//Increase the size
            }
            //Store the max size
            ans = max(ans, size);
        }
    }
    return ans;
}


// Array Pair Sum Divisibility Problem
//T.C - O(N)  S.C - O(N)
bool canArrange(vector<int>& arr, int k) {
    unordered_map<int,int> hash;
    //Store the mods of each element
    for(auto it : arr) hash[(it%k+k)%k]++;//Handles negative values also

    if(hash[0]%2 == 1) return false;//Elements with mod 0 are odd(can't form pairs)
    
    for(int i = 1; i < k; i++){
        //Couldn't find the complement count for a pair
        if(hash[i] != hash[k-i]) return false;
    }
    return true;
}


// Count distinct elements in every window of size k
//T.C - O(N)  S.C - O(N)
void countDistinctElements(int arr[],int k,int n){
    unordered_map<int,int>map;

    int count = 0;//Count of elements in each window

    for(int i = 0; i < k; i++){//Traverse the first window
        if(map[arr[i]] == 0) count++;//Found an unique element
        map[arr[i]]++;//Otherwise just store in map
    }

    // Print count of first window
    cout << dist_count << endl;
  
    // Traverse through the remaining array
    for (int i = k; i < n; i++) {
        // Remove first element of previous window
        // If there was only one occurrence, then reduce distinct count.
        if (hm[arr[i - k]] == 1) dist_count--;

        // reduce count of the removed element
        hm[arr[i - k]]--;
  
        // Add new element of current window
        // If this element appears first time, increment distinct element count
  
        if (hm[arr[i]] == 0) dist_count++;
        hm[arr[i]]++;
  
        // Print count of current window
        cout << dist_count << endl;
    }
}


// Repeated DNA Sequences
// T.C - O(N*10)  S.C - O(N)
vector<string> findRepeatedDnaSequences(string s) {
    unordered_map<string, int> counter;
    vector<string> res;
        
    if (s.size() < 10) return res;//We have to generate substr of len 10
    
    //While we can generate substr of len 10, push the those substrs in map as seen
    for (int i=0; i<s.size()-9; i++) counter[s.substr(i, 10)]++;

    //Now traverse the map        
    for (auto a:counter){
        //If the substr in map is seen and repeated ( > 1)
        if (a.second > 1) res.push_back(a.first);
    }
    return res;
}


// Swapping pairs make sum equal
// Brute force solution
//T.C - O(M*N) S.C - O(1)
bool sumSwap(vector<int>& nums1, vector<int>& nums2, int n, int m) {
    int sum1 = accumulate(nums1.begin(), nums1.end(),0);
    int sum2 = accumulate(nums2.begin(), nums2.end(),0);

    int newsum1,newsum2;
    int val1,val2;

    for(int i = 0; i < nums1.size();i++){
        for(int j = 0; j < nums2.size();j++){
            newsum1 = sum1 - nums1[i] + nums2[j];
            newsum2 = sum2 - nums2[j] + nums1[i];
            if(newsum1 == newsum2) return true;
        }
    }
}
//Optimized Solution
//T.C - O(N+M) S.C - O(M)
bool sumSwap(vector<int>& nums1, vector<int>& nums2, int n, int m){
    int sum1 = accumulate(nums1.begin(), nums1.end(),0);
    int sum2 = accumulate(nums2.begin(), nums2.end(),0);

    unordered_map<int,bool> exists;
    for(auto i : nums2) exists[nums2[i]] = true;

    if(abs(sum1 - sum2)%2 == 1) return false;

    for(auto it : nums1){
        int expected = nums1[it] + (sum2 - sum1)/2;
        //If need to print -> nums1[it] & (sum2-sum1)/2
        if(exists[expected]) return true;
    }
    return false;//If no pair exists
}


// Subarray Sums Divisible by K
//T.C - O(N)  S.C - O(K)
int subarraysDivByK(vector<int>& nums, int k) {
    vector<int> counts(k,0);
    int prefixSum = 0;

    for(int it : nums){
        //it%k we have to add this actually but we add k to handle negative values
        //but if the value is positive then adding k will exceed range so modulo again
        prefixSum += (it%k + k)%k;
        counts[prefixSum%k]++;//Store the modulo in map
    }

    int res = counts[0];
    for(int i : counts){
        //It is the no. of subarrays that the rem count in map can generate
        res += (i*(i-1))/2;
    }
    return res;
}


// Longest subarray with sum divisible by K
//T.C - O(N) S.C - O(N)
int longestSubarraysDivByK(vector<int>& nums, int k){
    int maxLen = 0;
    map<int, int> hash;
    int prefixSum = 0;
    int rem = 0;
    map[rem] = -1;//Initial value of rem is -1

    for(int i = 0; i < nums.size();i++){
        prefixSum += nums[i];//calculate the sum and rem
        rem = prefixSum % k;
        if(rem < 0) rem += k;//To handle negative values

        if(hash.find(rem) != hash.end()){//If we find the rem in map
        int idx = hash[rem];//In which idx we saw this rem prev
        int len = i - idx;//Length of subarray
        maxLen = max(maxLen,len);
        }
        else hash[rem] = i;//Seeing the rem for first time
    }
    return maxLen;
}


//Longest Subarray With Equal Number Of Zeroes And Ones
//T.C - O(N)  S.C - O(N)
int equalZeroOne(vector<int>& nums){
    unordered_map<int,int> map;
    map[0] = -1;//Initialize with -1 at 0 idx

    int prefixSum = 0;
    int maxLen = 0;
    for(int i = 0; i < nums.size();i++){
        if(nums[i] == 0) prefixSum -= 1;//To neutralize the sum when we find 1
        else prefixSum += 1;

        if(map.find(prefixSum) != map.end()){//We've seen the sum before
        int idx = map[prefixSum];//Means equal 0 and 1
        maxLen = max(maxLen,i - idx);//Store the max len
        }
        else map[sum] = i;//Seeing the sum for first time
    }
}


// Determine whether a string matches with a given pattern
//T.C - O(N)  S.C - O(3N)
bool wordPattern(string pattern, string s) {
    //Can't map 2 keys with same value
    if(pattern.length() == 0 || s.length() == 0) return false;
    if(pattern.length() != s.length()) return false;
    
    vector<string>words;//It will store the string s as strings array
    int idx = 0;
    string temp = "";
    while(idx < s.length()) {
        if(s[idx] == ' '){//If found a space
            words.push_back(temp);//Push to words array
            temp = "";//Reset the string for next value
        }
        else temp += s[idx];//Store the word in string in temp string
        idx++;//Move idx forward
    }
    words.push_back(temp);//For the last word

    if(words.size() != pattern.length()) return false;

    unordered_map<char,string> map;
    set<string>hash;

    for(int i = 0; i < pattern.length(); i++){//Traverse the pattern
    if(map.find(pattern[i]) != map.end()){//Found the char already mapped to some word
    if(map[pattern[i]] != words[i]) return false;//Mapped to a diff word
    }
    else{
        //The word is already mapped
        if(hash.count(words[i]) > 0) return false;
        map[pattern[i]] = words[i];//First time seeing the word so map
        hash.insert(words[i]);//Push the mapped word in set to check its presence
    }
    }
    return true;
}


// Check If a String Contains All Binary Codes of Size K
//T.C - O(N)  S.C - O(N)
bool hasAllCodes(string s, int k) {
    if (k > s.size()) return false;//Invalid case
    //Store the codes from string
    unordered_set<string> hash;
    
    //Insert in set all substrs from idx to k(k size)
    for (int i = 0; i <= s.size()-k; i++) hash.insert(s.substr(i, k));

    //If the size of set(no. of codes generated) equals to 2^k subsets return true
    return hash.size() == pow(2, k);
}


// First Missing Positive
// T.C - O(2N)  S.C - O(1)
int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    int i=0;//Start with the first element
    while(i<n){
        //If number is in req range and number and idx don't match 
        if(nums[i] > 0 && nums[i] <=n && nums[i] != nums[nums[i] - 1]){
            swap(nums[i],nums[nums[i] - 1]);//Place the num on its idx
            //But don't move forward yet
        }
        else ++i;//If num is < 0 or >=n then skip it
    }

    //Traverse the arr again
    for(int i=0;i<nums.size();i++){
        //If num is not at idx then that num is missing
        if(nums[i] != i+1) return i+1;
    }
    return n+1;//All nums are present return the next element > size
}