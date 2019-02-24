/**
 * \file object.cpp
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
 * The source file for defining the base GenEx Object and Layer classes.
 *
 */

#include "base.hpp"
#include "math.hpp"
#include "util.hpp"
#include "events.hpp"
#include "object.hpp"

// --- OBJECT CLASS -------------------------------------------------------------------------------

Uint64 GenEx::Object::_num_instances = 0; // initialize _num_instances to 0 on start

// ------ CONSTRUCTORS ----------------------------------------------------------------------------

GenEx::Object::Object(GenEx::Events::EventHandlers evt_handlers) : position({0, 0, 0}),
                                                                   anchor_point({0.5, 0.5, 0.5}),
                                                                   offset({0, 0, 0}),
                                                                   rotation({0, 0, 0}),
                                                                   scale({0, 0, 0}),
                                                                   move_vector({0, 0, 0}),
                                                                   angle_vector({0, 0, 0}),
                                                                   event_handlers(evt_handlers) {
    event_handlers.init(this);
    instance_id = _num_instances++;
}

GenEx::Object::Object() : Object(GenEx::Events::GenerateEventHandlerStruct()) { }

GenEx::Object::Object(const GenEx::Object &other) : Object(other.event_handlers) {
    event_handlers = other.event_handlers;
    position = other.position;
    anchor_point = other.anchor_point;
    offset = other.offset;
    rotation = other.rotation;
    scale = other.scale;
    move_vector = other.move_vector;
    angle_vector = other.angle_vector;
}

GenEx::Object::Object(GenEx::Object &&other) : Object(other.event_handlers) {
    event_handlers  = std::move(other.event_handlers);
    position        = std::move(other.position);
    anchor_point    = std::move(other.anchor_point);
    offset          = std::move(other.offset);
    rotation        = std::move(other.rotation);
    scale           = std::move(other.scale);
    move_vector     = std::move(other.move_vector);
    angle_vector    = std::move(other.angle_vector);
}

// ------ ASSIGNMENT OPERATORS --------------------------------------------------------------------

GenEx::Object &GenEx::Object::operator= (const GenEx::Object &other) {
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

GenEx::Object &GenEx::Object::operator= (GenEx::Object &&other) {
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

// ------ OBJECT DESTRUCTOR -----------------------------------------------------------------------

void GenEx::Object::destroy() {
    if (!dead) {
        dead = true;
        event_handlers.destroy(this);
    }
}

GenEx::Object::~Object() { destroy(); }

bool GenEx::Object::is_dead() { return dead; }

// ------ OBJECT FUNCTIONS ------------------------------------------------------------------------

Uint64 GenEx::Object::get_id() { return instance_id; }

GenEx::Object *GenEx::Object::clone() { return new Object(*this); }

// ------ OBJECT EVENT HANDLERS -------------------------------------------------------------------

void GenEx::Object::render(SDL_Renderer *target, int offset_x, int offset_y, int offset_z) {
    event_handlers.render(this, target, offset_x, offset_y, offset_z);
}

bool GenEx::Object::update(double elapsed) {
    position += move_vector  * (60.0 / elapsed);
    rotation += angle_vector * (60.0 / elapsed);
    return event_handlers.update(this, elapsed);
}

bool GenEx::Object::targetreset() { return event_handlers.targetreset(this); }

bool GenEx::Object::windowevent(Uint8 event, Sint32 data1, Sint32 data2) {
    return event_handlers.windowevent(this, event, data1, data2);
}

bool GenEx::Object::keydown(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat) {
    return event_handlers.keydown(this, key, scancode, mod, repeat);
}

bool GenEx::Object::keyup(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat) {
    return event_handlers.keyup(this, key, scancode, mod, repeat);
}

bool GenEx::Object::textediting(char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                                 Sint32 start, Sint32 length) {
    return event_handlers.textediting(this, text, start, length);
}

bool GenEx::Object::textinput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
    return event_handlers.textinput(this, text);
}

bool GenEx::Object::mousedown(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
    return event_handlers.mousedown(this, x, y, button, clicks, which);
}

bool GenEx::Object::mouseup(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
    return event_handlers.mouseup(this, x, y, button, clicks, which);
}

bool GenEx::Object::mousemotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel, bool buttons[5],
                                Uint32 which) {
    return event_handlers.mousemotion(this, x, y, xrel, yrel, buttons, which);
}

bool GenEx::Object::mousewheel(bool flipped, Sint32 x, Sint32 y, Uint32 which) {
    return event_handlers.mousewheel(this, flipped, x, y, which);
}

bool GenEx::Object::clipboardupdate(char text[]) {
    return event_handlers.clipboardupdate(this, text);
}

