#include <SDL.h>
#include <iostream> 
 
int main(int argc, char* argv[]) { 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl; 
        return 1; 
    } 
 
    SDL_Window* window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN); 
    if (!window) { 
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl; 
        SDL_Quit(); 
        return 1; 
    } 
 
    // Wait for 2 seconds 
    SDL_Delay(2000); 
 
    SDL_DestroyWindow(window); 
    SDL_Quit(); 
    return 0; 
} 