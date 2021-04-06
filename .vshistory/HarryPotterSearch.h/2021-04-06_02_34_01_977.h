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
inline auto strict = false;

namespace option{
	inline char exit[] = "exit";
	inline char search[] = "search";
	inline char Goto[] = "goto";
	inline char help[] = "help";
	inline char clear[] = "clear";
	inline char information[] = "info";
	inline char strictOn[] = "strictOn";
	inline char strictOff[] = "strictOff";
}
#endif
