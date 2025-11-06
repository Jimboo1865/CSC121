cmake_minimum_required(VERSION 3.16)
project(GameofLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML (version 3.x)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
# Bundle SFML frameworks into the app bundle (for portable release)
if(APPLE)
    set(SFML_DEPLOY_SCRIPT "/opt/homebrew/Cellar/sfml/3.0.2/bin/macdeploysfml")
    if(EXISTS ${SFML_DEPLOY_SCRIPT})
        add_custom_command(TARGET GameofLife POST_BUILD
            COMMAND ${SFML_DEPLOY_SCRIPT} $<TARGET_FILE:GameofLife>
            COMMENT "🧩 Bundling SFML frameworks into GameofLife.app"
        )
    endif()
endif()
add_executable(GameofLife
    GameofLife.cpp
)

# Link SFML
target_link_libraries(GameofLife PRIVATE SFML::Graphics SFML::Window SFML::System)

# --- macOS .app bundle setup ---
if(APPLE)
    set_target_properties(GameofLife PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourname.GameofLife"
        MACOSX_BUNDLE_BUNDLE_NAME "Game of Life"
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
    )

    # Optional: copy assets into .app
    file(GLOB ASSETS "assets/*")
    foreach(ASSET ${ASSETS})
        add_custom_command(TARGET GameofLife POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${ASSET}
                $<TARGET_FILE_DIR:GameofLife>/../Resources
        )
    endforeach()

    # --- Skip macdeploysfml ---
    message(STATUS "SFML 3 detected — skipping macdeploysfml (not needed)")
endif()
