#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/resource.h>
#include <string.h>

int main()
{
    file *fd
    printf(" Результаты мониторинга системы успешно записаны в файл log.txt.\n");
    fd = fopen("../filles/log.txt","w");
    fputs("System Monitoring", fd);
    fclose(fd);
    return 0
}
 /*   
    // Открытие файла log.txt для записи
    int fd = open("../filles/log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
    //printf("System Monitoring");
    
    fputs("System Monitoring", fd);
   
    // Код мониторинга системы
    // Выведем информацию о текущем процессе и системном времени
    int pid = getpid();
    printf("Current process ID: %d", pid);
    time_t current_time = time(NULL);
    printf("Current time: %s", ctime(&current_time));

    // Получение информации об использовании оперативной памяти
    struct sysinfo mem_info;
    sysinfo(&mem_info);
    printf("Total RAM: %ld MB", mem_info.totalram / 1024 / 1024);
    printf("Free RAM: %ld MB", mem_info.freeram / 1024 / 1024);

    // Получение информации об использовании процессора
    struct rusage cpu_info;
    getrusage(RUSAGE_SELF, &cpu_info);
    printf("CPU Usage: %ld.%06ld seconds", cpu_info.ru_utime.tv_sec, cpu_info.ru_utime.tv_usec);

    // Получение информации о дисковом пространстве
    struct statvfs disk_info;
    statvfs(".", &disk_info);
    printf("Total Disk Space: %ld GB", (disk_info.f_blocks * disk_info.f_frsize) / 1024 / 1024 / 1024);
    printf("Available Disk Space: %ld GB", (disk_info.f_bavail * disk_info.f_frsize) / 1024 / 1024 / 1024);

    // Закрытие файла

    close(fd);

    return 0;
}
*/


/*#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 5 // размер блока

// функция перестановки символов в блоке
void shuffle_block(char *block) {
int len = strlen(block);
for (int i = 0; i < len - 1; i += 2) {
char temp = block[i];
block[i] = block[i+1];
block[i+1] = temp;
}
}

int main() {
FILE *input_file, *output_file;
char buffer[BLOCK_SIZE+1]; // буфер для чтения/записи блоков

// открытие файлов для чтения и записи
input_file = fopen("input.txt", "r");
output_file = fopen("output.txt", "w");

// чтение и шифрование блоков
while (fgets(buffer, BLOCK_SIZE+1, input_file)) {
shuffle_block(buffer);
fputs(buffer, output_file);
}

// закрытие файлов
fclose(input_file);
fclose(output_file);

return 0;
}*/
