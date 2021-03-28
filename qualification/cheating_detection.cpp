#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
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
    const int NUM = 100;
    const int Q_NUM = 10000;
    int total_cases_number;
    cin >> total_cases_number;
    int P;
    cin >> P;
    for (int case_num = 1; case_num <= total_cases_number; case_num++) {
        vector<string> answers(NUM);
        vector<ld> player_mean(NUM);      // the correct rate of each player
        vector<ld> question_mean(Q_NUM);  // the correct rate of each question
        // calculate player mean and question mean
        for (int i = 0; i < NUM; i++) {
            cin >> answers[i];
            for (int j = 0; j < Q_NUM; j++) {
                if (answers[i][j] == '1') {
                    player_mean[i]++;
                    question_mean[j]++;
                }
            }
            player_mean[i] /= Q_NUM;
        }
        for (int i = 0; i < Q_NUM; i++) {
            question_mean[i] /= NUM;
        }
        // calculate the index for each player:
        // index[i] = \sum_j 1/(1 - player_mean[i])^2 * question_mean[j]^4 for
        // wrong answers
        vector<ld> index(NUM);
        for (int i = 0; i < NUM; i++) {
            for (int j = 0; j < Q_NUM; j++) {
                if (answers[i][j] == '0') {
                    index[i] += pow((1.0 / (1 - player_mean[i])), 2) *
                                pow(question_mean[j], 4.0);
                }
            }
        }
        // find the max index
        // correctness is near 100%
        int result = 0;
        for (int i = 0; i < NUM; i++) {
            if (index[i] > index[result]) {
                result = i;
            }
        }
        cout << "Case #" << case_num << ": " << result + 1 << endl;
    }
    return 0;
}