#include "simgui.h"
#include <format>

static float NormalizeStick(Sint16 value)
{
    const float result = value < 0
                             ? static_cast<float>(value) / 32768.0f
                             : static_cast<float>(value) / 32767.0f;

    return result;
}

static float NormalizeAxis(Sint16 value)
{
    return std::clamp(
        static_cast<float>(value) / 32767.0f,
        0.0f, 1.0f);
}

static void ReadController(SDL_Gamepad *gamepad,
                           ControllerState &state)
{
    state = {};

    if (!gamepad)
        return;

    state.left.x = NormalizeStick(
        SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTX));
    state.left.y = NormalizeStick(
        SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTY));

    state.right.x = NormalizeStick(
        SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_RIGHTX));
    state.right.y = NormalizeStick(
        SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_RIGHTY));

    state.left.clicked =
        SDL_GetGamepadButton(gamepad, SDL_GAMEPAD_BUTTON_LEFT_STICK);
    state.right.clicked =
        SDL_GetGamepadButton(gamepad, SDL_GAMEPAD_BUTTON_RIGHT_STICK);

    state.leftTrigger = NormalizeAxis(
        SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER));
    state.rightTrigger = NormalizeAxis(
        SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER));

    for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i)
    {
        state.buttons[static_cast<std::size_t>(i)] =
            SDL_GetGamepadButton(
                gamepad, static_cast<SDL_GamepadButton>(i));
    }
}

namespace Draw
{

    using List = ImDrawList;

    static constexpr ImU32 Background = IM_COL32(17, 20, 29, 255);
    static constexpr ImU32 Body = IM_COL32(45, 51, 66, 255);
    static constexpr ImU32 BodyEdge = IM_COL32(90, 101, 123, 255);
    static constexpr ImU32 Surface = IM_COL32(27, 32, 44, 255);
    static constexpr ImU32 White = IM_COL32(235, 240, 250, 255);
    static constexpr ImU32 Muted = IM_COL32(135, 148, 170, 255);
    static constexpr ImU32 Green = IM_COL32(66, 222, 143, 255);
    static constexpr ImU32 Blue = IM_COL32(65, 158, 255, 255);
    static constexpr ImU32 Yellow = IM_COL32(255, 202, 74, 255);
    static constexpr ImU32 Red = IM_COL32(255, 91, 106, 255);

    static void Circle(List *dl, float centerX, float centerY, float radius,
                       ImU32 fill, ImU32 outline, float thickness = 2.0f)
    {
        dl->AddCircleFilled({centerX, centerY}, radius, fill, 48);
        dl->AddCircle({centerX, centerY}, radius, outline, 48, thickness);
    }

    static void RoundedRect(List *dl, float centerX, float centerY, float width, float height,
                            ImU32 fill, ImU32 outline,
                            float rounding = 8.0f)
    {
        ImVec2 min = {centerX - width / 2.0f, centerY - height / 2.0f};
        ImVec2 max = {centerX + width / 2.0f, centerY + height / 2.0f};

        dl->AddRectFilled(min, max, fill, rounding);
        dl->AddRect(min, max, outline, rounding, 2.0f);
    }

    static void DrawButton(List *dl, float centerX, float centerY, float radius, bool pressed)
    {
        const ImU32 fill = pressed ? Blue : IM_COL32(37, 43, 57, 255);
        const ImU32 edge = pressed ? White : IM_COL32(100, 112, 135, 255);

        Circle(dl, centerX, centerY, radius, fill, edge, pressed ? 3.0f : 2.0f);
    }

    static void DrawButton(List *dl, float centerX, float centerY, float width, float height, bool pressed)
    {
        const ImU32 fill = pressed ? Blue : IM_COL32(37, 43, 57, 255);
        const ImU32 edge = pressed ? White : IM_COL32(100, 112, 135, 255);

        RoundedRect(dl, centerX, centerY, width, height, fill, edge);
    }

    static void DrawStick(List *dl, float centerX, float centerY, float radius, float scale, const Stick &stick)
    {
        Circle(dl, centerX, centerY, radius,
               IM_COL32(24, 29, 40, 255),
               stick.clicked ? Green : BodyEdge,
               stick.clicked ? 4.0f * scale : 2.0f * scale);

        const float margin = 20 * scale;
        const float travel = radius - margin - 9.0f * scale;

        Circle(dl, centerX + stick.x * travel, centerY + stick.y * travel, radius - margin,
               stick.clicked ? IM_COL32(66, 222, 143, 255)
                             : IM_COL32(76, 87, 108, 255),
               stick.clicked ? White : IM_COL32(139, 153, 178, 255),
               4.0f * scale);
    }

