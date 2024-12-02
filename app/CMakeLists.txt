set(EXE_SOURCES
    "sdl2_main.cc")
add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
   SDL2::SDL2 
   SDL2::SDL2main
   SDL2_image::SDL2_image
   SDL2_ttf::SDL2_ttf)
if (WIN32)
  target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf)
endif()
install(TARGETS ${EXECUTABLE_NAME} CONFIGURATIONS Debug DESTINATION Debug/)
install(FILES ${CMAKE_SOURCE_DIR}/app/image.bmp CONFIGURATIONS Debug DESTINATION Debug)
install(DIRECTORY "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/debug/bin/" 
        CONFIGURATIONS Debug DESTINATION Debug
         FILES_MATCHING PATTERN "*.dll")
message(CMAKE_BINARY_DIR= "${CMAKE_BINARY_DIR}")
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_17)