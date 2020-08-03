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

using namespace std;
using namespace baseee;



int main(int argc,char *argv[])
{
	array<char, 1112> in = {u8"𐐷€奉旨朕钦奉隆裕皇太后懿旨：前因民军起事，各省响应，九夏沸腾，生灵涂炭。特命袁世凯遣员与民军代表讨论大局，议开国会、公决政体。两月以来，尚无确当办法。南北暌隔，彼此相持。商辍于途，士露于野。徒以国体一日不决，故民生一日不安。今全国人民心理多倾向共和。南中各省，既倡议于前，北方诸将，亦主张于后。人心所向，天命可知。予亦何忍因一姓之尊荣，拂兆民之好恶。是用外观大势，内审舆情，特率皇帝将统治权公诸全国，定为共和立宪国体。近慰海内厌乱望治之心，远协古圣天下为公之义。袁世凯前经资政院选举为总理大臣，当兹新旧代谢之际，宜有南北统一之方。即由袁世凯以全权组织临时共和政府，与民军协商统一办法。总期人民安堵，海宇乂安，仍合满、汉、蒙、回、藏五族完全领土为一大中华民国。予与皇帝得以退处宽闲，优游岁月，长受国民之优礼，亲见郅治之告成，岂不懿欤！钦此。"};
	array<char32_t, 371> out;
	array<char32_t, 371> key = {U"𐐷€奉旨朕钦奉隆裕皇太后懿旨：前因民军起事，各省响应，九夏沸腾，生灵涂炭。特命袁世凯遣员与民军代表讨论大局，议开国会、公决政体。两月以来，尚无确当办法。南北暌隔，彼此相持。商辍于途，士露于野。徒以国体一日不决，故民生一日不安。今全国人民心理多倾向共和。南中各省，既倡议于前，北方诸将，亦主张于后。人心所向，天命可知。予亦何忍因一姓之尊荣，拂兆民之好恶。是用外观大势，内审舆情，特率皇帝将统治权公诸全国，定为共和立宪国体。近慰海内厌乱望治之心，远协古圣天下为公之义。袁世凯前经资政院选举为总理大臣，当兹新旧代谢之际，宜有南北统一之方。即由袁世凯以全权组织临时共和政府，与民军协商统一办法。总期人民安堵，海宇乂安，仍合满、汉、蒙、回、藏五族完全领土为一大中华民国。予与皇帝得以退处宽闲，优游岁月，长受国民之优礼，亲见郅治之告成，岂不懿欤！钦此。"};


	time_t b = clock();
	cout << baseee::coder::Utf8ToUtf32(in.cbegin(), in.cend(), out.begin(), out.end()) << endl;
	time_t e = clock();
	int ok = 0, err = 0;
	for (int a = 0; a < 371; a++) {
		if (out[a] == key[a]) ++ok;
		else {
			++err;
		}
	}
	cout << "OK:" << ok << endl;
	cout << "ERR:" << err << endl;
	cout << "begin:" << b << "\nend:" << e << endl;
	cout << "use:" << e - b << endl;


	return 0;
}
