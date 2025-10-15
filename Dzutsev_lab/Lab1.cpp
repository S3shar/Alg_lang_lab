#include <iostream>
#include <fstream>
#include <limits>
#include "Pipe.h"
#include "Station.h"
#include "utils.h"
#include <format>
#include <chrono>
#include <unordered_map>


using namespace std;
using namespace chrono;
void save_to_file(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Station>& stations, const string& filename){
    ofstream ofs(filename);
    if (!(pipes.empty() && stations.empty())){
        if (!pipes.empty())
            for (const auto& pipe : pipes)
                pipe.second.SavePipe(ofs);
        if (!stations.empty())
            for (const auto& station : stations)
                station.second.SaveStation(ofs);
    } else
        cout << "Нет объектов для сохранения в файл" << endl;
}


void load_file(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations, const string& filename){
    ifstream ifs(filename);
    if (!ifs){
        cout << "Такого файла не существует" << endl;
        return;
    }
    Pipe pipe;
    Station station;
    string line;
    pipes.clear();
    stations.clear();
    while (ifs >> line){
        if (line == "P"){
            pipe.LoadPipe(ifs);
            pipes[pipe.getId()] = pipe;
        }
        if (line == "S"){
            station.LoadStation(ifs);
            stations[station.getId()] = station;
        }
    }
}


void print_menu(){
    cout << "Выберите действие:" << endl;
    cout << "1. Добавить трубу" << endl;
    cout << "2. Добавить КС" << endl;
    cout << "3. Просмотр всех объектов" << endl;
    cout << "4. Просмотр труб по фильтру" << endl;
    cout << "5. Просмотр КС по фильтру" << endl;
    cout << "6. Редактировать трубу" << endl;
    cout << "7. Редактировать КС" << endl;
    cout << "8. Сохранить" << endl;
    cout << "9. Загрузить" << endl;
    cout << "0. Выход" << endl;
}


int main(){
    redirect_output_wrapper cerr_log(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_"+ time + ".log");
	if (logfile)
		cerr_log.redirect(logfile);
    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;
    while (1){
        print_menu();
        switch (safe_input(0, 9)){
            case 1: {
                Pipe pipe;
                cout << "1) Добавление новой трубы:" << endl;
                cin >> pipe;
                pipes[pipe.getId()] = pipe;
                break;
            }
            case 2: {
                Station station;
                cout << "2) Добавление новой КС:" << endl;
                cin >> station;
                stations[station.getId()] = station;
                break;
            }
            case 3: {
                if (!(pipes.empty() && stations.empty())){
                    cout << "3) ";
                    if (!pipes.empty()){
                        for (const auto& pipe : pipes)
                            cout << "Параметры трубы с id " << pipe.first << ":"  << endl << pipe.second;
                    }
                    if (!stations.empty()){
                        for (const auto& station : stations)
                            cout  << "Параметры станции с id " << station.first << endl << station.second;
                    }
                } else
                    cout << "Ни одного объекта еще не было добавлено" << endl;
                break;
            }
            case 4: {
                cout << "Фильтр (по названию - 0, по признаку 'в ремонте' - 1): ";
                if (safe_input(0, 1) == 0){
                    cout << "Название: ";
                    string name;
                    INPUT_LINE(cin, name);
                    find_by_filter(pipes, Pipe::check_pipe_by_name, name);
                } else {
                    std::cout << "В ремонте (0 - нет, 1 - да) - ";
	                find_by_filter(pipes, Pipe::check_pipe_by_in_repair, (bool)safe_input(0, 1, "0 (нет) или 1 (да)"));
                }
                break;
            }
            case 5: {
                cout << "Фильтр (по названию - 0, по проценту незадействованных цехов - 1): ";
                if (safe_input(0, 1) == 0){
                    cout << "Название: ";
                    string name;
                    INPUT_LINE(cin, name);
                    find_by_filter(stations, Station::check_station_by_name, name);
                } else {
                    std::cout << "Минимальный процент незадействованных цехов (от 0 до 100) - ";
                    find_by_filter(stations, Station::check_station_by_workshop_percentage, safe_input(0., 100.) / 100.);
                }
                break;
            }    
            // case 4: {
            //     cout << "4) Редактирование трубы:" << endl;
            //     if (!pipes.empty()){
            //         cout << "Укажите номер трубы, котору"
            //         cout << "Труба все еще в ремонте? (0 - нет, 1 - да) - ";
            //         pipe.setInRepair(safe_input(0, 1, "0 (нет) или 1 (да): "));
            //     } else
            //         cout << "Добавьте трубу перед тем, как ее редактировать" << endl;
            //     break;
            // }
            // case 5: {
            //     cout << "5) Редактирование КС:" << endl;
            //     if (!stations.empty()){
            //         cout << "Количество цехов в работе на данный момент - ";
            //         station.setStationClass(safe_input(0, station.getWorkshops()));
            //     } else
            //         cout << "Добавтье КС перед так, как ее редактирвоать" << endl;
            //     break;
            // }
            case 6: {
                cout << "6) ";
                cout << "Укажите файл для сохранения (по умолчанию output.dat): ";
                string filename;
                INPUT_LINE(cin, filename);
                if (filename.empty())
                    filename = "output.dat";
                save_to_file(pipes, stations, filename);
                break;
            }
            case 7:{
                cout << "7) ";
                cout << "Укажите файл для загрузки (по умолчанию output.dat): ";

                string filename;
                INPUT_LINE(cin, filename);
                if (filename.empty())
                    filename = "output.dat";
                load_file(pipes, stations, filename);
                break;
            }
            case 0: {
                return 0;
            }
        }
    }
    return 0;
}