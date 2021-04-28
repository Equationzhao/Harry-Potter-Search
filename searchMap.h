#pragma once
#ifndef _SEARCHMAP_
#define _SEARCHMAP_
#include <string>
#include <vector>

/**
 * \brief 查找器
 * 用于查找page和chapter
 */
class searchMap
{
private:
	searchMap() = default;

	std::vector<int> lpage_;
	std::vector<int> page_;
	std::vector<int> pchapter_;
	std::vector<std::string> chapter_;
public:
	static searchMap* mainSearcher;

	~searchMap()
	{
		delete mainSearcher;
	}

	auto setPage( const int pLine, const int page )
	{
		lpage_.emplace_back(pLine);
		page_.emplace_back(page);
	}

	auto setChapter( const int pLine, const std::string chapter )
	{
		pchapter_.emplace_back(pLine);
		chapter_.emplace_back(chapter);
	}

	auto searchPage( const int line )
	{
		for (auto i = 0; lpage_[i] != *lpage_.end(); i++)
		{
			if (lpage_[i] > line)
			{
				return page_[i];
			}
		}
		return 0;
	}

	auto searchChapter( const int line )
	{
		for (auto i = 0; pchapter_[i] != *pchapter_.end(); i++)
		{
			if (pchapter_[i] > line)
			{
				return chapter_[i];
			}
		}
		return chapter_.back();
	}
};
#endif
