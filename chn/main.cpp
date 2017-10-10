#include <set>
#include <unordered_set>
#include <functional>
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <locale>
#include <map>
#include <cmath>
#include <ctime>
using namespace std;

struct Parent {
	unordered_map<wstring, int> key;
	int sum;
};

struct Per {
	size_t loc;
	float prob;
};

unordered_map<wchar_t, Parent> maps;
unordered_set<wstring> wset;
unordered_set<wchar_t> invalid_character = {
L'.', L',', L'!', L'@', L'#', L'$', L'%', L'^',
L'&', L'*', L'(', L')', L'-', L'_', L'=', L'+',
L'<', L'>', L'/', L'"', L';', L':', L'，', L'。',
L'《', L'》', L'？', L'、', L'：', L'；', L'’', L'‘',
L'“', L'”', L'！', L'￥', L'…', L'）', L'（', L'—',
L'「', L'」', L'～',L'＝',
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
	fio.seekg(0, ios::end);
	streampos ps = fio.tellg();
	fio.seekg(0, ios::beg);
	time_t start = time(NULL);
	time_t end = time(NULL), temp = start;
	wstring input;
	float perc = 0;
	while (fio >> input) {
		streampos pstemp = fio.tellg();
		end = time(NULL);
		float perh = (float)pstemp / ps * 100;
		if (end - temp > 0 || perh - perc > 0.9999) {
			temp = end;
			perc = perh;
			cout << flush << '\r' << "[" << string((int)(perh * 4 / 5), '#') << string(80 - (int)(perh * 4 / 5), ' ') << "] " << pstemp << "/" << ps << "  " << setprecision(3) << perh << "%   " << end - start << "s   ";
		}
		for (auto &ch : input)
			if (invalid_character.find(ch) != invalid_character.end())
				ch = L' ';
		for (size_t i = 1; i < input.size(); ++i) {
			//双字符
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
			if (i >= 2) {
				//三字符
				if (input[i] == L' ' || input[i - 1] == L' ' || input[i - 2] == L' ') continue; //跳过空格
				if (maps.find(input[i]) == maps.end())
					maps[input[i]].sum = 1;
				else
					maps[input[i]].sum++;
				wstringstream wsstemp; wsstemp << input[i - 2] << input[i - 1];
				wstring wstemp = wsstemp.str();
				Parent &par = maps[input[i]];
				if (par.key.find(wstemp) == par.key.end())
					par.key[wstemp] = 1;
				else
					par.key[wstemp]++;
			}
			if (i >= 3) {
				if (input[i] == L' ' || input[i - 1] == L' ' || input[i - 2] == L' ' || input[i - 3] == L' ') continue; //跳过空格
				if (maps.find(input[i]) == maps.end())
					maps[input[i]].sum = 1;
				else
					maps[input[i]].sum++;
				wstringstream wsstemp; wsstemp << input[i - 3] << input[i - 2] << input[i - 1];
				wstring wstemp = wsstemp.str();
				Parent &par = maps[input[i]];
				if (par.key.find(wstemp) == par.key.end())
					par.key[wstemp] = 1;
				else
					par.key[wstemp]++;
			}
		}
	}
	fio.close();
	cout << flush << '\r' << "[" << string(80, '#') << "] " << ps << "/" << ps << "  100%   " << end - start << "s   ";
	cout << endl;
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
		wstringstream wsstemp;
		vector<Per> stc;
		unordered_set<size_t> slocs;
		unordered_set<size_t> sorder;
		for (size_t i = 1; i < line.size(); ++i) {
			wsstemp.str(L"");
			wsstemp << line[i - 1];
			float son = (float)maps[line[i]].key[wsstemp.str()];
			float mo = (float)maps[line[i]].sum;
			stc.push_back({ i, son == 0 ? 0 : son / mo * log(mo) });
		}
		//录入概率
		for (size_t i = 0; i < stc.size(); ++i)
			for (size_t j = i; j < stc.size(); ++j)
				if (stc[i].prob < stc[j].prob) {
					Per ptemp = stc[j];
					stc[j] = stc[i];
					stc[i] = ptemp;
				}
		//句中概率排序
		for (size_t i = 0; i < stc.size(); ++i)
			if (slocs.find(stc[i].loc) == slocs.end() && slocs.find(stc[i].loc - 1) == slocs.end()) {
				slocs.emplace(stc[i].loc);
				slocs.emplace(stc[i].loc - 1);
				sorder.emplace(stc[i].loc);
			}
		//句中短语排序
		for (size_t i = 0; i < line.size(); ++i) {
			if (sorder.find(i + 1) == sorder.end())
				wcout << line[i] << L" ";
			else {
				wcout << line[i] << line[i + 1] << L" ";
				++i;
			}
		}
	}
	cout << endl;
	return 0;
}

void readdic(string dicfilename) {
	wfstream fio;
	fio.imbue(chn);
	fio.open(dicfilename);
	wstring s;
	while (!fio.eof()) {
		fio >> s;
		wset.insert(s);
	}
}

int twidec(string dicfilename) {
	wcin.imbue(chn); wcout.imbue(chn);
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

void makeSum(string dicfilename) {
	//read maps
	unordered_set<wstring> cp;
	unordered_map<wstring, unsigned>sums;
	for (auto tree : maps) {
		for (auto item : tree.second.key) {
			wstringstream wss;
			wss << item.first << tree.first;
			sums[wss.str()] = item.second;
		}
	}
	typedef function<bool(pair<wstring, unsigned>, pair<wstring, unsigned>)> Comparator;
	Comparator comFunctor = [](pair<wstring, unsigned> elem1, pair<wstring, unsigned> elem2) {
		return elem1.second > elem2.second;
	};
	set<pair<wstring, unsigned>, Comparator> sumsSet(sums.begin(), sums.end(), comFunctor);
	for (auto item : sumsSet) {
		/*bool issm = false;
		for (auto cmp : sumsSet) {
			if(cmp.first != item.first && item.first.find(cmp.first) != item.first.npos)
				if (item.second > (double)cmp.second * 0.7) {
					issm = true;
					break;
				}
		}
		if (!issm)*/
		if(item.second > 20)
			cp.insert(item.first);
	}
	//cp.erase(L"");
	cp.erase(L"定的");
	cp.erase(L"是冤");
	wofstream fio(dicfilename, ios::app);
	fio.imbue(chn);
	for (auto item : cp)
		fio << item << endl;
	fio.close();
}

void writeMap(string filename) {
	wofstream fio(filename);
	fio.imbue(chn);
	for (auto item : maps) {
		fio << item.first << L" " << item.second.sum;
		for (auto piece : item.second.key) 
			fio << piece.first << L" " << piece.second << L" ";
		fio << endl;
	}
	fio.close();
}

void readMapFile(string filename) {
	wifstream fio(filename);
	fio.imbue(chn);
	while (!fio.eof()) {
		wchar_t ch; int sum;
		fio >> ch >> sum;
		maps[ch].sum = sum;
		wstring line;
		getline(fio, line);
		wstringstream wss; wss << line;
		wstring first; int second;
		while (wss >> first >> second) 
			maps[ch].key[first] = second;
	}
}

int main(int argc, char *argv[]) {
	wcin.imbue(chn); wcout.imbue(chn);
	string dicFile("dic.txt");
	readdic(dicFile);
	//travelsal(argv[1]);
	//writeMap("maps.txt");
	//readMapFile("maps.txt");
	//makeSum(dicFile);
	//process(argv[2]);
	//twidec("dic.txt");

	return 0;
}
