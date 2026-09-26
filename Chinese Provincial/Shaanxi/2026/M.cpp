#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n, m, A, B, ans;
int mp[3000][3000], dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int main() {
	cin >> n >> m >> A >> B;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			if (c == '#') mp[i][j] = -1;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (mp[i][j] != -1) {
				ll cnt = 0;
				for (int k = 0, x, y; k < 4; k++) {
					x = i + dx[k];
					y = j + dy[k];
					if (x < 1 || x > n || y < 1 || y > m) continue;
					if (mp[x][y] != -1) cnt++;
				}
				if (A > B - 2 * cnt)
					mp[i][j] = 1;
				else
					mp[i][j] = 2;
			}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (mp[i][j] != -1) {
				ll cnt = 0;
				for (int k = 0, x, y; k < 4; k++) {
					x = i + dx[k];
					y = j + dy[k];
					if (x < 1 || x > n || y < 1 || y > m) continue;
					if (mp[x][y] == mp[i][j]) cnt++;
				}
				if (mp[i][j] == 1)
					ans += A + cnt;
				else
					ans += B - cnt;
			}
	cout << ans << '\n';
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mp[i][j] == -1)
				cout << "#";
			else if (mp[i][j] == 1)
				cout << "A";
			else
				cout << "B";
		}
		cout << '\n';
	}
	return 0;
}