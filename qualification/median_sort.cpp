#include <bits/stdc++.h>
using namespace std;
#define ll long long
// #define LOCAL
// #define IO
ll INF = 1e18;

int main(int, char **) {
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
    int N, Q;
    cin >> N >> Q;
    int answer;  // receive answer from judge
    auto ask = [&](int a, int b, int c) {
        cout << a << " " << b << " " << c << endl;
        cin >> answer;
    };
    for (int case_num = 1; case_num <= total_cases_number; case_num++) {
        vector<int> A = {1, 2};  // the required result
        // insert 3,4,5,...,N to A
        for (int i = 3; i <= N; i++) {
            int left = 0;
            int right = i - 2;
            // ternary search the insertion index
            while (left <= right) {
                if (left == right) {
                    // if the same, extend a bit to identify the insertion index
                    // can not gain 1.58 bits from this query
                    if (left == 0) {
                        right++;
                    } else {
                        left--;
                    }
                }
                int mid1 = (left + left + right) / 3;
                int mid2 = (left + right + right + 1) / 3;
                // +1 to prevent mid1 == mid2
                ask(A[mid1], A[mid2], i);
                if (answer == -1) {
                    return 0;
                }
                // update left and right
                if (answer == A[mid1]) {
                    right = mid1 - 1;
                } else if (answer == A[mid2]) {
                    left = mid2 + 1;
                } else {
                    left = mid1 + 1;
                    right = mid2 - 1;
                }
            }
            A.insert(A.begin() + left, i);
        }
        for (auto &i : A) {
            cout << " " << i;
        }
        cout << endl;
        cin >> answer;
        if (answer == -1) {
            return 0;
        }
    }
    return 0;
}