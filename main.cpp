#include <iostream>
#include <cassert> // Библиотека для проверок
#include "../main-project/precipitation.h"
#include "../main-project/processing.h"

// Тест 1: Пустой массив
void testEmptyRecords() {
    Precipitation* records[10] = { nullptr };
    // assert проверяет условие. Если функция вернет НЕ 0.0, программа аварийно завершится
    assert(process(records, 0, 5) == 0.0);
    std::cout << "[ОК] Тест 1 (Пустой массив) пройден.\n";
}

// Тест 2: Нет совпадений по месяцу
void testNoMatchMonth() {
    Precipitation* records[2];
    records[0] = new Precipitation{ 1, 3, 10.5, "дождь" };
    records[1] = new Precipitation{ 2, 4, 5.0, "снег" };

    assert(process(records, 2, 5) == 0.0);
    std::cout << "[ОК] Тест 2 (Другой месяц) пройден.\n";

    delete records[0]; delete records[1];
}

// Тест 3: Успешное суммирование
void testSuccessfulSum() {
    Precipitation* records[3];
    records[0] = new Precipitation{ 1, 5, 12.2, "дождь" };
    records[1] = new Precipitation{ 15, 5, 3.5, "сильный дождь" };
    records[2] = new Precipitation{ 20, 6, 4.0, "снег" };

    assert(process(records, 3, 5) == 15.7);
    std::cout << "[ОК] Тест 3 (Суммирование) пройден.\n";

    delete records[0]; delete records[1]; delete records[2];
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Запуск модульных тестов...\n";
    std::cout << "-------------------------------------\n";

    testEmptyRecords();
    testNoMatchMonth();
    testSuccessfulSum();

    std::cout << "-------------------------------------\n";
    std::cout << "ВСЕ ТЕСТЫ ВЫПОЛНЕНЫ УСПЕШНО!\n";
    return 0;
}