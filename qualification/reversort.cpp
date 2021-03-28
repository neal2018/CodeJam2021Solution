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
        int N;
        cin >> N;
        vector<int> L(N);
        for (int i = 0; i < N; i++) {
            cin >> L[i];
        }
        int cost = 0;
        // implementation the pseudo code in hte problem
        for (int i = 0; i < N - 1; i++) {
            int target = i;
            // find the index of the minimal number in [i, N-1]
            for (int j = i; j < N; j++) {
                if (L[j] < L[target]) {
                    target = j;
                }
            }
            reverse(L.begin() + i, L.begin() + target + 1);
            cost += (target - i + 1);
        }
        cout << "Case #" << case_num << ": " << cost << endl;
    }
    return 0;
}