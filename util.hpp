#ifndef UTIL_HPP
#define UTIL_HPP

#include "base.hpp"

namespace GenEx {
    namespace Util {
        /** \brief Splits a string based on a delimiter.
         *
         * \param std::string <u>s</u>: The string to split
         * \param std::string <u><i>delimiter</i></u>: The delimiter; defaults to " "
         * \return std::vector<std::string> Vector of substrings
         *
         */
        std::vector<std::string> SplitString(std::string s, std::string delimiter = " ") {
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

        /** \brief Joins a vector of strings together into one.
         *
         * \param std::vector<std::string> <u>strings</u>: Vector of strings to join together
         * \param std::string <u><i>sep</i></u> = "": Optional string to separate the strings
         *        that are joined together
         * \param std::string <u><i>beg</i></u> = "": Optional string to put in front of the
         *        finished joined string
         * \param std::string <u><i>end</i></u> = "": Optional string to put at the end of the
         *        finished joined string
         * \return std::string A string representing the conjoined string in the form of
         *        <i>{beg} + {strings[0]} + {sep} + {strings[1]} + {sep} + ... + {strings[n]} +
         *        {end}</i>
         *
         */
        std::string JoinString(std::vector<std::string> strings, std::string sep = "", std::string beg = "", std::string end = "") {
            std::stringstream sst;
            sst << beg;
            for (auto iter = strings.begin(); iter != strings.end(); iter++) {
                sst << *iter;
                if (iter < strings.end() - 1) sst << sep;
            }
            sst << end;
            return sst.str();
        }

        /** \brief Tokenizes a string by spaces; keeps items surrounded in quotes together.
         *
         * \param std::string <u>s</u>: The string you want to tokenize
         * \return std::vector<std::string> A vector of substrings
         *
         */
        std::vector<std::string> Tokenize(std::string s) {
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

// --- REGEX-RELATED FUNCTIONS --------------------------------------------------------------------

        /** \brief Splits a string based on a regular expression (regex).
         *
         * \param std::string <u>s</u>: The string to split
         * \param std::string <u>regex</u>: The regex to split on; defaults to "\\s+"
         * \return std::vector<std::string> Vector of substrings
         *
         */
        std::vector<std::string> RegexSplit(std::string s, std::string regex = "\\s+") {
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

        /** \brief Replaces a regular expression (regex) in a string with another regex.
         *
         * \param std::string <u>s</u>: A string
         * \param std::string <u>find</u>: The regex to find
         * \param std::string <u>replace</u>: The string to replace <i>find</i> with
         * \return std::string String in which all occurences of <i>find</i> are replaced with
         *         <i>replace</i>
         *
         */
        std::string RegexReplace(std::string s, std::string find, std::string replace) {
            return std::regex_replace(s, std::regex(find), replace);
        }

// --- MAP-RELATED FUNCTIONS ----------------------------------------------------------------------

        /** \brief Finds which keys in a map refer to a specific value.
         *
         * \param std::vector<K> &<u>vec</u>: Reference to vector to deposit keys into
         * \param std::unordered_map<K,V> &<u>elem_map</u>: The map to search
         * \param V <u>value</u>: The value to search for
         * \param bool TRUE if the value is in the map
         *
         */
        template <typename K, typename V>
        bool FindByValue(std::vector<K> &vec, std::unordered_map<K, V> &elem_map, V value) {
            bool result = false;

            for (auto iter = elem_map.begin(); iter != elem_map.end(); iter++) {
                if (iter->second == value) {
                    result = true;
                    vec.push_back(iter->first);
                }
            }
            return result;
        }

        /** \brief Finds whether a value appears in a map.
         *
         * \param std::vector<K> &<u>vec</u>: Reference to vector to deposit keys into
         * \param std::unordered_map<K,V> &<u>elem_map</u>: The map to search
         * \param V <u>value</u>: The value to search for
         * \param bool TRUE if the value is in the map
         *
         */
        template <typename K, typename V>
        bool FindByValue(std::nullptr_t vec, std::unordered_map<K, V> &elem_map, V value) {
            for (auto iter = elem_map.begin(); iter != elem_map.end(); iter++) {
                if (iter->second == value) {
                    return true;
                }
            }
            return false;
        }
    }
}

#endif // UTIL_HPP
