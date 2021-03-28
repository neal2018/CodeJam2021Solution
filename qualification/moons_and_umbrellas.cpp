#include <bits/stdc++.h>
using namespace std;
#define ll long long
// #define LOCAL
// #define IO
ll INF = 1e18;

int main(int, char**) {
#ifdef IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
#ifdef LOCAL
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif

    int total_cases_number;
    cin >> total_cases_number;
    for (int case_num = 1; case_num <= total_cases_number; case_num++) {
        int X, Y;
        string S;
        cin >> X >> Y >> S;
        int n = S.size();
        vector<vector<ll>> dp(n, vector<ll>(2, INF));
        // dp[i][j]: the cost of dp[:i] ending with j (C:0, J:1)
        // inf if not possible
        if (S[0] != 'J') {
            dp[0][0] = 0;
        }
        if (S[0] != 'C') {
            dp[0][1] = 0;
        }
        for (int i = 1; i < n; i++) {
            if (S[i] != 'J') {
                // can set S[i] to 'C'
                // if previous one is 'J', need to pay Y for "JC"
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + Y);
            }
            if (S[i] != 'C') {
                // can set S[i] to 'J'
                // if previous one is 'C', need to pay X for "CJ"
                dp[i][1] = min(dp[i - 1][0] + X, dp[i - 1][1]);
            }
        }
        cout << "Case #" << case_num << ": ";
        cout << min(dp[n - 1][0], dp[n - 1][1]) << endl;
    }
    return 0;
}