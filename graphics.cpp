/**
 * \file graphics.cpp
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
 * The source file for graphics-related routines & classes.
 *
 */

#include "graphics.hpp"

// --- RENDERING FUNCTIONS ------------------------------------------------------------------------

bool GenEx::Graphics::RenderImg(SDL_Texture *img, SDL_Renderer *target, float x, float y,
                                SDL_Rect *clipping_rect, float offset_x, float offset_y,
                                float anchor_x, float anchor_y, double rotation, float scale_x,
                                float scale_y, bool flip_horizontal, bool flip_vertical) {
    if (img == nullptr || target == nullptr) return false;

    int tw, th; // get width & height
    SDL_QueryTexture(img, nullptr, nullptr, &tw, &th);

    float w, h;
    w = scale_x * tw;
    h = scale_y * th;

    SDL_Rect dstrect;
    dstrect.x = x - (w  * anchor_x);
    dstrect.x += offset_x;
    dstrect.y = y - (h * anchor_y);
    dstrect.y += offset_y;
    dstrect.w = (int)w;
    dstrect.h = (int)h;

    //SDL_Point center = {center_x, center_y};

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (flip_horizontal && flip_vertical) {
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    } else if (flip_horizontal) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (flip_vertical) {
        flip = SDL_FLIP_VERTICAL;
    }

    return SDL_RenderCopyEx(target, img, clipping_rect, &dstrect,
                            rotation, nullptr, flip) == 0;
}

bool GenEx::Graphics::RenderImg(SDL_Surface *surf, SDL_Renderer *target, float x, float y,
                                SDL_Rect *clipping_rect, float offset_x, float offset_y,
                                float anchor_x, float anchor_y, double rotation, float scale_x,
                                float scale_y, bool flip_horizontal, bool flip_vertical) {
    SDL_Texture *tex = SDL_CreateTextureFromSurface(target, surf);
    if (tex == nullptr) {
        return false;
    }
    bool ret_val = GenEx::Graphics::RenderImg(tex, target, x, y, clipping_rect, offset_x, offset_y,
                                              anchor_x, anchor_y, rotation, scale_x, scale_y,
                                              flip_horizontal, flip_vertical);
    SDL_DestroyTexture(tex);
    return ret_val;
}

