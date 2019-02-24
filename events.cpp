/**
 * \file events.cpp
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
 * The source file for event typedefs and default event handler functions.
 *
 */

#include "events.hpp"

GenEx::Events::EventHandlers GenEx::Events::GenerateEventHandlerStruct() {
    GenEx::Events::EventHandlers evt_handlers;

    evt_handlers.init            = GenEx::Events::InitEventHandler;
    evt_handlers.destroy         = GenEx::Events::DestroyEventHandler;
    evt_handlers.render          = GenEx::Events::RenderEventHandler;
    evt_handlers.update          = GenEx::Events::UpdateEventHandler;
    evt_handlers.targetreset     = GenEx::Events::TargetResetEventHandler;
    evt_handlers.windowevent     = GenEx::Events::WindowEventHandler;
    evt_handlers.keydown         = GenEx::Events::KeyDownEventHandler;
    evt_handlers.keyup           = GenEx::Events::KeyUpEventHandler;
    evt_handlers.textinput       = GenEx::Events::TextInputEventHandler;
    evt_handlers.textediting     = GenEx::Events::TextEditingEventHandler;
    evt_handlers.mousedown       = GenEx::Events::MouseButtonDownEventHandler;
    evt_handlers.mouseup         = GenEx::Events::MouseButtonUpEventHandler;
    evt_handlers.mousemotion     = GenEx::Events::MouseMotionEventHandler;
    evt_handlers.mousewheel      = GenEx::Events::MouseWheelEventHandler;
    evt_handlers.clipboardupdate = GenEx::Events::ClipboardUpdateEventHandler;
    evt_handlers.filedrop        = GenEx::Events::DropFileEventHandler;
    evt_handlers.textdrop        = GenEx::Events::DropTextEventHandler;
    evt_handlers.begindrop       = GenEx::Events::DropBeginEventHandler;
    evt_handlers.completedrop    = GenEx::Events::DropCompleteEventHandler;
    evt_handlers.jaxis           = GenEx::Events::JoystickAxisEventHandler;
    evt_handlers.jball           = GenEx::Events::JoystickTrackballEventHandler;
    evt_handlers.jhat            = GenEx::Events::JoystickHatEventHandler;
    evt_handlers.jbtndown        = GenEx::Events::JoystickButtonDownEventHandler;
    evt_handlers.jbtnup          = GenEx::Events::JoystickButtonUpEventHandler;
    evt_handlers.caxis           = GenEx::Events::ControllerAxisEventHandler;
    evt_handlers.cbtndown        = GenEx::Events::ControllerButtonDownEventHandler;
    evt_handlers.cbtnup          = GenEx::Events::ControllerButtonUpEventHandler;
    evt_handlers.fingerdown      = GenEx::Events::FingerDownEventHandler;
    evt_handlers.fingerup        = GenEx::Events::FingerUpEventHandler;
    evt_handlers.fingermotion    = GenEx::Events::FingerMotionEventHandler;
    evt_handlers.gesturerecord   = GenEx::Events::RecordGestureEventHandler;
    evt_handlers.gestureperform  = GenEx::Events::PerformGestureEventHandler;
    evt_handlers.multigesture    = GenEx::Events::MultiGestureEventHandler;
    evt_handlers.userevent       = GenEx::Events::UserEventHandler;

    return evt_handlers;
}
