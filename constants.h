namespace Constants {
    namespace OpenGL {
        inline constexpr int attribs[] = {
            WX_GL_RGBA,
            WX_GL_DOUBLEBUFFER,
            WX_GL_DEPTH_SIZE, 24,
            WX_GL_SAMPLE_BUFFERS, 1,
            WX_GL_SAMPLES, 4,
            0
        };
    }
    namespace OverlayButton {
        constexpr int BUTTON_WIDTH = 24;
        constexpr int BUTTON_HEIGHT = 24;
        constexpr int BUTTON_OFFSET_X = 10;
        constexpr int BUTTON_OFFSET_Y = 10;
    }
}
