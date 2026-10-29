#include "simgui.h"
#include <format>

#include <imgui_internal.h>

enum class CompetitionMode
{
    Disabled,
    Autonomous,
    Teleop,
    Count
};

struct CompetitionState
{
    CompetitionMode mode = CompetitionMode::Teleop;
    bool connected = false;
};

std::string competitionStateToString(CompetitionMode state)
{
    switch (state)
    {
    case CompetitionMode::Disabled:
        return "Disabled";
    case CompetitionMode::Autonomous:
        return "Autonomous";
    case CompetitionMode::Teleop:
        return "Teleop";
    default:
        return "Unknown";
    }
}

struct SimGuiSettings
{
    SDL_Scancode leftXNeg = SDL_SCANCODE_A;
    SDL_Scancode leftXPos = SDL_SCANCODE_D;

    SDL_Scancode leftYNeg = SDL_SCANCODE_W;
    SDL_Scancode leftYPos = SDL_SCANCODE_S;

    SDL_Scancode rightXNeg = SDL_SCANCODE_J;
    SDL_Scancode rightXPos = SDL_SCANCODE_L;

    SDL_Scancode rightYNeg = SDL_SCANCODE_I;
    SDL_Scancode rightYPos = SDL_SCANCODE_K;

    SDL_Scancode leftButtonUp = SDL_SCANCODE_F;
    SDL_Scancode leftButtonDown = SDL_SCANCODE_C;
    SDL_Scancode leftButtonLeft = SDL_SCANCODE_X;
    SDL_Scancode leftButtonRight = SDL_SCANCODE_V;

    SDL_Scancode rightButtonUp = SDL_SCANCODE_H;
    SDL_Scancode rightButtonDown = SDL_SCANCODE_N;
    SDL_Scancode rightButtonLeft = SDL_SCANCODE_B;
    SDL_Scancode rightButtonRight = SDL_SCANCODE_M;

    SDL_Scancode buttonSelect = SDL_SCANCODE_SPACE;

    SDL_Scancode buttonL1 = SDL_SCANCODE_Q;
    SDL_Scancode buttonL2 = SDL_SCANCODE_E;

    SDL_Scancode buttonR1 = SDL_SCANCODE_U;
    SDL_Scancode buttonR2 = SDL_SCANCODE_O;
};

struct KeyBinding
{
    const char *name;
    SDL_Scancode *key;
};

static SimGuiSettings settings;

static KeyBinding keyBindings[] = {
    {"Left X -", &settings.leftXNeg},
    {"Left X +", &settings.leftXPos},
    {"Left Y -", &settings.leftYNeg},
    {"Left Y +", &settings.leftYPos},

    {"Right X -", &settings.rightXNeg},
    {"Right X +", &settings.rightXPos},
    {"Right Y -", &settings.rightYNeg},
    {"Right Y +", &settings.rightYPos},

    {"Up", &settings.leftButtonUp},
    {"Down", &settings.leftButtonDown},
    {"Left", &settings.leftButtonLeft},
    {"Right", &settings.leftButtonRight},

    {"X", &settings.rightButtonUp},
    {"B", &settings.rightButtonDown},
    {"Y", &settings.rightButtonLeft},
    {"A", &settings.rightButtonRight},

    {"Select", &settings.buttonSelect},
    {"L1", &settings.buttonL1},
    {"L2", &settings.buttonL2},
    {"R1", &settings.buttonR1},
    {"R2", &settings.buttonR2},
};

static int waitingForKey = -1;

static void ReadInit(ImGuiContext *, ImGuiSettingsHandler *) {}

static void *ReadOpen(
    ImGuiContext *, ImGuiSettingsHandler *handler,
    const char *name)
{
    return strcmp(name, "Settings") == 0
               ? handler->UserData
               : nullptr;
}

template <std::size_t N, std::size_t M>
consteval auto concat(const char (&a)[N], const char (&b)[M])
{
    struct Result
    {
        char value[N + M - 1]{};

        constexpr const char *c_str() const { return value; }
    };

    Result result{};

    for (std::size_t i = 0; i < N - 1; ++i)
        result.value[i] = a[i];

    for (std::size_t i = 0; i < M; ++i)
        result.value[N - 1 + i] = b[i];

    return result;
}

template <bool AddNewLine = false, std::size_t N>
consteval auto concatFormatString(const char (&format)[N])
{
    if constexpr (AddNewLine)
        return concat(format, std::is_unsigned_v<std::underlying_type_t<SDL_Scancode>> ? "%u\n" : "%d\n");
    else
        return concat(format, std::is_unsigned_v<std::underlying_type_t<SDL_Scancode>> ? "%u\0" : "%d\0");
}

