#include <vector>
#include <queue>
#include <climits>
#include <iostream>

using namespace std;

int nodes, src, dest;
vector<int> dist, work;
queue<int> q;

struct Edge {
  int to, rev;
  int f, cap;
};

vector<vector<Edge> > g;

void addEdge(int s, int t, int cap);
bool dinic_bfs();
int dinic_dfs(int u, int f);
int maxFlow();

int main() {
    int n, m, c, u, v;
    cin >> n >> m;

    src = 0;
    dest = n - 1;

    dist.assign(n + 1, 0);
    work.assign(n + 1, 0);
    g.assign(n + 1, vector<Edge>());
    nodes = n;

    for (int i = 0; i < m; ++i){
        cin >> u >> v >> c;
        addEdge(u - 1, v - 1, c);
    }
    cout << maxFlow() << endl;
}

/* Добавляет ребра. Если cap указать для обоих ребер, то тогда
 * программа будет работать с неориентированным графом.
 */
void addEdge(int s, int t, int cap){
  Edge a = {t, g[t].size(), 0, cap};
  Edge b = {s, g[s].size(), 0, 0};
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(dist.begin(), dist.end(), -1);
  dist[src] = 0;
  q.push(src);
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for (int j = 0; j < (int) g[u].size(); j++) {
      Edge &e = g[u][j];
      int v = e.to;
      if (dist[v] < 0 && e.f < e.cap) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
  return dist[dest] >= 0;
}

int dinic_dfs(int u, int f) {
  if (u == dest)
    return f;
  for (int &i = work[u]; i < (int) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    int v = e.to;
    if (dist[v] == dist[u] + 1) {
      int df = dinic_dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
  }
  return 0;
}

int maxFlow() {
  int result = 0;
  while (dinic_bfs()) {
    fill(work.begin(), work.end(), 0);
    while (int delta = dinic_dfs(src, INT_MAX))
      result += delta;
  }
  return result;
}


