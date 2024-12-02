#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

/**
 * code is compatible with SDL need full signature for main
 */
int main(int argc, char** argv) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Failed to initialize the SDL2 library\n";
    return -1;
  }
  
  if(IMG_Init(IMG_INIT_PNG) < 0)
  {
    std::cout << "Failed to initialize the SDL2 Image library\n";
    return -1;
  }
  
  if(TTF_Init() < 0)
  {
    std::cout << "Failed to initialize the SDL2 TTF library\n";
    return -1;
  }
  
  SDL_Window* window{SDL_CreateWindow(
    "Hello Window", 0, 0, 800, 300, 0)};
  
  if(!window)
  {
    std::cout << "Failed to create window\n";
    return -1;
  }

  SDL_Surface *window_surface = SDL_GetWindowSurface(window);

  if(!window_surface)
  {
    std::cout << "Failed to get the surface from the window\n";
    return -1;
  }
  
  SDL_Surface *image = SDL_LoadBMP("image.bmp");
  if(!image)
  {
    std::cout << "Failed to load image\n";
    std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    return -1;
  }
  SDL_UpdateWindowSurface(window);
  
  
  //Window will close as SDL_PollEvent() returns 0 if no events are in the queue. 
  // processed the window close event.
  bool keep_window_open = true;
  while(keep_window_open)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event) > 0)
    {
      switch(event.type)
      {
          case SDL_QUIT:
             keep_window_open = false;
             break;
      }
      SDL_BlitSurface(image, NULL, window_surface, NULL);
      SDL_UpdateWindowSurface(window);
    }
  }
  return 0;
}