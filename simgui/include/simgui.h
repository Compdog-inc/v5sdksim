#pragma once

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlgpu3.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#include <array>
#include <algorithm>
#include <memory>

#include <vex/v5.h>

#include "simgui.h"

struct GamepadDeleter
{
    void operator()(SDL_Gamepad *p) const
    {
        if (p)
            SDL_CloseGamepad(p);
    }
};

using GamepadPtr = std::unique_ptr<SDL_Gamepad, GamepadDeleter>;

struct Stick
{
    float x = 0.0f;
    float y = 0.0f;
    bool clicked = false;
};

struct ControllerState
{
    Stick left;
    Stick right;

    float leftTrigger = 0.0f;
    float rightTrigger = 0.0f;

    std::array<bool, SDL_GAMEPAD_BUTTON_COUNT> buttons{};
};

void frame(GamepadPtr &gamepad, ControllerState &state);

int runGui();