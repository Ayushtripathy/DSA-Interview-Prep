//Binary Trees
class TreeNode{
  public:
    int data;
    Node* left;
    Node* right;
};

//InOrder Tree Traversal(recursive)
// T.C - O(N) S.C - O(1) Stack space - O(N) Worst and O(logN) Best
void printInOrder(TreeNode* root){
    if (root == NULL) return;
 
    // Recur on left child
    printInOrder(root->left);
 
    //Print the data of root
    cout << root->data << " ";
 
    //Recur on right child
    printInOrder(root->right);
}
//PreOrder Tree Traversal(recursive)
// T.C - O(N) S.C - O(1) Stack space - O(N) Worst and O(logN) Best
void printPreOrder(TreeNode* root){
    if (root == NULL) return;
 
    //Print the data of root
    cout << root->data << " ";
 
    // Recur on left child
    printPreOrder(root->left);
 
    //Recur on right child
    printPreOrder(root->right);
}

//PostOrder Tree Traversal(recursive)
// T.C - O(N) S.C - O(1) Stack space - O(N) Worst and O(logN) Best
void printPostOrder(TreeNode* root){
    if (root == NULL) return;
 
    // Recur on left child
    printPostOrder(root->left);
 
    //Recur on right child
    printPostOrder(root->right);
 
    //Print the data of root
    cout << root->data << " ";
}


//InOrder Tree Traversal(Iterative)
// T.C - O(N) S.C - O(N) & O(logN) Best
vector<int> inOrderTraversal(TreeNode* root) {
    vector<int> inOrder;
    if(!root) return inOrder;

    stack<TreeNode*> st;
    TreeNode* curr = root;

     //Initially we wont push the root because we need the leftmost
    while(curr!=NULL || !st.empty()){
        if(curr){//Similar to recurring left
            st.push(curr);
            curr = curr->left;
        }
        else{//End of the left side
        if(st.empty()) break;
        curr = st.top();//Extracting the root and storing the val
        st.pop();
        inOrder.push_back(curr->val);//Similar to printing root val
        curr = curr->right;//Similar to recurring right
        }
    }
    return inOrder;
}


//PreOrder Tree Traversal(Iterative)
// T.C - O(N) S.C - O(N) & O(logN) Best
vector<int> preOrderTraversal(TreeNode* root) {
    vector<int> preOrder;
    if(!root) return preOrder;

    stack<TreeNode*> st;
    TreeNode* curr = root;
    st.push(curr);//Push initially because we node the first when we go left

    //We'll push right first and then left because of LIFO so left will pop first
    while(!st.empty()){
        curr = st.top();//Extracting the root and storing the val
        st.pop();
        preOrder.push_back(curr->val);//Similar to printing root val

        if(curr->right!){//Similar to recurring right
            st.push(curr->right);
        }

        if(curr->left!){//Similar to recurring left
            st.push(curr->left);
        }
    }
    return preOrder;
}


//PostOrder Tree Traversal(Iterative)
// T.C - O(N) S.C - O(N) & O(logN) Best
vector<int> preOrderTraversal(TreeNode* root){
      vector<int> postorder;
        if(root==NULL)
            return postorder;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty())
        {
            root=st.top();
            st.pop();
            postorder.push_back(root->val);
            if(root->left!=NULL)
                st.push(root->left);
            if(root->right!=NULL)
                st.push(root->right);      
        }
        reverse(postorder.begin(), postorder.end());
        return postorder;
}


//Preorder Inorder Postorder Traversals in One Traversal
//T.C - O(3N) S.C - O(4N)
vector<int>preInPostTraversal(TreeNode* root){
    if(!root) return;

    stack<pair<TreeNode*,int>>st;
    st.push({root,1});//Initially the root is preorder(1)
    vector<int> pre,in,post;

    while(!st.empty()){
        int node = st.pop();
        st.pop();

        //Preorder Traversal
        if(node.second == 1){//1 means preorder traversal
        pre.push_back(node.first->val);
        node.second++;//Make it inorder 1 -> 2
        st.push(node);//Push it again to be part of inorder
        if(node.first->left) st.push({node.first->left,1});
        }

        //Inorder Traversal
        else if(node.second == 2){//2 means inorder traversal
        in.push_back(node.first->val);
        node.second++;//Make it postorder 2 -> 3
        st.push(node);//Push it again to be part of postorder
        if(node.first->right) st.push({node.first->right,1});
        }

        //Postorder Traversal
        else{//Don't push back to stack or increment
            post.push_back(node.first->val);
        }
    }
}


// Level Order Traversal
//T.C- O(N)  S.C - O(N)
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;
        
    queue<TreeNode*> q;//To store the levels
    q.push(root);
        
    while(!q.empty()){
        int size = q.size();
        vector<int> level;
            
        for(int i=0;i<size;i++){
        TreeNode* node = q.front();
        q.pop();
                
        if(node->left) q.push(node->left);//Push the left childs

        if(node->right) q.push(node->right);// Push the right childs

        level.push_back(node->val);//Store the node of current level
        }
       res.push_back(level);//Push the level to final ans
    }
    return res;
}


