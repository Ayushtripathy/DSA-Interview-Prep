//Search Binary Search Tree
// T.C - O(H)  S.C - O(1)
TreeNode* searchBST(TreeNode* rot,int val){
    if(!root) return NULL;

    if(root->val == val) return root;
    else if(root->val > val) return searchBST(root->left,val);
    else return searchBST(root->right,val);
}

// Ceil in a Binary Search Tree
//T.C - O(H)  S.C - O(1)
int findCeil(TreeNode* root,int key){
    int ceil = -1;
    while(root){
        if(root->data == key){
            ceil = root->data;//Found the given value itself
            return ceil;
        }
        if(root->data < key){
            root = root->right;
        }
        else{
            ceil = root->data;//Found a node greater than key
            root = root->left;//Now minimize the greatest node by going left 
        }
    }
    return ceil;
}

// Floor in a Binary Search Tree
//T.C - O(H)  S.C - O(1)
int findFloor(TreeNode* root,int key){
    int floor = -1;
    while(root){
        if(root->data == key){
            floor = root->data;//Found the given value itself
            return floor;
        }
        if(root->data > key){
            root = root->left;
        }
        else{
            floor = root->data;
            root = root->right;//Now maximise the greatest node by going right 
        }
    }
    return floor;
}


// Insert a given Node in Binary Search Tree
// T.C - O(H)  S.C - O(1)
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(!root) return new TreeNode(val);//Its the first node
    
    TreeNode* curr = root;

    while(true){
        if(val >= curr->val){
            if(curr->right) curr = curr->right;
            else{
                curr->right = new TreeNode(val);
                break;
            }
        }
        
        else{
            if(curr->left) curr = curr->left;
            else{
                curr->left = new TreeNode(val);
                break;
            }
        }
    }
    return root;
}


// Delete a Node in Binary Search Tree
// T.C - O(H)  S.C - O(1)
TreeNode* findLastRight(TreeNode* root){
    if(!root->right) return root;
    return findLastRight(root->right);
}
TreeNode* helper(TreeNode* root){
    //If one side is null then attach the available side tree to node
    if(!root->left) return root->right;
    else if(!root->right) return root->left;

    TreeNode* rightChild = root->right;
    TreeNode* lastRight = findLastRight(root->left);
    //Connect the rightmost node of left subtree to right child
    lastRight->right = rightChild;

    return root->left;
}
TreeNode* deleteNode(TreeNode* root, int key) {
    if(!root) return NULL;

    //If the root is the node to be deleted
    if(root->val == key) return helper(root);

    TreeNode* dummy = root;

    while(root){
        if(root->val > key){//We have to explore the left subtree
        //left child exists and it is the node to be deleted
        if(root->left && root->left->val == key){
            root->left = helper(root->left);
            break;
        }
        else root = root->left;
        }
        else{//WE have to explore the right subtree
        //Right child exists and it is the node to be deleted 
            if(root->right && root->right->val == key){
                root->right = helper(root->right);
                break;
            }
            else root = root->right;
        }
    }
    return dummy;
}


// K-th Smallest/Largest Element in BST
//T.C - O(min(K,N))  S.C - O(min(K,N))
void inorder(TreeNode* root, int& k,int &ans) {
    if (!root) return;

    inorder(root->left,k,ans);//We need smallest so check left

    //K is 0 so we have found our kth ans
    if (--k == 0) ans = root->val;

    inorder(root->right,k,ans);//Left doesn't give kth smallest so go right
}  
int kthSmallest(TreeNode* root, int k) {
    int ans;
    inorder(root,k,ans);
    return ans;
}
TreeNode* kthLargest(TreeNode* root,int &k){
	if(!root) return NULL;
	
	TreeNode* right=kthLargest(root->right,k);
	if(right!=NULL) return right;//If right side returns some largest element
	k--;

	if(k==0) return root;
	
	return kthLargest(root->left,k);
}


