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
	wstring input = L"��һ�������͵İ�ѧ�����У��Ͼ���ѧ����ǰ����ʱ��ͬ�����������干���ˣ�ı����֮ǿʢ�����ѧ֮������Ϊ���ҵĸ�ǿ�������������������Ҫ�Ĺ��ס������Ǹĸ￪����������Ϊ������ֱ�����ص��ۺ��Դ�ѧ���Ͼ���ѧ����ո�µ���ʷ�����л������µ��������ڽ�ѧ�����к�������ȸ������򱣳����õķ�չ̬�ƣ������ѧָ����ۺ�ʵ����λ��ȫ����Уǰ�С�1994�꣬�Ͼ���ѧ��ȷ��Ϊ���ҡ�211���̡��ص�֧�ֵĴ�ѧ��1999�꣬�Ͼ���ѧ������ҡ�985���̡������ص㽨��ĸ�ˮƽ��ѧ���У�2006�꣬�������ͽ���ʡ�ٴ�ǩ���ص㹲���Ͼ���ѧ��Э�飻2011�꣬�������ͽ���ʡǩ��Э������ص㹲���Ͼ���ѧ��";
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