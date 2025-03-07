#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIDTH = 800, HEIGHT = 600;

int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    int flags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE ;
    SDL_Window *window = SDL_CreateWindow( "GridForge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags );

    if ( NULL == window )
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }

    // SDL_Surface* icon = IMG_Load("./CMakeFiles/GridForge.dir/Assets/Icons/resources.rc.obj");
    // std::cout << SDL_GetError() << '\n';
    // SDL_SetWindowIcon(window, icon);
    // SDL_FreeSurface(icon);

    SDL_Event windowEvent;
    int x = 0 , y = 0;
    bool fscreen = false;

    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            { break; }
            else if (SDL_MOUSEBUTTONDOWN == windowEvent.type)
            {
                //TESTS
                //-----------------------------------------------------------------------------------------------------------------------------------
                // SDL_GetMouseState(&x, &y);
                // std::cout << SDL_GetCPUCount() << '\n' << SDL_GetSystemRAM() << '\n' << SDL_GetClipboardText() << '\n' << x << '-' << y << '\n';

                // SDL_OpenURL("https://github.com/MohammadYehya");

                // SDL_RenderDrawLine(,100,100,300,300)
            }
            else if (SDL_KEYDOWN == windowEvent.type)
            {
                if(windowEvent.key.keysym.sym == SDLK_F11)
                {
                    SDL_SetWindowFullscreen(window, flags | (!fscreen? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
                    fscreen = !fscreen;
                }
            }
        }
    }

    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}