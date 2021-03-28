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
        int N, C;
        cin >> N >> C;
        cout << "Case #" << case_num << ":";
        int MAX = (N + 1) * N / 2 - 1;  // maximum is 2+3+..+N
        if (C < N - 1 || C > MAX) {
            cout << " IMPOSSIBLE" << endl;
            continue;
        }
        // assign 1,2,3,..,N to result
        vector<int> result(N);
        for (int i = 0; i < N; i++) {
            result[i] = i + 1;
        }
        // we go backward to find the target list
        // pre-subtract the cost of each turn by 1, so that the minimal cost is
        // 0 not 1
        C -= N - 1;
        for (int i = N - 1; i > 0; i--) {
            // simulate the i-th turn backwardly
            // if cost is zero, no need to continue
            if (C == 0) {
                break;
            }
            // in i-th turn, previous i-1 numbers are sorted (1,2,3,...,i-1)
            // the maximal cost we can spend in i-th turn is N-i-1
            // (remember the pre-subtract 1)
            // by moving number i to the last index
            int reverse_cost = min(C, N - i);
            C -= reverse_cost;
            // reverse the corresponding part
            reverse(result.begin() + i - 1, result.begin() + i + reverse_cost);
        }
        for (auto& x : result) {
            cout << " " << x;
        }
        cout << endl;
    }
    return 0;
}