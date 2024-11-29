#include <bits/stdc++.h>

using namespace std;

vector<int> p;
vector<pair<int, int>> mst_g;

// Функция для нахождения представителя множества (сжатие путей)
int dsu_get(int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

// Функция для объединения двух множеств (рандомизация для балансировки)
void dsu_unite(int a, int b) {
    a = dsu_get(a);
    b = dsu_get(b);
    if (rand() & 1) 
        swap(a, b);
    if (a != b)
        p[a] = b;
}

int n, m;
vector<pair<int, pair<int, int>>> g;

int cost = 0;
vector<pair<int, int>> result;


int findMSTwithDSU() {
    // Инициализация DSU
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }

    // Сортировка рёбер по весу
    sort(g.begin(), g.end());

    // Обработка рёбер
    for (int i = 0; i < m; ++i) {
        int w = g[i].first;
        int a = g[i].second.first;
        int b = g[i].second.second;

        // Если вершины принадлежат разным компонентам, добавляем ребро в MST
        if (dsu_get(a) != dsu_get(b)) {
            cost += w;
            result.push_back({a, b});
            dsu_unite(a, b);
        }
    }
}

int main() {
    // Ввод количества вершин и рёбер
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;

    cout << "Введите рёбра в формате: вес вершина1 вершина2" << endl;
    for (int i = 0; i < m; ++i) {
        int w, a, b;
        cin >> w >> a >> b;
        g.push_back({w, {a, b}});
    }

    findMSTwithDSU();

    // Вывод результата
    cout << "Стоимость минимального остовного дерева: " << cost << endl;
    cout << "Рёбра в остовном дереве:" << endl;
    for (const auto& x : result) {
        cout << x.first << " - " << x.second << endl;
    }

    return 0;
}
