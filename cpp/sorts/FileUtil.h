#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> readNumbersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다!" << std::endl;
        return {};
    }

    std::vector<int> numbers;
    int num;
    while (file >> num) {
        numbers.push_back(num);
    }
    file.close();

    return numbers;
}

void writeArrayToFile(const std::string& filename, int* arr, int size) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다!" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << arr[i] << std::endl;
    }

    file.close();
}