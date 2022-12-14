#include <pthread.h>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <cstdlib>

// максимальное количество задач
int limit = 0;
// портфель задач
int briefcase = 0;
// Мьютекс для портфеля задач
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// Мьютекс для записи информации о работе потоков
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


/// Книга, то что будут возвращать студенты.
struct Book {
    // имя книги
    std::string name;
    // Имя потока, который добавил книгу
    std::string thread_name;
    // Номер ряда
    int m = 0;
    // Номер шкафа
    int n = 0;
    // Номер книги в шкафу
    int k = 0;
};

///  Стркутура аргумента, необходимо для потоков
struct Argument {
    // портфель
    int briefcase;
    // Задачи
    std::vector<std::array<int, 3>> objectives;
    // Каталог книг
    std::vector<Book> catalog;
    // максимум задач
    int limit;
    char **argv;
};

/**
 * Проверяем, доступен ли файл
 * @param str имя файла
 * @return код, отвечающий, доступен ли файл или нет
 */
int checkFile(char *str) {
    std::ifstream iff(str);
    if (!iff.is_open()) {
        std::cout << "One of the files isn't available!\n";
        return -1;
    }
    iff.close();
    return 2;
}

/**
 * Выбираем режим работы в зависимости от аргументов командной строки
 * @param argc количество аргументов
 * @param argv сами аргументы
 * @return
 */
int work_mode(int argc, char **argv) {
    // В зависимости от количества аргументов, выбираем режим работы
    if (argc == 1) {
        std::cout << "The application will run in console mode\n";
        return 0;
    }
    if (argc == 2) {
        return checkFile(argv[1]);
    }
    if (argc == 3) {
        if (checkFile(argv[1]) == -1) {
            return -1;
        }
        if (checkFile(argv[2]) == -1) {
            return -1;
        }
        return 1;
    }
    if (argc == 4) {
        std::cout << "The application will run in command line mode\n";
        return 3;
    } else {
        std::cout << "Wrong amount of arguments";
        return -1;
    }
}

/**
 * Составляет вектор задач.
 * @param M количество рядов
 * @param N количество шкафов в ряду
 * @param K количество книг в шкафу
 * @return Вектор с координатами книг, которые нужно найти.
 */
std::vector<std::array<int, 3>> generate_objectives(int M, int N, int K) {
    // Создаем вектор задач (по сути книг, которые нам надо найти).
    std::vector<std::array<int, 3>> tasks;
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            for (int k = 0; k < K; k++) {
                // Массив с координатами книги
                std::array<int, 3> temp = {m, n, k};
                tasks.push_back(temp);
            }
        }
    }
    return tasks;
}

/**
 * Заполняет каталог книгами
 * @param void_ptr аргумент
 * @return nullptr, завершает поток
 */
void *fill_catalog(void *void_ptr) {
    // Координаты книги
    int coordinates[3];
    // Имя потока
    char name[16];
    // Получаем аргументы
    auto *arguments = (Argument *) void_ptr;
    while (true) {
        // Закрываем мьютекс портфеля
        pthread_mutex_lock(&mutex1);
        // Увеличиваем номер задачи в портфеле на 1
        arguments->briefcase += 1;
        // Открываем мьютекс портфеля
        pthread_mutex_unlock(&mutex1);
        // Берем номер в каталоге
        int old_briefcase = arguments->briefcase - 1;
        // Работаем пока не заполним весь каталог
        if (old_briefcase < arguments->limit) {
            // Получаем координаты
            for (int i = 0; i < 3; ++i) {
                coordinates[i] = arguments->objectives[old_briefcase][i];
            }
            // Получаем имя потока
            pthread_getname_np(pthread_self(), name, 16);
            // Вносим возвращенную книгу в каталог
            arguments->catalog[old_briefcase] = Book{std::to_string(old_briefcase + 1), name, coordinates[0] + 1,coordinates[1] + 1, coordinates[2] + 1};
        } else {
            return nullptr;
        }
        // Закрываем мьютекс вывода
        pthread_mutex_lock(&mutex2);
        // Пишем в консоль о проделанной работе
        std::cout << name << " has returned a book! Book id: \"" << std::to_string(old_briefcase + 1)
                  << "\" Book address - row: " << coordinates[0] + 1 << " bookcase: "
                  << coordinates[1] + 1 << " book: " << coordinates[2] + 1 << "\n";
        // Открываем мьютекс вывода
        pthread_mutex_unlock(&mutex2);
    }
}

/**
 * Выводит информацию в нужный поток
 * @param os поток
 * @param catalog каталог с книгами
 */
