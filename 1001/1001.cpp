#include <bits/stdc++.h>

using namespace std;

const int N0 = 1000 + 5;
const int N = 1000 * 1000 * 2 + 5;
const long long INFTY = 0x7f7f7f7f7f7f7f7fll;

bool v[N];
long long d[N];
int id[N0][N0][2];
vector<pair<int, int> > e[N];

void addedge(int u, int v, int w) {
    e[u].push_back(make_pair(v, w));
    e[v].push_back(make_pair(u, w));
}

long long spfa(int s, int t, int cnt) {
    for (int i = 1; i <= cnt; i++) {
        v[i] = false;
        d[i] = INFTY;
    }
    queue<int> q;
    v[s] = true;
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        v[x] = false;
        for (vector<pair<int, int> >::iterator it = e[x].begin(); it != e[x].end(); it++) {
            int y = it->first, w = it->second;
            if (d[x] + w < d[y]) {
                d[y] = d[x] + w;
                if (!v[y]) {
                    v[y] = true;
                    q.push(y);
                }
            }
        }
    }
    return d[t];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 1 && m == 1) {
        puts("0");
        return 0;
    }
    if (n == 1 || m == 1) {
        int mi = INT_MAX;
        for (int i = 1; i < m + n - 1; i++) {
            int x;
            scanf("%d", &x);
            mi = min(mi, x);
        }
        printf("%d\n", mi);
        return 0;
    }
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            id[i][j][0] = ++cnt;
            id[i][j][1] = ++cnt;
        }
    }
    int s = ++cnt;
    int t = ++cnt;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            int x;
            scanf("%d", &x);
            if (i == 1) {
                addedge(id[i][j][1], s, x);
            } else if (i == n) {
                addedge(id[i - 1][j][0], t, x);
            } else {
                addedge(id[i - 1][j][0], id[i][j][1], x);
            }
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            if (j == 1) {
                addedge(id[i][j][0], t, x);
            } else if (j == m) {
                addedge(id[i][j - 1][1], s, x);
            } else {
                addedge(id[i][j - 1][1], id[i][j][0], x);
            }
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            int x;
            scanf("%d", &x);
            addedge(id[i][j][0], id[i][j][1], x);
        }
    }
    printf("%lld\n", spfa(s, t, cnt));
    return 0;
}
