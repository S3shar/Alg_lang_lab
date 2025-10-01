#include "Station.h"
#include <iostream>
#include "utils.h"

int Station::MaxID = 1;

void Station::LoadStation(std::istream& in){
    getline(in >> std::ws, name);
    in >> id >> workshops >> workshops_in_operation >> station_class;
    Station::MaxID = id + 1;
    std::cout << "Станция загружена успешно" << std::endl;
}

void Station::SaveStation(std::ostream& out) const{
    out << "S\n";
    out << name << std::endl;
    out << workshops << std::endl;
    out << workshops_in_operation << std::endl;
    out << station_class << std::endl;

    std::cout << "Станция была успешно сохранена" << std::endl;
}

std::istream& operator >> (std::istream& in, Station& station){
    station.id = Station::MaxID++;
    std::cout << "Введите название - ";
    getline(in >> std::ws, station.name);
    std::cout << "Введите количество цехов - ";
    station.workshops = safe_input(1, 20);
    std::cout << "Введите количество цехов в работе - ";
    station.workshops_in_operation = safe_input(0, station.workshops);
    std::cout << "Введите класс станции (латинские a, b или c) - ";
    station.station_class = safe_input('a', 'b', "a, b или c");
    return in;
}

std::ostream& operator << (std::ostream& out, const Station& station){
    out << "Название - " << station.name << ";\n"
        << "Количество цехов - " << station.workshops << ";\n"
        << "Количество цехов в работе - " << station.workshops_in_operation << ";\n"
        << "Класс станции - " << station.station_class << ";\n\n";
    return out;
}