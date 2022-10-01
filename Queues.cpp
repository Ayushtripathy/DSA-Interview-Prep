//Queue Implementation(Arrays)
int main(){
    int arr[5];
    int count = 0;
    int front = 0;
    int rear = 0;

    void push(int x){
        if(count == size) return;
        arr[rear%size] = x;
        rear++;
        count++;
    }

    void pop(){
        if(count ==0) return;
        arr[front%size] = -1;
        front++;
        count--;
    }

    int front(){
        if(count == 0) return -1;
        return arr[front%size];
    }

    bool isEmpty(){
    return count == 0;
    }
}


//Queue Implementation(2 Stacks)
//T.C - O(1) Amortized S.C - O(2N)
int main(){
    stack<int>input;
    stack<int>output; 

    void push(int x){
        input.push(x);
    }

    void pop(){
        if(!output.empty()) output.pop();
        else{
            while(!input.empty()){
                output.push(input.top());
                input.pop();
            }
            output.pop();
        }
    }

    int top(){
        if(!output.empty()) return output.top();
        else{
            while(!input.empty()){
                output.push(input.top());
                input.pop();
            }
           return output.top();
        }
    }
}


//Implement Queue using Linked List
class LLNode*{
    int data;
    Node* next;

    Node* front = NULL;
    Node* rear = NULL;
 void enqueue(int value){
    Node* newNode = new Node(value);
    newnode->next = NULL;

    if(!front && !rear) front = rear = newNode;
    else{
        rear->next = newNode;
        rear = newNode;
    }
 }
 int dequeue(){
    if(!front) return -1;
    else{
        Node* temp = front;
        int tempData= front->data;
        front = front->next;
        free(temp);
        return tempData;
    }
 }
}


//Implement Circular Queue
//T.C - O(1)
class CircularQueue{
    private:
    int arr[SIZE],front,rear;
    public:
    Queue(){
    front = -1;
    rear = -1;
    }
    bool isFull(){
        if(front == 0 && rear == SIZE - 1) return true;
        if(front == rear+1) return true;
        return false;
    }
    bool isEmpty(){
        if(front == -1) return true;
        else return false;
    }
    void enqueue(int x){
        if(isFull()) return;
        else{
            if(front == -1) front = 0;
            rear = (rear+1)%SIZE;
            items[rear] = x;
        }
    }
    int deQueue(){
        int el;
        if(isEmpty()) return -1;
        else{
            element = items[front];
            if(front == rear){
                front = -1;
                rear = -1;
            }
            else{
                front = (front + 1)%SIZE;
            }
            return element;
        }
    }
};


//Implement Doubly Ended Queue
//T.C - O(1)
class Deque{
    int arr[MAX];
    int front;
    int rear;
    int size;
    public:
    Deque(int size){
        front = -1;
        rear = 0;
        this->size = size;
    }
    bool isFull() {
        return ((front == 0 && rear == size - 1) || front == rear + 1);
        }
    bool isEmpty() return front == -1;
    void insertFront(int key){
        if(isFull()) return;
        if(front == -1){
            front = 0;
            rear = 0;
        }
        else if(front == 0) front = size -1;
        else front = front - 1;

        arr[front] = key;
    }
    void insertBack(int key){
        if(front = -1){
            front = 0;
            rear = 0;
        }
        else if(rear == size - 1) rear = 0;
        else rear = rear + 1;

        arr[rear] = key;
    }
    void deleteFront(){
        if (isEmpty()) return;
        if (front == rear) {
            front = -1;
            rear = -1;
            }
        else if (front == size - 1) front = 0;
        else front = front + 1;
    }
    void deleteBack(){
        if(isEmpty()) return;
        if(front == rear){
            front = -1;
            rear = -1;
        }
        else if(rear == 0) rear = size - 1;
        else rear = rear - 1;
    }
    int getFront(){
        if(isEmpty()) return -1;
        return arr[front];
    }
    int getBack(){
        if(isEmpty() || rear < 0) return -1;
        return arr[rear];
    }
};


//Reverse a Queue using recursion
//T.C - O(N)
void reverseQueue(queue<int>&q){
    if(q.empty()) return;

    int data = q.front();
    q.pop();

    reverseQueue(q);

    q.push(data);
}


//Reverse the first “K” elements of a queue
//T.C - O(N+K) S.C - O(N)
void reverseQueueFirstKElements(int k, queue<int>&q){
    if(q.empty() || k > q.size()) return;

    stack<int>st;

    for(int i = 0; i < k;++i){
        st.push(q.front());
        q.pop();
    }

    while(!st.empty()){
        q.push(st.top());
        st.pop();
    }

    for(int i = 0; i < q.size() - k;++i){
        q.push(q.front());
        q.pop();
    }
}


