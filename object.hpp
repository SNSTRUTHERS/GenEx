/**
 * \file object.hpp
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
 * The header file for defining the base GenEx Object and Layer classes.
 *
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "base.hpp"
#include "events.hpp"

namespace GenEx {

// --- OBJECT CLASS -------------------------------------------------------------------------------

    /** \brief The base object class for GenEx.
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
        static Uint64 _num_instances;
        bool dead = false;

    protected:
        Events::EventHandlers event_handlers;

    public:
// ------ OBJECT CONSTRUCTORS ---------------------------------------------------------------------

        /** \brief Constructor with a struct containing event handlers to use.
         *
         * \param Object::EventHandlers <u>evt_handlers</u>: Struct of event handlers for this
         *        Object to use
         *
         */
        Object(Events::EventHandlers evt_handlers);

        /** \brief Empty constructor for GenEx Objects. Loads the object with default
         *        event handlers.
         */
        Object();

        /** \brief Copy constructor for GenEx Objects.
         *
         * \param Object &<u>other</u>: Reference to an Object to copy
         *
         */
        Object(const Object &other);

        /** \brief Move constructor for GenEx Objects.
         *
         * \param Object &<u>other</u>: Reference to an Object to copy
         *
         */
        Object(Object &&other);

// ------ OBJECT OPERATORS ------------------------------------------------------------------------

        /** \brief Copy assignment for objects.
         *
         * \param Object &<u>other</u>: Reference to another object
         */
        Object &operator= (const Object &other);

        /** \brief Move assignment for objects.
         *
         * \param Object &<u>other</u>: Reference to another object
         */
        Object &operator= (Object &&other);

// ------ OBJECT FUNCTIONS ------------------------------------------------------------------------

        /** \brief Destroy this object
         */
        virtual void destroy();

        /** \brief Destructor for GenEx Objects. Can be overwritten in subclass.
         */
        virtual ~Object();

        /** \brief Returns whether or not this object has been destroyed (i.e. is dead).
         *
         * \return bool TRUE if the object has been destroyed
         *
         */
        bool is_dead();

        /** \brief Gets the unique identifier for this object.
         *
         * \return Uint64 This object's ID
         *
         */
        Uint64 get_id();

        /** \brief Clones the object.
         *
         * \return Object A new object made based off the properties of this object
         *
         */
        virtual Object *clone();

