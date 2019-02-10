#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "base.hpp"

namespace GenEx {
    namespace Events {

// --- EVENT HANDLER TYPEDEFS ---------------------------------------------------------------------

        /** \brief Typedef for an event handler for when something is initialized
         */
        typedef void (*OnInitEvent)();

        /** \brief Typedef for an event handler for when something is destroyed
         */
        typedef void (*OnDestroyEvent)();

        /** \brief Typedef for an event handler for when sprites/graphics are updated
         */
        typedef bool (*UpdateEvent)(double);

        /** \brief Typedef for an event handler for an SDL_SYSWMEVENT
         */
        typedef bool (*SysWMEvent)(SDL_SysWMmsg*);

        /** \brief Typedef for an event handler for an SDL_KEYDOWN event
         */
        typedef bool (*KeyDownEvent)(SDL_Keycode, SDL_Scancode, Uint8);

        /** \brief Typedef for an event handler for an SDL_KEYUP event
         */
        typedef bool (*KeyUpEvent)(SDL_Keycode, SDL_Scancode, Uint8);

        /** \brief Typedef for an event handler for an SDL_TEXTEDITING event
         */
        typedef bool (*TextEditingEvent)(char[SDL_TEXTEDITINGEVENT_TEXT_SIZE], Sint32, Sint32);

        /** \brief Typedef for an event handler for an SDL_TEXTINPUT event
         */
        typedef bool (*TextInputEvent)(char[SDL_TEXTINPUTEVENT_TEXT_SIZE]);

        /** \brief Typedef for an event handler for an SDL_CLIPBOARDUPDATE event
         */
        typedef bool (*ClipboardUpdateEvent)(char[]);

        /** \brief Typedef for an event handler for an SDL_MOUSEBUTTONDOWN event
         */
        typedef bool(*MouseButtonDownEvent)(Sint32, Sint32, Uint8, Uint8, Uint32);

        /** \brief Typedef for an event handler for an SDL_MOUSEBUTTONUP event
         */
        typedef bool(*MouseButtonUpEvent)(Sint32, Sint32, Uint8, Uint8, Uint32);

        /** \brief Typedef for an event handler for an SDL_MOUSEMOTION event
         */
        typedef bool(*MouseMotionEvent)(Sint32, Sint32, Sint32, Sint32, bool[5], Uint32);

        /** \brief Typedef for an event handler for an SDL_MOUSEWHEEL event
         */
        typedef bool(*MouseWheelEvent)(Uint32, Sint32, Sint32, Uint32);

        /** \brief Typedef for an event handler for an SDL_USEREVENT event
         */
        typedef bool(*UserEvent)(Sint32, void*, void*);

// --- DEFAULT EVENT HANDLER FUNCTIONS ------------------------------------------------------------

        /** \brief The default event handler for when objects are initialized.
         */
        void OnInitEventHandler() { }

        /** \brief The default event handler for when objects are to be destroyed.
         */
        void OnDestroyEventHandler() { }

        /** \brief The default event handler for when objects need to be updated.
         *
         * \param double <u>elapsed</u>: How much time has elapsed from the previous frame
         * \return bool TRUE to continue running the application
         *
         */
        bool UpdateEventHandler(double elapsed) {
            return true;
        }

        /** \brief The default event handler for an SDL_KEYDOWN event (i.e. when a key is
         *        first pressed).
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was pressed
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was pressed
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        bool KeyDownEventHandler(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            return true;
        }

        /** \brief The default event handler for an SDL_KEYUP event (i.e. when a key is
         *        released after being pressed).
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was released
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was released
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        bool KeyUpEventHandler(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            return true;
        }

        /** \brief The default event handler for an SDL_TEXTEDITING event (i.e. when text
         *        composition has started or changed)
         *
         * \param char <u>text</u>[32]: The event text in UTF-8 encoding
         * \param Sint32 <u>start</u>: The cursor position within the composition
         * \param Sint32 <u>length</u>: The length of selected text in the composition, if any
         * \return bool TRUE to continue running the application
         *
         */
        bool TextEditingEventHandler(char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                     Sint32 start, Sint32 length) {
            return true;
        }

