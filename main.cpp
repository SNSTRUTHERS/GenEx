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
        break;

    case SDL_KEYUP:
        break;

    case SDL_TEXTINPUT:
        break;

    case SDL_TEXTEDITING:
        break;

    case SDL_MOUSEBUTTONDOWN:
        break;

    case SDL_MOUSEBUTTONUP:
        break;

    case SDL_MOUSEMOTION:
        btns[0] = event.motion.state & SDL_BUTTON_LMASK;
        btns[1] = event.motion.state & SDL_BUTTON_MMASK;
        btns[2] = event.motion.state & SDL_BUTTON_RIGHT;
        btns[3] = event.motion.state & SDL_BUTTON_X1MASK;
        btns[4] = event.motion.state & SDL_BUTTON_X2MASK;
        break;

    case SDL_MOUSEWHEEL:
        break;

    case SDL_CLIPBOARDUPDATE:
        cliptext = SDL_GetClipboardText();
        break;


    case SDL_USEREVENT:
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

    /*auto objptr = std::make_shared<Object>();
    Layer *layer1 = new Layer(objptr, std::make_shared<Object>());
    std::cout << "Number of objects: " << layer1->num_objects() << '\n';
    layer1->remove_object(1);
    std::cout << "Number of objects: " << layer1->num_objects() << '\n';
    layer1->remove_object(0);
    std::cout << "Number of objects: " << layer1->num_objects() << '\n';
    delete layer1;*/

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
