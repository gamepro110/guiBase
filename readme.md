# guiBase

[StudioCherno/Walnut][Walnut] inspired cross platform GUI application library.

using [GLFW][glfw] for cross platform window creation. while using [Dear ImGui][Imgui] for simple but effective grafical visualization using the vulkan backend.

## Todo

- [ ] add tests

### backlog

- [ ] switch submodules to CMake CPM modules
  - [ ] imgui
  - [ ] glfw
- [ ] make wayland default
  - find stable version of [glfw] that gives less problems wayland protocols

### done

- [x] add `#include "misc/cpp/imgui_stdlib.cpp"` to [layer.hpp](<./guiBaseLib/src/guiBase/Layer.hpp>)
- [x] add `#include <format>` to [Logger.hpp](<./guiBaseLib/src/guiBase/Logger.hpp>)

## untested

- macos

[Walnut]: https://github.com/StudioCherno/Walnut
[glfw]: https://github.com/glfw/glfw
[Imgui]: https://github.com/ocornut/imgui
