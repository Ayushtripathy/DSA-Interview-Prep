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
//T.C - O(NlogK) S.C - O(K)
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
// Top 'K' Frequent Numbers
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
struct MyComp {
    bool operator() (const pair<int, string>& a, const pair<int, string>& b) {
        if(a.first != b.first) return a.first > b.first;//If word count is not equal return the more freq
        else return a.second < b.second;//If the count is equal return the smallerr one
    }
};


// Frequency Sort
//T.C - O()  S.C - O()
string frequencySort(string s) {}


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


// 'K' Closest Points to the Origin  LC 973
// Sum of all elements between k1’th and k2’th smallest elements
// Smallest Number Range  LC 632
// Merge k sorted arrays LC 23
// Kth Smallest Number in a Sorted Matrix  LC 378
// Find median in a stream LC 295
// K Pairs with Largest Sums  LC 373
// Kth largest element in a stream LC 703
// Rearrange String  LC 767
// Rearrange String K Distance Apart  LC 358
// Scheduling Tasks  LC 621
// Frequency Stack LC 895
// Sliding Window Median  LC 480
// Maximize Capital  LC 502
// Next Interval  LC 436
// Mth Smallest Number in K Sorted arrays 
// Maximum distinct elements after removing k elements