// Zig-Zag or Spiral Traversal in Binary Tree
// T.C - O(N)  S.C - O(N)
vector<vector<int>> zigzagLevelOrder(TreeNode* root){
    vector<vector<int>> res;
    if(!root) return res;
        
    queue<TreeNode*> q;//TO store the levels
    q.push(root);
    bool zigzag = false;//TO check for alternate zigzag

    while(!q.empty()){
        int size = q.size();
        vector<int>level(size);

        for(int i=0;i<size;i++){
            TreeNode* curr = q.front();
            q.pop();

            int idx = zigzag ? i : size - 1 - i;
            level[idx] = curr->val;

            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
        //If this is the alternate level
        zigzag =  !zigzag;
        res.push_back(level);
    }
    return res;
}


// Diagonal Order Traversal
//T.C - O(N)  S.C - O(N)
vector<int> diagonalTraversal(TreeNode* root) {
    vector<int>ans;
    
    if(!root) return ans;
    
    queue<TreeNode*>q;
    q.push(root);
    
    while(!q.empty()){
            TreeNode* curr = q.front();
            q.pop();
      
            while(curr){
              //Here's the start(int left) for next diagonal
              if(curr->left) q.push(curr->left);//Push the left node for further nodes
              curr = curr->right;//Keep moving right to sum until the end of diagonal
              ans.push_back(curr->data);
            }
        }
    return ans;
}


// Morris Traversal
//T.C - O(N)  S.C - O(1)
vector<int> morrisTraversal(TreeNode* root){
    vector<int>inorder;
    TreeNode* curr = root;

    while(curr){
        if(!curr->left){
            inorder.push_back(curr->val);
            curr = curr->right;
        }
        else{
            TreeNode* prev = curr->left;
            while(prev->right && prev->right != curr) prev = prev->right;
            if(!prev->right){
                prev->right = curr;
                curr = curr->right;
            }
            else{
                prev->right = NULL;
                inorder.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    return inorder;
}


// Boundary Traversal Binary Tree
// T.C - O(H+H+N)  S.C - O(N)
bool isLeaf(TreeNode* root){
    if(!root) return false;
    if(!root->left && !root->right) return true;
    else return false;
}
void leftBoundary(TreeNode* root,vector<int> &ans){
    TreeNode* curr = root;
    while(curr){
        if(!isLeaf(root)) ans.push_back(curr->data);//It is the left most node and not a leaf
        if(curr->left) curr = curr->left;//Go to left nodes
        else curr = curr->right;//If there are no left nodes then go to right
    }
}
void rightBoundary(TreeNode* root,Vector<int> &ans){
    TreeNode* curr = root;
    stack<int>st;//taking a stack because we need right in reverse order
    while(curr){
        if(!isLeaf(root)) st.push(curr->data);
        if(curr->right) curr = curr->right;
        else curr = curr->left;
    }

    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
}
void addLeaves(TreeNode* root,vector<int> &ans){
    if(isLeaf(root)){//Traverse the tree and add the leaf nodes to ans
        res.push_back(root->data);
        return;
    }

    if(root->left) addLeaves(root->left,res);
    if(root->right) addLeaves(root->right,res);
}
vector<int> boundaryTraversal(TreeNode* root){
    vector<int>ans;
    if(!root) return ans;

    if(!isLeaf(root)) ans.push_back(root->data);//Push root to ans

    leftBoundary(root,ans);//Store the left most nodes excluding the leaves
    addLeaves(root,ans);//Store the leaf nodes
    rightBoundary(root,ans);//Store the right most nodes in reverse excluding the leaves

    return res;
}


// Vertical Order Traversal of Binary Tree
//T.C - O(NlogN)  S.C - O(3N) 
vector<vector<int>> verticalTraversal(TreeNode* root) {
    //Multiset -> allow duplicates and stores in sorted manner
    //NodeValue -> Vertical Level -> Level
    //Moving down Level++
    //Moving right verticalLevel++ else verticalLevel--;

    map<int,map<int,multiset<int>>>nodes;//verticalLevel->Level->Multiple Nodes
    queue<pair<TreeNode*,pair<int,int>>>todo;//Node->verticalLevel->Level
    todo.push({root,{0,0}});

    while(!todo.empty()){
        TreeNode* curr = todo.front().first;
        int x = todo.front().second.first;//Horizontal range goes from -a to +a
        int y = todo.front().second.second;//Vertical range goes from 0 to +a
        todo.pop();

        nodes[x][y].insert(curr->val);//Store in the multiset map

        if(curr->left) todo.push({curr->left,{x-1,y+1}});//X-1 going left & y+1 going down
        if(curr->right) todo.push({curr->right,{x+1,y+1}});//X-1 going right & y+1 going down
    }

    vector<vector<int>>ans;
    for(auto it : nodes){ //Traverse the map
        vector<int>verticalLevel;
        for(auto x : it.second){ //Traverse the multiset in the map
            verticalLevel.insert(verticalLevel.end(),x.second.begin(),x.second.end());
        }
        ans.push_back(verticalLevel);
    }
    return ans;
}


// Top View of Binary Tree
//T.C - O(N)  S.C - O(N)
vector<int>topView(TreeNode* root){
    vector<int>ans;
    if(!root) return ans;

    map<int, int> hash;//Store the levels and corresponding nodes in sorted order
    queue<pair<TreeNode*,int>>q;
    q.push({root,0});

    while (!q.empty()){
        TreeNode* curr = q.front().first;
        int verticalLevel = q.front().second;
        q.pop();

        //Store the first node for every vertical line
        if(hash.find(verticalLevel) == hash.end()){//Haven't encounter the node earlier
            hash[verticalLevel] = curr->val;
        }

        if(curr->left) q.push({curr->left,verticalLevel - 1});
        if(curr->right) q.push({curr->right,verticalLevel + 1});
    }

    for(auto it : hash){
        ans.push_back(it.second);
    }
    return ans;
}


// Bottom View of Binary Tree
//T.C - O(N)  S.C - O(N)
vector<int>bottomView(TreeNode* root){
    vector<int>ans;
    if(!root) return ans;

    map<int, int> hash;//Store the levels and corresponding nodes in sorted order
    queue<pair<TreeNode*,int>>q;
    q.push({root,0});

    while (!q.empty()){
        TreeNode* curr = q.front().first;
        int verticalLevel = q.front().second;
        q.pop();

        //Store the last level node on the line after overwriting the prev ones
        hash[verticalLevel] = curr->val;

        if(curr->left) q.push({curr->left,verticalLevel - 1});
        if(curr->right) q.push({curr->right,verticalLevel + 1});
    }

    for(auto it : hash){
        ans.push_back(it.second);
    }
    return ans;
}


// Binary Tree Left Side View
//T.C - O(N) S.C - O(H)
vector<int> leftView(TreeNode* root) {
    vector<int> res;
    if(!root) return res;
        
    queue<TreeNode*> q;//To store the levels
    q.push(root);
        
    while(!q.empty()){
        int size = q.size();
        res.push_back(q.front()->val);//Store the value on curr level
            
        while(size--){
        TreeNode* node = q.front();
        q.pop();
        
        //Push the left childs first because we need the left nodes to be in front of queue
        if(node->left) q.push(node->left);//Push the left childs

        if(node->right) q.push(node->right);// Push the right childs
        }
     }
    return res;
}


// Binary Tree Right Side View
//T.C - O(N) S.C - O(H)
vector<int> rightView(TreeNode* root) {
    vector<int> res;
    if(!root) return res;
        
    queue<TreeNode*> q;//To store the levels
    q.push(root);
        
    while(!q.empty()){
        int size = q.size();
        res.push_back(q.front()->val);//Store the value on curr level
            
        while(size--){
        TreeNode* node = q.front();
        q.pop();
        
        //Push the right childs first because we need the right nodes to be in front of queue
        if(node->right) q.push(node->right);//Push the right childs

        if(node->left) q.push(node->left);// Push the left childs
        }
     }
    return res;
}


//Maximum Depth in Binary Tree
//T.C - O(N)  S.C - O(1)
int maxDepthTree(TreeNode* root){
    if(!root) return 0;

    int lDepth = maxDepthTree(root->left);
    int rDepth = maxDepthTree(root->right);

    return 1 + max(lDepth, rDepth);
}


// Check for Balanced Binary Tree
//T.C - O(N)  S.C - O(N)
bool isBalanced(TreeNode* root){
    if(!root) return true;

    int lh = maxDepthTree(root->left);//Calculate left height
    int rh = maxDepthTree(root->right);//Calculate right height

    //In any case the left and right node should have ht. diff of at most 1
    if(abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right)) return true;
    return false;
}


// Diameter of Binary Tree(longest path b/w 2 nodes)
//T.C - O(N)  S.C - O(N)
int heightTree(TreeNode* root,int maxDia){
    if(!root) return 0;

    int lh = heightTree(root->left,maxDia);
    int rh = heightTree(root->right,maxDia);

    //Check if curr node gives the largest dist
    int maxDia = max(lh + rh,maxDia);

    //Return that side's height
    return 1 + max(lh,rh);
}
int diameterTree(TreeNode* root){
    int maxDia = 0;
    heightTree(root,maxDia);
    return maxDia;
}


//Count Leaf Nodes
// T.C - O(N) S.C - O(N)
int countLeafNodes(TreeNode* root){
    if(!root) return 0;

    //Found a leaf node
    if(!root->left && !root->right) return 1;

    //Not a leaf node but return the leaves from left and right
    else return countLeafNodes(root->left) + countLeafNodes(root->right);
}


// Sum of Left Leaves
//T.C - O(N) S.C - O(N)
void leftLeafSumUtil(TreeNode* root,int &res, int direction){
    if(!root) return;
        
    // leaf node
    if(!root->left && root->right){
    // left leaf
        if(direction == 0)
            res += root->val;
            return;
        }
        
    leftLeafSumUtil(root->left, 0); // 0 means left direction
    leftLeafSumUtil(root->right, 1); // 1 means right direction
}
int sumOfLeftLeaves(TreeNode* root) {
    int res = 0;
    leftLeafSumUtil(root,res, -1);
    return res;
}


// Check it two trees are Identical or Not
//T.C - O(N) S.C - O(N)
bool isIdentical(TreeNode* root1,TreeNode* root2) {
    if(!root1 || !root2) return (root1 == root2);

    //Return if values of root are equal and left and right portions are same
    return (root1->value == root2->val) && isIdentical(root1->left,root2->left) && isIdentical(root1->right,root2->right)
}


// Maximum Path Sum in Binary Tree
// T.C - O(N)  S.C - O(N)
int maxPathUtil(TreeNode* node,int &maxSum){
    if(!node) return 0;

    int leftSum = max(0,maxPathUtil(node->left,maxSum));//Taking max with 0
    int rightSum = max(0,maxPathUtil(node->right,maxSum));//To avoid negative sum

    int maxSum = max((leftSum + rightSum + node->val),maxSum);

    return (node->val + max(leftSum,rightSum));//Whichever path has max sum from left and right 
}
int maxPathLeafUtil(TreeNode* node,int &maxSum){
    if(!node) return 0;
    //If its a leaf node
    if(!root->left && !root->right) return root->data;

    int leftSum = max(0,maxPathUtil(node->left,maxSum));//Taking max with 0
    int rightSum = max(0,maxPathUtil(node->right,maxSum));//To avoid negative sum

    //If its not a leaf node
    if(root->left && root->right) {
        int maxSum = max((leftSum+rightSum+node->val),maxSum);
        return (node->val + max(leftSum,rightSum));//Whichever path has max sum from left and right 
    }

    //If any of the child is null
    return (!root->left) ? rightSum + root->data : leftSum + root->data;
}
int maxPathSum(TreeNode* root){
    //Similar to diameter of tree
    int maxSum = INT_MIN;
    maxPathUtil(root,maxSum);
    return maxSum;
}


// Binary Tree Path Sum(Root to leaf)
//T.C - O(N)  S.C - O(1)
bool hasPathSum(TreeNode* root,int targetSum){
    if(!root) return false;

    //If we are at leaf node
    if(!root->left && !root->right) return ((root->val - targetSum) == 0);//Found the target sum

    //Recur to both sides and check for the rem sum(val-sum) on either sides
    return hasPathSum(root->left,(targetSum - root->val)) || hasPathSum(root->right,(targetSum - root->val));
}


// Check for Symmetrical Binary Trees
//T.C - O(N)  S.C - O(N)
bool isSymmetricUtil(TreeNode* left, TreeNode* right){
    if(!left && !right) return true;

    else if(!left || !right) return left == right;

    else if(left->val != right->val) return false;

    return isSymmetricUtil(left->left,right->right) && isSymmetricUtil(left->right,right->left);
}
bool isSymmetric(TreeNode* root) {
    if(!root) return true;
    return isSymmetricUtil(root->left,root->right);
}


// Print Root to Node Path in Binary Tree
//T.C - O(N)  S.C - O(H)
bool getPath(TreeNode*root,int node,vector<ans>&path){
    if(!root) return false;//If we reach any left or right which gives null
    path.push_back(root->val);//Add the root to path

    if(root->val == node) return true;//Found the node

    //Either of left or right gives the path to the node
    if(getPath(root->left,node,path) || getPath(root->right,node,path)) return true;

    //No path found further
    path.pop_back();//Remove the last pushed element 
    return false;
}
vector<int> rootToNodePath(TreeNode *root,int node){
    vector<int>path;//To store the path
    if(!root) return path;

    getPath(root,node,path);
    return path;
}


// Lowest Common Ancestor in Binary Tree
// T.C - O(N) S.C - O(1)
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root) return NULL;

    if(!p || !q) return NULL;//If any 1 of them is null

    //Root itself is one of the childs
    if(root == p || root == q) return root;//Found one of the req nodes

    int leftAncestor = lowestCommonAncestor(root->left,p,q);//Check for the lca in left
    int rightAncestor = lowestCommonAncestor(root->right,p,q);//Check for the lca in right

    if(leftAncestor && rightAncestor) return root;//Left an right both have a successor

    if(leftAncestor) return leftAncestor;//Whichever one gives not null return that
    else return rightAncestor;
}


// Maximum Width of Binary Tree
//T.C - O(N)  S.C - O(N)
int getMaxWidth(TreeNode* root){
    if (!root) return 0;
 
    int result = 0;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int n = q.size();//Higher the level/queue size, higher the width
        result = max(n, result);
 
        for(int i=1;i<=n;i++){
            TreeNode* temp = q.front();
            q.pop();
            
            if (temp->left != NULL) q.push(temp->left);
            if (temp->right != NULL) q.push(temp->right);
        }
    }
    return result;
}
//For including Null values
int widthOfBinaryTree(TreeNode* root) {
    if(!root) return 0;
    unsigned int maxWidth = 0;
    queue<pair<TreeNode*, int>> q;
    q.push({root,1});
    while(!q.empty()) {
        unsigned int l = q.front().second;
        unsigned int r = l; // right started same as left
        int size = q.size();
        while(size--){
            TreeNode* node = q.front().first;
            r = q.front().second;
            q.pop();
                
            if (node->left) q.push({node->left,r*2});
            if (node->right) q.push({node->right,r*2 + 1});
        }
        maxWidth = max(maxWidth,(r + 1 - l));
    }
    return maxWidth;
}


