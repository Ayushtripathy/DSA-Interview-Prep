// Implement Trie 1
class TrieNode {
  public:
    vector<TrieNode*> dict;//Trie has arr of 26 chars
    bool isEnd;//Flag that tells us if word exists
    TrieNode(){//Ini the constructor
        isEnd = false;
        dict.resize(26, nullptr);
    }
};
class Trie {    
    public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();//Create the root node
    }

    // T.C - O(word len)
    void insert(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store does not exist in trie yet
            if(node->dict[word[i] - 'a'] == NULL){
                //Store the char in dict on next newly created Trie node
                node->dict[word[i] - 'a'] = new TrieNode();
            }
            node = node->dict[word[i] - 'a'];//Move the newly created Trie node
        }
        node->isEnd = true;//Marks the end of the word
    }

    // T.C - O(len)
    bool search(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char doesn't exist in trie
            if(node->dict[word[i] - 'a'] == NULL) return false;
            node = node->dict[word[i] - 'a'];//Move to the next trie node
        }
        //When we reach the end of word(if it exists) it'll be true else false
        return node->isEnd;
    }

    // T.C - O(len)
    // Returns if there is any word in the trie that starts with the given prefix
    bool startsWith(string prefix) {
        TrieNode* node = root;//Start with the root
        for(int i = 0; i < prefix.length(); i++){
            //The char doesn't exist in trie
            if(node->dict[prefix[i] - 'a'] == NULL) return false;
            node = node->dict[prefix[i] - 'a'];//Move to the next trie node
        }
        return true;//We are still at a trie node that means the prefix exists
    }
};


// Implement Trie 2
class TrieNode {
    public:
    TrieNode* dict[26];//Trie has arr of 26 chars
    int cntEndWith = 0;//Tells the words ending with str
    int cntPrefix = 0;//Tells the words starting with str
};
class Trie {
    private:
    TrieNode* root;
    public:
    Trie() {
        root = new TrieNode();//Create the root node
    }

    // T.C - O(word len)
    void insert(string &word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store does not exist in trie yet
            if(node->dict[word[i] - 'a'] == NULL){
                //Store the char in dict on next newly created Trie node
                node->dict[word[i] - 'a'] = new TrieNode();
            }
            node = node->dict[word[i] - 'a'];//Move the newly created Trie node
            //Prefix will be incremented in the new(next) trie
            node->cntPrefix++;//There is a word with this prefix(curr word)
        }
        node->cntEndWith++;//Marks the end of the word(There exists a word)
    }
    
    // T.C- O(word len)
    int countWordsEqualTo(string &word){
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store exists in trie
            if(node->dict[word[i] - 'a'] != NULL){
                node = node->dict[word[i] - 'a'];//Move the next Trie node
            }
            else return 0;//No word exists equal to given word(All chars need to match)
        }
        //We're at the end of word so return the count of words ending with given word
        return node->cntEndWith;
    }
    
    // T.C- O(word len)
    int countWordsStartingWith(string &word){
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store exists in trie
            if(node->dict[word[i] - 'a'] != NULL){
                node = node->dict[word[i] - 'a'];//Move the next Trie node
            }
            else return 0;//No prefix exists equal to given prefix(All chars need to match)
        }
        //We're at the end of prefix so return the count of prefix ending with given prefix
        return node->cntPrefix;
    }
    
    // T.C- O(word len)
    void erase(string &word){
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store exists in trie
            if(node->dict[word[i] - 'a'] != NULL){
                node = node->dict[word[i] - 'a'];//Move the next Trie node
                node->cntPrefix--;
            }
            else return;//No word exists to erase
        }
        //We're at the end of word so return the count of words ending with given word
        return node->cntEndWith--;
    }
};


// Complete String
// T.C - O(N*wordlen) + (N*wordlen)
class TrieNode {
  public:
    vector<TrieNode*> dict;//Trie has arr of 26 chars
    bool isEnd;//Flag that tells us if word exists
    TrieNode(){//Ini the constructor
        isEnd = false;
        dict.resize(26, nullptr);
    }
};
class Trie {    
    TrieNode* root;
    public:
    Trie() {
        root = new TrieNode();//Create the root node
    }

    // T.C - O(word len)
    void insert(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store does not exist in trie yet
            if(node->dict[word[i] - 'a'] == NULL){
                //Store the char in dict on next newly created Trie node
                node->dict[word[i] - 'a'] = new TrieNode();
            }
            node = node->dict[word[i] - 'a'];//Move the newly created Trie node
        }
        node->isEnd = true;//Marks the end of the word
    }

    // T.C - O(word len)
    bool checkPrefixExist(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store exists in trie
            if(node->dict[word[i] - 'a'] != NULL){
                //Move to the next trie node
                node = node->dict[word[i] - 'a'];
                //Reference node's prev should be true(prev words should end)
                if(node->isEnd == false) return false;
            }
            else return false;//Trie doesn't contain the word
        }
        return true;//Marks the end of the word
    }
};
string completeString(int n, vector<string> &a){
    Trie* trie = new Trie();//Create a trie
    for(auto &it:a) trie->insert(it);//Insert all strings to trie

    string longest = "";//To store the longest string
    for(auto &it:a){//For all strings in array
       if(trie->checkPrefixExist(it)){//Check if all prefixes exist for the curr string
           if(it.length() > longest.length()) longest = it;
           else if(it.length() == longest.length() && it < longest) longest = it;
       }
    }
    if(longest == "") return "None";
    return longest;
}


