В папке files хранится "log.txt" - результат моиторинга программы.
В папке obj  хранится "progrun.cpp", для запуска скрипта переходим в эту папку и прописываем "gcc progrun.cpp -o progrun", а затем "./progrun"
В папке src хранятся файлы программы, в которых:
program.cpp - Алгоритм Ли и функция мониторинга системы
4. Запуск програмы происходит из папки obj, для запуска прописываем "gcc progrun.cpp -o progrun", а затем "./progrun", далее вводим координаты начальной и конечной вершин, кратчайший путь между которыми, посчитает программа. На экране выводится кратчайший путь(если он сущетсвует). Результат мониторинга системы будет помещен в файл log.txt в папку files.
