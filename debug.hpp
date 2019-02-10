#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "base.hpp"

namespace GenEx {
    namespace Debug {
        /** \brief Returns a string representing the version of GenEx.
         *
         * \return std::string Version string
         *
         */
        std::string GetVersionString() {
            std::stringstream sst;
            sst << EX_NAME << ' ';
            switch (VERSION_STATE) {
            case 0:
                sst << "early_dev ";
                break;
            case 1:
                sst << "pre-alpha ";
                break;
            case 2:
                sst << "alpha ";
                break;
            case 3: // TBD
                break;
            default:
                break;
            }
            sst << 'v' << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH;
            return sst.str();
        }

        /** \brief Gets a string representing the orientation of the display.
         *
         * \param Uint8 <u>orientation</u>: An enumeration value representing the orientation
         *        of the display
         * \return std::string String representation of <i>orientation</i>
         *
         */
        std::string GetDisplayOrientationString(Uint8 orientation) {
            switch (orientation) {
            case SDL_ORIENTATION_LANDSCAPE:
                return "landscape";
            case SDL_ORIENTATION_LANDSCAPE_FLIPPED:
                return "landscape flipped";
            case SDL_ORIENTATION_PORTRAIT:
                return "portrait";
            case SDL_ORIENTATION_PORTRAIT_FLIPPED:
                return "portrait flipped";
            default:
                return "unknown";
            }
        }

        /** \brief Gets a string with all the information given in an SDL_DisplayEvent.
         *
         * \param SDL_DisplayEvent &<u>devent</u>: a display event
         * \return std::string String representation of <i>devent</i>
         *
         */
        std::string GetDisplayEventString(SDL_DisplayEvent &devent) {
            switch (devent.event) {
            case SDL_DISPLAYEVENT_ORIENTATION:
                return "orientation event {orientation=" +
                       GetDisplayOrientationString(devent.data1);
            default:
                return "{}";
            }
        }

        /** \brief Gets a string version of a joystick hat value.
         *
         * \param Uint8 <u>jhatval</u>: An enumeration value representing the hat value of a
         *        joystick
         * \return std::string String representation of <i>jhatval</i>
         *
         */
        std::string GetHatValue(Uint8 jhatval) {
            switch (jhatval) {
            case SDL_HAT_CENTERED:
                return "centered";
            case SDL_HAT_UP:
                return "up";
            case SDL_HAT_RIGHT:
                return "right";
            case SDL_HAT_DOWN:
                return "down";
            case SDL_HAT_LEFT:
                return "left";
            case SDL_HAT_LEFTDOWN:
                return "down-left";
            case SDL_HAT_LEFTUP:
                return "up-left";
            case SDL_HAT_RIGHTDOWN:
                return "down-right";
            case SDL_HAT_RIGHTUP:
                return "up-right";
            default:
                return "unknown";
            }
        }

        /** \brief Gets the string version of an SDL_WindowEvent event type.
         *
         * \param Uint8 <u>evt_type</u>: An enumeration value representing the event type of an
         *        SDL_WindowEvent
         * \return std::string String representation of <i>evt_type</i>
         *
         */
        std::string GetWindowEventString(Uint8 evt_type) {
            switch (evt_type) {
            case SDL_WINDOWEVENT_CLOSE:
                return "closed";
            case SDL_WINDOWEVENT_ENTER:
                return "entered";
            case SDL_WINDOWEVENT_EXPOSED:
                return "exposed";
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                return "gained focus";
            case SDL_WINDOWEVENT_FOCUS_LOST:
                return "lost focus";
            case SDL_WINDOWEVENT_HIDDEN:
                return "hidden";
            case SDL_WINDOWEVENT_HIT_TEST:
                return "hit test";
            case SDL_WINDOWEVENT_LEAVE:
                return "left";
            case SDL_WINDOWEVENT_MAXIMIZED:
                return "maximized";
            case SDL_WINDOWEVENT_MINIMIZED:
                return "minimized";
            case SDL_WINDOWEVENT_MOVED:
                return "moved";
            case SDL_WINDOWEVENT_NONE:
                return "none";
            case SDL_WINDOWEVENT_RESIZED:
                return "resized";
            case SDL_WINDOWEVENT_RESTORED:
                return "restored";
            case SDL_WINDOWEVENT_SHOWN:
                return "shown";
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                return "changed size";
            case SDL_WINDOWEVENT_TAKE_FOCUS:
                return "took focus";
            default:
                return "undefined";
            }
        }

