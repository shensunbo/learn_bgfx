#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#include <chrono>
#include <unistd.h>

#include "log/mylog.h"
#include "bgfx/bgfx.h"
#include <bgfx/platform.h>
#include <bx/uint32_t.h>

#include "logo.h"

#define WNDW_WIDTH 1600
#define WNDW_HEIGHT 900

static bool s_showStats = false;

static void glfw_errorCallback(int error, const char *description)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void glfw_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
		s_showStats = !s_showStats;
}

int main(void)
{
    glfwSetErrorCallback(glfw_errorCallback);

    if (!glfwInit()) {
        mylog(LogLevel::E, "glfwInit failed");
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // 创建 GLFW 窗口
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "BGFX Example", NULL, NULL);
    if (!window) {
        // 创建窗口失败
        glfwTerminate();
        mylog(LogLevel::E, "glfwCreateWindow failed");
        return -1;
    }

    glfwSetKeyCallback(window, glfw_keyCallback);

    // // 设置当前为 GLFW 窗口上下文
    // glfwMakeContextCurrent(window);

    // // 初始化 GLAD
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     // GLAD 初始化失败
    //     glfwDestroyWindow(window);
    //     glfwTerminate();
    //     mylog(LogLevel::E, "gladLoadGLLoader failed");
    //     return -1;
    // }

    bgfx::renderFrame();

    // 初始化 BGFX
    bgfx::Init init;
    init.type     = bgfx::RendererType::Count;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.platformData.nwh  = (void*)glfwGetX11Window(window);
    init.platformData.ndt  = glfwGetX11Display();
    init.resolution.width  = 1920;
    init.resolution.height = 1080;
    init.resolution.reset  = BGFX_RESET_VSYNC;
    bgfx::init(init);

    bgfx::setViewClear(0
    , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
    , 0x303030ff
    , 1.0f
    , 0
    );

    unsigned int counter = 0;
    mylog(LogLevel::I, "hello world");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        			// Set view 0 default viewport.
        bgfx::setViewRect(0, 0, 0, uint16_t(600), uint16_t(400) );

        // This dummy draw call is here to make sure that view 0 is cleared
        // if no other draw calls are submitted to view 0.
        bgfx::touch(0);

        // Use debug font to print information about this example.
        bgfx::dbgTextClear();

        const bgfx::Stats* stats = bgfx::getStats();

        bgfx::dbgTextImage(
                bx::max<uint16_t>(uint16_t(stats->textWidth/2), 20)-20
            , bx::max<uint16_t>(uint16_t(stats->textHeight/2),  6)-6
            , 40
            , 12
            , s_logo
            , 160
            );

        bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

        bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
        bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

        bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
            , stats->width
            , stats->height
            , stats->textWidth
            , stats->textHeight
            );

        bgfx::frame();
        counter++;
    }

    // 清理 BGFX 和 GLFW
    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
