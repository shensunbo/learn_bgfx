#include "showDebugLogo.h"
#include "res/logo.h"
#include "log/mylog.h"
#include "bgfx/bgfx.h"
#include <bgfx/platform.h>
#include <bx/uint32_t.h>

void showDebugLogo(GLFWwindow* window, unsigned int width, unsigned int height){

    bgfx::setViewClear(0
    , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
    , 0xffffffff
    , 1.0f
    , 0
    );

    unsigned int counter = 0;
    mylog(LogLevel::I, "hello world");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        			// Set view 0 default viewport.
        bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height) );

        // This dummy draw call is here to make sure that view 0 is cleared
        // if no other draw calls are submitted to view 0.
        bgfx::touch(0);

        // Use debug font to print information about this example.
        bgfx::dbgTextClear();

        const bgfx::Stats* stats = bgfx::getStats();

        bgfx::dbgTextPrintf(0, 0, 0xf1, "Hello, BGFX! Frame: %d", counter); // 在 (0,0) 位置显示文本
        bgfx::dbgTextPrintf(0, 3, 0xf1, "This is another line of text."); // 在下一行显示文本

        bgfx::dbgTextImage(
                bx::max<uint16_t>(uint16_t(stats->textWidth/2), 20)-20
            , bx::max<uint16_t>(uint16_t(stats->textHeight/2),  6)-6
            , 40
            , 12
            , s_logo
            , 160
            );

        bgfx::dbgTextPrintf(0, 1, 0xf2, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

        bgfx::dbgTextPrintf(80, 1, 0xf2, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
        bgfx::dbgTextPrintf(80, 2, 0xf2, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

        bgfx::dbgTextPrintf(0, 2, 0xf3, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
            , stats->width
            , stats->height
            , stats->textWidth
            , stats->textHeight
            );

        bgfx::setDebug(BGFX_DEBUG_TEXT);

        // bgfx::dbgTextPrintf(0, 2, 0x0f, "Frame Time: %.2f ms", 1000.0f * stats->cpuTimeFrame / stats->gpuFrameNum);

        bgfx::frame();

        counter++;
    }
}