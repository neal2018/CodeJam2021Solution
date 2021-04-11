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
        ll N;
        cin >> N;
        vector<string> X(N);
        ll res = 0;
        for (int i = 0; i < N; i++) {
            cin >> X[i];
            if (i > 0) {
                ll size = X[i].size();
                ll size_pre = X[i - 1].size();
                if (size == size_pre && X[i] <= X[i - 1]) {
                    X[i] += '0';
                    res += 1;
                }
                if (size_pre > size) {
                    // append 9 to be the same size as X[i-1]
                    string nines = X[i] + string(size_pre - size, '9');
                    // append 0 to be the same size as X[i-1]
                    string zeros = X[i] + string(size_pre - size, '0');
                    if (zeros > X[i - 1]) {
                        res += size_pre - size;
                        X[i] = zeros;
                    } else if (X[i - 1] < nines) {
                        res += size_pre - size;
                        // if X[i] is a prefix of both X[i-1] and X[i-1] + 1
                        // then we can make X[i] = X[i-1] + 1
                        X[i] = X[i - 1];
                        int j = size_pre - 1;
                        while (X[i][j] == '9') {
                            j--;
                        }
                        X[i][j] = X[i][j] + 1;
                        for (j++; j < size_pre; j++) {
                            X[i][j] = '0';
                        }
                    } else {
                        // we have to increase one digit
                        res += size_pre - size + 1;
                        X[i] = zeros + '0';
                    }
                }
            }
        }
        cout << "Case #" << case_num << ": " << res << endl;
    }
    return 0;
}