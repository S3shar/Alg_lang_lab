#include <iostream>
#include <fstream>
#include <limits>
#include "Pipe.h"
#include "Station.h"
#include "utils.h"
#include <format>
#include <chrono>

using namespace std;
using namespace chrono;

const int max_stream_size = 100;


// void save_pipe(const Pipe& pipe, ofstream& ofs){
//     ofs << "Pipe\n";
//     ofs << pipe.name << endl;
//     ofs << pipe.length << endl;
//     ofs << pipe.diameter << endl;
//     ofs << pipe.in_repair << endl;

//     cout << "Труба была успешно сохранена" << endl;
// }

// void save_station(const Station& station, ofstream& ofs){
//     ofs << "S\n";
//     ofs << station.name << endl;
//     ofs << station.workshops << endl;
//     ofs << station.workshops_in_operation << endl;
//     ofs << station.station_class << endl;

//     cout << "Станция была успешно сохранена" << endl;
// }

void save_to_file(const Pipe& pipe, const Station& station, const string& filename){
    ofstream ofs(filename);
    if (pipe.getDiameter() || station.getWorkshops()){
        if (pipe.getDiameter())
            pipe.SavePipe(ofs);
        if (station.getWorkshops())
            station.SaveStation(ofs);
    } else
        cout << "Нет объектов для сохранения в файл" << endl;
}

// void load_pipe(Pipe& pipe, ifstream& ifs){
//     getline(ifs >> ws, pipe.getName());
//     ifs >> pipe.length >> pipe.diameter >> pipe.in_repair;
//     cout << "Труба загружена успешно" << endl;
// }

// void load_station(Station& station, ifstream& ifs){
//     getline(ifs >> ws, station.getName());
//     ifs >> station.workshops >> station.workshops_in_operation >> station.station_class;
//     cout << "КС загружена успешно" << endl;
// }

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
            pipe.LoadPipe(ifs);
        }
        if (line == "S"){
            station.LoadStation(ifs);
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


int main(){
    redirect_output_wrapper cerr_log(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_"+ time);
	if (logfile)
		cerr_log.redirect(logfile);
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
                if (pipe.getDiameter() || station.getWorkshops()){
                    cout << "3) ";
                    if (pipe.getDiameter())
                        cout << "Параметры трубы:" << endl << pipe;
                    if (station.getWorkshops() != 0)
                        cout  << "Параметры станции:" << endl << station;
                } else
                    cout << "Ни одного объекта еще не было добавлено" << endl;
                break;
            }
            case 4: {
                cout << "4) Редактирование трубы:" << endl;
                if (pipe.getDiameter()){
                    cout << "Труба все еще в ремонте? (0 - нет, 1 - да) - ";
                    pipe.setInRepair(safe_input(0, 1, "0 (нет) или 1 (да): "));
                } else
                    cout << "Добавьте трубу перед тем, как ее редактировать" << endl;
                break;
            }
            case 5: {
                cout << "5) Редактирование КС:" << endl;
                if (station.getWorkshops()){
                    cout << "Количество цехов в работе на данный момент - ";
                    station.setStationClass(safe_input(0, station.getWorkshops()));
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