/*
*Copyright (c) equationzhao All Rights Reserved.
*?汾??? V1.0.0
*??????? equationzhao
*????????equationzhao@foxmail.com
*???????2021.3.31
*??????USTB???????????????
*Private Repository:https://github.com/Equationzhao/Harry-Potter-Search
*/

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <regex>
#include <time.h>
#include <Windows.h>
using namespace std;

ifstream file[8];
class item;
char strFind[100];
int lineNo = 0;
vector<string> line(50000);
vector<item> Index;

char Exit[] = "exit";
char Search[] = "search";
char Goto[] = "goto";
char Help[] = ".help";
char Clear[] = ".clear";
char information[] = ".info";

void info( );
void Softwareinformation( );
void initial( );
void showMenu( );
void search( );
void showTitle( );
void showOutcome( );
void GotoRecord(int const &);
string findChapter(int const &);
string findPage(int const &);

class item{
public:
	item(int const pLine,string const pChapter,string const pPage) :line(pLine),chapter(pChapter),page(pPage){
		idGenerator++;
		id = idGenerator;
		if (line == -1){
			found = false;
		}
		else{
			found = true;
			if (0 <= line && line < 78){
				book = "J.K.Rowling - HP 0 - Harry Potter Prequel";
			}
			else if (78 <= line && line < 9810){
				book = "HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7";
			}
			else if (9810 <= line && line < 19814){
				book = "J.K.Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban";
			}
			else if (19814 <= line && line < 24162){
				book = "HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2";
			}
			else if (24162 <= line && line < 24867){
				book = "J.K.Rowling - Quidditch Through the Ages";
			}
			else if (24867 <= line && line < 26004){
				book = "J.K.Rowling - The Tales of Beedle the Bard";
			}
			else if (26004 <= line && line < 39616){
				book = "J.K.Rowling - HP 6 - Harry Potter and the Half - Blood Prince";
			}

			else if (39616 <= line && line < 49447){
				book = "J.K.Rowling - HP 4 - Harry Potter and the Goblet of Fire";
			}
		}
	}
	~item( ){
	}
	void setPage(string const pPage){
		page = pPage;
	}
	void setChapter(string const pChapter){
		chapter = pChapter;
	}
	void setLine(int const &L){
		line = L;
	}
	static void setName(string const pName){
		name = pName;
	}
	int getLine( ){
		return line;
	}
	string getPaper( ) const{
		return page;
	}
	string getChapter( ) const{
		return chapter;
	}
	string getBook( ){
		return book;
	}
	static string getName( ){
		return name;
	}
	static bool getFound( ){
		return found;
	}
	void output( )const{
		cout << left << id << "\t" << name << "\t\t" << page << "\t" << setw(15) << chapter << "   \t" << book << endl;
	}
	static void reset( ){
		idGenerator = 0;
		name = "";
	}
private:

	int id;
	int line;
	string page;
	string chapter;
	string book;
	static bool found;
	static int idGenerator;
	static string name;
};

bool item::found = false;
int item::idGenerator = 0;
string item::name = "unknown";

void info( ){
	cout << "?????????鼮??????v1.0.0\n";
}
void Softwareinformation( ){
	cout << "* Copyright (c) equationzhao All Rights Reserved.\n"
		<< "* ?汾??? V1.0.0\n"
		<< "* ??????? equationzhao\n"
		<< "* ????????equationzhao@foxmail.com\n"
		<< "* ???????20210331\n"
		<< "* ??????USTB???????????????\n";
}
void showInfo( ){
	cout << "????\"search NAME\",????\"NAME\"??????/????\n????\"goto N\",?????N?????\n????\"exit\"????????\n"
		<< "???.clear?????????????????\n???.help??????????????\n???.info?????????????????\n\n";
}
void showRemind( ){
	cout << "???:\n\t1.???????в????????goto,????????\n\t2.??????????????,????\"Harry Potter\"??\"Harry   Potter \"??????\n";
}
void initial( ){
	file[0].open("./textSource/hp1.txt",std::ifstream::in);
	file[1].open("./textSource/hp2.txt",std::ifstream::in);
	file[2].open("./textSource/hp3.txt",std::ifstream::in);
	file[3].open("./textSource/hp4.txt",std::ifstream::in);
	file[4].open("./textSource/hp5.txt",std::ifstream::in);
	file[5].open("./textSource/hp6.txt",std::ifstream::in);
	file[6].open("./textSource/hp7.txt",std::ifstream::in);
	file[7].open("./textSource/hp8.txt",std::ifstream::in);
	int i = 0;
	while (1){
		while (getline(file[i],line[lineNo])){
			//cout << line[lineNo] << endl;
			lineNo++;
		}
		file[i].close( );
		i++;
		if (i == 8){
			break;
		}
	}
}

