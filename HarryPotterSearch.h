#pragma once
#ifndef _HARRY_POTTER_SEARCH_
#define _HARRY_POTTER_SEARCH_
#include <string>
#include <regex>
inline auto info() -> void;
inline auto softwareInformation() -> void;
auto initial() -> void;
auto showMenu() -> void;
auto gotoSearch() -> void;
auto search() -> void;
auto showTitle() -> void;
auto showOutcome() -> void;
auto checkNum(const char charNum[], int& n) -> bool;
auto gotoRecord(const int&) -> void;
auto isDigit(const std::string& str) -> bool;
auto strict = false;

auto isDigit(const std::string& str) -> bool
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

class isChapterClass
{
public:
	auto operator()(const std::string& i)->bool
	{
		if (i.size() >= 25)
		{
			return false;
		}
		const std::regex pattern("chapter", std::regex::icase);
		return std::regex_search(i.begin(), i.end(), pattern);
	}
};

class isPageClass
{
public:
	auto operator()(const std::string& i) -> bool
	{
		return !i.empty() && i.size() < 4 && isdigit(i.at(0));
	}
};

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
