# Quilt
A Kirby's Epic Yarn modding tool for various aspects of the game.



## Dependencies
Before compiling Quilt, you will first need to download or compile the following libraries or files:

- [GLFW 3.3.10](https://github.com/glfw/glfw/releases/tag/3.3.10)
- [Glad](https://glad.dav1d.de/)
- [ImGui docking branch](https://github.com/ocornut/imgui/tree/docking)
- [Native File Dialog Extended](https://github.com/btzy/nativefiledialog-extended)
- [C++ JSON Parser](https://github.com/nlohmann/json)

Should you compile any source files yourself, place all objects into the `lib` folder. When prompted to move a header file into the project, create any folders that don't exist if necessary.

### GLFW
Download or compile the **GLFW** library and place `libglfw3.a` into the `lib` folder.

Move `glfw3.h` and `glfw3native.h` into `include/lib/GLFW/`.
### glad
> [!TIP]
> If you want to compile **glad** alongside Quilt instead of seperately, you can skip this.

Download and compile the **glad** source code for the target configuration. In this case, it is OpenGL 3.3 Core.

Move `glad.h` into `include/lib/glad/`.

### ImGui
> [!IMPORTANT]
> You must use the docking branch of ImGui.

> [!TIP]
> It's ideal to compile **ImGui** seperately, but you can skip this if you wish to compile it alongside Quilt.

Compile the following files:
- `imgui.cpp`
- `imgui_demo.cpp`
- `imgui_draw.cpp`
- `imgui_tables.cpp`
- `imgui_widgets.cpp`
- `backends/imgui_impl_glfw.cpp`
- `backends/imgui_impl_opengl3.cpp`

Move the following header files into `include/lib/imgui/`:
- `imconfig.h`
- `imgui.h`
- `imgui_impl_glfw.h`
- `imgui_internal.h`
- `imstb_rectpack.h`
- `imstb_textedit.h`
- `imstb_truetype.h`
- `imgui_impl_opengl3.h`
- `imgui_impl_opengl3_loader.h`

### Native File Dialog Extended
> [!TIP]
> If you want to compile **Native File Dialog Extended** alongside Quilt instead of seperately, you can skip compiling it. Be sure to compile the appropriate files for your OS.

Move `nfd.h` into `include/lib/`.

### C++ JSON Parser
> [!NOTE]
> This dependency is header-only. Move `json.hpp` to `include/lib/`.