/**
 * \file debug.hpp
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
 * The header file for debugging functions for GenEx printouts.
 *
 */

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "base.hpp"

namespace GenEx {
    namespace Debug {
        /** \brief Returns a string representing the version of GenEx.
         *
         * \return std::string Version string
         *
         */
        std::string GetVersionString();

        /** \brief Gets a string representing the orientation of the display.
         *
         * \param Uint8 <u>orientation</u>: An enumeration value representing the orientation
         *        of the display
         * \return std::string String representation of <i>orientation</i>
         *
         */
        std::string GetDisplayOrientationString(Uint8 orientation);

        /** \brief Gets a string with all the information given in an SDL_DisplayEvent.
         *
         * \param SDL_DisplayEvent &<u>devent</u>: a display event
         * \return std::string String representation of <i>devent</i>
         *
         */
        std::string GetDisplayEventString(SDL_DisplayEvent &devent);

        /** \brief Gets a string version of a joystick hat value.
         *
         * \param Uint8 <u>jhatval</u>: An enumeration value representing the hat value of a
         *        joystick
         * \return std::string String representation of <i>jhatval</i>
         *
         */
        std::string GetHatValue(Uint8 jhatval);

        /** \brief Gets the string version of an SDL_WindowEvent event type.
         *
         * \param Uint8 <u>evt_type</u>: An enumeration value representing the event type of an
         *        SDL_WindowEvent
         * \return std::string String representation of <i>evt_type</i>
         *
         */
        std::string GetWindowEventString(Uint8 evt_type);

        /** \brief Returns a string representing the window management subsystem SDL is using
         *        from an <i>SDL_SYSWM_TYPE</i> enum entry.
         *
         * \param SDL_SYSWM_TYPE <u>type</u>: Constant representing a subsystem type.
         * \return std::string String representation of <i>type</i>.
         *
         */
        std::string GetSubsystemString(SDL_SYSWM_TYPE type);

        /** \brief Gets a string containing relevant information from an SDL_SysWMEvent.
         *
         * \param SDL_SysWMmsg *<u>msg</u>: A pointer to a system window management event message
         * \return std::string String representation of <i>msg</i>
         *
         */
        std::string GetSysWMEventString(SDL_SysWMmsg *msg);

        /** \brief Returns a string containing all the relevant information in an SDL_Event.
         *
         * \param SDL_Event &<u>event</u>: An SDL event
         * \return std::string String representation of <i>event</i>
         *
         */
        std::string GetEventString(SDL_Event &event);

        /** \brief Returns a string containing all the relevant information in an SDL_Event.
         *
         * \param SDL_Event *<u>event</u>: Pointer to an SDL event
         * \return std::string String representation of <i>event</i>
         *
         */
         std::string GetEventString(SDL_Event *event);
    }
}

#endif // DEBUG_HPP