void search( ){
	int len = strlen(strFind);
	clock_t start,end;
	start = clock( );
	int num = 0;
	for (int n = 0; n < lineNo; n++){
		for (int j = 0; j < line[n].size( ); j++){
			if (strFind[0] == line[n][j]){
				int flage = true;
				for (int k = 1; k < len; k++){
					if (strFind[k] != line[n][j + k]){
						flage = false;
						break;
						j += k;
					}
				}
				if (flage){
					//cout << line[n] << endl;
					num++;
					j += len;
					item newItem(n,findChapter(n),findPage(n));
					Index.push_back(newItem);
				}
			}
		}
	}
	if (!num){
		Index.emplace_back(-1,"none","none");
	}
	end = clock( );
	showOutcome( );
	cout << "??????" << (double)( end - start ) / 1000 << "??" << endl;
}

string findChapter(int const &L){
	//chapter??????,????е????????С??25
	regex pattern("chapter",regex::icase);
	for (int i = L; i >= 0; i--){
		if (line[i].size( ) >= 25){
			continue;
		}
		string::const_iterator strB = line[i].begin( );
		string::const_iterator strE = line[i].end( );
		if (regex_search(strB,strE,pattern)){
			return line[i];
		}
	}
	return "unknown";
}

string findPage(int const &L){
	//?????????,????е????????С?????3
	for (int i = L; i < line.size( ); i++){
		if (line[i].size( ) >= 4){
			continue;
		}
		for (int j = 0; j < line[i].size( ); j++){
			if (isdigit(line[i][j])){
				return line[i];
			}
		}
	}
	return "unknown";
}

void GotoRecord(int const &n){
	if (n > Index.size( ) || n == 0){
		cout << "No existed record! :-(\n";
		return;
	}
	else{
		cout << "??" << n << "?????" << endl;
		int tempLine = Index[n - 1].getLine( );
		if (tempLine == 0){
			cout << line[0] << endl << line[2] << endl << line[4] << endl;
		}
		else if (tempLine == line.size( ) - 1){
			cout << line[tempLine - 4] << endl << line[tempLine - 2] << endl << line[tempLine] << endl;
		}
		else{
			cout << line[tempLine - 2] << endl << line[tempLine] << endl << line[tempLine + 2] << endl;
		}
	}
}

void showTitle( ){
	cout << left << "???" << "\t" << "????/????" << "\t\t" << "???" << "\t" << setw(20) << "???" << "   \t" << "????" << endl;
	return;
}

void showOutcome( ){
	system("cls");
	info( );
	if (!item::getFound( )){
		cout << "??в????~~" << endl;
		return;
	}
	showTitle( );
	for (int i = 0; i < Index.size( ); i++){
		Index[i].output( );
	}
	cout << "???????" << Index.size( ) << "?????" << endl;
	return;
}

void showMenu( ){
	bool flage = true;
	while (1){
		char option[10];
		cin >> option;
		cin.ignore( );//For cin.getline() will recive '\n'
		if (!strcmp(option,Exit)){
			return;
		}
		else if (!strcmp(option,Clear)){
			system("cls");
		}
		else if (!strcmp(option,information)){
			Softwareinformation( );
		}
		else if (!strcmp(option,Help)){
			showInfo( );
		}
		else if (!strcmp(option,Search)){
			Index.clear( );
			item::reset( );
			cin.getline(strFind,100);
			item::setName(strFind);
			flage = false;
			search( );
		}
		else if (!strcmp(option,Goto)){
			if (flage){
				cout << "No existed record! :-(\n";
				cin.ignore( );
				continue;
			}
			char charNum[10];
			cin >> charNum;
			int flage = false;
			int n = 0;
			for (int i = 0; i < strlen(charNum); i++){
				if (isdigit(charNum[i])){
					n *= 10;
					n += charNum[i] - '0';
					flage = true;
				}
				else{
					flage = false;
					break;
				}
			}
			if (flage){
				GotoRecord(n);//???????n?????
			}
			else{
				cout << "NaN\nPlease input a NUMBER!\n";
			}
		}
		else{
			cout << "\nError\nType in .help to get more information\n";
		}
	}
}

int main( ){
	SetConsoleTitle(L"?????????鼮??????");
	info( );//???????????????
	showInfo( );//???????????
	showRemind( );//??????????
	initial( );//???????????????????vector<string>??
	showMenu( );//???????
	cout << "\nEND\n";
	return 0;
}