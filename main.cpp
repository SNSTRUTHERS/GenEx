#include "genex.h"

using namespace GenEx;

static double FPS;
static Uint32 win_id;

// event handling
bool handle_event(SDL_Event &event) {
    bool running = true;

    char *cliptext = new char[32];
    bool btns[5];

    switch (event.type) {
    case SDL_WINDOWEVENT:
        switch (event.window.type) {
        // window is closed
        case SDL_WINDOWEVENT_CLOSE:
            break;

        // gain mouse focus
        case SDL_WINDOWEVENT_ENTER:
            break;

        // lose mouse focus
        case SDL_WINDOWEVENT_LEAVE:
            break;

        // window hidden
        case SDL_WINDOWEVENT_HIDDEN:
            break;

        // window shown
        case SDL_WINDOWEVENT_SHOWN:
            break;

        // window exposed & should be redrawn
        case SDL_WINDOWEVENT_EXPOSED:
            break;

        // window maximized
        case SDL_WINDOWEVENT_MAXIMIZED:
            break;

        // window minimized
        case SDL_WINDOWEVENT_MINIMIZED:
            break;

        // change in window's position
        case SDL_WINDOWEVENT_MOVED:
            break;

        // window resized
        case SDL_WINDOWEVENT_RESIZED:
            break;

        // size of the window has been manually changed
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            break;

        // window restored to normal size/position
        case SDL_WINDOWEVENT_RESTORED:
            break;

        // gain keyboard focus
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            break;

        // lose keyboard focus
        case SDL_WINDOWEVENT_FOCUS_LOST:
            break;

        // hit test
        case SDL_WINDOWEVENT_HIT_TEST:
            break;

        // window is being granted keyboard focus
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            break;

        }
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            case SDLK_F3:
                DEBUGGING = DEBUGGING ? 0 : ( (SDL_GetModState() & KMOD_CTRL) ? 2: 1 );
                break;
            case SDLK_F4:
                running = !((SDL_GetModState() & KMOD_ALT) > 0) && (!SDL_GetHintBoolean(SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4, SDL_FALSE));
                break;
        }
//        Events::KeyDownEventHandler(event.key.keysym.sym, event.key.keysym.scancode, event.key.repeat);
        break;

    case SDL_KEYUP:
//        Events::KeyUpEventHandler(event.key.keysym.sym, event.key.keysym.scancode, event.key.repeat);
        break;

    case SDL_TEXTINPUT:
//        Events::TextInputEventHandler(event.text.text);
        break;

    case SDL_TEXTEDITING:
//        Events::TextEditingEvent(event.edit.text, event.edit.start, event.edit.length);
        break;

    case SDL_MOUSEBUTTONDOWN:
//        Events::MouseButtonDownEventHandler(event.button.x, event.button.y, event.button.button, event.button.clicks, event.button.which);
        break;

    case SDL_MOUSEBUTTONUP:
//        Events::MouseButtonUpEventHandler(event.button.x, event.button.y, event.button.button, event.button.clicks, event.button.which);
        break;

    case SDL_MOUSEMOTION:
        btns[0] = event.motion.state & SDL_BUTTON_LMASK;
        btns[1] = event.motion.state & SDL_BUTTON_MMASK;
        btns[2] = event.motion.state & SDL_BUTTON_RIGHT;
        btns[3] = event.motion.state & SDL_BUTTON_X1MASK;
        btns[4] = event.motion.state & SDL_BUTTON_X2MASK;
//        Events::MouseMotionEventHandler(event.motion.x, event.motion.y, event.motion.xrel,  event.motion.yrel, btns, event.motion.which);
        break;

    case SDL_MOUSEWHEEL:
//        Events::MouseWheelEventHandler(event.wheel.direction, event.wheel.x, event.wheel.y, event.wheel.which);
        break;

    case SDL_CLIPBOARDUPDATE:
        cliptext = SDL_GetClipboardText();
//        Events::ClipboardUpdateEventHandler(txt);
        break;


    case SDL_USEREVENT:
//        Events::UserEventHandler(event.user.code, event.user.data1, event.user.data2);
        break;

    default:
        break;
    }

    delete[] cliptext;
    return running;
}

// update
bool update(double elapsed) {
    return true;
}

// draw function
void draw(SDL_Renderer *renderer) {
    Math::BezierCurve c{ { 300.0, 300.0 }, { 350.0, 250.0 }, { 700.0, 450.0 }, { 550.0, 440.0 } };
    static Math::BezierPath p( { std::make_tuple( c, 0 ) } );
    Graphics::RenderPath(p, renderer, { 255, 255, 255, 255 });
}

// debug screen
void draw_debug(SDL_Renderer *renderer) {
    std::stringstream sst;
    sst << "FPS: " << roundf(FPS* 100)/100;

    SDL_Surface *fpssurf = TTF_RenderText_Blended(DEBUG_FONT, sst.str().c_str(), { 0, 0, 0, 255 });
    Graphics::RenderImg(fpssurf, renderer, 0.0f, DEBUG_FONT_SIZE / 32.0f, nullptr,
                        0.0f, 0.0f, 0.0f, 0.0f);
    SDL_FreeSurface(fpssurf);
    fpssurf = TTF_RenderText_Blended(DEBUG_FONT, sst.str().c_str(), { 255, 255, 255, 255 });
    Graphics::RenderImg(fpssurf, renderer, 0.0f, 0.0f, nullptr, 0.0f, 0.0f, 0.0f, 0.0f);
    SDL_FreeSurface(fpssurf);
}

// main loop
void main_loop(SDL_Renderer *renderer) {
    bool running = true;
    SDL_Event event;

    std::vector<double> fps_buffer;
    double fps_counter = 0.0;

    double elapsed, prev;
    prev = Time::GetSecs();
    FPS = 0.0;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    running = handle_event(event);
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);
        draw(renderer);
        if (DEBUGGING)
            draw_debug(renderer);
        SDL_RenderPresent(renderer);

        elapsed = Time::GetSecs() - prev;
        running &= update(elapsed);
        prev = Time::GetSecs();

        fps_counter += elapsed;

        if (fps_counter > 0.125 && fps_buffer.size() > 10) {
            FPS = 0.0;
            fps_counter = 0;
            for (auto &d : fps_buffer) FPS += d;
            FPS /= fps_buffer.size();
            fps_buffer.clear();
        }
        fps_buffer.push_back(1.0 / ( elapsed + 0.00001 ));

        std::stringstream sst;
        sst << "FPS: " << roundf(*(fps_buffer.end()-1) * 100)/100;
    }
}

int main(int argc, char *argv[]) {
    // initialize SGE/GenEx
    if (!Init()) {
        return -1;
    }
    std::cout << Debug::GetVersionString() << '\n';

    SDL_Window *win = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       1280, 720, WINFLAGS);
    win_id = SDL_GetWindowID(win);
    if (win == nullptr) {
        TTF_Quit();
        SDL_Quit();
        return -2;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, RENFLAGS);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return -2;
    }

    main_loop(ren);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    TTF_CloseFont(DEBUG_FONT);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