void output_catalog(std::ostream &os, const std::vector<Book> &catalog) {
    for (const auto &i: catalog) {
        os << "Book id: " << i.name << " Row number: "
           << i.m << " Bookcase number: " << i.n << " Book number: "
           << i.k << " returned by " << i.thread_name << "\n";
    }
}

/**
 * Записывает данные в файл (актуально для ввода данных через консоль и командную строку)
 * @param catalog каталог с книгами
 */
void console_to_file(const std::vector<Book> &catalog) {
    std::cout << "\n\nWould you like to write the data above in a file?\nif yes, please input the output file name"
                 "\nif no, input any other string\n";
    std::string path;
    std::cin >> path;
    std::ofstream out;
    out.open(path);
    if (out.is_open()) {
        output_catalog(out, catalog);

    }
    out.close();
}

/**
 * ///Выводит результаты программы в консоль или файл
 * @param catalog каталог с книгами
 * @param input_type способ ввода входных данных
 * @param argv аргументы командной строки
 */
void output_res(const std::vector<Book> &catalog, int input_type, char **argv) {
    if (input_type == 0 || input_type == 3) {
        output_catalog(std::cout, catalog);
        console_to_file(catalog);
    } else {
        // Выводим информацию в выходной файл и консоль
        std::ofstream out;
        if (input_type == 1) {
            out.open(argv[2]);
        } else if (input_type == 2) {
            out.open(argv[1]);
        }
        if (out.is_open()) {
            output_catalog(std::cout, catalog);
            output_catalog(out, catalog);
        }
        std::cout << "The output file has been updated\n";
        out.close();
    }
}

/**
 * Основная функция программы
 * @param argc количество аргументов
 * @param argv аргументы
 * @return код выполнения программы
 */
int main(int argc, char **argv) {
    // Входные данные
    int m, n, k;
    // Вариант ввода данных
    int input_type = work_mode(argc, argv);
    if (input_type == 0) { // ввод данных через консоль
        std::cout << "Please input the amourt of rows, bookcases and books. Use spacebar as a separator:\n";
        std::cin >> m >> n >> k;
    } else if (input_type == 1) { //ввод данных через файл
        std::cout << "File input mode selected\n";
        std::ifstream iff(argv[1]);
        iff >> m >> n >> k;
        iff.close();
    } else if (input_type == 2) { // Генерация случайных входных данных.
        srand(static_cast<unsigned int>(time(0)));
        m = 1 + (rand() % 10);
        n = 1 + (rand() % 10);
        k = 1 + (rand() % 10);
    } else if (input_type == 3) { //ввод данных через командную строку
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        k = atoi(argv[3]);
    } else {
        // Завершаем работу программы в случае неверной передачи аргументов
        std::cout << "Please restart the application with the correct arguments\n";
        return 0;
    }
    // Выводим размер библиотеки
    std::cout << "Input:\nRows: " << m << "\nBookcases per row: " << n
              << "\nBooks per bookcase: " << k << "\n\n";
    // Проверяем данные на корректность
    if (m <= 0 || n <= 0 || k <= 0) {
        // Завершаем работу программы, если входные данные некорректны
        std::cout << "M, N, K values must be positive! Please restart the program and input the correct data\n";
        return 0;
    }
    // Создаем вектор задач, хранящий координаты книг
    std::vector<std::array<int, 3>> tasks = generate_objectives(m, n, k);
    // Подсчитываем максимальное количество задач
    limit = m * n * k;
    // Cоздаем вектор книг (каталог) размером с количеством пропавших книг (M*N*K)
    std::vector<Book> catalog = std::vector<Book>(limit);
    // Создаем аргумент, чтоб позже передать его потокам
    auto *arguments = new Argument{briefcase, tasks, catalog, limit, argv};
    std::cout << "The students started returning books to the library:\n";
    // Cоздаем 3 потока, каждый поток - это какой-то студент
    pthread_t student1, student2, student3;
    // Передаем функцию для исполнения и выдаем потокам имена
    pthread_create(&student1, nullptr, fill_catalog, (void *) arguments);
    pthread_setname_np(student1, "Bob");
    pthread_create(&student2, nullptr, fill_catalog, (void *) arguments);
    pthread_setname_np(student2, "Jake");
    pthread_create(&student3, nullptr, fill_catalog, (void *) arguments);
    pthread_setname_np(student3, "Alice");
    // Подключаем новые потоки к текущему потоку
    pthread_join(student1, nullptr);
    pthread_join(student2, nullptr);
    pthread_join(student3, nullptr);
    std::cout << "THE LOG IS OVER\nPRINTING CATALOG:\n";
    // Вывод каталога в консоль и файл
    output_res(arguments->catalog, input_type, argv);
    delete arguments;
    return 0;
}