bool GenEx::Object::filedrop(std::string filename) {
    return event_handlers.filedrop(this, filename);
}

bool GenEx::Object::textdrop(char text[]) {
    return event_handlers.textdrop(this, text);
}

bool GenEx::Object::begindrop() {
    return event_handlers.begindrop(this);
}

bool GenEx::Object::completedrop() {
    return event_handlers.completedrop(this);
}

bool GenEx::Object::jaxis(SDL_JoystickID joystick_id, Uint8 axis, Sint16 value) {
    return event_handlers.jaxis(this, joystick_id, axis, value);
}

bool GenEx::Object::jball(SDL_JoystickID joystick_id, Uint8 ball, Sint16 x, Sint16 y) {
    return event_handlers.jball(this, joystick_id, ball, x, y);
}

bool GenEx::Object::jhat(SDL_JoystickID joystick_id, Uint8 hat, Uint8 value) {
    return event_handlers.jhat(this, joystick_id, hat, value);
}

bool GenEx::Object::jbtndown(SDL_JoystickID joystick_id, Uint8 button) {
    return event_handlers.jbtndown(this, joystick_id, button);
}

bool GenEx::Object::jbtnup(SDL_JoystickID joystick_id, Uint8 button) {
    return event_handlers.jbtnup(this, joystick_id, button);
}

bool GenEx::Object::caxis(SDL_JoystickID controller_id, Uint8 axis, Sint16 value) {
    return event_handlers.caxis(this, controller_id, axis, value);
}

bool GenEx::Object::cbtndown(SDL_JoystickID controller_id, Uint8 button) {
    return event_handlers.cbtndown(this, controller_id, button);
}

bool GenEx::Object::cbtnup(SDL_JoystickID controller_id, Uint8 button) {
    return event_handlers.cbtnup(this, controller_id, button);
}

bool GenEx::Object::fingerdown(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                               float pressure) {
    return event_handlers.fingerdown(this, touch_id, finger_id, x, y, pressure);
}

bool GenEx::Object::fingerup(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                             float pressure) {
    return event_handlers.fingerup(this, touch_id, finger_id, x, y, pressure);
}

bool GenEx::Object::fingermotion(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                 float dx, float dy, float pressure) {
    return event_handlers.fingermotion(this, touch_id, finger_id, x, y, dx, dy, pressure);
}

bool GenEx::Object::gesturerecord(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                  Uint32 num_fingers, float x, float y) {
    return event_handlers.gesturerecord(this, touch_id, gesture_id, num_fingers, x, y);
}

bool GenEx::Object::gestureperform(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                   Uint32 num_fingers, float x, float y, float error) {
    return event_handlers.gestureperform(this, touch_id, gesture_id, num_fingers, x, y, error);
}

bool GenEx::Object::multigesture(SDL_TouchID touch_id, Uint16 num_fingers, float x, float y,
                                 float d_theta, float d_dist) {
    return event_handlers.multigesture(this, touch_id, num_fingers, x, y, d_theta, d_dist);
}

bool GenEx::Object::userevent(Sint32 code, void *data1, void *data2) {
    return event_handlers.userevent(this, code, data1, data2);
}

// --- LAYER CLASS --------------------------------------------------------------------------------
// ------ CONSTRUCTORS ----------------------------------------------------------------------------

GenEx::Layer::Layer() : Object() { }

GenEx::Layer::Layer(const GenEx::Layer &other) : Object(other) {
    objects = other.objects;
    id_map = other.id_map;
}

GenEx::Layer::Layer(GenEx::Layer &&other) : Object(other) {
    objects = std::move(other.objects);
    id_map = std::move(other.id_map);
}

GenEx::Layer::Layer(Events::EventHandlers evt_handlers) : Object(evt_handlers) { }

GenEx::Layer::Layer(Events::EventHandlers evt_handlers,
             std::initializer_list< std::shared_ptr<GenEx::Object> > init_list) :
                 Layer(evt_handlers) {
    for (auto &objptr : init_list) {
        Uint64 objid = objptr->get_id();
        objects[objid] = objptr;
        id_map["object" + std::to_string(objid)] = objid;
    }
}

GenEx::Layer::Layer(std::initializer_list< std::shared_ptr<GenEx::Object> > init_list) :
    Layer(Events::GenerateEventHandlerStruct(), init_list) { }

GenEx::Layer::Layer(Events::EventHandlers evt_handlers, std::initializer_list<GenEx::Object*>
                        init_list) : Layer(event_handlers) {
    for (auto &objptr : init_list) {
        if (objptr != nullptr) {
            Uint64 objid = objptr->get_id();
            objects[objid] = std::shared_ptr<GenEx::Object>(objptr);
            id_map["object" + std::to_string(objid)] = objid;
        }
    }
}