// ------ OBJECT EVENT HANDLERS -------------------------------------------------------------------

        /** \brief Renders this object on to a target.
         *
         * \param SDL_Renderer *<u>target</u>: A target to render to
         * \param int <u>offset_x</u>: X offset from the usual rendering position
         * \param int <u>offset_y</u>: Y offset from the usual rendering position
         * \param int <u>offset_z</u>: Z offset from the usual rendering position
         *
         */
        virtual void render(SDL_Renderer *target, int offset_x, int offset_y, int offset_z);

        /** \brief Updates the object.
         *
         * \param double <elapsed>: The elapsed time since the previous frame in seconds
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool update(double elapsed);

        /** \brief Resets texture-related data in the object when a target resets.
         *
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool targetreset();

        /** \brief Manages window events.
         *
         * \param Uint8 <u>event</u>: The type of window event
         * \param Sint32 <u>data1</u>: Event-related data
         * \param Sint32 <u>data2</u>: Event-related data
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool windowevent(Uint8 event, Sint32 data1, Sint32 data2);

        /** \brief Manages keydown events.
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was pressed
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was pressed
         * \param Uint16 <u>mod</u>: Active key modifiers
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool keydown(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat);

        /** \brief Manages keyup events.
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was pressed
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was pressed
         * \param Uint16 <u>mod</u>: Active key modifiers
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool keyup(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat);

        /** \brief Manages textediting events.
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was pressed
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was pressed
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool textediting(char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                 Sint32 start, Sint32 length);

        /** \brief Manages textinput events.
         *
         * \param char <u>text</u>[32]: The vent text in UTF-8 encoding
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool textinput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]);

        /** \brief Managed mousedown events.
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
        virtual bool mousedown(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which);

        /** \brief Manages mouseup events.
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
        virtual bool mouseup(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which);

        /** \brief Manages mousemotion events.
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
        virtual bool mousemotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel,
                                 bool buttons[5], Uint32 which);

        /** \brief Manages mousewheel events.
         *
         * \param bool <u>flipped</u>: TRUE if the SDL_MOUSEWHEEL event's direction =
         *        SDL_MOUSEWHEEL_FLIPPED
         * \param Sint32 <u>x</u>: How much the wheel scrolled horizontally
         * \param Sint32 <u>y</u>: How much the wheel scrolled vertically
         * \param Uint32 <u>which</u>: The mouse instance ID or <i>SDL_TOUCH_MOUSEID</i>
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool mousewheel(bool flipped, Sint32 x, Sint32 y, Uint32 which);

        /** \brief Manages clipboardupdate events.
         *
         * \param char <u>text</u>[]: The text copied from the clipboard
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool clipboardupdate(char text[]);

        /** \brief Manages filedrop events.
         *
         * \param std::string <u>filename</u>: Name of the file to open
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool filedrop(std::string filename);

        /** \brief Manages textdrop events.
         *
         * \param char <u>text</u>[]: Text that was dropped
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool textdrop(char text[]);

        /** \brief Manages begindrop events.
         *
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool begindrop();

        /** \brief Manages completedrop events.
         *
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool completedrop();

        /** \brief Manages jaxis events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>axis</u>: The axis on the joystick whose value is being given
         * \param Sint16 <u>value</u>: The value of the axis
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jaxis(SDL_JoystickID joystick_id, Uint8 axis, Sint16 value);

        /** \brief Manages jball events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>ball</u>: The trackball on the joystick whose values are being given
         * \param Sint16 <u>x</u>: Relative horizontal motion of the trackball
         * \param Sint16 <u>y</u>: Relative vertical motion of the trackball
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jball(SDL_JoystickID joystick_id, Uint8 ball, Sint16 x, Sint16 y);

        /** \brief Manages jhat events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>hat</u>: The hat on the joystick whose value is being given
         * \param Uint8 <u>value</u>: The value of the hat
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jhat(SDL_JoystickID joystick_id, Uint8 hat, Uint8 value);

        /** \brief Manages jbtndown events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>button</u>: The button on the joystick being pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jbtndown(SDL_JoystickID joystick_id, Uint8 button);

        /** \brief Manages jbtnup events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>button</u>: The button on the joystick being released
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jbtnup(SDL_JoystickID joystick_id, Uint8 button);

        /** \brief Manages caxis events.
         *
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>axis</u>: The axis on the controller whose value is being given
         * \param Sint16 <u>value</u>: The value of the axis
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool caxis(SDL_JoystickID controller_id, Uint8 axis, Sint16 value);

        /** \brief Manages cbtndown events.
         *
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>button</u>: The button on the controller being pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool cbtndown(SDL_JoystickID controller_id, Uint8 button);

        /** \brief Manages cbtnup events.
         *
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>button</u>: The button on the controller being released
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool cbtnup(SDL_JoystickID controller_id, Uint8 button);

        /** \brief Manages fingerdown events.
         *
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
        virtual bool fingerdown(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                float pressure);

        /** \brief Manages fingerup events.
         *
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
        virtual bool fingerup(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                              float pressure);

        /** \brief Manages fingermotion events.
         *
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
        virtual bool fingermotion(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                  float dx, float dy, float pressure);

        /** \brief Manages gesturerecord events.
         *
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param SDL_GestureID <u>gesture_id</u>: The ID of the gesture being recorded
         * \param Uint32 <u>num_fingers</u>: The number of fingers used to draw the stroke
         * \param float <u>x</u>: The normalized horizontal center of the gesture (0.0f-1.0f)
         * \param float <u>y</u>: The normalized vertical center of the gesture (0.0f-1.0f)
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool gesturerecord(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                   Uint32 num_fingers, float x, float y);

        /** \brief Manages gestureperform events.
         *
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
        virtual bool gestureperform(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                    Uint32 num_fingers, float x, float y, float error);

        /** \brief Manages multigesture events.
         *
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param Uint16 <u>num_fingers</u>: The number of fingers used in this gesture
         * \param float <u>x</u>: The normalized horizontal center of the gesture (0.0f-1.0f)
         * \param float <u>y</u>: The normalized vertical center of the gesture (0.0f-1.0f)
         * \param float <u>d_theta</u>: The amount of rotation that occured during this motion
         * \param float <u>d_dist</u>: The amount of pinching that occured during this motion
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool multigesture(SDL_TouchID touch_id, Uint16 num_fingers, float x, float y,
                                  float d_theta, float d_dist);

        /** \brief Manages user events.
         *
         * \param SDL_TouchID <u>touch_id</u>: The ID of a touch device
         * \param Uint16 <u>num_fingers</u>: The number of fingers used in this gesture
         * \param float <u>x</u>: The normalized horizontal center of the gesture (0.0f-1.0f)
         * \param float <u>y</u>: The normalized vertical center of the gesture (0.0f-1.0f)
         * \param float <u>d_theta</u>: The amount of rotation that occured during this motion
         * \param float <u>d_dist</u>: The amount of pinching that occured during this motion
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool userevent(Sint32 code, void *data1, void *data2);
    };

// --- LAYER CLASS --------------------------------------------------------------------------------

    /** \brief A collection of GenEx objects.
     */
    class Layer : public Object {
    protected:
        std::unordered_map<Uint64, std::shared_ptr<Object> > objects; // maps IDs to objects
        std::unordered_map<std::string, Uint64> id_map; // maps strings to IDs

    public:
// ------ LAYER CONSTRUCTORS ----------------------------------------------------------------------

        /** \brief Empty constructor
         */
        Layer();

        /** \brief Copy constructor for GenEx Layers.
         *
         * \param Layer &<u>other</u>: The layer to copy
         *
         */
        Layer(const Layer &other);

        /** \brief Move constructor for GenEx Layers.
         *
         * \param Layer &&<u>other</u>: The layer to move
         *
         */
        Layer(Layer &&other);

        /** \brief Constructs a new layer with the given event handlers
         *
         * \param Events::EventHandlers <u>evt_handlers</u>: Event handlers for this layer to use
         *
         */
        Layer(Events::EventHandlers evt_handlers);

        /** \brief Constructs a new layer with the given event handlers & Objects
         *
         * \param Events::EventHandlers <u>evt_handlers</u>: Event handlers for this layer to use
         * \param initlist : Any number of Object pointers or shared_ptrs to Objects
         *
         */
        Layer(Events::EventHandlers evt_handlers, std::initializer_list< std::shared_ptr<Object> >
              init_list);

        /** \brief Constructs a new layer using an initializer list
         *
         * \param <u>init_list</u>: Any number of Object pointers or shared_ptrs to Objects
         *
         */
        Layer(std::initializer_list< std::shared_ptr<Object> > init_list);

        /** \brief Constructs a new layer with the given event handlers & Objects
         *
         * \param Events::EventHandlers <u>evt_handlers</u>: Event handlers for this layer to use
         * \param initlist : Any number of Object pointers or shared_ptrs to Objects
         *
         */
        Layer(Events::EventHandlers evt_handlers, std::initializer_list<Object*> init_list);

        /** \brief Constructs a new layer using an initializer list
         *
         * \param <u>init_list</u>: Any number of Object pointers or shared_ptrs to Objects
         *
         */
        Layer(std::initializer_list<Object*> init_list);

// ------ LAYER OPERATORS -------------------------------------------------------------------------

        /** \brief Copy assignment for GenEx Layers.
         *
         * \param Layer &<u>other</u>: The layer to copy
         *
         */
        Layer &operator= (const Layer &other);

        /** \brief Move assignment for GenEx Layers.
         *
         * \param Layer &&<u>other</u>: The layer to move
         *
         */
        Layer &operator= (Layer &&other);

// ------ LAYER METHODS ---------------------------------------------------------------------------

        /** \brief Destroys this layer
         */
        virtual void destroy() override;

        /** \brief Clones this layer and the objects inside of it.
         *
         * \return Object* Pointer to the new Layer
         *
         */
        Object *clone() override;

        /** \brief Returns how many objects are contained in this layer.
         *
         * \return size_t The amount of objects in this layer
         *
         */
        size_t num_objects();

        /** \brief Adds a new object to this layer.
         *
         * \param std::shared_ptr(Object) *<u>objptr</u>: Shared pointer to an object to add
         * \param std::string <u>name</u>: The string identifier you want to use for this object
         * \return std::string The actual string identifier used to reference the object
         *
         */
        std::string add_object(std::shared_ptr<Object> objptr, std::string name);

        /** \brief Adds a new object to this layer.
         *
         * \param Object *<u>objptr</u>: Raw pointer to an object to add
         * \param std::string <u>name</u>: The string identifier you want to use for this object
         * \return std::string The actual string identifier used to reference the object
         *
         */
        std::string add_object(Object *objptr, std::string name) {
            return add_object(std::shared_ptr<Object>(objptr), name);
        }

        /** \brief Gets an object from this layer.
         *
         * \param Uint64 <u>num_id</u>: The numeric ID of the object you want to get
         * \return std::shared_ptr(Object) Shared pointer to the object with the provided ID, or
         *         NULLPTR if no object with the provided ID is found in this layer
         *
         */
        std::shared_ptr<Object> get_object(Uint64 num_id);

        /** \brief Gets an object from this layer.
         *
         * \param std::string <u>str_id</u>: The string ID of the object for this layer
         * \return std::shared_ptr(Object) Shared pointer to the object with the provided ID, or
         *         NULLPTR if no object with the provided ID is found in this layer
         *
         */
        std::shared_ptr<Object> get_object(std::string str_id);

        /** \brief Returns the begin iterator for iterating over objects.
         *
         * \return std::unordered_map::const_iterator Read-only iterator to the beginning of the
         *         object collection in this layer.
         *
         */
        std::unordered_map<Uint64, std::shared_ptr<Object> >::const_iterator begin() const;

        /** \brief Returns the end iterator for iterating over objects.
         *
         * \return std::unordered_map::const_iterator Read-only iterator to the end of the
         *         object collection in this layer.
         *
         */
        std::unordered_map<Uint64, std::shared_ptr<Object> >::const_iterator end() const;

        /** \brief Gets an object from this layer.
         *
         * \param Uint64 <u>num_id</u>: The numeric ID of the object you want to get
         * \return std::shared_ptr(Object) Shared pointer to the object with the provided ID, or
         *         NULLPTR if no object with the provided ID is found in this layer
         *
         */
        std::shared_ptr<Object> operator[] (Uint64 num_id);

        /** \brief Gets an object from this layer.
         *
         * \param std::string <u>str_id</u>: The string ID of the object for this layer
         * \return std::shared_ptr(Object) Shared pointer to the object with the provided ID, or
         *         NULLPTR if no object with the provided ID is found in this layer
         *
         */
        std::shared_ptr<Object> operator[] (std::string str_id);

        /** \brief Removes an object from this layer; nothing bad happens if the ID doesn't match
         *        to an object to this layer.
         *
         * \param Uint64 <u>num_id</u>: The numeric ID of the object you want to get
         *
         */
        void remove_object(Uint64 num_id);

        /** \brief Removes an object from this layer; nothing bad happens if the ID doesn't match
         *        to an object to this layer.
         *
         * \param std::string <u>str_id</u>: The string ID of the object for this layer
         *
         */
        void remove_object(std::string str_id);

        /** \brief Removes an object from this layer; nothing bad happens if the pointer provided
         *        doesn't match that of any object in this layer.
         *
         * \param std::shared_ptr(Object) &<u>objptr</u>: Shared pointer to an object
         *
         */
        void remove_object(std::shared_ptr<Object> &objptr);

// ------ LAYER EVENT HANDLERS --------------------------------------------------------------------

        virtual void render(SDL_Renderer *target, int offset_x, int offset_y, int offset_z);

        virtual bool update(double elapsed);

        virtual bool targetreset();

        virtual bool windowevent(Uint8 event, Sint32 data1, Sint32 data2);

        virtual bool keydown(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat);

        virtual bool keyup(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat);

        virtual bool textediting(char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                 Sint32 start, Sint32 length);

        virtual bool textinput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]);

        virtual bool mousedown(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which);

        virtual bool mouseup(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which);

        virtual bool mousemotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel,
                                 bool buttons[5], Uint32 which);

        virtual bool mousewheel(bool flipped, Sint32 x, Sint32 y, Uint32 which);

        virtual bool clipboardupdate(char text[]);

        virtual bool filedrop(std::string filename);

        virtual bool textdrop(char text[]);

        virtual bool begindrop();

        virtual bool completedrop();

        virtual bool jaxis(SDL_JoystickID joystick_id, Uint8 axis, Sint16 value);

        virtual bool jball(SDL_JoystickID joystick_id, Uint8 ball, Sint16 x, Sint16 y);

        virtual bool jhat(SDL_JoystickID joystick_id, Uint8 hat, Uint8 value);

        virtual bool jbtndown(SDL_JoystickID joystick_id, Uint8 button);

        virtual bool jbtnup(SDL_JoystickID joystick_id, Uint8 button);

        virtual bool caxis(SDL_JoystickID controller_id, Uint8 axis, Sint16 value);

        virtual bool cbtndown(SDL_JoystickID controller_id, Uint8 button);

        virtual bool cbtnup(SDL_JoystickID controller_id, Uint8 button);

        virtual bool fingerdown(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                float pressure);

        virtual bool fingerup(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                              float pressure);

        virtual bool fingermotion(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                  float dx, float dy, float pressure);

        virtual bool gesturerecord(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                   Uint32 num_fingers, float x, float y);

        virtual bool gestureperform(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                    Uint32 num_fingers, float x, float y, float error);

        virtual bool multigesture(SDL_TouchID touch_id, Uint16 num_fingers, float x, float y,
                                  float d_theta, float d_dist);

        virtual bool userevent(Sint32 code, void *data1, void *data2);
    };
}

#endif // OBJECTS_HPP
