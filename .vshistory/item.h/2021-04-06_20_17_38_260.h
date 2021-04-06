#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#ifndef _ITEM_
#define _ITEM_

/**
 * brief item类存储搜索结果的信息
 */
class item{
public:
	auto setBookName(int lineNum) -> void	{
		if (lineNum_ == -1){
			found_ = false;
		}
		else{
			found_ = true;
			if (0 <= lineNum_ && lineNum_ < 78){
				book_ = "J.K.Rowling - HP 0 - Harry Potter Prequel";
			}
			else if (78 <= lineNum_ && lineNum_ < 9810){
				book_ = "HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7";
			}
			else if (9810 <= lineNum_ && lineNum_ < 19814){
				book_ = "J.K.Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban";
			}
			else if (19814 <= lineNum_ && lineNum_ < 24162){
				book_ = "HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2";
			}
			else if (24162 <= lineNum_ && lineNum_ < 24867){
				book_ = "J.K.Rowling - Quidditch Through the Ages";
			}
			else if (24867 <= lineNum_ && lineNum_ < 26004){
				book_ = "J.K.Rowling - The Tales of Beedle the Bard";
			}
			else if (26004 <= lineNum_ && lineNum_ < 39616){
				book_ = "J.K.Rowling - HP 6 - Harry Potter and the Half - Blood Prince";
			}

			else if (39616 <= lineNum_ && lineNum_ < 49447){
				book_ = "J.K.Rowling - HP 4 - Harry Potter and the Goblet of Fire";
			}
		}
	}

	item(int const &pLine,std::string pChapter,std::string pPage)
		: lineNum_(pLine),page_(std::move(pPage)),
		chapter_(std::move(pChapter)){
		idGenerator_++;
		id_ = idGenerator_;
		setBookName(lineNum_);
	}

	~item( )
		= default;

	void setPage(std::string const &pPage){
		page_ = pPage;
	}

	void setChapter(std::string const &pChapter){
		chapter_ = pChapter;
	}

	void setLine(int const &l){
		lineNum_ = l;
	}

	static void setName(std::string const &pName){
		name_ = pName;
	}

	[[nodiscard]] int getLineNum( ) const{
		return lineNum_;
	}

	[[nodiscard]] std::string getPaper( ) const{
		return page_;
	}

	[[nodiscard]] std::string getChapter( ) const{
		return chapter_;
	}

	[[nodiscard]] std::string getBook( ) const{
		return book_;
	}

	static std::string getName( ){
		return name_;
	}

	static bool getFound( ){
		return found_;
	}

	void output( ) const{
		std::cout << std::left << id_ << "\t" << name_ << "\t\t" << page_ << "\t" << std::setw(15) << chapter_ << "   \t" << book_ << std::endl;
	}

	static void reset( ){
		idGenerator_ = 0;
		name_ = "";
	}

private:
	int id_;
	int lineNum_;
	std::string page_;
	std::string chapter_;
	std::string book_;
	static bool found_;
	static int idGenerator_;
	static std::string name_;
};

bool item::found_ = false;
int item::idGenerator_ = 0;
std::string item::name_ = "unknown";

#endif