//Number of Distinct Substrings in a String
// T.C - O(N^2)  S.C - O()
struct TrieNode {
  TrieNode * links[26];

  bool containsKey(char ch) {
    return (links[ch - 'a'] != NULL);
  }

  TrieNode * get(char ch) {
    return links[ch - 'a'];
  }

  void put(char ch, TrieNode * Trienode) {
    links[ch - 'a'] = node;
  }
};
int countDistinctSubstrings(string & s) {
    TrieNode * root = new TrieNode();
    int count = 0;
    int n = s.size();
    
    for (int i = 0; i < n; i++) {
        TrieNode * node = root;
        for (int j = i; j < n; j++) {
            //If char doesn't exist make a new trie node and increase count
            if (!node->containsKey(s[j])) {
                node->put(s[j], new TrieNode());
                count++;//only increase when new node is made
            }
            node = node->get(s[j]);//Move to next trie node
        }
    }
    return count + 1;//Include empty substring too
}


// Maximum XOR of Two Numbers in an Array
// T.C - O(N*32 + M*32)  S.C - O(?)
class TrieNode {
  public:
    TrieNode* dict;//Trie has 0 and 1 values
    TrieNode(){//Ini the constructor
        dict.resize(2, nullptr);
    }
};
class Trie {
    private:  
    TrieNode* root;
    public:
    Trie() {
        root = new TrieNode();//Create the root node
    }

    // T.C - O(word len)
    void insert(int num) {
        TrieNode* node = root;
        for(int i = 31; i>=0; i--){
            int bit = (num >> i) & 1;//Extract the last set bit
            //The bit we need to store does not exist in trie yet
            if(node->dict[bit] == NULL){
                //Store the bit in dict on next newly created Trie node
                node->dict[bit] = new TrieNode();
            }
            node = node->dict[bit];//Move the newly created Trie node
        }
    }

    // T.C - O(word len)
    bool findMax(int num) {
        TrieNode* node = root;
        int maxHere = 0;//Initial 00000 and we'll switch acc to req
        for(int i = 31; i>=0; i--){
            int bit = (num >> i) & 1;//Extract the last set bit
            //If the trie does contain the opposite bit(We need opp bit to get max xor)
            if(node->dict[!bit] != NULL){
                maxHere |= (1 << i);//Set the ith bit(flip bits in maxHere)
                node node->dict[!bit];//Move the next trie node of !bit
            }
            //No need to set the bit just take 0 
            else node = node->dict[bit];//Move the next trie node of bit
        }
        return maxHere;
    }
};
int findMaximumXOR(vector<int>& nums) {
    Trie trie;//Create a trie 
    int ans = 0;
    for(auto it : nums) {//For each element
        //insert the bits of that num into trie
        trie.insert(it);
        //Calculate the max of xor value for that element
        ans = max(ans, trie.findMax(it));
    }
    return ans;
}


//  Maximum XOR With an Element From Array
vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
    // Step 1
    // T.C - O(NlogN)
    sort(nums.begin(),nums.end());
    
    // Step 2
    //Store the queries and sort acc to a[i](prev queries will always be in trie)
    vector<pair<int,pair<int,int>>> offlineQueries;
    int q = queries.size();
    for(int i=0;i<q;i++){
        offlineQueries.push_back({queries[i][1],{queries[i][0],i}});
    }
    // T.C - O(QlogQ)
    sort(offlineQueries.begin(),offlineQueries.end());
    
    // Step 3
    vector<int>ans(q,0);
    int ind = 0;
    int n = nums.size();
    Trie trie;
    // T.C - O((Q+N)*32)
    for(int i=0;i<q;i++){
        //Extract all 3 parts of the query
        int ai = offlineQueries[i].first;
        int xi = offlineQueries[i].second.first;
        int qInd = offlineQueries[i].second.second;

        //Traverse the array and push elements into trie which are smaller than ai
        while(ind < n && nums[ind] <= ai){
            trie.insert(nums[ind]);
            ind++;
        }

        //Store in qInd to restore the original order of queries
        if(ind == 0) ans[qInd] = -1;//No one in array was smaller than ai
        else ans[qInd] = trie.findMax(xi);//Get max xor for for all queries ands store in ans
    }
    return ans;
}


// Pattern Searching using Trie(Doubt???)
// T.C - O()  S.C - O()
class TrieNode{
    private:
    TrieNode *children[256] = {NULL};
    list<int> *indexes;
    public:
    TrieNode(){
        // Create an empty linked list for indexes of suffixes starting from this node
        indexes = new list<int>;
    }
 
