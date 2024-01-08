    #include <stdio.h>
    #include <pthread.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/sysinfo.h>
    #include <sys/statvfs.h>
    #include <sys/resource.h>
    #define ROWS 10
    #define COLS 10
    
    int pid1;
    int startX, startY, endX, endY, res;
    time_t current_time;
    struct sysinfo mem;
    struct rusage cpu; 
    struct statvfs disk; 
    
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
    int queue[ROWS * COLS][2]; // Алгоритм Ли для поиска кратчайшего пути
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
   
   void* SysInform()
   {
    pid1 = getpid(); 
    current_time = time(NULL);
    sysinfo(&mem);
    getrusage(RUSAGE_SELF, &cpu);
    statvfs(".", &disk);
   }
   
   void* leeThread() { 
   res = leeAlgorithm(startX, startY, endX, endY); // вызов ф-й с передачей параметров (задача)
   pthread_exit(NULL); // завершение потока
   }

    int main() {
    printGraph();
    
    printf("Введите координаты начальной вершины (x y): ");
    scanf("%d %d", &startX, &startY);
    printf("Введите координаты конечной вершины (x y): ");
    scanf("%d %d", &endX, &endY);

    pthread_t threads[2]; // Объявляем массив структур потоков (системные)
    
    
    pthread_create(&threads[1], NULL, leeThread, NULL); // создание потоков и передача параметров
    pthread_create(&threads[2], NULL, SysInform, NULL); // создание потоков и передача параметров
    pthread_join(threads[1], NULL); // ждем завершения потока
    pthread_join(threads[2], NULL); // ждем завершения потока

    if (res == -1) {
      printf("Путь не найден\n");
    }
    else {
      printf("Кратчайший путь между вершинами: %d\n", res);
    }
    
    printf(" Результаты мониторинга записаны в файл log.txt.\n");

    freopen("../filles/log.txt", "w", stdout); //Запись результатов мониторинга в файл log.txt
    printf("System Monitoring:\n"); 
    printf("Current process ID: %d\n", pid1);
    printf("Current time: %s \n", ctime(&current_time));
    printf("Total RAM: %ld MB\n", mem.totalram / 1024 / 1024);
    printf("Free RAM: %ld MB\n", mem.freeram / 1024 / 1024);
    printf("CPU Usage: %ld.%06ld seconds\n", cpu.ru_utime.tv_sec, cpu.ru_utime.tv_usec);
    printf("Total Disk Space: %ld GB\n", (disk.f_blocks * disk.f_frsize) / 1024 / 1024 / 1024);
    printf("Available Disk Space: %ld GB\n", (disk.f_bavail * disk.f_frsize) / 1024 / 1024 / 1024);

    return 0;
    }

