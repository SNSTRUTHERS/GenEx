/**
 * \file util.cpp
 *
 * \author Simon Struthers <snstruthers@gmail.com>
 * \version pre_dev v0.1.0
 *
 * \section LICENSE
 * GenEx (short for General Executor) - window manager and runtime environment.
 * Copyright (C) 2019 | The GenEx Project
 *
 * This file is part of GenEx.
 *
 * GenEx is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License version 2 as published by the Free Software Foundation.
 *
 * GenEx is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at https://www.gnu.org/copyleft/gpl.html
 *
 * You should have received a copy of the GNU General Public License version 2 along with GenEx.
 * If not, see http://www.gnu.org/licenses.
 *
 * \section DESCRIPTION
 * The source file for GenEx utility functions.
 *
 */

#include "util.hpp"

std::vector<std::string> GenEx::Util::SplitString(std::string s, std::string delimiter = " ") {
    std::vector<std::string> ls;
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        ls.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    ls.push_back(s);

    return ls;
}

std::string GenEx::Util::JoinString(std::vector<std::string> strings, std::string sep = "",
                                    std::string beg = "", std::string end = "") {
    std::stringstream sst;
    sst << beg;
    for (auto iter = strings.begin(); iter != strings.end(); iter++) {
        sst << *iter;
        if (iter < strings.end() - 1) sst << sep;
    }
    sst << end;
    return sst.str();
}

std::vector<std::string> GenEx::Util::Tokenize(std::string s) {
    std::vector<std::string> ls;
    size_t tokenbegin = 0;
    bool quotesflag = false;

    size_t index = 0;
    while (index < s.size()) {
        if (s[index] == '"') {
            quotesflag = !quotesflag;
        }
        else if (s[index] == ' ' && (!quotesflag)) {
            std::string subs = s.substr(tokenbegin, index - tokenbegin);
            subs.erase(std::remove(subs.begin(), subs.end(), '"'), subs.end());

            ls.push_back(subs);

            tokenbegin = index + 1;
        }
        index++;
    }
    std::string subs = s.substr(tokenbegin, index - tokenbegin);
    subs.erase(std::remove(subs.begin(), subs.end(), '"'), subs.end());
    ls.push_back(subs);

    return ls;
}

std::vector<std::string> GenEx::Util::RegexSplit(std::string s, std::string regex = "\\s+") {
    std::vector<std::string> elems;
    std::regex rgx(regex);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        elems.push_back(*iter);
        iter++;
    }

    return elems;
}

std::string GenEx::Util::RegexReplace(std::string s, std::string find, std::string replace) {
    return std::regex_replace(s, std::regex(find), replace);
}
