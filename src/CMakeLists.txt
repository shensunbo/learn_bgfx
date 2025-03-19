add_definitions(-DBX_CONFIG_DEBUG)

add_executable(bgfx_test main.cpp)

target_sources(bgfx_test PRIVATE
    app/showDebugLogo.cpp
)

target_include_directories(bgfx_test PRIVATE 
    ${COMMON_INC_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(bgfx_test PRIVATE ${COMMON_DEP_SRC_FILES})

target_link_directories(bgfx_test PRIVATE ${COMMON_LIB_DIR})
target_link_libraries(bgfx_test PRIVATE
    -lassimp
    -limgui
    -lglfw
    -lGL
    -lbgfx
    -lbx
    -lbimg
)

