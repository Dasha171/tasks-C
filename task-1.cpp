#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

const int MOD = 1e9 + 7;
const long long INF = 1e18;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

void dijkstra(int start, vector<long long>& dist, vector<vector<Edge>>& graph) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[start] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push(make_pair(0, start));
    
    while (!pq.empty()) {
        long long d = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        
        if (d > dist[v]) continue;
        
        for (size_t i = 0; i < graph[v].size(); i++) {
            Edge& edge = graph[v][i];
            if (dist[edge.to] > dist[v] + edge.weight) {
                dist[edge.to] = dist[v] + edge.weight;
                pq.push(make_pair(dist[edge.to], edge.to));
            }
        }
    }
}

void findPaths(int v, int end, vector<vector<Edge>>& graph, vector<long long>& dist,
              vector<int>& path, vector<vector<int>>& allPaths, set<int>& used) {
    if (v == end) {
        allPaths.push_back(path);
        return;
    }
    
    for (size_t i = 0; i < graph[v].size(); i++) {
        Edge& edge = graph[v][i];
        if (dist[edge.to] == dist[v] + edge.weight && used.find(edge.to) == used.end()) {
            path.push_back(edge.to);
            used.insert(edge.to);
            findPaths(edge.to, end, graph, dist, path, allPaths, used);
            used.erase(edge.to);
            path.pop_back();
        }
    }
}

bool pathsIntersect(const vector<int>& path1, const vector<int>& path2) {
    set<int> vertices1(path1.begin(), path1.end());
    for (size_t i = 0; i < path2.size(); i++) {
        if (vertices1.count(path2[i])) return true;
    }
    

    set<pair<int, int>> edges1;
    for (size_t i = 0; i < path1.size() - 1; i++) {
        int u = min(path1[i], path1[i + 1]);
        int v = max(path1[i], path1[i + 1]);
        edges1.insert(make_pair(u, v));
    }
    
    for (size_t i = 0; i < path2.size() - 1; i++) {
        int u = min(path2[i], path2[i + 1]);
        int v = max(path2[i], path2[i + 1]);
        if (edges1.count(make_pair(u, v))) return true;
    }
    
    return false;
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--; 
    
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        u--; v--; 
        graph[u].push_back(Edge(v, d));
        graph[v].push_back(Edge(u, d));
    }
    

    vector<long long> dist_s(n);
    dijkstra(s, dist_s, graph);
    

    vector<long long> dist_t(n);
    dijkstra(t, dist_t, graph);
    

    vector<vector<int>> paths_s_to_t;
    vector<int> path_s;
    path_s.push_back(s);
    set<int> used_s;
    used_s.insert(s);
    findPaths(s, t, graph, dist_s, path_s, paths_s_to_t, used_s);
    

    vector<vector<int>> paths_t_to_s;
    vector<int> path_t;
    path_t.push_back(t);
    set<int> used_t;
    used_t.insert(t);
    findPaths(t, s, graph, dist_t, path_t, paths_t_to_s, used_t);
    

    cout << "Number of paths from s to t: " << paths_s_to_t.size() << endl;
    cout << "Number of paths from t to s: " << paths_t_to_s.size() << endl;
    
    long long result = 0;
    for (size_t i = 0; i < paths_s_to_t.size(); i++) {
        for (size_t j = 0; j < paths_t_to_s.size(); j++) {
            if (!pathsIntersect(paths_s_to_t[i], paths_t_to_s[j])) {
                result = (result + 1) % MOD;
            }
        }
    }
    
    cout << result << endl;
    return 0;
}


// 4BAp5. 
//Непересекающиеся кратчайшие пути ограничение по времени на тест: 2 s ограничение по памяти на тест. 512 МВ
// На какой-то паре двое друзей Андрей и Вова решили сыграть в игру на взвешенном неориентированном графе. Граф состоит из ті вершин и т двухсторонних ребер, і-е ребро соединяет вершины и, и и и имеет длину d,.
// Андрей стартует в вершине в, а Вова — в вершине t. Оба начинают движение одновременно. Цель Андрея — как можно быстрее достичь вершины t, а цель Вовы - как можно быстрее добраться до вершины в.
// Сколькими способами они могут выбрать свои кратчайшие пути так, чтобы ни разу не пересечься (ни в вершине, ни по ребру)? Так как ответ может быть слишком большим, посчитайте его по модулю 10° + 7.
// Входные данные
// Первая строка содержит четыре целых числа п, т (1 ≤ n ≤ 100 000, 1 ≤ m ≤ 200 000) - количество вершин и ребер.
// Вторая строка содержит два целых числа s и t (1 < s, t ≤ n. s / t) — стартовые позиции игроков соответственно Следующие т строк содержат по три целых числа и. v, и d, (1 < u,, u, ≤ n. 1 ≤ d, ≤ 10") — описание ребер графа.
// Гарантируется, что в графе нет кратных ребер или петель, а также он связен.
// Выходные данные
// Выведите одно целое число — количество различных пар кратчайших путей, по которым Андрей и Вова могут двигаться, не встретившись. Ответ выведите по модулю 10° + 7.
// Примеры входные данные
// 4 4  12  1 3 1  2 4 1  4 1 1  3 2 1
// выходные данные
// 2
// входные данные
// 3 3   3  1 2 1  2 3 1  3 1 2
// выходные данные 
// 2
