#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "base.hpp"
#include "math.hpp"
#include "util.hpp"
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
        Object(Events::EventHandlers evt_handlers) :
                   position({0, 0, 0}), anchor_point({0.5, 0.5, 0.5}),
                   offset({0, 0, 0}), rotation({0, 0, 0}), scale({0, 0, 0}),
                   move_vector({0, 0, 0}), angle_vector({0, 0, 0}),
                   event_handlers(evt_handlers) {
            event_handlers.init(this);
            instance_id = _num_instances++;
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
        Object(const Object &other) : Object(other.event_handlers) {
            event_handlers = other.event_handlers;
            position = other.position;
            anchor_point = other.anchor_point;
            offset = other.offset;
            rotation = other.rotation;
            scale = other.scale;
            move_vector = other.move_vector;
            angle_vector = other.angle_vector;
        }

        /** \brief Move constructor for GenEx Objects.
         *
         * \param Object &<u>other</u>: Reference to an Object to copy
         *
         */
        Object(Object &&other) : Object(other.event_handlers) {
            event_handlers = std::move(other.event_handlers);
            position = std::move(other.position);
            anchor_point = std::move(other.anchor_point);
            offset = std::move(other.offset);
            rotation = std::move(other.rotation);
            scale = std::move(other.scale);
            move_vector = std::move(other.move_vector);
            angle_vector = std::move(other.angle_vector);
        }

// ------ OBJECT OPERATORS ------------------------------------------------------------------------

        /** \brief Copy assignment for objects.
         *
         * \param Object &<u>other</u>: Reference to another object
         */
        Object &operator= (const Object &other) {
            if (&other != this) {
                event_handlers = other.event_handlers;
                position = other.position;
                anchor_point = other.anchor_point;
                offset = other.offset;
                rotation = other.rotation;
                scale = other.scale;
                move_vector = other.move_vector;
                angle_vector = other.angle_vector;
            }
            return *this;
        }

        /** \brief Move assignment for objects.
         *
         * \param Object &<u>other</u>: Reference to another object
         */
        Object &operator= (Object &&other) {
            if (&other != this) {
                event_handlers = std::move(other.event_handlers);
                position = std::move(other.position);
                anchor_point = std::move(other.anchor_point);
                offset = std::move(other.offset);
                rotation = std::move(other.rotation);
                scale = std::move(other.scale);
                move_vector = std::move(other.move_vector);
                angle_vector = std::move(other.angle_vector);
            }
            return *this;
        }

// ------ OBJECT FUNCTIONS ------------------------------------------------------------------------

        /** \brief Destroy this object
         */
        virtual void destroy() {
            if (!dead) {
                dead = true;
                event_handlers.destroy(this);
            }
        }

        /** \brief Destructor for GenEx Objects. Can be overwritten in subclass.
         */
        virtual ~Object() {
            destroy();
        }

        /** \brief Returns whether or not this object has been destroyed (i.e. is dead).
         *
         * \return bool TRUE if the object has been destroyed
         *
         */
        bool is_dead() { return dead; }

        /** \brief Gets the unique identifier for this object.
         *
         * \return Uint64 This object's ID
         *
         */
        Uint64 get_id() { return instance_id; }

        /** \brief Clones the object.
         *
         * \return Object A new object made based off the properties of this object
         *
         */
        virtual Object *clone() {
            return new Object(*this);
        }

// ------ OBJECT EVENT HANDLERS -------------------------------------------------------------------

        /** \brief Renders this object on to a target.
         *
         * \param SDL_Renderer *<u>target</u>: A target to render to
         * \param int <u>offset_x</u>: X offset from the usual rendering position
         * \param int <u>offset_y</u>: Y offset from the usual rendering position
         * \param int <u>offset_z</u>: Z offset from the usual rendering position
         *
         */
        virtual void render(SDL_Renderer *target, int offset_x, int offset_y, int offset_z) { }

        /** \brief Updates the object.
         *
         * \param double <elapsed>: The elapsed time since the previous frame in seconds
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool update(double elapsed) {
            position += move_vector  * (60.0 / elapsed);
            rotation += angle_vector * (60.0 / elapsed);
            return event_handlers.update(this, elapsed);
        }

        /** \brief Resets texture-related data in the object when a target resets.
         *
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool targetreset() {
            return event_handlers.targetreset(this);
        }

        /** \brief Manages window events.
         *
         * \param Uint8 <u>event</u>: The type of window event
         * \param Sint32 <u>data1</u>: Event-related data
         * \param Sint32 <u>data2</u>: Event-related data
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool windowevent(Uint8 event, Sint32 data1, Sint32 data2) {
            return event_handlers.windowevent(this, event, data1, data2);
        }

        /** \brief Manages keydown events.
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was pressed
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was pressed
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool keydown(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            return event_handlers.keydown(this, key, scancode, repeat);
        }

        /** \brief Manages keyup events.
         *
         * \param SDL_Keycode <u>key</u>: The keycode/key that was pressed
         * \param SDL_Scancode <u>scancode</u>: The scancode/location on the keyboard that
         *        was pressed
         * \param Uint8 <u>repeat</u>: How many times the key was pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool keyup(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            return event_handlers.keyup(this, key, scancode, repeat);
        }

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
                                 Sint32 start, Sint32 length) {
            return event_handlers.textediting(this, text, start, length);
        }

        /** \brief Manages textinput events.
         *
         * \param char <u>text</u>[32]: The vent text in UTF-8 encoding
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool textinput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
            return event_handlers.textinput(this, text);
        }

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
        virtual bool mousedown(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
            return event_handlers.mousedown(this, x, y, button, clicks, which);
        }

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
        virtual bool mouseup(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
            return event_handlers.mouseup(this, x, y, button, clicks, which);
        }

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
                                 bool buttons[5], Uint32 which) {
            return event_handlers.mousemotion(this, x, y, xrel, yrel, buttons, which);
        }

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
        virtual bool mousewheel(bool flipped, Sint32 x, Sint32 y, Uint32 which) {
            return event_handlers.mousewheel(this, flipped, x, y, which);
        }

        /** \brief Manages clipboardupdate events.
         *
         * \param char <u>text</u>[]: The text copied from the clipboard
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool clipboardupdate(char text[]) {
            return event_handlers.clipboardupdate(this, text);
        }

        /** \brief Manages filedrop events.
         *
         * \param std::string <u>filename</u>: Name of the file to open
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool filedrop(std::string filename) {
            return event_handlers.filedrop(this, filename);
        }

        /** \brief Manages textdrop events.
         *
         * \param char <u>text</u>[]: Text that was dropped
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool textdrop(char text[]) {
            return event_handlers.textdrop(this, text);
        }

        /** \brief Manages begindrop events.
         *
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool begindrop() {
            return event_handlers.begindrop(this);
        }

        /** \brief Manages completedrop events.
         *
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool completedrop() {
            return event_handlers.completedrop(this);
        }

        /** \brief Manages jaxis events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>axis</u>: The axis on the joystick whose value is being given
         * \param Sint16 <u>value</u>: The value of the axis
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jaxis(SDL_JoystickID joystick_id, Uint8 axis, Sint16 value) {
            return event_handlers.jaxis(this, joystick_id, axis, value);
        }

        /** \brief Manages jball events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>ball</u>: The trackball on the joystick whose values are being given
         * \param Sint16 <u>x</u>: Relative horizontal motion of the trackball
         * \param Sint16 <u>y</u>: Relative vertical motion of the trackball
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jball(SDL_JoystickID joystick_id, Uint8 ball, Sint16 x, Sint16 y) {
            return event_handlers.jball(this, joystick_id, ball, x, y);
        }

        /** \brief Manages jhat events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>hat</u>: The hat on the joystick whose value is being given
         * \param Uint8 <u>value</u>: The value of the hat
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jhat(SDL_JoystickID joystick_id, Uint8 hat, Uint8 value) {
            return event_handlers.jhat(this, joystick_id, hat, value);
        }

        /** \brief Manages jbtndown events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>button</u>: The button on the joystick being pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jbtndown(SDL_JoystickID joystick_id, Uint8 button) {
            return event_handlers.jbtndown(this, joystick_id, button);
        }

        /** \brief Manages jbtnup events.
         *
         * \param SDL_JoystickID <u>joystick_id</u>: The ID of the joystick
         * \param Uint8 <u>button</u>: The button on the joystick being released
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool jbtnup(SDL_JoystickID joystick_id, Uint8 button) {
            return event_handlers.jbtnup(this, joystick_id, button);
        }

        /** \brief Manages caxis events.
         *
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>axis</u>: The axis on the controller whose value is being given
         * \param Sint16 <u>value</u>: The value of the axis
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool caxis(SDL_JoystickID controller_id, Uint8 axis, Sint16 value) {
            return event_handlers.caxis(this, controller_id, axis, value);
        }

        /** \brief Manages cbtndown events.
         *
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>button</u>: The button on the controller being pressed
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool cbtndown(SDL_JoystickID controller_id, Uint8 button) {
            return event_handlers.cbtndown(this, controller_id, button);
        }

        /** \brief Manages cbtnup events.
         *
         * \param SDL_JoystickID <u>controller_id</u>: The ID of the controller
         * \param Uint8 <u>button</u>: The button on the controller being released
         * \return bool TRUE to continue running the application
         *
         */
        virtual bool cbtnup(SDL_JoystickID controller_id, Uint8 button) {
            return event_handlers.cbtnup(this, controller_id, button);
        }

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
                                float pressure) {
            return event_handlers.fingerdown(this, touch_id, finger_id, x, y, pressure);
        }

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
                              float pressure) {
            return event_handlers.fingerup(this, touch_id, finger_id, x, y, pressure);
        }

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
                                  float dx, float dy, float pressure) {
            return event_handlers.fingermotion(this, touch_id, finger_id, x, y, dx, dy, pressure);
        }

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
                                   Uint32 num_fingers, float x, float y) {
            return event_handlers.gesturerecord(this, touch_id, gesture_id, num_fingers, x, y);
        }

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
                                    Uint32 num_fingers, float x, float y, float error) {
            return event_handlers.gestureperform(this, touch_id, gesture_id, num_fingers, x, y,
                                                 error);
        }

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
                                  float d_theta, float d_dist) {
            return event_handlers.multigesture(this, touch_id, num_fingers, x, y, d_theta, d_dist);
        }

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
        virtual bool userevent(Sint32 code, void *data1, void *data2) {
            return event_handlers.userevent(this, code, data1, data2);
        }
    };

    Uint64 Object::_num_instances = 0; // initialize _num_instances to 0 on start

