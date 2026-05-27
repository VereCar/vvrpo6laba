#include <iostream>
#include "constants.h"
#include "precipitation.h"
#include "file_reader.h"

int main() {
    std::cout << "Лабораторная работа N8. Выполнил студент группы: ИТ-23\n";
    std::cout << "Вариант 3: Осадки\n\n";

    Precipitation* records[MAX_LINES] = { nullptr };
    int size = readData("data.txt", records, MAX_LINES);

    std::cout << "Исходные данные из файла:\n";
    printRecords(records, size);

    freeData(records, size);
    return 0;
}