// LCA of a Binary Search Tree
// T.C - O(H)  S.C - O(1)
TreeNode* lcaBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root) return root;
    if(!p || !q) return NULL;

    //If both the nodes are smaller then go to left
    if ((root -> val > p -> val) && (root -> val > q -> val)) {
        return lcaBST(root -> left, p, q);
        }
    
    //If both the nodes are larger then go to right
    if ((root -> val < p -> val) && (root -> val < q -> val)) {
        return lcaBST(root -> right, p, q);
        }
    return root;    
}


// Check if a tree is a BST or BT
// T.C - O(N)  S.C - O(1)
bool isValidBST(TreeNode* root,TreeNode* minLeft=NULL,TreeNode* maxRight=NULL) {
    if(!root) return false;

    //If root is out of bounds at any point
    if(minLeft && root->val <= minLeft->val) return false;
    if(maxRight && root->val >= maxRight->val) return false;

    return isValidBST(root->left,minLeft,root) && isValidBST(root->right,root,maxRight);
}


// Construct a BST from a inorder traversal
//T.C - O(N)  S.C - O(1)
TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end){
    if(end<=start) return NULL; 

    int midIdx=(end+start)/2;

    TreeNode* root = new TreeNode(nums[midIdx]);

    root->left = sortedArrayToBST(nums, start, midIdx-1);
    root->right = sortedArrayToBST(nums, midIdx+1,end);

    return root;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBST(nums, 0,nums.size());
}


// Construct a BST from a preorder traversal
//T.C - O(3N)  S.C - O(1)
TreeNode* buildTree(vector<int>&preorder,int &idx,int upperBound){
    //If we've reached the end or exceeded the bound
    if(idx == preorder.size() || preorder[idx] > upperBound) return NULL;

    //Make the root of tree and increment the idx to nxt element of array
    TreeNode* root = new TreeNode(preorder[idx++]);
    //Make the root's left and pass the root's value as upperbound
    root->left = buildTree(preorder,idx,root->val);
    //Make the root's right and pass the same upperbound
    //When we go to right value is supposed to inc but it'll still be smaller than prev upperbound
    root->right = buildTree(preorder,idx,upperBound);

    return root;
}
TreeNode* bstFromPreorder(vector<int>& preorder) {
    int idx = 0;
    return buildTree(preorder,idx,INT_MAX);
}


// Construct a BST from a Level order traversal
//T.C - O(NlogN) S.C - O(N)
TreeNode* constructBST(TreeNode* root,int data){
    if(!root){
        root = new TreeNode(data);
        return root;
    }

    //If key is smaller than root then attach it to left side
    if(data <= root->val) root->left = constructBST(root->left,data);
    //If key is larger than root then attach it to right side
    else root->right = constructBST(root->right,data);

    return root;
}
TreeNode* bstFromLevelOrder(vector<int>& levelOrder) {
    if(levelOrder.size() == 0) return NULL;

    TreeNode* root = NULL;//Create new root and initialize from zero
    //For every element in array attach it to tree
    for(int i = 0; i < levelOrder.size();++i) root = constructBST(root,levelOrder[i]);

    return root;
}


// Pair sum in a BST
// Using inorder
// T.C - O(2N)  S.C - O(N)
void inorder(TreeNode* root,vector<int> &ans){
    if(root==NULL) return;
    inorder(root->left,ans);
    ans.push_back(root->val);
    inorder(root->right,ans);
}
bool findTarget(TreeNode* root, int k) {
    vector<int> ans;
    inorder(root,ans);
    int i=0,j=ans.size()-1;
    while(i<j){
        if(ans[i]+ans[j]==k) return true;
        else if(ans[i]+ans[j]<k) i++;
        else j--;
        }
    return false;    
}
//Using BST Iterator(Time O(1) & Space O(logN)
// T.C - O(N) S.C - O(2*H)
class BSTIterator {
    //If inorder storing is allowed - Store inorder and return elements
    stack<TreeNode*> st;
    bool reverse = true;// reverse true before -> reverse false next
    public:
    BSTIterator(TreeNode* root,bool isReverse) {
        reverse = isReverse;
        pushAll(root);//Pushes al left nodes to stack
    }
    
