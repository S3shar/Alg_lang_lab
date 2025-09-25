#include <iostream>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

const int max_stream_size = 100;

struct Pipe {
    string name = "None";
    double length = 0.;
    int diameter = 0;
    bool in_repair = false;
};

struct Station {
    string name = "None";
    int workshops = 0, workshops_in_operation = 0;
    char station_class = ' ';
};

template <typename T>
T safe_input(T min, T max, string message = "None"){
    T attribute;
    while (1){
        if ((cin >> attribute) && attribute >= min && attribute <= max)
            return attribute;
        cout << "Введите ";
        if (message == "None")
            cout << "число от " << min << " до " << max;
        else
            cout << message;
        cout << ": ";
        cin.clear();
        cin.ignore(max_stream_size, '\n');
    }
}

void save_pipe(const Pipe& pipe, ofstream& ofs){
    ofs << "Pipe\n";
    ofs << pipe.name << endl;
    ofs << pipe.length << endl;
    ofs << pipe.diameter << endl;
    ofs << pipe.in_repair << endl;

    cout << "Труба была успешно сохранена" << endl;
}

void save_station(const Station& station, ofstream& ofs){
    ofs << "Station\n";
    ofs << station.name << endl;
    ofs << station.workshops << endl;
    ofs << station.workshops_in_operation << endl;
    ofs << station.station_class << endl;

    cout << "Станция была успешно сохранена" << endl;
}

void save_to_file(const Pipe& pipe, const Station& station, const string& filename){
    ofstream ofs(filename);
    if (pipe.diameter || station.workshops){
        if (pipe.diameter)
            save_pipe(pipe, ofs);
        if (station.workshops)
            save_station(station, ofs);
    } else
        cout << "Нет объектов для сохранения в файл" << endl;
}

void load_pipe(Pipe& pipe, ifstream& ifs){
    getline(ifs >> ws, pipe.name);
    ifs >> pipe.length >> pipe.diameter >> pipe.in_repair;
    cout << "Труба загружена успешно" << endl;
}

void load_station(Station& station, ifstream& ifs){
    getline(ifs >> ws, station.name);
    ifs >> station.workshops >> station.workshops_in_operation >> station.station_class;
    cout << "КС загружена успешно" << endl;
}

void load_file(Pipe& pipe, Station& station, const string& filename){
    ifstream ifs(filename);
    if (!(ifs)){
        cout << "Не удалось открыть файл на чтение" << endl;
        return;
    }
    string line;
    pipe={};
    station={};
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


istream& operator >> (istream& in, Pipe& pipe){
    cout << "Введите название - ";
    in >> ws;
    getline(in, pipe.name);
    cout << "Введите длину (км) - ";
    pipe.length = safe_input(0.001, 4000.);
    cout << "Введите диаметр (мм) - ";
    pipe.diameter = safe_input(0, 1420);
    cout << "В ремонте (0 - нет, 1 - да) - ";
    pipe.in_repair = safe_input(0, 1, "0 (нет) или 1 (да)");
    return in;
}

istream& operator >> (istream& in, Station& station){
    cout << "Введите название - ";
    in >> ws;
    getline(in, station.name);
    cout << "Введите количество цехов - ";
    station.workshops = safe_input(1, 20);
    cout << "Введите количество цехов в работе - ";
    station.workshops_in_operation = safe_input(0, station.workshops);
    cout << "Введите класс станции (латинские a, b или c) - ";
    station.station_class = safe_input('a', 'b', "a, b или c");
    return in;
}

ostream& operator << (ostream& out, const Pipe& pipe){
    out << "Название - " << pipe.name << ";\n" 
        << "Длина - " << pipe.length << ";\n"
        << "Диаметр - " << pipe.diameter << ";\n"
        << ((pipe.in_repair) ? "В" : "Не в") << " ремонте" << ";\n\n";
    return out;
}

ostream& operator << (ostream& out, const Station& station){
    out << "Название - " << station.name << ";\n"
        << "Количество цехов - " << station.workshops << ";\n"
        << "Количество цехов в работе - " << station.workshops_in_operation << ";\n"
        << "Класс станции - " << station.station_class << ";\n\n";
    return out;
}


int main(){
    Pipe pipe;
    Station station;
    while (1){
        print_menu();
        switch (safe_input(0, 7)){
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
                    pipe.in_repair = safe_input(0, 1, "0 (нет) или 1 (да): ");
                } else
                    cout << "Добавьте трубу перед тем, как ее редактировать" << endl;
                break;
            }
            case 5: {
                cout << "5) Редактирование КС:" << endl;
                if (station.workshops){
                    cout << "Количество цехов в работе на данный момент - ";
                    station.workshops_in_operation = safe_input(0, station.workshops);
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