/**
 * \file time.hpp
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
 * The header file for GenEx timing-related functions.
 *
 */

#ifndef TIME_HPP
#define TIME_HPP

#include "base.hpp"

namespace GenEx {
    namespace Time {
        static const std::chrono::time_point<std::chrono::high_resolution_clock> START_TIME =
            std::chrono::high_resolution_clock::now();

        /** \brief Returns the current time in seconds with nanosecond accuracy if possible.
         *
         * \return double Current time in seconds
         */
        const double GetSecs();

        /** \brief Returns the time since GenEx was initialized with nanosecond accuracy
         *        if possible.
         *
         * \return double Current time in seconds
         */
        const double GetTime();
    }
}

#endif // TIME_HPP
