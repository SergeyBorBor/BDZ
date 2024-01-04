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
    FILE *fd;
    printf(" Результаты мониторинга системы успешно записаны в файл log.txt.\n");
    fd = fopen("../filles/log.txt","w");
    fputs("System Monitoring", fd);

    // Код мониторинга системы
    // Выведем информацию о текущем процессе и системном времени
    int pid = getpid();
    fputs("Current process ID: %d", pid);
    time_t current_time = time(0);
   // printf("Current time: %s", ctime(&current_time));
    
    fclose(fd);
    return 0;
}
