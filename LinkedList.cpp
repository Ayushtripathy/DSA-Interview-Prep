//Implementation and Operation Linked Lists
class Node {
  int data;
  Node *next;
  Node(val){
      this->val = data;
      }
      //Insertion
      Node* insertAtBegin(Node* head, int val){
          Node* newNode = new Node(val) // creating new node of linked list
          if(head == NULL) return newNode;
          else { // inserting the node at the beginning
          newNode->next = head;
          return newNode;
          }
          }
          
          Node* insertAtEnd(Node* head, int val){
            if( head == NULL ) { // handing the special case
            Node* newNode = new Node(val);
            head = newNode;
            return head;
            }
            Node* temp = head;
            // traversing the list to get the last node
            while( temp->next != NULL ) temp = temp->next;
            Node* newNode = new Node(val);
            temp->next = newNode;
            return head;
            }
            
            void insertAfter(Node* prevNode, int val){
            Node* newNode = new Node(val);
            newNode->next = prevNode->next;
            prevNode->next = newNode;
            }
            
            //Deletion
            Node* deleteLL(Node* head, Node* del){
                // if the node to be deleted is the head node
                if(head == del) return head->next; // special case for the first Node
                Node* temp = head;
                
                while( temp->next != NULL ){
                if(temp->next == del){ // finding the node to be deleted
                temp->next = temp->next->next;
                delete del; // free the memory of that Node
                return head;
                }
                temp = temp->next;
                }
                return head; // if no node matches in the Linked List
                }
};

//Implementation and Operation Doubly Linked Lists
class DLLNode {
  int data;
  class Node* next;
  class Node* prev;
  DLLNode(data){
      this->data = data;
  }
  
  //Insertion
  void insertFront(Node* head, int data) {
  // allocate memory for newNode
   Node* newNode = new Node(data);
  // make newNode as a head
  newNode->next = head;
  // assign null to prev
  newNode->prev = NULL;
  // previous of head (now head is the second node) is newNode
  if(head != NULL) head->prev = newNode;
  // head points to newNode
   head = newNode;
   }
   
   void insertEnd(Node* head, int data) {
       Node* newNode = new Node(data);
       // assign null to next of newNode
       newNode->next = NULL;
       // store the head node temporarily (for later use)
       Node* temp = head;
       // if the linked list is empty, make the newNode as head node
       if (head == NULL) {
           newNode->prev = NULL;
           head = newNode;
           return;
           }
        // if the linked list is not empty, traverse to the end of the linked list
        while (temp->next != NULL) temp = temp->next;
  // now, the last node of the linked list is temp
  // assign next of the last node (temp) to newNode
  temp->next = newNode;
  // assign prev of newNode to temp
  newNode->prev = temp;
  }


  void insertAfter(Node* prev_node, int data) {
  if (prev_node == NULL) return;
  // allocate memory for newNode
  Node* newNode = new Node(data);
  // set next of newNode to next of prev node
  newNode->next = prev_node->next;
  // set next of prev node to newNode
  prev_node->next = newNode;
  // set prev of newNode to the previous node
  newNode->prev = prev_node;
  // set prev of newNode's next to newNode
  if (newNode->next != NULL) newNode->next->prev = newNode;
  }

  //Deletion
  void deleteNode(Node* head,Node* del_node) {
  if(head == NULL || del_node == NULL) return;

  // if del_node is the head node, point the head pointer to the next of del_node
  if(head == del_node) head = del_node->next;

  // if del_node is not at the last node, point the prev of node next to del_node to the previous of del_node
  if(del_node->next != NULL) del_node->next->prev = del_node->prev;

  // if del_node is not the first node, point the next of the previous node to the next node of del_node
  if(del_node->prev != NULL) del_node->prev->next = del_node->next;

  // free the memory of del_node
  free(del_node);
  }
};

//Implementation and Operation Circular Linked Lists
class CLLNode {
  int data;
  Node* next;

  Node* addFront(Node* head, int data) {
  if (head == NULL) return head;
  // allocate memory to the new node
  Node* newNode = new Node(data);
  // store the address of the current first node in the newNode
  newNode->next = head->next;
  // make newNode as head
  head->next = newNode;
  return head;
  }

