//Implementation of Stack(Arrays)
int main(){
    int arr[5];
    int top = -1;
    
    void push(int x){
        arr[++top] = x;
    }
    
    void pop(){
        top--;
    }

    int top(){
        return arr[top];
    }

    int size(){
        return top + 1;
    }

    bool isEmpty(){
        return top == -1;
    }
}

//Implementation of Stack(Linked List)
//T.C - O(1)
void stackLL(){
    class Node{
    int data;
    Node* next;
    };

    Node* top = NULL;
    
    void push(int data){
        Node* temp = new Node();
        if(!temp) exit(1);
        
        temp->data = data;
        temp->next = top;
        top = temp;
    }
    
    int isEmpty(){
    //If top is NULL it means that
    //there are no elements are in stack
    return top == NULL;
    }
    
    int peek(){
    // If stack is not empty , return the top element
    if (!isEmpty()) return top->data;
    else exit(1);
    }
        
    void pop(){
    Node* temp;
    if(!top) exit(1);
    else{
        temp = top;
        top = top->next;
        free(temp);
        }
    }
}


//Implementation of Stack(Queues)
//Using Two Queues
//T.C - O(N) S.C - O(N)
int main(){
    void push(x){
        q2.push(x);
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop()
        }
        swap(q1, q2);
    }

    void pop(){
        q1.pop();
    }

    int top(){
        return q1.front();
    }
}
//Using Single Queue
//T.C - O(N) S.C - O(N)
int main(){
    void push(x){
       q1.push(x);
       for(int i=0; i<q1.size()-1; i++){
           q1.push(q1.front());
           q1.pop();
       }
    }

    void pop(){
        q1.pop();
    }

    int top(){
        return q1.front();
    }
}


//Valid Parentheses
//T.C - O(N) S.C - O(N)
bool isValidParentheses(string str){
    stack<char> st;
    if(str.length() == 0) return true;
    if(str.length() == 1) return false;

    for(int i=0; i<str.length(); i++){
        char c = str[i];
        //If c is a closing bracket
        if(c == '}'|| c == ')' || c == ']'){
            //If there wasn't any opening bracket for this
            if(st.empty()) return false; 
            //If i took out } from string but there wasn't a { in stack
            if(c == '}' && stack.top() != '{') return false;
            if(c == ')' && stack.top() != '(') return false;
            if(c == ']' && stack.top() != '[') return false;
            st.pop();
        }
        //If c is an opening bracket
        else st.push(c);
    }
    if(stack.empty()) return true;
    return false;
}


//Next Greater Element
//T.C - O(2N) + O(2N) S.C - O(N)
//For circular array i = i%n
vector<int> nextGreaterElements(vector<int>& nums,int n){
    vector<int>ans(n);
    stack<int>st;
    //Traverse from the end
    for(int i=0; i<2n-1; ++i){
        //Remove any smaller elements in stack
        while(!st.empty() && arr[i%n] >= st.top()) st.pop();
        //Remaining element would be next greater
        if(!st.empty()) ans[i] = st.top();
        else ans[i] = -1; //No element greater is present
        st.push(arr[i%n]);
    }
    return ans;
}
vector<int> nextSmallerElements(vector<int>& nums,int n){
    vector<int>ans(n);
    stack<int>st;
    //Traverse from the end
    for(int i=0; i<2n-1; i++){
        //Remove any greater elements in stack
        while(!st.empty() && arr[i%n] <= st.top()) st.pop();
        //Remaining element would be next smaller
        if(!st.empty()) ans[i] = st.top();
        else ans[i] = -1; //No element greater is present
        st.push(arr[i%n]);
    }
    return ans;
}


//Reverse a Stack(Recursion)
//T.C - O(N^2)  S.C - O(N)
void insertAtBottom(stack<int>&st,int element){
    if(st.empty()){//Whenever stack gets empty insert the element in bottom
        st.push(element);
        return;
    }
    int el = st.top();
    st.pop();
    insertAtBottom(st,element);

    st.push(el);//After the recur call insert the el into stack
}
void reverseStack(stack<int> &stack){
    if(stack.empty()) return;
    
    int top = stack.top();
    stack.pop();
    reverseStack(stack);
    insertAtBottom(stack,top);
}


