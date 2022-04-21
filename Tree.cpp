#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

std::vector<std::string> getDirs(std::string path) {
    std::vector<std::string> Dirs;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            Dirs.push_back(entry.path().string());
        }
    }
    return Dirs;
}

std::vector<std::string> getFiles(std::string path) {
    std::vector<std::string> Files;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            Files.push_back(entry.path().string());
        }
    }
    return Files;
}

std::vector<std::string> getTree(std::string dir) {
    std::vector<std::string> currDirs;
    std::vector<std::string> tree;
    currDirs.push_back(dir);

    while (currDirs.size() != NULL) {
        try {
            std::vector<std::string> subDirs;
            for (size_t i = 0; i < currDirs.size(); i++) {
                std::vector<std::string> dirBuffer = getDirs(currDirs[i]);
                for (size_t i = 0; i < dirBuffer.size(); i++) {
                    subDirs.push_back(dirBuffer[i]);
                }
            }
            for (size_t i = 0; i < subDirs.size(); i++) {
                tree.push_back(subDirs[i]);
            }
            currDirs = subDirs;
        }
        catch (const std::exception&) {}
    }
    return tree;
}

int main()
{
    // NOTE: Go to Project -> Properties -> Configuration Properties -> C++ Language Standard -> ISO C++17 Standard (/std:c++17)
    std::vector<std::string> Tree = getTree("C:\\testfolder");
    for (size_t i = 0; i < Tree.size(); i++) {
        std::cout << Tree[i] << std::endl;
    }
}