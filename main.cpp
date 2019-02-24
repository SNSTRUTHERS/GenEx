/**
 * \file main.cpp
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
 * The main GenEx executable code.
 *
 */

#include "genex.h"

using namespace GenEx;

/** \brief Handles event polling.
 *
 * \param Layer &<u>winlayer</u>: The top level layer
 * \param std::unordered_map &<u>windowthreads</u>: A map containing the window thread data
 * \param std::vector &<u>events</u>: A vector in which to place the events
 *
 */
void poll_events(Layer &winlayer,
                 std::unordered_map<Uint64, Graphics::WindowThreadData*> &windowthreads,
                 std::vector<SDL_Event> &events) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == GENEX_CREATEWINDOWEVENT) {
            Graphics::WindowData  *windt        = (Graphics::WindowData*)  event.user.data1;
            Events::EventHandlers *evt_handlers = (Events::EventHandlers*) event.user.data2;
            Graphics::WindowThreadData *wd = Graphics::CreateWindow(*windt, *evt_handlers);

            delete windt;
            delete evt_handlers;

            windowthreads[wd->window->get_id()] = wd;
            winlayer.add_object(std::shared_ptr<Object>(wd->window),
                                std::string("win") + std::to_string(wd->window->get_id()));
            continue;
        }
        events.emplace_back(event);
    }
}

/** \brief Pushes an event to create a new GenEx window.
 *
 * \param Graphics::WindowData <u>windt</u>: Data used to construct the window
 * \param Events::EventHandlers <u>evt_handlers</u>: Event handlers for the window to use
 *
 */
void addwin(Graphics::WindowData &windt, Events::EventHandlers &evt_handlers) {
    SDL_Event evt;
    SDL_zero(evt);

    Graphics::WindowData *wd = new Graphics::WindowData();
    *wd = windt;
    Events::EventHandlers *evh = new Events::EventHandlers();
    *evh = evt_handlers;

    evt.type = GENEX_CREATEWINDOWEVENT;
    evt.user.data1 = (void*)(wd);
    evt.user.data2 = (void*)(evh);

    SDL_PushEvent(&evt);
}

/** \brief Pushes an event to create a new GenEx window.
 *
 * \param std::string <u>title</u>: The window title
 * \param int <u>x</u>: The window's x-position
 * \param int <u>y</u>: The window's y-position
 * \param int <u>w</u>: The window's width
 * \param int <u>h</u>: The window's height
 * \param Uint32 <u><i>winflags</i></u>: Flags for setting up the window
 * \param Uint32 <u><i>renflags</i></u>: Flags for setting up the window renderer
 * \param Events::EventHandlers <u><i>evt_handlers</i></u>: Event handlers for the window to use
 *
 */
void addwin(std::string title, int x, int y, int w, int h,
            Uint32 winflags = DEFAULT_WINFLAGS,
            Uint32 renflags = DEFAULT_RENFLAGS,
            double framerate = Graphics::DEFAULT_FRAMERATE,
            Events::EventHandlers evt_handlers = Events::GenerateEventHandlerStruct()) {
    Graphics::WindowData windt = {title, x, y, w, h, winflags, renflags, framerate};
    addwin(windt, evt_handlers);
}

int main(int argc, char *argv[]) {
    // initialize SGE/GenEx
    if (!Init()) {
        return -1;
    }
    std::cout << Debug::GetVersionString() << '\n';

    // Things to keep track of top-level objects
    Layer winlayer; // PARENT WINDOW LAYER
    std::unordered_map<Uint64, Graphics::WindowThreadData*> windowthreads;
    std::unordered_map<Uint64, double> windowtimes;

    {
        addwin("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);
    }

    bool quitflag = false;
    std::vector<SDL_Event> events;
    while (!quitflag) {
        poll_events(winlayer, windowthreads, events);

        // loop through all top-level objects
        for (auto pr = winlayer.begin(); pr != winlayer.end(); pr++) {
            std::shared_ptr<GenEx::Object> obj = pr->second;
            Uint64 obj_id = obj->get_id();

            // handle windows
            if (windowthreads.find(obj_id) != windowthreads.end()) {
                if (windowthreads[obj_id]->complete) {
                    SDL_DestroyCond(windowthreads[obj_id]->c);
                    SDL_DestroyMutex(windowthreads[obj_id]->m);
                    delete windowthreads[obj_id];

                    windowthreads.erase(obj_id);
                    obj->destroy();
                    winlayer.remove_object(obj);
                    break;
                }
                else {
                    bool evt_flag = true;
                    if (windowtimes.find(obj_id) != windowtimes.end() &&
                            windowthreads[obj_id]->framerate > 0.0) {
                        evt_flag = (Time::GetTime() - windowtimes[obj_id]) >
                                       (1.0 / windowthreads[obj_id]->framerate);
                    }

                    if (evt_flag) {
                        Graphics::Window *win = ((Graphics::Window*)(obj.get()));
                        Uint32 win_id = win->get_window_id();

                        SDL_LockMutex(windowthreads[obj_id]->m);

                        for (auto &evt : events) {
                            if (evt.type == SDL_QUIT) {
                                quitflag = true;
                                break;
                            }

                            if ((evt.type == SDL_WINDOWEVENT     &&
                                    win_id == evt.window.windowID) ||
                                (evt.type == SDL_MOUSEBUTTONDOWN &&
                                    win_id == evt.button.windowID) ||
                                (evt.type == SDL_MOUSEBUTTONUP   &&
                                    win_id == evt.button.windowID) ||
                                (evt.type == SDL_MOUSEMOTION     &&
                                    win_id == evt.motion.windowID) ||
                                (evt.type == SDL_MOUSEWHEEL      &&
                                    win_id == evt.wheel.windowID)  ||
                                 evt.type != SDL_WINDOWEVENT) {
                                windowthreads[obj_id]->event_buffer.emplace_back(evt);
                            }
                        }

                        SDL_CondSignal( windowthreads[obj_id]->c);
                        SDL_UnlockMutex(windowthreads[obj_id]->m);

                        windowtimes[obj_id] = Time::GetTime();
                    }
                }
            }
        }

        events.clear();

        if (winlayer.num_objects() < 1)
            quitflag = true;
    }

    winlayer.destroy();

    SDL_Quit();
    return 0;
}
