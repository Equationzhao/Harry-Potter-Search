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
#include <ctime>
#include <Windows.h>
using namespace std;

class item;
char strFind[100];
/**
 * brief line的size
 */
int lineNo = 0;
/**
 * brief 用于储存file中每行的字符串
 */
vector<string> line(50000);
/**
 * brief 用于存储每条记录的索引
 */
vector<item> index;

namespace option{
	char exit[] = "exit";
	char search[] = "search";
	char Goto[] = "goto";
	char help[] = "help";
	char clear[] = "clear";
	char information[] = "info";
	char strictOn[] = "strictOn";
	char strictOff[] = "strictOff";
}

auto info( )->void;
auto softwareInformation( )->void;
auto initial( )->void;
auto showMenu( )->void;
auto search( )->void;
auto showTitle( )->void;
auto showOutcome( ) -> void;
auto gotoRecord(int const &) -> void;
auto findChapter(int const &)->string;
auto findPage(int const &)->string;
auto strict = false;

class item{
public:
	item(int const &pLine,string const &pChapter,string const &pPage)
		: line_(pLine),page_(pPage),
		chapter_(pChapter){
		idGenerator_++;
		id_ = idGenerator_;
		if (line_ == -1){
			found_ = false;
		}
		else{
			found_ = true;
			if (0 <= line_ && line_ < 78){
				book_ = "J.K.Rowling - HP 0 - Harry Potter Prequel";
			}
			else if (78 <= line_ && line_ < 9810){
				book_ = "HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7";
			}
			else if (9810 <= line_ && line_ < 19814){
				book_ = "J.K.Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban";
			}
			else if (19814 <= line_ && line_ < 24162){
				book_ = "HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2";
			}
			else if (24162 <= line_ && line_ < 24867){
				book_ = "J.K.Rowling - Quidditch Through the Ages";
			}
			else if (24867 <= line_ && line_ < 26004){
				book_ = "J.K.Rowling - The Tales of Beedle the Bard";
			}
			else if (26004 <= line_ && line_ < 39616){
				book_ = "J.K.Rowling - HP 6 - Harry Potter and the Half - Blood Prince";
			}

			else if (39616 <= line_ && line_ < 49447){
				book_ = "J.K.Rowling - HP 4 - Harry Potter and the Goblet of Fire";
			}
		}
	}

	~item( )
		= default;

	void setPage(string const &p_page){
		page_ = p_page;
	}

	void setChapter(string const &pChapter){
		chapter_ = pChapter;
	}

	void set_line(int const &l){
		line_ = l;
	}

	static void set_name(string const &p_name){
		name_ = p_name;
	}

	[[nodiscard]] int get_line( ) const{
		return line_;
	}

	[[nodiscard]] string get_paper( ) const{
		return page_;
	}

	[[nodiscard]] string get_chapter( ) const{
		return chapter_;
	}

	[[nodiscard]] string getBook( ) const{
		return book_;
	}

	static string getName( ){
		return name_;
	}

	static bool getFound( ){
		return found_;
	}

	void output( ) const{
		cout << left << id_ << "\t" << name_ << "\t\t" << page_ << "\t" << setw(15) << chapter_ << "   \t" << book_ << endl;
	}

	static void reset( ){
		idGenerator_ = 0;
		name_ = "";
	}

private:
	int id_;
	int line_;
	string page_;
	string chapter_;
	string book_;
	static bool found_;
	static int idGenerator_;
	static string name_;
};

bool item::found_ = false;
int item::idGenerator_ = 0;
string item::name_ = "unknown";

auto info( ) -> void{
	cout << "哈利波特书籍检索系统v1.0.1\n";
}

auto softwareInformation( ) -> void{
	cout << "* Copyright (c) EquationZhao All Rights Reserved.\n"
		<< "* 版本号： V1.0.1\n"
		<< "* 创建人： EquationZhao\n"
		<< "* 电子邮箱：equationzhao@foxmail.com\n"
		<< "* 创建时间：20210331\n"
		<< "* 描述：USTB程序设计实践Ⅰ作业\n";
}

auto showInfo( ) -> void{
	cout << "输入\"search NAME\",查询为\"NAME\"的人名/地名\n输入\"goto N\",查询第N条记录\n输入\"exit\"退出查询系统\n"
		<< "使用clear命令清除屏幕上的内容\n使用help命令以显示此提示\n使用info命令显示软件相关信息\n使用strictOn/strictOff命令启用/关闭严格模式\n\n";
}

auto showRemind( ) -> void{
	cout << "注意:\n\t1.请不要在没有查询过时使用goto,会造成错误\n\t2.本软件对空格敏感,例如\"Harry Potter\"与\"Harry   Potter \"是不同的\n"
		<< "\t3.本软件默认关闭严格搜索模式,在检索人名/地名时影响较小,但在检索其他字符串时可能存在误差\n\t  若要启用/关闭严格模式,请使用strictOn/strictOff命令\n";
}

