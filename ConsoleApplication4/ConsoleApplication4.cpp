#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct Item {
    std::string name;
    int weight;
    int value;
};

int main() {
    setlocale(LC_ALL, "RU");
    std::vector<Item> items = {
        {"Ноутбук", 4, 12},
        {"Книга", 1, 10},
        {"Зонт", 3, 8},
        {"Телефон", 1, 20},
        {"Рюкзак", 2, 4},
        {"Бутылка воды", 1, 2},
        {"Камера", 5, 15},
        {"Планшет", 3, 9}
    };

    int n = items.size(); 
    int W = 15;           

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i - 1][w];

            if (items[i - 1].weight <= w) {
                int newValue = dp[i - 1][w - items[i - 1].weight] + items[i - 1].value;
                if (newValue > dp[i][w]) {
                    dp[i][w] = newValue;
                }
            }
        }
    }

    int maxValue = dp[n][W];
    std::cout << "Максимальная стоимость: " << maxValue << std::endl;

    std::vector<std::string> selectedItems;
    int currentW = W;
    for (int i = n; i > 0; --i) {
        if (dp[i][currentW] != dp[i - 1][currentW]) {
            selectedItems.push_back(items[i - 1].name);
            currentW -= items[i - 1].weight;
        }
    }

    std::cout << "Выбранные предметы:" << std::endl;
    for (const auto& item : selectedItems) {
        std::cout << "- " << item << std::endl;
    }

    std::cout << "\nDP таблица (для отладки):" << std::endl;
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            std::cout << std::setw(4) << dp[i][w];
        }
        std::cout << std::endl;
    }

    return 0;
}


