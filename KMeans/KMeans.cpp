#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <limits>

struct Point{
    double x, y;
};

struct Edge{
    int u, v;
    double weight;
};

double euclideanDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Найти корень сжатием путей
int find(std::vector<int>& parent, int i){
    if (parent[i] != i){
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

//Объединение двух множеств по рангу
void unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v){
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rootU != rootV){
        if (rank[rootU] < rank[rootV]){  // Сделать дерево меньшей высоты поддеревом другого дерева
            parent[rootU] = rootV;
        }
        else if (rank[rootU] > rank[rootV]){
            parent[rootV] = rootU;
        }
        else{
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int main(){
    int N = 50;
    int K = 5;
    std::vector<Point> points(N);

    // Генерация N случайных точек
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-5, 5);
    for (int i = 0; i < N; ++i) {
        points[i] = {dis(gen), dis(gen)};
    }

    // Построение полного взвешенного графа
    std::vector<Edge> edges;
    for (int i = 0; i < N; ++i){
        for (int j = i + 1; j < N; ++j){
            double d = euclideanDistance(points[i], points[j]);
            edges.push_back({i, j, d});
        }
    }

    // Построение MST
    
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
        return a.weight < b.weight;
    });

    std::vector<int> parent(N), rank(N, 0);
    std::iota(parent.begin(), parent.end(), 0);

    std::vector<Edge> MST;
    // Если добавление новой ребра не образует цикл, то можно добавлять
    for (const auto& edge : edges){
        if (find(parent, edge.u) != find(parent, edge.v)){
            MST.push_back(edge);
            unionSets(parent, rank, edge.u, edge.v);
        }
    }

    // по начальным N-K ребрам отсортированного массива построить матрицу смежности неориентированного графа и выделить K компонент связности (вершины каждой компоненты образуют один кластер)
    std::vector<Edge> nkEdges(MST.begin(), MST.end() - (K - 1));
    std::vector<std::vector<int>> adjMatrix(N, std::vector<int>(N, 0));
    for (const auto& edge : nkEdges) {
        adjMatrix[edge.u][edge.v] = 1;
        adjMatrix[edge.v][edge.u] = 1;
    }

    // Reset 
    std::iota(parent.begin(), parent.end(), 0);
    std::fill(rank.begin(), rank.end(), 0);

    for (const auto &edge: nkEdges){
        unionSets(parent, rank, edge.u, edge.v);
    }

    std::vector<std::vector<int>> clusters(N);
    for (int i = 0; i < N; ++i){
        clusters[find(parent, i)].push_back(i);
    }

    // Удалить empty vector
    clusters.erase(std::remove_if(clusters.begin(), clusters.end(), [](const std::vector<int>& c) {
        return c.empty();
    }), clusters.end());

    // Cluster

    // iterate every clusters
    for (const auto& cluster : clusters) {
        int num_vertices = cluster.size();

        double min_x = std::numeric_limits<double>::max();
        double max_x = -std::numeric_limits<double>::max();
        double min_y = std::numeric_limits<double>::max();
        double max_y = -std::numeric_limits<double>::max();
        Point Centroid = {0, 0};

        for (int i : cluster){
            const auto& p = points[i];
            if (p.x < min_x) min_x = p.x;
            if (p.x > max_x) max_x = p.x;
            if (p.y < min_y) min_y = p.y;
            if (p.y > max_y) max_y = p.y;
            Centroid.x += p.x;
            Centroid.y += p.y;
        }
        Centroid.x /= num_vertices;
        Centroid.y /= num_vertices;
        std::cout << "Cluster with " << num_vertices << " vertices:" << std::endl;
        std::cout << "Min coordinate: (" << min_x << ", " << min_y << ")" << std::endl;
        std::cout << "Max coordinate: (" << max_x << ", " << max_y << ")" << std::endl;
        std::cout << "Centroid: (" << Centroid.x << ", " << Centroid.y << ")" << std::endl << std::endl;;
    }
    return 0;
}