static void ReadLine(
    ImGuiContext *, ImGuiSettingsHandler *,
    void *entry, const char *line)
{
    auto *s = static_cast<SimGuiSettings *>(entry);

    if (sscanf(line, concatFormatString("LeftXNeg=").c_str(), &s->leftXNeg) == 1)
        return;

    if (sscanf(line, concatFormatString("LeftXPos=").c_str(), &s->leftXPos) == 1)
        return;

    if (sscanf(line, concatFormatString("LeftYNeg=").c_str(), &s->leftYNeg) == 1)
        return;

    if (sscanf(line, concatFormatString("LeftYPos=").c_str(), &s->leftYPos) == 1)
        return;

    if (sscanf(line, concatFormatString("RightXNeg=").c_str(), &s->rightXNeg) == 1)
        return;

    if (sscanf(line, concatFormatString("RightXPos=").c_str(), &s->rightXPos) == 1)
        return;

    if (sscanf(line, concatFormatString("RightYNeg=").c_str(), &s->rightYNeg) == 1)
        return;

    if (sscanf(line, concatFormatString("RightYPos=").c_str(), &s->rightYPos) == 1)
        return;

    if (sscanf(line, concatFormatString("LeftButtonUp=").c_str(), &s->leftButtonUp) == 1)
        return;

    if (sscanf(line, concatFormatString("LeftButtonDown=").c_str(), &s->leftButtonDown) == 1)
        return;

    if (sscanf(line, concatFormatString("LeftButtonLeft=").c_str(), &s->leftButtonLeft) == 1)
        return;

    if (sscanf(line, concatFormatString("LeftButtonRight=").c_str(), &s->leftButtonRight) == 1)
        return;

    if (sscanf(line, concatFormatString("RightButtonUp=").c_str(), &s->rightButtonUp) == 1)
        return;

    if (sscanf(line, concatFormatString("RightButtonDown=").c_str(), &s->rightButtonDown) == 1)
        return;

    if (sscanf(line, concatFormatString("RightButtonLeft=").c_str(), &s->rightButtonLeft) == 1)
        return;

    if (sscanf(line, concatFormatString("RightButtonRight=").c_str(), &s->rightButtonRight) == 1)
        return;

    if (sscanf(line, concatFormatString("ButtonSelect=").c_str(), &s->buttonSelect) == 1)
        return;

    if (sscanf(line, concatFormatString("ButtonL1=").c_str(), &s->buttonL1) == 1)
        return;

    if (sscanf(line, concatFormatString("ButtonL2=").c_str(), &s->buttonL2) == 1)
        return;

    if (sscanf(line, concatFormatString("ButtonR1=").c_str(), &s->buttonR1) == 1)
        return;

    if (sscanf(line, concatFormatString("ButtonR2=").c_str(), &s->buttonR2) == 1)
        return;
}

static void ApplyAll(ImGuiContext *, ImGuiSettingsHandler *) {}

static void ClearAll(
    ImGuiContext *, ImGuiSettingsHandler *handler)
{
    *static_cast<SimGuiSettings *>(handler->UserData) = {};
}

static void WriteAll(
    ImGuiContext *, ImGuiSettingsHandler *handler,
    ImGuiTextBuffer *buf)
{
    const auto *s =
        static_cast<const SimGuiSettings *>(handler->UserData);

    buf->appendf("[SimGui][Settings]\n");
    buf->appendf(concatFormatString<true>("LeftXNeg=").c_str(),
                 s->leftXNeg);
    buf->appendf("LeftXPos=%d\n", s->leftXPos);
    buf->appendf("LeftYNeg=%d\n", s->leftYNeg);
    buf->appendf("LeftYPos=%d\n", s->leftYPos);
    buf->appendf("RightXNeg=%d\n", s->rightXNeg);
    buf->appendf("RightXPos=%d\n", s->rightXPos);
    buf->appendf("RightYNeg=%d\n", s->rightYNeg);
    buf->appendf("RightYPos=%d\n", s->rightYPos);
    buf->appendf("LeftButtonUp=%d\n", s->leftButtonUp);
    buf->appendf("LeftButtonDown=%d\n", s->leftButtonDown);
    buf->appendf("LeftButtonLeft=%d\n", s->leftButtonLeft);
    buf->appendf("LeftButtonRight=%d\n", s->leftButtonRight);
    buf->appendf("RightButtonUp=%d\n", s->rightButtonUp);
    buf->appendf("RightButtonDown=%d\n", s->rightButtonDown);
    buf->appendf("RightButtonLeft=%d\n", s->rightButtonLeft);
    buf->appendf("RightButtonRight=%d\n", s->rightButtonRight);
    buf->appendf("ButtonSelect=%d\n", s->buttonSelect);
    buf->appendf("ButtonL1=%d\n", s->buttonL1);
    buf->appendf("ButtonL2=%d\n", s->buttonL2);
    buf->appendf("ButtonR1=%d\n", s->buttonR1);
    buf->appendf("ButtonR2=%d\n\n", s->buttonR2);
}

