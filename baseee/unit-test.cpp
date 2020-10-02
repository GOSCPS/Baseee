// unit-test.cpp单元测试
//MIT License
//Copyright(c) 2020 chhdao
//

#include <iostream>
#include "string.hpp"
#include "log.hpp"
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
	array<char,13> Source = {u8"𐐷aa哈哈"};
	array<char16_t, 7> Key = { u"𐐷aa哈哈" };
	array<char16_t, 7> Aims;
	array<char, 13> Tmp = {};

	cout << baseee::coder::Utf8ToUtf16(Source.begin(), Source.end(),
		Aims.begin(), Aims.end()) << endl;
	cout << baseee::coder::Utf16ToUtf8(Aims.begin(), Aims.end(), Tmp.begin(), Tmp.end())
		<< endl;
	cout << baseee::coder::Utf8ToUtf16(Tmp.begin(), Tmp.end(),
		Aims.begin(), Aims.end()) << endl;

	for (auto a = 0; a < Key.size(); a++) {
		if (Key[a] == Aims[a]) {
			cout << "OK" << endl;
		}
		else {
			cout << "ERROR" << endl;
			cout << "At " << a << endl;
			cout << bitset<16>(Key[a]) << " <- " << bitset<16>(Aims[a]) << endl;
		}
	}

	return 0;
}
