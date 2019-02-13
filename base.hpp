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
#include <unordered_map>
#include <exception>
#include <tuple>
#include <regex>
#include <memory>

#define SDL_main main
#include "SDL.h"
#include "SDL_syswm.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define absv(x) x > 0 ? x : -x\

namespace GenEx {
    static const Uint8  VERSION_STATE = 0;
    static const Uint32 VERSION_MAJOR = 0;
    static const Uint32 VERSION_MINOR = 0;
    static const Uint32 VERSION_PATCH = 3;
    static const std::string EX_NAME = "General Executor"; // The program name

    /** \brief The names of those who have contributed to the development of GenEx
     */
    static const std::string EX_CONT = "Simon NE Struthers, Morgan Dorval, Pat Struthers";

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

    /** \brief The current working directory
     */
    static std::string WORKING_DIR;

    /** \brief The default window flags when creating a new window
     */
    static const Uint32 WINFLAGS = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;


    /** \brief The default renderer flags when creating a rendering context/target
     */
    static const Uint32 RENFLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;

    /** \brief The debug flag; 0 -> no debug options; 1 -> basic debug; 2 -> extended debugs
     */
    static int DEBUGGING = 0;

    // THE FONT USED FOR THE DEBUG SCREEN
    static TTF_Font *DEBUG_FONT;
    static const int DEBUG_FONT_SIZE = 32;

    /** \brief Initializes the General Executor and SDL
     */
    bool Init() {
        bool flag = true;
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
            return false;

        if (TTF_Init() < 0)
            flag = false;

        int imgflags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
        if (!(IMG_Init(imgflags) & imgflags))
            flag = false;


        WORKING_DIR = SDL_GetBasePath();
        DEBUG_FONT = TTF_OpenFont((WORKING_DIR+"opensans.ttf").c_str(), DEBUG_FONT_SIZE);

        if (!flag) {
            TTF_Quit();
            IMG_Quit();
        }

        return flag;
    }

    /** \brief Resets the working directory to a new value.
     *
     * \param std::string <u>dir</u>: The new value for the working directory
     *
     */
    void SetWorkingDir(std::string dir) {
        WORKING_DIR = dir;
    }

    /** \brief Returns the current working directory.
     *
     * \return std::string Current working directory
     *
     */
    std::string GetWorkingDir() { return WORKING_DIR; }

    class Object;
}

#endif // BASE_HPP
