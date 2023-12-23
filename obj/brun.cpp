#include <cstdlib>
int main() {
    // Запуск программы b1.cpp
    system("g++ ../src/b1.cpp -o b1 && ./b1");

    // Запуск программы b2.cpp
    system("g++ ../src/b2.cpp -o b2 && ./b2");

    return 0;
}
