/**
 * \file graphics/window.hpp
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
 * The header file defining the Window class & related functions.
 *
 */

#ifndef GRAPHICS_WINDOW_HPP
#define GRAPHICS_WINDOW_HPP

#include "base.hpp"
#include "graphics/draw.hpp"
#include "object.hpp"
#include "time.hpp"

#undef CreateWindow
#undef CreateWindowA
#undef CreateWindowEx
#undef CreateWindowStation
#undef CreateWindowW

namespace GenEx {
    namespace Graphics {

// --- WINDOW-RELATED EVENT HANDLERS --------------------------------------------------------------

        struct WindowData {
            std::string title;
            int x;
            int y;
            int w;
            int h;
            Uint32 winflags;
            Uint32 renflags;
            double framerate;
        };

        const double DEFAULT_FRAMERATE = 144.0;

// --- THE WINDOW CLASS ---------------------------------------------------------------------------

        /** \brief The base Window class; a collection of objects contained in a GUI window
         */
        class Window : public Layer {
        private:
            SDL_Window *window;
            SDL_Renderer *renderer = nullptr;
            SDL_GLContext gl_context = nullptr;

            WindowData initdata;

            double t_elapsed, t_prev;

        public:
            /** \brief Constructs a new window with the given window data & event handlers.
             *
             * \param Events::EventHandlers <u>evt_handlers</u>: Event handlers for this window
             * \param WindowData <u>dt</u>: Data to construct this window
             *
             */
            Window(Events::EventHandlers evt_handlers, WindowData dt);

            /** \brief Constructs a new window with the given window data.
             *
             * \param WindowData <u>dt</u>: Data to construct this window
             *
             */
            Window(WindowData dt);

            /** \brief Copy constructor using an existing window and new window data.
             *
             * \param Window &<u>other</u>: Reference to another window
             * \param WindowData <u>dt</u>: Data to construct this window
             *
             */
            Window(const Window &other, WindowData dt);

            /** \brief Copy constructor using an existing window.
             *
             * \param Window &<u>other</u>: Reference to another window
             *
             */
            Window(const Window &other);

            /** \brief Move constructor using a temporary window and new window data.
             *
             * \param Window &&<u>other</u>: Reference to another window
             *
             */
            Window(Window &&other);

// ------ WINDOW FLAGS/DATA SETTERS ---------------------------------------------------------------

            /** \brief Resize this window.
             *
             * \param int <u>w</u>: The new width
             * \param int <u>h</u>: The new height
             *
             */
            void resize(int w, int h);

            /** \brief Sets the screen position of the window.
             *
             * \param int <u>x</u>: X-position
             * \param int <u>y</u>: Y-position
             *
             */
            void set_position(int x, int y);

            /** \brief Set the caption/title for this window.
             *
             * \param std::string <u>title</u>: The new caption/title
             *
             */
            void set_title(std::string title);

            /** \brief Set the brightness of this window.
             *
             * \param float <u>brightness</u>: 0.0f for dark; 1.0f for full brightness
             *
             */
            void set_brightness(float brightness);

            /** \brief Set the opacity of this window.
             *
             * \param float <u>opacity</u>: 0.0f for transparent; 1.0f for opaque
             *
             */
            void set_opacity(float opacity);

            /** \brief Set the minimum size this window can be resized to.
             *
             * \param int <u>minw</u>: Minimum width
             * \param int <u>minh</u>: Minimum height
             *
             */
            void set_min_size(int minw, int minh);

            /** \brief Set the maximum size this window can be resized to.
             *
             * \param int <u>maxw</u>: Maximum width
             * \param int <u>maxh</u>: Maximum height
             *
             */
            void set_max_size(int maxw, int maxh);

            /** \brief Set whether or not this window should have borders or not.
             *
             * \param bool <u>bordered</u>: TRUE to have window borders
             *
             */
            void set_bordered(bool bordered);

            /** \brief Sets the logical size (drawable area) of the window.
             *
             * \param int <u>w</u>: Width of drawing space
             * \param int <u>h</u>: Height of drawing space
             *
             */
            void set_logical_size(int w, int h);