void GenEx::Graphics::RenderLine(SDL_Renderer *target, SDL_Color color,
                                 int x0, int y0, int x1, int y1, float wd) {
    Uint8 r,g,b,a;
    SDL_BlendMode blend_mode;
    SDL_GetRenderDrawColor(target, &r, &g, &b, &a);
    SDL_GetRenderDrawBlendMode(target, &blend_mode);

    std::map<Uint8, std::vector<SDL_Point> > alpha_map;

    bool steep = SDL_abs(y1-y0) > SDL_abs(x1-x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    // compute the slope
    float dx = x1-x0;
    float dy = y1-y0;
    float gradient = dy/dx;
    if (dx == 0.0)
        gradient = 1;

    int xpxl1 = x0;
    int xpxl2 = x1;
    float intersectY = y0;

    // main loop
    if (steep) {
        for (int x = xpxl1 ; x <=xpxl2 ; x++) {
            alpha_map[(Uint8) (255*freciprocal(intersectY))].emplace_back(
                SDL_Point{ (int)intersectY, x }
            );
            alpha_map[(Uint8) (255*fracofnum(intersectY))].emplace_back(
                SDL_Point{ (int)intersectY+1, x }
            );
            intersectY += gradient;
        }
    }
    else {
        for (int x = xpxl1 ; x <=xpxl2 ; x++) {
            alpha_map[(Uint8) (255*freciprocal(intersectY))].emplace_back(
                SDL_Point{ x, (int)intersectY }
            );
            alpha_map[(Uint8) (255*fracofnum(intersectY))].emplace_back(
                SDL_Point{ x, (int)intersectY+1 }
            );
            intersectY += gradient;
        }
    }

    SDL_SetRenderDrawBlendMode(target, SDL_BLENDMODE_BLEND);
    for (auto &iter : alpha_map) {
        if (iter.first > 0) {
            SDL_SetRenderDrawColor(target, color.r, color.g, color.b,
                                   (Uint8)(color.a*(iter.first / 255.f)));
            SDL_Point *parr = &(iter.second)[0];
            SDL_RenderDrawPoints(target, parr, iter.second.size());
        }
    }

    SDL_SetRenderDrawColor(target, r, g, b, a);
    SDL_SetRenderDrawBlendMode(target, blend_mode);
}

template <typename T>
void GenEx::Graphics::RenderLines(SDL_Renderer *target, SDL_Color color,
                                  std::vector< Math::Vector<2,T> > &pts, float wd) {
    if (pts.size() < 2)
        return;

    for (auto iter = pts.begin(); iter != pts.end() - 1; iter++) {
        GenEx::Math::Vector<2,T> pt0 = *iter;
        GenEx::Math::Vector<2,T> pt1 = *(iter+1);

        int x0, y0, x1, y1;
        x0 = std::round(pt0[0]);
        x1 = std::round(pt1[0]);
        y0 = std::round(pt0[1]);
        y1 = std::round(pt1[1]);

        GenEx::Graphics::RenderLine(target, color, x0, y0, x1, y1, wd);
    }
}

template <typename T>
void GenEx::Graphics::RenderBezier(GenEx::Math::Bezier<T> bezier, SDL_Renderer *target,
                                   SDL_Color color, float thickness, unsigned int samples) {
    std::vector< Math::Vector<2,T> > pts;
    bezier.sample(pts, samples);

    GenEx::Graphics::RenderLines(target, color, pts, thickness);
}

template <typename T>
void GenEx::Graphics::RenderPath(GenEx::Math::Path<T> &path, SDL_Renderer *target,
                                 SDL_Color color, float thickness) {
    std::vector< Math::Vector<2,T> > pts;
    path.sample(pts);

    GenEx::Graphics::RenderLines(target, color, pts, thickness);
}

// --- WINDOW CLASS -------------------------------------------------------------------------------
// ------ CONSTRUCTORS ----------------------------------------------------------------------------

GenEx::Graphics::Window::Window(GenEx::Events::EventHandlers evt_handlers,
                                GenEx::Graphics::WindowData dt) : Layer(evt_handlers) {
    initdata = dt;

    window = SDL_CreateWindow(dt.title.c_str(), dt.x, dt.y, dt.w, dt.h, dt.winflags);
    renderer = SDL_CreateRenderer(window, -1, dt.renflags);

    if (dt.winflags & SDL_WINDOW_OPENGL) {
        SDL_GL_CreateContext(window);
    }
    else if (dt.winflags & SDL_WINDOW_VULKAN) {

    }

    SDL_SetWindowTitle(window, dt.title.c_str());
    t_prev = GenEx::Time::GetTime();
}

GenEx::Graphics::Window::Window(WindowData dt) : Window(GenEx::Events::GenerateEventHandlerStruct(),
                                                        dt) { }

GenEx::Graphics::Window::Window(const GenEx::Graphics::Window &other,
                                GenEx::Graphics::WindowData dt) : Layer(other) {
    initdata = dt;
    objects = other.objects;
    id_map = other.id_map;

    SDL_GetWindowSize(other.window, &dt.w, &dt.h);
    window = SDL_CreateWindow(SDL_GetWindowTitle(other.window), dt.x, dt.y, dt.w, dt.h,
                              dt.winflags);
    renderer = SDL_CreateRenderer(window, -1, dt.renflags);

    if (dt.winflags & SDL_WINDOW_OPENGL) {
        SDL_GL_CreateContext(window);
    }
    else if (dt.winflags & SDL_WINDOW_VULKAN) {

    }

    SDL_SetWindowTitle(window, dt.title.c_str());
    t_prev = GenEx::Time::GetTime();
}

GenEx::Graphics::Window::Window(const GenEx::Graphics::Window &other) : Layer(other) {
    initdata = other.initdata;
    objects = other.objects;
    id_map = other.id_map;

    window = SDL_CreateWindow(SDL_GetWindowTitle(other.window), initdata.x, initdata.y,
                              initdata.w, initdata.h, initdata.winflags);
    renderer = SDL_CreateRenderer(window, -1, initdata.renflags);

    if (initdata.winflags & SDL_WINDOW_OPENGL) {
        SDL_GL_CreateContext(window);
    }
    else if (initdata.winflags & SDL_WINDOW_VULKAN) {

    }

    SDL_SetWindowTitle(window, initdata.title.c_str());
    t_prev = GenEx::Time::GetTime();
}

GenEx::Graphics::Window::Window(GenEx::Graphics::Window &&other) : Layer(other) {
    objects    = std::move(other.objects);
    id_map     = std::move(other.id_map);
    window     = std::move(other.window);
    renderer   = std::move(other.renderer);
    gl_context = std::move(other.gl_context);

    t_elapsed  = std::move(other.t_elapsed);
    t_prev     = std::move(other.t_prev);
}

// ------ 3D ACCELERATION-RELATED FUNCTIONS -------------------------------------------------------

void GenEx::Graphics::Window::gl_make_current() { SDL_GL_MakeCurrent(window, gl_context); }

// ------ WINDOW PROPERTY SETTERS -----------------------------------------------------------------

void GenEx::Graphics::Window::resize(int w, int h) {
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) {
        SDL_DisplayMode dspmd;
        dspmd.driverdata = 0;
        dspmd.format = SDL_GetWindowPixelFormat(window);
        dspmd.refresh_rate = 0;
        dspmd.w = w;
        dspmd.h = h;

        SDL_SetWindowDisplayMode(window, &dspmd);
    }
    SDL_SetWindowSize(window, w, h);
}

