#include <iostream>
#include <fstream>
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

const int max_stream_size = 100;

struct Pipe {
    std::string name = "None";
    double length = 0.;
    int diameter = 0;
    bool in_repair = false;
};

struct Station {
    std::string name = "None";
    int workshops = 0, workshops_in_operation = 0;
    char station_class = 0;
};

template <typename T>
void safe_input( std::string message, T& attribute, T min = 0, T max = std::numeric_limits<T>::max()){  //https://en.cppreference.com/w/cpp/types/numeric_limits.html
    while (1){
        if ((cin >> attribute) && attribute >= min && attribute <= max)//!!!!!!!!!!!!!!!!!!!
            return;
        cout << "Ошибка! " << message;
        cin.clear();
        cin.ignore(max_stream_size, '\n');
    }
}

void save_pipe(const Pipe& pipe, std::ofstream& ofs){
    ofs << "Pipe\n";
    ofs << pipe.name << endl;
    ofs << pipe.length << endl;
    ofs << pipe.diameter << endl;
    ofs << pipe.in_repair << endl;

    cout << "Труба была успешно сохранена" << endl;//!!!
}

void save_station(const Station& station, std::ofstream& ofs){
    ofs << "Station\n";
    ofs << station.name << endl;
    ofs << station.workshops << endl;
    ofs << station.workshops_in_operation << endl;
    ofs << station.station_class << endl;

    cout << "Станция была успешно сохранена" << endl;//!!!
}

void save_to_file(const Pipe& pipe, const Station& station, const std::string& filename){
    std::ofstream ofs(filename);
    if (pipe.diameter || station.workshops){
        if (pipe.diameter)
            save_pipe(pipe, ofs);
        if (station.workshops)
            save_station(station, ofs);
    } else
        cout << "Нет объектов для сохранения в файл" << endl;
}

void load_pipe(Pipe& pipe, std::ifstream& ifs){
    ifs >> std::ws;
    std::getline(ifs, pipe.name);
    ifs >> pipe.length >> pipe.diameter >> pipe.in_repair;
    ifs >> std::ws;
    cout << "Труба загружена успешно" << endl;
}

void load_station(Station& station, std::ifstream& ifs){
    ifs >> std::ws;
    std::getline(ifs, station.name);
    ifs >> station.workshops >> station.workshops_in_operation >> station.station_class;
    ifs >> std::ws;
    cout << "КС загружена успешно" << endl;
}

void load_file(Pipe& pipe, Station& station, const std::string& filename){
    std::ifstream ifs(filename);
    if (!(ifs)){
        cout << "Не удалось открыть файл на чтение" << endl;
        return;
    }
    std::string line;
    while (ifs >> line){
        if (line == "Pipe"){
            load_pipe(pipe, ifs);
        }
        if (line == "Station"){
            load_station(station, ifs);
        }
    }
}

void print_menu(){
    cout << "Выберите действие:" << endl;
    cout << "1. Добавить трубу" << endl;
    cout << "2. Добавить КС" << endl;
    cout << "3. Просмотр всех объектов" << endl;
    cout << "4. Редактировать трубу" << endl;
    cout << "5. Редактировать КС" << endl;
    cout << "6. Сохранить" << endl;
    cout << "7. Загрузить" << endl;
    cout << "0. Выход" << endl;
}


std::istream& operator >> (std::istream& in, Pipe& pipe){
    cout << "Введите название - ";
    in >> std::ws;
    std::getline(in, pipe.name);
    cout << "Введите длину - ";
    safe_input("Введите положительное число: ", pipe.length, 0.00001);
    cout << "Введите диаметр - ";
    safe_input("Введите число не меньше 1: ", pipe.diameter, 1);
    cout << "В ремонте (0 - нет, 1 - да) - ";
    safe_input("Введите 0 (нет) или 1 (да): ", pipe.in_repair, false, true);
    return in;
}

std::istream& operator >> (std::istream& in, Station& station){
    cout << "Введите название - ";
    in >> std::ws;
    std::getline(in, station.name);
    cout << "Введите количество цехов - ";
    safe_input("Введите положительное число: ", station.workshops);
    cout << "Введите количество цехов в работе - ";
    safe_input("Количество цехов в работе не может быть меньше нуля или больше общего количества цехов. Попробуйте еще раз: ", 
        station.workshops_in_operation, 0, station.workshops);
    cout << "Введите класс станции (латинские a, b или c) - ";
    safe_input("Класс станции может быть либо а либо b либо с. Попробуйте еще раз: ", 
        station.station_class, 'a', 'c');
    return in;
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe){
    out << "Название - " << pipe.name << ";\n" 
        << "Длина - " << pipe.length << ";\n"
        << "Диаметр - " << pipe.diameter << ";\n"
        << ((pipe.in_repair) ? "В" : "Не в") << " ремонте" << ";\n\n";
    return out;
}

std::ostream& operator << (std::ostream& out, const Station& station){
    out << "Название - " << station.name << ";\n"
        << "Количество цехов - " << station.workshops << ";\n"
        << "Количество цехов в работе - " << station.workshops_in_operation << ";\n"
        << "Класс станции - " << station.station_class << ";\n\n";
    return out;
}


int main(){
    Pipe pipe;
    Station station;
    int command;
    while (1){
        print_menu();
        safe_input("Такого пунтка меню нет. Введите число от 0 до 7 включительно: ", command, 0, 7);
        switch (command){
            case 1: {
                cout << "1) Добавление новой трубы:" << endl; cin >> pipe;
                break;
            }
            case 2: {
                cout << "2) Добавление новой КС:" << endl; cin >> station;
                break;
            }
            case 3: {
                if (pipe.diameter || station.workshops){
                    cout << "3) ";
                    if (pipe.diameter)
                        cout << "Параметры трубы:" << endl << pipe;
                    if (station.workshops != 0)
                        cout  << "Параметры станции:" << endl << station;
                } else
                    cout << "Ни одного объекта еще не было добавлено" << endl;
                break;
            }
            case 4: {
                cout << "4) Редактирование трубы:" << endl;
                if (pipe.diameter){
                    cout << "Труба все еще в ремонте? (0 - нет, 1 - да) - ";
                    safe_input("Введите 0 (нет) или 1 (да): ", pipe.in_repair, false, true);
                } else
                    cout << "Добавьте трубу перед тем, как ее редактировать" << endl;
                break;
            }
            case 5: {
                cout << "5) Редактирование КС:" << endl;
                if (station.workshops){
                    cout << "Количество цехов в работе на данный момент - ";
                    safe_input("Количество цехов в работе не может быть меньше нуля или больше общего количества цехов. Попробуйте еще раз: ", 
        station.workshops_in_operation, -1, station.workshops);
                } else
                    cout << "Добавтье КС перед так, как ее редактирвоать" << endl;
                break;
            }
            case 6: {
                cout << "6) ";
                save_to_file(pipe, station, "output.dat");
                break;
            }
            case 7:{
                cout << "7) ";
                load_file(pipe, station, "output.dat");
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                cout << "Введенная команда не существует, попробуйте еще раз" << endl;
            }
        }
    }
    return 0;
}