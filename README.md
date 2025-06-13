# InteractiveGL

InteractiveGL is a C++ application that demonstrates OpenGL rendering with a wxWidgets-based GUI. It supports loading assets and shaders, and provides interactive control over 3D transformations such as scaling and rotation.

---

## Dependencies

This project depends on the following libraries and tools:

- **C++20** compatible compiler (e.g., GCC, Clang, MSVC)
- **CMake** version 3.28 or newer
- **wxWidgets** — included locally in `thirdparty/wxWidgets`
- **GLAD** — OpenGL function loader, included in `thirdparty/glad`
- **GLM** — Header-only math library for OpenGL (fetched automatically by CMake, version 0.9.9.8)

> On Windows, required wxWidgets `.dll` files are automatically copied to the build output directory after build.  


---

This project makes use of the following open-source libraries:
wxWidgets — Licensed under the wxWindows Library Licence.
GLAD — Licensed under the MIT License.
GLM — Licensed under the MIT License.


