#pragma once

#include <cstdint>
#include <sys/time.h>

namespace pwswd {

    static constexpr std::uint32_t PowerButtonShortPressDuration = 300E3;
    static constexpr std::uint32_t PowerButtonLongPressDuration = 2E6;

    static constexpr std::uint16_t JoyStickXAxisCenter = 1730;
    static constexpr std::uint16_t JoyStickYAxisCenter = 1620;
    static constexpr std::uint16_t JoyStickDeadZone = 350;
    static constexpr std::uint16_t JoyStickSpeedDownscaler = 200;

    enum class EventType {
        Synchronization     = 0,
        Buttons             = 1,
        RelativeAxes        = 2
    };

    enum class SynchronizationEvent {
        Report = 0,
        Config = 1,
        MTReport = 2,
        Dropped = 3
    };

    enum class ButtonState {
        Released    = 0,
        Pressed     = 1,
        Held        = 2
    };

    enum class RelativeAxis {
        AxisX  = 0,
        AxisY  = 1,
        AxisRX = 3,
        AxisRY = 4
    };

    enum class Button {
        Select      = 1,
        Start       = 28,

        A           = 29,
        B           = 56,
        X           = 57,
        Y           = 42,

        L1          = 15,
        L2          = 104,
        L3          = 98,
        R1          = 14,
        R2          = 109,
        R3          = 83,

        Home        = 102,
        DpadUp      = 103,
        DpadDown    = 108,
        DpadLeft    = 105,
        DpadRight   = 106,

        Power       = 116,
        VolumeUp    = 115,
        VolumeDown  = 114,

        MouseLeft   = 272,
        MouseRight  = 273,
        MouseMiddle = 274
    };

    struct InputEvent {
        struct timeval time;
        std::uint16_t type;
        std::uint16_t code;
        std::int32_t value;
    };

    enum class MouseMode {
        Deactivated,
        LeftJoyStick,
        RightJoyStick
    };

    static inline std::uint64_t toMicroSeconds(const timeval time) {
        return time.tv_sec * 1E6 + time.tv_usec;
    }

    static inline InputEvent createButtonInputEvent(Button button, ButtonState state) {
        pwswd::InputEvent event;

        gettimeofday(&event.time, nullptr);
        event.type = static_cast<std::uint16_t>(EventType::Buttons);
        event.code = static_cast<std::uint16_t>(button);
        event.value = static_cast<std::int32_t>(state);

        return event;
    }

    static inline InputEvent createRelativeAxisInputEvent(RelativeAxis axis, std::int32_t value) {
        pwswd::InputEvent event;

        gettimeofday(&event.time, nullptr);
        event.type = static_cast<std::uint16_t>(EventType::RelativeAxes);
        event.code = static_cast<std::uint16_t>(axis);
        event.value = value;

        return event;        
    }

    static inline InputEvent createSyncEvent() {
        pwswd::InputEvent event;

        gettimeofday(&event.time, nullptr);
        event.type = static_cast<std::uint16_t>(EventType::Synchronization);
        event.code = static_cast<std::uint16_t>(SynchronizationEvent::Report);
        event.value = 0;

        return event;
    }

}