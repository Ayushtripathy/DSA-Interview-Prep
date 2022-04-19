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
//T.C - O(1)Amortised S.C - O(2N)
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
class Node*{
    int data;
    Node* next;
}
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
            for(int i = 0; i <4;i++){//Check all 4 directions
            int nx = x + dx[i];//Add the dir value to curr idx value
            int ny = y + dy[i];
            //If invalid due to any of these reasons,skip the cell
            if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 1) continue;
            grid[nx][ny] = 2;//Mark the orange rotten
            rotten.push({nx,ny});
            }
        }
        if(!rotten.empty()) days++;//After every k oranges increment the days to rot
    }
    return total == count ? days : -1;
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

//Minimum sum of squares of character counts in a given string after removing “k” characters.
//T.C - O(K*logN) S.C - O(N)
int minStringValue(string str, int k){
    if(k >= str.length()) return 0;
    int freq[26] = {0};
    //Store the freq of each char
    for(int i=0;i<str.length();i++) freq[str[i] - 'a']++;

    priority_queue<int>q;//Store the freq in max heap
    for(int i=0;i<26;i++) q.push(freq[i]);

    while(k--){//This is to remove the highly frequent char
        //Extract max k freq and decrease them by 1
        int temp = q.top();
        q.pop();
        q.push(--temp);
    }
    //Calculate the sum of squares by taking values from heap
    int result = 0;
    while(!q.empty()){
        int temp = q.top();
        result += temp*temp;
        q.pop()
    }
    return result;
}

//Interleave First half of queue with Second half
//T.C - O() S.C - O()


//Implement K queues in an array
//T.C - O() S.C - O()
