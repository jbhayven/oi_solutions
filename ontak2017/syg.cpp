#include <bits/stdc++.h>
using namespace std;

#define MAX_N 3010

int n, m;
struct node_info {
    int t;
    int d;
    int capture_t;
    
    vector<int> net;
    vector<pair<int, int>> road;
    int dist[MAX_N];
    
    bool is_child[MAX_N];
    
    int par;
    int size;
    int preorder;
    int postorder;
} nodes[MAX_N];

int ans;

void read_nodes() {
    cin >> n >> m;
    
    nodes[1].t = 0;
    for (int i = 2; i <= n; i++)
        cin >> nodes[i].t;
    
    nodes[1].d = 0;    
    for (int i = 2; i <= n; i++)
        cin >> nodes[i].d;
    
    int a, b;
    for (int i = 0; i < n-1; i++) {
        cin >> a >> b;
        nodes[a].net.push_back(b);
        nodes[b].net.push_back(a);
    }
    
    int p, q, s;
    for (int i = 0; i < m; i++) {
        cin >> p >> q >> s;
        nodes[p].road.push_back({q, s});
        nodes[q].road.push_back({p, s});
    }
}

void init_tree(int v = 1, int par = 0) {
    static int order = 0;
    
    nodes[v].par = par;
    nodes[v].capture_t = min(nodes[par].capture_t + nodes[v].d, (int) 1e9); // we don't need higher times
    if (nodes[v].capture_t < nodes[v].t)
        nodes[v].t = -1;
    nodes[v].size = 1;
    nodes[v].is_child[v] = true;
        
    nodes[v].preorder = order++;
    
    for (int u : nodes[v].net) {
        if (u == par) continue;

        init_tree(u, v);
        
        nodes[v].size += nodes[u].size;
        nodes[v].is_child[u] = true;
        for (int i = 1; i <= n; i++)
            if (nodes[u].is_child[i])
                nodes[v].is_child[i] = true;
    }
    
    nodes[v].postorder = order++;
}

void do_dijkstra(int v) {
    priority_queue<pair<int, int>> q;
    bool visited[MAX_N];
    
    for (int i = 1; i <= n; i++)
        visited[i] = false;
    
    for (int i = 1; i <= n; i++)
        nodes[v].dist[i] = INT_MAX;
    nodes[v].dist[v] = 0;
    
    q.push({0, v});
    while (!q.empty()) {
        int top = q.top().second; q.pop();
        
        if (visited[top]) continue;
        visited[top] = true;
        
        for (auto road : nodes[top].road) {
            int u = road.first;
            int dist = road.second;
            if (visited[u]) continue;
            
            if (nodes[v].dist[u] > nodes[v].dist[top] + dist) {
                nodes[v].dist[u] = nodes[v].dist[top] + dist;
                q.push({-nodes[v].dist[u], u});
            }
        }
    }
}

void get_road_dists() {
    for (int i = 1; i <= n; i++)
        do_dijkstra(i);
}
    
bool first_step[MAX_N];
bool second_step[MAX_N][MAX_N];
int pre[2*MAX_N];
int post[2*MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    read_nodes();
    init_tree();
    get_road_dists();
    
    ans = 0;
    
    /* Step 1 */
    for (int i = 1; i <= n; i++) {
        if (nodes[1].dist[i] >= nodes[i].capture_t) continue; // can't be on time
        if (nodes[i].t + 1 == nodes[i].capture_t) continue;   // impossible
        
        first_step[i] = true;
        ans = max(ans, nodes[i].size);
    }
    
    /* Step 2 */
    auto second_time = [=](int i, int j){
        return max(nodes[1].dist[i], nodes[i].t + 1) + nodes[i].dist[j];
    };
        
    for (int i = 1; i <= n; i++) {
        if (!first_step[i]) continue;
        for (int j = 1; j <= n; j++) {
            if (!first_step[j]) continue;
            
            if (nodes[i].is_child[j]) continue;
            if (nodes[j].is_child[i]) continue;
           
            if (second_time(i, j) >= nodes[j].capture_t) continue;
            second_step[i][j] = true;
            ans = max(ans, nodes[i].size + nodes[j].size);
        }
    }
    
    /* Step 3 */
    auto third_time = [=](int i, int j, int k) {
        return max(second_time(i, j), nodes[j].t + 1) + nodes[j].dist[k];
    };
    
    auto add_val = [](int tab[], int pos, int val) {
        while(pos < 2*MAX_N) {
            tab[pos] = max(tab[pos], val);
            pos += (pos & -pos);
        }
    };
    auto get_val = [](int tab[], int max_pos) {
        int val = 0;
        int pos = max_pos;
        while(pos > 0) {
            val = max(val, tab[pos]);
            pos -= (pos & -pos);
        }
        return val;
    };
    
    /* Wybrać środkowy wierzchołek dla trójki */
    for (int j = 1; j <= n; j++) {
        /* Drzewa prefiksowe trzymają wierzchołki 
         * uporządkowane w kolejności inorder i postorder */
        for (int i = 0; i < 2*MAX_N; i++)
            pre[i] = post[i] = 0;
        
        /* Wierzchołki do wstawienia w kolejności najwcześniejszego czasu, 
         * w którym wychodząc z j damy jeszcze radę (tj. porządek po 
         * nodes[v].capture_t - nodes[v].dist[j]. Na końcu wektora są te, 
         * które dodajemy najwcześniej */
        vector<int> to_tree;
        for (int k = 1; k <= n; k++) {
            if (!second_step[j][k]) continue;
            to_tree.push_back(k);
        }
        sort(to_tree.begin(), to_tree.end(), 
            [=](int a, int b){ 
                return nodes[a].capture_t - nodes[a].dist[j] 
                        < nodes[b].capture_t - nodes[b].dist[j]; 
            });
            
        /* Przetwarzać pary pierwszy-drugi w kolejności 
         * malejących czasów wejścia do wierzchołka drugiego */
        vector<int> to_cons;
        for (int i = 1; i <= n; i++) {
            if (!second_step[i][j]) continue;
            to_cons.push_back(i);
        }
        sort(to_cons.begin(), to_cons.end(), 
            [=](int a, int b){ 
                return second_time(a, j) > second_time(b, j); 
            });
            
        for (int i : to_cons) {
            while(!to_tree.empty() && 
                    third_time(i, j, to_tree.back()) < 
                        nodes[to_tree.back()].capture_t) {
                
                int k = to_tree.back(); to_tree.pop_back();
                
                /* We will ask about preorders not smaller than some val */
                add_val(pre, 2*MAX_N - nodes[k].preorder, nodes[k].size);
                
                /* We will ask about postorders not greater than some val */
                add_val(post, nodes[k].postorder, nodes[k].size);
            }
            
            ans = max(ans, nodes[i].size + nodes[j].size + get_val(pre, 2*MAX_N - nodes[i].postorder));
            ans = max(ans, nodes[i].size + nodes[j].size + get_val(post, nodes[i].preorder));
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
