// unit-test.cpp单元测试
//MIT License
//Copyright(c) 2020 chhdao
//

#include <iostream>
#include "baseee-string/string.hpp"
#include "baseee-log/log.hpp"
#include <utility>
#include <thread>
#include <array>
#include <bitset>
#include <ctime>
#include <cstdio>

using namespace std;
using namespace baseee;



int main(int argc,char *argv[])
{
	array<char,8> in = { u8"Unicode" };
	array<char16_t,8> out;
	array<char16_t,8> key = { u"Unicode" };


	time_t b = clock();
	baseee::coder::Utf8ToUtf16(in.cbegin(), in.cend(), out.begin(), out.end());
	time_t e = clock();
	int ok = 0, err = 0;
	for (int a = 0; a < out.size(); a++) {
		if (out[a] == key[a]) ++ok;
		else {
			++err;
			cout << "right:" << bitset<8>(key[a]) << endl;
			cout << "error:" << bitset<8>(out[a]) << endl;
		}
	}
	cout << "OK:" << ok << endl;
	cout << "ERR:" << err << endl;
	cout << "begin:" << b << "\nend:" << e << endl;
	cout << "use:" << e - b << endl;


	return 0;
}
