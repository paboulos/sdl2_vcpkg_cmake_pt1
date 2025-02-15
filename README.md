# Introduction

This repo is a CMake vcpkg starter project for anyone following the [studyplan.dev/sdl](https://www.studyplan.dev/sdl) course.
It has presets for a Ninja and Visual Studio CMake project that uses the SDL2 C++ libraries.

## Open-source Prequisites for All Features in this Repo

 1. git
 2. cmake
 3. clang
 4. ninja
 5. MS Visual Studio Community C++

## Usage Advice

 1. If you make modifications to the CMakeList files it may break the existing build.
    - In this situation remove everything from the build directory and rerun the CMake project generation.
 2. CMake and VCPKG will cache dependencies and settings after it loads the libraries. So subsequent builds will be faster.
 3. CMake is complex, but there are a large list of variables that can make project changes less complicated.

  [CMake Variables List](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html)

## Install the Package Manager

  [Read Beginners Guide](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd)
  
  1. clone vcpkg git repo and cd into it
  2. set VCPKG_ROOT path in Env
  3. ```vcpkg integrate install```

- There are many possible environments we can build C++ applications for.
  - For example, these can include PCs running Windows, phones running iOS, smartwatches, etc.
  - A triplet is a simple string that specifies what the target environment is.
  - For example, x64-windows specifies that our target is 64-bit Windows devices.
- When we download a package through vcpkg, we need to specify which target we want.
- We can do that every time we install a package, but it’s usually easier to specify a default.
- We do that by creating a VCPKG_DEFAULT_TRIPLET as an environment variable.
- set local env var
   ```$env:VCPKG_DEFAULT_TRIPLET = 'x64-windows'```

- We can see what vcpkg packages we have downloaded by running .\vcpkg.exe list from the vcpkg directory.
  - For example, if our Visual Studio build configuration is targeting x64,
  - we should ensure that the list includes the x64-windows version of our package
  - If it’s missing, we can specify the desired triplet as an additional argument to the vcpkg install command:
   ```.\vcpkg install spdlog --triplet x64-windows```
- Verify with command:
  ```vcpkg list```
- A package folder can includes 3 things we are interested in:

   1. Header files (.h) within an include directory
   2. Object Library files (.lib) within the lib directory
   3. Dynamic Library files (.dll) within the lib directory

## SDL2 Packages Required for CMake

- Do not use SDL3 since this demo is using SDL2
- Path Variables
  - There is another mechanism we can use to help our system find the files our programs depend on.
    - The OS maintains a list of locations it will automatically search for objects such as .dll files. It is called the path variable, and it is available under System Properties
    - Rather than moving the .dll files next to the executable, we could move them into one of the directories in that variable, such as windows/system32.
    - Alternatively, we could add a new directory to the path variable, and store our DLLs there.  
      - SDL is a cross-platform library that allows us to create windows, access input devices, and create graphics.
      - SDL_image is an extension that allows us to work with images in all the common formats, such as jpeg and png
      - SDL_ttf is an extension that we can use to render text at run-time

- For a CMake build system the SDL libraries will be stored in a subdirectory of our project.
- we need to ensure our system can find the SDL libraries our program is using.
- Dynamic libraries must be on the System Path or in the same directory.
- For this example the three DLL files we need are:

  1. SDL2.dll
  2. SDL2_image.dll
  3. SDL2_ttf.dll
- How the package libraries were setup

    ```vcpkg new --application```

    ```vcpkg search sdl2```
  
  - To update vcpkg.json with package names
    ```vcpkg add port <package>```
  
### Packager Notes

- You'll notice in the generation stage that target linking libraries inside the CMake config files use names that are namespaced,
  - i.e. package::target  

You can see this in the terminal when vcpkg is installing the packages such as

```sdl2-image provides CMake targets:find_package(SDL2_image CONFIG REQUIRED) target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)```

### CMAKE

- [Read More](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html)
  - There are CMake generators that can produce ninja, make, and IDE build files
  - Ninja is meant to replace Make, which is slow when performing incremental (or no-op) builds.
  - This can considerably slow down developers working on large projects.
  - create a directory named build inside the project root
  - CMakePresets.json and CMakeUserPresets.json live in the project's root directory.
    - They both have exactly the same format, and both are optional (though at least one must be present if --preset is specified).
    - When Cmake runs locally ${sourceDir} evaluates to the path to the project source directory containing a CMakeLists.txt

### CMakePresets

- Open the CMakePresets.json file and update the environment variables where you installed Ninja, Clang, and Visual Studio
  "environment": {
        "VCPKG_ROOT": "",
        "CLANG_BIN": "",
        "MSVC_BIN": ""
      }
  - CMake projects should set: -DCMAKE_TOOLCHAIN_FILE to the location of vcpkg/scripts/buildsystems/vcpkg.cmake
  - All MSBuild C++ projects can now #include any installed libraries. Linking will be handled automatically.
    - Installing new libraries will make them instantly available.

### CMake Notes

SDLmain is an example of a static library.

- Static libraries get included in our executable file.so there is no external library dependency on it.
- Create the build directory
  - Refer to the CMakePresets.json for the configured preset names. We will use "ninja" or "msvc"
  
    ```cmake --preset ninja -S . -B ./build```
  
    ```cmake --preset msvc -S . -B ./build```

## Build and Installing the Application

- From the project root run the command
    ```cmake --build ./build --target install --config Debug```
- Inside the install directory is a CMake preset build for the application and its dependencies.
