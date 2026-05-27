#include <iostream>
#include <string>
#include <algorithm>
#include "constants.h"
#include "precipitation.h"
#include "file_reader.h"

void filterRain(Precipitation* records[], int size) {
    std::cout << "\n[Фильтр]: Дни с дождем:\n";
    for (int i = 0; i < size; ++i) {
        if (records[i]->characteristic.find("дождь") != std::string::npos) {
            std::cout << records[i]->day << "." << records[i]->month << " - " << records[i]->amount << " мм (" << records[i]->characteristic << ")\n";
        }
    }
}

void filterLowPrecipitation(Precipitation* records[], int size) {
    std::cout << "\n[Фильтр]: Осадки < 1.5 мм:\n";
    for (int i = 0; i < size; ++i) {
        if (records[i]->amount < 1.5) {
            std::cout << records[i]->day << "." << records[i]->month << " - " << records[i]->amount << " мм\n";
        }
    }
}

int compareByAmount(const Precipitation* a, const Precipitation* b) {
    return (a->amount > b->amount) - (a->amount < b->amount);
}

int compareComplex(const Precipitation* a, const Precipitation* b) {
    if (a->characteristic != b->characteristic) return (a->characteristic > b->characteristic) - (a->characteristic < b->characteristic);
    if (a->month != b->month) return (a->month > b->month) - (a->month < b->month);
    return (a->day > b->day) - (a->day < b->day);
}

typedef int (*CompareFunc)(const Precipitation*, const Precipitation*);
typedef void (*SortFunc)(Precipitation* [], int, CompareFunc);

void shakerSort(Precipitation* arr[], int size, CompareFunc comp) {
    int left = 0, right = size - 1;
    bool swapped = true;
    while (left < right&& swapped) {
        swapped = false;
        for (int i = left; i < right; ++i) {
            if (comp(arr[i], arr[i + 1]) > 0) { std::swap(arr[i], arr[i + 1]); swapped = true; }
        }
        right--;
        for (int i = right; i > left; --i) {
            if (comp(arr[i - 1], arr[i]) > 0) { std::swap(arr[i - 1], arr[i]); swapped = true; }
        }
        left++;
    }
}

void quickSortInternal(Precipitation* arr[], int low, int high, CompareFunc comp) {
    if (low < high) {
        Precipitation* pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (comp(arr[j], pivot) <= 0) std::swap(arr[++i], arr[j]);
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSortInternal(arr, low, pi - 1, comp);
        quickSortInternal(arr, pi + 1, high, comp);
    }
}

void quickSort(Precipitation* arr[], int size, CompareFunc comp) {
    quickSortInternal(arr, 0, size - 1, comp);
}

int main() {
    std::cout << "***********************************************************\n";
    std::cout << "Лабораторная работа N8. Выполнил студент группы: 25ИСиТ1д\n";
    std::cout << "Вариант 3: Осадки\n\n";

    Precipitation* records[MAX_LINES] = { nullptr };
    int size = readData("data.txt", records, MAX_LINES);

    SortFunc sortMethods[2] = { shakerSort, quickSort };
    CompareFunc compareCriteria[2] = { compareByAmount, compareComplex };

    int choice;
    do {
        std::cout << "\n1. Показать таблицу\n2. Фильтр: Дождь\n3. Фильтр: Мало осадков\n4. Сортировка\n0. Выход\nВыбор: ";
        std::cin >> choice;

        if (choice == 1) printRecords(records, size);
        else if (choice == 2) filterRain(records, size);
        else if (choice == 3) filterLowPrecipitation(records, size);
        else if (choice == 4) {
            int sIdx, cIdx;
            std::cout << "Метод (0-Шейкер, 1-Быстрая): "; std::cin >> sIdx;
            std::cout << "Критерий (0-Объем, 1-Комплексный): "; std::cin >> cIdx;
            if ((sIdx == 0  sIdx == 1) && (cIdx == 0  cIdx == 1)) {
                sortMethods[sIdx](records, size, compareCriteria[cIdx]);
                printRecords(records, size);
            }
        }
    } while (choice != 0);

    freeData(records, size);
    return 0;
}