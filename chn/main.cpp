#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>
#include <ctime>
using namespace std;
int main() {
	locale china("chs");
	wfstream fio;
	unordered_set<wstring> wset;
	fio.imbue(china); wcin.imbue(china); wcout.imbue(china);
	fio.open("baidu.txt");
	wstring s;
	while (!fio.eof()) {
		fio >> s;
		wset.insert(s);
		fio >> s; 
	}
	size_t loc, forward_parts = 0, backward_parts = 0;
	bool isword = true;
	wstring input = L"在一个多世纪的办学历程中，南京大学及其前身与时代同呼吸、与民族共命运，谋国家之强盛、求科学之进步，为国家的富强和民族的振兴做出了重要的贡献。尤其是改革开放以来，作为教育部直属的重点综合性大学，南京大学又在崭新的历史机遇中焕发出新的生机，在教学、科研和社会服务等各个领域保持良好的发展态势，各项办学指标和综合实力均位居全国高校前列。1994年，南京大学被确定为国家“211工程”重点支持的大学；1999年，南京大学进入国家“985工程”首批重点建设的高水平大学行列；2006年，教育部和江苏省再次签订重点共建南京大学的协议；2011年，教育部和江苏省签署协议继续重点共建南京大学。";
	wstring copy = input;
	while (input.size() > 0) {
		loc = 0;
		for (size_t i = 4 < input.size() ? 4 : input.size(); i > 1; --i) {
			wstring wtemp = input.substr(0, i);
			if (wset.find(wtemp) != wset.end()) {
				if (!isword)
					wcout << " ";
				wcout << wtemp << " ";
				loc = i;
				forward_parts++;
				isword = true;
				break;
			}
		}
		if (!loc) {
			wcout << input.substr(0, 1);
			loc = 1;
			isword = false;
		}
		input = input.substr(loc);
	}
	cout << "\nparts: " << forward_parts << endl;
	isword = true;
	input = copy;
	wstringstream wss;
	vector<wstring> vecw;
	while (input.size() > 0) {
		loc = 0;
		for (size_t i = 4 < input.size() ? 4 : input.size(); i > 1; --i) {
			wstring wtemp = input.substr(input.length() - i);
			if (wset.find(wtemp) != wset.end()) {
				if (!isword)
					vecw.push_back(L" ");
				vecw.push_back(L" " + wtemp);
				loc = i;
				backward_parts++;
				isword = true;
				break;
			}
		}
		if (!loc) {
			vecw.push_back(input.substr(input.length() - 1));
			loc = 1;
			isword = false;
		}
		input = input.substr(0, input.length() - loc);
	}
	for (auto i = vecw.size() - 1; i > 0; --i)
		wcout << vecw[i];
	cout << "\nparts: " << backward_parts << endl;
	return 0;
}