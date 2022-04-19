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
//T.C = O(V + E)
vector<int>bfsGraph(int V, vector<int> adj[]){
    // To store output
    vector<int> ans;
    // Initialise visited array
    vector<int> vis(V + 1, 0)
     // Loop for each node -> helps in disconnected graphs
     for (int i = 1; i <= V; i++){
         if (!vis[i]){
             // store adjacent nodes of each node
             queue<int> q;
             q.push(i);
             
             // mark visited
             vis[i] = 1;
             
             while (!q.empty()){
                 int node = q.front();
                 q.pop();
                 ans.push_back(node);
                 
                 // Extract all the adjacent nodes
                 for (auto it : adj[node]){
                     if (!vis[it]){
                         q.push(it);
                         vis[it] = 1;
                    }
                }
            }
        }
    }

    return ans;
}

//Depth First Search
//T.C = O(V + E)
void dfs(int node, vector<int> &vis, vector<int> adj[], vector<int> &storeDfs){
    // push for ans
    storeDfs.push_back(node);
    // Mark the node visited
    vis[node] = 1;

    // Traverse the adjacent nodes of that exctracted node
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
// Intuition - Check for parent node and current node using pair. If the adjacent
// node is visited but its not the parent node then its a cycle.
bool cycleBFS(int node,int V,vector<int>adj[],vector<int>&vis){
    queue<pair<int, int>> q;
    vis[node] = 1;
    q.push({node, -1});

    while (!q.empty()){
        int currNode = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (auto it : adj[currNode]){
            if (!vis[it]){
                vis[it] = 1;
                q.push({it, currNode});
            }
            // It is visited but the parent node didn't mark it, then who did?
            else if (it != parent) return true;
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
        else if (it != parent) return true;
        return false;
}
bool isCycle(int V, vector<int> adj[]){
    vector<int> vis(V + 1, 0);
    for (int i = 0; i <= V; i++){
        if (!vis[i]){
            if (cycleBFS(i, V, adj, vis)) return true;
            if (cycleDFS(i, -1, adj, vis)) return true;
        }
    }
    return false;
}

//Bipartite Graph(Graph Coloring) -
//T.C - O(N + E) S.C - O(N) + O(N) + O(N + E)
//Intuition - Traverse the nodes and check if adjacent nodes are colored and of same color.
bool bipartiteBFS(int node, vector<int> adj[], vector<int> color){
    queue<int> q;
    q.push(node);
    color[node] = 1;

    while (!q.empty())
    {
        int currNode = q.front();
        q.pop();

        for (auto it : adj[currNode])
        {
            if (color[it] == -1)
            {
                color[it] = 1 - color[currNode];
                q.push(it);
            }
            else if (color[it] == color[currNode])
            {
                return false;
                ;
            }
        }
    }
    return true;
}
bool bipartiteDFS(int node, vector<int> adj[], vector<int> color){
    if (color[node] == -1)
    {
        color[node] = 1;
    }

    for (auto it : adj[node])
    {
        // If adj nodes are not colored yet
        if (color[it] == -1)
        {
            // Alter the colors
            color[it] = 1 - color[node];

            // If the any of the adj nodes is not bipartite return
            if (!bipartiteDFS(it, adj, color))
                return false;
            // Adjacent nodes are colored and with same color
        }
        else if (color[it] != color[node])
            return false;
    }
    return true;
}
bool isBipartite(int V, vector<int> adj[]){
    vector<int> color(V, -1);

    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            if (!bipartiteBFS(i, adj, color))
                return false;
            if (!bipartiteDFS(i, adj, color))
                return false;
        }
    }
    return true;
}
}
;

// Topological Sort DFS
// T.C - O(N + E) S.C - O(N) + O(N) + O(N + E)
// Intuition - Use normal Dfs and store the values in stack in the end
void findTopoDFS(int node, vector<int> &vis, stack<int> &st, vector<int> adj[]){
    vis[node] = 1;

    for (auto it : adj[node]){
        if (!vis[it]) findTopoDFS(it, vis, st, adj);
    }
    st.push(node);
}
vector<int> topoSort(int V, vector<int> adj[]){
    vector<int> vis(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++){
        if (!vis[i]) findTopoDFS(i, vis, st, adj);
    }

    vector<int> topo;
    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }

    return topo;
}

//Topological Sort BFS(Kahn's Algorithm)
// T.C - O(N+E) S.C - O(N) + O(N+E)
// Intuition - Calculate Indegree of all nodes. Push the nodes having 0 indegree
// to a queue. Extract from queue and reduce the indegree for the adj nodes until 0.
// When 0, insert to queue.
vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);
    queue<int> q;

    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) indegree[it]++;
    }

    for (int i = 0; i < V; i++){
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;

    int count = 0 // To Check Cycle in Directed Graph BFS
        while (!q.empty()){
        int node = q.front();
        q.pop();
        count++; // To Check Cycle in Directed Graph BFS
        topo.push_back(node);
        for (auto it : adj[node]){
            indegree[it]--;
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    // if (count == N) return false;
    // return true; // To Check Cycle in Directed Graph BFS
    return topo;
}

//Cycle Detection DFS (Directed Graph)
//T.C - O(N+E) S.C - O(2N) + O(N) + O(N+E)
// Intuition - Use normal DFS but use two visited arrays. If for any node both vis array
// is marked then there is a cycle
bool checkCycle(int node,vector<int>adj[],vector<int>vis,vector<int>dfsVis){
    vis[node] = 1;
    dfsVis[node] = 1;

    for (auto it : adj[node]){
        if (!vis[it]){
            if (checkCycle(it, adj, vis, dfsVis))
                return true;
        }
        else if (dfsVis[it]){
            return true;
        }
    }
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
// Intuition - Use BFS normally, create a distance array initialized by INT_MAX. Compare the
// distances from prev nodes and curr nodes and store the min.
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
// Intuition - Find Topo Sort, then calculate path just like the unit weight in Pair - 1st is Node 2nd is Weight 
// Why TopoSprt - This multiple time calling DFS/BFS degrades the Time Complexity,
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
    stack<int> st;

    for (int i = 0; i < V; i++){
        if (!vis[i]) findTopoDFS(i, vis, st, adj);
    }

    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (dist[node] != INT_MAX) { // Reached that node
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
// Intuition - Can't use the same method as unit weight because here weights are different,
// Take a pq(min heap) <dist,node>, Dist array marked INF. 
// Greedy - Taking the min node from pq.
// Can use a Set to overwrite repeated nodes
// It differs from the minimum spanning tree because the shortest distance between two
// vertices might not include all the vertices of the graph.
void Djikstras(vector<pair<int,int>>adj[],int src,int V){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distTo(V + 1, INT_MAX);

    distTo[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty){
        int dist = pq.top().first;      // Dist covered yet
        int prevDist = pq.top().second; // Node for which dist is stored yet
        pq.pop();
        vector<pair<int, int>>::iterator it;
        for (auto it : adj[prevDist]){
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