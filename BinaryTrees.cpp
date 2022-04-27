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

// Level Order Traversal
//T.C- O(N)  S.C - O(N)
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;
        
    queue<TreeNode*> q;//TO store the levels
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



// Reverse Level Order Traversal : LC 107
// Level Averages in a Binary Tree : LC 637
// Minimum Depth of a Binary Tree : LC 111, LC 104
// Level Order Successor 
// Connect Level Order Siblings (medium): LC 117
// Problem Challenge 1
// Problem Challenge 2: LC 199
// Binary Tree Path Sum : LC 112
// All Paths for a Sum (medium): LC 113, LC 257
// Sum of Path Numbers (medium): LC 129
// Path With Given Sequence (medium): LC 1430
// Count Paths for a Sum (medium): LC 437
// Problem Challenge 1: LC 543
// Problem Challenge 2: LC 124