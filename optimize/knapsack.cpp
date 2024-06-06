#include <iostream>
#include <vector>
#include <algorithm>

bool cmp(std::pair<double, int> a, std::pair<double, int> b){
    return a.first > b.first;
};

int greedy(std::vector<int>& weight, std::vector<int>& value, int cap){
    int n = weight.size();

    // massiv for ratio
    std::vector<std::pair<double, int>> ratio(n);
    for(int i = 0; i < n; i++){
        ratio[i] = {double(value[i]) / weight[i], i};
    }

    sort(ratio.begin(), ratio.end(), cmp);

    int res = 0;
    for (auto& item : ratio){
        int index = item.second;
        if (weight[index] <= cap){
            cap -= weight[index];
            res += value[index];
        }
    }

    return res;
}

void dynamic(std::vector<int>& weight, std::vector<int>& value, int cap, std::vector<std::vector<int>>& dp){
    int n = weight.size();

    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= cap; j++){
            dp[i][j] = dp[i - 1][j];

            if (j >= weight[i-1]){
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - weight[i - 1]] + value[i - 1]);
            }
        }
    }

    std::cout << dp[n][cap];
}

void trace_back(std::vector<int>& weight, std::vector<int>& value, int cap, std::vector<std::vector<int>>& dp) {
    int n = weight.size();
    std::vector<int> picked_items;
    while (n > 0) {
        if (dp[n][cap] != dp[n - 1][cap]) { // значит вещ п выбран
            picked_items.push_back(n - 1);
            cap -= weight[n - 1];
        }
        n--;
    }

    std::reverse(picked_items.begin(), picked_items.end());
    for (int index : picked_items)
        std::cout << index << ' ';
    std::cout << std::endl;
}

int main(){
    int n = 4;

    std::vector<int> weight(n), value(n);
   
    srand(time(NULL));
    int W = 0;
    for (int i = 0; i < n; i++) {
        weight[i] = rand() % 100 + 1;
        value[i] = rand() % 100 + 1;
        W += weight[i];
    }
    int cap = W / 2; 


    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(cap + 1, 0));

    std::cout << "Greedy: " << std::endl << greedy(weight, value, cap) << std::endl << std::endl;
    std::cout << "Dynamic: " << std::endl;
    dynamic(weight, value, cap, dp);
    std::cout << std::endl << std::endl;

    std::cout << "Method: ";
    if (n <= 30){
    trace_back(weight, value, cap, dp);
    };
}