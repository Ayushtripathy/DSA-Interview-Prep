//Search Binary Search Tree
// T.C - O(H)  S.C - O(1)
TreeNode* searchBST(TreeNode* rot,int val){
    if(!root) return NULL;

    if(root->val == val) return root;
    else if(root->val > val) return searchBST(root->left,val);
    else return searchBST(root->right,val);
}


// Remove BST keys outside the given range		
// Unique BSTs		
// Merge two BST’s		
// Fixing two nodes of a BST
