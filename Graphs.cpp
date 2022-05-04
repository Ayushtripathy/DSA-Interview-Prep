//Graph Taking Input
//Adjacency Matrix
//S.C = O(N + E)
int main(){
    int n, m;
    cin >> n >> m;
    // declare the adjacency matrix
    int adj[n + 1][m + 1];
    // run loop for edges
    for (int i = 0; i < m; i++){
        // vertices input
        int u, v;
        cin >>> u >> v; // For ex - u = 1, v = 2;

        adj[u][v] = 1; // edge from 1 to 2
        adj[v][u] = 1; // edge from 2 to 1
    }
    return 0;
}

//Adjacency List
//S.C = O(N + E)
int main(){
    int n, m;
    cin >> n >> m;
    // declare the adjacency list
    vector<int> adj[n + 1] // Unweighted graph
    vector<pair<int, int>> adj[n + 1] // Weighted graph
        // run loop for edges
        for (int i = 0; i < m; i++){
        
        // vertices input
        int u, v;     // Unweighted graph
        int u, v, wt; // Weighted graph

        cin >>> u >> v;       // Unweighted graph
        cin >>> u >> v >> wt; // Weighted graph

        adj[u].push_back(v); // Unweighted graph
        adj[v].push_back(u); // Unweighted graph

        adj[u].push_back({v, wt}); // Weighted graph
        adj[v].push_back({u, wt}); // Weighted graph
    }
    return 0;
}


//Breadth First Search
//T.C = O(V + E) S.C - O(N+E) + O(2N)
vector<int>bfsGraph(int V, vector<int> adj[]){
    vector<int> ans;// To store output
    vector<int> vis(V + 1, 0)// Initialise visited array
     // Loop for each node -> helps in disconnected graphs
     for (int i = 1; i <= V; i++){
         if (!vis[i]){//Node hasn't been visited yet
             queue<int> q;
             q.push(i);//Push the first node
             vis[i] = 1;// mark node visited
             
             while (!q.empty()){
                 int node = q.front();
                 q.pop();
                 ans.push_back(node);
                 
                 // Extract all the adjacent nodes of curr node
                 for (auto it : adj[node]){
                     if (!vis[it]){
                         q.push(it);
                         vis[it] = 1;//Mark visited
                    }
                }
            }
        }
    }

    return ans;
}


//Depth First Search
//T.C = O(V + E) S.C - O(N+E) + O(2N)
void dfs(int node, vector<int> &vis, vector<int> adj[], vector<int> &storeDfs){
    // push for ans
    storeDfs.push_back(node);
    // Mark the node visited
    vis[node] = 1;

    // Traverse the adjacent nodes of that extracted node
    for (auto it : adj[node]){
        if (!vis[it]){
            dfs(it, vis, adj, storeDfs);
        }
    }
}
vector<int> dfsGraph(int V, vector<int> adj[]){
    vector<int> storedDfs;
    vector<int> vis(V + 1, 0);

    // For disconnected graphs
    for (int i = 1; i <= V; i++){
        if (!vis[i]){
            dfs(i, vis, adj, storeDfs);
        }
    }
    return storeDfs;
}


//Cycle Detection(Undirected Graph)
//T.C - O(N+E) S.C - O(N) + O(N+E)
bool cycleBFS(int node,int V,vector<int>adj[],vector<int>&vis){
    queue<pair<int, int>> q;//pair to store node and parent
    q.push({node, -1});//Initially no one is parent
    vis[node] = 1;

    while (!q.empty()){
        int currNode = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (auto it : adj[currNode]){
            if (!vis[it]){
                q.push({it, currNode});//it is curr node and currnode becomes parent node
                vis[it] = 1;
            }
            // It is visited but the parent node didn't mark it, then who did?
            else if (it != parent) return true;//There is a cycle
        }
    }
    return false;
}
bool cycleDFS(int node, int parent, vector<int> adj[], vector<int> &vis){
    vis[node] = 1;
    for (auto it : adj[node]){
        if (!vis[it]){
            if (cycleDFS(it, node, adj, vis)) return true;
        }
        else if (it != parent) return true;//Only parent could mark the node visited
    }
    return false;
}
bool isCycle(int V, vector<int> adj[]){
 // Intuition - Check for parent node and current node using pair. If the adjacent
 // node is visited but its not the parent node then its a cycle.
    vector<int> vis(V + 1, 0);
    for (int i = 0; i <= V; i++){
        if (!vis[i]){
            if (cycleBFS(i, V, adj, vis)) return true;
            if (cycleDFS(i, -1, adj, vis)) return true;
        }
    }
    return false;
}


