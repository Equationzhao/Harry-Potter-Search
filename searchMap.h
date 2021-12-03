#pragma once
#ifndef _SEARCHMAP_
#define _SEARCHMAP_
#include <string>
#include <vector>

/**
 * \brief 查找器
 * 用于查找page和chapter
 */
class searchMap {
private:
    searchMap() : p_lastLine(0), c_lastLine(0){};
    std::vector<int> lpage_;
    std::vector<int> page_;
    std::vector<int> pchapter_;
    std::vector<std::string> chapter_;
    int p_lastLine;
    int c_lastLine;

public:
    static searchMap *mainSearcher;

    ~searchMap() {
        delete mainSearcher;
    }

    auto setPage(const int &pLine, const int &page) -> void {
        lpage_.emplace_back(pLine);
        page_.emplace_back(page);
    }

    auto setChapter(const int &pLine, const std::string &chapter) -> void {
        pchapter_.emplace_back(pLine);
        chapter_.emplace_back(chapter);
    }

    auto searchPage(const int &line) -> int {
        auto p_size = lpage_.size();
        for (auto i = p_lastLine; i < p_size; i++) {
            if (lpage_[i] > line) {
                p_lastLine = i;
                return page_[i];
            }
        }
        return 0;
    }

    auto searchChapter(const int &line) -> std::string {
        auto c_size = pchapter_.size();
        for (auto i = c_lastLine; i < c_size; i++) {
            if (pchapter_[i] > line) {
                c_lastLine = i;
                return chapter_[i];
            }
        }
        return chapter_.back();
    }

    auto operator=(const searchMap &rhs) -> searchMap & {
        lpage_ = rhs.lpage_;
        chapter_ = rhs.chapter_;
        pchapter_ = rhs.pchapter_;
        page_ = rhs.page_;
        return *this;
    }

    auto cpy(const searchMap &rhs) -> void {
        lpage_ = rhs.lpage_;
        chapter_ = rhs.chapter_;
        pchapter_ = rhs.pchapter_;
        page_ = rhs.page_;
    }

    auto initial() -> void {
        c_lastLine = 0;
        p_lastLine = 0;
    }
};

#endif