GenEx::Layer::Layer(std::initializer_list<GenEx::Object*> init_list) :
    Layer(Events::GenerateEventHandlerStruct(), init_list) { }

// ------ ASSIGNMENT OPERATORS --------------------------------------------------------------------

GenEx::Layer &GenEx::Layer::operator= (const GenEx::Layer &other) {
    objects = other.objects;
    id_map = other.id_map;
    return *this;
}

GenEx::Layer &GenEx::Layer::operator= (GenEx::Layer &&other) {
    objects = std::move(other.objects);
    id_map = std::move(other.id_map);
    return *this;
}

// ------ LAYER FUNCTIONS -------------------------------------------------------------------------

void GenEx::Layer::destroy() {
    if (!is_dead()) {
        Object::destroy();
        objects.clear();
        id_map.clear();
    }
}

GenEx::Object *GenEx::Layer::clone() {
    GenEx::Layer *new_layer = new GenEx::Layer();
    for (auto iter = objects.begin(); iter != objects.end(); iter++) {
        std::vector<std::string> vec;
        GenEx::Util::FindByValue(vec, id_map, iter->second->get_id());
        std::shared_ptr<Object> sp(iter->second);
        new_layer->add_object(sp, vec[0]);
    }
    return new_layer;
}

size_t GenEx::Layer::num_objects() { return objects.size(); }

std::string GenEx::Layer::add_object(std::shared_ptr<GenEx::Object> objptr, std::string name) {
    std::shared_ptr<GenEx::Object> object_to_add = objptr;

    // if the object is already in this layer, clone it
    if (GenEx::Util::FindByValue(nullptr, objects, objptr)) {
        object_to_add = std::make_shared<GenEx::Object>(*objptr);
    }

    std::string name_to_use = name;
    while (id_map.find(name_to_use) != id_map.end()) {
        std::smatch matches;

        // if a number isn't found at the end of the string, add one
        if (!std::regex_search(name_to_use, matches, std::regex("(\\d+)(?!.*\\d)"))) {
            name_to_use += "0";
        } else {
            // replace old number with new number
            name_to_use = GenEx::Util::RegexReplace(name_to_use, "(\\d+)(?!.*\\d)", "");
            name_to_use = std::to_string(std::stoi(matches[0])+1); // add new number
        }
    }

    id_map[name_to_use] = object_to_add->get_id();
    objects[object_to_add->get_id()] = object_to_add;

    return name_to_use;
}

std::shared_ptr<GenEx::Object> GenEx::Layer::get_object(Uint64 num_id) {
    auto iter = objects.find(num_id);
    if (iter != objects.end()) {
        return iter->second;
    }
    return nullptr;
}

std::shared_ptr<GenEx::Object> GenEx::Layer::operator[] (Uint64 num_id) {
    return get_object(num_id);
}

std::shared_ptr<GenEx::Object> GenEx::Layer::get_object(std::string str_id) {
    auto iter = id_map.find(str_id);
    if (iter != id_map.end()) {
        return objects[iter->second];
    }
    return nullptr;
}

std::shared_ptr<GenEx::Object> GenEx::Layer::operator[] (std::string str_id) {
    return get_object(str_id);
}

std::unordered_map<Uint64, std::shared_ptr<GenEx::Object> >::const_iterator GenEx::Layer::begin()
const { return objects.cbegin(); }

std::unordered_map<Uint64, std::shared_ptr<GenEx::Object> >::const_iterator GenEx::Layer::end()
const { return objects.cend(); }

void GenEx::Layer::remove_object(Uint64 num_id) {
    if (objects.find(num_id) != objects.end()) {
        objects.erase(num_id);
        std::vector<std::string> vec;
        GenEx::Util::FindByValue(vec, id_map, num_id);
        id_map.erase(vec[0]);
    }
}

void GenEx::Layer::remove_object(std::string str_id) {
    auto iter = id_map.find(str_id);
    if (iter != id_map.end()) {
        objects.erase(iter->second);
        id_map.erase(iter);
    }
}

void GenEx::Layer::remove_object(std::shared_ptr<GenEx::Object> &objptr) {
    std::vector<Uint64> vec;
    if (GenEx::Util::FindByValue(vec, objects, objptr)) {
        objects.erase(vec[0]);

        std::vector<std::string> vec2;
        GenEx::Util::FindByValue(vec2, id_map, vec[0]);
        id_map.erase(vec2[0]);
    }
}