// Bipartite Graph(Graph Coloring)
// T.C - O(N + E) S.C - O(N) + O(N) + O(N + E)
bool bipartiteBFS(int node, vector<int> adj[], vector<int> color){
    queue<int> q;
    q.push(node);
    color[node] = 1;//COlor the node

    while (!q.empty()){
        int currNode = q.front();
        q.pop();

        for (auto it : adj[currNode]){
            if (color[it] == -1){//If adj node hasn't been colored
                color[it] = 1 - color[currNode];//color the node with alternate color
                q.push(it);
            }//Adjacent node has same color
            else if (color[it] == color[currNode]) return false;
        }
    }
    return true;
}
bool bipartiteDFS(int node, vector<int> adj[], vector<int> color){
    if (color[node] == -1) color[node] = 1;

    for (auto it : adj[node]) {
        // If adj nodes are not colored yet
        if (color[it] == -1){
            // Alter the colors
            color[it] = 1 - color[node];
            // If the any of the adj nodes is not bipartite return
            if (!bipartiteDFS(it, adj, color)) return false;
            // Adjacent nodes are colored and with same color
        }
        else if (color[it] == color[node]) return false;
    }
    return true;
}
bool isBipartite(int V, vector<int> adj[]){
 //Intuition - Traverse the nodes and check if adjacent nodes are colored and of same color
    vector<int> color(V, -1);
    for (int i = 0; i < V; i++){
        if (color[i] == -1){//Hasn't been colored
            if (!bipartiteBFS(i, adj, color)) return false;
            if (!bipartiteDFS(i, adj, color)) return false;
        }
    }
    return true;
}


// Topological Sort DFS(DAG)
// T.C - O(N + E) S.C - O(N) + O(N) + O(N + E)
void findTopoDFS(int node, vector<int> &vis, stack<int> &st, vector<int> adj[]){
    vis[node] = 1;

    for (auto it : adj[node]){
        if (!vis[it]) findTopoDFS(it, vis, st, adj);
    }
    st.push(node);
}
vector<int> topoSort(int V, vector<int> adj[]){
 //Use normal Dfs and store the values in stack in the end
    vector<int> vis(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++){
        if (!vis[i]) findTopoDFS(i, vis, st, adj);
    }

    vector<int> topo;
    while (!st.empty()) {//To return ans in reverse order
        topo.push_back(st.top());
        st.pop();
    }

    return topo;
}


//Topological Sort BFS(Kahn's Algorithm)(DAG)
// T.C - O(N+E) S.C - O(N) + O(N+E)
vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);
    //Calculate the indegree of vertices
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) indegree[it]++;//Edge present from 1 to 2
    }
    //Push the indegrees with 0 value to queue
    queue<int> q;
    for (int i = 0; i < V; i++){
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    //int count = 0; To Check Cycle in Directed Graph BFS
        while (!q.empty()){
        int node = q.front();
        q.pop();
        //count++;  To Check Cycle in Directed Graph BFS
        topo.push_back(node);//Push to ans
        for (auto it : adj[node]){
            indegree[it]--;//Reduce the indegree of adjacent nodes
            if (indegree[it] == 0) q.push(it);
        }
    }
    // if (count == N) return false;
    // return true; // To Check Cycle in Directed Graph BFS
    return topo;
}


//Cycle Detection DFS (Directed Graph)
//T.C - O(N+E) S.C - O(2N) + O(N) + O(N+E)
bool checkCycle(int node,vector<int>adj[],vector<int>vis,vector<int>dfsVis){
 // Use normal DFS but use two visited arrays. If for any node both vis array
 // is marked then there is a cycle
    vis[node] = 1;
    dfsVis[node] = 1;

    for (auto it : adj[node]){
        if (!vis[it]){
            if (checkCycle(it, adj, vis, dfsVis)) return true;
        }
        else if (dfsVis[it]) return true;//If both vis and dfsvis have the node
    }
    dfsVis[node] = 0;//Unmark the node when returning in dfs call
    return false;
}
bool isCyclic(int N,vector<int>adj[]){
    vector<int> vis(N, 0);
    vector<int> dfsVis(N, 0);

    for (int i = 0; i < N; i++){
        if (!vis[i]) {
            if (checkCycle(i, adj, vis, dfsVis)) return true;
        }
    }
    return false;
}


//Shortest Path Unit Weights (Undirected Graph)
//T.C - O(N+E) S.C - O(N) + O(N) + O(N+E)
// Why BFS? -> The path used in BFS always has least number of edges between any two vertices.
// So if all edges are of same weight, we can use BFS to find the shortest path.
void shortestPathUnitWeightBFS(vector<int>adj[],int N,int src){
    int dist[N] = {INT_MAX};
    queue<int>q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()){
        int node = q.front();
        q.pop();

        for (auto it : adj[node]){
            //dist to reach adjacent nodes is less than the prev distance
            if (dist[node] + 1 < dist[it]){ // Cost of coming to this node + 1 is less than the curr distance stored
                dist[it] = dist[node] + 1;
                q.push(it);
            }
        }
    }

    for (int i = 0; i < N; i++) cout << dist[i] << "";
}


