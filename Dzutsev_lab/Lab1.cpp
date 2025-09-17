#include <iostream>
#include <fstream>
#include <iostream>

enum {max_stream_size = 100, max_string_size = 100};

struct Pipe {
    char name[max_string_size] = "None";
    double length = 0.;
    double diameter = 0.;
    bool in_repair = false;
};

struct Station {
    char name[max_string_size] = "None";
    int workshops = -1, workshops_in_operation = 0;
    short station_class = 0;
};

using std::cout;
using std::cin;
using std::endl;


void safe_double_input(double& attribute){
    while (1){
        if ((cin >> attribute) && attribute > 0.)
            return;
        cout << "Ошибка! Введите положительное число: ";
        cin.clear();
        cin.ignore(max_stream_size, '\n');
    }
}

void safe_bool_input(bool& attribute){
    int temp;
    while (1){
        if ((cin >> temp) && (temp == 0 || temp == 1)){
            attribute = (temp == 1);
            return;
        }
        cout << "Ошибка! Введите 0 (нет) или 1 (да): ";
        cin.clear();
        cin.ignore(max_stream_size, '\n');
    }
}

void safe_int_input(int& attribute){
    while (1){
        if ((cin >> attribute) && attribute >= 0)
            return;
        cout << "Ошибка! Введите неотрицательное число: ";
        cin.clear();
        cin.ignore(max_stream_size, '\n');
    }
}

void check_workshops_in_operation(int& workshops, int& workshops_in_operation){
    while (1){
        if ((cin >> workshops_in_operation) 
        && 0 <= workshops_in_operation && workshops_in_operation <= workshops)
            return;
        cout << "Ошибка! Количество цехов в работе не может быть меньше нуля или больше общего количества цехов.\
        Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(max_stream_size, '\n');
    }
}

void safe_station_class_input(short& station_class){
    while (1){
        if ((cin >> station_class) && (1 <= station_class && station_class <= 5))
            return;
        cout << "Ошибка! Класс станции может быть должен быть целым числом от 1 до 5 включительно.\
        Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(max_stream_size, '\n');
    }
}

std::istream& operator >> (std::istream& in, Pipe& pipe){
    cout << "Введите название - ";
    in >> std::ws;
    std::cin.getline(pipe.name, max_string_size);
    cout << "Введите длину - ";
    safe_double_input(pipe.length);
    cout << "Введите диаметр - ";
    safe_double_input(pipe.diameter);
    cout << "В ремонте (0 - нет, 1 - да) - ";
    safe_bool_input(pipe.in_repair);
    return in;
}

std::istream& operator >> (std::istream& in, Station& station){
    cout << "Введите название - ";
    in >> std::ws;
    std::cin.getline(station.name, max_string_size);
    cout << "Введите количество цехов - ";
    safe_int_input(station.workshops);
    cout << "Введите количество цехов в работе - ";
    check_workshops_in_operation(station.workshops, station.workshops_in_operation);
    cout << "Введите класс станции (целое число от 1 до 5 включительно) - ";
    safe_station_class_input(station.station_class);
    return in;
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe){
    out << "Название - " << pipe.name << ";\n" 
        << "Длина - " << pipe.diameter << ";\n"
        << "Диаметр - " << pipe.length << ";\n"
        << ((pipe.in_repair) ? "В" : "Не в") << " ремонте" << ";\n";
    return out;
}

std::ostream& operator << (std::ostream& out, const Station& station){
    out << "Название - " << station.name << ";\n"
        << "Количество цехов - " << station.workshops << ";\n"
        << "Количество цехов в работе - " << station.workshops_in_operation << ";\n"
        << "Класс станции - " << station.station_class << ";\n";
    return out;
}

int main(){
    Pipe pipe;
    Station station;
    short command;
    while (1){
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех объектов" << endl;
        cout << "4. Редактировать трубу" << endl;
        cout << "5. Редактировать КС" << endl;
        cout << "6. Сохранить" << endl;
        cout << "7. Загрузить" << endl;
        cout << "0. Выход" << endl;

        cin >> command;
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
                if (pipe.diameter || (station.workshops >= 0)){
                    cout << "3) ";
                    if (pipe.diameter)
                        cout << "Параметры трубы:" << endl << pipe;
                    if (station.workshops >= 0)
                        cout  << "Параметры станции:" << endl << station;
                } else
                    cout << "Ни одной трубы еще не было добавлено" << endl;
                break;
            }
            case 4: {
                cout << "4) Редактирование трубы:" << endl;
                if (pipe.diameter){
                    cout << "Труба все еще в ремонте? (0 - нет, 1 - да) - ";
                    safe_bool_input(pipe.in_repair);
                } else
                    cout << "Добавьте трубу перед тем, как ее редактировать" << endl;
                break;
            }
            case 5: {
                cout << "5) Редактирование КС:" << endl;
                if (station.workshops >= 0){
                    cout << "Количество цехов в работе на данный момент - ";
                    check_workshops_in_operation(station.workshops, station.workshops_in_operation);
                } else
                    cout << "Добавтье КС перед так, как ее редактирвоать" << endl;
                break;
            }
            case 6: {
                cout << "6) ";
                std::ofstream ofs("output.dat", std::ios::out | std::ios::binary);
                if (!(ofs)){
                    std::cerr << "Не удалось создать файл для записи" << endl;
                    break;
                }
                ofs.write((char *)&pipe, sizeof(Pipe));
                ofs.write((char *)&station, sizeof(Station));
                ofs.close();
                cout << "Данные успешно сохранены" << endl;
                break;
            }
            case 7:{
                cout << "7) ";
                std::ifstream ifs ("output.dat", std::ios::in | std::ios::binary);
                if (!(ifs)){
                    std::cerr << "Не удалось открыть файл на чтение" << endl;
                    break;
                }
                ifs.read((char *)&pipe, sizeof(Pipe));
                ifs.read((char *)&station, sizeof(Station));
                ifs.close();
                cout << "Данные успешно загружены" << endl;
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