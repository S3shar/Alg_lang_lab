#pragma once
#include <string>
#include <iostream>


class Station {
    static int MaxID;
    int id;
    std::string name = "None";
    int workshops = 0, workshops_in_operation = 0;
    char station_class = 'a';
public:
    
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getWorkshops() const { return workshops; }
    int getWorkshopsInOperation() const { return workshops_in_operation; }

    void setStationClass(char c) { station_class = c; }

    void LoadStation(std::istream& in);
    void SaveStation(std::ostream& out) const;

    static bool check_station_by_name(const Station& station, std::string name);
    static bool check_station_by_workshop_percentage(const Station& station, double percentage);

    friend std::istream& operator>>(std::istream& in, Station& station);
    friend std::ostream& operator<<(std::ostream& out, const Station& station);
};