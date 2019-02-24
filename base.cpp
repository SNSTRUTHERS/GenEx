/**
 * \file base.cpp
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
 * The base source file for initialization and importing supplementary libraries.
 *
 */

#include "base.hpp"

bool GenEx::Init() {
    bool flag = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    if (TTF_Init() < 0)
        flag = false;

    int imgflags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
    if (!(IMG_Init(imgflags) & imgflags))
        flag = false;


    WORKING_DIR = SDL_GetBasePath();

    if (!flag) {
        TTF_Quit();
        IMG_Quit();
    }

    // Register GenEx-related user events
    GENEX_CREATEWINDOWEVENT = SDL_RegisterEvents(1);

    return flag;
}

void GenEx::SetWorkingDir(std::string dir) { GenEx::WORKING_DIR = dir;  }
std::string         GenEx::GetWorkingDir() { return GenEx::WORKING_DIR; }