//Sort a stack(Recursion)
//T.C - O(N^N)  S.C - O(N)
void sortedInsert(stack<int> &st, int element){
    if(st.empty() || element > st.top()){
        st.push(element);
        return;
    }

    int el = st.top();
    st.pop();
    sortedInsert(st,element);
    st.push(el);
}
void sortStack(stack<int> &st){
    if(st.empty()) return;
    
    int top = st.top();
    st.pop();
    sortStack(st);
    sortedInsert(st,top);
}


//Stock Span Problem
//T.C - O(N)  S.C - O(N)
vector<int> stockSpan(int price[],int size){
    vector<int>output(size,0);
    stack<int>st;
    st.push(0);//Push the first element index
    output[0] = 1;//Default value is 1

    for(int i = 1;i<size;i++){
        //Remove all the prices lesser than current price in stack
        while(!st.empty() && price[st.top()] < price[i]){
            st.pop();
        }
        // If stack becomes empty, then price[i] is greater than all elements on left of it,
        // Else price[i] is greater than elements after top of stack
        output[i] = (st.empty()) ? (i + 1) : (i - st.top());
        st.push(i);
    }
    return output;
}


//Celebrity Problem
//T.C - O(N) S.C - O(N)
//Stack Based
bool MATRIX[N][N] = {{0, 0, 1, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 0},
                    {0, 0, 1, 0}};
bool knows(int a, int b) return MATRIX[a][b];
int findCelebrity(int n){
    stack<int>st;
    //Push all elements to stack
    for(int i = 0; i < n;i++) st.push(i);

    //Extract 2 people and check which one can be celebrity
    while(st.size() > 1){
        int a = st.top();
        st.pop();
        int b = st.top();
        st.pop();
        //A can't be celebrity
        if(knows(a,b)) st.push(b);
        //B can't be celebrity
        else st.push(a);
    }

    if(st.empty()) return -1;

    int celeb = st.top();//Celeb acc. to us
    st.pop();

    for(int i =0; i<n;++i){
        //Everybody knows celeb and celeb doesn't know anyone
        if(i != celeb && (knows(celeb,i)) || !knows(i,celeb)) return -1;
    }
    return celeb;
}


//LRU Cache
//T.C - O(1)
//Use Hashmap and DLL -> Head->MRUNode->Node->Node->LRUNode->Tail 
class LRUCache{
    public
    //Implement the DLL;
    class Node{
        int key;
        int val;
        Node* prev;
        Node* next;
        Node(int _key,int val){
            key = _key;
            val = _val;
        }
    };

    Node* head = new(-1,-1);
    Node* tail = new(-1,-1);
    //Capacity of cache
    int cacheCapacity;
    unordered_map<int,Node*>map;//Store key and node address
    LRUCache(int capacity){
        cacheCapacity = capacity;
        head->next = tail;
        tail->prev = head;
    }

    void addNode(Node* newNode){
        Node* temp = head->next;
        newNode->next = temp; 
        newNode->prev = head;
        head->next = newNode;
        temp->prev = newNode;
    }

    void deleteNode(Node* delNode){
        //Store the next and prev nodes
        Node* delPrev = delNode->prev;
        Node* delNext = delNode->next;
        //Make them point to each other
        delPrev->next = delNext;
        delNext->prev = delPrev;
    }

    int get(int key){
        //Found the key in map
        if(map.find(key) != map.end()){
            Node* resNode = map[key];//Value at key(address of node)
            int ans = resNode->val;
            map.erase(key);//Remove from the map
            deleteNode(resNode);
            addNode(resNode);//Add again as it becomes recently used now
            map[key] = head->next//Store the new address
            return ans;
        }
        return -1;
    }

