#pragma once

#ifndef _VEX_V5

#include <vector>
#include <functional>
#include "pros/ai_vision.h"

namespace pros
{
    namespace sim
    {
        void register_ai_vision_detection_callback(std::function<std::vector<pros::aivision_object_s_t>()> callback);
    }
}

#endif