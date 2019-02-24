/**
 * \file base.hpp
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
 * The base header file for initialization and importing supplementary libraries
 *
 */

#ifndef BASE_HPP
#define BASE_HPP

// trim away all the shit from <windows.h> on _WIN32
#define WIN_32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <exception>
#include <chrono>
#include <algorithm>
#include <utility>
#include <initializer_list>
#include <unordered_set>
#include <unordered_map>
#include <exception>
#include <tuple>
#include <regex>
#include <memory>

#define SDL_main main
#include "SDL.h"
#include "SDL_syswm.h"
#include "SDL_image.h"
#include "SDL_vulkan.h"
#include "SDL_ttf.h"

#define absv(x) x > 0 ? x : -x

namespace GenEx {

// -- CREDIT & VERSION INFO CONSTANTS -------------------------------------------------------------

    static constexpr Uint8  VERSION_STATE = 0;
    static constexpr Uint32 VERSION_MAJOR = 0;
    static constexpr Uint32 VERSION_MINOR = 1;
    static constexpr Uint32 VERSION_PATCH = 0;
    static constexpr char EX_NAME[] = "General Executor"; // The program name

    /** \brief The names of those who have contributed to the development of GenEx
     */
    static constexpr char EX_CONT[] =
        "Simon NE Struthers, Morgan Dorval, Pat Struthers";

// -- BASE GENEX EXCEPTION CLASS ------------------------------------------------------------------

    /** \brief A base Error class for all Gen-Ex related exceptions
     */
    class Error : public std::exception {
    public:
        explicit Error(const char* message) : msg_(message) { }
        explicit Error(const std::string& message) : msg_(message) { }

        virtual ~Error() throw (){}

        virtual const char *what() const throw (){
            return msg_.c_str();
        }
    protected:
        std::string msg_;
    };

// -- WORKING DIRECTORY RELATED VARS & FUNCTIONS --------------------------------------------------

    /** \brief The current working directory
     */
    static std::string WORKING_DIR;

    /** \brief Resets the working directory to a new value.
     *
     * \param std::string <u>dir</u>: The new value for the working directory
     *
     */
    void SetWorkingDir(std::string dir);

    /** \brief Returns the current working directory.
     *
     * \return std::string Current working directory
     *
     */
    std::string GetWorkingDir();

// -- DEFAULT WINDOW INITIALIZATION FLAGS ---------------------------------------------------------

    /** \brief The default window flags when creating a new window
     */
    static const Uint32 DEFAULT_WINFLAGS = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;

    /** \brief The default renderer flags when creating a rendering context/target
     */
    static const Uint32 DEFAULT_RENFLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;

// -- GENEX USER EVENT TYPES ----------------------------------------------------------------------

    /** \brief The event ID for creating a GenEx window
     */
    static Uint32 GENEX_CREATEWINDOWEVENT;

// -- INITIALIZE GENEX ----------------------------------------------------------------------------

    /** \brief Initializes the General Executor and SDL
     */
    bool Init();

// -- GENEX OBJECT FORWARD DECLARATION ------------------------------------------------------------

    class Object;
}

#endif // BASE_HPP
