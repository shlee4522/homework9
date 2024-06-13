#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10  //최대 Vertex 수 정의

//Graph의 인접 리스트 노드 구조체
typedef struct Node {
    int vertex;  //Vertex 번호
    struct Node* next;  //다음 노드를 가리키는 포인터
} Node;

//Graph 구조체
typedef struct Graph {
    Node* adjLists[MAX_VERTEX];  //인접한 리스트 배열
    int visited[MAX_VERTEX];  //방문 여부를 판단하는 배열
} Graph;

//노드 생성 함수
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));  //새로운 노드 메모리 할당
    newNode->vertex = v;  //노드에 Vertex 번호 할당
    newNode->next = NULL;  //다음 노드를 NULL로 초기화
    return newNode;  //생성된 노드 반환
}

//Graph 초기화 함수
Graph* createGraph() {
    Graph* graph = malloc(sizeof(Graph));  //새로운 Graph 메모리 할당
    for (int i = 0; i < MAX_VERTEX; i++) {
        graph->adjLists[i] = NULL;  //모든 인접 리스트를 NULL로 초기화
        graph->visited[i] = 0;  //모든 방문 배열을 0으로 초기화
    }
    return graph;  //초기화된 그래프 반환
}

//Vertex 삽입 함수
void insertVertex(Graph* graph, int v) {
    if (v >= 0 && v < MAX_VERTEX) {  //Vertex 번호가 유효한지 확인
        if (graph->adjLists[v] == NULL) {  //Vertex가 존재하지 않으면
            graph->adjLists[v] = createNode(v);  //새로운 Vertex 추가
            printf("%d inserted.\n", v);  //성공 메시지 출력
        } else {
            printf("%d already exists.\n", v);  //이미 존재하는 경우 메시지 출력
        }
    } else {
        printf("%d is out of bounds.\n", v);  //Vertex 번호가 유효하지 않으면 메시지 출력
    }
}

// Edge 삽입 함수
void insertEdge(Graph* graph, int src, int dest) {
    if (src >= 0 && src < MAX_VERTEX && dest >= 0 && dest < MAX_VERTEX) {  //두 Vertex 번호가 유효한지 확인
        Node* newNode = createNode(dest);  //목적지 Vertex에 대한 새로운 노드 생성
        newNode->next = graph->adjLists[src]->next;  //목적지 노드를 소스 노드의 다음에 연결
        graph->adjLists[src]->next = newNode;  //소스 노드의 다음 노드로 설정

        newNode = createNode(src);  //소스 Vertex에 대한 새로운 노드 생성
        newNode->next = graph->adjLists[dest]->next;  //소스 노드를 목적지 노드의 다음에 연결
        graph->adjLists[dest]->next = newNode;  //목적지 노드의 다음 노드로 설정

        printf("Inserted between %d and %d.\n", src, dest);  //성공 메시지 출력
    } else {
        printf("Out of bounds.\n");  //Vertex 번호가 유효하지 않으면 메시지 출력
    }
}

// DFS 탐색 함수
void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];  //현재 Vertex의 인접 리스트 가져오기
    Node* temp = adjList;

    graph->visited[vertex] = 1;  //현재 Vertex 방문 표시
    printf("%d ", vertex);  //현재 Vertex 출력

    int adjVertices[MAX_VERTEX];  //인접한 Vertex를 저장할 배열
    int count = 0;
    temp = temp->next;  //인접 리스트의 첫 번째 노드로 이동
    while (temp) {  //인접 리스트를 따라 탐색
        adjVertices[count++] = temp->vertex;  //인접한 Vertex 배열에 추가
        temp = temp->next;  //다음 노드로 이동
    }

    //인접한 Vertex를 오름차순으로 정렬
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (adjVertices[i] > adjVertices[j]) {
                int temp = adjVertices[i];
                adjVertices[i] = adjVertices[j];
                adjVertices[j] = temp;
            }
        }
    }

    //정렬된 순서대로 DFS 호출
    for (int i = 0; i < count; i++) {
        if (!graph->visited[adjVertices[i]]) {
            DFS(graph, adjVertices[i]);
        }
    }
}

