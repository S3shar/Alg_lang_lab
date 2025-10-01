#pragma once
#include <string>
#include <iostream>


class Pipe {
    int id;
	std::string name = "None";
	double length = 0.0;
	int diameter = 0;
	bool in_repair = false;
public:
    static int MaxID;
	
	int getId() const { return id; }
	std::string getName() const { return name; }
	double getLength() const { return length; }
	int getDiameter() const { return diameter; }
	bool isInRepair() const { return in_repair; }

	void setInRepair(bool r) { in_repair = r; }

	void LoadPipe(std::istream& in);
	void SavePipe(std::ostream& out) const;

	friend std::istream& operator>>(std::istream& in, Pipe& pipe);
	friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
};