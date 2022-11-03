#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define VMAX 801 // 문제에서 최대 Node의 개수는 800개
#define INF 2100000000 // 문제에서 Node 사이의 최대 거리는 1000

using namespace std;

vector<pair<int, int>> a[VMAX]; // 노드 사이의 거리를 저장하는 Vector
bool pass = true; // 1->N으로 가는 경로가 있는지 여부를 확인하는 변수

// ==================== 다익스트라 알고리즘 ====================
int dijkstras(int start, int end) {
    priority_queue<pair<int, int>> pq; // 각 노드에 연결되어 있는 노드에 대한 정보를 담는 배열
    int dist[VMAX]; // 시작지점과 끝지점의 최단거리를 저장하는 배열

    for (int i = 1; i < VMAX; i++) // 거리의 초기값은 INF로 설정
        dist[i] = INF;

    dist[start] = 0; // 시작지점->시작지점의 거리는 0
    pq.push({-0, start}); // 시작지점->시작지점으로 가기 위한 최단경로는 0으로 설정하여 큐에 삽입.

    while (!pq.empty()) {
        int x = pq.top().second; // 현재 노드
        int wx = -pq.top().first; // 현재 노드까지의 거리
        pq.pop();

        if (x == end) return wx; // 끝지점에 도착할 경우 함수 종료

        for (int i = 0; i < a[x].size(); i++) {
            int y = a[x][i].first; // 다음 노드
            int wy = a[x][i].second; // 현재 노드에서 다음 노드로 가는 거리

            if (dist[y] > dist[x] + wy) { // 현재 노드까지의 거리 + 다음 노드와의 거리가 더 가깝다면 최단거리를 갱신
                dist[y] = dist[x] + wy;
                pq.push({-dist[y], y});
            }
        }
    }

    pass = false;
    return 0;
}
// =======================================================

int main() {
    int n, e;
    cin >> n >> e;

    int A, B;

    for (int x, y, w, i = 0; i < e; i++) {
        cin >> x >> y >> w;

        a[x].push_back({y, w});
        a[y].push_back({x, w});
    }

    cin >> A >> B;

    // 1->A->B->N으로 가는 최소경로
    int num1 = dijkstras(1, A) + dijkstras(A, B) + dijkstras(B, n);
    // 1->B->A->N으로 가는 최소경로
    int num2 = dijkstras(1, B) + dijkstras(B, A) + dijkstras(A, n);
    int result = min(num1, num2);

    if (pass)
        cout << result << endl;
    else
        cout << "-1" << endl;
}