        /** \brief Returns a string representing the window management subsystem SDL is using
         *        from an <i>SDL_SYSWM_TYPE</i> enum entry.
         *
         * \param SDL_SYSWM_TYPE <u>type</u>: Constant representing a subsystem type.
         * \return std::string String representation of <i>type</i>.
         *
         */
        std::string GetSubsystemString(SDL_SYSWM_TYPE type) {
            switch (type) {
            case SDL_SYSWM_WINDOWS:
                return "Microsoft Windows(TM)";
            case SDL_SYSWM_X11:
                return "X Window System";
            case SDL_SYSWM_WINRT:
                return "WinRT";
            case SDL_SYSWM_DIRECTFB:
                return "DirectFB";
            case SDL_SYSWM_COCOA:
                return "Cocoa (macOS)";
            case SDL_SYSWM_UIKIT:
                return "UIKit (iOS)";
            case SDL_SYSWM_WAYLAND:
                return "Wayland";
            case SDL_SYSWM_MIR:
                return "Mir";
            case SDL_SYSWM_ANDROID:
                return "Android";
            case SDL_SYSWM_VIVANTE:
                return "Vivante";
            case SDL_SYSWM_OS2:
                return "OS/2";
            case SDL_SYSWM_UNKNOWN:
                return "unknown";
            default:
                return "unknown";
            }
        }

        /** \brief Gets a string containing relevant information from an SDL_SysWMEvent.
         *
         * \param SDL_SysWMmsg *<u>msg</u>: A pointer to a system window management event message
         * \return std::string String representation of <i>msg</i>
         *
         */
        std::string GetSysWMEventString(SDL_SysWMmsg *msg) {
            std::stringstream sst;
            sst << "{subsystem=\"" << GetSubsystemString(msg->subsystem) << "\"";

#if defined(SDL_VIDEO_DRIVER_WINDOWS)
            sst << ",hwnd=" << msg->msg.win.hwnd << ",msg=" << msg->msg.win.msg <<
                   ",wParam" << msg->msg.win.wParam << "lParam" << msg->msg.win.lParam;
#endif
#if defined(SDL_VIDEO_DRIVER_X11)
            sst << ",display=" << msg->msg.x11.event.display << ",window=" <<
                   msg->msg.x11.event.window << ",serial=" << msg->msg.x11.event.serial;
#endif
#if defined(SDL_VIDEO_DRIVER_DIRECTFB)
            sst << ",clazz=" << msg->msg.dfb.event.clazz << ",window_id=" <<
                   msg->msg.dfb.event.window.window_id << ",type=" <<
                   msg->msg.dfb.event.window.type;
#endif

            sst << "}";
            return sst.str();
        }

