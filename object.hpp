#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "base.hpp"
#include "math.hpp"
#include "events.hpp"

namespace GenEx {
    /** \brief The base object class for GenEx
     */
    class Object {
    public:
        Math::Vector3 position; // where to render the object
        Math::Vector3 anchor_point; // anchor point to position the object

        Math::Vector3 offset; // translation values
        Math::Vector3 rotation; // rotation values
        Math::Vector3 scale; // scaling values

        Math::Vector3 move_vector;
        Math::Vector3 angle_vector;

    private:
        Uint64 instance_id;
        Events::EventHandlers event_handlers;

    public:
        /** \brief Constructor with a struct containing event handlers to use.
         *
         * \param Object::EventHandlers <u>evt_handlers</u>: Struct of event handlers for this
         *        Object to use
         *
         */
        Object(Events::EventHandlers evt_handlers) :
                   position({0, 0, 0}), anchor_point({0.5, 0.5, 0.5}),
                   offset({0, 0, 0}), rotation({0, 0, 0}), scale({0, 0, 0}),
                   move_vector({0, 0, 0}), angle_vector({0, 0, 0}),
                   event_handlers(evt_handlers) {
            event_handlers.init(this);
        }

        /** \brief Empty constructor for GenEx Objects. Loads the object with default
         *        event handlers.
         */
        Object() : Object(Events::GenerateEventHandlerStruct()) { }

        /** \brief Copy constructor for GenEx Objects.
         *
         * \param Object &<u>other</u>: Reference to an Object to copy
         *
         */
        Object(const Object &other) : Object(other.event_handlers) { }

        /** \brief Copy constructor for GenEx Objects.
         *
         * \param Object &<u>other</u>: Reference to an Object to copy
         *
         */
        Object(Object &&other) : Object(other.event_handlers) { }

        /** \brief Destructor for GenEx Objects. Can be overwritten in subclass.
         */
        virtual ~Object() {
            event_handlers.destroy(this);
        }

        virtual void render(SDL_Renderer *target) { }

        virtual bool update(double elapsed) {
            position += move_vector  * (60.0 / elapsed);
            rotation += angle_vector * (60.0 / elapsed);
            return event_handlers.update(this, elapsed);
        }

        virtual bool targetreset() {
            return event_handlers.targetreset(this);
        }

        virtual bool windowevent(Uint8 event, Sint32 data1, Sint32 data2) {
            return event_handlers.windowevent(this, event, data1, data2);
        }

        virtual bool keydown(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            return event_handlers.keydown(this, key, scancode, repeat);
        }

        virtual bool keyup(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            return event_handlers.keyup(this, key, scancode, repeat);
        }

        virtual bool textediting(char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                 Sint32 start, Sint32 length) {
            return event_handlers.textediting(this, text, start, length);
        }

        virtual bool textinput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
            return event_handlers.textinput(this, text);
        }

        virtual bool mousedown(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
            return event_handlers.mousedown(this, x, y, button, clicks, which);
        }

        virtual bool mouseup(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
            return event_handlers.mouseup(this, x, y, button, clicks, which);
        }

        virtual bool mousemotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel,
                                 bool buttons[5], Uint32 which) {
            return event_handlers.mousemotion(this, x, y, xrel, yrel, buttons, which);
        }

        virtual bool mousewheel(bool flipped, Sint32 x, Sint32 y, Uint32 which) {
            return event_handlers.mousewheel(this, flipped, x, y, which);
        }

        virtual bool clipboardupdate(char text[]) {
            return event_handlers.clipboardupdate(this, text);
        }

        virtual bool filedrop(std::string filename) {
            return event_handlers.filedrop(this, filename);
        }

        virtual bool textdrop(char text[]) {
            return event_handlers.textdrop(this, text);
        }

        virtual bool begindrop() {
            return event_handlers.begindrop(this);
        }

        virtual bool completedrop() {
            return event_handlers.completedrop(this);
        }

        virtual bool jaxis(SDL_JoystickID joystick_id, Uint8 axis, Sint16 value) {
            return event_handlers.jaxis(this, joystick_id, axis, value);
        }

        virtual bool jball(SDL_JoystickID joystick_id, Uint8 ball, Sint16 x, Sint16 y) {
            return event_handlers.jball(this, joystick_id, ball, x, y);
        }

        virtual bool jhat(SDL_JoystickID joystick_id, Uint8 hat, Uint8 value) {
            return event_handlers.jhat(this, joystick_id, hat, value);
        }

        virtual bool jbtndown(SDL_JoystickID joystick_id, Uint8 button) {
            return event_handlers.jbtndown(this, joystick_id, button);
        }

        virtual bool jbtnup(SDL_JoystickID joystick_id, Uint8 button) {
            return event_handlers.jbtnup(this, joystick_id, button);
        }

        virtual bool caxis(SDL_JoystickID controller_id, Uint8 axis, Sint16 value) {
            return event_handlers.caxis(this, controller_id, axis, value);
        }

        virtual bool cbtndown(SDL_JoystickID controller_id, Uint8 button) {
            return event_handlers.cbtndown(this, controller_id, button);
        }

        virtual bool cbtnup(SDL_JoystickID controller_id, Uint8 button) {
            return event_handlers.cbtnup(this, controller_id, button);
        }

        virtual bool fingerdown(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                float pressure) {
            return event_handlers.fingerdown(this, touch_id, finger_id, x, y, pressure);
        }

        virtual bool fingerup(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                              float pressure) {
            return event_handlers.fingerup(this, touch_id, finger_id, x, y, pressure);
        }

        virtual bool fingermotion(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                  float dx, float dy, float pressure) {
            return event_handlers.fingermotion(this, touch_id, finger_id, x, y, dx, dy, pressure);
        }

        virtual bool gesturerecord(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                   Uint32 num_fingers, float x, float y) {
            return event_handlers.gesturerecord(this, touch_id, gesture_id, num_fingers, x, y);
        }

        virtual bool gestureperform(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                    Uint32 num_fingers, float x, float y, float error) {
            return event_handlers.gestureperform(this, touch_id, gesture_id, num_fingers, x, y,
                                                 error);
        }

        virtual bool multigesture(SDL_TouchID touch_id, Uint16 num_fingers, float x, float y,
                                  float d_theta, float d_dist) {
            return event_handlers.multigesture(this, touch_id, num_fingers, x, y, d_theta, d_dist);
        }

        virtual bool userevent(Sint32 code, void *data1, void *data2) {
            return event_handlers.userevent(this, code, data1, data2);
        }
    };
}

#endif // OBJECTS_HPP
