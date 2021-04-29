#pragma once
#ifndef _HARRY_POTTER_SEARCH_
#define _HARRY_POTTER_SEARCH_
#include <string>
auto info() -> void;
auto softwareInformation() -> void;
auto isChapter( const std::string& i ) -> bool;
auto isPage( const std::string& i ) -> bool;
auto initial() -> void;
auto showMenu() -> void;
auto gotoSearch() -> void;
auto search() -> void;
auto showTitle() -> void;
auto showOutcome() -> void;
auto checkNum( const char charNum[], int& n ) -> bool;
auto gotoRecord( const int& ) -> void;
auto isDigit( const std::string& str ) -> bool;
auto strict = false;

inline auto isDigit( const std::string& str ) -> bool
{
	auto flag(true);
	for (auto& i : str)
	{
		if (!isdigit(i))
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
