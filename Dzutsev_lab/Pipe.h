#pragma once
#include <string>
#include <iostream>


class Pipe {
    static int MaxID;
    int id;
	std::string name = "None";
	double length = 0.0;
	int diameter = 0;
	bool in_repair = false;
public:
	
	int getId()  { return id; }
	std::string getName() const { return name; }
	double getLength() const { return length; }
	int getDiameter() const { return diameter; }
	bool isInRepair() const { return in_repair; }

	void setInRepair(bool r) { in_repair = r; }

	void LoadPipe(std::istream& in);
	void SavePipe(std::ostream& out) const;

	static bool check_pipe_by_name(const Pipe& pipe, std::string name);
	static bool check_pipe_by_in_repair(const Pipe& pipe, bool in_rep);

	friend std::istream& operator>>(std::istream& in, Pipe& pipe);
	friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
};