// Sums of all the Diagonals Binary Tree
//T.C - O(N)  S.C - O(N)
vector<int> diagonalSum(TreeNode* root) {
    vector<int>ans;
    
    if(!root) return ans;
    
    queue<TreeNode*>q;
    q.push(root);
    
    while(!q.empty()){
        int size = q.size();
        int sum = 0;
        vector<int> temp;
        while(size--){
            TreeNode* curr = q.front();
            q.pop();
      
            while(curr){
              sum += curr->data;
              if(curr->left) q.push(curr->left);//Push the left node for further nodes
              curr = curr->right;//Keep moving right to sum until the end of diagonal
            }
        }
        ans.push_back(sum);
    }
    return ans;
}


// Children Sum Property in Binary Tree 
// T.C - O(N)  S.C - O(H)
void changeSumTree(TreeNode* root){
    if(!root) return;
    int childSum = 0;
    //Add both the child's value to sum 
    if(root->left) childSum += root->left->data;
    if(root->right) childSum += root->right->data;

    //If child nodes have greater sum than parent node replace parent
    if(childSum >= root->data) root->data = childSum;
    else{ // If child nodes have less sum than parent
        if(root->left) root->left->data = root->data;
        if(root->right) root->right->data = root->data;
    }

    //Recur further in left and right
    changeSumTree(root->left);
    changeSumTree(root->right);

    //This part is for when we return from recursion
    int totalSum = 0;
    if(root->left) totalSum += root->left->data;
    if(root->right) totalSum += root->right->data;
    //Replace the parent root with child total sum
    if(root->left || root->right) root->data = totalSum;
}