// ------ LAYER EVENT HANDLERS --------------------------------------------------------------------

void GenEx::Layer::render(SDL_Renderer *target, int offset_x, int offset_y, int offset_z) {
    Object::render(target, offset_x, offset_y, offset_z);
    for (auto iter : objects)
        if (!iter.second->is_dead()) {
            remove_object(iter.second);
        }
        else
            iter.second->render(target,
                                position[0] + offset_x,
                                position[1] + offset_y,
                                position[2] + offset_z);

    SDL_SetRenderTarget(target, nullptr);
}

bool GenEx::Layer::update(double elapsed) {
    for (auto iter : objects) {
        if (iter.second->is_dead()) {
            remove_object(iter.second);
        }
        else if (!(iter.second->update(elapsed)))
            return false;
    }
    return Object::update(elapsed);
}

bool GenEx::Layer::targetreset() {
    for (auto iter : objects) {
        if (iter.second->is_dead()) {
            remove_object(iter.second);
        }
        else if (!(iter.second->targetreset()))
            return false;
    }
    return Object::targetreset();
}

bool GenEx::Layer::windowevent(Uint8 event, Sint32 data1, Sint32 data2) {
    for (auto iter : objects) {
        if (!(iter.second->windowevent(event, data1, data2)))
            return false;
    }
    return Object::windowevent(event, data1, data2);
}

bool GenEx::Layer::keydown(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat) {
    for (auto iter : objects) {
        if (!(iter.second->keydown(key, scancode, mod, repeat)))
            return false;
    }
    return Object::keydown(key, scancode, mod, repeat);
}

bool GenEx::Layer::keyup(SDL_Keycode key, SDL_Scancode scancode, Uint16 mod, Uint8 repeat) {
    for (auto iter : objects) {
        if (!(iter.second->keyup(key, scancode, mod, repeat)))
            return false;
    }
    return Object::keyup(key, scancode, mod, repeat);
}

bool GenEx::Layer::textediting(char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE],
                               Sint32 start, Sint32 length) {
    for (auto iter : objects) {
        if (!(iter.second->textediting(text, start, length)))
            return false;
    }
    return Object::textediting(text, start, length);
}

bool GenEx::Layer::textinput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
    for (auto iter : objects) {
        if (!(iter.second->textinput(text)))
            return false;
    }
    return Object::textinput(text);
}

bool GenEx::Layer::mousedown(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
    for (auto iter : objects) {
        if (!(iter.second->mousedown(x, y, button, clicks, which)))
            return false;
    }
    return Object::mousedown(x, y, button, clicks, which);
}

bool GenEx::Layer::mouseup(Sint32 x, Sint32 y, Uint8 button, Uint8 clicks, Uint32 which) {
    for (auto iter : objects) {
        if (!(iter.second->mouseup(x, y, button, clicks, which)))
            return false;
    }
    return Object::mouseup(x, y, button, clicks, which);
}

bool GenEx::Layer::mousemotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel,
                               bool buttons[5], Uint32 which) {
    for (auto iter : objects) {
        if (!(iter.second->mousemotion(x, y, xrel, yrel, buttons, which)))
            return false;
    }
    return Object::mousemotion(x, y, xrel, yrel, buttons, which);
}

bool GenEx::Layer::mousewheel(bool flipped, Sint32 x, Sint32 y, Uint32 which) {
    for (auto iter : objects) {
        if (!(iter.second->mousewheel(flipped, x, y, which)))
            return false;
    }
    return Object::mousewheel(flipped, x, y, which);
}

bool GenEx::Layer::clipboardupdate(char text[]) {
    for (auto iter : objects) {
        if (!(iter.second->clipboardupdate(text)))
            return false;
    }
    return Object::clipboardupdate(text);
}

bool GenEx::Layer::filedrop(std::string filename) {
    for (auto iter : objects) {
        if (!(iter.second->filedrop(filename)))
            return false;
    }
    return Object::filedrop(filename);
}

bool GenEx::Layer::textdrop(char text[]) {
    for (auto iter : objects) {
        if (!(iter.second->textdrop(text)))
            return false;
    }
    return Object::textdrop(text);
}

bool GenEx::Layer::begindrop() {
    for (auto iter : objects) {
        if (!(iter.second->begindrop()))
            return false;
    }
    return Object::begindrop();
}

bool GenEx::Layer::completedrop() {
    for (auto iter : objects) {
        if (!(iter.second->completedrop()))
            return false;
    }
    return Object::completedrop();
}