auto initial( ) -> void{
	auto *const file = new ifstream[8];
	file[0].open("./textSource/hp1.txt",std::ifstream::in);
	file[1].open("./textSource/hp2.txt",std::ifstream::in);
	file[2].open("./textSource/hp3.txt",std::ifstream::in);
	file[3].open("./textSource/hp4.txt",std::ifstream::in);
	file[4].open("./textSource/hp5.txt",std::ifstream::in);
	file[5].open("./textSource/hp6.txt",std::ifstream::in);
	file[6].open("./textSource/hp7.txt",std::ifstream::in);
	file[7].open("./textSource/hp8.txt",std::ifstream::in);
	auto i = 0;
	while (true){
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
}

auto search( ) -> void{
	const auto len = strlen(strFind);
	const auto start = clock( );
	for (auto n = 0; n < lineNo; n++){
		for (auto j = 0; j < line[n].size( ); j++){
			if (strFind[0] == line[n][j]){
				int flag = true;
				for (auto k = 1; k < len; k++){
					if (strFind[k] != line[n][k + j]){
						flag = false;
						break;
					}
				}
				if (flag){
					if (!strict){
						j += len;
					}
					item newItem(n,findChapter(n),findPage(n));
					index.push_back(newItem);
				}
			}
		}
	}
	const auto end = clock( );
	showOutcome( );
	cout << "查询用时" << static_cast<double>( end - start ) / 1000 << "秒" << endl;
}

auto findChapter(int const &L) -> string{
	//chapter表示章节,且一行的字符数均小于25
	const regex pattern("chapter",regex::icase);
	for (auto i = L; i >= 0; i--){
		if (line[i].size( ) >= 25){
			continue;
		}
		const string::const_iterator strB = line[i].begin( );
		const string::const_iterator strE = line[i].end( );
		if (regex_search(strB,strE,pattern)){
			return line[i];
		}
	}
	return "unknown";
}

auto findPage(int const &L) -> string{
	//数字表示页码,且一行的字符数均小于等于3
	for (auto i = L; i < lineNo; i++){
		if (line[i].size( ) >= 4){
			continue;
		}
		if (isdigit(line[i][0])){
			return line[i];
		}
	}
	return "unknown";
}

auto gotoRecord(int const &n) -> void{
	if (n > index.size( ) || n == 0){
		cout << "No existed record! :-(\n";
		return;
	}
	cout << "第" << n << "条记录" << endl;
	const auto temp_line = index[n - 1].get_line( );
	if (temp_line == 0){
		cout << line[0] << endl << line[2] << endl << line[4] << endl;
	}
	else if (temp_line == line.size( ) - 1){
		cout << line[temp_line - 4] << endl << line[temp_line - 2] << endl << line[temp_line] << endl;
	}
	else{
		cout << line[temp_line - 2] << endl << line[temp_line] << endl << line[temp_line + 2] << endl;
	}
}

auto showTitle( ) -> void{
	cout << left << "序号" << "\t" << "人名/地名" << "\t\t" << "页码" << "\t"
		<< setw(20) << "章节" << "   \t" << "书名" << endl;
}

auto showOutcome( ) -> void{
	system("cls");
	info( );
	if (!item::getFound( )){
		cout << "没有查询到~~" << endl;
		return;
	}
	showTitle( );
	for (auto &i : index){
		i.output( );
	}
	cout << "共查询到" << index.size( ) << "条记录" << endl;
}

auto showMenu( ) -> void{
	auto flag = true;
	while (true){
		char option[100];
		cin >> option;
		cin.ignore( ); //For cin.getline() will recive '\n'
		if (!strcmp(option,option::search)){
			index.clear( );
			item::reset( );
			cin.getline(strFind,100);
			item::set_name(strFind);
			flag = false;
			search( );
		}
		else if (!strcmp(option,option::Goto)){
			if (flag){
				cout << "No existed record! :-(\n";
				cin.ignore( );
				continue;
			}
			char char_num[10];
			cin >> char_num;
			auto n = 0;
			auto flag1 = false;
			const auto len_char = strlen(char_num);
			for (auto i = 0; i < len_char; i++){
				if (isdigit(char_num[i])){
					n *= 10;
					n += char_num[i] - '0';
					flag1 = true;
				}
				else{
					flag1 = false;
					break;
				}
			}
			if (flag1){
				gotoRecord(n); //跳转到第n条记录
			}
			else{
				cout << "NaN\nPlease input a valid NUMBER!\n";
			}
		}
		else if (!strcmp(option,option::exit)){
			return;
		}
		else if (!strcmp(option,option::clear)){
			system("cls");
		}
		else if (!strcmp(option,option::information)){
			softwareInformation( );
		}
		else if (!strcmp(option,option::help)){
			showInfo( );
		}
		else if (!strcmp(option,option::strictOn)){
			if (strict){
				cout << "strict mode is already on!\n";
			}
			else{
				cout << "strict mode on\n";
				strict = true;
			}
		}
		else if (!strcmp(option,option::strictOff)){
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
	info( ); //显示基本软件名称
	showInfo( ); //显示基本操作
	showRemind( ); //显示注意事项
	initial( ); //初始接受文件信息并存于vector<string>中
	showMenu( ); //显示操作
	softwareInformation( );
	cout << "\nEND\n";
	return 0;
}
