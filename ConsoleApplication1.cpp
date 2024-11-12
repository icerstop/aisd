#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <locale.h>
#include <fstream>

struct Item {
	int value, weight;
	Item(int value, int weight) : value(value), weight(weight)
	{}
};

void knapSack(int W, std::vector<Item>& items) {
	int n = items.size();
	std::vector<std::vector<int>> K(n + 1, std::vector<int>(W + 1));
	int i, w;

	for (i = 0; i <= n; i++) {
		for (w = 0; w <= W; w++) {
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (items[i - 1].weight <= w)
				K[i][w] = std::max(items[i - 1].value + K[i - 1][w - items[i - 1].weight], K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}

	int res = K[n][W];
	std::cout << "Maximal value: " << res << std::endl;

	w = W;
	for (i = n; i > 0 && res > 0; i--) {
		if (res == K[i - 1][w])
			continue;
		else {
			std::cout << "Loaded container with value " << items[i - 1].value << " and weight " << items[i - 1].weight << "\n";
			res = res - items[i - 1].value;
			w = w - items[i - 1].weight;
		}
	}
}


bool comp(const Item& a, const Item& b) {
	double r1 = (double)a.value / a.weight;
	double r2 = (double)b.value / b.weight;
	return r1 > r2;
}

void greedyKnapSack(std::vector<Item>& items, int W) {
	sort(items.begin(), items.end(), comp);

	int curWeight = 0;
	double finalvalue = 0.0;

	for (auto& item : items) {
		if (curWeight + item.weight <= W) {
			curWeight += item.weight;
			finalvalue += item.value;
			std::cout << "Loaded container with value " << item.value << " and weight " << item.weight << "\n";
		}
	}

	std::cout << "Maximal value: " << finalvalue;
}

int main() {
	setlocale(LC_CTYPE, "Polish");
	int choice, n, b;
	while(true){
		std::cout << "1. Losowe generowanie." << std::endl;
		std::cout << "2. Wczytanie z pliku." << std::endl;
		std::cout << "3. Wyjœcie" << std::endl;
		std::cout << std::endl;
		std::cout << "Wybór: ";
		std::cin >> choice;
		switch (choice) {
			case 1: {
				system("cls");
				std::cout << "Podaj ³adownoœæ statku: ";
				std::cin >> b;
				std::cout << std::endl;
				std::cout << "Podaj liczbê kontenerów: ";
				std::cin >> n;
				std::cout << std::endl;
				system("cls");

		}
			case 2: {
				std::ifstream file("data.txt");
				if (file.is_open()) {
					// Dynamic Programming
					int n, W;
					file >> n;
					std::cout << "Liczba kontenerów: " << n << std::endl;
					std::vector<Item> items_dp;

					for (int i = 0; i < n; i++) {
						int weight, value;
						file >> weight >> value;
						items_dp.push_back(Item(value, weight));
					}

					file >> W;
					std::cout << "£adownoœæ statku: " << W << std::endl;
					std::cout << std::endl;
					std::cout << "Algorytm dynamiczny: " << std::endl;
					knapSack(W, items_dp);
					std::cout << std::endl;

					// Reset file pointer to beginning for Greedy Algorithm
					file.clear();
					file.seekg(0, std::ios::beg);

					// Greedy Algorithm
					file >> n;
					std::vector<Item> items;

					for (int i = 0; i < n; i++) {
						int weight, value;
						file >> weight >> value;
						items.push_back(Item(value, weight));
					}

					file >> W;
					std::cout << std::endl;
					std::cout << "Algorytm zach³anny:" << std::endl;
					greedyKnapSack(items, W);
					std::cout << std::endl;
					std::cout << "Naciœnij enter, aby kontynuowaæ..." << std::endl;
					std::cin.ignore();
					std::cin.get(); 
				}
				else {
					std::cout << "Unable to open file";
				}
				break;
		}
			case 3: {
				return 0;
			}
		}
	}
}