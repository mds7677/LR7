#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
class task_1{
    public:
    std::string Straight(int n, int bits){
    std::string binaryDirect = "";
    for (int i = bits - 1; i >= 0; --i) { // O(bits)
        binaryDirect += ((n >> i) & 1) ? '1' : '0';
    }
    return binaryDirect;
}
    std::string Complement(int n , int bits){
    std::string binaryComplement = "";
    if (n < 0) {
        n = ~(-n) + 1; // O(bits)
    }
    for (int i = bits - 1; i >= 0; --i) { // O(bits)
        binaryComplement += ((n >> i) & 1) ? '1' : '0';
    }
    return binaryComplement;
}

void run(){
    int n;
    std::cout << "Введите число в прямом коде: ";
    std::cin >> n;
    int bits = sizeof(int) * 8;
    std::cout << "Прямой кодa: "<< Straight(n,bits)<< "\nДополнительный код: " << Complement(n,bits) << std::endl;
}
};
class task_2{
    public:
// преобразование двоичного числа в дополнительный код
std::string toComplementaryCode(const std::string& binary) {
    if (binary[0] == '0') {
        // Если >0
        return binary;
    }
    // побитовая инверсия (O(n))
    std::string inverted = binary;
    for (size_t i = 0; i < binary.size(); ++i) { // O(n)
        inverted[i] = (binary[i] == '0') ? '1' : '0';
    }

    // добавляем 1 к инвертированному числу (O(n))
    std::string result = inverted;
    bool carry = true;
    for (int i = binary.size() - 1; i >= 0 && carry; --i) { // O(n)
        if (result[i] == '0') {
            result[i] = '1';
            carry = false;
        } else {
            result[i] = '0';
        }
    }

    return result;
}
std::string addBinary(const std::string& binary1, const std::string& binary2) {
    size_t n = std::max(binary1.size(), binary2.size());
    std::string a = binary1;
    std::string b = binary2;
    // дополнение чисел до одинаковой длины (O(n))
    while (a.size() < n) a = "0" + a;
    while (b.size() < n) b = "0" + b;
    // сложение в дополнительном коде (O(n))
    std::string sum(n, '0');
    bool carry = false;
    for (int i = n - 1; i >= 0; --i) { // O(n)
        int bitSum = (a[i] - '0') + (b[i] - '0') + carry;
        sum[i] = (bitSum % 2) + '0';
        carry = bitSum > 1;
    }
    if (carry) {
        sum = "1" + sum;
    }

    return sum;
}

// перевод из дополнительного кода в прямой
std::string toDirectCode(const std::string& binary) {
    if (binary[0] == '0') {
        return binary;// > 0
    }

    // вычитаем 1 (O(n))
    std::string decremented = binary;
    bool borrow = true;
    for (int i = binary.size() - 1; i >= 0 && borrow; --i) { // O(n)
        if (decremented[i] == '1') {
            decremented[i] = '0';
            borrow = false;
        } else {
            decremented[i] = '1';
        }
    }

    // инвертируем побитно (O(n))
    for (size_t i = 0; i < decremented.size(); ++i) { // O(n)
        decremented[i] = (decremented[i] == '0') ? '1' : '0';
    }

    return decremented;
}

void run() {
    std::string binary1, binary2;
    std::cout << "Введите первое число (в двоичном формате): ";
    std::cin >> binary1;
    std::cout << "Введите второе число (в двоичном формате): ";
    std::cin >> binary2;

    std::string comp1 = toComplementaryCode(binary1);
    std::string comp2 = toComplementaryCode(binary2);

    std::string sum = addBinary(comp1, comp2);
    std::string result = toDirectCode(sum);

    std::cout << "Сумма чисел в прямом коде: " << result << std::endl;
}
};
class task_3{
    public:
int charToValue(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    if ('a' <= c && c <= 'z') return c - 'a' + 10;
    return -1;
}
char valueToChar(int value) {
    if (0 <= value && value <= 9) return '0' + value;
    if (10 <= value && value <= 35) return 'A' + (value - 10);
    return '?';
}

// произвольная система счисления
std::string addNumbers(const std::string& num1, const std::string& num2, int base) {
    std::vector<int> result;
    int carry = 0, i = num1.size() - 1, j = num2.size() - 1;

    // O(max(num1, num2))
    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? charToValue(num1[i--]) : 0;
        int digit2 = (j >= 0) ? charToValue(num2[j--]) : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        result.push_back(sum % base);
    }

    std::reverse(result.begin(), result.end()); // O(n)
    std::string resultStr;
    for (int digit : result) {
        resultStr.push_back(valueToChar(digit));
    }

    return resultStr;
}