    // A recursive function to insert a suffix of the txt in subtree rooted with this node
    void insertSuffix(string s, int index){
        // Store index in linked list
        indexes->push_back(index);
        
        // If string has more characters
        if (s.length() > 0){
            // Find the first character
            char cIndex = s.at(0);
            
            // If there is no edge for this character, add a new edge
            if (!children[cIndex]) children[cIndex] = new SuffixTrieNode();
            // Recur for next suffix
            children[cIndex]->insertSuffix(s.substr(1), index+1);
        }
    }
 
    // A function to search a pattern in subtree 
    list<int>* search(string s){
        // If all characters of pattern have been processed,
        if (s.length() == 0) return indexes;
        
        // if there is an edge from the current node of suffix trie, follow the edge.
        if (children[s.at(0)]) return (children[s.at(0)])->search(s.substr(1));
        
        else return NULL; // If there is no edge, pattern doesn’t exist in text
    }
};
class Trie{
    private:
    TrieNode root;
    public:
    // Constructor (Builds a trie of suffixes of the given text)
    Trie(string txt){
        // Consider all suffixes of given string and insert
        // them into the Suffix Trie using recursive function
        // insertSuffix() in TrieNode class
        for (int i = 0; i < txt.length(); i++)
            root.insertSuffix(txt.substr(i), i);
    }
 
    // Function to searches a pattern in this suffix trie.
    void search(string pat){
    // Let us call recursive search function for root of Trie.
    // We get a list of all indexes (where pat is present in text) in
    // variable 'result'
    list<int> *result = root.search(pat);
 
    // Check if the list of indexes is empty or not
    if (result == NULL) cout << "Pattern not found" << endl;
    else{
       list<int>::iterator i;
       int patLen = pat.length();
       for (i = result->begin(); i != result->end(); ++i)
         cout << "Pattern found at position " << *i - patLen<< endl;
    }
    }
};


// Auto Complete Feature using Trie(Doubt???)
// T.C - O()  S.C - O()
class TrieNode {
  public:
    vector<TrieNode*> dict;//Trie has arr of 26 chars
    bool isEnd;//Flag that tells us if word exists
    TrieNode(){//Ini the constructor
        isEnd = false;
        dict.resize(26, nullptr);
    }
};
class Trie {    
    public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();//Create the root node
    }


    // T.C - O(word len)
    void insert(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char we need to store does not exist in trie yet
            if(node->dict[word[i] - 'a'] == NULL){
                //Store the char in dict on next newly created Trie node
                node->dict[word[i] - 'a'] = new TrieNode();
            }
            node = node->dict[word[i] - 'a'];//Move the newly created Trie node
        }
        node->isEnd = true;//Marks the end of the word
    }


    // T.C - O(len)
    bool search(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            //The char doesn't exist in trie
            if(node->dict[word[i] - 'a'] == NULL) return false;
            node = node->dict[word[i] - 'a'];//Move to the next trie node
        }
        //When we reach the end of word(if it exists) it'll be true else false
        return node->isEnd;
    }
    

    // Returns 0 if current node has a child 
    // If all children are NULL, return 1. 
    bool isLastNode(TrieNode* root) { 
        for (int i = 0; i < ALPHABET_SIZE; i++){
            if (root->children[i]) return 0; 
        }
        return 1; 
    } 
    

    // Recursive function to print auto-suggestions for given node
    void suggestionsRec(TrieNode* root, string currPrefix) { 
        // found a string in Trie with the given prefix 
        if (root->isEnd){ 
		cout << currPrefix; 
		cout << endl; 
        } 
        
        // All children struct node pointers are NULL 
        if (isLastNode(root)) return; 
        
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (root->dict[i]) { // append current character to currPrefix string 
            currPrefix.push_back(97 + i); 
			suggestionsRec(root->dict[i], currPrefix); // recur over the rest 
            } 
        } 
    }
    
    
    // print suggestions for given query prefix. 
    int printAutoSuggestions(TrieNode* root, const string query) { 
        TrieNode* node = root; 
        
        // Check if prefix is present & find the the node (of last level) with last char of given str 
        int n = query.length(); 
        for(int level = 0; level < n; level++) { 
            int index = CHAR_TO_INDEX(query[level]); 
            // no string in the Trie has this prefix 
            if (!node->dict[index]) return 0; 
            node = node->dict[index]; 
        } 
        
        // If prefix is present as a word. 
        bool isWord = (node->isEnd == true); 
        
        // If prefix is last node of tree (has no children) 
        bool isLast = isLastNode(node); 
        
        // If prefix is present as a word, but there is no subtree below the last matching node. 
        if (isWord && isLast) { 
            cout << query << endl; 
            return -1; 
        } 
        
        // If there are are nodes below last matching character. 
        if (!isLast){ 
            string prefix = query; 
            suggestionsRec(node, prefix); 
            return 1; 
        } 
    } 

};