        /** \brief The default event handler for an SDL_TEXTINPUT event (i.e. when text
         *        composition has been committed  or non-IME text input is given)
         *
         * \param char <u>text</u>[32]: The vent text in UTF-8 encoding
         * \return bool TRUE to continue running the application
         *
         */
        bool TextInputEventHandler(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
            return true;
        }

        /** \brief The default event handler for an SDL_CLIPBOARDUPDATE event (i.e. when the
         *        clipboard has been updated/gets new data)
         * \param char <u>text</u>[]: The text copied from the clipboard
         *
         * \return bool TRUE to continue running the application
         *
         */
        bool ClipboardUpdateEventHandler(char text[]) {
            return true;
        }

        /** \brief The default event handler for an SDL_MOUSEBUTTONDOWN event (i.e. when a
         *        button on the mouse is clicked).
         *
         * \param Sint32 <u>x</u>: The relative X-position of the mouse
         * \param Sint32 <u>y</u>: The relative Y-position of the mouse
         * \param Uint8 <u>button</u>: The button on the mouse that was clicked
         * \param Uint8 <u>clicks</u>: How many times the mouse was clicked (e.g. 2 for
         *        double-click)
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        bool MouseButtonDownEventHandler(Sint32 x, Sint32 y, Uint8 button,
                                         Uint8 clicks, Uint32 which) {
            return true;
        }

        /** \brief The default event handler for an SDL_MOUSEBUTTONUP event (i.e. when a
         *        button on the mouse is released after being clicked).
         *
         * \param Sint32 <u>x</u>: The relative X-position of the mouse
         * \param Sint32 <u>y</u>: The relative Y-position of the mouse
         * \param Uint8 <u>button</u>: The button on the mouse that was released
         * \param Uint8 <u>clicks</u>: How many times the mouse was released (e.g. 2 for
         *        double-click)
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        bool MouseButtonUpEventHandler(Sint32 x, Sint32 y, Uint8 button,
                                       Uint8 clicks, Uint32 which) {
            return true;
        }

        /** \brief The default event handler for an SDL_MOUSEMOTION event (i.e. when the
         *        mouse moves across the screen).
         *
         * \param Sint32 <u>x</u>: The relative X-position of the mouse
         * \param Sint32 <u>y</u>: The relative Y-position of the mouse
         * \param Sint32 <u>xrel</u>: The relative movement of the mouse along the X-axis
         * \param Sint32 <u>yrel</u>: The relative movement of the mouse along the Y-axis
         * \param bool <u>buttons</u>[5]: Which mouse buttons are being pressed; [0] -> left,
         *        [1] -> middle, [2] -> right, [3] -> X1, [4] -> X2
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        bool MouseMotionEventHandler(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel,
                                     bool buttons[5], Uint32 which) {
            return true;
        }

        /** \brief The default event handler for an SDL_MOUSEWHEEL event (i.e. when the scroll
         *        wheel on the mouse is scrolled
         *
         * \param Uint32 <u>direction</u>: Either <i>SDL_MOUSEWHEEL_NORMAL</i> for usual behavior
         *        or <i>SDL_MOUSEWHEEL_FLIPPED</i> where x & y must be flipped
         * \param Sint32 <u>x</u>: How much the wheel scrolled horizontally
         * \param Sint32 <u>y</u>: How much the wheel scrolled vertically
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        bool MouseWheelEventHandler(Uint32 direction, Sint32 x, Sint32 y, Uint32 which) {
            return true;
        }

        /** \brief The default event handler for an SDL_USEREVENT (i.e. user-defined event).
         *
         * \param Sint32 <u>code</u>: The UserEvent code
         * \param void *<u>data1</u>: Pointer to UserEvent-related data
         * \param void *<u>data2</u>: Pointer to UserEvent-related data
         * \return bool TRUE to continue running the application
         *
         */
        bool UserEventHandler(Sint32 code, void *data1, void *data2) {
            return true;
        }

    }
}

#endif // EVENTS_HPP