    static void DrawAxis(List *dl, float centerX, float centerY, float width, float height, float value)
    {
        RoundedRect(dl, centerX, centerY, width, height,
                    IM_COL32(25, 30, 41, 255),
                    BodyEdge, 6.0f);

        const float inner = height - 8.0f;
        const float filled = inner * std::clamp(value, 0.0f, 1.0f);

        if (filled > 0.0f)
        {
            const float bottom = centerY + height / 2.0f - 4.0f;
            RoundedRect(dl,
                        centerX, bottom - filled / 2.0f,
                        width - 8.0f, filled,
                        value > 0.25f ? Green : Blue,
                        value > 0.25f ? Green : Blue, 4.0f);
        }
    }
} // namespace Draw

static void DrawController(const ControllerState &s)
{
    using namespace Draw;

    ImDrawList *dl = ImGui::GetWindowDrawList();
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const ImVec2 avail = ImGui::GetContentRegionAvail();

    constexpr float canvasWidth = 1920.0f;
    constexpr float canvasHeight = 820.0f;

    const float scale = std::max(0.1f, std::min(
                                           avail.x / canvasWidth, avail.y / canvasHeight));

    const ImVec2 canvasSize = {canvasWidth * scale, canvasHeight * scale};

    dl->AddRectFilled(origin, {origin.x + canvasSize.x, origin.y + canvasSize.y}, Background, 12.0f);
    dl->PushClipRect(origin, {origin.x + canvasSize.x, origin.y + canvasSize.y}, true);

    const auto pressed = [&](SDL_GamepadButton button)
    {
        return s.buttons[static_cast<std::size_t>(button)];
    };

    DrawButton(dl, origin.x + 510 * scale, origin.y + 195 * scale,
               240 * scale, 75 * scale,
               pressed(SDL_GAMEPAD_BUTTON_LEFT_SHOULDER));

    DrawButton(dl, origin.x + 1410 * scale, origin.y + 195 * scale,
               240 * scale, 75 * scale,
               pressed(SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER));

    DrawAxis(dl, origin.x + 510 * scale, origin.y + 75 * scale,
             240 * scale, 75 * scale,
             s.leftTrigger);

    DrawAxis(dl, origin.x + 1410 * scale, origin.y + 75 * scale,
             240 * scale, 75 * scale,
             s.rightTrigger);

    DrawButton(dl, origin.x + 662 * scale, origin.y + 551 * scale, 60 * scale, 90 * scale, pressed(SDL_GAMEPAD_BUTTON_DPAD_UP));
    DrawButton(dl, origin.x + 662 * scale, origin.y + 734 * scale, 60 * scale, 90 * scale, pressed(SDL_GAMEPAD_BUTTON_DPAD_DOWN));
    DrawButton(dl, origin.x + 572 * scale, origin.y + 643 * scale, 90 * scale, 60 * scale, pressed(SDL_GAMEPAD_BUTTON_DPAD_LEFT));
    DrawButton(dl, origin.x + 752 * scale, origin.y + 643 * scale, 90 * scale, 60 * scale, pressed(SDL_GAMEPAD_BUTTON_DPAD_RIGHT));

    DrawStick(dl, origin.x + 465 * scale, origin.y + 445 * scale, 90 * scale, scale, s.left);
    DrawStick(dl, origin.x + 1450 * scale, origin.y + 445 * scale, 90 * scale, scale, s.right);

    DrawButton(dl, origin.x + 1258 * scale, origin.y + 551 * scale, 45 * scale,
               pressed(SDL_GAMEPAD_BUTTON_NORTH));
    DrawButton(dl, origin.x + 1258 * scale, origin.y + 734 * scale, 45 * scale,
               pressed(SDL_GAMEPAD_BUTTON_SOUTH));
    DrawButton(dl, origin.x + 1168 * scale, origin.y + 643 * scale, 45 * scale,
               pressed(SDL_GAMEPAD_BUTTON_WEST));
    DrawButton(dl, origin.x + 1349 * scale, origin.y + 643 * scale, 45 * scale,
               pressed(SDL_GAMEPAD_BUTTON_EAST));

    const ImU32 backFill = pressed(SDL_GAMEPAD_BUTTON_BACK)
                               ? Blue
                               : IM_COL32(38, 45, 58, 255);
    const ImU32 startFill = pressed(SDL_GAMEPAD_BUTTON_START)
                                ? Blue
                                : IM_COL32(38, 45, 58, 255);

    RoundedRect(dl, origin.x + 881 * scale, origin.y + 355 * scale, 60, 40, backFill, BodyEdge, 8.0f);
    RoundedRect(dl, origin.x + 1041 * scale, origin.y + 355 * scale, 60, 40, startFill, BodyEdge, 8.0f);

    Circle(dl, origin.x + 961 * scale, origin.y + 688 * scale, 51 * scale,
           pressed(SDL_GAMEPAD_BUTTON_GUIDE)
               ? Green
               : IM_COL32(38, 45, 58, 255),
           pressed(SDL_GAMEPAD_BUTTON_GUIDE) ? White : BodyEdge);

    dl->PopClipRect();

    ImGui::Dummy(canvasSize);
}

