/*
*Copyright (c) equationzhao All Rights Reserved.
*版本号： V1.0.1
*创建人： equationzhao
*电子邮箱：equationzhao@foxmail.com
*创建时间：2021.3.31
*描述：USTB程序设计实践Ⅰ作业
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

class item;
char strFind[20];
int lineNo = 0;
vector<string> line(50000);
vector<item> Index;

char Exit[] = "exit";
char Search[] = "search";
char Goto[] = "goto";
char Help[] = "help";
char Clear[] = "clear";
char information[] = "info";
char StrictOn[] = "strictOn";
char StrictOff[] = "strictOff";
bool strict = false;

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
	cout << "哈利波特书籍检索系统v1.0.0\n";
}
void Softwareinformation( ){
	cout << "* Copyright (c) equationzhao All Rights Reserved.\n"
		<< "* 版本号： V1.0.0\n"
		<< "* 创建人： equationzhao\n"
		<< "* 电子邮箱：equationzhao@foxmail.com\n"
		<< "* 创建时间：20210331\n"
		<< "* 描述：USTB程序设计实践Ⅰ作业\n";
}
void showInfo( ){
	cout << "输入\"search NAME\",查询为\"NAME\"的人名/地名\n输入\"goto N\",查询第N条记录\n输入\"exit\"退出查询系统\n"
		<< "使用clear命令清除屏幕上的内容\n使用help命令以显示此提示\n使用info命令显示软件相关信息\n使用strictOn/strictOff命令启用/关闭严格模式\n\n";
}
void showRemind( ){
	cout << "注意:\n\t1.请不要在没有查询过时使用goto,会造成错误\n\t2.本软件对空格敏感,例如\"Harry Potter\"与\"Harry   Potter \"是不同的\n"
		<< "\t3.本软件默认关闭严格搜索模式,在检索人名/地名时影响较小,但在检索其他字符串时可能存在误差\n\t  若要启用/关闭严格模式,请使用strictOn/strictOff命令\n";
}
void initial( ){
	ifstream *file = new ifstream[8];
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
	delete[]file;
	return;
}

void search( ){
	size_t len = strlen(strFind);
	clock_t start,end;
	start = clock( );
	for (int n = 0; n < lineNo; n++){
		for (int j = 0; j < line[n].size( ); j++){
			if (strFind[0] == line[n][j]){
				int flage = true;
				for (int k = 1; k < len; k++){
					if (strFind[k] != line[n][j + k]){
						flage = false;
						break;
					}
				}
				if (flage){
					if (!strict){
						j += len;
					}
					item newItem(n,findChapter(n),findPage(n));
					Index.push_back(newItem);
				}
			}
		}
	}
	end = clock( );
	showOutcome( );
	cout << "查询用时" << (double)( end - start ) / 1000 << "秒" << endl;
	return;
}

string findChapter(int const &L){
	//chapter表示章节,且一行的字符数均小于25
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
	//数字表示页码,且一行的字符数均小于等于3
	for (int i = L; i < line.size( ); i++){
		if (line[i].size( ) >= 4){
			continue;
		}
		if (isdigit(line[i][0])){
			return line[i];
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
		cout << "第" << n << "条记录" << endl;
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
	return;
}

void showTitle( ){
	cout << left << "序号" << "\t" << "人名/地名" << "\t\t" << "页码" << "\t"
		<< setw(20) << "章节" << "   \t" << "书名" << endl;
	return;
}

void showOutcome( ){
	system("cls");
	info( );
	if (!item::getFound( )){
		cout << "没有查询到~~" << endl;
		return;
	}
	showTitle( );
	for (int i = 0; i < Index.size( ); i++){
		Index[i].output( );
	}
	cout << "共查询到" << Index.size( ) << "条记录" << endl;
	return;
}
void showMenu( ){
	bool flage = true;
	while (1){
		char option[100];
		cin >> option;
		cin.ignore( );//For cin.getline() will recive '\n'
		if (!strcmp(option,Search)){
			Index.clear( );
			item::reset( );
			cin.getline(strFind,20);
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
			int n = 0;
			size_t flage = false,lenChar = strlen(charNum);
			for (int i = 0; i < lenChar; i++){
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
				GotoRecord(n);//跳转到第n条记录
			}
			else{
				cout << "NaN\nPlease input a valid NUMBER!\n";
			}
		}
		else if (!strcmp(option,Exit)){
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
		else if (!strcmp(option,StrictOn)){
			if (strict){
				cout << "strict mode is already on!\n";
			}
			else{
				cout << "strict mode on\n";
				strict = true;
			}
		}
		else if (!strcmp(option,StrictOff)){
			if (!strict){
				cout << "strict mode is already off!\n";
			}
			else{
				strict = false;
				cout << "strict mode off\n";
			}
		}
		else{
			cout << "\nError\nType in \'help\' to get more information\n";
		}
	}
}
int main( ){
	SetConsoleTitle(L"哈利波特书籍检索系统");
	info( );//显示基本软件名称
	showInfo( );//显示基本操作
	showRemind( );//显示注意事项
	initial( );//初始接受文件信息并存于vector<string>中
	showMenu( );//显示操作
	Softwareinformation( );
	cout << "\nEND\n";
	return 0;
}