// вычитание чисел в произвольной системе счисления
std::string subtractNumbers(const std::string& num1, const std::string& num2, int base) {
    std::vector<int> result;
    int borrow = 0, i = num1.size() - 1, j = num2.size() - 1;

    // O(max(num1,num2))
    while (i >= 0 || j >= 0 || borrow > 0) {
        int digit1 = (i >= 0) ? charToValue(num1[i--]) : 0;
        int digit2 = (j >= 0) ? charToValue(num2[j--]) : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff);
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back(); // Удаление нулей. O(n)
    }

    std::reverse(result.begin(), result.end()); // O(n)
    std::string resultStr;
    for (int digit : result) {
        resultStr.push_back(valueToChar(digit));
    }

    return resultStr;
}
void run() {
    int base;
    std::string num1, num2, operation;

    std::cout << "Введите основание системы счисления (от 2 до 36): ";
    std::cin >> base;
    while(base < 2 || base > 36){
        std::cout << "wrong input \n Enter the right number: ";
        std::cin >> base;

    }
    std::cout << "Введите первое число: ";
    std::cin >> num1;
    std::cout << "Введите второе число: ";
    std::cin >> num2;
    std::cout << "Введите операцию (+ или -): ";
    std::cin >> operation;
        if (operation == "+") {
            std::cout << "Результат: " << addNumbers(num1, num2, base) << "\n";
        } else if (operation == "-") {
            std::cout << "Результат: " << subtractNumbers(num1, num2, base) << "\n";
        } else {
            std::cerr << "Неверная операция.\n";
        }
}
};
class task_4{
    public:
//побитовые операции
bool isDivisible(int number, int prime) {
    int quotient = 0;
    int remainder = 0;

    // деления через побитовые операции
    // O(log(n))
    for (int bit = 31; bit >= 0; --bit) {
        remainder = (remainder << 1) | ((number >> bit) & 1); // Добавляем бит к остатку (<< O(1), | O(1))
        if (remainder >= prime) { // Если остаток больше делителя
            remainder -= prime; // Вычитаем делитель (через побитовые операции)
            quotient = (quotient << 1) | 1;
        } else {
            quotient = (quotient << 1);
        }
    }
    return remainder == 0;
}
//проверка делимости
std::vector<bool> checkDivisibility(const std::vector<int>& numbers, const std::vector<int>& primes) {
    std::vector<bool> results;

    // O(m * n * log(max_number))
    for (int number : numbers) {// O(n)
        for (int prime : primes) {// O(m)
            results.push_back(isDivisible(number, prime)); //проверка делимости O(log(max_number))
        }
    }

    return results;
}

void printResults(const std::vector<int>& numbers, const std::vector<int>& primes, const std::vector<bool>& results) {
    size_t idx = 0;

    for (int number : numbers) {
        for (int prime : primes) {
            std::cout << "Число " << number << (results[idx++] ? " делится " : " не делится ") << "на " << prime << ".\n";
        }
    }
}
void run(){
    std::vector<int> numbers;
    std::vector<int> primes = {5, 73, 151};

    int count;
    std::cout << "Введите количество чисел для проверки: ";
    std::cin >> count;

    std::cout << "Введите числа:\n";
    for (int i = 0; i < count; ++i) { // O(n)
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }
    std::vector<bool> results = checkDivisibility(numbers, primes);
    printResults(numbers, primes, results);
}
};
class task_5{
    public:
// Функция для преобразования числа в бинарное
std::string toBinary(int number, int bits) {
    std::string binary = "";
    for (int i = bits - 1; i >= 0; --i) {
        binary += (number & (1 << i)) ? '1' : '0';
    }
    return binary;
}
// Функция для эксперимента
int findPoisonedBarrel(int poisonedBarrel) {
    const int numBarrels = 240;
    const int numSlaves = 5;
    std::vector<bool> slaves(numSlaves, false);

    // Определяем, какие бочки тестирует каждый раб
    for (int barrel = 0; barrel < numBarrels; ++barrel) {
        for (int slave = 0; slave < numSlaves; ++slave) {
            if (barrel & (1 << slave)) {
                if (barrel == poisonedBarrel) {
                    slaves[slave] = true;
                }
            }
        }
    }

    // вычисляем номер отравленной бочки на основе "смертей" рабов
    int foundBarrel = 0;
    for (int slave = 0; slave < numSlaves; ++slave) {
        if (slaves[slave]) {
            foundBarrel |= (1 << slave);
        }
    }

    return foundBarrel;
}
void run(){
    const int numBarrels = 240;
    srand(time(nullptr));
    int poisonedBarrel = rand() % numBarrels;

    std::cout << "Праздник в честь Патриция!\n";
    std::cout << "К сожалению, одна из " << numBarrels << " бочек была отравлена.\n";
    std::cout << "Вы должны помочь Патрицию найти отравленную бочку.\n";
    std::cout << "Патриций пожертвовал пятью рабами, чтобы определить яд.\n";
    //бинарное представление отравленной бочки.
    std::cout << "Отравленная бочка имеет номер (для отладки): " << poisonedBarrel << "\n";
    std::cout << "Бинарное представление отравленной бочки: " << toBinary(poisonedBarrel, 8) << "\n";
    //отравленную бочку
    int foundBarrel = findPoisonedBarrel(poisonedBarrel);
    if (foundBarrel == poisonedBarrel) {
        std::cout << "Вы успешно определили отравленную бочку: #" << foundBarrel << "\n";
    } else {
        std::cout << "Ошибка! Вы указали на бочку #" << foundBarrel << ", но яд был в #" << poisonedBarrel << "\n";
    }
}
};