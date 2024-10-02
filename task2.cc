#include <iostream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h> // For _mkdir on Windows
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

void listFiles(const std::string& path) {
    struct dirent* entry;
    DIR* dir = opendir(path.c_str());

    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << path << " - " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "Files in directory: " << path << "\n";
    while ((entry = readdir(dir)) != nullptr) {
        // Skip the "." and ".." entries
        if (entry->d_name[0] != '.') {
            std::cout << (entry->d_type == DT_DIR ? "[D] " : "[F] ") << entry->d_name << "\n";
        }
    }

    closedir(dir);
}

void createDirectory(const std::string& path) {
    if (_mkdir(path.c_str()) == 0) { // Use _mkdir for MinGW
        std::cout << "Directory created: " << path << "\n";
    } else {
        perror("Failed to create directory");
    }
}

void copyFile(const std::string& source, const std::string& destination) {
    FILE* src = fopen(source.c_str(), "rb");
    FILE* dest = fopen(destination.c_str(), "wb");

    if (src == nullptr || dest == nullptr) {
        perror("Error opening files");
        return;
    }

    char buffer[BUFSIZ];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);
    std::cout << "Copied " << source << " to " << destination << "\n";
}



void moveFile(const std::string& source, const std::string& destination) {
    // Check if the destination file exists
    if (access(destination.c_str(), F_OK) != -1) {
        // File exists, prompt for overwrite
        std::cout << "File exists. Overwrite? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(); // Clear the newline from the buffer

        if (choice != 'y' && choice != 'Y') {
            std::cout << "Move operation cancelled.\n";
            return;
        }
    }

    // Attempt to move the file
    if (rename(source.c_str(), destination.c_str()) == 0) {
        std::cout << "Moved " << source << " to " << destination << "\n";
    } else {
        perror("Error moving file");
    }
}
int main() {
    std::string command;
    std::string currentPath = "."; // Start in the current directory

    while (true) {
        std::cout << "\nCurrent Directory: " << currentPath << "\n";
        std::cout << "Commands: ls (list), mkdir (create dir), cp (copy), mv (move), cd (change dir), exit\n";
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        if (command == "ls") {
            listFiles(currentPath);
        } else if (command.rfind("mkdir ", 0) == 0) {
            std::string dirName = command.substr(6);
            createDirectory(currentPath + "/" + dirName);
        } else if (command.rfind("cp ", 0) == 0) {
            std::string files = command.substr(3);
            size_t spaceIndex = files.find(' ');
            if (spaceIndex != std::string::npos) {
                std::string source = currentPath + "/" + files.substr(0, spaceIndex);
                std::string destination = currentPath + "/" + files.substr(spaceIndex + 1);
                copyFile(source, destination);
            } else {
                std::cout << "Invalid command format. Use: cp <source> <destination>\n";
            }
        } else if (command.rfind("mv ", 0) == 0) {
            std::string files = command.substr(3);
            size_t spaceIndex = files.find(' ');
            if (spaceIndex != std::string::npos) {
                std::string source = currentPath + "/" + files.substr(0, spaceIndex);
                std::string destination = currentPath + "/" + files.substr(spaceIndex + 1);
                moveFile(source, destination);
            } else {
                std::cout << "Invalid command format. Use: mv <source> <destination>\n";
            }
        } else if (command.rfind("cd ", 0) == 0) {
            std::string dirName = command.substr(3);
            std::string newPath = currentPath + "/" + dirName;
            if (chdir(newPath.c_str()) == 0) {
                currentPath = newPath;
            } else {
                std::cerr << "Directory does not exist: " << newPath << "\n";
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command. Please try again.\n";
        }
    }

    return 0;
}
