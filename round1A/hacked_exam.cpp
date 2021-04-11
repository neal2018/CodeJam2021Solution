#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define i128 __int128_t
// #define LOCAL
// #define IO
ll INF = 1e18;

i128 gcd(i128 a, i128 b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

string toString(i128 num) {
    string str = "";
    while (num != 0) {
        int digit = num % 10;
        str = to_string(digit) + str;
        num /= 10;
    }
    return str == "" ? "0" : str;
}

int main(int, char**) {
#ifdef IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
#ifdef LOCAL
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif
    const int MAX_Q = 150;
    i128 C[MAX_Q][MAX_Q];  // combination numbers
    for (int i = 0; i < MAX_Q; ++i) {
        C[0][i] = 0;
        C[i][0] = 1;
    }
    for (int i = 1; i < MAX_Q; ++i) {
        for (int j = 1; j < MAX_Q; ++j) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]);
        }
    }
    int total_cases_number;
    cin >> total_cases_number;
    for (int case_num = 1; case_num <= total_cases_number; case_num++) {
        ll N, Q;
        cin >> N >> Q;
        vector<string> A(3);
        vector<ll> scores(3);
        for (int i = 0; i < N; i++) {
            cin >> A[i] >> scores[i];
        }
        // fill the rest, pretending always three people
        for (int i = N; i < 3; i++) {
            A[i] = A[i - 1];
            scores[i] = scores[i - 1];
        }
        // flip, pretending first people always anwers T
        for (int i = 1; i < 3; i++) {
            for (int j = 0; j < Q; j++) {
                if (A[0][j] == 'F') {
                    A[i][j] ^= 'T' ^ 'F';
                }
            }
        }
        vector<ll> type_cnt(4);  // count # of problems of each types
        for (int i = 0; i < Q; i++) {
            if (A[1][i] == 'T' && A[2][i] == 'T') {
                type_cnt[0]++;
            } else if (A[1][i] == 'F' && A[2][i] == 'T') {
                type_cnt[1]++;
            } else if (A[1][i] == 'T' && A[2][i] == 'F') {
                type_cnt[2]++;
            } else {
                type_cnt[3]++;
            }
        }
        i128 total_ways = 0;  // # of combinations of answers fitting scores
        vector<i128> choose_T(4);  // points get if choose T in each type
        vector<i128> choose_F(4);  // points get if choose F in each type
        vector<ll> p(4);           // x0's # of answered right in each type
        // p0 + p1 + p2 + p3 = x0
        // p0 - p1 + p2 - p3 = x1 - type_cnt[1] - type_cnt[3]
        // p0 + p1 - p2 - p3 = x2 - type_cnt[2] - type_cnt[3]
        // find all possible (p0, p1, p2, p3)
        ll y0 = scores[0];
        ll y1 = scores[1] - type_cnt[1] - type_cnt[3];
        ll y2 = scores[2] - type_cnt[2] - type_cnt[3];
        for (p[0] = 0; p[0] <= type_cnt[0]; p[0]++) {
            p[1] = y0 + y2 - 2 * p[0];
            if (p[1] % 2 != 0 || p[1] > 2 * type_cnt[1] || p[1] < 0) {
                continue;
            }
            p[1] /= 2;
            p[2] = y0 + y1 - 2 * p[0];
            if (p[2] % 2 != 0 || p[2] > 2 * type_cnt[2] || p[2] < 0) {
                continue;
            }
            p[2] /= 2;
            p[3] = 2 * p[0] - y1 - y2;
            if (p[3] % 2 != 0 || p[3] > 2 * type_cnt[3] || p[3] < 0) {
                continue;
            }
            p[3] /= 2;
            i128 numbers = C[type_cnt[0]][p[0]] * C[type_cnt[1]][p[1]] *
                           C[type_cnt[2]][p[2]] * C[type_cnt[3]][p[3]];
            total_ways += numbers;
            for (int i = 0; i < 4; i++) {
                choose_T[i] += numbers * p[i];
                choose_F[i] += numbers * (type_cnt[i] - p[i]);
            }
        }
        vector<char> type2answer(4, 'T');
        i128 corrects = 0;
        for (int i = 0; i < 4; i++) {
            if (choose_F[i] > choose_T[i]) {
                type2answer[i] = 'F';
            }
            corrects += max(choose_F[i], choose_T[i]);
        }
        i128 my_gcd = gcd(corrects, total_ways);
        corrects /= my_gcd;
        total_ways /= my_gcd;
        string answers = A[0];
        // flip back
        for (int i = 0; i < Q; i++) {
            if ((A[1][i] == 'T' && A[2][i] == 'T' && type2answer[0] == 'F') ||
                (A[1][i] == 'F' && A[2][i] == 'T' && type2answer[1] == 'F') ||
                (A[1][i] == 'T' && A[2][i] == 'F' && type2answer[2] == 'F') ||
                (A[1][i] == 'F' && A[2][i] == 'F' && type2answer[3] == 'F')) {
                answers[i] ^= 'T' ^ 'F';
            }
        }
        cout << "Case #" << case_num << ": " << answers << " "
             << toString(corrects) << "/" << toString(total_ways) << endl;
    }
    return 0;
}