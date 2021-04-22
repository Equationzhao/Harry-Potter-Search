#pragma once
#ifndef _HARRY_POTTER_SEARCH_
#define _HARRY_POTTER_SEARCH_
#include <string>
auto info( )->void;
auto softwareInformation( )->void;
auto initial( )->void;
auto showMenu( )->void;
auto gotoSearch( ) -> void;
auto search( )->void;
auto showTitle( )->void;
auto showOutcome( ) -> void;
auto checkNum(char const charNum[],bool &flag1,int &n) -> void;
auto gotoRecord(int const &) -> void;
auto findChapter(int const &)->std::string;
auto findPage(int const &)->std::string;
auto isDigit(char const a[]) -> bool;
auto strict = false;

auto isDigit(char const str[]) -> bool

{
	auto flag(true);
	for (auto i = 0; i < strlen(str); i++)
	{
		if (!isdigit(str[i]))
		{
			flag = false;
			break;
		}
	}
	return flag;
}

namespace option
{
	char exit[] = "exit";
	char search[] = "search";
	char Goto[] = "goto";
	char help[] = "help";
	char clear[] = "clear";
	char information[] = "info";
	char strictOn[] = "strictOn";
	char strictOff[] = "strictOff";
}
#endif
