/**
 * \file genex.h
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
 * The master include header for GenEx.
 *
 */

#include "base.hpp"     // The base header; imports SDL & C++ std libs; defines general purpose vars
#include "time.hpp"     // General-purpose timing functions & timer class
#include "util.hpp"     // General-purpose utility functions
#include "math.hpp"     // Math library
#include "debug.hpp"    // Debugging-related string printout functions
#include "events.hpp"   // Default event handlers
#include "object.hpp"   // Base object implementation
#include "graphics.hpp" // Graphics display library & primitives