// Check If Binary Tree is Sum Tree Or Not
//T.C - O(N)  S.C - O(H)
int checkSum(TreeNode* root,int &flag){
    if(!root) return 0;

    //If it's a leaf node just return its own value(it has no child)
    if(!root->left && !root->right) return root->val;

    if(flag == 0) return 0;//Flag will be false if it doesn't follow sum property

    //Recur in both sides to check sum property
   int left = checkSum(root->left);
   int right = checkSum(root->right);

   //If the sum from right and left children is not equal to parent
   if(left + right != root->val) flag = 0;//make the flag false
   
   // Send the left & right sum along with node value as for the upper parent whole left tree is left sum
   return left + right + root->val;
}
bool isSumTree(TreeNode* root) {
   int flag = 1;
    checkSum(root,flag);
    return flag;
}


// Convert a given Binary Tree to SumTree
// T.C - O(N)  S.C - O(1)
int convertSumTree(TreeNode* root){
    if(!root) return 0;

    int rootValue = root->val;//Store the original value to return along with child sum

    //Store the left and right children sum in root
    root->val = convertSumTree(root->left) + convertSumTree(root->right);

    //return the original root value and sum
    return root->val + rootValue;
}


// Print all the Nodes at a distance of K in Binary Tree
// T.C - O(N+N)  S.C - O(3N)
void markParents(TreeNode* root,unordered_map<TreeNode*,TreeNode*>&parent,TreeNode* target){
    queue<TreeNode*>q;
    q.push(root);//Initially push the root
    while(!q.empty()){//Normal BFS(level order traversal)
        TreeNode* curr = q.front();
        q.pop();

        if(curr->left){
            parent[curr->left] = curr;//parent[leftchild] = curr node
            q.push(curr->left);
        }
        if(curr->right){
            parent[curr->right] = curr;
            q.push(curr->right);
        }
    }
}
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    unordered_map<TreeNode*, TreeNode*> parent;
    markParents(root,parent,target);

    //vis is req for when the node goes in all dir it will encounter its parent again which is already accounted for
    queue<TreeNode*>q;
    q.push(target);//We have to start traversing from target node
    unordered_map<TreeNode*,bool> visited;
    visited[target] = true;//When we encounter this node again we'll skip it
    int curr_level = 0;

    //BFS again to go to k nodes from target
    while(!q.empty()){
        int size = q.size();
        if(curr_level++ == k) break;//We have reached nodes at distance k
        while(size--){//For a level
            TreeNode* curr = q.front();
            q.pop();
            if(curr->left && !visited[curr->left]){//Node has left child and we haven't visited it before
                q.push(curr->left);
                visited[curr->left] = true;//when we encounter this node again we'll skip it
            }
            if(curr->right && !visited[curr->right]){
                q.push(curr->right);
                visited[curr->right] = true;
            }
            //IF the node has a parent and the parent node hasn't been visited
            if(parent[curr] && !visited[parent[curr]]){
                q.push(parent[curr]);
                visited[parent[curr]] = true;
            }
        }
    }

    vector<int>ans;//To store the ans
    while(!q.empty()){//Elements remaining in the queue will be the ans
    TreeNode* node = q.front();
    q.pop();
    ans.push_back(node->val);
    }
    return ans;
}


