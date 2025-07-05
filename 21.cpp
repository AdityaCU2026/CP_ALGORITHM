// LCA->(Binary Lifting)

const int MAXN = 1e5 + 5;
const int LOG = 20;

vector<int> tree[MAXN];
int up[MAXN][LOG];  // up[u][j] is the 2^j-th ancestor of u
int depth[MAXN];

void dfs(int node, int parent) {
    up[node][0] = parent;
    for (int i = 1; i < LOG; i++) {
        if (up[node][i - 1] != -1)
            up[node][i] = up[up[node][i - 1]][i - 1];
        else
            up[node][i] = -1;
    }

    for (int child : tree[node]) {
        if (child != parent) {
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    // 1. Lift u up to depth of v
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != -1 && depth[up[u][i]] >= depth[v])
            u = up[u][i];
    }

    if (u == v)
        return u;

    // 2. Lift u and v up together
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != -1 && up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}
void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    memset(up, -1, sizeof up);
    depth[1] = 0;
    dfs(1, -1);  // assuming 1 is root

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }

    return 0;
}
