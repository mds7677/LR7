#include "../tasks/tasks.cpp"
void printMenu() {
    std::cout << "+-------------------+----------------+ \n";
    std::cout << "|     Menu          |   Option       | \n";
    std::cout << "+-------------------+----------------+ \n";
    std::cout << "| 1. task_1         |   Press 1      | \n";
    std::cout << "| 2. task_2         |   Press 2      | \n";
    std::cout << "| 3. task_3         |   Press 3      | \n";
    std::cout << "| 4. task_4         |   Press 4      | \n";
    std::cout << "| 5. task_5         |   Press 5      | \n";
    std::cout << "| 6. exit           |   Press 6      | \n";
    std::cout << "+-------------------+----------------+ \n";
}
// cделать проверку на ввод чисел(ZOV) в каждой системе исчисления !!!!!!!!!!!!!!!!!
int main(){
    int n;
    task_1 task;
    task_2 task_2;
    task_3 task_3;
    task_4 four;
    task_5 five;
    printMenu();
    std::cin >> n;
    switch (n)
    {
    case 1:
        task.run();
        break;
    case 2:
        task_2.run();
        break;
    case 3:
        task_3.run();
        break;
    case 4:
        four.run();
    break;
    case 5:
        five.run();
        break;
    default:
    return 0;
        break;
    }
    return 0;
}