  Node* addEnd(Node* head, int data) {
  // allocate memory to the new node
  Node* newNode = new Node(data);
  // store the address of the head node to next of newNode
  newNode->next = head->next;
  // point the current head node to the newNode
  head->next = newNode;
  // make newNode as the head node
  head = newNode;
  return head;
  }

  Node* addAfter(Node* head, int data, int item) {
  // check if the list is empty
  if (head == NULL) return NULL;

   Node *newNode, *p;
   p = head->next;
   do {// if the item is found, place newNode after it
  if (p->data == item) {
    // allocate memory to the new node
    newNode = new Node(data);
    // make the next of the current node as the next of newNode
    newNode->next = p->next;
    // put newNode to the next of p
    p->next = newNode;
    // if p is the head node, make newNode as the head node
    if (p == head) head = newNode;
    return head;
    }
    
    p = p->next;
    } while (p != last->next);

  return head;
  }

  void deleteNode(Node* head, int key) {
  if (*head == NULL) return;
  // if the list contains only a single node
  if (head->data == key && head->next == head) {
  free(head);
  head = NULL;
  return;
  }

  Node *temp = head, d;

  // if head is to be deleted
  if (head->data == key) {
  // find the node before the head node
  while (temp->next != head) temp = temp->next;

  // point temp node to the next of head i.e. first node
  temp->next = head->next;
  free(head);
  head = temp->next;
  }

  // travel to the node to be deleted
  while (temp->next != head && temp->next->data != key) temp = temp->next;

  // if node to be deleted was found
  if (temp->next->data == key) {
  d = temp->next;
  temp->next = d->next;
  free(d);
  }
  }
};

//Reverse a Linked List
//T.C - O(N) S.C - O(1)
void reverseLL(Node* head){
    if(!head) return;
    Node* next = NULL;
    Node* prev = NULL;
    Node* curr = head;

    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

//Reverse a Linked list in groups of size k
//T.C - O((N/k)*k) S.C - O(1)
Node* reverseKGroup(Node* head, int k){
    if(!head) return head;
    int count = countNodes(head);
    if(count < k) return head;//Less than k nodes are there
    Node* curr = head;
    Node* next = NULL;
    Node* prev = NULL;
    int cnt = 0;
    //Reversing logic
    while(curr && cnt < k){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        cnt++;
    }

    //Conecting nodes after reverse (head)->1 2 3 == 3 2 1(head)->(next)
    if(next) head->next = reverseKGroup(next,k);
    return prev;//After complete reversing,prev becomes head;
}

//Reverse alternate K nodes in a Linked List
//T.C - O(N) S.C - O(N)
Node* reverseAlternativelyInGroup(Node* head, int k){
    if(k <= 1 || !head || !head->next) return head;
    Node* prev,next;
    Node* curr = head;
    int count = 0;
    while(curr && count < k){//First k nodes are reversed
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    count = 0;//Reset count
    if(next){
        head->next = next;//Attach head and the next node after reversed nodes
        curr = next;
        while(curr && count < k - 1){//Skip k-1 nodes because alternative
            curr = curr->next;
            count++;
        }
        if(curr) curr->next = reverseAlternativelyInGroup(curr->next,k);
    }
    return prev;
}

//Reverse a Sub-list
//T.C - O(N) S.C - O(1)
Node* reverseBetween(ListNode* head, int left, int right){
    if(!head) return head;
    if(left==right) return head;

    Node* prev = NULL;
    Node* curr = head;

    while(m > 1){//Reach upto the point from where to reverse
        prev = curr;
        curr = curr->next;
        m--;
        n--;
    }

    Node* connection = prev;//Used later to connect to head of reversed portion
    Node* tail = curr;

    while(n > 0){//Reverse the sublist portion
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        n--;
    }
    if(connection) connection->next = prev;//Because prev is head of reversed sublist
    else head = prev; 

    tail->next = curr;//Connect the rest of list
    return head;
}

//Middle of a Linked List
//T.C - O(N) S.C - O(1)
int middleLL(Node* head){
    if(!head || !head->next) return head;
    Node* slow = head;
    Node* fast = head;

    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
    }

    return slow->data;
}

//Merge Sort Linked List
//T.C - O(NlogN) S.C - O(logN)
Node* mergeSort(Node* head){
    if(!head || !head->next) return head;

    Node* mid = findMid(head);
    Node* head1 = head;
    Node* head2 = mid->next;
    mid->next = NULL;

    head1 = mergeSort(head1);
    head2 = mergeSort(head2);

    Node* ans = mergeTwoLL(head1,head2);
    return ans;
}

//Check if given Linked List is Plaindrome
//T.C - O(3N/2) S.C - O(1)
bool isPalindrome(Node* head){
    if(head==NULL || head->next==NULL) return true;
    ListNode* fast =head;
    ListNode* slow = head;

    while(fast->next!=NULL && fast->next->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }

    slow->next = reverseList(slow->next);
    slow = slow->next;

    while(slow){
      if(head->val != slow->val) return false;
      head = head->next;
      slow = slow->next;
    }
      return true;  
}

//Delete a given Node when a node is given
//T.C - O(1) S.C - O(1)
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}

