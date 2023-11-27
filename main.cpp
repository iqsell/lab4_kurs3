#include "classes.h"
int main() {
    SecondPerson FirstPerson;
    int choice;
    int personChoice;
    std::string start_time, end_time, desc;
    Dailytern free_time(-1, -1, "");
    std::string old_start_time;
    SecondPerson secondPerson;

    do {
        std::cout
                << "Выберите человека (1 - Первый человек, 2 - Второй человек, 3 - Выход из программы, 4 - сложение, 5 - вычитание, 6- деление): ";
        std::cin >> personChoice;

        switch (personChoice) {
            case 1:
                do {
                    std::cout
                            << "Выберите действие:\n1. Добавить работу\n2. Удалить работу\n3. Изменить работу\n4. Найти свободное время\n5. Сгенерировать список дел\n6. Выход\n";
                    std::cin >> choice;

                    switch (choice) {
                        case 1:
                            do {
                                std::cout << "Введите время начала и окончания работы в формате ЧЧ:ММ:\n";
                                std::cin >> start_time >> end_time;
                            } while (!checkTimeFormat(start_time) || !checkTimeFormat(end_time));
                            std::getline(std::cin >> std::ws, desc);
                            FirstPerson.addWork(convertTimeToInt(start_time), convertTimeToInt(end_time), desc);
                            break;
                        case 2:
                            do {
                                std::cout << "Введите время начала работы, которую нужно удалить, в формате ЧЧ:ММ:\n";
                                std::cin >> start_time;
                            } while (!checkTimeFormat(start_time));
                            FirstPerson.removeWork(convertTimeToInt(start_time));
                            break;
                        case 3:
                            do {
                                std::cout
                                        << "Введите время начала существующей работы, новое время начала, новое время окончания и новое описание в формате ЧЧ:ММ:\n";
                                std::cin >> old_start_time >> start_time >> end_time;
                            } while (!checkTimeFormat(start_time) || !checkTimeFormat(end_time) ||
                                     !checkTimeFormat(old_start_time));
                            std::getline(std::cin >> std::ws, desc);
                            FirstPerson.changeWork(convertTimeToInt(old_start_time), convertTimeToInt(start_time),
                                                   convertTimeToInt(end_time), desc);
                            break;
                        case 4:
                            do {
                                std::cout
                                        << "Введите время начала и время окончания для поиска свободного времени в формате ЧЧ:ММ:\n";
                                std::cin >> start_time >> end_time;
                            } while (!checkTimeFormat(start_time) || !checkTimeFormat(end_time));
                            free_time = FirstPerson.findFreeTime(convertTimeToInt(start_time),
                                                                 convertTimeToInt(end_time));
                            if (free_time.start_time != -1) {
                                std::cout << "Свободное время найдено с " << free_time.start_time << " до "
                                          << free_time.end_time << std::endl;
                            } else {
                                std::cout << "Свободное время не найдено" << std::endl;
                            }
                            break;
                        case 5:
                            std::cout << "Генерация списка дел:\n";
                            FirstPerson.generateRedo();
                            break;
                        case 6:
                            break;
                        default:
                            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
                    }
                } while (choice != 6);
                break;
            case 2:
                do {
                    std::cout
                            << "Выберите действие для второго человека:\n1. Добавить работу\n2. Удалить работу\n3. Изменить работу\n4. Найти свободное время\n5. Сгенерировать список дел\n6. Выход\n";
                    std::cin >> choice;

                    switch (choice) {
                        case 1:
                            do {
                                std::cout << "Введите время начала и окончания работы в формате ЧЧ:ММ:\n";
                                std::cin >> start_time >> end_time;
                            } while (!checkTimeFormat(start_time) || !checkTimeFormat(end_time));
                            std::getline(std::cin >> std::ws, desc);
                            secondPerson.addWork(convertTimeToInt(start_time), convertTimeToInt(end_time), desc);
                            break;
                        case 2:
                            do {
                                std::cout << "Введите время начала работы, которую нужно удалить, в формате ЧЧ:ММ:\n";
                                std::cin >> start_time;
                            } while (!checkTimeFormat(start_time));
                            secondPerson.removeWork(convertTimeToInt(start_time));
                            break;
                        case 3:
                            do {
                                std::cout
                                        << "Введите время начала существующей работы, новое время начала, новое время окончания и новое описание в формате ЧЧ:ММ:\n";
                                std::cin >> old_start_time >> start_time >> end_time;
                            } while (!checkTimeFormat(start_time) || !checkTimeFormat(end_time) ||
                                     !checkTimeFormat(old_start_time));
                            std::getline(std::cin >> std::ws, desc);
                            secondPerson.changeWork(convertTimeToInt(old_start_time), convertTimeToInt(start_time),
                                                    convertTimeToInt(end_time), desc);
                            break;
                        case 4:
                            do {
                                std::cout
                                        << "Введите время начала и время окончания для поиска свободного времени в формате ЧЧ:ММ:\n";
                                std::cin >> start_time >> end_time;
                            } while (!checkTimeFormat(start_time) || !checkTimeFormat(end_time));
                            free_time = secondPerson.findFreeTime(convertTimeToInt(start_time),
                                                                  convertTimeToInt(end_time));
                            if (free_time.start_time != -1) {
                                std::cout << "Свободное время найдено с " << free_time.start_time << " до "
                                          << free_time.end_time << std::endl;
                            } else {
                                std::cout << "Свободное время не найдено" << std::endl;
                            }
                            break;
                        case 5:
                            std::cout << "Генерация списка дел для второго человека:\n";
                            secondPerson.generateRedo();
                            break;
                        case 6:
                            break;
                        default:
                            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
                    }
                } while (choice != 6);
                break;
            case 4:
            {
                std::vector<Dailytern> unionSchedule = FirstPerson + secondPerson;
                std::cout << "Объединенный список дел:\n";
                for (const auto &work: unionSchedule) {
                    std::cout << work.description << " (с " << work.start_time << " до " << work.end_time << ")"
                              << std::endl;
                }
                break;
            }
            case 5: // разность
            {
                std::vector<Dailytern> differenceSchedule = FirstPerson - secondPerson;
                std::cout << "Разница в расписаниях:\n";
                for (const auto &work: differenceSchedule) {
                    std::cout << work.description << " (с " << work.start_time << " до " << work.end_time << ")"
                              << std::endl;
                }
                break;
            }
            case 6: // пересечение
            {
                std::vector<Dailytern> intersectionSchedule = FirstPerson / secondPerson;
                std::cout << "Пересечение расписаний:\n";
                for (const auto &work: intersectionSchedule) {
                    std::cout << work.description << " (с " << work.start_time << " до " << work.end_time << ")"
                              << std::endl;
                }
                break;
            }
            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";

        }
    } while (personChoice != 3);

    return 0;
}