    void put(int key, int value){
        if(map.find(key) != map.end()){//Node already exists
        Node* existingNode = map[key];
        map.erase(key);
        deleteNode(existingNode);
        }
        if(map.size() == cacheCapacity){//If size is exceeded
            map.erase(tail->prev->key);//Remove node from map
            deleteNode(tail->prev);//Delete the node just before tail
        }
        addNode(new Node(key,value));//Add new node
        map[key] = head->next;//Store the address of node
    }
};


//Largest Area Histogram
//T.C - O(N^3)  S.C - O(1)
//Brute Force
int largestRectangleArea(vector<int> &heights) {
  int max_area = 0;

  for (int i = 0; i < heights.size(); i++) {//First bar
    for (int j = i; j < heights.size(); j++) {//Second Bar
      int min_height = INT_MAX;
      //Find height of the shortest bar lying between them
      for (int k = i; k <= j; k++) {
        min_height = min(min_height, heights[k]);
      }
      //Also store the max area
      max_area = max(max_area, min_height * (j - i + 1));
    }
  }
  return max_area;
}
//Stack Based
//T.C - O(3N)  S.C - O(3N)
int largestRectangleArea(vector<int> &heights){
    stack<int>st;
    int leftSmall[heights.size()];
    int rightSmall[heights.size()];

    //Next smaller element to left
    for(int i = 0; i < heights.size(); i++){
        //Remove the greater elements from stack
        while(!st.empty() && heights[st.top()] >= heights[i]) st.pop();

        if(st.empty()) leftSmall[i] = 0;
        else leftSmall[i] = st.top() + 1;
        st.push(i);
    }

    //Next smaller element to right
    for(int i = heights.size() - 1; i >= 0; i--){
        //Remove the greater elements from stack
        while(!st.empty() && heights[st.top()] >= heights[i]) st.pop();

        if(st.empty()) rightSmall[i] = heights.size() - 1;
        else rightSmall[i] = st.top() - 1;
        st.push(i);
    }

    //Calculate max area
    int maxArea = 0;
    for(int i=0;i< heights.size(); i++){
        int currArea = heights[i]*(rightSmall[i] - leftSmall[i] + 1);
        maxArea = max(maxArea,currArea);
    }
    return maxArea;
}
//Most Optimized
//T.C - O(2N)  S.C - O(N)
int largestRectangleArea(int* heights,int size){
    stack<int>st;
    int maxArea = 0;

    for(int i = 0; i < size;++i){
        //Found a smaller element in stack
        while(!st.empty() && (i == size || heights[st.top()] >= heights[i])){
            int height = heights[st.top()];//Right smaller
            st.pop();
            int width;
            if(st.empty()) width = i;
            else width = i - st.top() - 1;//RS - LS - 1
            maxArea = max(maxArea, width * height);
        }
        st.push(i);
    }
    return maxArea;
}


//Max Rectangle in Binary Matrix with all 1's
//T.C - O(N*M) S.C - O(M)
int maxAreaMatrix(int M[MAX][MAX],int n,int m){
    //Compute area for 1'st row
    int area = largestRectangleArea(M[0],m);

    //Start from 2nd row
    for(int i=1;i<n;++i){
        for(int j=0;j<m;++j){
            //Update row by adding prev row's value
            if(M[i][j] != 0) M[i][j] += M[i-1][j]; 
            else M[i][j] = 0;//If row value is zero
        }
        //Row is updated now 
        area = max(area,largestRectangleArea(M[i],m))
    }
    return area;
}


//Expression contains redundant bracket or not
//T.C - O(N)  S.C - O(N)
bool findRedundantBrackets(string &str){
    stack<char> st;
    for(int i = 0;i<str.length();++i){
        //Push the operators and opening braces
        if(str[i] != ')') st.push(str[i]);
        else if(str[i] == ')') {//Found a closing bracket
            bool isRedundant = true;
            //Until we find an opening bracket
            while(st.top() != '('){
                //If an operator was between open and close braces(no redundant)
                if(st.top() == '+' || st.top() == '-' || st.top() == '*' || st.top() == '/') isRedundant = false;
                st.pop();//Pop the operators
            }
            //If no operator was found between the brackets
            if(isRedundant) return true;
            st.pop();//Pop the closing bracket we found in else if
        }
    }
    return false;
}