static void RegisterSettings()
{
    ImGuiSettingsHandler h;
    h.TypeName = "SimGui";
    h.TypeHash = ImHashStr("SimGui");
    h.UserData = &settings;
    h.ReadInitFn = ReadInit;
    h.ReadOpenFn = ReadOpen;
    h.ReadLineFn = ReadLine;
    h.ApplyAllFn = ApplyAll;
    h.WriteAllFn = WriteAll;
    h.ClearAllFn = ClearAll;

    ImGui::AddSettingsHandler(&h);
}

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

static void HandleKeyBindingEvent(const SDL_Event &event)
{
    if (waitingForKey < 0)
        return;

    if (event.type != SDL_EVENT_KEY_DOWN)
        return;

    if (event.key.repeat)
        return;

    if (event.key.scancode == SDL_SCANCODE_ESCAPE)
    {
        waitingForKey = -1;
        return;
    }

    *keyBindings[waitingForKey].key = event.key.scancode;
    ImGui::MarkIniSettingsDirty();
    waitingForKey = -1;
}

static bool IsKeyDown(
    const bool *keyboard,
    int keyCount,
    SDL_Scancode key)
{
    const int index = static_cast<int>(key);

    return key != SDL_SCANCODE_UNKNOWN &&
           index >= 0 &&
           index < keyCount &&
           keyboard[index];
}

static void HandleKeyboardButton(
    bool &button,
    const bool *keyboard,
    int keyCount,
    SDL_Scancode key)
{
    button = button || IsKeyDown(keyboard, keyCount, key);
}

static void HandleKeyboardAxis(
    float &axis,
    float gamepadAxis,
    const bool *keyboard,
    int keyCount,
    SDL_Scancode negative,
    SDL_Scancode positive,
    float deltaTime,
    float response = 18.0f)
{
    const bool neg = IsKeyDown(keyboard, keyCount, negative);
    const bool pos = IsKeyDown(keyboard, keyCount, positive);

    float target = gamepadAxis;

    if (neg != pos)
        target = neg ? -1.0f : 1.0f;

    const float blend = 1.0f - std::exp(-response * deltaTime);

    axis += (target - axis) * blend;

    axis = std::clamp(axis, -1.0f, 1.0f);
}

static void ApplyKeyboardInput(
    ControllerState &state,
    const ControllerState &gamepadState,
    float deltaTime)
{
    if (waitingForKey >= 0)
        return;

    int keyCount = 0;
    const bool *keyboard = SDL_GetKeyboardState(&keyCount);

    // Left stick
    HandleKeyboardAxis(
        state.left.x,
        gamepadState.left.x,
        keyboard, keyCount,
        settings.leftXNeg,
        settings.leftXPos,
        deltaTime);

    HandleKeyboardAxis(
        state.left.y,
        gamepadState.left.y,
        keyboard, keyCount,
        settings.leftYNeg,
        settings.leftYPos,
        deltaTime);

    // Right stick
    HandleKeyboardAxis(
        state.right.x,
        gamepadState.right.x,
        keyboard, keyCount,
        settings.rightXNeg,
        settings.rightXPos,
        deltaTime);

    HandleKeyboardAxis(
        state.right.y,
        gamepadState.right.y,
        keyboard, keyCount,
        settings.rightYNeg,
        settings.rightYPos,
        deltaTime);

    // Left buttons
    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_DPAD_UP],
        keyboard, keyCount, settings.leftButtonUp);

    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_DPAD_DOWN],
        keyboard, keyCount, settings.leftButtonDown);

    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_DPAD_LEFT],
        keyboard, keyCount, settings.leftButtonLeft);

    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_DPAD_RIGHT],
        keyboard, keyCount, settings.leftButtonRight);

    // Right buttons
    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_NORTH],
        keyboard, keyCount, settings.rightButtonUp);

    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_SOUTH],
        keyboard, keyCount, settings.rightButtonDown);

    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_WEST],
        keyboard, keyCount, settings.rightButtonLeft);

    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_EAST],
        keyboard, keyCount, settings.rightButtonRight);

    // Select
    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_GUIDE],
        keyboard, keyCount, settings.buttonSelect);

    // Top shoulders
    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_LEFT_SHOULDER],
        keyboard, keyCount, settings.buttonL1);

    HandleKeyboardButton(
        state.buttons[SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER],
        keyboard, keyCount, settings.buttonR1);

    // Bottom triggers

    state.leftTrigger =
        IsKeyDown(keyboard, keyCount, settings.buttonL2)
            ? 1.0f
            : gamepadState.leftTrigger;

    state.rightTrigger =
        IsKeyDown(keyboard, keyCount, settings.buttonR2)
            ? 1.0f
            : gamepadState.rightTrigger;
}

