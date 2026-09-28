#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
const int N = 1e5 + 10;

struct Fen {
    int mu, zi;
    bool operator<(const Fen &other) const {
        return zi * other.mu < mu * other.zi;
    }
    bool operator<=(const Fen &other) const {
        return zi * other.mu <= mu * other.zi;
    }
};

struct Node {
    Fen tim;
    int len;
    bool operator<(const Node &other) const {
        if (len != other.len)
            return len > other.len;
        return tim < other.tim;
    }
};

struct Worm {
    int l, r, v;
};

struct Op {
    Fen tim;
    int type;
    Worm x;
} op[N * 2];

int n, x, cnt = 0, ans = 0;

priority_queue<Node> q;

bool cmpTim(Op a, Op b) { return a.tim < b.tim; }

void solve() {
    Worm tmp;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> tmp.l >> tmp.r >> tmp.v;
        if (tmp.l <= x) {
            if (x - tmp.r <= 0) {
                op[++cnt].tim = (Fen){1, 0};
                op[cnt].type = 1;
                op[cnt].x = tmp;
            } else {
                op[++cnt].tim = (Fen){tmp.v, x - tmp.r};
                op[cnt].type = 1;
                op[cnt].x = tmp;
            }
            if (x - tmp.l <= 0) {
                op[++cnt].tim = (Fen){1, 0};
                op[cnt].type = 2;
                op[cnt].x = tmp;
            } else {
                op[++cnt].tim = (Fen){tmp.v, x - tmp.l};
                op[cnt].type = 2;
                op[cnt].x = tmp;
            }
        }
    }
    op[++cnt].tim = (Fen){1, 3000000000ll};
    sort(op + 1, op + 1 + cnt, cmpTim);
    /*for (int i = 1; i <= cnt; i++) {
        cout << op[i].tim.zi << "/" << op[i].tim.mu << endl;
    }*/
    Fen curT = (Fen){1, -1};
    int top = 1;
    while (top <= cnt) {
        if (curT < op[top].tim) {
            curT = op[top].tim;
            // cout << curT.zi << "/" << curT.mu << endl;
            // int flag = 0;
            while (op[top].tim <= curT) {
                if (op[top].type == 1) {
                    q.push((Node){(Fen){op[top].x.v, x - op[top].x.l},
                                  op[top].x.r - op[top].x.l});
                    // flag = 1;
                    /*cout << "in: " << op[top].x.r - op[top].x.l
                         << ", tim: " << x - op[top].x.l << "/" << op[top].x.v
                         << endl;*/
                }
                top++;
            }
            while (!q.empty() && q.top().tim < curT) {
                /*cout << "1out: " << q.top().len << ", tim: " << q.top().tim.zi
                     << "/" << q.top().tim.mu << endl;*/
                q.pop();
            }
            if (!q.empty()) {
                ans = max(ans, q.top().len);
                // cout << "1ans: " << q.top().len << endl;
            }
            while (!q.empty() && q.top().tim <= curT) {
                /*cout << "2out: " << q.top().len << ", tim: " << q.top().tim.zi
                     << "/" << q.top().tim.mu << endl;*/
                q.pop();
            }
            if (!q.empty()) {
                ans = max(ans, q.top().len);
            }
            // cout << "2ans: " << q.top().len << endl;
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
