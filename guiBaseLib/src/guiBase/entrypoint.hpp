#pragma once
#include "guiBase/App.hpp"

/// for marking variables as unused
#define UNUSED(expr) (void)(expr)

namespace guiBase {
    extern App* CreateApp(int argc, char** argv);

    extern bool gRunning;

    int appMain(int argc, char** argv);
}// namespace guiBase