//Detect a cycle in Linked List
//T.C - O(N) S.C - O(1)
bool detectCycle(Node* head){
    if(!head) return false;
    Node* fast = head;
    Node* slow = head;
    while(slow && fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}

//Find the starting point of the Loop of LinkedList and Remove it
//T.C - O(N) S.C - O(1)
void startingPointLoop(Node* head){
     if(head==NULL||head->next==NULL) return;
    Node*slow = head;
    Node* fast = head;
    //Check for Loop
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
        if(slow==fast){
            break;
        }
    }
    //No loop
    if(slow!=fast) return;//If the above loop broke for some other reason

     slow = head;//To find the starting of loop
     while(slow!=fast){
        fast = fast->next;
        slow = slow->next;
    }
    //Slow contains the starting of loop
    while(fast->next != slow) fast = fast->next;
    fast->next = NULL;//Remove the loop
    return;
}

//Merge two sorted Linked Lists
//T.C - O(N+M) S.C - O(1)
Node* mergeTwoLists(Node* list1,Node* list2){
    if(!list1) return list2;
    if(!list2) return list1;
    ListNode* newHead = NULL;
    ListNode* newTail = NULL;
    //Initialize the list by the smaller value out of two
    if(list1->val < list2->val){
        newHead = list1;
        newTail = list1;
        list1 = list1->next;
    }
    else{
        newHead = list2;
        newTail = list2;
        list2 = list2->next;
    }

    while(list1 && list2){
        if(list1->val <= list2->val){
        newTail->next = list1;
        newTail = list1;
        list1 = list1->next;
        }
        else{
        newTail->next = list2;
        newTail = list2;
        list2 = list2->next
        }
    }
    //If any one is exhausted and one is remaining
    if(list1) newTail->next = list1;
    if(list2) newTail->next = list2;

    return newHead;
}

//Remove Nth node from end
//T.C - O(N) S.C - O(1)
Node* removeNthFromEnd(Node* head,int n){
    if(!head) return head;
    Node* dummy = new Node();
    dummy->next = head;
    Node* fast = dummy;
    Node* slow = dummy;

    for(int i=1;i<=n;++i) fast = fast->next;

    while(fast->next){
        fast = fast->next;
        slow = slow->next;
    }

    slow->next = slow->next->next;
    return dummy->next;
}

//Intersection 'Y' of two linked lists
//T.C - O(n1 + n1 - n2 + n2) S.C - O(1)
Node* getIntersection(Node* headA,Node* headB){
    if(!headA) return NULL;
    if(!headB) return NULL;
    //Count no. of nodes in both lists
    int countA = countNodes(headA);
    int countB = countNodes(headB);

    int diff = abs(countA - countB);

    //Move the pointers to get equal starting pos
    if(countA > countB){
        for(int i = 0;i<diff;++i) headA = headA->next;
    }
    else if(countB > countA){
        for(int i = 0;i<diff;++i) headB = headB->next;
    }
    //While the intersection is not found
    while(headA != headB){
        headA = headA->next;
        headB = headB->next;
    }

    if(headA) return headA;

    return NULL;
}

