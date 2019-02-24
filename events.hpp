/**
 * \file events.hpp
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
 * The header file for event typedefs and default event handler functions.
 *
 */

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "base.hpp"

namespace GenEx {
    namespace Events {

// --- EVENT HANDLER TYPEDEFS ---------------------------------------------------------------------
// ------ OBJECT-RELATED TYPEDEFS -----------------------------------------------------------------

        /** \brief Typedef for an event handler for when something is initialized
         */
        typedef void (*InitEvent)(GenEx::Object*);

        /** \brief Typedef for an event handler for when something is destroyed
         */
        typedef void (*DestroyEvent)(GenEx::Object*);

        /** \brief Typedef for an event handler for rendering objects
         */
        typedef void (*RenderEvent)(GenEx::Object*, SDL_Renderer*, int, int, int);

        /** \brief Typedef for an event handler for when sprites/graphics are updated
         */
        typedef bool (*UpdateEvent)(GenEx::Object*, double);

        /** \brief Typedef for an event handler for an SDL_RENDER_TARGETS_RESET or
         *        SDL_RENDER_DEVICE_RESET event
         */
        typedef bool (*TargetResetEvent)(GenEx::Object*);

        /** \brief Typedef for an event handler for an SDL_WINDOWEVENT event
         */
        typedef bool(*WindowEvent)(GenEx::Object*, Uint8, Sint32, Sint32);

// ------ KEYBOARD-RELATED TYPEDEFS ---------------------------------------------------------------

        /** \brief Typedef for an event handler for an SDL_KEYDOWN event
         */
        typedef bool (*KeyDownEvent)(GenEx::Object*, SDL_Keycode, SDL_Scancode, Uint16, Uint8);

        /** \brief Typedef for an event handler for an SDL_KEYUP event
         */
        typedef bool (*KeyUpEvent)(GenEx::Object*, SDL_Keycode, SDL_Scancode, Uint16, Uint8);

