#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>
#include <ctime>
using namespace std;

struct Parent {
	unordered_map<wstring, int> key;
	int sum;
};

struct Per {
	size_t loc;
	double prob;
};

unordered_map<wchar_t, Parent> maps;
unordered_set<wchar_t> invalid_character = {
L'.', L',', L'!', L'@', L'#', L'$', L'%', L'^',
L'&', L'*', L'(', L')', L'-', L'_', L'=', L'+',
L'<', L'>', L'/', L'"', L';', L':', L'，', L'。',
L'《', L'》', L'？', L'、', L'：', L'；', L'’', L'‘',
L'“', L'”', L'！', L'￥', L'…', L'）', L'（', L'—',
L'「', L'」',
L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',
L'a', L'b', L'c', L'd', L'e', L'f', L'g',
L'h', L'i', L'j', L'k', L'l', L'm', L'n',
L'o', L'p', L'q', L'r', L's', L't',
L'u', L'v', L'w', L'x', L'y', L'z',
L'A', L'B', L'C', L'D', L'E', L'F', L'G',
L'H', L'I', L'J', L'K', L'L', L'M', L'N',
L'O', L'P', L'Q', L'R', L'S', L'T',
L'U', L'V', L'W', L'X', L'Y', L'Z'
};
locale chn("chs");

int travelsal(string train_file) {
	wfstream fio(train_file);
	fio.imbue(chn);
	wstring input;
	while (fio >> input) {
		for (auto &ch : input)
			if (invalid_character.find(ch) != invalid_character.end())
				ch = L' ';
		for (int i = 1; i < input.size(); ++i) {
			if (input[i] == L' ' || input[i - 1] == L' ') continue; //跳过空格
			if (maps.find(input[i]) == maps.end())
				maps[input[i]].sum = 1;
			else
				maps[input[i]].sum++;
			wstringstream wsstemp; wsstemp << input[i - 1];
			wstring wstemp = wsstemp.str();
			Parent &par = maps[input[i]];
			if (par.key.find(wstemp) == par.key.end())
				par.key[wstemp] = 1;
			else
				par.key[wstemp]++;
		}
	}
	return 0;
}

int process(string inputfile) {
	wfstream fio(inputfile);
	fio.imbue(chn);
	wstringstream wss; wss << fio.rdbuf();
	wstring input = wss.str(), line;
	for (auto &ch : input)
		if (invalid_character.find(ch) != invalid_character.end())
			ch = L' ';
	wss.str(L"");
	wss << input;
	while (wss >> line) { //遍历句段
		wcout << line << endl;
		wstringstream wsstemp;
		vector<Per> stc;
		for (size_t i = 1; i < line.size(); ++i) {
			wsstemp.str(L"");
			wsstemp << line[i - 1];
			double son = maps[line[i]].key[wsstemp.str()];
			double mo = maps[line[i]].sum;
			stc.push_back({ i, son / mo });
		}
		//录入概率
		for (int i = 0; i < stc.size(); ++i)
			for (int j = i; j < stc.size(); ++j)
				if (stc[i].prob < stc[j].prob) {
					Per ptemp = stc[j];
					stc[j] = stc[i];
					stc[i] = ptemp;
				}
		//排序
	}
	return 0;
}

int twidec() {
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
	wstring input = L"吴御洲是南大计科最强的。";
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

int main() {
	wcin.imbue(chn); wcout.imbue(chn);
	string filename("sc.txt");
	travelsal(filename);
	process("test.txt");
	//twidec();
	return 0;
}