//Minimum Cost to Make String Valid
//T.C - O(N) S.C - O(N)
int findMinCost(string str){
    //For odd braces
    if(str.length()%2 != 0) return -1;
    stack<char> st;

    for(int i=0; i<str.length();++i){
        if(str[i] == '(') st.push(str[i]);
        else{
            //For removing valid braces
            if(!st.empty() && st.top() == '(') st.pop();
            else st.push(str[i]);
        }
    }

    //For the remaining invalid braces
    int a = 0,b = 0;
    while(!st.empty()){
        if(st.top() == '(') b++;
        else a++;
        st.pop();
    }
    int cost = (((a+1) >> 1) + ((b+1) >> 1));
    return cost;
}


//Design a Stack that supports getMin() in O(1) time and space.
//T.C - O(1) S.C - O(1)
class SpecialStack {
    // Define the data members.
    stack<int>st;
    int mini = INT_MAX;
    public: 
    void push(int data) {
        // Implement the push() function.
        if(st.empty()){//For 1st element
            st.push(data);
            mini = data;
        }
        else{
            if(data < mini){
                st.push(2*data - mini);
                mini = data;
            }
            else st.push(data);
        }
    }

    int pop() {
        // Implement the pop() function.
        if(st.empty()) return -1;

        int curr = st.top();
        st.pop();
        if(curr > mini) return curr;
        else{
            int prevMin = mini;
            int val = 2*mini - curr;
            mini = val;
            return prevMin;
        }
    }

    int top() {
        // Implement the top() function.
        if(st.empty()) return -1;

        int curr = st.top();
        if(curr < mini) return mini;
        else return curr;
    }

    bool isEmpty() {
        // Implement the isEmpty() function.
        return st.empty();
    }