static GamepadPtr OpenFirstGamepad()
{
    int count = 0;
    SDL_JoystickID *ids = SDL_GetGamepads(&count);

    GamepadPtr result;

    if (ids)
    {
        for (int i = 0; i < count; ++i)
        {
            if (SDL_Gamepad *pad = SDL_OpenGamepad(ids[i]))
            {
                result.reset(pad);
                break;
            }
        }

        SDL_free(ids);
    }

    return result;
}

void frame(GamepadPtr &gamepad, ControllerState &state)
{
    if (ImGui::Begin(std::format("Controller - {0}###Controller", gamepad ? SDL_GetGamepadName(gamepad.get()) : "Not Connected").c_str(), nullptr))
    {
        DrawController(state);
    }
    ImGui::End();
}

int runGui()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

    // Create SDL window graphics context
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    SDL_Window *window = SDL_CreateWindow("Robot Simulation", (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Create GPU Device
    SDL_GPUDevice *gpu_device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_METALLIB, true, nullptr);
    if (gpu_device == nullptr)
    {
        printf("Error: SDL_CreateGPUDevice(): %s\n", SDL_GetError());
        return 1;
    }

    // Claim window for GPU Device
    if (!SDL_ClaimWindowForGPUDevice(gpu_device, window))
    {
        printf("Error: SDL_ClaimWindowForGPUDevice(): %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetGPUSwapchainParameters(gpu_device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigDpiScaleFonts = true;                        // Enable automatic DPI scaling of fonts based on monitor DPI
    io.ConfigDpiScaleViewports = true;                    // Enable automatic DPI scaling of viewports based on monitor DPI

    // Setup Dear ImGui style
    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::StyleColorsDark();
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;

    // Setup scaling
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale; // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLGPU(window);
    ImGui_ImplSDLGPU3_InitInfo init_info = {};
    init_info.Device = gpu_device;
    init_info.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(gpu_device, window);
    init_info.MSAASamples = SDL_GPU_SAMPLECOUNT_1;                     // Only used in multi-viewports mode.
    init_info.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR; // Only used in multi-viewports mode.
    init_info.PresentMode = SDL_GPU_PRESENTMODE_VSYNC;
    ImGui_ImplSDLGPU3_Init(&init_info);

    ImVec4 clear_color = ImVec4(32 / 255.0f, 33 / 255.0f, 36 / 255.0f, 1.00f);

    GamepadPtr gamepad = OpenFirstGamepad();
    ControllerState state;

    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
                done = true;

            if (event.type == SDL_EVENT_GAMEPAD_ADDED && !gamepad)
                gamepad.reset(SDL_OpenGamepad(event.gdevice.which));

            if (event.type == SDL_EVENT_GAMEPAD_REMOVED && gamepad)
            {
                if (event.gdevice.which ==
                    SDL_GetGamepadID(gamepad.get()))
                {
                    gamepad.reset();
                    gamepad = OpenFirstGamepad();
                }
            }

            if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP)
            {
                switch (event.key.key)
                {
                case SDLK_W:
                    break;
                case SDLK_S:
                    break;
                case SDLK_A:
                    break;
                case SDLK_D:
                    break;
                }
            }
        }

        ReadController(gamepad.get(), state);

#ifdef AS_LIBRARY

        vexSimControllerConnectionStatusSet(kControllerMaster, gamepad ? kV5ControllerVexnet : kV5ControllerOffline);

        vexSimControllerSet(kControllerMaster, AnaLeftX, static_cast<int32_t>(state.left.x * 127));
        vexSimControllerSet(kControllerMaster, AnaLeftY, static_cast<int32_t>(-state.left.y * 127));
        vexSimControllerSet(kControllerMaster, AnaRightX, static_cast<int32_t>(state.right.x * 127));
        vexSimControllerSet(kControllerMaster, AnaRightY, static_cast<int32_t>(-state.right.y * 127));

        vexSimControllerSet(kControllerMaster, ButtonL1, state.buttons[SDL_GAMEPAD_BUTTON_LEFT_SHOULDER] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonL2, state.leftTrigger > 0.25f ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonR1, state.buttons[SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonR2, state.rightTrigger > 0.25f ? 127 : 0);

        vexSimControllerSet(kControllerMaster, ButtonUp, state.buttons[SDL_GAMEPAD_BUTTON_DPAD_UP] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonDown, state.buttons[SDL_GAMEPAD_BUTTON_DPAD_DOWN] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonLeft, state.buttons[SDL_GAMEPAD_BUTTON_DPAD_LEFT] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonRight, state.buttons[SDL_GAMEPAD_BUTTON_DPAD_RIGHT] ? 127 : 0);

        vexSimControllerSet(kControllerMaster, ButtonX, state.buttons[SDL_GAMEPAD_BUTTON_NORTH] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonB, state.buttons[SDL_GAMEPAD_BUTTON_SOUTH] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonY, state.buttons[SDL_GAMEPAD_BUTTON_WEST] ? 127 : 0);
        vexSimControllerSet(kControllerMaster, ButtonA, state.buttons[SDL_GAMEPAD_BUTTON_EAST] ? 127 : 0);

        vexSimControllerSet(kControllerMaster, ButtonSEL, state.buttons[SDL_GAMEPAD_BUTTON_GUIDE] ? 127 : 0);

        vexSimControllerSet(kControllerMaster, BatteryLevel, 100);
        vexSimControllerSet(kControllerMaster, BatteryCapacity, 100);
#endif

        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLGPU3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        frame(gamepad, state);

        // Rendering
        ImGui::Render();
        ImDrawData *draw_data = ImGui::GetDrawData();
        const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);

        SDL_GPUCommandBuffer *command_buffer = SDL_AcquireGPUCommandBuffer(gpu_device); // Acquire a GPU command buffer

        SDL_GPUTexture *swapchain_texture;
        SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer, window, &swapchain_texture, nullptr, nullptr); // Acquire a swapchain texture

        if (swapchain_texture != nullptr && !is_minimized)
        {
            // This is mandatory: call ImGui_ImplSDLGPU3_PrepareDrawData() to upload the vertex/index buffer!
            ImGui_ImplSDLGPU3_PrepareDrawData(draw_data, command_buffer);

            // Setup and start a render pass
            SDL_GPUColorTargetInfo target_info = {};
            target_info.texture = swapchain_texture;
            target_info.clear_color = SDL_FColor{clear_color.x, clear_color.y, clear_color.z, clear_color.w};
            target_info.load_op = SDL_GPU_LOADOP_CLEAR;
            target_info.store_op = SDL_GPU_STOREOP_STORE;
            target_info.mip_level = 0;
            target_info.layer_or_depth_plane = 0;
            target_info.cycle = false;
            SDL_GPURenderPass *render_pass = SDL_BeginGPURenderPass(command_buffer, &target_info, 1, nullptr);

            // Render ImGui
            ImGui_ImplSDLGPU3_RenderDrawData(draw_data, command_buffer, render_pass);

            SDL_EndGPURenderPass(render_pass);
        }

        // Submit the command buffer
        SDL_SubmitGPUCommandBuffer(command_buffer);
    }

    // Cleanup
    gamepad.reset();

    SDL_WaitForGPUIdle(gpu_device);
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLGPU3_Shutdown();
    ImGui::DestroyContext();

    SDL_ReleaseWindowFromGPUDevice(gpu_device, window);
    SDL_DestroyGPUDevice(gpu_device);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