//Shortest Path Weighted DAG
//T.C - O((N+E)*2)  S.C - O(2N) + O(N+E)
// Why TopoSort - This multiple time calling DFS/BFS degrades the Time Complexity,
// hence Topological Ordering save you from that overhead as you already know which
// nodes will come after the current node , so you keep on updating it.
void findTopoDFS(int node,vector<int>&vis,stack<int>&st,vector<pair<int,int>>adj[]){
    vis[node] = 1;
    for (auto it : adj[node]){
        if (!vis[it.first]) findTopoDFS(it.first, vis, st, adj);
    }
    st.push(node);
}
void shortestPathWeightedDAG(int src,int V, vector<pair<int,int>> adj[]) {
    vector<int> vis(V, 0);
    stack<int> st;//It will contain the toposort in reverse

    for (int i = 0; i < V; i++){
        if (!vis[i]) findTopoDFS(i, vis, st, adj);
    }

    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    while (!st.empty()) {
        int node = st.top();
        st.pop();
        //If that node has been visited already
        if (dist[node] != INT_MAX) { 
            for (auto it : adj[node]) {
    // Dist for curr node and the weight of adj node is less than Dist saved already for that node
            if (dist[node] + it.second < dist[it.first]){
            dist[it.first] = dist[node] + it.second;
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
        (dist[i] == INT_MAX) ? count << "INF" : cout << src << "-" << i << dist[i] << "";
}

//Dijkstra's Algorithm
//T.C - O((N+E)*logN)  S.C - O(N) + O(N) + O(N+E)
// (Shortest Path from Src to every node in undirected weighted graphs)
// Greedy - Taking the min node from pq.
// Can use a Set to overwrite repeated nodes
// It differs from the minimum spanning tree because the shortest distance between two
// vertices might not include all the vertices of the graph.
void Dijkstra(vector<pair<int,int>>adj[],int src,int V){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distTo(V + 1, INT_MAX);

    distTo[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty){
        int dist = pq.top().first;      // Dist covered yet
        int prevNode = pq.top().second; // Node for which dist is stored yet
        pq.pop();
        vector<pair<int, int>>::iterator it;
        for (auto it : adj[prevNode]){
            int next = it.first;     // Node
            int nextDist = it.second // Distance
            if (dist + nextDist < distTo[next]){ // If new distance is less than prev stored
                distTo[next] = dist + nextDist;
                pq.push(make_pair(distTo[next], next));
            }
        }
    }

    for (int i = 1; i <= N; i++)
        (dist[i] == INT_MAX) ? cout << "INF" : cout << src << "-" << i << distTo[i] << "";
}


//Minimum Spanning Tree Prim's Algorithm(Only for connected graph)
//T.C - O((V+E)logV)  S.C - O(3V+E)
void primsAlgo(int V,vector<pair<int,int>>adj[]){
    // We require 3 arrays to store parent,keys,present in array or not
    int parent[V] = {-1};
    int key[v] = {INT_MAX};
    bool mstSet[V] = {false};
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    key[0] = 0;//Min dist to 0 from 0 is 0
    parent[0] = -1;//No one is parent of 0
    pq.push({0,0});//Store key of i and idx(0 idx -> 0 val)
    
    for(int i=0;i<V-1;i++){
        int idx = pq.top().second;//Gives the minimal index
        pq.pop();
        mstSet[idx] = true;

        for(auto it : adj[idx]){//For adjacent nodes of that picked out min value
        int node = it.first;
        int weight = it.second;
        if(!mstSet[node] && weight < key[node]){//The adj node isn't part of mst and have a less edge value
            parent[node] = idx;//Make it the parent node(idx)
            pq.push({key[node],node});
            key[node] = weight;//store the new min wt. for adjacent nodes
          }
        }
    }
    //Print the output
    for(int i=1;i<V;i++){
        cout<<parent[i]<<"-"<<i<<endl;
    }
}


//Disjoint Sets(Union by rank & Path compression)
//T.C- O(4a) S.C - O(2N)
int parent[10000];
int rank[10000];
void makeSet(){
    for(int i=1;i<=n;i++){
        parent[i] = i;
        rank[i] = 0;
    }
}
int findParent(int node){
    if(node == parent[node]) return node;
    //Path compression - Directly connect node to parent
    return parent[node] = findParent(parent[node]);
}
void union(int u,int v){
    u = findParent(u);
    v = findParent(v);

    if(rank[u] < rank[v]) parent[u] = v;//Attach u to v
    else if(rank[u] > rank[v]) parent[v] = u;//Attach v to u
    else{
        parent[v] = u;
        rank[u]++;
    }
}
void main(){
    makeSet();
    int m;
    cin>>m;
    while(m--){
        int u,v;
        union(u,v);
    }
    //If  u and v belong to the same components
    if(findParent(2) != findParent(3)){
        cout<<'Different Components'<<endl;
    }
    else{
        cout<<"Same"<<endl;
    }
}


//Kruskal's Algorithm
//Based on Greedy approach
//T.C - O(3MlogM + M*4a)  S.C - O(M+2N)
struct node{
    int u;
    int v;
    int wt;
    node(int first, int second,int weight){
        u = first;
        v = second;
        wt = weight;
    }
};
bool comp(node a,node b){
    return a.wt < b.wt;
}
int findParent(int node,vector<int>&parent){
    if(node == parent[node]) return node;
    //Path compression - Directly connect node to parent
    return findParent(parent[node],parent);
}
void union(int u,int v,vector<int>&parent,vector<int>&rank){
    u = findParent(u,parent);
    v = findParent(v,parent);

    if(rank[u] < rank[v]) parent[u] = v;//Attach u to v
    else if(rank[v] < rank[u]) parent[v] = u;//Attach v to u
    else{
        parent[v] = u;
        rank[u]++;
    }
}
int main(){
    int N,m;
    cin>>N>>m;
    vector<node>edges;//Linear data structure to store graph nodes
    for(int i=0;i<m; i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back(node(u,v,wt));
    }
    sort(edges.begin(), edges.end(),comp)//Sort the node array to greedily select path with min wt

    vector<int>parent(N);
    for (int i = 0; i <N; i++) parent[i] = i;
    vector<int>rank(N,0);

    int cost = 0;
    vector<pair<int,int>>mst;
    for(auto it : edges){
        //If they belong to diff. components join them
        if(findParent(it.v,parent) != findParent(it.u,parent)){
            cost += it.wt;
            mst.push_back({it.u,it.v});
            union(it.u,it.v,parent,rank);
        }
    }
    cout<<cost<<endl;

    for(auto it : mst){
        cout<<it.first<<"->"<<it.second<<endl;
    }
    return 0;
}



//Floyd Warshall Algorithm
//T.C - O(V*V*V) S.C - O(V*V)
//For every u,v in Graph G,find shortest path from u to v
//Based on DP and works for both directed and undirected
vector<vector<int>> floydWarshall(int graph[][V]){
    vector<vector<int>>dist(V,-1);//Store the final dist
    //Initialize ans matrix with original matrix
    for (i = 0; i < V; i++){
        for (j = 0; j < V; j++) dist[i][j] = graph[i][j];
    }

    //Try every vertex as intermediate vertex
    for(int k = 0; k < V; k++){
        //Pick every vertex as src 
        for(int i = 0; i < V; i++){
            //Pick every vertex as destination for given src
            for(int j = 0; j < V; j++){
                if(dist[k][j] != INT_MAX && dist[k][j] != INT__MAX){
                    //If going via vertex k gives shorter path than the original one
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }
    return dist;
}


//Kosaraju's Algorithm for Strongly Connected Components
//T.C - O(N+2(N+E)) S.C - O(N+E+2N)
void findTopoDFS(int node, vector<int> &vis, stack<int> &st, vector<int> adj[]){
    vis[node] = 1;

    for (auto it : adj[node]){
        if (!vis[it]) findTopoDFS(it, vis, st, adj);
    }
    st.push(node);
}
void revDFS(int node,vector<int>&vis,vector<int>transpose[]){
    cout<<node<<" ";
    vis[node] = 1;
    for(auto it:transpose[node]){
        if(!vis[it]) revDFS(it,vis,transpose);
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<int>adj[n];
    //Take input
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    //1. Find topo sort and store in stack
    stack<int>st;
    vector<int>vis(n,0);
    for (int i = 0; i <n; i++){
        if(!vis[i]) findTopoDFS(i, vis, st, adj);
    }

    //2. Transpose the graph(reverse links)
    vector<int>transpose[n];
    for (int i = 0; i <n; i){
        vis[i] = 0;//Unmark the visited nodes
        //Reverse links
        for(auto it: adj[i]) transpose[it].push_back(i);
    }

    //3.Do DFS acc to finishing time
    while(!st.empty()){
        int node = st.top();
        st.pop();
        if(!vis[node]){
            cout<<"SCC:";
            revDFS(node,vis,transpose);
            cout<<endl;
        }
    }
    return 0;
}


//Bellman Ford Algorithm
// Similar to Dijkstras but works for negative weights too
//In case of undirected graphs, convert to directed
//It is DP based can detect negative weight cycle
//T.C - O(V*E)  S.C - O(V)
struct node{
    int u;
    int v;
    int wt;
    node(int first, int second,int weight){
        u = first;
        v = second;
        wt = weight;
    }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<node>edges;
    //Take input
    for(int i=0;i<m;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back(node(u,v,wt));
    }

    int src;
    cin>>src;

    int inf = INT_MAX;
    vector<int>dist(n,inf);//initialize with infinity
    dist[src] = 0;//dist of src will be 0

    for(int i=1;i<=n;i++){//Run for n-1 times, after that it gives negative cycle
        for(auto:edges){
            if(dist[u] != INT_MAX && dist[it.u] + it.wt < dist[it.v]){
                dist[it.v] = dist[it.u] + it.wt;
            }
        }
    }
    //Why n-1 times? -> on first pass only one edge
    //having src will change and then affect the other nodes on later passes
    int fl = 0;
    for(auto it:edges){
        if(dist[it.u] + it.wt < dist[it.v]){
            cout<<"Negative Cycle";
            fl = 1;
            break;
        }
    }
    if(!fl){
        for(int i=0;i<n;i++){
            cout<<i<<" "<<dist[i]<<endl;
        }
    }
    return 0;
}


//Find the no. of islands
//T.C - O(V*V) S.C - O(V+E)
void islandPresent(vector<vector<char>>&grid,int i,int j){
    //Boundary checking
    if(i<0 || i>=grid.size() || j<0 || j>=grid[0].size()) return;

    //If already visited(2) or no land(0)
    if(grid[i][j] == '0') return;

    grid[i][j] = '0'//Mark the curr as visited

    //Search in all 4 directions
    islandPresent(grid,i+1,j);//Check in right dir
    islandPresent(grid,i,j-1);//Check in upward dir
    islandPresent(grid,i-1,j);//Check in left dir
    islandPresent(grid,i,j+1);//Check in downward dir

}
int numIslands(vector<vector<char>>&grid){
    //Count the no. of disconnected components
    int islands = 0;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0;i<grid[0].size();j++){
        //do DFS in case hasn't been visited and there's land
            if(grid[i][j] == '1'){
            islandPresent(grid,i,j);
            ++islands;
          }
        }
    }
    return islands;
}


//Course Scheduling
// T.C - O(N+E) S.C - O(N) + O(N+E)
vector<int> courseScheduling(int courses, vector<int> prerequisites[]) {
    vector<int> indegree(courses, 0);
    //Calculate the indegree of vertices
    for (int i = 0; i < courses; i++) {
        for (auto it : prerequisites[i]) indegree[it]++;//Edge present from 1 to 2
    }
    //Push the indegrees with 0 value to queue
    queue<int> q;
    for (int i = 0; i < courses; i++){
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    int count = 0;
        while (!q.empty()){
        int node = q.front();
        q.pop();
        count++;
        topo.push_back(node);//Push to ans
        for (auto it : prerequisites[node]){
            indegree[it]--;//Reduce the indegree of adjacent nodes
            if (indegree[it] == 0) q.push(it);
        }
    }
    //Return only if scheduling is possible
    if(count == numCourses) return topo;
    else{
        vector<int>dummy;
        return dummy;
        }
}


//Clone a graph
//T.C - O(V+E) S.C - O(2V)
void dfs(Node* node,Node* copy,vector<Node*>&vis){
    //For ex - vis[0] = 0
    vis[copy->val] = copy;//mark the node visited and place the node in vis array
    //Usually we do for(auto it : adj[node])
    for(auto it:node->neighbors){//Traverse the adjacent nodes
      if(!vis[it->val]){//vis array has no value meaning that the curr adj node hasn't been visited yet
      Node* newNode = new Node(it->val);//Create a new node
      (copy->neighbors).push_back(newNode);//Push all the adj nodes of curr node as neighbors to the copied node
      dfs(it,newNode,vis);//send it as curr node and newNode as new copy node
      }
      //If the adj node is visited,just store the neighbors
      else (copy->neighbors).push_back(vis[it->val]);
    }
}
Node* cloneGraph(Node* node) {
    if(!node) return node;

    vector<Node*>vis(1000,NULL);//create visited array
    Node* copy = new Node(node->val);//create the first copy node
    dfs(node,copy,vis);//send the copy node in dfs to attach and copy other nodes
    return copy;
}


// Find whether path exist between two vertices
//T.C - O(N+E)  S.C - O(2N)
bool dfs(vector<vector<int>>&graph,vector<int>&visited,int start,int end){
    if(start == end) return true;//found a path
    if(visited[start]) return false;

    visited[start] = 1;//mark visited

    for(int i = 0;i<graph[start].size(),++i){//traverse the neighbors
    //check if path is possible fom further nodes
        if(dfs(graph,visited,graph[start][i],end)) return true;
    }
    return false;
}
bool validPath(int n, vector<vector<int>>& edges, int start, int end){
    vector<vector<int>> graph(n);
    for(int i=0; i<edges.size(); i++) {
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }

    vector<int>visited(n,0);
    return dfs(graph,visited,start,end);
}


// Alien Dictionary
//T.C - O(N+E)  S.C - O(2K+K*K)
void dfs(int src,vector<vector<int>>&graph,vector<int>&vis,string &ans){
    vis[src] = 1;
    for(auto it:graph[src]){
        if(!vis[it]) dfs(it,graph,vis,ans);
    }
    char ch = src + 'a';//convert src(int form) to char form
    ans += ch;
}
string findOrder(string dict[], int N, int K){
    vector<vector<int>>graph(K);
    for(int i=0;i<N-1;i++){
        string w1 = dict[i];//Extract two words to compare
        string w2 = dict[i+1];

        //Loop to form the graph
        for(int j=0;j<min(w1.length(),w2.length());j++){//Traverse the extracted strings
           if(w1[j] != w2[j]){//if diff chars are found w1[j] < w2[j]
           //create a directed graph,for ex in abc & abd -> c<d so make graph c->d
            graph[w1[j] - 'a'].push_back(w2[j] - 'a');
            break;
           }
        }
    }
    
    //Now store the topo sort
    vector<int>vis(K,0);
    string ans = "";
    for(int i=0;i<K;i++){
        if(!vis[i]) dfs(i,graph,vis,ans);
    }
    return ans;
}


//Bridges in graph(Critical Connections in a Network)
//T.C - O(V+E)  S.C - O(3N)
void dfs(int node, int parent,vector<int>&vis ,vector<int>&low,vector<int>&tim,int timer,vector<vector<int>>&adj,vector<vector<int>>&bridges){
    vis[node]=1;//Mark visited
    low[node]=tim[node]=timer++;//Every time a node is visited inc timer
    for(auto it : adj[node]){//Traverse for adj nodes
        if(it == parent)continue;//if its a parent then skip
        
        if(!vis[it]){
         dfs(it,node,vis,low,tim,timer,adj,bridges);//traverse for further nodes until no more nodes can be visited
         low[node]=min(low[node],low[it]);//store the min time of curr or adj nodes
         //if node is reaching the adj before the curr node(curr node is the only connection)
         if(low[it]>tim[node]) bridges.push_back({node,it}); 
        }
        else low[node]=min(low[node],tim[it]);
        }
}
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>>adj(n);//Convert and store as graph
    for(auto &x:connections){
        adj[x[0]].push_back(x[1]);
        adj[x[1]].push_back(x[0]);
        }
        //To store ans
    vector<vector<int>>bridges;
        
    vector<int>vis(n,0); //Stores the initial time
    vector<int>low(n,-1);//Store the min time for node
    vector<int>tim(n,-1);
    int timer=0;
       
    for(int i=0;i<n;i++){//Do normal dfs if not visited
        if(!vis[i]) dfs(i,-1,vis,low,tim,timer,adj,bridges);
    }
    return bridges;
}


//Articulation Point
// T.C - O(V+E)  S.C - O(3N)
void dfs(int node, int parent,vector<int>&vis ,vector<int>&low,vector<int>&tim,int timer,vector<vector<int>>&adj,vector<int>&isArticulation){
    vis[node]=1;//Mark visited
    low[node]=tim[node]=timer++;//Every time a node is visited inc timer
    int child = 0;
    for(auto it : adj[node]){//Traverse for adj nodes
        if(it == parent)continue;//if its a parent then skip
        
        if(!vis[it]){
         dfs(it,node,vis,low,tim,timer,adj,bridges);//traverse for further nodes until no more nodes can be visited
         low[node]=min(low[node],low[it]);//store the min time of curr or adj nodes
         //if node is reaching the adj before the curr node(curr node is the only connection)
         if(low[it]>=tim[node] && parent != -1) isArticulation[node] = 1; 
         child++;
        }
        else low[node]=min(low[node],tim[it]);
        }
        //Fo first node
        if(parent == -1 && child > 1) isArticulation[node] = 1;
}
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>>adj(n);//Convert and store as graph
    for(auto &x:connections){
        adj[x[0]].push_back(x[1]);
        adj[x[1]].push_back(x[0]);
        }
        //To store ans
    vector<int>isArticulation;
        
    vector<int>vis(n,0); //Stores the initial time
    vector<int>low(n,-1);//Store the min time for node
    vector<int>tim(n,-1);
    int timer=0;
       
    for(int i=0;i<n;i++){//Do normal dfs if not visited
        if(!vis[i]) dfs(i,-1,vis,low,tim,timer,adj,isArticulation);
    }
    vector<int>ans;
    for(int i=0;i<n;i++){
        if(isArticulation[i] == 1) ans.push_back(i);
    }
    return ans;
}


// Snake and Ladder Problem
//T.C - O(N+E)  S.C - O(4N)
int main(){
    int ladders,snakes;
    cin>>ladders;
    map<int,int>ladderMap;//To avoid linear search and store the pos of ladders
    map<int,int>snakeMap;//To avoid linear search and store the pos of snakes

    for(int i=0;i<ladders;i++){
        int u,v;//can jump from u to v
        cin>>u>>v;
        ladderMap[u] = v;//Store the pos to  where we jump using ladder
    }

     cin>>snakes;
    for(int i=0;i<snakes;i++){
        int u,v;//can drop from u to v
        cin>>u>>v;
        snakeMap[u] = v;//Store the pos to  where we drop from snake
    }

    int moves = 0;
    queue<int> q;//For doing bfs
    q.push(1);//we start from 1st box
    bool found = false;
    vector<int>vis(101,0);
    vis[1] = true;
    while(!q.empty() && !found){
        int size = q.size();
        while(sz--){
            int top = q.front();
            q.pop();
            //Play the dice
            for(int die = 1;die<=6;die++){
                if(top + die == 100){//IF we reach the end
                    found = true;
                }
                //Still inside the board and ladder is present and we haven't visited the ladder before
                if(top + die <= 100 && ladderMap[top+die] && !vis[ladderMap[top+die]]){
                    vis[ladderMap[top+die]] = true;
                    if(ladderMap[top+die] == 100) found = true;
                    q.push(ladderMap[top+die]);
                }
                else if(top + die <= 100 && snakeMap[top+die] && !vis[snakeMap[top+die]]){
                    vis[snakeMap[top+die]] = true;
                    if(snakeMap[top+die] == 100) found = true;
                    q.push(snakeMap[top+die]);
                }
                //Neither snake nor ladder
                else if(top + die <= 100 && !ladderMap[top+die] && !snakeMap[top+die] && !vis[ladderMap[top+die]]){
                    vis[top+die] = true;
                    q.push(top+die);
                }
            }
        }
        moves++;
    }
    if(found) cout<<moves<<endl;
    else cout <<"-1"<<endl;
}


// Min no. of operations
// T.C - O(end-start+1)  S.C - O(N)
int findMinMoves(int start,int end,int arr[]){
    int vis[end+1];
    vis[start] = 1;

    queue<pair<int,int>>q;
    q.push({start,0});//Initially steps is 0

    while(!q.empty()){
        int node = q.front().first;
        int steps = q.front().second;
        if (node == end) return steps;
        q.pop();

        for(int i=0;i<n;i++){//For all members of array
            int dest = node*arr[i];
            if(dest <= end && !vis[dest]){
                q.push({dest,steps+1});
                vis[dest] = 1;
            }
        }
        return -1;
    }
}


//Rolling ball in maze 
// T.C - O(N+E)  S.C - O(N)
bool hasPath(vector<vector<int>>&maze,vector<int>&start,vector<int>&destination){
    int n = maze.size();
    int m = maze[0].size();

    queue<pair<int,int>>q;//Push the coordinates
    q.push({start[0],start[1]});

    int vis[n][m];
    memset(vis,0,sizeof vis);
    vis[start[0],start[1]] = 1;

    int dx[] = {-1,0,1,0};
    int dy[] = {0,1,0,-1};

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        //Reached the destination
        if(x == destination[0] && y == destination[1]) return true;

        for(ind = 0; ind<4;ind++){//Go in 4 dirs
        int newX = x;
        int newY = y;
        //While coordinates are in bound and haven't hit a wall yet
        while(newX >= 0 && newX < n && newY >= 0 && newY < m && maze[newX][newY] == 0){
            newX += dx[ind];
            newY += dy[ind];
        }
        //We have hit a wall or crossed boundary(store the 0 before 1)
        newX -= dx[ind];
        newY -= dy[ind];
        if(vis[newX][newY] == 0){//haven't visited this point yet
        vis[newX][newY] = 1;
        q.push({newX, newY});
        }
        }
    }
    return false;
}


// Shortest Source to Destination Path Binary Matrix
// T.C - O(R*C)*8  S.C - O(R*C)
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int res = 1;
    int row = grid.size();
    int col = grid[0].size();
    if (row == 0 || col == 0) return -1;
    if (grid[0][0] != 0 | grid[row-1][col-1] != 0) return -1;

    queue<pair<int,int>>q;
    q.push({0,0});
    vector<pair<int,int>> directions = {{1,0},{0,1},{-1,0},{0,-1},{1,-1},{-1,1},{1,1},{-1,-1}};

    grid[0][0] = 1;//Avoids vis array and mark vis in original array

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        //We can reach end of array
        if(x == row - 1 && y == col - 1) return grid[row-1][col-1];

        for(auto dir : directions){//Check all 8 directions whether curr orange can rot anyone
            int nx = x + dir.first;//Add the dir value to curr idx value
            int ny = y + dir.second;
            //If invalid due to any of these reasons,skip the cell
            if(nx < 0 || ny < 0 || nx >= row || ny >= col || grid[nx][ny] != 0) continue;
            grid[nx][ny] = grid[i][j]+1;//Increment the steps req before by 1
            q.push({nx,ny});
    }
    return -1;
    }
}


//Number of ways to arrive at destination
//T.C - O((N+E)logN)  S.C - O(2N)
int countPaths(int n, vector<vector<int>>& roads) {
    int mod = 1e9+7;
    vector<int>ways(n,0);
    vector<int>dist(n,INT_MAX);

    dist[0] = 0;
    ways[0] = 1;//one way to reach itself
    //Create adjacency list
    vector<pair<int,int>>adj[n];
    for(auto it:roads){
        adj[it[0]].push_back({it[1],it[2]});
        adj[it[1]].push_back({it[0],it[2]});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0,0});
    while(!pq.empty()){
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for(auto it : adj[node]){
            int wt = it.second;
            int adjNode = it.first;
            if(dist + wt < dist[adjNode]){//If dist yet + wt of adj Node is less than original dist of adjNode
                dist[adjNode] = wt + dist;
                ways[adjNode] = ways[node];//ways of adj nodes will be equal to the ways of original node
                pq.push({dist[it],adjNode});
            }
            else if(wt + dist == dist[adjNode]){//Encounter the same distance
            ways[adjNode] = (ways[adjNode] + ways[node])%mod;//Increase the number of ways
            }
        }
    }
}


// Word Ladder
//T.C - O(N*M*26) where N is dict size and M is length of each word in dict
// S.C - O(2N)
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    queue<string>q;//For BFS
    q.push(beginWord);
    int wordSize = beginWord.length();

    unordered_set<string>word;//for O(1) lookup of dictionary
    for(int i=0;i<wordList.size();i++) word.insert(wordList[i]);

    if(word.find(end) == word.end()) return 0;//End word has to be in dictionary but start may or maynot be
    int len = 0;

    while(!q.empty()){
        len++;
        int qlen = q.size();
        for(int i=0;i<qlen;i++){//Run for all strings in queue
        string s = q.front();//Extract the string from queue
        q.pop();
        for(int j=0;j<wordSize;j++){//Check for the no. of chars that begin word has
            char org = s[j];//Need to store the original to restore it
        for(char ch='a';ch<='z';ch++){
            s[j] = ch;//Replace each char of the str extracted from the queue with all alphabets
            if(s==end) return len+1;//s becomes the end word while replacing
            if(word.find(s) == word.end()) continue;//Word formed after replacement is not in dictionary

            word.erase(s);//Found the word in the dictionary but haven't reached the end;
            q.push(s);//Push to queue and repeat the replacements
        }
        s[j] = org;//So when we move to next char the prev char restores its original form
        }
        }
    }
    return 0;
}


