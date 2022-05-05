// Heap Implementation
class MaxHeap {
    private:
    int size;//Size of curr heap array
    int capacity;// Capacity of heap
    vector<int> maxHeap;//Heap array
    int parent(int i) { return (i)/2; }
    public:
    MaxHeap(int capacity){//Initialize using constructor
        size = 0;
        maxHeap[0] = -1;
        this->capacity = capacity;
        maxHeap.resize(capacity);
    }

    //T.C - O(logN)
    void insert(int key){
        if(size == capacity) return;//Heap is full
        size++;//Increase size of heap
        int idx = size;//Store the last index
        maxHeap[idx] = key;//Insert the key at last index

        while(idx > 1){//Up heapify
        int parent = idx/2;
            if(maxHeap[parent] < maxHeap[idx]){
                swap(maxHeap[parent],maxHeap[idx]);
                idx = parent;//Now the new node is at parent index after swapping
            }
        }
    }

    //T.C - O(logN)
    void delete(){
        if(size == 0) return;

        maxHeap[1] = maxHeap[size];//Swap first and last nodes
        size--;//Removed the node access

        int idx = 1;
        while(idx < size){//Down heapify
            int leftIndex = 2*idx;//Pos of left child
            int rightIndex = 2*idx + 1;//Pos of right child

            //If left idx is in bounds and arr[i](parent) is less than arr[left](left child)
            if(leftIndex < size && maxHeap[idx] < maxHeap[leftIndex]){
                swap(maxHeap[idx], maxHeap[leftIndex]);
                idx = leftIndex;//Move to left child
            }
            //If right idx is in bounds and arr[i](parent) is less than arr[right](right child)
            else if(rightIndex < size && maxHeap[idx] > maxHeap[rightIndex]){
                swap(maxHeap[idx], maxHeap[rightIndex]);
                idx = rightIndex;//Move to right child
            }
        }
    }

    void heapify(int i) {
    int leftChild = 2*i;
    int rightChild = 2*i + 1;
    int largest = i;//Right now i holds the largest value in heap
    
    //If left child is larger than curr idx than store it as largest node
    if((leftChild <= size) && (maxHeap[leftChild] > maxHeap[largest])) largest = leftChild;
    //If right child is larger than curr idx than store it as largest node
    if((rightChild <= size) and  (maxHeap[rightChild] > maxHeap[largest])) largest = rightChild;

    if(largest != i) {//Largest has updated
        swap(maxHeap[largest], maxHeap[i]);//Place the node its right place
        heapify(largest);//Now heapify this point further
        }
    }

    //T.C - O(logN)
    int extractMax(){
        if(size == 0) return -1;//Heap is empty
        if(size == 1) { //Only one element present
            size--;//Decrease size of heap
            return maxHeap[1];//Return top(first) element
        }
        else{
            int root = maxHeap[1];//Store the max element(present at first idx or root)
            maxHeap[1] = maxHeap[size];//Swap the first and last nodes(just like  deletion)
            size--;//Decrease the size of the heap
            heapify(1);//Element was removed from 1st idx so heapify the tree from that idx
            return root;
        }
    }

    int getSize() { return size; }

    int getElement(int idx) {
        if(idx > size || idx < 0) return -1;
        return maxHeap[idx];//Return element at that index
    }

    void printHeap(){
        for(int i=1;i<=size;i++) cout<<maxHeap[i]<<" ";
    }
};


// Heap Sort
//T.C - O(NlogN) S.C - O(1)
void heapify(int arr[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapify(arr, n, largest);
    }
}
void heapSort(int arr[],int size){
    int n = size;

    while(n > 1){
        swap(arr[n],arr[1]);
        n--;
        
        // Heapify root element to get highest element at root again
        heapify(arr,n,1);
    }
}


