#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

int main() {
    printf(" Результаты мониторинга системы успешно записаны в файл log.txt.\n");
    // Открытие файла log.txt для записи
    int fd = open("../files/log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Дублирование дескриптора файлового дескриптора stdout для записи в файл
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }

    // Отображение информации о системе
    printf("System Monitoring");

    // Код мониторинга системы
    // Выведем информацию о текущем процессе и системном времени
    int pid = getpid();
    printf("Current process ID: %d", pid);
    time_t current_time = time(NULL);
    printf("Current time: %s", ctime(&current_time));

    // Закрытие файла
    close(fd);

    return 0;
}