// Min Steps by Knight
// T.C - O(N*N)  S.C - O(N*N)
int minStepKnight(vector<int>&KnightPos,vector<int>&TargetPos,int n){
    int k1 = KnightPos[0];
    int k2 = KnightPos[1];
    int t1 = TargetPos[0];
    int t2 = TargetPos[1];
    vector<vector<int>> arr(N,vector<int>(N,0));
    if(k1 == t1 && k2 == t2) return 0;

    queue<pair<int,int>>q;
    q.push({k1-1,k2-1});//Minus 1 to make 0 based indexing
    //8 Dirs for knight
    int dx[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
    int dy[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
    while(!q.empty()){
        int i = q.front().first;
        int j = q.front().second;
        q.pop();

        for(int i=0;i<8;i++){//Check in 8 dirs where knight can go
            int nx = i + dx[i];
            int ny = j + dy[i];
            if(nx >=0 && nx<n && ny >=0 && ny<n && arr[nx][ny]==0){
                arr[nx][ny] = arr[i][j] + 1;
                q.push({nx,ny});
            }
        }
    }
    return arr[t1-1][t2-1];
}


// Circle of Strings
//Euler Path -> Every edge should be travelled exactly once
// Euler Circuit -> Euler path having same start and end vertex 
//T.C - O()  S.C - O()
void dfs(int start, vector<int> adj[], vector<bool> &visited) {
   visited[start] = true;
   for (auto it: adj[start]) {
     if (visited[it] == false)
       dfs(it, adj, visited);
   }
} 
bool IsConnected(int s, int V, vector<int> adj[], vector<bool> &mark) {
   vector < bool > visited(26, false);
   dfs(s, adj, visited);

   for (int i = 0; i < 26; i++){
     if (!visited[i] && mark[i]) return false;
   }
   return true;
}
int isCircle(int V, vector < string > A) {
   vector < bool > mark(26, false);
   vector < int > adj[26];
   vector < int > indegree(26, 0);

   for (int i = 0; i < V; i++) {
     string s = A[i];//Extract a string from vector
     int u = s[0] - 'a';//Store the first alphabet
     int v = s[s.size() - 1] - 'a';//Store the last alphabet
     mark[u] =  mark[v] = true;//mark the two chars
     indegree[v]++;//There is an edge from u to v
     adj[u].push_back(v);//push the node to graph
   }

   for (int i = 0; i < 26; i++) {
     if (adj[i].size() != indegree[i]) return false;
   }
   //Check whether the graph forms an eulerian circuit
   return IsConnected(A[0].front() - 'a', 26, adj, mark);
}


// Minimum Height Trees 
// T.C - O(V+E) S.C - O(V)
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges){
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);//More connection means less height
    vector<int> ans; 
    for(auto &e : edges){   
        adj[e[0]].push_back(e[1]);//Create graph
        adj[e[1]].push_back(e[0]);
        indegree[e[0]]++;//calculate indegree of all nodes
        indegree[e[1]]++;//Doing indegree for both vertices because undirected degree
    }

    queue<int>q;
    for(int i=0;i<n;i++){//Indegrees with 1 value can never be root
        if(indegree[i] == 1){
            q.push(i);
            indegree[i]--;
        }
    }

    while(!q.empty()){
        int size = q.size();
        ans.clear();//for new iteration
        for(int i=0;i<size;i++){
            int node = q.front();
            q.pop();
            ans.push_back(node);//The ans stored after the last iteration is output
            for(auto it:adj[node]){
                indegree[it]--;
                if(indegree[it] == 1) q.push(it);
            }
        }
    }
    if(n == 1) ans.push_back(0);
    return ans;
}