// Check if a binary tree is a min-heap or not
//T.C - O(N) S.C - O(N)
bool isMaxHeap(TreeNode* root){
    if(!root) return true;

    //We'll do level order traversal
    queue<TreeNode*>q;
    p.push(root);
    bool isNull = false;//When an empty left or right child is seen for a node

    while(q.empty()){
        TreeNode* curr = q.front();
        q.pop();

        if(curr->left){//Left child exists
        //If either heap property is violated(left child m pehle null tha so its not CBT)
        if(isNull || curr->left->data >= curr->data) return false;
            q.push(curr->left);
        }
        else isNull = true;
        if(curr->right){//Right child exists
        if(isNull || curr->right->data >= curr->data) return false;
        q.push(curr->right);
        }
        else isNull = true;
    }
    return true;//Only reach here if its a max heap
}


// Check if an array represents a min-heap or not
//T.C - O(N) S.C - O(H)
bool checkMinHeap(vector<int>arr,int idx = 1){
    if(2*idx + 1 > arr.size()) return true;//Every leaf node is heap

    //Check if left child is heap(Check for smaller value && send the child to check further)
    bool left = (arr[i] <= arr[2*idx]) && checkMinHeap(arr,2*i);

    //Check if right child is heap(Check for smaller value && send the child to check further)
    bool right = (arr[i] <= arr[2*idx+1]) && checkMinHeap(arr,2*i+1);

    return left && right;
}


// Convert a Binary Search Tree into a Min Heap
//T.C - O(N)  S.C - O(N)
void inorder(TreeNode* root,queue<int>&keys){
    if(!root) return;

    inorder(root->left,keys);
    keys.push(root->data);
    inorder(root->right,keys);
}
TreeNode* constructHeap(queue<int> &keys){
    // construct a queue to store the parents
    queue<TreeNode*> q;
 
    // initialize the root of the complete binary tree
    TreeNode* root = new TreeNode(keys.front());
    keys.pop();
 
    // enqueue root node
    q.push(root);
 
    // loop till all keys are processed
    while (!keys.empty()){
        // dequeue front node
        TreeNode* parent = q.front();
        q.pop();
 
        // allocate the left child of the parent node with the next key
        parent->left = new TreeNode(keys.front());
        keys.pop();
 
        // enqueue left child node
        q.push(parent->left);
 
        // if the next key exists
        if (!keys.empty()){
            // allocate the right child of the parent node with the next key
            parent->right = new TreeNode(keys.front());
            keys.pop();
 
            // enqueue right child node
            q.push(parent->right);
        }
    }
    return root;
}
void convertBSTreeToMinHeap(TreeNode* root){
    if(!root) return;

    queue<int> keys;//Store the inorder in sorted order

    inorder(root,keys);//For max heap just store the keys in reverse inorder

    //If it's CBT already,just replace root's data with preorder

    root = constructHeap(keys);//If it's not a CBT
}


// Kth Smallest Number
//T.C - O(NlogK) S.C - O(K)
int findKthSmallest(vector<int>& nums, int k) {
    priority_queue<int> pq;//Build a max heap
    // priority_queue<int, vector<int>, greater<int>> pq;//Min heap

    //Push array elements to heap
    for(auto num : nums){
        pq.push(num);

        if(pq.size() > k) pq.pop();
    }  
    return pq.top();
}


// Sort a nearly sorted (or K sorted) array
//If the elements are exactly k dist away from their pos 
// T.C - O(N)  S.C - O(1)
vector<int> SortKDistanceArray(vector<int> &input, int k){

    for(int i=0 ; i<input.size() - k;i++){
        if(input[i]<input[i+k]) continue;
        swap(input[i],input[i+k]);
       }
    return input;
}
//T.C - O((N-K)logK)  S.C - O(K)
void sortKSortedArray(vector<int>&arr,int k){
    priority_queue<int, vector<int>, greater<int>>pq;//Min heap

    int index = 0;//Idx where we keep inserting element from heap in sorted form
    for(int i=0;i<arr.size();i++){
        pq.push(arr[i]);//Push the new arr element 
        if(pq.size() > k){
        arr[index++] = pq.top();//Put the min val from heap at idx and increment
        pq.pop();
        }
    }

    //After 1st k+1 elements are sorted,sort the rest of elements by getting the min from heap
    while(!pq.empty()){
        arr[index++] = pq.top();
        pq.pop();
    }
}


