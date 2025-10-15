#pragma once
#include <iostream>
#include <unordered_map>

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl

#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
    }
	void redirect (std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

template <typename T, typename T2>
using Filter = bool(*)(const T2& obj, T param);

template <typename T, typename T2>
void find_by_filter(const std::unordered_map<int, T2>& objs, Filter<T, T2> f, T param){
	if (objs.empty()){
		std::cout << "Добавьте хотя бы один объект" << std::endl;
        return;
	}
    std::cout << "4) Просмотр объектов по фильтру:" << std::endl;
	for (const auto & obj : objs){
		if (f(obj.second, param))
			std::cout << obj.second;
	}
}

template <typename T>
T safe_input(T min, T max, std::string message = "None"){
	T attribute;
	while (!(std::cin >> attribute)
        || std::cin.peek() != '\n'
        || attribute < min || attribute > max){
		std::cout << "Введите ";
		if (message == "None")
			std::cout << "число от " << min << " до " << max;
		else
			std::cout << message;
		std::cout << ": ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
    std::cerr << attribute << std::endl;
    return attribute;
}