// Unit Area of Largest region of 1s
//T.C - O(R*C)  S.C - O(R*C)
int isSafe(vector<vector<int>>&grid,int row,int col,vector<vector<int>>&vis,int &count){
    return (row >= 0) && (row < grid.size()) && (col >= 0) && (col < grid[0].size()) && (!vis[row][col] && grid[row][col] == 1);
}
void DFS(vector<vector<int>>&grid,int row,int col,vector<vector<int>>&vis,int &count){
    int dx[] =  {-1, -1, -1, 0, 0, 1, 1, 1};//All 8 dirs
    int dy[] =  {-1, 0, 1, -1, 1, -1, 0, 1};

    vis[row][col] = 1;
    for(int k=0;i<8;k++){
        //IF its safe to move than traverse further  to maximize area
        if(isSafe(grid,row,col,vis,count)){
            count++;
            int newRow = row + dx[k];
            int newCol = col + dy[k];
            DFS(grid,newRow,newCol,vis,count);
        }
    }
}
int findMaxArea(vector<vector<int>>& grid){
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<int>>vis(row*col,0);

    int maxArea = INT_MIN;
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            if(!vis[i][j] && grid[i][j] == 1){
                int count = 1;
                DFS(grid,i,j,vis,count);
                maxArea = max(maxArea,count);
            }
        }
    }
    return maxArea;
}


//Flood Fill Algorithm
//T.C - O(N)  S.C - O(N)
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor){
    if(sr==sc && sc==newColor && image[sr][sc]==newColor) return image;

    int m=image.size();
    int n=image[0].size();

    queue<pair<int,int>> q;//Store thr xy coordinates
    q.push({sr,sc});//Push the initial coordinates
    int prevColor = image[sr][sc];
    image[sr][sc] = newColor;//Paint the initial point with new color

    while(!q.empty()){
        //Get the coordinates out
        int i = q.front().first;
        int j = q.front().second;
        q.pop();

        int dx[]={1,0,-1,0};
        int dy[]={0,1,0,-1};

        for(int i=0;i<4;i++){
            int nx = i + dx[i];
            int ny = j + dy[i];

            //Covers all the invalid conditions
            if(nx>=0 && ny>=0 && nx<m && ny<n && image[nx][ny]==prevColor){
            //If we somehow get here it means that we can change value in this point
            image[nx][ny] = newColor;//Paint the point
            q.push({nx,ny});
            }
        }
    }
    return image;
}