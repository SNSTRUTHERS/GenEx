/**
 * \file util.hpp
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
 * The header file for GenEx utility functions.
 *
 */

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
        std::vector<std::string> SplitString(std::string s, std::string delimiter);

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
        std::string JoinString(std::vector<std::string> strings, std::string sep,
                               std::string beg, std::string end);

        /** \brief Tokenizes a string by spaces; keeps items surrounded in quotes together.
         *
         * \param std::string <u>s</u>: The string you want to tokenize
         * \return std::vector<std::string> A vector of substrings
         *
         */
        std::vector<std::string> Tokenize(std::string s);

// --- REGEX-RELATED FUNCTIONS --------------------------------------------------------------------

        /** \brief Splits a string based on a regular expression (regex).
         *
         * \param std::string <u>s</u>: The string to split
         * \param std::string <u>regex</u>: The regex to split on; defaults to "\\s+"
         * \return std::vector<std::string> Vector of substrings
         *
         */
        std::vector<std::string> RegexSplit(std::string s, std::string regex);

        /** \brief Replaces a regular expression (regex) in a string with another regex.
         *
         * \param std::string <u>s</u>: A string
         * \param std::string <u>find</u>: The regex to find
         * \param std::string <u>replace</u>: The string to replace <i>find</i> with
         * \return std::string String in which all occurences of <i>find</i> are replaced with
         *         <i>replace</i>
         *
         */
        std::string RegexReplace(std::string s, std::string find, std::string replace);

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