static void DrawKeyBindings()
{
    if (ImGui::BeginTable(
            "KeyBindingsTable", 2,
            ImGuiTableFlags_BordersInnerV |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableSetupColumn("Action",
                                ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Key",
                                ImGuiTableColumnFlags_WidthFixed, 160.0f);
        ImGui::TableHeadersRow();

        for (int i = 0;
             i < static_cast<int>(
                     sizeof(keyBindings) / sizeof(keyBindings[0]));
             ++i)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted(keyBindings[i].name);

            ImGui::TableSetColumnIndex(1);

            const bool waiting = waitingForKey == i;

            char label[128];

            if (waiting)
            {
                std::snprintf(label, sizeof(label),
                              "...##key%d", i);
            }
            else
            {
                const char *keyName =
                    SDL_GetScancodeName(*keyBindings[i].key);

                if (!keyName || keyName[0] == '\0')
                    keyName = "???";

                std::snprintf(label, sizeof(label),
                              "%s##key%d", keyName, i);
            }

            ImGui::SetNextItemWidth(-1.0f);

            if (waiting)
                ImGui::PushStyleColor(
                    ImGuiCol_Button,
                    ImVec4(0.55f, 0.30f, 0.08f, 1.0f));

            if (ImGui::Button(label, ImVec2(-1.0f, 0.0f)))
                waitingForKey = waiting ? -1 : i;

            if (waiting)
                ImGui::PopStyleColor();
        }

        ImGui::EndTable();
    }
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

void DrawCompetitionState(CompetitionState &competitionState)
{
    if (ImGui::BeginCombo("Competition State", competitionStateToString(competitionState.mode).c_str()))
    {
        for (int i = 0; i < static_cast<int>(CompetitionMode::Count); ++i)
        {
            const CompetitionMode mode = static_cast<CompetitionMode>(i);
            const bool selected = (mode == competitionState.mode);

            if (ImGui::Selectable(competitionStateToString(mode).c_str(), selected))
            {
                competitionState.mode = mode;
            }

            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    ImGui::Checkbox("Field Control Connected", &competitionState.connected);
}

#ifdef AS_LIBRARY
CompetitionState getCompetitionState()
{
    CompetitionMode mode;

    uint32_t status = vexCompetitionStatus();
    if (status & V5_COMP_BIT_EBL)
    {
        mode = CompetitionMode::Disabled;
    }
    else if (status & V5_COMP_BIT_MODE)
    {
        mode = CompetitionMode::Autonomous;
    }
    else
    {
        mode = CompetitionMode::Teleop;
    }

    return CompetitionState{mode, (status & V5_COMP_BIT_COMP) != 0};
}

void setCompetitionState(CompetitionState state)
{
    uint32_t status = 0;
    if (state.mode == CompetitionMode::Disabled)
    {
        status |= V5_COMP_BIT_EBL;
    }
    else if (state.mode == CompetitionMode::Autonomous)
    {
        status |= V5_COMP_BIT_MODE;
    }

    if (state.connected)
    {
        status |= V5_COMP_BIT_COMP;
    }

    vexSimCompetitionStatusSet(status);
}
#endif

void frame(GamepadPtr &gamepad, ControllerState &controllerState, CompetitionState &competitionState)
{
    ImGui::SetNextWindowSize(ImVec2(800, 520), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(std::format("Controller - {0}###Controller", gamepad ? SDL_GetGamepadName(gamepad.get()) : "Not Connected").c_str(), nullptr))
    {
        DrawController(controllerState);
    }
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(400, 820), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Key Bindings", nullptr))
    {
        DrawKeyBindings();
    }
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Competition State", nullptr))
    {
        DrawCompetitionState(competitionState);
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
    RegisterSettings();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigDpiScaleFonts = true;                        // Enable automatic DPI scaling of fonts based on monitor DPI
    io.ConfigDpiScaleViewports = true;                    // Enable automatic DPI scaling of viewports based on monitor DPI
    io.IniFilename = "simgui.ini";
    ImGui::LoadIniSettingsFromDisk(io.IniFilename);

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

    CompetitionState competitionState;

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

            HandleKeyBindingEvent(event);
        }

        ControllerState gamepadState;
        if (gamepad)
        {
            ReadController(gamepad.get(), gamepadState);
        }

        state.buttons = gamepadState.buttons;

        ApplyKeyboardInput(state, gamepadState, io.DeltaTime);

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

        competitionState = getCompetitionState();
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

        frame(gamepad, state, competitionState);

#ifdef AS_LIBRARY
        setCompetitionState(competitionState);
#endif

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
