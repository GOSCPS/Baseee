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
	vector<char32_t> in;//= { U"🎀🏳️‍🌈Unicode统一世界🏳️‍🌈🎀" };
	vector<char> out;
	vector<char> key;//= { u8"🎀🏳️‍🌈Unicode统一世界🏳️‍🌈🎀" };


	time_t b = clock();
	for (int a = 0; a < 3; a++) {
		cout << baseee::coder::Utf32ToUtf8(in.cbegin(), in.cend(), out.begin(), out.end()) << endl;
		cout << baseee::coder::Utf8ToUtf32(out.cbegin(), out.cend(), in.begin(), in.end()) << endl;
		cout << baseee::coder::Utf32ToUtf8(in.cbegin(), in.cend(), out.begin(), out.end()) << endl;
	}
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
