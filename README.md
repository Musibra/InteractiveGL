# InteractiveGL

InteractiveGL is a C++ application that demonstrates OpenGL rendering with a wxWidgets-based GUI. It provides interactive control over 3D transformations such as scaling and rotation.

---

## Dependencies

This project depends on the following libraries and tools:

- **C++20** compatible compiler (e.g., MSVC)
- **CMake** version 3.28 or newer
- **wxWidgets** — included locally in `thirdparty/wxWidgets`
- **GLAD** — OpenGL function loader, included in `thirdparty/glad`
- **GLM** — Header-only math library for OpenGL (fetched automatically by CMake, version 0.9.9.8)

> On Windows, required wxWidgets `.dll` files are automatically copied to the build output directory after build.  


---

# Third-Party Licenses

This project uses the following open-source libraries:

- **[wxWidgets](https://www.wxwidgets.org/)**  
  Licensed under the [wxWindows Library Licence](https://www.wxwidgets.org/about/licence/).

- **[GLAD](https://github.com/Dav1dde/glad)**  
  Licensed under the [MIT License](https://opensource.org/licenses/MIT).

- **[GLM](https://github.com/g-truc/glm)**  
  Licensed under the [MIT License](https://opensource.org/licenses/MIT).

-**Icons** used in this project are provided by [Icons8](https://icons8.com)