// 'K' Closest Numbers
//T.C - O(NlogK + KlogK)  S.C - O(K)
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    vector<int> ans;
    priority_queue<pair<int,int>> pq;
        
    for(int i=0;i<arr.size();i++){
        pq.push({abs(arr[i]-x),arr[i]});
        if(pq.size()>k) pq.pop();
    }

    while(pq.size()>0){
    ans.push_back(pq.top().second);
    pq.pop();
    }

    sort(ans.begin(), ans.end());
    return ans;
}


// Merge two maxheaps
//T.C - O((M+N) + N)  S.C - O(M+N)
void heapify(vector<int>&arr, int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapify(arr, n, largest);
    }
}
vector<int> mergeHeaps(vector<int>&a,vector<int>&b,int n,int m){
    //Step1. Merge both arrays
    vector<int>ans;
    for(auto i : a) ans.push_back(i);
    for(auto i : b) ans.push_back(i);
    
    //step2. Build heap from the resultant array
    int size = ans.size();
    for(int i = size/2-1;i>=0;i--){
        heapify(ans,size,i);
    }
    return ans;
}


// Top 'K' Frequent Numbers
//T.C - O(NlogK) S.C - O(K+N)
vector<int> topKFrequent(vector<int>& nums, int k) {
    //Create a min heap because we need largest freq
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    unordered_map<int,int>map;//Instead of values themselves we'll store their freqs
    vector<int>ans;

    for(int i=0;i<nums.size();i++) map[nums[i]]++;//Insert freq of all elements in map

    //Instead of iterating the array we iterate the map(it contains freqs)
    for(auto it=map.begin();it!=map.end();it++){
        pq.push({it->second,it->first});//Push key and values(it->first stores the element itself)
        if(pq.size() > k) pq.pop();//Pop the min elements(retain the max ones in heap)
    }

    //The remaining elements in heap is our ans
    while(pq.size() > 0){
        ans.push_back(pq.top().second);
        pq.pop();
    }
    return ans;
}
// Top 'K' Frequent Words
struct MyComp {
    bool operator() (const pair<int, string>& a, const pair<int, string>& b) {
        if(a.first != b.first) return a.first > b.first;//If word count is not equal return the more freq
        else return a.second < b.second;//If the count is equal return the smallerr one
    }
};
vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> hashmap;
    for(string& word : words) hashmap[word] += 1;
    
    priority_queue<pair<int, string>, vector<pair<int, string>>, MyComp> pq;
    for(auto it = hashmap.begin(); it != hashmap.end(); ++it) {
        pq.push(make_pair(it->second, it->first));
        if(pq.size() > k) pq.pop();
    }
    vector<string> res;
    while(!pq.empty()) {
        res.insert(res.begin(), pq.top().second);
        pq.pop();
    }
    return res;
}


// Frequency Sort
//T.C - O(N)  S.C - O(logN + N)
string frequencySort(string s) {
    unordered_map<char, int>map;
    priority_queue<pair<int,char>>pq;

    for(auto c : s) map[c]++;//Store freq in map

    for(auto it : map) pq.push({it.second, it.first});//Store the freq and char

    s = "";//Empty the original string

    while(!pq.empty()){
        int freq = pq.top().first;
        int _char = pq.top().second;
        for(int i=0;i<freq;i++) s += _char;
        pq.pop();
    }
    return s;
}
//For array elements
vector<int> frequencySort(vector<int>& nums) {        
    //Creating map of array elements with their count
    unordered_map<int, int> map;
    for(auto x: nums) map[x]++;//Store the freqs in map
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, comp> pq;
    vector<int> ans;
        
    //Traversing through map and pushing it in heap
    for(auto x: map) pq.push({x.second, x.first}); // Making pair of count and the number
        
    //Pushing the heap elements in vector multiplied with it's frequency
    while(pq.size() > 0){
        int freq = pq.top().first;
        int value = pq.top().second;
        //Push the value freq times in output
        for(int i=0; i<freq;i++) ans.push_back(value);
        pq.pop();
    }
    return ans;
}


