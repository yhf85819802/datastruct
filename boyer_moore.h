// @author yinhongfeng
// @email  754505518@qq.com
// @reference https://zh.wikipedia.org/wiki/Boyer-Moore%E5%AD%97%E7%AC%A6%E4%B8%B2%E6%90%9C%E7%B4%A2%E7%AE%97%E6%B3%95
// @reference http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
// @reference http://blog.jobbole.com/52830/ 


#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <string.h>
#include <algorithm>

namespace {

std::unordered_map<char, std::set<int>> gen_bad_match_hash(const std::string& pattern) {
    int size = pattern.size();
    std::unordered_map<char, std::set<int>> char_index_dict;

    for (int i = 0; i != size; ++i) {
        char c = pattern[i];
        char_index_dict[c].insert(i);
    }

    return char_index_dict;
}

std::vector<int> gen_good_match_array(const std::string& pattern) {
    int size = pattern.size();
    std::vector<int> good_match_array(size);
    std::unordered_map<char, int> char_index_dict;

    const char* p = pattern.data();

    for (int i = size - 1; i != 0; --i) {
        int len = size - i;
        const char* suffix = p + i;

        int j = i - 1;
        for (; j >= 0; --j) {
            const char* prefix = p + j;
            if (!strncmp(prefix, suffix, len)) {
                good_match_array[i] = suffix - prefix;
                break;
            }
        }

        if (j < 0) {
            if (i == size - 1) {
                good_match_array[i] = size;
            } else {
                good_match_array[i] = good_match_array[i + 1];
            }
        }
    }

    good_match_array[0] = 0;

    return good_match_array;
}

} // namespace

namespace boyer_moore {

// @return index if found match, -1 else
int find(const std::string& text, const std::string& pattern) {
    auto&& bad_match_hash = gen_bad_match_hash(pattern);
    auto&& good_match_array = gen_good_match_array(pattern);
    int pattern_size = pattern.size();
    int text_size = text.size();

    for (int i = 0; i <= text_size - pattern_size;) {
        int j = pattern_size - 1;
        for (; j >= 0 && pattern[j] == text[i + j]; --j);

        // In this state,it means all the chars are matched
        if (j < 0) {
            return i;
        }

        int bad_i_delta = 0;
        char c = text[i + j];
        auto it = bad_match_hash.find(c);
        if (it == bad_match_hash.end()) {
            bad_i_delta = j - (-1) ;
        } else {
            const auto& c_index_set = bad_match_hash[c];
            auto it_begin = c_index_set.begin();
            if (j < *it_begin) {
                bad_i_delta = j - (-1);
            } else {
                auto it = c_index_set.lower_bound(j);
                if (it == it_begin) {
                    bad_i_delta = j - (-1);
                } else {
                    bad_i_delta = j - *(--it);
                }
            }
        }
        
        int good_i_delta = -1;
        if (j != pattern_size - 1) {
            good_i_delta = good_match_array[j + 1];
        }

        i += std::max(bad_i_delta, good_i_delta);
    }

    return -1;
}

} // namespace boyer_moore 

#endif