        /** \brief Typedef for an event handler for an SDL_TEXTEDITING event
         */
        typedef bool (*TextEditingEvent)(GenEx::Object*, char[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                         Sint32, Sint32);

        /** \brief Typedef for an event handler for an SDL_TEXTINPUT event
         */
        typedef bool (*TextInputEvent)(GenEx::Object*, char[SDL_TEXTINPUTEVENT_TEXT_SIZE]);

// ------ EXTERNAL INPUT-RELATED TYPEDES ----------------------------------------------------------

        /** \brief Typedef for an event handler for an SDL_CLIPBOARDUPDATE event
         */
        typedef bool (*ClipboardUpdateEvent)(GenEx::Object*, char[]);

        /** \brief Typedef for an event handler for an SDL_DROPFILE event
         */
        typedef bool (*DropFileEvent)(GenEx::Object*, std::string);

        /** \brief Typedef for an event handler for an SDL_DROPTEXT event
         */
        typedef bool (*DropTextEvent)(GenEx::Object*, char[]);

        /** \brief Typedef for an event handler for an SDL_DROPBEGIN event
         */
        typedef bool (*DropBeginEvent)(GenEx::Object*);

        /** \brief Typedef for an event handler for an SDL_DROPCOMPLETE event
         */
        typedef bool (*DropCompleteEvent)(GenEx::Object*);

// ------ MOUSE-RELATED TYPEDEFS ------------------------------------------------------------------

        /** \brief Typedef for an event handler for an SDL_MOUSEBUTTONDOWN event
         */
        typedef bool(*MouseButtonDownEvent)(GenEx::Object*, Sint32, Sint32, Uint8, Uint8, Uint32);

        /** \brief Typedef for an event handler for an SDL_MOUSEBUTTONUP event
         */
        typedef bool(*MouseButtonUpEvent)(GenEx::Object*, Sint32, Sint32, Uint8, Uint8, Uint32);

        /** \brief Typedef for an event handler for an SDL_MOUSEMOTION event
         */
        typedef bool(*MouseMotionEvent)(GenEx::Object*, Sint32, Sint32, Sint32,
                                        Sint32, bool[5], Uint32);

        /** \brief Typedef for an event handler for an SDL_MOUSEWHEEL event
         */
        typedef bool(*MouseWheelEvent)(GenEx::Object*, bool, Sint32, Sint32, Uint32);

// ------ JOYSTICK-RELATED TYPEDEFS ---------------------------------------------------------------

        /** \brief Typedef for an event handler for an SDL_JOYAXISMOTION event
         */
        typedef bool(*JoystickAxisEvent)(GenEx::Object*, SDL_JoystickID, Uint8, Sint16);

        /** \brief Typedef for an event handler for an SDL_JOYBALLMOTION event
         */
        typedef bool(*JoystickTrackballEvent)(GenEx::Object*, SDL_JoystickID,
                                              Uint8, Sint16, Sint16);

        /** \brief Typedef for an event handler for an SDL_JOYHATMOTION event
         */
        typedef bool (*JoystickHatEvent)(GenEx::Object*, SDL_JoystickID, Uint8, Uint8);

        /** \brief Typedef for an event handler for an SDL_JOYBUTTONDOWN event
         */
        typedef bool (*JoystickButtonDownEvent)(GenEx::Object*, SDL_JoystickID, Uint8);

        /** \brief Typedef for an event handler for an SDL_JOYBUTTONUP event
         */
        typedef bool (*JoystickButtonUpEvent)(GenEx::Object*, SDL_JoystickID, Uint8);

// ------ GAME CONTROLLER-RELATED TYPEDEFS --------------------------------------------------------

        /** \brief Typedef for an event handler for an SDL_CONTROLLERAXISMOTION event
         */
        typedef bool(*ControllerAxisEvent)(GenEx::Object*, SDL_JoystickID, Uint8, Sint16);

        /** \brief Typedef for an event handler for an SDL_CONTROLLERBUTTONDOWN event
         */
        typedef bool(*ControllerButtonDownEvent)(GenEx::Object*, SDL_JoystickID, Uint8);

        /** \brief Typedef for an event handler for an SDL_CONTROLLERBUTTONUP event
         */
        typedef bool(*ControllerButtonUpEvent)(GenEx::Object*, SDL_JoystickID, Uint8);

// ------ TOUCHSCREEN-RELATED TYPEDEFS ------------------------------------------------------------

        /** \brief Typedef for an event handler for an SDL_FINGERDOWN event
         */
        typedef bool(*FingerDownEvent)(GenEx::Object*, SDL_TouchID, SDL_FingerID, float,
                                       float, float);

        /** \brief Typedef for an event handler for an SDL_FINGERUP event
         */
        typedef bool(*FingerUpEvent)(GenEx::Object*, SDL_TouchID, SDL_FingerID, float,
                                       float, float);

        /** \brief Typedef for an event handler for an SDL_FINGERMOTION event
         */
        typedef bool(*FingerMotionEvent)(GenEx::Object*, SDL_TouchID, SDL_FingerID, float,
                                       float, float, float, float);

        /** \brief Typedef for an event handler for an SDL_DOLLARRECORD event
         */
         typedef bool(*RecordGestureEvent)(GenEx::Object*, SDL_TouchID, SDL_GestureID, Uint32,
                                          float, float);

        /** \brief Typedef for an event handler for an SDL_DOLLARGESTURE event
         */
        typedef bool(*PerformGestureEvent)(GenEx::Object*, SDL_TouchID, SDL_GestureID, Uint32,
                                          float, float, float);

        /** \brief Typedef for an event handler for an SDL_MULTIGESTURE event
         */
        typedef bool(*MultiGestureEvent)(GenEx::Object*, SDL_TouchID, Uint16,
                                         float, float, float, float);

// ------ USER EVENT TYPEDEF ----------------------------------------------------------------------

        /** \brief Typedef for an event handler for an SDL_USEREVENT event
         */
        typedef bool(*UserEvent)(GenEx::Object*, Sint32, void*, void*);

// --- DEFAULT EVENT HANDLER FUNCTIONS ------------------------------------------------------------
// ------ OBJECT-RELATED FUNCTIONS ----------------------------------------------------------------

        /** \brief The default event handler for when objects are initialized.
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to the object to initialize
         *
         */
        inline void InitEventHandler(GenEx::Object *obj) { }

        /** \brief The default event handler for when objects are to be destroyed.
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to the object to destroy
         *
         */
        inline void DestroyEventHandler(GenEx::Object *obj) { }

        /** \brief The default event handler for when objects are to be rendered.
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to the object to destroy
         * \param SDL_Renderer *<u>target</u>: Pointer to a render target
         * \param int <u>offset_x</u>: Horizontal offset
         * \param int <u>offset_y</u>: Vertical offset
         * \param int <u>offset_z</u>: Depth offset
         *
         */
        inline void RenderEventHandler(GenEx::Object *obj, SDL_Renderer *target,
                                       int offset_x, int offset_y, int offset_z) { }

        /** \brief A minimal event handler for when objects need to be updated.
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to the object to update
         * \param double <u>elapsed</u>: How much time has elapsed from the previous frame
         * \return bool TRUE to continue running the application
         *
         */
        inline bool UpdateEventHandler(GenEx::Object *obj, double elapsed) {
            return true;
        }

        /** \brief The default event handler for an SDL_RENDER_TARGETS_RESET event or an
         *        SDL_RENDER_DEVICE_RESET (and all texture-related values in the object need
         *        to be reset).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \return bool TRUE to continue running the application
         *
         */
        inline bool TargetResetEventHandler(GenEx::Object *obj) {
            return true;
        }

        /** \brief The default event handler for an SDL_WINDOWEVENT.
         *
         * \param GenEx::Object *<u></u>: Pointer to an object
         * \param Uint8 <u>event</u>: The event ID
         * \param Sint32 <u>data1</u>: Event-dependent data
         * \param Sint32 <u>data2</u>: Event-dependent data
         * \return bool TRUE to continue running the application
         *
         */
        inline bool WindowEventHandler(GenEx::Object *obj, Uint8 event, Sint32 data1,
                                       Sint32 data2) {
            return true;
        }

// ------ KEYBOARD-RELATED FUNCTIONS --------------------------------------------------------------

        /** \brief The default event handler for an SDL_KEYDOWN event (i.e. when a key is
         *        first pressed).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_Keycode <u>key</u>: The keycode/key that was pressed
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was pressed
         * \param Uint16 <u>mod</u>: Active key modifiers
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        inline bool KeyDownEventHandler(GenEx::Object *obj, SDL_Keycode key, SDL_Scancode scancode,
                                        Uint16 mod, Uint8 repeat) {
            return true;
        }

        /** \brief The default event handler for an SDL_KEYUP event (i.e. when a key is
         *        released after being pressed).
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was released
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was released
         * \param Uint16 <u>mod</u>: Active key modifiers
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        inline bool KeyUpEventHandler(GenEx::Object *obj, SDL_Keycode key, SDL_Scancode scancode,
                                      Uint16 mod, Uint8 repeat) {
            return true;
        }

        /** \brief The default event handler for an SDL_TEXTEDITING event (i.e. when text
         *        composition has started or changed)
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param char <u>text</u>[32]: The event text in UTF-8 encoding
         * \param Sint32 <u>start</u>: The cursor position within the composition
         * \param Sint32 <u>length</u>: The length of selected text in the composition, if any
         * \return bool TRUE to continue running the application
         *
         */
        inline bool TextEditingEventHandler(GenEx::Object *obj,
                                            char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                            Sint32 start, Sint32 length) {
            return true;
        }

        /** \brief The default event handler for an SDL_TEXTINPUT event (i.e. when text
         *        composition has been committed  or non-IME text input is given)
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param char <u>text</u>[32]: The vent text in UTF-8 encoding
         * \return bool TRUE to continue running the application
         *
         */
        inline bool TextInputEventHandler(GenEx::Object *obj,
                                          char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
            return true;
        }

// ------ EXTERNAL INPUT-RELATED FUNCTIONS ---------------------------------------------------------

        /** \brief The default event handler for an SDL_CLIPBOARDUPDATE event (i.e. when the
         *        clipboard has been updated/gets new data)
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param char <u>text</u>[]: The text copied from the clipboard
         * \return bool TRUE to continue running the application
         *
         */
        inline bool ClipboardUpdateEventHandler(GenEx::Object *obj, char text[]) {
            return true;
        }

        /** \brief The default event handler for an SDL_DROPFILE event (i.e. when a file is dropped
         *        into a window).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param std::string <u>filename</u>: Name of the file to open
         * \return bool TRUE to continue running the application
         *
         */
        inline bool DropFileEventHandler(GenEx::Object *obj, std::string filename) {
            return true;
        }

        /** \brief The default event handler for an SDL_DROPTEXT event (i.e. when text is dropped
         *        into a window).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param char <u>text</u>[]: Text that was dropped
         * \return bool TRUE to continue running the application
         *
         */
        inline bool DropTextEventHandler(GenEx::Object *obj, char text[]) {
            return true;
        }

        /** \brief The default event handler for an SDL_DROPBEGIN event (i.e. when a drag-and-drop
         *        has begun).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \return bool TRUE to continue running the application
         *
         */
        inline bool DropBeginEventHandler(GenEx::Object *obj) {
            return true;
        }

        /** \brief The default event handler for an SDL_DROPCOMPLETE event (i.e. when a drag-and-
         *        drop has finished).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \return bool TRUE to continue running the application
         *
         */
        inline bool DropCompleteEventHandler(GenEx::Object *obj) {
            return true;
        }

// ------ MOUSE-RELATED FUNCTIONS -----------------------------------------------------------------

        /** \brief The default event handler for an SDL_MOUSEBUTTONDOWN event (i.e. when a
         *        button on the mouse is clicked).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param Sint32 <u>x</u>: The relative X-position of the mouse
         * \param Sint32 <u>y</u>: The relative Y-position of the mouse
         * \param Uint8 <u>button</u>: The button on the mouse that was clicked
         * \param Uint8 <u>clicks</u>: How many times the mouse was clicked (e.g. 2 for
         *        double-click)
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        inline bool MouseButtonDownEventHandler(GenEx::Object *obj, Sint32 x, Sint32 y,
                                                Uint8 button, Uint8 clicks, Uint32 which) {
            return true;
        }

        /** \brief The default event handler for an SDL_MOUSEBUTTONUP event (i.e. when a
         *        button on the mouse is released after being clicked).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param Sint32 <u>x</u>: The relative X-position of the mouse
         * \param Sint32 <u>y</u>: The relative Y-position of the mouse
         * \param Uint8 <u>button</u>: The button on the mouse that was released
         * \param Uint8 <u>clicks</u>: How many times the mouse was released (e.g. 2 for
         *        double-click)
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        inline bool MouseButtonUpEventHandler(GenEx::Object *obj, Sint32 x, Sint32 y, Uint8 button,
                                              Uint8 clicks, Uint32 which) {
            return true;
        }

        /** \brief The default event handler for an SDL_MOUSEMOTION event (i.e. when the
         *        mouse moves across the screen).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
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
        inline bool MouseMotionEventHandler(GenEx::Object *obj, Sint32 x, Sint32 y, Sint32 xrel,
                                            Sint32 yrel, bool buttons[5], Uint32 which) {
            return true;
        }

        /** \brief The default event handler for an SDL_MOUSEWHEEL event (i.e. when the scroll
         *        wheel on the mouse is scrolled).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param bool <u>flipped</u>: TRUE if the SDL_MOUSEWHEEL event's direction =
         *        SDL_MOUSEWHEEL_FLIPPED
         * \param Sint32 <u>x</u>: How much the wheel scrolled horizontally
         * \param Sint32 <u>y</u>: How much the wheel scrolled vertically
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        inline bool MouseWheelEventHandler(GenEx::Object *obj, bool flipped, Sint32 x, Sint32 y,
                                           Uint32 which) {
            return true;
        }

// ------ JOYSTICK-RELATED FUNCTIONS --------------------------------------------------------------

        /** \brief The default event handler for an SDL_JOYAXISMOTION event (i.e. when an axis
         *        on a joystick is moved).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>axis</u>: The axis on the joystick whose value is being given
         * \param Sint16 <u>value</u>: The value of the axis
         * \return bool TRUE to continue running the application
         *
         */
        inline bool JoystickAxisEventHandler(GenEx::Object *obj, SDL_JoystickID joystick_id,
                                             Uint8 axis, Sint16 value) {
            return true;
        }

        /** \brief The default event handler for an SDL_JOYBALLMOTION event (i.e. when a trackball
         *        on a joystick is moved).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>ball</u>: The trackball on the joystick whose values are being given
         * \param Sint16 <u>x</u>: Relative horizontal motion of the trackball
         * \param Sint16 <u>y</u>: Relative vertical motion of the trackball
         * \return bool TRUE to continue running the application
         *
         */
        inline bool JoystickTrackballEventHandler(GenEx::Object *obj, SDL_JoystickID joystick_id,
                                                  Uint8 ball, Sint16 x, Sint16 y) {
            return true;
        }

        /** \brief The default event handler for an SDL_JOYHATMOTION event (i.e. when a hat
         *        on a joystick is moved).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>hat</u>: The hat on the joystick whose value is being given
         * \param Uint8 <u>value</u>: The value of the hat
         * \return bool TRUE to continue running the application
         *
         */
        inline bool JoystickHatEventHandler(GenEx::Object *obj, SDL_JoystickID joystick_id,
                                            Uint8 hat, Uint8 value) {
            return true;
        }

        /** \brief The default event handler for an SDL_JOYBUTTONDOWN event (i.e. when a button
         *        on a joystick is pressed).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>button</u>: The button on the joystick being pressed
         * \return bool TRUE to continue running the application
         *
         */
        inline bool JoystickButtonDownEventHandler(GenEx::Object *obj, SDL_JoystickID joystick_id,
                                                   Uint8 button) {
            return true;
        }

        /** \brief The default event handler for an SDL_JOYBUTTONUP event (i.e. when a button
         *        on a joystick is released).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>button</u>: The button on the joystick being released
         * \return bool TRUE to continue running the application
         *
         */
        inline bool JoystickButtonUpEventHandler(GenEx::Object *obj, SDL_JoystickID joystick_id,
                                                 Uint8 button) {
            return true;
        }

// ------ GAME CONTROLLER-RELATED FUNCTIONS -------------------------------------------------------

        /** \brief The default event handler for an SDL_CONTROLLERAXISMOTION event (i.e. when an
         *        axis on a game controller is moved).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>axis</u>: The axis on the controller whose value is being given
         * \param Sint16 <u>value</u>: The value of the axis
         * \return bool TRUE to continue running the application
         *
         */
        inline bool ControllerAxisEventHandler(GenEx::Object *obj, SDL_JoystickID controller_id,
                                               Uint8 axis, Sint16 value) {
            return true;
        }

        /** \brief The default event handler for an SDL_CONTROLLERBUTTONDOWN event (i.e. when a
         *        button on a game controller is pressed).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>button</u>: The button on the controller being pressed
         * \return bool TRUE to continue running the application
         *
         */
        inline bool ControllerButtonDownEventHandler(GenEx::Object *obj,
                                                     SDL_JoystickID controller_id,
                                                     Uint8 button) {
            return true;
        }

        /** \brief The default event handler for an SDL_CONTROLLERBUTTONUP event (i.e. when a
         *        button on a game controller is released).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>button</u>: The button on the controller being released
         * \return bool TRUE to continue running the application
         *
         */
        inline bool ControllerButtonUpEventHandler(GenEx::Object *obj,
                                                   SDL_JoystickID joystick_id,
                                                   Uint8 button) {
            return true;
        }

// ------ TOUCHSCREEN-RELATED FUNCTIONS -----------------------------------------------------------

        /** \brief The default event handler for an SDL_FINGERDOWN event (i.e. when, on a
         *        touchscreen, the user presses their finger down somewhere on-screen).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param SDL_FingerID <u>finger_id</u>: The ID of the finger being used
         * \param float <u>x</u>: The X-position of the touch in screen space, normalized from
         *        0.0f to 1.0f
         * \param float <u>y</u>: The Y-position of the touch in screen space, normalized from
         *        0.0f to 1.0f
         * \param float <u>pressure</u>: The amount of pressure the finger is applying, normalized
         *        from 0.0f to 1.0f
         * \return bool TRUE to continue running the application
         *
         */
        inline bool FingerDownEventHandler(GenEx::Object *obj, SDL_TouchID touch_id,
                                           SDL_FingerID finger_id, float x, float y,
                                           float pressure) {
            return true;
        }

        /** \brief The default event handler for an SDL_FINGERUP event (i.e. when, on a
         *        touchscreen, the user lifts their finger off the screen).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param SDL_FingerID <u>finger_id</u>: The ID of the finger being used
         * \param float <u>x</u>: The X-position of the touch in screen space, normalized from
         *        0.0f to 1.0f
         * \param float <u>y</u>: The Y-position of the touch in screen space, normalized from
         *        0.0f to 1.0f
         * \param float <u>pressure</u>: The amount of pressure the finger is applying, normalized
         *        from 0.0f to 1.0f
         * \return bool TRUE to continue running the application
         *
         */
        inline bool FingerUpEventHandler(GenEx::Object *obj, SDL_TouchID touch_id,
                                         SDL_FingerID finger_id, float x, float y,
                                         float pressure) {
            return true;
        }

        /** \brief The default event handler for an SDL_FINGERMOTION event (i.e. when, on a
         *        touchscreen, the user moves their finger around the screen).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param SDL_FingerID <u>finger_id</u>: The ID of the finger being used
         * \param float <u>x</u>: The X-position of the touch in screen space, normalized from
         *        0.0f to 1.0f
         * \param float <u>y</u>: The Y-position of the touch in screen space, normalized from
         *        0.0f to 1.0f
         * \param float <u>dx</u>: The relative X-movement of the touch, normalized from 0.0f
         *        to 1.0f
         * \param float <u>dy</u>: The relative Y-movement of the touch, normalized from 0.0f
         *        to 1.0f
         * \param float <u>pressure</u>: The amount of pressure the finger is applying, normalized
         *        from 0.0f to 1.0f
         * \return bool TRUE to continue running the application
         *
         */
        inline bool FingerMotionEventHandler(GenEx::Object *obj, SDL_TouchID touch_id,
                                             SDL_FingerID finger_id, float x, float y,
                                             float dx, float dy, float pressure) {
            return true;
        }

        /** \brief The default event handler for an SDL_DOLLARRECORD event (i.e. when the
         *        application is recording a new gesture).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param SDL_GestureID <u>gesture_id</u>: The ID of the gesture being recorded
         * \param Uint32 <u>num_fingers</u>: The number of fingers used to draw the stroke
         * \param float <u>x</u>: The normalized horizontal center of the gesture (0.0f-1.0f)
         * \param float <u>y</u>: The normalized vertical center of the gesture (0.0f-1.0f)
         * \return bool TRUE to continue running the application
         *
         */
        inline bool RecordGestureEventHandler(GenEx::Object *obj, SDL_TouchID touch_id,
                                              SDL_GestureID gesture_id, Uint32 num_fingers,
                                              float x, float y) {
            return true;
        }

        /** \brief The default event handler for an SDL_DOLLARGESTURE event (i.e. when the user
         *        is performing a gesture).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param SDL_GestureID <u>gesture_id</u>: The ID of a gesture
         * \param Uint32 <u>num_fingers</u>: The number of fingers used to draw the stroke
         * \param float <u>x</u>: The normalized horizontal center of the gesture (0.0f-1.0f)
         * \param float <u>y</u>: The normalized vertical center of the gesture (0.0f-1.0f)
         * \param float <u>error</u>: The percent error between the gesture template and the
         *        actual performed gesture (lower is better)
         * \return bool TRUE to continue running the application
         *
         */
        inline bool PerformGestureEventHandler(GenEx::Object *obj, SDL_TouchID touch_id,
                                              SDL_GestureID gesture_id, Uint32 num_fingers,
                                              float x, float y, float error) {
            return true;
        }

        /** \brief The default event handler for an SDL_MULTIGESTURE event (i.e. when the user
         *        is performing a multi-finger gesture, such as a pinch, swipe, or rotate).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param Uint16 <u>num_fingers</u>: The number of fingers used in this gesture
         * \param float <u>x</u>: The normalized horizontal center of the gesture (0.0f-1.0f)
         * \param float <u>y</u>: The normalized vertical center of the gesture (0.0f-1.0f)
         * \param float <u>d_theta</u>: The amount of rotation that occured during this motion
         * \param float <u>d_dist</u>: The amount of pinching that occured during this motion
         * \return bool TRUE to continue running the application
         *
         */
        inline bool MultiGestureEventHandler(GenEx::Object *obj, SDL_TouchID touch_id,
                                             Uint16 num_fingers,float x, float y,
                                             float d_theta, float d_dist) {
            return true;
        }

// ------ USER EVENT FUNCTION ---------------------------------------------------------------------

        /** \brief The default event handler for an SDL_USEREVENT (i.e. user-defined event).
         *
         * \param GenEx::Object *<u>obj</u>: Pointer to an object
         * \param Sint32 <u>code</u>: The UserEvent code
         * \param void *<u>data1</u>: Pointer to UserEvent-related data
         * \param void *<u>data2</u>: Pointer to UserEvent-related data
         * \return bool TRUE to continue running the application
         *
         */
        inline bool UserEventHandler(GenEx::Object *obj, Sint32 code, void *data1, void *data2) {
            return true;
        }

// --- EVENT HANDLERS STRUCT ----------------------------------------------------------------------

        /** \brief A struct containing event handlers for use by GenEx Objects
         */
        struct EventHandlers {
            /** Initialization event
             * \param GenEx::object *<u>obj</u>
             */
            InitEvent    init;
            /** Destroy event
             * \param GenEx::object *<u>obj</u>
             */
            DestroyEvent destroy;
            /** Render event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_Renderer *<u>renderer</u>
             * \param int <u>offset_x</u>
             * \param int <u>offset_y</u>
             * \param int <u>offset_z</u>
             */
            RenderEvent  render;
            /** Update event
             * \param GenEx::Object *<u>obj</u>
             * \param double elapsed
             */
            UpdateEvent  update;
            /** Destroy event
             * \param GenEx::object *<u>obj</u>
             * \param Uint8 <u>event</u>
             * \param Sint32 <u>data1</u>
             * \param Sint32 <u>data2</u>
             */
            WindowEvent      windowevent;
            /** Target reset event
             * \param GenEx::Object *<u>obj</u>
             * \param double elapsed
             */
            TargetResetEvent targetreset;

            /** Key down event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_Keycode <u>key</u>
             * \param SDL_Scancode <u>scancode</u>
             * \param Uint16 <u>mod</u>
             * \param Uint8 <u>repeat</u>
             */
            KeyDownEvent     keydown;
            /** Key up event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_Keycode <u>key</u>
             * \param SDL_Scancode <u>scancode</u>
             * \param Uint16 <u>mod</u>
             * \param Uint8 <u>repeat</u>
             */
            KeyUpEvent       keyup;
            /** Text editing event
             * \param GenEx::Object *<u>obj</u>
             * \param char <u>text</u>[32]
             * \param Sint32 <u>start</u>
             * \param Sint32 <u>length</u>
             */
            TextEditingEvent textediting;
            /** Text input event
             * \param GenEx::Object *<u>obj</u>
             * \param char <u>text</u>[32]
             */
            TextInputEvent   textinput;

            /** Mouse button down event
             * \param GenEx::Object *<u>obj</u>
             * \param Sint32 <u>x</u>
             * \param Sint32 <u>y</u>
             * \param Uint8 <u>button</u>
             * \param Uint8 <u>clicks</u>
             * \param Uint32 <u>which</u>
             */
            MouseButtonDownEvent mousedown;
            /** Mouse button up event
             * \param GenEx::Object *<u>obj</u>
             * \param Sint32 <u>x</u>
             * \param Sint32 <u>y</u>
             * \param Uint8 <u>button</u>
             * \param Uint8 <u>clicks</u>
             * \param Uint32 <u>which</u>
             */
            MouseButtonUpEvent   mouseup;
            /** Mouse motion event
             * \param GenEx::Object *<u>obj</u>
             * \param Sint32 <u>x</u>
             * \param Sint32 <u>y</u>
             * \param Sint32 <u>xrel</u>
             * \param Sint32 <u>yrel</u>
             * \param bool <u>buttons</u>[5]
             * \param Uint32 <u>which</u>
             */
            MouseMotionEvent     mousemotion;
            /** Mouse wheel event
             * \param GenEx::Object *<u>obj</u>
             * \param bool <u>flipped</u>
             * \param Sint32 <u>x</u>
             * \param Sint32 <u>y</u>
             * \param Uint32 <u>which</u>
             */
            MouseWheelEvent      mousewheel;

            /** Clipboard update event
             * \param GenEx::Object *<u>obj</u>
             * \param char text[]
             */
            ClipboardUpdateEvent clipboardupdate;
            /** Drop file event
             * \param GenEx::Object *<u>obj</u>
             * \param std::string filename
             */
            DropFileEvent        filedrop;
            /** Drop text event
             * \param GenEx::Object *<u>obj</u>
             * \param char text[]
             */
            DropTextEvent        textdrop;
            /** Drop begin event
             * \param GenEx::Object *<u>obj</u>
             */
            DropBeginEvent       begindrop;
            /** Drop complete event
             * \param GenEx::Object *<u>obj</u>
             */
            DropCompleteEvent    completedrop;

            /** Joystick axis motion event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>joystick_id</u>
             * \param Uint8 <u>axis</u>
             * \param Sint16 <u>value</u>
             */
            JoystickAxisEvent       jaxis;
            /** Joystick trackball motion event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>joystick_id</u>
             * \param Uint8 <u>ball</u>
             * \param Sint16 <u>x</u>
             * \param Sint16 <u>y</u>
             */
            JoystickTrackballEvent  jball;
            /** Joystick hat motion event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>joystick_id</u>
             * \param Uint8 <u>hat</u>
             * \param Uint8 <u>value</u>
             */
            JoystickHatEvent        jhat;
            /** Joystick button down event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>joystick_id</u>
             * \param Uint8 <u>button</u>
             */
            JoystickButtonDownEvent jbtndown;
            /** Joystick button up event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>joystick_id</u>
             * \param Uint8 <u>button</u>
             */
            JoystickButtonUpEvent   jbtnup;

            /** Controller axis motion event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>controller_id</u>
             * \param Uint8 <u>axis</u>
             * \param Sint16 <u>value</u>
             */
            ControllerAxisEvent       caxis;
            /** Controller button down event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>controller_id</u>
             * \param Uint8 <u>button</u>
             */
            ControllerButtonDownEvent cbtndown;
            /** Controller button up event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_JoystickID <u>controller_id</u>
             * \param Uint8 <u>button</u>
             */
            ControllerButtonUpEvent   cbtnup;

            /** Finger down event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_TouchID <u>touch_id</u>
             * \param SDL_FingerID <u>finger_id</u>
             * \param float <u>x</u>
             * \param float <u>y</u>
             * \param float <u>pressure</u>
             */
            FingerDownEvent     fingerdown;
            /** Finger up event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_TouchID <u>touch_id</u>
             * \param SDL_FingerID <u>finger_id</u>
             * \param float <u>x</u>
             * \param float <u>y</u>
             * \param float <u>pressure</u>
             */
            FingerUpEvent       fingerup;
            /** Finger motion event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_TouchID <u>touch_id</u>
             * \param SDL_FingerID <u>finger_id</u>
             * \param float <u>x</u>
             * \param float <u>y</u>
             * \param float <u>dx</u>
             * \param float <u>dy</u>
             * \param float <u>pressure</u>
             */
            FingerMotionEvent   fingermotion;
            /** Gesture record event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_TouchID <u>touch_id</u>
             * \param SDL_GestureID <u>gesture_id</u>
             * \param Uint32 <u>num_fingers</u>
             * \param float <u>x</u>
             * \param float <u>y</u>
             */
            RecordGestureEvent  gesturerecord;
            /** Gesture perform event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_TouchID <u>touch_id</u>
             * \param SDL_GestureID <u>gesture_id</u>
             * \param Uint32 <u>num_fingers</u>
             * \param float <u>x</u>
             * \param float <u>y</u>
             * \param float <u>error</u>
             */
            PerformGestureEvent gestureperform;
            /** Multi-gesture event
             * \param GenEx::Object *<u>obj</u>
             * \param SDL_TouchID <u>touch_id</u>
             * \param Uint16 <u>num_fingers</u>
             * \param float <u>x</u>
             * \param float <u>y</u>
             * \param float <u>d_theta</u>
             * \param float <u>d_dist</u>
             */
            MultiGestureEvent   multigesture;

            /** User event
             * \param GenEx::Object *<u>obj</u>
             * \param Sint32 <u>code</u>
             * \param void *<u>data1</u>
             * \param void *<u>data2</u>
             */
            UserEvent userevent;
        };

        /** \brief Generates the default event handlers structure for new GenEx Objects.
         *
         * \return EventHandlers Struct containing the default GenEx event handlers
         *
         */
        EventHandlers GenerateEventHandlerStruct();
    }
}

#endif // EVENTS_HPP
