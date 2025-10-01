#pragma once
#include <iostream>

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

