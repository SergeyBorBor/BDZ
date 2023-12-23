#include <cstdlib>
int main() {
    // Запуск программы b1.cpp
    system("g++ ../src/b1.cpp -o p1 && ./p1");

    // Запуск программы b2.cpp
    system("g++ ../src/b2.cpp -o p2 && ./p2");

    return 0;
}