void GenEx::Graphics::Window::set_position(int x, int y) {
    SDL_SetWindowPosition(window, x, y);
}

void GenEx::Graphics::Window::set_title(std::string title) {
    SDL_SetWindowTitle(window, title.c_str());
}

void GenEx::Graphics::Window::set_brightness(float brightness) {
    SDL_SetWindowBrightness(window, brightness);
}

void GenEx::Graphics::Window::set_opacity(float opacity) {
    SDL_SetWindowOpacity(window, opacity);
}

void GenEx::Graphics::Window::set_min_size(int minw, int minh) {
    SDL_SetWindowMinimumSize(window, minw, minh);
}

void GenEx::Graphics::Window::set_max_size(int maxw, int maxh) {
    SDL_SetWindowMaximumSize(window, maxw, maxh);
}

void GenEx::Graphics::Window::set_bordered(bool bordered) {
    SDL_SetWindowBordered(window, bordered ? SDL_TRUE : SDL_FALSE);
}

void GenEx::Graphics::Window::set_logical_size(int w, int h) {
    if ( !(initdata.winflags & SDL_WINDOW_OPENGL) &&
         !(initdata.winflags & SDL_WINDOW_VULKAN)) {
        SDL_RenderSetLogicalSize(renderer, w, h);
    }
}

void GenEx::Graphics::Window::set_fullscreen(Uint32 fullscreen) {
    SDL_SetWindowFullscreen(window, fullscreen);
}

// ------ WINDOW PROPERTY GETTERS -----------------------------------------------------------------

Uint32 GenEx::Graphics::Window::get_window_id() { return SDL_GetWindowID(window); }

int GenEx::Graphics::Window::get_display_index() { return SDL_GetWindowDisplayIndex(window); }

SDL_Rect GenEx::Graphics::Window::get_screen_rect() {
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_GetWindowPosition(window, &rect.x, &rect.y);
    SDL_GetWindowSize(window, &rect.w, &rect.h);

    int t, l, b, r;
    SDL_GetWindowBordersSize(window, &t, &l, &b, &r);
    rect.w += l+r;
    rect.h += t+b;

    return rect;
}

SDL_Rect GenEx::Graphics::Window::get_rect() {
    SDL_Rect rect = {0, 0, 0, 0};

    if (initdata.winflags & SDL_WINDOW_OPENGL) {
        SDL_GL_GetDrawableSize(window, &rect.w, &rect.h);
    }
    else {
        SDL_RenderGetLogicalSize(renderer, &rect.w, &rect.h);
        if (!rect.w && !rect.h)
            SDL_GetRendererOutputSize(renderer, &rect.w, &rect.h);
    }

    return rect;
}

