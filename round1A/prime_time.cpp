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
        ll max_p = 500;
        vector<ll> P(max_p);  // the freq of each number
        ll M;
        cin >> M;
        ll sum = 0;
        for (int i = 0; i < M; i++) {
            ll p, n;
            cin >> p >> n;
            P[p] = n;
            sum += p * n;
        }
        ll res = 0;
        // notice that the range of the sum of the second group is small
        ll max_second_sum = 3273;  // (ln(4.99e17)/ln(499)) * 499
        // iterate all the possible value of first_sum
        for (ll i = 1; i < max_second_sum && sum - i > 0; i++) {
            ll first_sum = sum - i;
            ll second_sum = 0;   // equals i
            ll second_prod = 1;  // equals sum - i
            vector<ll> P_seen(max_p);
            bool found_factor = true;
            // factoring first_sum, check if their sum and prod meet the
            // requirements of the second group
            while (first_sum > 1 && found_factor) {
                found_factor = false;
                for (int j = 2; j < max_p; j++) {
                    if (first_sum % j == 0) {
                        // can not exceed the given numbers
                        if (P_seen[j] < P[j]) {
                            P_seen[j] += 1;
                            second_sum += j;
                            second_prod *= j;
                            first_sum /= j;
                            found_factor = true;
                        }
                        break;
                    }
                }
            }
            if (first_sum == 1 && second_sum == i && second_prod == sum - i) {
                res = max(res, second_prod);
            }
        }
        cout << "Case #" << case_num << ": " << res << endl;
    }
    return 0;
}