// Minimum Cost of ropes
//T.C - O(NlogN) S.C - O(N)
int minCost(int arr[],int n){
    //Create a min heap
    priority_queue<int,vector<int>,greater<int>>pq;

    //Push the elements to min heap
    for(int i=0;i<n;i++) pq.push(arr[i]);

    int cost = 0;
    while(!pq.empty()){
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();

        int sum = first + second;//Add the two min ropes
        cost += sum;//Add the cost to join
        pq.push(sum);//Push the joined rope in min heap
    }
    return cost;
}


// Merge K sorted arrays LC 23
//T.C - O(NlogK)  S.C - O(K)
typedef pair<int, pair<int, int> > ppi;
vector<int> mergeKArrays(vector<vector<int>>arr){
    vector<output>;
    //Pair<int,Pair<int,int>> -> value,<arrayIdx,elementIdx> 
    priority_queue<ppi,vector<ppi>,greater<ppi>>pq;

    //Store the heads of k arrays in min heap
    for(int i=0;i<arr.size();i++) pq.push({arr[i][0],{i,0}});

    while(!pq.empty()){
        ppi curr = pq.top();
        pq.pop();
        int value = curr.first;
        int arrIdx = curr.second.first;
        int eleIdx = curr.second.second;

        output.push_back(value);//Store the value in ans

        //Insert the nxt element of same array as before into the heap
        if(eleIdx + 1 < arr[arrIdx].size()) pq.push({arr[arrIdx][eleIdx+1],{arrIdx,eleIdx+1}});
    }
    return output;
}


// Kth Largest Sum Subarray
//Brute force - Find sum of all subarrays using 2 loops,store them in an array,sort it and return k-1 element
//T.C - O(N*NlogN) S.C - O(N*N)
int kthLargestSum(vector<int>&arr,int n,int k){
    vector<int>res;
	// Pick starting point
	for (int i=0; i <n; i++){
		// Pick ending point
		int temp=0;
		for (int j=i; j<n; j++){
			// sum of subarray between current starting and ending points
			temp += arr[j];
			res.push_back(temp);
		}
	}
    //Sort the array
    sort(res.begin(),res.end());

	return result[k-1];
}
//Optimized Solution
// T.C - O(N*NlogK)  S.C - O(K)
int kthLargestSum(vector<int>&arr,int n,int k){
    priority_queue<int,vector<int>, greater<int>>pq;

    for(int i=0;i<n;i++){
        int sum = 0;
        for(int j=i;j<n;j++){
            sum += arr[j];
            if(pq.size() < k) pq.push(sum);
            else{//We filled the k elements so now we'll only push greater sums than existing
                if(pq.top() < sum){//Found a sum greater
                    pq.pop();//But we allow only k elements so pop first
                    pq.push(sum);
                }
            }
        }
    }
    return pq.top();
}


// Kth Smallest Number in a Sorted Matrix
//T.C - O(N*NlogK) S.C - O(K)
int kthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<int>pq; 
    int n = matrix.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            pq.push(matrix[i][j]);
            if(pq.size() > k) pq.pop();
        }
    }
    return pq.top();   
}


// Rearrange String
//T.C - O(N+N)  S.C - O(1)
string reorganizeString(string s) {
    vector<int>freq(26);

    // Step 1 Count the occ. of each charcater in given string
    for(auto ch : s) {
        //If occ. of any char exceeds half of str length then its not possible to reorganize
        if(++freq[ch-97] > (s.length()+1)/2) return "";
    }

    // Step 2 Make a max_heap of pair and push count and chars
    //T.C and S.C will be O(1) because it takes O(n) to build heap but n is 26 here(constant)
    priority_queue<pair<int, char>> pq;//pair-> count,char
    for(int i=0;i<26;i++){
        //Don't push the chars that are not in string
        if(freq[i]) pq.push({freq[i],97+i});
    }

    int idx = 0;//Index from where we'll reorganize string
    pair<int,char> prev = pq.top();//Extract the char with max freq
    pq.pop();
    s[idx++] = prev.second;//Place the char in string
    
    while(!pq.empty()){
        pair<int,char> curr = pq.top();
        pq.pop();
        s[idx++] = curr.second;
        //The prev char before curr still had some count remaining so push it(after decrementing count) again to use it again
        if(--prev.first) pq.push(prev);
        //Now the curr char placed becomes the prev and we'll extract a new one from queue
        prev = curr;
    }
    return s;
}