bool GenEx::Layer::jaxis(SDL_JoystickID joystick_id, Uint8 axis, Sint16 value) {
    for (auto iter : objects) {
        if (!(iter.second->jaxis(joystick_id, axis, value)))
            return false;
    }
    return Object::jaxis(joystick_id, axis, value);
}

bool GenEx::Layer::jball(SDL_JoystickID joystick_id, Uint8 ball, Sint16 x, Sint16 y) {
    for (auto iter : objects) {
        if (!(iter.second->jball(joystick_id, ball, x, y)))
            return false;
    }
    return Object::jball(joystick_id, ball, x, y);
}

bool GenEx::Layer::jhat(SDL_JoystickID joystick_id, Uint8 hat, Uint8 value) {
    for (auto iter : objects) {
        if (!(iter.second->jhat(joystick_id, hat, value)))
            return false;
    }
    return Object::jhat(joystick_id, hat, value);
}

bool GenEx::Layer::jbtndown(SDL_JoystickID joystick_id, Uint8 button) {
    for (auto iter : objects) {
        if (!(iter.second->jbtndown(joystick_id, button)))
            return false;
    }
    return Object::jbtndown(joystick_id, button);
}

bool GenEx::Layer::jbtnup(SDL_JoystickID joystick_id, Uint8 button) {
    for (auto iter : objects) {
        if (!(iter.second->jbtnup(joystick_id, button)))
            return false;
    }
    return Object::jbtnup(joystick_id, button);
}

bool GenEx::Layer::caxis(SDL_JoystickID controller_id, Uint8 axis, Sint16 value) {
    for (auto iter : objects) {
        if (!(iter.second->caxis(controller_id, axis, value)))
            return false;
    }
    return Object::caxis(controller_id, axis, value);
}

bool GenEx::Layer::cbtndown(SDL_JoystickID controller_id, Uint8 button) {
    for (auto iter : objects) {
        if (!(iter.second->cbtndown(controller_id, button)))
            return false;
    }
    return Object::cbtndown(controller_id, button);
}

bool GenEx::Layer::cbtnup(SDL_JoystickID controller_id, Uint8 button) {
    for (auto iter : objects) {
        if (!(iter.second->cbtnup(controller_id, button)))
            return false;
    }
    return Object::cbtnup(controller_id, button);
}

bool GenEx::Layer::fingerdown(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                              float pressure) {
    for (auto iter : objects) {
        if (!(iter.second->fingerdown(touch_id, finger_id, x, y, pressure)))
            return false;
    }
    return Object::fingerdown(touch_id, finger_id, x, y, pressure);
}

bool GenEx::Layer::fingerup(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                            float pressure) {
    for (auto iter : objects) {
        if (!(iter.second->fingerup(touch_id, finger_id, x, y, pressure)))
            return false;
    }
    return Object::fingerup(touch_id, finger_id, x, y, pressure);
}

bool GenEx::Layer::fingermotion(SDL_TouchID touch_id, SDL_FingerID finger_id, float x, float y,
                                float dx, float dy, float pressure) {
    for (auto iter : objects) {
        if (!(iter.second->fingermotion(touch_id, finger_id, x, y, dx, dy, pressure)))
            return false;
    }
    return Object::fingermotion(touch_id, finger_id, x, y, dx, dy, pressure);
}

bool GenEx::Layer::gesturerecord(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                 Uint32 num_fingers, float x, float y) {
    for (auto iter : objects) {
        if (!(iter.second->gesturerecord(touch_id, gesture_id, num_fingers, x, y)))
            return false;
    }
    return Object::gesturerecord(touch_id, gesture_id, num_fingers, x, y);
}

bool GenEx::Layer::gestureperform(SDL_TouchID touch_id, SDL_GestureID gesture_id,
                                  Uint32 num_fingers, float x, float y, float error) {
    for (auto iter : objects) {
        if (!(iter.second->gestureperform(touch_id, gesture_id, num_fingers, x, y, error)))
            return false;
    }
    return Object::gestureperform(touch_id, gesture_id, num_fingers, x, y, error);
}

bool GenEx::Layer::multigesture(SDL_TouchID touch_id, Uint16 num_fingers, float x, float y,
                                float d_theta, float d_dist) {
   for (auto iter : objects) {
        if (!(iter.second->multigesture(touch_id, num_fingers, x, y, d_theta, d_dist)))
            return false;
    }
    return Object::multigesture(touch_id, num_fingers, x, y, d_theta, d_dist);
}

bool GenEx::Layer::userevent(Sint32 code, void *data1, void *data2) {
    for (auto iter : objects) {
        if (!(iter.second->userevent(code, data1, data2)))
            return false;
    }
    return Object::userevent(code, data1, data2);
}
