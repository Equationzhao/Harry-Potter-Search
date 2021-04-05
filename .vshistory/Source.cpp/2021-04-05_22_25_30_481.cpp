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
char str_find[100];
/**
 * brief line的size
 */
int line_no = 0;
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
	char strict_on[] = "strictOn";
	char strict_off[] = "strictOff";
}
bool strict = false;

auto info( )->void;
auto software_information( )->void;
auto initial( )->void;
auto show_menu( )->void;
auto search( )->void;
auto show_title( )->void;
auto show_outcome( ) -> void;
auto goto_record(int const &) -> void;
auto find_chapter(int const &)->string;
auto find_page(int const &)->string;

class item{
public:
	item(int const &p_line,string const &p_chapter,string const &p_page)
		: line_(p_line),page_(p_page),
		chapter_(p_chapter){
		id_generator_++;
		id_ = id_generator_;
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

	void set_page(string const &p_page){
		page_ = p_page;
	}

	void set_chapter(string const &p_chapter){
		chapter_ = p_chapter;
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

	[[nodiscard]] string get_book( ) const{
		return book_;
	}

	static string get_name( ){
		return name_;
	}

	static bool get_found( ){
		return found_;
	}

	void output( ) const{
		cout << left << id_ << "\t" << name_ << "\t\t" << page_ << "\t" << setw(15) << chapter_ << "   \t" << book_ << endl;
	}

	static void reset( ){
		id_generator_ = 0;
		name_ = "";
	}

private:
	int id_;
	int line_;
	string page_;
	string chapter_;
	string book_;

	static bool found_;
	static int id_generator_;
	static string name_;
};

bool item::found_ = false;
int item::id_generator_ = 0;
string item::name_ = "unknown";

auto info( ) -> void{
	cout << "哈利波特书籍检索系统v1.0.1\n";
}

auto software_information( ) -> void{
	cout << "* Copyright (c) EquationZhao All Rights Reserved.\n"
		<< "* 版本号： V1.0.1\n"
		<< "* 创建人： EquationZhao\n"
		<< "* 电子邮箱：equationzhao@foxmail.com\n"
		<< "* 创建时间：20210331\n"
		<< "* 描述：USTB程序设计实践Ⅰ作业\n";
}

auto show_info( ) -> void{
	cout << "输入\"search NAME\",查询为\"NAME\"的人名/地名\n输入\"goto N\",查询第N条记录\n输入\"exit\"退出查询系统\n"
		<< "使用clear命令清除屏幕上的内容\n使用help命令以显示此提示\n使用info命令显示软件相关信息\n使用strictOn/strictOff命令启用/关闭严格模式\n\n";
}

auto show_remind( ) -> void{
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
		while (getline(file[i],line[line_no])){
			//cout << line[lineNo] << endl;
			line_no++;
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
	const auto len = strlen(str_find);
	const auto start = clock( );
	for (auto n = 0; n < line_no; n++){
		for (auto j = 0; j < line[n].size( ); j++){
			if (str_find[0] == line[n][j]){
				int flag = true;
				for (auto k = 1; k < len; k++){
					if (str_find[k] != line[n][j + k]){
						flag = false;
						break;
					}
				}
				if (flag){
					if (!strict){
						j += len;
					}
					item newItem(n,find_chapter(n),find_page(n));
					index.push_back(newItem);
				}
			}
		}
	}
	const auto end = clock( );
	show_outcome( );
	cout << "查询用时" << static_cast<double>( end - start ) / 1000 << "秒" << endl;
}

auto find_chapter(int const &L) -> string{
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

auto find_page(int const &L) -> string{
	//数字表示页码,且一行的字符数均小于等于3
	for (auto i = L; i < line_no; i++){
		if (line[i].size( ) >= 4){
			continue;
		}
		if (isdigit(line[i][0])){
			return line[i];
		}
	}
	return "unknown";
}

auto goto_record(int const &n) -> void{
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

auto show_title( ) -> void{
	cout << left << "序号" << "\t" << "人名/地名" << "\t\t" << "页码" << "\t"
		<< setw(20) << "章节" << "   \t" << "书名" << endl;
}

auto show_outcome( ) -> void{
	system("cls");
	info( );
	if (!item::get_found( )){
		cout << "没有查询到~~" << endl;
		return;
	}
	show_title( );
	for (auto &i : index){
		i.output( );
	}
	cout << "共查询到" << index.size( ) << "条记录" << endl;
}

auto show_menu( ) -> void{
	auto flag = true;
	while (true){
		char option[100];
		cin >> option;
		cin.ignore( ); //For cin.getline() will recive '\n'
		if (!strcmp(option,option::search)){
			index.clear( );
			item::reset( );
			cin.getline(str_find,100);
			item::set_name(str_find);
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
				goto_record(n); //跳转到第n条记录
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
			software_information( );
		}
		else if (!strcmp(option,option::help)){
			show_info( );
		}
		else if (!strcmp(option,option::strict_on)){
			if (strict){
				cout << "strict mode is already on!\n";
			}
			else{
				cout << "strict mode on\n";
				strict = true;
			}
		}
		else if (!strcmp(option,option::strict_off)){
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
	show_info( ); //显示基本操作
	show_remind( ); //显示注意事项
	initial( ); //初始接受文件信息并存于vector<string>中
	show_menu( ); //显示操作
	software_information( );
	cout << "\nEND\n";
	return 0;
}
