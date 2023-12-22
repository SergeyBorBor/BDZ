#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10

int graph[ROWS][COLS];

void generateGraph() {
    // Заполнение графа случайными значениями
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            graph[i][j] = rand() % 2;
        }
    }
}

void printGraph() {
    // Вывод графа на экран
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int leeAlgorithm(int startX, int startY, int endX, int endY) {
    // Алгоритм Ли для поиска кратчайшего пути
    int queue[ROWS * COLS][2];
    int front = 0, rear = 0;
    int visited[ROWS][COLS] = {0};
    int distance[ROWS][COLS] = {0};

    queue[rear][0] = startX;
    queue[rear][1] = startY;
    rear++;
    visited[startX][startY] = 1;

    while (front != rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        if (x == endX && y == endY) {
            return distance[x][y];
        }

        if (x > 0 && graph[x-1][y] && !visited[x-1][y]) {
            queue[rear][0] = x-1;
            queue[rear][1] = y;
            rear++;
            visited[x-1][y] = 1;
            distance[x-1][y] = distance[x][y] + 1;
        }

        if (x < ROWS-1 && graph[x+1][y] && !visited[x+1][y]) {
            queue[rear][0] = x+1;
            queue[rear][1] = y;
            rear++;
            visited[x+1][y] = 1;
            distance[x+1][y] = distance[x][y] + 1;
        }

        if (y > 0 && graph[x][y-1] && !visited[x][y-1]) {
            queue[rear][0] = x;
            queue[rear][1] = y-1;
            rear++;
            visited[x][y-1] = 1;
            distance[x][y-1] = distance[x][y] + 1;
        }

        if (y < COLS-1 && graph[x][y+1] && !visited[x][y+1]) {
            queue[rear][0] = x;
            queue[rear][1] = y+1;
            rear++;
            visited[x][y+1] = 1;
            distance[x][y+1] = distance[x][y] + 1;
        }
    }

    return -1;
}

int main() {
    generateGraph();
    printGraph();

    int startX, startY, endX, endY;
    printf("Введите координаты начальной вершины (x y): ");
    scanf("%d %d", &startX, &startY);
    printf("Введите координаты конечной вершины (x y): ");
    scanf("%d %d", &endX, &endY);

    int distance = leeAlgorithm(startX, startY, endX, endY);
    if (distance == -1) {
        printf("Путь не найден\n");
    } else {
        printf("Кратчайший путь между вершинами: %d\n", distance);
    }

    return 0;
}