// --- LAYER CLASS --------------------------------------------------------------------------------

    /** \brief A collection of GenEx objects.
     */
    class Layer : public Object {
    private:
        std::unordered_map<Uint64, std::shared_ptr<Object> > objects; // maps IDs to objects
        std::unordered_map<std::string, Uint64> id_map; // maps strings to IDs

        void add_objects() { }

        void add_objects(std::shared_ptr<Object> objptr) {
            Uint64 objid = objptr->get_id();
            objects[objid] = objptr;
            id_map["object" + std::to_string(objid)] = objid;
        }

        void add_objects(Object *objptr) {
            if (objptr != nullptr) {
                Uint64 objid = objptr->get_id();
                objects[objid] = std::shared_ptr<Object>(objptr);
                id_map["object" + std::to_string(objid)] = objid;
            }
        }

        template <typename ..._Others>
        void add_objects(Object *objptr, _Others... objs) {
            add_objects(objptr);
            add_objects(objs...);
        }

        template <typename ..._Others>
        void add_objects(std::shared_ptr<Object> objptr, _Others... objs) {
            add_objects(objptr);
            add_objects(objs...);
        }

    public:
// ------ LAYER CONSTRUCTORS ----------------------------------------------------------------------

        /** \brief Constructs a new layer with the provided Objects
         *
         * \param ... : Any number of Object pointers or shared_ptrs to Objects
         *
         */
        template <typename ...PTRS>
        Layer(PTRS... objs) : Object() {
            add_objects(objs...);
        }

        /** \brief Constructs a new layer with the given event handlers & Objects
         *
         * \param Events::EventHandlers <u>evt_handlers</u>: Event handlers for this layer to use
         * \param ... : Any number of Object pointers or shared_ptrs to Objects
         *
         */
        template <typename ...PTRS>
        Layer(Events::EventHandlers evt_handlers, PTRS... objs) : Object(evt_handlers) {
            add_objects(objs...);
        }

        /** \brief Constructs a new layer using an initializer list
         *
         * \param <u>init_list</u>: List of shared_ptrs to Objects
         *
         */
        Layer(std::initializer_list< std::shared_ptr<Object> > init_list) {
            for (auto &objptr : init_list)
                add_objects(objptr);
        }

        /** \brief Constructs a new layer using an initializer list
         *
         * \param <u>init_list</u>: List of raw pointers to Objects
         *
         */
        Layer(std::initializer_list<Object*> init_list) {
            for (auto &objptr : init_list)
                add_objects(objptr);
        }

        /** \brief Copy constructor for GenEx Layers.
         *
         * \param Layer &<u>other</u>: The layer to copy
         *
         */
        Layer(const Layer &other) : Object(other) {
            objects = other.objects;
            id_map = other.id_map;
        }

        /** \brief Move constructor for GenEx Layers.
         *
         * \param Layer &&<u>other</u>: The layer to move
         *
         */
        Layer(Layer &&other) : Object(other) {
            objects = std::move(other.objects);
            id_map = std::move(other.id_map);
        }

// ------ LAYER OPERATORS -------------------------------------------------------------------------

        /** \brief Copy assignment for GenEx Layers.
         *
         * \param Layer &<u>other</u>: The layer to copy
         *
         */
        Layer &operator= (const Layer &other) {
            objects = other.objects;
            id_map = other.id_map;
            return *this;
        }

        /** \brief Move assignment for GenEx Layers.
         *
         * \param Layer &&<u>other</u>: The layer to move
         *
         */
        Layer &operator= (Layer &&other) {
            objects = std::move(other.objects);
            id_map = std::move(other.id_map);
            return *this;
        }

// ------ LAYER METHODS ---------------------------------------------------------------------------

        /** \brief Destroys this layer
         */
        void destroy() override {
            if (!is_dead()) {
                objects.clear();
                id_map.clear();
                Object::destroy();
            }
        }

        /** \brief Clones this layer and the objects inside of it.
         *
         * \return Object* Pointer to the new Layer
         *
         */
        Object *clone() override {
            Layer *new_layer = new Layer();
            for (auto iter = objects.begin(); iter != objects.end(); iter++) {
                std::vector<std::string> vec;
                Util::FindByValue(vec, id_map, iter->second->get_id());
                std::shared_ptr<Object> sp(iter->second);
                new_layer->add_object(sp, vec[0]);
            }
            return new_layer;
        }

        /** \brief Returns how many objects are contained in this layer.
         *
         * \return size_t The amount of objects in this layer
         *
         */
        size_t num_objects() {
            return objects.size();
        }

        /** \brief Adds a new object to this layer.
         *
         * \param std::shared_ptr(Object) *<u>objptr</u>: Shared pointer to an object to add
         * \param std::string <u>name</u>: The string identifier you want to use for this object
         * \return std::string The actual string identifier used to reference the object
         *
         */
        std::string add_object(std::shared_ptr<Object> objptr, std::string name) {
            std::shared_ptr<Object> object_to_add = objptr;

            // if the object is already in this layer, clone it
            if (Util::FindByValue(nullptr, objects, objptr)) {
                object_to_add = std::make_shared<Object>(*objptr);
            }

            std::string name_to_use = name;
            while (id_map.find(name_to_use) != id_map.end()) {
                std::smatch matches;

                // if a number isn't found at the end of the string, add one
                if (!std::regex_search(name_to_use, matches, std::regex("(\\d+)(?!.*\\d)"))) {
                    name_to_use += "0";
                } else {
                    // replace old number with new number
                    name_to_use = Util::RegexReplace(name_to_use, "(\\d+)(?!.*\\d)", "");
                    name_to_use = std::to_string(std::stoi(matches[0])+1); // add new number
                }
            }

            id_map[name_to_use] = object_to_add->get_id();
            objects[object_to_add->get_id()] = object_to_add;

            return name_to_use;
        }

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
        std::shared_ptr<Object> get_object(Uint64 num_id) {
            auto iter = objects.find(num_id);
            if (iter != objects.end()) {
                return iter->second;
            }
            return nullptr;
        }

        /** \brief Gets an object from this layer.
         *
         * \param std::string <u>str_id</u>: The string ID of the object for this layer
         * \return std::shared_ptr(Object) Shared pointer to the object with the provided ID, or
         *         NULLPTR if no object with the provided ID is found in this layer
         *
         */
        std::shared_ptr<Object> get_object(std::string str_id) {
            auto iter = id_map.find(str_id);
            if (iter != id_map.end()) {
                return objects[iter->second];
            }
            return nullptr;
        }

        /** \brief Gets an object from this layer.
         *
         * \param Uint64 <u>num_id</u>: The numeric ID of the object you want to get
         * \return std::shared_ptr(Object) Shared pointer to the object with the provided ID, or
         *         NULLPTR if no object with the provided ID is found in this layer
         *
         */
        std::shared_ptr<Object> operator[] (Uint64 num_id) {
            return get_object(num_id);
        }

        /** \brief Gets an object from this layer.
         *
         * \param std::string <u>str_id</u>: The string ID of the object for this layer
         * \return std::shared_ptr(Object) Shared pointer to the object with the provided ID, or
         *         NULLPTR if no object with the provided ID is found in this layer
         *
         */
        std::shared_ptr<Object> operator[] (std::string str_id) {
            return get_object(str_id);
        }

        /** \brief Removes an object from this layer; nothing bad happens if the ID doesn't match
         *        to an object to this layer.
         *
         * \param Uint64 <u>num_id</u>: The numeric ID of the object you want to get
         *
         */
        void remove_object(Uint64 num_id) {
            if (objects.find(num_id) != objects.end()) {
                objects.erase(num_id);
                std::vector<std::string> vec;
                Util::FindByValue(vec, id_map, num_id);
                id_map.erase(vec[0]);
            }
        }

        /** \brief Removes an object from this layer; nothing bad happens if the ID doesn't match
         *        to an object to this layer.
         *
         * \param std::string <u>str_id</u>: The string ID of the object for this layer
         *
         */
        void remove_object(std::string str_id) {
            auto iter = id_map.find(str_id);
            if (iter != id_map.end()) {
                objects.erase(iter->second);
                id_map.erase(iter);
            }
        }

        /** \brief Removes an object from this layer; nothing bad happens if the pointer provided
         *        doesn't match that of any object in this layer.
         *
         * \param std::shared_ptr(Object) &<u>objptr</u>: Shared pointer to an object
         *
         */
        void remove_object(std::shared_ptr<Object> &objptr) {
            std::vector<Uint64> vec;
            if (Util::FindByValue(vec, objects, objptr)) {
                objects.erase(vec[0]);

                std::vector<std::string> vec2;
                Util::FindByValue(vec2, id_map, vec[0]);
                id_map.erase(vec2[0]);
            }
        }

// ------ LAYER EVENT HANDLERS --------------------------------------------------------------------

        virtual void render(SDL_Renderer *target, int offset_x, int offset_y, int offset_z) {
            for (auto iter : objects)
                iter.second->render(target,
                                    position[0] + offset_x,
                                    position[1] + offset_y,
                                    position[2] + offset_z);
        }

        virtual bool update(double elapsed) {
            for (auto iter : objects) {
                if (!(iter.second->update(elapsed)))
                    return false;
            }
            return Object::update(elapsed);
        }

        virtual bool targetreset() {
            for (auto iter : objects) {
                if (!(iter.second->targetreset()))
                    return false;
            }
            return Object::targetreset();
        }

        virtual bool windowevent(Uint8 event, Sint32 data1, Sint32 data2) {
            for (auto iter : objects) {
                if (!(iter.second->windowevent(event, data1, data2)))
                    return false;
            }
            return Object::windowevent(event, data1, data2);
        }

        virtual bool keydown(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            for (auto iter : objects) {
                if (!(iter.second->keydown(key, scancode, repeat)))
                    return false;
            }
            return Object::keydown(key, scancode, repeat);
        }

        virtual bool keyup(SDL_Keycode key, SDL_Scancode scancode, Uint8 repeat) {
            for (auto iter : objects) {
                if (!(iter.second->keyup(key, scancode, repeat)))
                    return false;
            }
            return Object::keyup(key, scancode, repeat);
        }

        virtual bool textediting(char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                 Sint32 start, Sint32 length) {
            for (auto iter : objects) {
                if (!(iter.second->textediting(text, start, length)))
                    return false;
            }
            return Object::textediting(text, start, length);
        }

        virtual bool textinput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
            for (auto iter : objects) {
                if (!(iter.second->textinput(text)))
                    return false;
            }
            return Object::textinput(text);
        }

        virtual bool mousedown(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
            for (auto iter : objects) {
                if (!(iter.second->mousedown(x, y, button, clicks, which)))
                    return false;
            }
            return Object::mousedown(x, y, button, clicks, which);
        }

        virtual bool mouseup(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
            for (auto iter : objects) {
                if (!(iter.second->mouseup(x, y, button, clicks, which)))
                    return false;
            }
            return Object::mouseup(x, y, button, clicks, which);
        }

        virtual bool mousemotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel,
                                 bool buttons[5], Uint32 which) {
            for (auto iter : objects) {
                if (!(iter.second->mousemotion(x, y, xrel, yrel, buttons, which)))
                    return false;
            }
            return Object::mousemotion(x, y, xrel, yrel, buttons, which);
        }

        virtual bool mousewheel(bool flipped, Sint32 x, Sint32 y, Uint32 which) {
            for (auto iter : objects) {
                if (!(iter.second->mousewheel(flipped, x, y, which)))
                    return false;
            }
            return Object::mousewheel(flipped, x, y, which);
        }

        virtual bool clipboardupdate(char text[]) {
            for (auto iter : objects) {
                if (!(iter.second->clipboardupdate(text)))
                    return false;
            }
            return Object::clipboardupdate(text);
        }

        virtual bool filedrop(std::string filename) {
            for (auto iter : objects) {
                if (!(iter.second->filedrop(filename)))
                    return false;
            }
            return Object::filedrop(filename);
        }

        virtual bool textdrop(char text[]) {
            for (auto iter : objects) {
                if (!(iter.second->textdrop(text)))
                    return false;
            }
            return Object::textdrop(text);
        }

        virtual bool begindrop() {
            for (auto iter : objects) {
                if (!(iter.second->begindrop()))
                    return false;
            }
            return Object::begindrop();
        }

        virtual bool completedrop() {
            for (auto iter : objects) {
                if (!(iter.second->completedrop()))
                    return false;
            }
            return Object::completedrop();
        }

        virtual bool jaxis(SDL_JoystickID joystick_id, Uint8 axis, Sint16 value) {
            for (auto iter : objects) {
                if (!(iter.second->jaxis(joystick_id, axis, value)))
                    return false;
            }
            return Object::jaxis(joystick_id, axis, value);
        }

        virtual bool jball(SDL_JoystickID joystick_id, Uint8 ball, Sint16 x, Sint16 y) {
            for (auto iter : objects) {
                if (!(iter.second->jball(joystick_id, ball, x, y)))
                    return false;
            }
            return Object::jball(joystick_id, ball, x, y);
        }

        virtual bool jhat(SDL_JoystickID joystick_id, Uint8 hat, Uint8 value) {
            for (auto iter : objects) {
                if (!(iter.second->jhat(joystick_id, hat, value)))
                    return false;
            }
            return Object::jhat(joystick_id, hat, value);
        }

        virtual bool jbtndown(SDL_JoystickID joystick_id, Uint8 button) {
            for (auto iter : objects) {
                if (!(iter.second->jbtndown(joystick_id, button)))
                    return false;
            }
            return Object::jbtndown(joystick_id, button);
        }

        virtual bool jbtnup(SDL_JoystickID joystick_id, Uint8 button) {
            for (auto iter : objects) {
                if (!(iter.second->jbtnup(joystick_id, button)))
                    return false;
            }
            return Object::jbtnup(joystick_id, button);
        }

        virtual bool caxis(SDL_JoystickID controller_id, Uint8 axis, Sint16 value) {
            for (auto iter : objects) {
                if (!(iter.second->caxis(controller_id, axis, value)))
                    return false;
            }
            return Object::caxis(controller_id, axis, value);
        }

        virtual bool cbtndown(SDL_JoystickID controller_id, Uint8 button) {
            for (auto iter : objects) {
                if (!(iter.second->cbtndown(controller_id, button)))
                    return false;
            }
            return Object::cbtndown(controller_id, button);
        }

        virtual bool cbtnup(SDL_JoystickID controller_id, Uint8 button) {
            for (auto iter : objects) {
                if (!(iter.second->cbtnup(controller_id, button)))
                    return false;
            }
            return Object::cbtnup(controller_id, button);
        }

        virtual bool fingerdown(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                float pressure) {
            for (auto iter : objects) {
                if (!(iter.second->fingerdown(touch_id, finger_id, x, y, pressure)))
                    return false;
            }
            return Object::fingerdown(touch_id, finger_id, x, y, pressure);
        }

        virtual bool fingerup(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                              float pressure) {
            for (auto iter : objects) {
                if (!(iter.second->fingerup(touch_id, finger_id, x, y, pressure)))
                    return false;
            }
            return Object::fingerup(touch_id, finger_id, x, y, pressure);
        }

        virtual bool fingermotion(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                  float dx, float dy, float pressure) {
            for (auto iter : objects) {
                if (!(iter.second->fingermotion(touch_id, finger_id, x, y, dx, dy, pressure)))
                    return false;
            }
            return Object::fingermotion(touch_id, finger_id, x, y, dx, dy, pressure);
        }

        virtual bool gesturerecord(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                   Uint32 num_fingers, float x, float y) {
            for (auto iter : objects) {
                if (!(iter.second->gesturerecord(touch_id, gesture_id, num_fingers, x, y)))
                    return false;
            }
            return Object::gesturerecord(touch_id, gesture_id, num_fingers, x, y);
        }

        virtual bool gestureperform(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                    Uint32 num_fingers, float x, float y, float error) {
            for (auto iter : objects) {
                if (!(iter.second->gestureperform(touch_id, gesture_id, num_fingers, x, y, error)))
                    return false;
            }
            return Object::gestureperform(touch_id, gesture_id, num_fingers, x, y, error);
        }

        virtual bool multigesture(SDL_TouchID touch_id, Uint16 num_fingers, float x, float y,
                                  float d_theta, float d_dist) {
           for (auto iter : objects) {
                if (!(iter.second->multigesture(touch_id, num_fingers, x, y, d_theta, d_dist)))
                    return false;
            }
            return Object::multigesture(touch_id, num_fingers, x, y, d_theta, d_dist);
        }

        virtual bool userevent(Sint32 code, void *data1, void *data2) {
            for (auto iter : objects) {
                if (!(iter.second->userevent(code, data1, data2)))
                    return false;
            }
            return Object::userevent(code, data1, data2);
        }
    };
}

#endif // OBJECTS_HPP
