#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/resource.h>
#include <sys/wait.h>

#define ROWS 10
#define COLS 10

int graph[ROWS][COLS] = { // задаем матрицу планарного графа
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

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
    pid_t pid;
    pid = fork();
    if(pid != 0)
    {
      printGraph();

      int startX, startY, endX, endY;
      printf("Введите координаты начальной вершины (x y): ");
      scanf("%d %d", &startX, &startY);
      printf("Введите координаты конечной вершины (x y): ");
      scanf("%d %d", &endX, &endY);

      int distance = leeAlgorithm(startX, startY, endX, endY);
      if (distance == -1) 
      {
        printf("Путь не найден\n");
      } 
      else 
      {
        printf("Кратчайший путь между вершинами: %d\n", distance);
      }
        wait(0);
    }
    else
    { 
       sleep(10);
       
       printf(" Результаты мониторинга записаны в файл log.txt.\n");
       //Запись результатов мониторинга в файл log.txt
       freopen("log.txt", "w", stdout);
       
       // Отображение информации о системе
       printf("System Monitoring:\n");

      // Код мониторинга системы
      // Выведем информацию о текущем процессе и системном времени
      int pid1 = getpid();
      printf("Current process ID: %d\n", pid1);
      time_t current_time = time(NULL);
      printf("Current time: %s \n", ctime(&current_time));

      // Получение информации об использовании оперативной памяти
      struct sysinfo mem;
      sysinfo(&mem);
      printf("Total RAM: %ld MB\n", mem.totalram / 1024 / 1024);
      printf("Free RAM: %ld MB\n", mem.freeram / 1024 / 1024);

      // Получение информации об использовании процессора
      struct rusage cpu;
      getrusage(RUSAGE_SELF, &cpu);
      printf("CPU Usage: %ld.%06ld seconds\n", cpu.ru_utime.tv_sec, cpu.ru_utime.tv_usec);

      // Получение информации о дисковом пространстве
      struct statvfs disk;
      statvfs(".", &disk);
      printf("Total Disk Space: %ld GB\n", (disk.f_blocks * disk.f_frsize) / 1024 / 1024 / 1024);
      printf("Available Disk Space: %ld GB\n", (disk.f_bavail * disk.f_frsize) / 1024 / 1024 / 1024);

     
  }

    return 0;
}