float GenEx::Graphics::Window::get_brightness() {
    return SDL_GetWindowBrightness(window);
}

std::string GenEx::Graphics::Window::get_title() {
    return std::string(SDL_GetWindowTitle(window));
}

float GenEx::Graphics::Window::get_opacity() {
    float opacity;
    SDL_GetWindowOpacity(window, &opacity);
    return opacity;
}

// ------ WINDOW EVENT HANDLERS -------------------------------------------------------------------

void GenEx::Graphics::Window::destroy() {
    if (!is_dead()) {
        Layer::destroy();
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
}

void GenEx::Graphics::Window::render(SDL_Renderer *target, int offset_x, int offset_y,
                                     int offset_z) {
    SDL_RenderClear(renderer);
    Layer::render(this->renderer, offset_x, offset_y, offset_z);
    SDL_RenderPresent(renderer);
}

bool GenEx::Graphics::Window::update(double elapsed) {
    t_elapsed = GenEx::Time::GetTime() - t_prev;
    bool ret_val = Layer::update(t_elapsed);
    t_prev = GenEx::Time::GetTime();
    return ret_val;
}

bool GenEx::Graphics::Window::windowevent(Uint8 event, Sint32 data1, Sint32 data2) {
    switch (event) {
    case SDL_WINDOWEVENT_CLOSE:
        return false;
    default:
        break;
    }
    return Layer::windowevent(event, data1, data2);
}

bool GenEx::Graphics::Window::handle_event(SDL_Event &event) {
    bool btns[5];

    //SDL_Log("Handling event: %s\n", Debug::GetEventString(event).c_str());

    switch (event.type) {
    case SDL_QUIT:
    case SDL_APP_TERMINATING:
        return false;

    case SDL_RENDER_DEVICE_RESET:
    case SDL_RENDER_TARGETS_RESET:
        return targetreset();

    case SDL_WINDOWEVENT:
        return windowevent(event.window.event, event.window.data1, event.window.data2);

    case SDL_KEYDOWN:
        return keydown(event.key.keysym.sym, event.key.keysym.scancode, event.key.keysym.mod,
                       event.key.repeat);
    case SDL_KEYUP:
        return keyup(event.key.keysym.sym, event.key.keysym.scancode, event.key.keysym.mod,
                     event.key.repeat);

    case SDL_TEXTEDITING:
        return textediting(event.edit.text, event.edit.start, event.edit.length);
    case SDL_TEXTINPUT:
        return textinput(event.text.text);

    case SDL_MOUSEBUTTONDOWN:
        return mousedown(event.button.x, event.button.y, event.button.button, event.button.clicks,
                         event.button.which);
    case SDL_MOUSEBUTTONUP:
        return mouseup(event.button.x, event.button.y, event.button.button, event.button.clicks,
                       event.button.which);

    case SDL_MOUSEMOTION:
        btns[0] = event.motion.state & SDL_BUTTON_LMASK;
        btns[1] = event.motion.state & SDL_BUTTON_MMASK;
        btns[2] = event.motion.state & SDL_BUTTON_RIGHT;
        btns[3] = event.motion.state & SDL_BUTTON_X1MASK;
        btns[4] = event.motion.state & SDL_BUTTON_X2MASK;
        return mousemotion(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel,
                           btns, event.motion.which);

    case SDL_MOUSEWHEEL:
        return mousewheel(event.wheel.direction, event.wheel.x, event.wheel.y, event.wheel.which);

    case SDL_CLIPBOARDUPDATE:
        return clipboardupdate(SDL_GetClipboardText());

    case SDL_DROPFILE:
        return filedrop(std::string(event.drop.file));

    case SDL_DROPTEXT:
        return textdrop(event.drop.file);

    case SDL_DROPBEGIN:
        return begindrop();

    case SDL_DROPCOMPLETE:
        return completedrop();

    case SDL_JOYAXISMOTION:
        return jaxis(event.jaxis.which, event.jaxis.axis, event.jaxis.value);

    case SDL_JOYBALLMOTION:
        return jball(event.jball.which, event.jball.ball, event.jball.xrel, event.jball.yrel);

    case SDL_JOYHATMOTION:
        return jhat(event.jhat.which, event.jhat.hat, event.jhat.value);

    case SDL_JOYBUTTONDOWN:
        return jbtndown(event.jbutton.which, event.jbutton.button);

    case SDL_JOYBUTTONUP:
        return jbtnup(event.jbutton.which, event.jbutton.button);

    case SDL_CONTROLLERAXISMOTION:
        return caxis(event.caxis.which, event.caxis.axis, event.caxis.value);

    case SDL_CONTROLLERBUTTONDOWN:
        return cbtndown(event.cbutton.which, event.cbutton.button);

    case SDL_CONTROLLERBUTTONUP:
        return cbtnup(event.cbutton.which, event.cbutton.button);

    case SDL_FINGERDOWN:
        return fingerdown(event.tfinger.touchId, event.tfinger.fingerId, event.tfinger.x,
                          event.tfinger.y, event.tfinger.pressure);

    case SDL_FINGERUP:
        return fingerup(event.tfinger.touchId, event.tfinger.fingerId, event.tfinger.x,
                        event.tfinger.y, event.tfinger.pressure);

    case SDL_FINGERMOTION:
        return fingermotion(event.tfinger.touchId, event.tfinger.fingerId, event.tfinger.x,
                            event.tfinger.y, event.tfinger.dx, event.tfinger.dy,
                            event.tfinger.pressure);

    case SDL_DOLLARRECORD:
        return gesturerecord(event.dgesture.touchId, event.dgesture.gestureId,
                             event.dgesture.numFingers, event.dgesture.x,
                             event.dgesture.y);

    case SDL_DOLLARGESTURE:
        return gestureperform(event.dgesture.touchId, event.dgesture.gestureId,
                              event.dgesture.numFingers, event.dgesture.x,
                              event.dgesture.y, event.dgesture.error);

    case SDL_MULTIGESTURE:
        return multigesture(event.mgesture.touchId, event.mgesture.numFingers,
                            event.mgesture.x, event.mgesture.y,
                            event.mgesture.dTheta, event.mgesture.dDist);

    case SDL_USEREVENT:
        return userevent(event.user.code, event.user.data1, event.user.data2);

    default:
        return true;
    }
}

// --- WINDOW THREAD MANAGEMENT VARS & FUNCTIONS --------------------------------------------------

int GenEx::Graphics::RunWindow(void *data) {
    GenEx::Graphics::WindowThreadData *windt = (GenEx::Graphics::WindowThreadData*)data;
    GenEx::Graphics::Window *win = windt->window;

    bool running = true;

    while (running) {
        win->render(nullptr, 0, 0, 0);
        running &= win->update(0);

        if (running) {
            // wait for signal from main thread to access event buffer
            SDL_CondWait(windt->c, windt->m);

            std::vector<SDL_Event> event_buffer(windt->event_buffer);
            windt->event_buffer.clear();

            for (auto &event : event_buffer) {
                running &= win->handle_event(event);
                if (!running)
                    break;
            }
        }
    }

    windt->complete = true;
    return 0;
}

GenEx::Graphics::WindowThreadData *GenEx::Graphics::CreateWindow(
        GenEx::Graphics::WindowData windt,
        Events::EventHandlers evt_handlers) {
    GenEx::Graphics::Window *win = new GenEx::Graphics::Window(evt_handlers, windt);
    std::string th_name = "win" + std::to_string((int)win->get_id());

    GenEx::Graphics::WindowThreadData *winthdt = new GenEx::Graphics::WindowThreadData {
        th_name,
        win,
        SDL_CreateCond(),
        SDL_CreateMutex(),
        std::vector<SDL_Event>(),
        windt.framerate,
        false
    };
    SDL_CreateThread(GenEx::Graphics::RunWindow, th_name.c_str(), (void*)(winthdt));
    return winthdt;
}

GenEx::Graphics::WindowThreadData *GenEx::Graphics::CreateWindow(
        std::string title, int x, int y, int w, int h, Uint32 winflags, Uint32 renflags,
        GenEx::Events::EventHandlers evt_handlers, double framerate) {
    WindowData windt = { title, x, y, w, h, winflags, renflags, framerate };
    return GenEx::Graphics::CreateWindow(windt, evt_handlers);
}
