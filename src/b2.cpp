#include "SystemMonitor.h"

int main() {
    std::string outputFolder = "../files/log.txt";
    SystemMonitor monitor(outputFolder);

    while (true) {
        std::vector<std::string> systemInfo = monitor.monitorSystem();
        std::string outputFile = outputFolder + "log.txt";
        if (!monitor.writeToFile(outputFile, systemInfo)) {
            std::cout << "Error writing to file" << std::endl;
        }
    }

    return 0;
}

