#include "vex/v5.h"
#include <memory>
#include "../../simgui/include/api.h"

#include <string>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#else
#include <dlfcn.h>
#endif

class RuntimeLibrary
{
public:
    RuntimeLibrary() = default;

    ~RuntimeLibrary()
    {
        unload();
    }

    RuntimeLibrary(const RuntimeLibrary &) = delete;
    RuntimeLibrary &operator=(const RuntimeLibrary &) = delete;

    RuntimeLibrary(RuntimeLibrary &&other) noexcept
        : handle(other.handle)
    {
        other.handle = nullptr;
    }

    bool load(const std::string &path)
    {
        unload();

#ifdef _WIN32
        handle = LoadLibraryA(path.c_str());
#else
        handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
#endif

        return handle != nullptr;
    }

    void unload()
    {
        if (!handle)
            return;

#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif

        handle = nullptr;
    }

    template <typename T>
    T getSymbol(const char *name) const
    {
        if (!handle)
            return nullptr;

#ifdef _WIN32
        return reinterpret_cast<T>(
            GetProcAddress(handle, name));
#else
        return reinterpret_cast<T>(
            dlsym(handle, name));
#endif
    }

    explicit operator bool() const
    {
        return handle != nullptr;
    }

    RuntimeLibrary &operator=(RuntimeLibrary &&other) noexcept
    {
        if (this != &other)
        {
            unload();
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

private:
#ifdef _WIN32
    HMODULE handle = nullptr;
#else
    void *handle = nullptr;
#endif
};

static SimFunctionTable *functionTable = nullptr;
static std::vector<RuntimeLibrary> simExtensions;

void loadSimExtensions()
{
    if (functionTable == nullptr)
    {
        functionTable = new SimFunctionTable();
        functionTable->vexSimControllerSet = vexSimControllerSet;
        functionTable->vexSimControllerConnectionStatusSet = vexSimControllerConnectionStatusSet;
        functionTable->vexSimCompetitionStatusSet = vexSimCompetitionStatusSet;
        functionTable->vexCompetitionStatus = vexCompetitionStatus;
        functionTable->vexDevicesGet = vexDevicesGet;
    }

    auto &plugin = simExtensions.emplace_back();

    if (plugin.load("libsimgui.dll"))
    {
        using LoadFunctionTable = int (*)(SimFunctionTable *);

        auto loadFunctionTableFn = plugin.getSymbol<LoadFunctionTable>("loadFunctionTable");

        if (loadFunctionTableFn)
            loadFunctionTableFn(functionTable);
    }
}