//BFS 탐색 함수
void BFS(Graph* graph, int startVertex) {
    int queue[MAX_VERTEX];  //BFS를 위한 큐 배열
    int front = 0;  //큐의 앞 인덱스
    int rear = 0;  //큐의 뒤 인덱스

    graph->visited[startVertex] = 1;  //시작 Vertex 방문 표시
    queue[rear++] = startVertex;  //시작 Vertex를 큐에 추가

    while (front != rear) {  //큐가 비어있지 않은 동안 반복
        int currentVertex = queue[front++];  //큐의 앞에서 Vertex를 꺼내기
        printf("%d ", currentVertex);  //꺼낸 Vertex 출력

        Node* temp = graph->adjLists[currentVertex];  //현재 Vertex의 인접 리스트 가져오기

        int adjVertices[MAX_VERTEX];  //인접한 Vertex를 저장할 배열
        int count = 0;
        temp = temp->next;  //인접 리스트의 첫 번째 노드로 이동
        while (temp) {  //인접 리스트를 따라 탐색
            adjVertices[count++] = temp->vertex;  //인접한 Vertex 배열에 추가
            temp = temp->next;  //다음 노드로 이동
        }

        //인접한 Vertex를 오름차순으로 정렬
        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
                if (adjVertices[i] > adjVertices[j]) {
                    int temp = adjVertices[i];
                    adjVertices[i] = adjVertices[j];
                    adjVertices[j] = temp;
                }
            }
        }

        //정렬된 순서대로 BFS 큐에 추가
        for (int i = 0; i < count; i++) {
            int adjVertex = adjVertices[i];
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;  // 방문 표시
                queue[rear++] = adjVertex;  //큐에 추가
            }
        }
    }
}

//그래프 출력 함수
void printGraph(Graph* graph) {
    for (int v = 0; v < MAX_VERTEX; v++) {
        Node* temp = graph->adjLists[v];
        if (temp) {  //인접 리스트가 존재하는 경우
            printf("Vertex %d:", v);  //Vertex 번호 출력
            temp = temp->next;
            while (temp) {
                printf(" -> %d", temp->vertex);  //인접한 Vertex 출력
                temp = temp->next;  //다음 노드로 이동
            }
            printf("\n");
        }
    }
}

//그래프 초기화 함수 (동적 메모리 해제 포함)
void resetGraph(Graph* graph) {
    for (int v = 0; v < MAX_VERTEX; v++) {
        Node* temp = graph->adjLists[v];
        while (temp) {
            Node* next = temp->next;  //다음 노드를 임시 저장
            free(temp);  //현재 노드 메모리 해제
            temp = next;  //다음 노드로 이동
        }
        graph->adjLists[v] = NULL;  //인접 리스트를 NULL로 초기화
        graph->visited[v] = 0;  //방문 배열 초기화
    }
    printf("Success\n"); //성공 메세지 출력 
}

//방문 배열 초기화 함수
void resetVisited(Graph* graph) {
    for (int i = 0; i < MAX_VERTEX; i++) {
        graph->visited[i] = 0;  //방문 배열을 0으로 초기화
    }
}

int main() {
    char command;  //사용자 명령어 입력 변수
    int vertex, src, dest;
    Graph* graph = createGraph();  //그래프 초기화

    //메뉴 출력
    printf("----------------------------------------------------------------\n");
    printf("Graph Searches\n");
    printf("----------------------------------------------------------------\n");
    printf("Initialize Graph = z\n");
    printf("Insert Vertex = v Insert Edge = e\n");
    printf("Depth First Search = d Breath First Search = b\n");
    printf("Print Graph = p Quit = q\n");
    printf("----------------------------------------------------------------\n");

    while (1) { 
        printf("Enter command: ");
        scanf(" %c", &command);  //명령어 입력

        switch (command) {
            case 'z':
                resetGraph(graph);  //그래프 초기화
                break;
            case 'v':
                printf("Enter vertex: ");
                scanf("%d", &vertex);  //Vertex 번호 입력
                insertVertex(graph, vertex);  //Vertex 삽입
                break;
            case 'e':
                printf("Enter source and destination vertices: ");
                scanf("%d %d", &src, &dest);  //소스와 목적지 Vertex 번호 입력
                insertEdge(graph, src, dest);  //Edge 삽입
                break;
            case 'd':
                printf("Enter start vertex for DFS: ");
                scanf("%d", &vertex);  //DFS 시작 Vertex 입력
                resetVisited(graph);  //방문 배열 초기화
                DFS(graph, vertex);  //DFS 수행
                printf("\n");
                break;
            case 'b':
                printf("Enter start vertex for BFS: ");
                scanf("%d", &vertex);  //BFS 시작 Vertex 입력
                resetVisited(graph);  //방문 배열 초기화
                BFS(graph, vertex);  //BFS 수행
                printf("\n");
                break;
            case 'p':
                printGraph(graph);  //그래프 출력
                break;
            case 'q':
                resetGraph(graph);  //그래프 초기화 및 메모리 해제
                free(graph);  //그래프 메모리 해제
                printf("Exiting program.\n");  //종료 메시지 출력
                return 0;  //프로그램 종료
            default:
                printf("Invalid command.\n");  //잘못된 명령어 메시지 출력
        }
    }

    return 0;
}