// 'K' Closest Points to the Origin
//T.C - O(NlogK)  S.C - O(K)
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    // Brute force - sort the  points and return the k closest/Smallest pts by calculating dist
    vector<vector<int>>res;//We want to return k points
    if(points.size()==0) return res;
    priority_queue<pair<int,pair<int,int>>> pq;//Build a max heap

    //Traverse the points
    for(auto point:points){
        int x = point[0];//Extract x and y coordinates
        int y = point[1];

        int dist = x*x + y*y;//dist from origin
        //Push dist and the coordinates
        if(pq.size() < k) pq.push({dist,{x,y}});
        else{
            if(dist < pq.top().first){//Found a smaller dist
            //Largest dist will be popped and smaller ones will be left
            pq.pop();
            pq.push({dist,{x,y}});
            }
        }
    }

    //Store the ans to return
    while(!pq.empty()){
        int x1 = pq.top().second.first;
        int y1 = pq.top().second.second;
        res.push_back({x1,y1});
        pq.pop();
    }
    return res;
}


// K Pairs with Smallest Sums
// T.C - O(M*NlogK)  S.C - O(K)
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    priority_queue<pair<int,pair<int,int>>> pq;  // default: the greatest comes top
   
    //Traverse the two arrays
    for(int i=0;i<nums1.size();i++) {
        for(int j=0;j<nums2.size();j++) {

            int sum = nums1[i]+nums2[j];//Take sum of 2 nums

            //There is space in pq so insert the sum 
            if (pq.size() < k) pq.push({sum,{nums1[i],nums2[j]}});
            //Found a small sum so remove the max sum and insert it
            else if (sum < pq.top().first) {
                pq.pop();
                pq.push({sum,{nums1[i],nums2[j]}});
            }
            else break;// save time! since we don't need to traverse the rest of vector 2
            }
        }

    vector<vector<int>> ans;//Store the ans from pq
    while(!pq.empty()) {
        // pq.second has ith and jth element from 1st and 2nd array
        ans.push_back({pq.top().second.first, pq.top().second.second});
        pq.pop();
    }
    reverse(ans.begin(),ans.end());
    return ans;
}


// Kth largest element in a stream
class KthLargest {
    public:
    priority_queue<int, vector<int>, greater<int>> pq;
    int size;
    //T.C - O(NlogK)  S.C - O(K)
    KthLargest(int k, vector<int> nums) {
        size=k;
        for(int i=0;i<nums.size();i++) {
            pq.push(nums[i]);
            if(pq.size()>k) pq.pop();//we just have to keep k largest
        }
    }
    //T.C - O(logN)  S.C - O(1)
    int add(int val) {
        pq.push(val);//NOw pq size will exceed  k
        if(pq.size()>size) pq.pop();//Del the min ones to maintain k elements only in min heap
        return pq.top();//This will give min from pq i.e k largest
    }
};