//Rotting Oranges
//T.C - O(N*N)*4 S.C - O(N*N)
int orangesRotting(vector<vector<int>>& grid){
    if(grid.empty()) return 0;
    int m = grid.size();
    int n = grid[0].size();
    int days = 0;
    int total = 0;
    int count = 0;

    queue<pair<int,int>> rotten;
    for(int i = 0; i < m; i++){//Traverse the matrix
        for(int j = 0; j < n; j++){
            if(grid[i][j] != 0) total++;//count total oranges
            if(grid[i][j] == 2) rotten.push({i,j});//Push the initially rotten oranges to queue
        }
    }

    int dx[4] = {0,0,1,-1};
    int dy[4] = {1,-1,0,0};

    while(!rotten.empty()){
        int k = rotten.size();
        count += k;//Currently rotten oranges
        while(k--){//Take out the rotten oranges from queue
            int x =  rotten.front().first;
            int y = rotten.front().second;
            rotten.pop();
            for(int i = 0; i <4;i++){//Check all 4 directions whether curr orange can rot anyone
            int nx = x + dx[i];//Add the dir value to curr idx value
            int ny = y + dy[i];
            //If invalid due to any of these reasons,skip the cell
            if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 1) continue;
            grid[nx][ny] = 2;//Mark the orange rotten
            rotten.push({nx,ny});
            }
        }
        if(!rotten.empty()) days++;//After every k oranges increment the days to rot(Still rotten oranges are left so another day will be required)
    }
    return total == count ? days : -1;//All oranges are rotten
}


//First non-repeating character in a stream
//T.C - O(N) S.C - O(N)
vector<char> firstNonRepeating(string &str){
    queue<char> q;
    int charCount[26] = {0};
    vector<char> ans;

    for(int i = 0; i <str.length(); i++){
        q.push(str[i]);//Push the char
        charCount[str[i] - 'a']++;//Increment the char's frequency

        while(!q.empty()){
            //If found a repeating character,empty the queue
            if(charCount[q.front() - 'a'] > 1) q.pop()
            else{//Store the ans
                ans.push_back(q.front());
                break;
            }
        }

        if(q.empty()) ans.push_back('-1');
    }
    return ans;
}


//Interleave First half of queue with Second half
//T.C - O(N) S.C - O(N)
void interLeaveQueue(queue<int>& q){
    if(q.size()%2 != 0) return;
    stack<int> st;
    int half = q.size()/2;
    // test case : 11 12 13 14 15 16 17 18 19 20
    for(int i=0; i<half; i++){
        //queue:16 17 18 19 20, stack: 15 14 13 12 11
        st.push(q.front());//Push half of the queue to stack
        q.pop();
    }

    while(!st.empty()){
        //queue : 16 17 18 19 20 15 14 13 12 11
        q.push(st.top());
        st.pop();
    }

    for(int i=0;i<half;i++){
        //queue: 15 14 13 12 11 16 17 18 19 20
        q.push(q.front());
        q.pop();
    }

    for(int i=0;i<half;i++){
        // queue: 16 17 18 19 20, stack: 11 12 13 14 15
        st.push(q.front());
        q.pop();
    }

    while(!st.empty()){
        q.push(st.top());
        st.pop();
        q.push(q.front());
        q.pop();
    }
}


//Implement K queues in an array
//T.C - O(1) S.C - O(2N+2K)
class KQueue{
    public:
    int *arr;
    int *front;//To store the queue front
    int *rear;//To store the queue front
    int *next;//Store the address of next freespot
    int n,k;
    int freespot;
    public:
    KQueue(int n, int k){
        this->n = n;
        this->k = k;
        arr = new int[n];
        front = new int[k];
        front = new int[k];
        next = new int[n];

        for(int i = 0; i <k;++i){
             front[i] = -1;
             rear[i] = -1;
        }
        for(int i = 0; i <n;++i) next[i] = i+1;
        next[n-1] = -1;//Last index
        freespot = 0;
    }

    // Pushes 'X' into the Qth queue
    void enqueue(int data, int qn){
        if(freespot == -1) return;//Overflow

        int index = freespot;//Find index where to push
        freespot = next[index]//Update freespot
        if(front[qn-1] == -1) front[qn-1] = index;//First element to be inserted
        else{
        next[rear[qn-1]] = index;//link new element to prev element
        next[index] = -1;//Slot is filled now
        rear[qn-1] = index;//move rear to the recently inserted element
        arr[index] = data;//Insert in array
        }
    }

    // Pops front element from Mth Queue. Returns -1 if the stack is empty, otherwise returns the popped element.
    int dequeue(int qn){
        if(front[qn-1] == -1) return -1;
        int index = front[qn-1]//Find index of element to be popped
        front[qn-1] = next[index];//Move front to the next index of the curr element
        next[index] = freespot;//Point the next of curr element to freespot
        freespot = index;//Move freespot to curr element as it gets deleted
        return arr[index];
    }
};

//Rotten Oranges
//T.C - O() S.C - O()
int rottenOranges(vector<vector<int>&grid){
    if(grid.empty()) return 0;
    int totalOranges = 0;
    int timeToRot = 0;
    int rottenOranges = 0;

    queue<pair<int,int>>q;
    for(int i = 0; i < grid.size();i++){
        for(int j = 0; j < grid[0].size();j++){
            if(grid[i][j] != 0) totalOranges++;
            if(grid[i][j] == 2) q.push({i,j});
        }
    }

    int dx[4] = {0,0,1,-1};
    int dy[4] = {1,-1,0,0};

    while(!q.empty){
        int k = q.size();
        rottenOranges += k;
        int i = q.front().first;
        int j = q.front().second;

        for(int z=0;z<4;z++){
            int nx = i + dx[z];
            int ny = j + dy[z];
            
            if(nx < 0 || ny < 0 || nx > grid.size() || ny > grid[0].size() || grid[nx][ny] != 1) continue;
            q.push({nx,ny});
        }
        if(q.empty()) timeToRot++;
    }

    return totalOranges == rottenOranges ? timeToRot : -1;
}