// Count total Nodes in a Complete Binary Tree
//T.C - O(log^2 N)  S.C - O(logN)
int rightHeight(TreeNode* root){
    int ht = 0;
    while(root){
        ht++;
        root = root->right;
    }
    return ht;
}
int leftHeight(TreeNode* root){
    int ht = 0;
    while(root){
        ht++;
        root = root->left;
    }
    return ht;
}
int countNodes(TreeNode* root) {
    if(!root) return 0;

    //Calculate the left and right tree heights to apply formula(2^h-1)
    int lh = leftHeight(root);
    int rh = rightHeight(root);

    //If the heights are equal then its a CBT and apply the formula to count nodes(2^h-1) without traversing further
    if(lh == rh) return (1<<lh) - 1;//(x<<y -> x2^y)

    //If ht. are unequal its not a CBT and traverse to left and right + 1(curr node)
    return 1 + countNodes(root->left) + countNodes(root->right);
}


// Minimum time taken to BURN the Binary Tree from a Node
// T.C - O(N+N)  S.C - O(4N)
int findMaxDistance(map<TreeNode*,TreeNode*>&parent,TreeNode* burningPoint){
    queue<TreeNode*>q;
    q.push(burningPoint);

    map<TreeNode*,bool>vis;
    vis[burningPoint] = true;
    int burnTime = 0;

    while(!q.empty()){
        int size = q.size();
        int flag = 0;
        while(size--){
            TreeNode* node = q.front();
            q.pop();
            if(node->left && !vis[node->left]){
                flag = 1;//Able to burn
                vis[node->left] = true;
                q.push(node->left);
            }
            if(node->right && !vis[node->right]){
                flag = 1;
                vis[node->right] = true;
                q.push(node->right);
            }
            if(parent[node] && !vis[parent[node]]){
                flag = 1;
                vis[parent[node]] = true;
                q.push(parent[node]);
            }
        }
        if(flag) burnTime++;//After every level we can check whether we were able to burn adj nodes or not;
    }
    return burnTime;
}
TreeNode* markParents(TreeNode* root,map<TreeNode*,TreeNode*>&parent,int start){
    queue<TreeNode*>q;
    q.push(root);//Initially push the root
    TreeNode* res;
    while(!q.empty()){//Normal BFS(level order traversal)
        TreeNode* curr = q.front();
        if(curr->data == start) res = curr;
        q.pop();

        if(curr->left){
            parent[curr->left] = curr;//parent[leftchild] = curr node
            q.push(curr->left);
        }
        if(curr->right){
            parent[curr->right] = curr;
            q.push(curr->right);
        }
    }
    return res;
}
int timeToBurnTree(TreeNode* root, int start) {
    map<TreeNode*,TreeNode*> parents;
    //Map parents to nodes and return the from which we have to start burning tree
    TreeNode* burningPoint = markParents(root,parents,start);

    return findMaxDistance(parent,burningPoint);
}