            /** \brief Sets whether or not the window is fullscreen.
             *
             * \param Uint32 <u>fullscreen</u>: 0 for non-fullscreen; SDL_WINDOW_FULLSCREEN for
             *        true fullscreen; SDL_WINDOW_FULLSCREEN_DESKTOP to maximize the window to the
             *        size of the desktop
             *
             */
            void set_fullscreen(Uint32 fullscreen);

// ------ ACCELERATION-RELATED FUNCTIONS ----------------------------------------------------------

            /** \brief Set this window to be the current OpenGL context
             */
            void gl_make_current();

// ------ WINDOW FLAGS/DATA GETTERS ---------------------------------------------------------------

            Uint32 get_window_id();

            /** \brief Gets which display the window is a part of.
             *
             * \return int Index representing a dispaly.
             *
             */
            int get_display_index();

            /** \brief Gets the window's position on the screen.
             *
             * \return SDL_Rect A rect representing the location of the window on the screen
             *
             */
            SDL_Rect get_screen_rect();

            /** \brief Gets the window's drawable area as a rectangle.
             *
             * \return SDL_Rect A rect representing the window's drawable area.
             *
             */
            SDL_Rect get_rect();

            /** \brief Gets the brightness of the window.
             *
             * \return float 0.0f for dark; 1.0f for full brightness
             *
             */
            float get_brightness();

            /** \brief Get the caption/title of the window.
             *
             * \return std::string The window caption/title
             *
             */
            std::string get_title();

            /** \brief Gets the opacity of the window.
             *
             * \return float 0.0f for transparent; 1.0f for opaque
             *
             */
            float get_opacity();

// ------ WINDOW EVENT HANDLERS -------------------------------------------------------------------

            /** \brief Destroys this window
             */
            void destroy();

            virtual void render(SDL_Renderer *target, int offset_x, int offset_y, int offset_z);

            virtual bool update(double elapsed);

            virtual bool windowevent(Uint8 event, Sint32 data1, Sint32 data2);

// ------ WINDOW EVENT DISTRIBUTION & MANAGEMENT --------------------------------------------------

            /** \brief Handles/distributes a given SDL_Event
             *
             * \param SDL_Event &<u>event</u>: An event to handle
             * \return bool TRUE to continue running the application
             *
             */
            bool handle_event(SDL_Event &event);
        };

// --- WINDOW THREAD MANAGEMENT VARS & FUNCTIONS --------------------------------------------------

        struct WindowThreadData {
            const std::string name;
            Window *window;
            SDL_cond *c;
            SDL_mutex *m;
            std::vector<SDL_Event> event_buffer;
            const double framerate;
            bool complete;
        };

        /** \brief Thread function to run a GenEx Window.
         *
         * \param void *<u>data</u>: Pointer to a WindowThreadData struct
         * \return int The return code of the window
         *
         */
        int RunWindow(void *data);

        /** \brief Creates a new GenEx Window.
         *
         * \param WindowData <u>windt</u>: Window initialization data
         * \param Events::EventHandlers <u>evt_handlers</u>: Event handlers for the
         *        window to use
         * \return WindowThreadData Pointers to the created Window and a return code for when the
         *         window closes
         *
         */
        WindowThreadData *CreateWindow(WindowData windt, Events::EventHandlers evt_handlers);

        /** \brief Creates a new GenEx Window.
         *
         * \param std::string <u>title</u>: The window title
         * \param int <u>x</u>: The window's x-position
         * \param int <u>y</u>: The window's y-position
         * \param int <u>w</u>: The window's width
         * \param int <u>h</u>: The window's height
         * \param Uint32 <u><i>winflags</i></u>: Flags for setting up the window
         * \param Uint32 <u><i>renflags</i></u>: Flags for setting up the window renderer
         * \param Events::EventHandlers <u><i>evt_handlers</i></u>: Event handlers for the
         *        window to use
         * \return WindowThreadData Pointers to the created Window and a return code for when the
         *         window closes
         *
         */
        WindowThreadData *CreateWindow(std::string title, int x, int y, int w, int h,
                                       Uint32 winflags = DEFAULT_WINFLAGS,
                                       Uint32 renflags = DEFAULT_RENFLAGS,
                                       Events::EventHandlers evt_handlers =
                                           Events::GenerateEventHandlerStruct(),
                                       double framerate = DEFAULT_FRAMERATE);
    }
}

#endif // GRAPHICS_WINDOW_HPP