        /** \brief Returns a string containing all the relevant information in an SDL_Event.
         *
         * \param SDL_Event &<u>event</u>: An SDL event
         * \return std::string String representation of <i>event</i>
         *
         */
        std::string GetEventString(SDL_Event &event) {
            std::string s = "unknown";
            std::string en = ",";
            switch (event.type) {
            case SDL_QUIT:
                s = "quit";
                break;
            case SDL_KEYDOWN:
                s = std::string("key '") + SDL_GetKeyName(event.key.keysym.sym) + "' down";
                break;
            case SDL_KEYUP:
                s = std::string("key '") + SDL_GetKeyName(event.key.keysym.sym) + "' up";
                break;
            case SDL_KEYMAPCHANGED:
                s = "key map changed";
                break;
            case SDL_SENSORUPDATE:
                s = "sensor " + std::to_string((int)event.sensor.which) + " \"" +
                    SDL_SensorGetName(SDL_SensorFromInstanceID(event.sensor.which)) +
                    "\" updated {data=[" + std::to_string(event.sensor.data[0]) + "," +
                    std::to_string(event.sensor.data[1]) + "," +
                    std::to_string(event.sensor.data[2]) + "," +
                    std::to_string(event.sensor.data[3]) + "," +
                    std::to_string(event.sensor.data[4]) + "," +
                    std::to_string(event.sensor.data[5]) + "]}";
                break;
            case SDL_TEXTEDITING:
                s = std::string("text editing {start=") + std::to_string((int)event.edit.start) +
                    ",length=" + std::to_string((int)event.edit.length) + ",text='" +
                    event.edit.text + "'}";
                break;
            case SDL_TEXTINPUT:
                s = std::string("text input '") + event.text.text + '\'';
                break;
            case SDL_MOUSEBUTTONDOWN:
                s = std::string("mouse btn ") + std::to_string((int)event.button.button) +
                    " down at pos (" + std::to_string((int)event.button.x) + ", " +
                    std::to_string((int)event.button.y) + ")";
                break;
            case SDL_MOUSEBUTTONUP:
                s = "mouse btn " + std::to_string((int)event.button.button) + " up at pos (" +
                    std::to_string((int)event.button.x) + ", " +
                    std::to_string((int)event.button.y) + ")";
                break;
            case SDL_MOUSEMOTION:
                s = "mouse motion {x=" + std::to_string((int)event.motion.x) + ",y=" +
                    std::to_string((int)event.motion.y) + ",xrel=" +
                    std::to_string((int)event.motion.xrel)+ ",yrel=" +
                    std::to_string((int)event.motion.yrel) + "}";
                break;
            case SDL_MOUSEWHEEL:
                s = std::string("mouse wheel motion {direction=") +
                    (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL ? "normal" : "flipped") +
                    ",x" + std::to_string((int)event.wheel.x) + ",y=" +
                    std::to_string((int)event.wheel.y) + "}";
                break;
            case SDL_WINDOWEVENT:
                s = "window event \"" + GetWindowEventString(event.window.event) +
                    "\" for window " + std::to_string((int)event.window.windowID);
                break;
            case SDL_SYSWMEVENT:
                s = "system window management event " + GetSysWMEventString(event.syswm.msg);
                break;
            case SDL_DROPBEGIN:
                s = "drop begin";
                break;
            case SDL_DROPCOMPLETE:
                s = "drop complete";
                break;
            case SDL_DROPFILE:
                s = "dropped file \"" + std::string(event.drop.file) + "\"";
                break;
            case SDL_DROPTEXT:
                s = "dropped text";
                break;
            case SDL_CLIPBOARDUPDATE:
                s = "clipboard updated";
                break;
            case SDL_FINGERDOWN:
                s = "finger down {dx=" + std::to_string(event.tfinger.dx) + ",dy=" +
                    std::to_string(event.tfinger.dy) + ",fingerId=" +
                    std::to_string((int)event.tfinger.fingerId) + ",pressure=" +
                    std::to_string(event.tfinger.pressure) + ",touchId=" +
                    std::to_string((int)event.tfinger.touchId) + ",x=" +
                    std::to_string(event.tfinger.x) + ",y=" +
                    std::to_string(event.tfinger.y) + "}";
                break;
            case SDL_FINGERUP:
                s = "finger up {dx=" + std::to_string(event.tfinger.dx) + ",dy=" +
                    std::to_string(event.tfinger.dy) + ",fingerId=" +
                    std::to_string((int)event.tfinger.fingerId) + ",pressure=" +
                    std::to_string(event.tfinger.pressure) + ",touchId=" +
                    std::to_string((int)event.tfinger.touchId) + ",x=" +
                    std::to_string(event.tfinger.x) + ",y=" +
                    std::to_string(event.tfinger.y) + "}";
                break;
            case SDL_FINGERMOTION:
                s = "finger motion {dx=" + std::to_string(event.tfinger.dx) + ",dy=" +
                    std::to_string(event.tfinger.dy) + ",fingerId=" +
                    std::to_string((int)event.tfinger.fingerId) + ",pressure=" +
                    std::to_string(event.tfinger.pressure) + ",touchId=" +
                    std::to_string((int)event.tfinger.touchId) + ",x=" +
                    std::to_string(event.tfinger.x) + ",y=" +
                    std::to_string(event.tfinger.y) + "}";
                break;
            case SDL_DOLLARGESTURE:
                s = "dollar gesture {gestureId" + std::to_string((int)event.dgesture.gestureId) +
                    ",numFingers=" + std::to_string((int)event.dgesture.numFingers) +
                    ",touchId=" + std::to_string((int)event.dgesture.touchId) + ",x=" +
                    std::to_string(event.dgesture.x) + + ",y=" +
                    std::to_string(event.dgesture.y) + "}";
                break;
            case SDL_DOLLARRECORD:
                s = "dollar record {gestureId" + std::to_string((int)event.dgesture.gestureId) +
                    ",numFingers=" + std::to_string((int)event.dgesture.numFingers) +
                    ",touchId=" + std::to_string((int)event.dgesture.touchId) + ",x=" +
                    std::to_string(event.dgesture.x) + + ",y=" +
                    std::to_string(event.dgesture.y) + "}";
                break;
            case SDL_MULTIGESTURE:
                s = "multigesture {dDist=" + std::to_string(event.mgesture.dDist) + ",dTheta=" +
                    std::to_string(event.mgesture.dTheta) + ",numFingers=" +
                    std::to_string((int)event.dgesture.numFingers) + + ",touchId=" +
                    std::to_string((int)event.mgesture.touchId) + ",x=" +
                    std::to_string(event.mgesture.x) + + ",y=" +
                    std::to_string(event.mgesture.y) + "}";
                break;
            case SDL_AUDIODEVICEADDED:
                s = "audio " + std::string(event.adevice.iscapture ? "capture" : "") +
                    " device " + std::to_string((int)event.adevice.which) + "added";
                break;
            case SDL_AUDIODEVICEREMOVED:
                s = "audio " + std::string(event.adevice.iscapture ? "capture" : "") +
                    " device " + std::to_string((int)event.adevice.which) + "removed";
                break;
            case SDL_APP_DIDENTERBACKGROUND:
                s = "entered background";
                break;
            case SDL_APP_DIDENTERFOREGROUND:
                s = "entered foreground";
                break;
            case SDL_APP_LOWMEMORY:
                s = "low memory warning";
                break;
            case SDL_APP_WILLENTERBACKGROUND:
                s = "entering background";
                break;
            case SDL_APP_WILLENTERFOREGROUND:
                s = "entering foreground";
                break;
            case SDL_JOYAXISMOTION:
                s = "joystick axis " + std::to_string((int)event.jaxis.axis) +
                    " motion on joystick " + std::to_string((int)event.jaxis.which) +
                    " moved to value " + std::to_string((int)event.jaxis.value);
                break;
            case SDL_JOYBALLMOTION:
                s = "joystick ball " + std::to_string((int)event.jball.ball) +
                    " motion on joystick " + std::to_string((int)event.jball.which) +
                    ", relative motion (" + std::to_string((int)event.jball.xrel) + ", " +
                    std::to_string((int)event.jball.yrel) + ")";
                break;
            case SDL_JOYBUTTONDOWN:
                s = "joystick btn " + std::to_string((int)event.jbutton.button) +
                    " down on joystick " + std::to_string((int)event.jbutton.which);
                break;
            case SDL_JOYBUTTONUP:
                s = "joystick btn " + std::to_string((int)event.jbutton.button) +
                    " up on joystick " + std::to_string((int)event.jbutton.which);
                break;
            case SDL_JOYHATMOTION:
                s = "joystick hat " + std::to_string((int)event.jhat.hat) +
                    " motion on joystick " + std::to_string((int)event.jhat.which) +
                    " to state \"" + GetHatValue(event.jhat.value) + "\"";
                break;
            case SDL_JOYDEVICEADDED:
                s = "joystick " + std::to_string((int)event.jdevice.which) + " added";
                break;
            case SDL_JOYDEVICEREMOVED:
                s = "joystick " + std::to_string((int)event.jdevice.which) + " removed";
                break;
            case SDL_CONTROLLERAXISMOTION:
                s = "controller axis " + std::to_string((int)event.caxis.axis) +
                    " motion on controller " + std::to_string((int)event.caxis.which) +
                    "moved to value" + std::to_string((int)event.caxis.value);
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                s = "controller btn " + std::to_string((int)event.cbutton.button) +
                    "down on controller " + std::to_string((int)event.cbutton.which);
                break;
            case SDL_CONTROLLERBUTTONUP:
                s = "controller btn " + std::to_string((int)event.cbutton.button) +
                "up on controller " + std::to_string((int)event.cbutton.which);
                break;
            case SDL_CONTROLLERDEVICEADDED:
                s = "controller " + std::to_string((int)event.cdevice.which) + " added";
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                s = "controller " + std::to_string((int)event.cdevice.which) + " removed";
                break;
            case SDL_CONTROLLERDEVICEREMAPPED:
                s = "controller " + std::to_string((int)event.cdevice.which) + " remapped";
                break;
            case SDL_RENDER_TARGETS_RESET:
                s = "render targets reset";
                break;
            case SDL_RENDER_DEVICE_RESET:
                s = "render device reset";
                break;
            case SDL_DISPLAYEVENT:
                s = "display event on display " + std::to_string((int)event.display.display) +
                    ": " + GetDisplayEventString(event.display);
                break;
            case SDL_USEREVENT:
                s = "user-defined event {code=" + std::to_string((int)event.user.code) + "}";
                break;
            default:
                break;
            }
            return s;
        }

        /** \brief Returns a string containing all the relevant information in an SDL_Event.
         *
         * \param SDL_Event *<u>event</u>: Pointer to an SDL event
         * \return std::string String representation of <i>event</i>
         *
         */
         std::string GetEventString(SDL_Event *event) {
            return GetEventString(*event);
        }

    }
}

#endif // DEBUG_HPP