// Construct a Binary Tree from Preorder and Inorder Traversal
//T.C - O(N)  S.C - O(N)
TreeNode* treeHelper(vector<int>&preorder,vector<int>& inorder,int preS,int preE,int inS,int inE){
    if(inS > inE || preS > preE) return NULL;//Inorder & Preorder start and end overlap

    int rootData = preorder[preS];//The root is at 0th idx of preorder
    rootIndex = -1;//Now we have to find the root in inorder array
    for(int i=inS;i<=inE;++i){
        if(inorder[i] == rootData){
            rootIndex = i;//Found the idx in inorder
            break;
        }
    }

    //Now allot the indices to left and right portions inorder as well as preorder
    int leftInStart = inS;//Inorder has the leftmost nodes in start
    int leftInEnd = rootIndex - 1;//Root is in middle to left portion will end before it
    int rightInStart = rootIndex + 1;//After the root the right portion starts
    int rightInEnd = inE;

    int leftPreStart = preS + 1;//We start from +1 idx because the 0th idx has root
    int leftPreEnd = leftInEnd - leftInStart + leftPreStart;//Because the length to left portion will be same in pre as well as post order
    int rightPreStart = leftPreEnd + 1;
    int rightPreEnd = preE;

    //Now make the new root node
    TreeNode *root = new TreeNode(rootData);

    //Now go to left and build the tree
    root->left = treeHelper(preorder,inorder,leftPreStart,leftPreEnd,leftInStart,leftInEnd);
    //Now go to right and build the tree
    root->right = treeHelper(preorder,inorder,rightPreStart,rightPreEnd,rightInStart,rightInEnd);

    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int preE = preorder.size();
    int inE = inorder.size();
    return treeHelper(preorder,inorder,0,preE-1,0,inE-1);
}


// Construct a Binary Tree from Postorder and Inorder Traversal
//T.C - O(N)  S.C - O(N)
TreeNode* treeHelper(vector<int>&postorder,vector<int>& inorder,int postS,int postE,int inS,int inE){
    if(inS > inE || postS > postE) return NULL;//Inorder & Postorder start and end overlap

    int rootData = postorder[postE];//The root is at nth idx of postorder
    int rootIndex = -1;//Now we have to find the root in inorder array
    for(int i=inS;i<=inE;++i){
        if(inorder[i] == rootData){
            rootIndex = i;//Found the idx in inorder
            break;
        }
    }

    //Now allot the indices to left and right portions inorder as well as postorder
    int leftInStart = inS;//Inorder has the leftmost nodes in start
    int leftInEnd = rootIndex - 1;//Root is in middle to left portion will end before it
    int rightInStart = rootIndex + 1;//After the root the right portion starts
    int rightInEnd = inE;

    int leftPostStart = postS;
    int leftPostEnd = leftInEnd - leftInStart + leftPostStart;//Because the length to left portion will be same in post as well as in order
    int rightPostStart = leftPostEnd + 1;
    int rightPostEnd = postE - 1;//Because the last idx has root

    //Now make the new root node
    TreeNode *root = new TreeNode(rootData);

    //Now go to left and build the tree
    root->left = treeHelper(postorder,inorder,leftPostStart,leftPostEnd,leftInStart,leftInEnd);
    //Now go to right and build the tree
    root->right = treeHelper(postorder,inorder,rightPostStart,rightPostEnd,rightInStart,rightInEnd);

    return root;
}
TreeNode* buildTree(vector<int>& postorder, vector<int>& inorder) {
    int postE = postorder.size();
    int inE = inorder.size();
    return treeHelper(postorder,inorder,0,postE-1,0,inE-1);
}


