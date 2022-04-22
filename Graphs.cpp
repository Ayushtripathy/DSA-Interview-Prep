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
//T.C - O(N+E) S.C - O(N) + O(N) + O(N+E)
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


//Minimum Spanning Tree Prim's Algorithm
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
//T.C - O()  S.C - O()



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