    int next() {
        TreeNode* temp = st.top();
        st.pop();
        if(!reverse) pushAll(temp->right);
        else pushAll(temp->left);
        return temp->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
    private:
    void pushAll(TreeNode* node) {
        while(node){
            st.push(node);
            if(reverse) node = node->right;
            else node = node->left;
        }
    }
};
bool findTarget(TreeNode* root, int k) {
    if(!root) return false;
    BSTIterator left = new BSTIterator(root,false); // It iterates from the next(left) nodes
    BSTIterator right = new BSTIterator(root,true);  //It iterates from the before(right) nodes

    //Now just do like two pointer approach
    int i = left.next();
    int j = right.next();
    while(i < j) {
        if(i + j == k) return true;
        else if(i + j < k) i = left.next();
        else j = right.next();
    }
    return false;
}


// Count BST nodes that lie in a given range
//T.C - O(H+k) S.C - O(1)
int getNodeCount(TreeNode* root,int low,int high){
    if(!root) return 0;
    //Special case
    if(root->data == high && root->data == low) return 1;

    //If curr node is in range,include it in count and recur for left and right children of it
    if(root->data <= high && root->data >= low){
        return 1 + getNodeCount(root->left,low,high) + getNodeCount(root->right,low,high);
    }

    //If curr node is smaller than low range discard let and recur for right
    else if(root->data < low) return getNodeCount(root->right,low,high);

    else return getNodeCount(root->left,low,high);
}


// Remove BST keys outside the given range
// T.C - O(N) S.C - O(1)
TreeNode* removeOutsideRange(TreeNode* root, int low,int high){
    if(!root) return NULL;

    //Remove outside range from left subtree
    root->left = removeOutsideRange(root->left,low,high);
    //Remove outside range from right subtree
    root->right = removeOutsideRange(root->right,low,high);

    //If root is outside range
    //If root is smaller than low req range
    if(root->key < low){
        //Whole left tree including root is invalid
        TreeNode* rChild = root->right;//Store the right side
        delete root;
        return rChild;
    }

     //If root is larger than high req range
    if(root->key > high){
        //Whole left tree including root is invalid
        TreeNode* lChild = root->left;//Store the left side
        delete root;
        return lChild;
    }
    //If root is in range then just simply return
    return root;
}		


// Inorder Successor/Predecessor in BST
//T.C - O(H)  S.C - O(1)
TreeNode* inorderSuccessor(TreeNode* root,TreeNode* p){
    TreeNode* successor = NULL;

    while(root){
        //If the value of given node is greater then discard the left tree and move right
        if(p->val >= root->val) root = root->right;
        else{ //Found a node greater than the req node
            successor = root;
            root = root->left;
        }
    }
    return successor;
}
TreeNode* inorderPredecessor(TreeNode* root,TreeNode* p){
    TreeNode* predecessor = NULL;

    while(root){
        //If the value of given node is smaller then discard the right tree and move left
        if(p->val <= root->val) root = root->left;
        else{ //Found a node smaller than the req node
            predecessor = root;
            root = root->right;
        }
    }
    return predecessor;
}


// Recover BST
//T.C - O(N)  S.C - O(1)
TreeNode* first;
TreeNode* prev;
TreeNode* middle;
TreeNode* last;
void inorder(TreeNode* root){
    if(!root) return;

    inorder(root->left);

    //There was a prev violation
    if(prev && (root->val < prev->val)){
        if(!first){ //For the first violation
            first = prev;
            middle = root;//In case we don't find 2nd violation we'll swap first and mid
        }
        else last = root;//For second violation
    }

    prev = root;

    inorder(root->right);
}
void recoverTree(TreeNode* root) {
    first = middle = last = NULL;//Initially
    prev = new TreeNode(INT_MIN);//First element in inorder is min
    inorder(root);
    //Found the violating elements so swap them
    if(first && last) swap(first->val, last->val);//For non adjacent
    else if(first && middle) swap(first->val, middle->val);//For adjacent
}


// Largest BST in Binary Tree
// T.C - O(N)  S.C - O(1)
class NodeValue{
    int maxNode,minNode,maxSize;
    NodeValue(int minNode,int maxNode,int maxSize){
        this->maxNode = maxNode;
        this->minNode = minNode;
        this->maxSize = maxSize;
    }
};
NodeValue largestBST(TreeNode* root){
    if(!root) return NodeValue(INT_MAX,INT_MIN,0);//Return empty BST

    //Get the no. of bst from left and right subtrees
    auto left = largestBST(root->left);
    auto right = largestBST(root->right);

    if(left.maxNode < root->val && root->val < right.minNode){
        //It is a valid BST
        //Pass the new min and new max and pass the tree size
        return NodeValue(min(root->val,left.minNode),max(root->val,right.maxNode),left.maxSize + right.maxSize + 1);
    }
    //If is not a valid BST
    return NodeValue(INT_MIN,INT_MAX,max(left.maxSize,right.maxSize));
}
int largestBSTSubtree(TreeNode* root){
    int largestSubTree = largestBST(root).maxSize;
}


// Count subtrees in a BST whose nodes lie within a given range
//T.C - O(N)  S.C - O(H)
bool getCount(TreeNode* root,int low,int high,int &count){
    if(!root) return true;//Null means in range

    //Check in both side subtrees whether they're in range
    bool left = getCount(root->left,low,high,count);
    bool right = getCount(root->right,low,high,count);

    if(left && right && root->data >= start && root->data <= end){
        ++count;//Increase count of valid bst in range
        return true;
    }
    return false;
}
int getCountBST(TreeNode* root,int low,int high){
    int count = 0;
    getCount(root,low,high,count);
    return count;
}


// Convert a binary tree to BST
// T.C - O(NlogN)  S.C - O(N)
void inorderSave(TreeNode* root,auto &set){
    if (!root) return;
 
    inorderSave(root->left, set);
    set.insert(root->data);
    inorderSave(root->right, set);
}
void convertToBSTHelper(TreeNode* root,auto &it){
    if(!root) return;

    //Do inorder traversal and change the values of tree
    convertToBSTHelper(root->left,it);
    root->data = *it;
    it++;
    convertToBSTHelper(root->right,it);
}
void convertToBST(TreeNode* root){
    // The set stores the elements in sorted order
    set<int> set;//Use multiset in case of duplicates
    inorderSave(root, set);

    //Set allows us to avoid sorting externally
    auto it = set.begin();//Runs an iterator to the 1st element of set
    convertToBSTHelper(root, it);
}


// Balance a Binary Search Tree
// T.C - O(N)  S.C - O(N)
TreeNode* balanceBST(TreeNode* root) {
    vector<int> inorderVal;

    storeInorder(root,inorderVal);

    return sortedArrayToBST(0,inorderVal.size() - 1,inorderVal);
}


// Merge two BST’s	
//T.C - O(N)  S.C - O(H)
void flattenToSortedDLL(TreeNode* root,TreeNode* head){
    if(!root) return;

    flattenToSortedDLL(root->right,head);

    root->right = head;

    if(head) head->left = root;

    head = root;

    flattenToSortedDLL(root->left,head);
}
TreeNode* sortedLLToBST(TreeNode* &head,int n){
    if(n <= 0 || !head) return NULL;

    TreeNode* left = sortedLLToBST(head,n/2);//Build the left subtree

    TreeNode* root = head;//Build the root of tree
    root->left = left;//Attach the left tree to left child of root
    head = head->next;//Move head

    root->right = sortedLLToBST(head,n-n/2-1);//Build the right subtree

    return root;
}
TreeNode* mergeTwoBST(TreeNode* root1,TreeNode* root2){
    //Brute force - Take Inorder of both trees,merge those arrays,sort it and then make a tree out of it

    //Step1. Convert both BST to DLL
    TreeNode* head1 = NULL;
    flattenToSortedDLL(root1,head1);
    head1->left = NULL;

    TreeNode* head2 = NULL;
    flattenToSortedDLL(root2,head2);
    head2->left = NULL;

    //Step2. Merge the two sorted LL into one linear tree
     Tree* head = _mergeTwoSortedLL(head1,head2);

     //Step3. Convert this LL to BST
     return sortedLLToBST(head,_countNodes(head));
}



// Find the median of BST in O(n) time and O(1) space
//T.C - O(N) S.C - O(1)
void helperMedian(TreeNode* root,TreeNode* &curr,TreeNode* &prev,int &cnt,int medianPart,int &flag){
    if(!root) return;
    //Do inorder traversal
    helperMedian(root->left,curr,prev,medianPart,flag);

    if(!prev){//We're encountering prev first time
        prev = root;//Make prev root
        cnt++;//Increase count
    }
    else if(cnt == medianPart){
        cnt++;
        curr = root;
        flag = 1;
        return;
    }
    else if(!flag){//Didn't find the median part
        cnt++;
        prev == root;
    }

    helperMedian(root->right,curr,prev,medianPart,flag);
}
float findMedianBST(TreeNode *root){
    //Brute - Find inorder and find median in array
    int count = 0;
    countNodes(root,count);//Count the nodes of tree
    TreeNode* curr = NULL;
    TreeNode* prev = NULL;

    int cnt = 1;
    int medianPart = (n/2) + 1;
    int flag = 0;

    helperMedian(root,curr,prev,cnt,medianPart,flag);

    if(count&1){//If count is odd
        float ans = curr->data*1.0;//Curr stores the median part for odd
        return ans;
    }
    else{//If count is even
        float ans = ((curr->data + prev->data)*1.0)/(2*1.0);//prev stores the n/2 part for even
        return ans;
    }
}


// Maximum Sum BST in Binary Tree
// T.C - O(N)  S.C - O()
class Node {
    bool isBST;//Keeps track of if tree(subtree) is bst
    int minVal, maxVal, sum;
};
Node helper(TreeNode *node, int &res) {
    //If node is null return default value
    if (!node) return { true, INT_MAX, INT_MIN, 0 };

    Node left = helper(node->left, res);//Get the left sum
    Node right = helper(node->right, res);//Get the right sum
    
    //If left and right both are BST and node value is in range
    if (left.isBST && right.isBST && left.maxVal < node->val && right.minVal > node->val) {
        //Calculate the sum
        int sum = left.sum + right.sum + node->val;
        res = max(res, sum);//Store the max sum

        //Return {[is a bst],[min val from curr and left,min val from curr and right],[sum]}
        return {true,min(left.minVal,node->val),max(right.maxVal,node->val),sum };
    }
    else return { false, 0, 0, 0 };
}
int maxSumBST(TreeNode* root) {
    int res = 0;
    helper(root, res);
    return res;
}


//Binary Search Tree to Greater Sum Tree
//T.C - O(N)  S.C - O(1)
void rev(TreeNode* root, int &sum){
    if(!root) return ;
        
    rev(root->right, sum);
	
    // The root value is continuously updated with the help of sum.
    root->val += sum;
	
    // And the count variable is changed so, that the next node in the traversal will be updated.
    sum = root->val;
    
    rev(root->left, sum);
}
TreeNode* bstToGst(TreeNode* root) {
	int sum = 0;
    rev(root, sum);
    return root;
}