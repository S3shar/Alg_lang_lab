#include "Pipe.h"
#include <iostream>
#include "utils.h"

int Pipe::MaxID = 1;

void Pipe::LoadPipe(std::istream& in){
	getline(in >> std::ws, name);
	in >> id >> length >> diameter >> in_repair;
	Pipe::MaxID = id + 1;
	std::cout << "Труба загружена успешно" << std::endl;
}

void Pipe::SavePipe(std::ostream& out) const{
	out << "Pipe\n";
	out << name << std::endl;
	out << length << std::endl;
	out << diameter << std::endl;
	out << in_repair << std::endl;

	std::cout << "Труба была успешно сохранена" << std::endl;
}

std::istream& operator >> (std::istream& in, Pipe& pipe) {
	pipe.id = Pipe::MaxID++;
	std::cout << "Введите название - ";
	std::getline(in >> std::ws, pipe.name);
	std::cout << "Введите длину (км) - ";
	pipe.length = safe_input(0.001, 4000.);
	std::cout << "Введите диаметр (мм) - ";
	pipe.diameter = safe_input(0, 1420);
	std::cout << "В ремонте (0 - нет, 1 - да) - ";
	pipe.in_repair = safe_input(0, 1, "0 (нет) или 1 (да)");
	return in;
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe) {
	out << "Название - " << pipe.name << ";\n"
		<< "Длина - " << pipe.length << ";\n"
		<< "Диаметр - " << pipe.diameter << ";\n"
		<< ((pipe.in_repair) ? "В" : "Не в") << " ремонте" << ";\n\n";
	return out;
}
