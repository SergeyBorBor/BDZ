#include <stdio.h>
#include <windows.h>
#include <sys/statvfs.h>
#include <unistd.h>

int main() {
    // Получаем начальное значение загрузки процессора
    float cpu_percent_prev = 0;
    FILETIME idle_time_prev, kernel_time_prev, user_time_prev;
    GetSystemTimes(&idle_time_prev, &kernel_time_prev, &user_time_prev);

    while (1) {
        // Получаем текущее значение загрузки процессора
        FILETIME idle_time, kernel_time, user_time;
        GetSystemTimes(&idle_time, &kernel_time, &user_time);

        ULARGE_INTEGER idle, kernel, user;
        idle.LowPart = idle_time.dwLowDateTime;
        idle.HighPart = idle_time.dwHighDateTime;
        kernel.LowPart = kernel_time.dwLowDateTime;
        kernel.HighPart = kernel_time.dwHighDateTime;
        user.LowPart = user_time.dwLowDateTime;
        user.HighPart = user_time.dwHighDateTime;

        float cpu_percent = (float)(100.0 - ((idle.QuadPart - idle_time_prev.QuadPart) * 100.0 / (kernel.QuadPart + user.QuadPart - kernel_time_prev.QuadPart - user_time_prev.QuadPart)));
        
        // Получаем текущее значение использования памяти
        MEMORYSTATUSEX mem_info;
        mem_info.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&mem_info);
        float memory_percent = (float)(mem_info.dwMemoryLoad);

        // Получаем текущее значение использования диска
        struct statvfs disk_info;
        statvfs("/", &disk_info);
        float disk_percent = (float)(100.0 - ((double)disk_info.f_bfree / (double)disk_info.f_blocks) * 100.0);

        // Если значение загрузки процессора изменилось, выводим сообщение
        if (cpu_percent != cpu_percent_prev) {
            printf("Загрузка процессора: %.2f%%\n", cpu_percent);
        }

        // Если значение использования памяти превышает 80%, выводим сообщение
        if (memory_percent > 80) {
            printf("Внимание! Использование памяти превышает 80%%\n");
        }

        // Если значение использования диска превышает 80%, выводим сообщение
        if (disk_percent > 80) {
            printf("Внимание! Использование диска превышает 80%%\n");
        }

        // Обновляем значение предыдущей загрузки процессора
        cpu_percent_prev = cpu_percent;

        // Ждем 1 секунду перед повторным опросом
        sleep(1);
    }
    return 0;
}