// Serialize and De-serialize Binary Tree
//T.C - O(N)  S.C - O(N)
// Encodes a tree to a single string
string serialize(TreeNode* root) {
    if(!root) return "";
    
    string str;
    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if(!node) str = str + "#,";//Append the null node as #
        else{//Here we don't check left and right individually
            //If a node exists then we have to push the children to queue whether its null or not
            q.push(node->left);
            q.push(node->right);
            str = str + to_string(node->val) + ",";//Append the node val to ans string
        }
    }
    return str;
}
// Decodes your encoded data to tree
TreeNode* deserialize(string data) {
    if(data.length() == 0) return NULL;//If string is empty

    stringstream s(data);//Allows the string to be iterated as objects
    string str;
    getline(s,str,',');//Iterate the string elements differentiated by a separator

    TreeNode* root = new TreeNode(stoi(str));//Make new root from str
    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty()){
        TreeNode* curr = q.front();
        q.pop();

        //Get the str object to make left root of tree
        getline(s,str,',');
        if(str == '#') curr->left = NULL;//If left child is null
        else{
            //Create the new node
            TreeNode* leftNode = new TreeNode(stoi(str));
            curr->left = leftNode;//Append the left child
            q.push(leftNode);//Push in queue the left child
        }

        //Get the str object to make right root of tree
        getline(s,str,',');
        if(str == '#') curr->right = NULL;//If right child is null
        else{
            //Create the new node
            TreeNode* rightNode = new TreeNode(stoi(str));
            curr->right = rightNode;//Append the right child
            q.push(rightNode);//Push in queue the right child
        }
    }
    return root;
}


// Flatten a Binary Tree to Linked List
//Optimized Solution
//T.C - O(N)  S.C - O(1)
void flatten(TreeNode* root){
    if(!root) return;

    TreeNode* curr = root;
    while(curr){
        if(curr->left){//If the left node exists
           TreeNode* prev = curr->left;//Go the root's left node
           while(prev->right) prev = prev->right;////Now traverse to the left tree's rightmost node
           prev->right = curr->right;
           curr->right = curr->left;
           curr->left = NULL;
        }
        curr = curr->right;
    }
}


// Count Paths for a Sum
//T.C - O(N*N)  S.C - O(1)
// Recursive Solution
void countPaths(TreeNode* root,int sum,int &paths){
    if(!root) return;
    if(root->val == sum) paths++;//Found a path with target sum

    countPaths(root->left,sum - root->val,paths);//find paths in left for rem sum
    countPaths(root->right,sum + root->val,paths);//find paths in right for rem sum
}
int pathSum(TreeNode* root,int sum){
    if(!root) return 0;
    int paths = 0;

    countPaths(root,sum,paths);//Count the paths from root
    pathSum(root->left,sum);//Now count the paths from left child
    pathSum(root->right,sum);//Now count the paths from right child

    return paths;
}
//Optimized Solution
//T.C - O(N)  S.C - O(N)
void dfs(TreeNode* root,unordered_map<int,int> seen,int &sum,int partialSum = 0) {
    // updating partialSum with the current node
    partialSum += root->val;
    // checking if we already found an interval summing up to that
    res += seen[partialSum - sum];
    seen[partialSum]++;// updating seen
    // searching potential left and right branches
    if (root->left) dfs(root->left, partialSum);
    if (root->right) dfs(root->right, partialSum);
    // clearing seen of the last value, for backtracking purposes
    seen[partialSum]--;
}
int int pathSum(TreeNode* root, int int targetSum) {
    int res = 0, sum;
    unordered_map<int,int> seen;
    sum = targetSum;
    // seen set with initial value 0 will help us match from the root
    seen[0] = 1;
    if (!root) return res;
    dfs(root,seen,sum);
    return res;
}


// Level Averages in a Binary Tree
// T.C - O(N) S.C - O(N)
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> ans;
    if(!root) return ans;
    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        double levelSum = 0;
        for(int i=0;i<size;i++){
            TreeNode* curr = q.front();
            q.pop();
            levelSum += curr->val;
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
            }
        double avg = levelSum/size;
        ans.push_back(avg);
        }
    return ans;
}


// Level Order Successor of a node
//T.C - O(N)  S.C - O(N)
TreeNode* levelOrderSuccessor(TreeNode* root,TreeNode* key){
    if(!root) return NULL;

    //Edge cases
    if(root == key){//Find successor of root itself
      if(root->left) return root->left;
      else if(root->right) return root->right;
      else return NULL;
    }

    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty()){
        TreeNode* currNode = q.front();
        q.pop();

        if(currNode->left) q.push(currNode->left);
        if(currNode->right) q.push(currNode->right);

        if(currNode == key) break;//If the node extracted from queue is the key node
    }
    return q.front();//front of queue contains the next element of key node in the level
}


// Sum Root to Leaf Numbers
//T.C - O(N)  S.C - O(H)
int findSum(TreeNode* root,int sumDigitNodes){
    if(!root) return 0;
    //Either we're in left or right traversal
    //The more we traverse on a side the more we increase the digits place
    sumDigitNodes = sumDigitNodes*10 + root->val;

    //If its a leaf node
    if(!root->left && !root->right) return sumDigitNodes;

    return findSum(root->left,sumDigitNodes) + findSum(root->right,sumDigitNodes);
}
int sumNumbers(TreeNode* root) {
    return findSum(root,0);
}


