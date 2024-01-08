    #include <stdio.h>
    #include <src/pthread.h>
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
   
   struct TaskMonitor {
   pid_t tpid;
   time_t tcurrent_time;
   struct sysinfo tmem; // Получение информации об использовании оперативной памяти
   struct rusage tcpu; // Получение информации об использовании процессора
   struct statvfs tdisk; // Получение информации о дисковом пространстве
   };

   void* SysInform(void* data)
   {struct TaskMonitor* task = (struct TaskMonitor*) data;
//    task->tpid=getpid();
    task->tcurrent_time = time(NULL);
    sysinfo(&task->tmem);
    getrusage(RUSAGE_SELF, &task->tcpu);
    statvfs(".", &task->tdisk);
    pthread_exit(NULL);
   } 

   struct IntegrateTask { // Шаблон для структуры "Задача потоку"
   int sx, sy, ex, ey, res; // интегрировать "от" (from), "до" (to), с "шагом" (step), результат сохранить в res
   };
   void* integrateThread(void* data) { // ф-я приведения типов задания и т.д.
   struct IntegrateTask* task = (struct IntegrateTask*)data; // объявления структуры task и присвоения аргументов
   task->res = leeAlgorithm(task->sx, task->sy, task->ex, task->ey); // вызов ф-и интегрирования с передачей параметров (задача)
   pthread_exit(NULL); // завершение потока
   }

    int main() {
    printGraph();
    int startX, startY, endX, endY;
    printf("Введите координаты начальной вершины (x y): ");
    scanf("%d %d", &startX, &startY);
    printf("Введите координаты конечной вершины (x y): ");
    scanf("%d %d", &endX, &endY);

    pthread_t threads[2]; // Объявляем массив структур потоков (системные)
    struct IntegrateTask tasks; // Объявляем массив структур заданий потокам
    struct TaskMonitor tmon;

    tasks.sx=startX;
    tasks.sy=startY;
    tasks.ex=endX;
    tasks.ey=endY;
    pthread_create(&threads[1], NULL, integrateThread, (void*)& tasks); // создание потоков и передача параме
    pthread_create(&threads[2], NULL, SysInform, (void*)& tmon); // создание потоков и передача параме
    pthread_join(threads[1], NULL); // ждем завершения потока
    pthread_join(threads[2], NULL); // ждем завершения потока

    if (tasks.res == -1) {
      printf("Путь не найден\n");
    }
    else {
      printf("Кратчайший путь между вершинами: %d\n", tasks.res);
    }
    printf(" Результаты мониторинга записаны в файл log.txt.\n");
    freopen("../filles/log.txt", "w", stdout); //Запись результатов мониторинга в файл log.txt
    printf("System Monitoring:\n"); // Отображение информации о системе
    printf("Current time: %s \n", ctime(&tmon.tcurrent_time));
    printf("Total RAM: %ld MB\n", tmon.tmem.totalram / 1024 / 1024);
    printf("Free RAM: %ld MB\n", tmon.tmem.freeram / 1024 / 1024);
    printf("CPU Usage: %ld.%06ld seconds\n", tmon.tcpu.ru_utime.tv_sec, tmon.tcpu.ru_utime.tv_usec);
    printf("Total Disk Space: %ld GB\n", (tmon.tdisk.f_blocks * tmon.tdisk.f_frsize) / 1024 / 1024 / 1024);
    printf("Available Disk Space: %ld GB\n", (tmon.tdisk.f_bavail * tmon.tdisk.f_frsize) / 1024 / 1024 / 1024);
    return 0;
    }

