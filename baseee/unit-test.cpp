// unit-test.cpp单元测试
//MIT License
//Copyright(c) 2020 chhdao
//

#include <iostream>
#include "string.hpp"
#include "log.hpp"
#include <utility>

using namespace std;
using namespace baseee;

int main(int argc,char *argv[])
{
	std::string s("           Hello World    ");

	cout << std::string(s.size(),'-') << endl;
	cout << s << endl;
	auto c = baseee::string::SwapCase(s);
	cout << c << endl;
	cout << baseee::string::SwapCase(s) << endl;

	


	return 0;
}