//Intersection of two Linked Lists(Common elements)
//T.C - O(N+M) S.C - O(N+M)
Node* findIntersection(Node* headA, Node* headB){
    Node* ptr1 = headA;
    Node* ptr2 = headB;
    Node* head = NULL;
    Node* tail = NULL;

    while(ptr1 && ptr2){
        if(ptr1->data == ptr2->data){//Elements are same
            if(!head){//New list hasn't formed yet
                Node* temp = new Node(ptr1->data);
                head = temp;
                tail = temp;
            }
            else{
                Node* temp = new Node(ptr1->data);
                tail->next = temp;
                tail = tail->next;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else{
            if(ptr1->data < ptr2->data) ptr1 = ptr1->next;
            else ptr2 = ptr2->next;
        }
    }
    return head;
}

//Remove Duplicates in a Sorted Linked List.
//T.C - O(N) S.C - O(1)
void removeDuplicates(Node* head){
    Node* curr = head;
    Node* next;

    while(curr->next){
        if(curr->data == curr->next->data){
            next = curr->next->next;
            delete(curr->next);
            curr->next = next;
        }
        else  curr = curr->next;
    }
}

//Remove Duplicates in a Un-sorted Linked List.
//T.C - O(N) S.C - O(N)
void removeDuplicates(Node* head){
    unordered_set<int> seen;
    Node* curr = head;
    Node* prev = NULL;//Prev node needed to remove the node

    while(curr){
        if(seen.find(curr->data) != seen.end()){
            prev->next = curr->next;
            delete(curr);
        }
        else{
            seen.insert(curr->data);
            prev = curr;
        }
        curr = prev->next;//Because curr is deleted
    }
}

//Add two linked lists
//T.C - O(max(n1,n2)) S.C - O(N)
Node* addTwoNumbers(Node *headA, Node *headB){
    Node* dummy = new Node();
    Node* temp = dummy;
    int carry = 0;

    while(headA && headB && carry){
        int sum = 0;//To store the sum of node values
        if(headA){
            sum += headA->val;
            headA = headA->next;
        }
        if(headB){
            sum += headB->val;
            headB = headB->next;
        }

        sum += carry;
        carry = sum  / 10;
        Node* newNode = new Node(sum%10);
        temp->next = newNode;//Append the new node to temp LL
        temp = temp->next;
    }
    return dummy->next;//Next node is head of new LL
}

//Multiply two linked lists
//T.C - O(M*N) S.C - O(N+M)
Node* multiplyLLDigit(Node* head,int digit){
    Node* dummy = new Node(-1);
    Node* ptr = dummy;
    Node* curr = head;
    int carry = 0;
    while(curr || carry){
        int sum = (curr != NULL ? curr->val : 0)*digit + carry;
        int dig = sum % 10;
        carry = dig / 10;

        ptr->next = new Node(dig);
        if(curr) curr = curr->next;
        ptr = ptr->next;
    }
    return dummy->next;
}
void addTwoLL(Node* head,Node* ans){
    Node* c1 = head;//New prod list
    Node* c2 = ans;//List containing prev sums
    int carry = 0;
    while(c1 || carry){
        int sum += carry + (c1!=NULL ? c1->data : 0) + (c2->next!=NULL ? c2->next->data : 0);
        int digit = sum % 10;
        int carry = sum / 10;

        if(c2->next) c2->next->data = digit;
        else c2->next = new Node(digit);

        if(c1) c1 = c1->next;
        c2 = c2->next;
    }
}
Node* multiplyLL(Node* list1, Node* list2){
    Node* l2 = list2;
    Node* dummy = new Node(-1);
    Node* ans = dummy;
    while(l2){//Multiply each node(digit) of list2 with list1
        Node* product = multiplyLLDigit(list1,l2->data);
        l2 = l2->next;

        addTwoLL(product,ans);
        ans = ans->next;
    }
    return dummy->next;
}

//Rotate a Linked List
//T.C - O(N + (N-N%k)) S.C - O(1)
Node* rotateLinkedList(Node* head,int k){
    if(!head || !head->next || k == 0) return head;
    Node* temp = head;
    int len = 1;//Count the nodes upto last element
    while(temp->next){
        ++len;
        temp = temp->next;
    }

    temp->next = head;//Join tail to head
    k = k % len;//If exceeds len
    int end = len - k;//Calculate the end point upto which traversal is needed
    while(end--) temp = temp->next;

    head = temp->next;//Make the next of end node head
    temp->next = NULL;//Break the link of end node

    return head;
}

//Flatten a LinkedList
//T.C - O(N) S.C - O(1)
Node* mergeTwoLists(Node* a, Node* b){
    Node* temp = new Node(0);
    Node* res  = temp;

    while(a && b){
        if(a->data < b->data){
            temp->bottom = a;
            temp = temp->bottom;
            a = a->bottom;
        }
        else{
            temp->bottom = b;
            temp = temp->bottom;
            b = b->bottom;
        }
    }
    if(a) temp->bottom = a;
    if(b) temp->bottom = b;

    return res->bottom
}
Node* flatten(Node* root){
    if(!root || root->next == NULL) return root;
    //Put the flattened list to root's next(recur)
    root->next = flatten(root->next);
    //merge the two lists
    root = mergeTwoLists(root,root->next);
    return root;
}

//Segregate even and odd nodes in a Linked List(Pos based)
//T.C - O(N) S.C - O(1)
Node* oddEvenList(Node* head){
    if(!head || !head->next || !head->next->next) return head;

    Node* odd = head;
    Node* even = head->next;
    Node* evenStart = head->next;

    while(odd->next && even->next){
        odd->next = even->next;
        even->next = odd->next->next;
        even = even->next;
        odd = odd->next;
    }
    odd->next = evenStart;//Join the end of odd nodes and start of even
    return head;
}

//Segregate even and odd nodes in a Linked List(Value based)
//T.C - O(N) S.C - O(1)
Node* oddEvenList(Node* head){
    if(!head || !head->next) return head;

    Node* oddStart = NULL;
    Node* oddEnd = NULL;
    Node* evenEnd = NULL;
    Node* evenStart = NULL;
    Node* curr = head;

    while(curr){//Something like merge two lists
        if((curr->data)%2 == 0){
            if(!evenStart){//No even node is present yet
                evenStart = curr;
                evenEnd = curr;
            }
            else{
                evenEnd->next = curr;
                evenEnd = evenEnd->next;
            }
        }
        else{
            if(!oddStart){//No odd node is present yet
                oddStart = curr;
                oddEnd = curr;
            }
            else{
                oddEnd->next = curr;
                oddEnd = oddEnd->next;
            }
        }
        curr = curr->next;
    }
    if(!evenStart) return oddStart;
    if(!oddStart) return evenStart;
    evenEnd->next = oddStart;
    oddEnd->next = NULL;
    head = evenStart;
    return head;
}

//Sort a linked list of 0s, 1s and 2s
//T.C - O(N) S.C - O(1)
Node* segregate012(Node* head){
    int count[3] = {0};
    Node* temp = head;
    while(temp){
        count[temp->val]++;
        temp = temp->next;
    }

    temp = head;
    int i = 0;
    while(temp){
        if(count[i] == 0){
            ++i;
        }
        else{
            temp->val = i;
            --count[i];
            temp = temp->next;
        }
    }
    return head;
}

//Rearrange a LinkedList
//T.C - O(3N/2) S.C - O(N)
void reorderList(Node* head){
    if(!head) return;
    stack<Node*>st;
    Node* temp = head;
    int size = 0;
    //Push all elements to stack to get the LIFO
    while(temp){
        st.push(temp);
        temp = temp->next;
        size++;
    }

    Node* ptr = head;
    for(int i = 0; i < size/2; i++){//Run for half only
        Node* el = st.top();
        st.pop();
        el->next = ptr->next;
        ptr->next = el;
        ptr = ptr->next->next;//Jump 2 nodes
    }
    ptr->next = NULL;
}

//Pairwise swap of a linked list (Doubt)?????
//T.C - O(N) S.C - O(1)
Node* pairWiseSwap(Node* head){
    if(!head || !head->next) return head;

    Node* dummy = new Node();
    dummy->next = head;
    Node* curr = dummy;

    while(curr){
        Node* first = curr->next;
        Node* second = NULL;

        if(first) second = first->next;
        if(second){
            Node* secondNext = second->next;
            second->next = first;
            curr->next = second;
            first->next = secondNext;
            curr = first;
        }
        else break;
    }
    return dummy->next;
}

//Happy Number
//T.C - O(logN) S.C - O(1)
int utilFn(int n){
    int ans = 0;
    while(n){//Stores the sum of squares of each digit
        int temp = n%10;
        ans += temp*temp;
        n /= 10;
    }
    return ans;
}
bool isHappy(int n) {
    //Use floyd cycle detection using two ptrs
    int slow = n;
    int fast = n;
    do{
        slow = utilFn(slow);//Slow pointer
        fast = utilFn(utilFn(fast));//Fast pointer
    } while(slow != fast);
    return slow == 1;
}

//Merge K sorted Linked list(Brute Force - Merge One by one)
//T.C - O(N*K) S.C - O(1)
Node* mergeTwoLists(Node* l1, Node* l2) {
          Node* head=NULL;  
          if(!l1) return l2;
          if(!l2) return l1;
		  
          if(l1->val<=l2->val) {  
              head=l1; 
              l1=l1->next; 
            }
          else { 
            head=l2;
            l2=l2->next;  
            }
		  
          Node *curr=head;
          while(l1 && l2){
            if(l1->val<=l2->val){  
              curr->next=l1;
              l1=l1->next;
              }
            else{
                curr->next=l2;
                l2=l2->next;
                }
            curr=curr->next;
          }
        
        if(l1) curr->next=l1;
        if(l2) curr->next=l2; 
        return head;
}
Node* mergeKLists(vector<Node*>& lists) {
        if(lists.size()==0) return NULL;
        Node* ans = mergeTwoLists(lists[0],lists[1]);
        for(int i=2;i<lists.size();i++) ans=mergeTwoLists(ans,lists[i]);
      
        return ans;
}
//Merge K sorted Linked list(Optimal - Min Heap)
//T.C - O(NlogK) S.C - O(K)
Node* mergeKLists(vector<ListNode*>& lists){
    priority_queue <Node*, vector<Node*>, greater<Node*>> pq;

    //Push head of all k lists
      for (int i = 0; i < lists.size(); i++){
      if (lists[i]) pq.push(lists[i]);
      }

      if(pq.empty()) return NULL;//K = 0 or lists are empty

      Node* dummy = new Node(0);
      Node* last = dummy;
      while(!pq.empty()){
          Node* curr = pq.top();//Extract the smallest out of k
          pq.pop();

          last->next = curr;//Append this small node to new list
          last = last->next;
          //Curr->next holds the address of tha next element that we picked
          if(curr->next) pq.push(curr->next);
      }
      return dummy->next;
}

//Clone a Linked List with Random and Next Pointer
//T.C - O(3N) S.C - O(N)
Node* cloneRandomList(Node* head){
    if(!head) return head;
    Node* curr = head;
    Node* temp;
    //Step 1 : Make clones of nodes in between
    while(curr){
        temp = curr->next;
        curr->next = new Node(curr->val);
        curr->next->next = temp;
        curr = temp;
    }
    curr = head//Reuse curr
    //Step 2 : Assign Random pointers to the clones
    while(curr){
        if(curr->next){
            //Clone->random = Clone 1(O)->1(C)->2(O)->2(C)
            curr->next->random = curr->random ? curr->random->next : curr->random;
        }
        curr = curr->next ? curr->next->next : curr->next;
    }
    //Step3 : Break the bonds b/w original and clones
    Node* original = head;
    Node* copy = head;
    temp = copy;//Store the ans;

    while(original && copy){
        //Connect original to original
        original->next = original->next ? original->next->next : original->next;
        //Connect copy to copy
        copy->next = copy->next ? copy->next->next : copy->next;

        original = original->next;
        copy = copy->next;
    }
    return temp;
}