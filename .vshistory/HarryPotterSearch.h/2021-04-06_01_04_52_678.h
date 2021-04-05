#pragma once
#ifndef HARRY_POTTER_SEARCH
#define HARRY_POTTER_SEARCH
#include <string>
auto info( )->void;
auto softwareInformation( )->void;
auto initial( )->void;
auto showMenu( )->void;
auto search( )->void;
auto showTitle( )->void;
auto showOutcome( ) -> void;
auto gotoRecord(int const &) -> void;
auto findChapter(int const &)->std::string;
auto findPage(int const &)->std::string;
auto strict = false;

namespace option{
	char exit[] = "exit";
	char search[] = "search";
	char Goto[] = "goto";
	char help[] = "help";
	inline char clear[] = "clear";
	inline char information[] = "info";
	inline char strictOn[] = "strictOn";
	inline char strictOff[] = "strictOff";
}
#endif
