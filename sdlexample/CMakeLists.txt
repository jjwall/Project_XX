cmake_minimum_required(VERSION 3.5)
project(SDLExample)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE sdlexample_srcs src/*)
add_executable(sdlexample ${sdlexample_srcs})
set_target_properties(sdlexample PROPERTIES CXX_VERSION 17)
target_link_libraries(sdlexample ${SDL2_LIBRARIES} SDL2_image)
target_include_directories(sdlexample PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_definitions(sdlexample PUBLIC SDL_MAIN_HANDLED)

add_custom_command(TARGET sdlexample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:sdlexample>/assets)