    int getMin() {
        // Implement the getMin() function.
        if(st.empty()) return -1;

        return mini;
    }  
};
class MinStack {
    stack<pair<int, int>> st;
    public:    
    void push(int val) {
        int minimum;
        if(st.empty()) minimum = val;//First time pushing in stack
        else minimum = min(val,st.top().second);//Keep track of min
        st.push({val,minimum});//Push the el with curr min
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
     return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};


//Merge Overlapping Intervals
//T.C - O(NlogN) S.C - O(N)
bool cmp(vector<int>v1,vector<int>v2){
    return v1[0] < v2[0];
}
void mergeOverlappingIntervals(vector<vector<int>>& intervals){
    sort(intervals.begin(), intervals.end(),cmp);//Sort by first value
    stack<vector<int>>st;
    st.push(intervals[0]);//Push the first interval

    for(int i=1; i<intervals.size();++i){
        vector<int>currMeet = intervals[i];
        vector<int>lastMeet = st.top();

        if(lastMeet[1] >= currMeet[0]){
            st.pop();
            vector<int>merged = {lastMeet[0],max(lastMeet[1],currMeet[1])};
            st.push(merged);
        }
        else st.push(currMeet);
    }
    stack<vector<int>>newSt;
    while(st.size() > 0){
        newSt.push(st.top());
        st.pop();
    }

    while(newSt.size() > 0){
        vector<int>finalMeet = newSt.top();
        newSt.pop();
        cout<<finalMeet[0]<<" "<<finalMeet[1]<<" "<<endl;
    }
}


//Evaluation of Postfix expression
int postfixEvaluation(string str){
    stack<int>st;
    for(int i=0;i<str.length();i++){
        //If its a number
        if(str[i] >= '0' && str[i] <= '9') st.push(str[i] - '0');
        else{//If its a operator
            int op2 = st.top();
            st.pop();
            int op1 = st.top();
            st.pop();

            switch(str[i]){
                case '+':
                st.push(op1 + op2);
                break;
                case '-':
                st.push(op1 - op2);
                break;
                case '*':
                st.push(op1 * op2);
                break;
                case '/':
                st.push(op1 / op2);
                break;
                case '^':
                st.push(pow(op1, op2));
                break;
            }
        }
    }
    return st.top();
}


//Infix to Postfix expression
string infixToPostfix(stack<char> st,string infix){
    string postfix;
    for(int i=0;i<infix.length();i++){
        //If it's an operand
        if((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z')) postfix += infix[i];
        else if(infix[i] == '(') st.push(infix[i]);
        else if(infix[i] == ')'){
            while(st.top() != '(' && !st.empty()){
                postfix += st.top();
                st.pop();
            }
        }
        else if(isOperator(infix[i])){
            if(st.empty()) st.push(infix[i]);
            else{
                if(precedence(infix[i]) > precedence(st.top())) st.push(infix[i]);
                else if((precedence(infix[i]) == precedence(st.top())) && infix[i] == '^') st.push(infix[i]);
                else{
                    while((!st.empty()) && precedence(infix[i]) <= precedence(st.top())){
                        postfix += st.top();
                        st.pop();
                    }
                    st.push(infix[i]);
                }
            }
        }
    }
    while(!st.empty()){
        postfix += st.top();
        st.pop();
    }
    return postfix;
}


//Find and Delete the middle element of a stack
//T.C - O(N) S.C - O(N)
void deleteUtil(stack<int> &st,int size,int current){
    if(current == size/2) st.pop();//REached the mid so remove

    int temp = st.top();
    st.pop();
    deleteUtil(st,size,current+1);
    st.push(temp);
}
void deleteMiddleStack(stack<int>st,int size){
    if(!st.empty()) return;
    deleteUtil(stack,size,0);
}


//Length of the Longest Valid Parentheses
//T.C - O(N) S.C - O(N)
int longestValidParentheses(string s){
    stack<int>st;
    st.push(-1);
    int maxLen = 0;

    for(int i=0; i<s.length(); i++){
        if(s[i] == '(') st.push(i);//Opening Braces
        else{
            st.pop();//Pop the idx
            if(st.empty()) st.push(i);//We need to check further
            else{//There must be a valid length for parentheses
               int len = i - st.top(); 
               maxLen = max(maxLen, len);
            }
        }
    }
    return maxLen;
}


// Decode String
// T.C - O(N) S.C - O(N)
string decodeString(string s) {
    stack<string> wordStack;//Stores the str chunks
    stack<int> numStack;//Stores the numerical chunks
        
    string currNum = "";//Num just before the open bracket
    string currStr = "";//Str just before the closing bracket
        
    for(char ch : s){
        //If it's a digit just store it in curr num
        if(isdigit(ch)) currNum += ch;
            
        //Found an open bracket
        else if(ch == '['){
            numStack.push(stoi(currNum));//Push into numStack(convert str to int)
            wordStack.push(currStr);//Push into wordStack
            //Reset both
            currNum = "";
            currStr = "";
        }
            
        //Found a closing bracket
        else if(ch == ']'){
            //Extract the num by which we have to repeat the str
            int prevNum = numStack.top();
            numStack.pop();
            //Extract the prev formed str to append to final result
            string prevStr = wordStack.top();
            wordStack.pop();
                
            //Repeat the currStr by prevNum times
            string temp = "";
            while(prevNum != 0){
                temp += currStr;
                prevNum--;
            }
            //Update the curr str
            currStr = prevStr + temp;
        }
            
        //If it's a char store it in curr str 
        else currStr += ch;
    }
    return currStr;
}


//N stacks in Array
//T.C - O(1) S.C - O(2S+N)
class NStack{
    public:
    int *arr;
    int *top;//To store the stack top
    int *next;//Store the prev tops or address of next freeSpot
    int n,s;
    int freeSpot;
    NStack(int N, int S){
        n = N;
        s = S;
        arr = new int[s];
        top = new int[n];
        next = new int[s];

        for(int i = 0; i <n;++i) top[i] = -1;
        for(int i = 0; i <s;++i) next[i] = i+1;
        next[s-1] = -1;//Last index
        freeSpot = 0;
    }

    // Pushes 'X' into the Mth stack. Returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x, int m){
        if(freeSpot == -1) return false;//Overflow

        int index = freeSpot;//Find index
        freeSpot = next[index]//Update freeSpot
        arr[index] = x;//Insert in array
        next[index] = top[m-1]//Update next;
        top[m-1] = index;

        return true;
    }

    // Pops top element from Mth Stack. Returns -1 if the stack is empty, otherwise returns the popped element.
    int pop(int m){
        if(top[m] == -1) return -1;
        //Reverse push operation
        int index = top[m-1];
        top[m-1] = next[index];
        next[index] = freeSpot;
        freeSpot = index;

        return arr[index];
    }
};


//Maximum of minimum for every window size
//T.C - O(N) S.C - O(N)
vector<int> maxOfMinWindowSize(int arr[],int size){
    stack<int>st;

    int left[size+1] = {-1};
    int right[size+1] = {n};

    nextSmallerElementsLeft(arr,left,size,st);//(0 to n)
    nextSmallerElementsRight(arr,right,size,st);//(n to 0)

    int ans[size+1] = {0};

    for(int i = 0;i < size; ++i){
        int len = right[i] - left[i] - 1;//Range for that particular element
        ans[len] = max(ans[len],arr[i]);//Store the max
    }

    for(int i=size-1;i>=0;i--) ans = max(ans[i],ans[i+1]);

    vector<int>res(size);
    for(int i=1;i<=size;++i){
        res[i-1] = ans[i];
    }
    return res;
}


//132 Pattern Geeky Buildings
//T.C - O(N) S.C - O(N)
bool find132pattern(vector<int>& nums) {
    //In 132 pattern -> nums[i] is from loop nums[j] is in stack and nums[k] is in s3
    int s3 = INT_MIN;
    stack<int> st;
    for(int i=nums.size()-1;i>=0;i--){
        if(nums[i] < s3) return true;
        else while(!st.empty() && nums[i] > st.top()){ 
            s3 = st.top();//Store the smaller num from stack in s3
            st.pop(); 
        }
        st.push(nums[i]);
    }
    return false;
}


//Restrictive Candy Crush
//T.C - O(N)  S.C - O(N)
string Reduced_String(int k,string s){
    if(k == 1) return "";//Every char should be removed

    stack<pair<char,int>>st;//store the char and its count of occ
    string ans = "";

    for(int i=0;i<s.length();i++){
        if(st.empty()) st.push({s[i],1});

        else if(st.top().first == s[i]){//Found same char
        st.push({s[i],st.top().second+1});//store the char and increase count
        if(st.top().second == k){//Reached the repetition limit
            int x = k;//Can't change k because we have to remove k every time
            while(x--) st.pop();
           }
        }
        else if(st.top().first != s[i]) st.push({s[i],1});//Any other that enters for first time
    }

    while(!st.empty()){
        ans = st.top().first + ans;
        st.pop();
    }
    return ans;
}


//Remove K digits
//T.C - O(N) S.C - O(N)
string removeKDigits(string num, int k) {
    if(k >= num.size()) return "0";//Edge case

    stack<char>st;

    for(int i=0;i<num.size();i++){
        if(st.empty()) st.push(num[i]);
        else{//Remove larger digits in left
            if(!st.empty() && num[i] < st.top() && k > 0){
                st.pop();
                k--;//We can only remove k digits
            }
            st.push(num[i]);
        }
    }

    if(k > 0){//If no small no.'s are present in stack but still we can remove digits
        st.pop();
        k--;
    }
    if(st.empty()) return "0";

    string ans;
    while(!st.empty()){
        // st - 0 0 2 0 if we do ans+=st.pop ans'd be 002
        ans = st.top() + ans;//Store ans in order(attach the popped no. to back)
        st.pop();
    }

    int i = 0;
    while(ans[i] == '0') i++;//Remove any leading zeroes(0200 -> 200)

    return (ans.substr(i) == "") ? "0" : ans.substr(i);
}