// Smallest Range Covering Elements from K Lists
vector<int> smallestRange(vector<vector<int>>& nums) {
    // Brute force 1 -> Calculate all ranges in T.C O(N*N*K*K) an store the smallest range
    // Brute force 2 -> Place the pointers at start of every  list
    // Store min & max from those ptrs and get a range [min,max]
    // Now check for smallest range and include at least 1 num from k arrays
    // Now we cant inc max value(list is sorted),inc min value
    //T.C - O(n*k*k) S.C - O(K)
}
//Optimized Solution
// T.C - O(N)  S.C - O()
class Node{
    public:
    int data, row, col;
    Node(int d,int r,int c){
        data = d;
        row = r;
        col = c;
    }
};
class compare{
    public:
    bool operator()(Node* a, Node* b){
        return a->data > b->data;
    }
};
vector<int> smallestRange(vector<vector<int>>& nums){
    int mini = INT_MAX;
    int maxi = INT_MIN;

    priority_queue<Node*,vector<Node*>,compare> pq;

    //Step 1. Create min heap for start of each list and track mini/maxi
    for(int i=0;i<nums.size();i++){
        int element = nums[i][0];
        mini = min(mini,element);
        maxi = max(maxi,element);
        pq.push(new Node(element,i,0));
    }

    int start = mini, end = maxi;

    //Step 2. Process ranges
    while(pq.empty()){
        Node* temp = pq.top();
        pq.pop();
        mini = temp->data;//Extracted the min element value

        //If the range is smaller than prev range
        if(maxi - mini < end - start) {
            start = mini;
            end = maxi;
        }
        //If next element exists move one element ahead and push
        if(temp->col + 1 < nums.size()){
            maxi = max(maxi,nums[temp->row][temp->col + 1]);
            pq.push(new Node(nums[temp->row][temp->col+1],temp->row,temp->col));
        }
        else break;
    }
    return {start,end};
}


// Max Frequency Stack
//T.C - O(logN)  S.C - O(N)
class FreqStack {
    // pq wil store freq,pos in stack,value
    priority_queue<pair<int,pair<int,int>>>pq;//Max heap
    unordered_map<int,int> freq;
    int pos = 0;
    public:
    FreqStack() {}
    
    void push(int val) {
        //Filter on basis of count first,if count is same filter on base of pos
        //Hence the order freq,pos,val
        //When elements is pushed inc freq in map and inc pos and push in heap
        pq.push({freq[val]++,{pos++,x}});
    }
    
    int pop() {
        int val = pq.top().second.second;//Give me the most freq from max heap
        pq.pop();
        freq[val]--;//We popped the val once so reduce the freq in map
        return val;
    }
};


// Mth Smallest Number in K Sorted arrays
//T.C - O(M*logK) S.C - O(K)
typedef pair<int, pair<int, int> > ppi;
int mthLargestFromKSorted(vector<vector<int>>arr,int m){
    //Brute force -> Merge all the arrays and sort them to give mth smallest number

    priority_queue<ppi,vector<ppi>,greater<ppi>>pq;//Min heap
    for(int i=0;i<arr.size();i++) pq.push({arr[i][0],{i,0}});

    int count = 0;
    int i = 0,j = 0;//We need the pos when returning
    while(count < m && !pq.empty()){//We only need to run loop for m times
    ppi curr = pq.top();
    pq.pop();
     i = curr.second.first;//Array idx
     j = curr.second.second//Element idx

    if(j+1 < arr[i].size()) pq.push({arr[i][j+1],{i,j+1}});

    count++;
    }

    //We have reached the mth time
    // now i and j hold the array idx and element idx of mth smallest element
    return arr[i][j];
} 


// Maximize Capital IPO
//T.C - O(NlogN + K*N)  S.C - O(N)
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    priority_queue<int>pq;// top element = max profit among all projects with Capital<=W; 
    vector<pair<int,int>>projects; // to store index of projects

    //Store the capital and index in sorted order
    for(int i = 0;i<capital.size();i++) projects.push_back({capital[i],i});
    sort(projects.begin(),projects.end());

    int j = 0;//Project to do

    while(k--){ // v[j].first has the capital amt. and v[j].second has the project idx
        //There are still projects available and capital req is less than available
        while(j < capital.size() && projects[j].first <= w){
            pq.push(profits[projects[j].second]);//We'll do the project
            j++;//Move on the next project
        }

        if(!pq.empty()){
            //Extract the max profit and add upon the prev available capital
            w = w + pq.top();
            pq.pop();
        }
    }
    return ans;
}