// Path With Given Sequence
// T.C - O(N)  S.C - O(H)
bool dfs(TreeNode* root,vector<int>&arr,int idx){
    if(idx > arr.size()) return false;//Out of bounds

    //Either the root is null or the root value is not in array idx
    if(!root || root->val != arr[idx]) return false;

    //If idx is at end of array check root is leaf or not
    //If its last node then root should be leaf
    if(idx == arr.size() - 1) return !root->left && !root->right;
    
    //Check for the rest of the arr sequence in left and right children
    return dfs(root->left,arr,idx + 1) || dfs(root->right,arr,idx + 1);
}
bool isValidSequence(TreeNode* root, vector<int>& arr) {
    if (!root) return arr.size() == 0;
    return dfs(root, arr, 0);
}


// Connect Level Order Siblings
// T.C - O(N)  S.C - O(1)
TreeNode* connect(TreeNode* root) {
    if(!root) return root;

    TreeNode* anchor = root;//This node will keep going left to give head of level
    while(anchor && anchor->left){
        TreeNode* runner = anchor;//This node wil traverse the nodes in linear fashion in a level
        while(true){
            runner->left->next = runner->right;//Connect left node to right node
            if(!runner->next) break;//Runner has no next node so can't access null
            runner->right->next = runner->next->left;
            runner = runner->next;//Traverse the level just like a linked list
        }
        anchor = anchor->left;//Move to next level and start a new runner 
    }
    return root;
}


// All Paths for a Sum(Upto leaves)
//T.C - O(N) S.C - O(H)
void findPaths(TreeNode* root, int sum, vector<int>& path, vector<vector<int> >& paths){
    if(!root) return;

    path.push_back(root->val);//Root is part of one of my paths

    //If its a leaf node(req) and sum has now become equal to curr node value then this is one of the paths
    if(!root->left && !root->right && sum == root->val) paths.push_back(path);

    //Find in left and right path with rest of the sum
    findPaths(root->left, sum - root->val, path, paths);
    findPaths(root->right, sum - root->val, path,paths);

    //While returning remove from path because now its not a part of path and we'll explore some other node
    path.pop();
}
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int> > paths;
    vector<int> path;
    findPaths(root, sum, path, paths);
    return paths;
}


// Binary Tree Paths
//T.C - O(N)  S.C - O(H)
void treePathHelper(TreeNode* root,vector<string>&ans,string curr){
    if(!root->right && !root->left){
        curr += to_string(root->val);
        ans.push_back(curr);
        return;
    }
         
    string s = to_string(root->val) + "->";
    if(root->left && !root->right){
        curr += s;
        treePathHelper(root->left,ans,curr);
    }
        
    else if(!root->left && root->right){
        curr += s;
        treePathHelper(root->right,ans,curr);
    }
    else{
        curr += s;
        treePathHelper(root->left,ans,curr);
        treePathHelper(root->right,ans,curr);
    }
}
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
    treePathHelper(root,ans,"");
    return ans;
}


// Even Odd Tree
//T.C - O(N)  S.C - O(N)
bool isEvenOddTree(TreeNode* root) {
    if(!root) return false;

    queue<TreeNode*>q;
    q.push(root);
    int level = 0;

    while(!q.empty()){
        int size = q.size();
        int prev = level%2 == 0 ? 0 : INT_MAX;//Store the prev node in a given level
        while(size--){
            auto node = q.front();
            q.pop();

            if(level%2 == 0){//If its an even level
            //For even level nodes should be odd and strictly increasing
            if(node->val%2 == 0 || node->val <= prev) return false;
            }
            else{
            //For odd level nodes should be even and strictly decreasing
            if(node->val%2 == 1 || node->val >= prev) return false;
            }

            prev = node->val;

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        level++;
    }
    return true;
}


// Check if given graph is tree or not
//T.C - O(N+Even) S.C - O(N)
bool cycleDFS(int node, int parent, vector<int> adj[], vector<int> &vis){
    vis[node] = 1;//Mark visited
    for (auto it : adj[node]){//TRaverse neighbors
        if (!vis[it]){//Not visited yet
            if (cycleDFS(it, node, adj, vis)) return true;//Check further for cycle
        }
        else if (it != parent) return true;//Only parent could mark the node visited
    }
    return false;
}
bool checkTree(int V,vector<int> adj[]){
    // An undirected graph is tree if :
    // 1) There is no cycle. 
    // 2) The graph is connected.
    vector<int> visited(V,0);
    //Check for cycle
    if(cycleDFS(0,-1,adj,visited)) return false;
    //Check if any node is unvisited(not connected)
    for (int u = 0; u < V; u++){
        if (!visited[u]) return false;
    }
    return true;
}


// Find distance between 2 nodes in a Binary tree
//T.C - O(2N)  S.C - O(2H)
int findLevel(TreeNode* root,int k ,int level){
    if(!root) return -1;
    if(root->val == k) return level;//Found the key at this level;

    int left = findLevel(root->left,k,level+1);//Find the key in left subtree & increment level(going 1 lvl down)
    //Didn't find the key in left subtree so go right
    if(left == -1) return findLevel(root->right,k,level+1);

    return left;
}
int findDistance(TreeNode* root,int a,int b){
    // Intuition - Find Lca and then dist of both nodes from lca
    TreeNode* lca = lowestCommonAncestor(root,a,b);

    //Finds the level at which a is(dist from lca)
    int dist1 = findLevel(lca,a,0);
    //Finds the level at which b is(dist from lca)
    int dist2 = findLevel(lca,b,0);

    //Add the 2 dist for dist b/w a and b
    return dist1 + dist2;
}