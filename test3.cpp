#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

// Function to initialize SDL and OpenGL
bool initializeSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set OpenGL version (we'll use OpenGL 3.3)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    return true;
}

// Function to create OpenGL context and load GLAD
bool initializeGLAD(SDL_Window* window) {
    // Create OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "GLAD loading OpenGL failed!" << std::endl;
        return false;
    }

    // Print OpenGL version to verify
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    return true;
}

// Main program
int main(int argc, char* argv[]) {
    // Initialize SDL
    if (!initializeSDL()) {
        return -1;
    }

    // Create a window with OpenGL context
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 + GLAD OpenGL Example", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        800, 600, 
        SDL_WINDOW_OPENGL
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Initialize OpenGL using GLAD
    if (!initializeGLAD(window)) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Define vertices for a simple triangle
    float vertices[] = {
        0.0f,  0.5f, 0.0f,  // Top vertex
       -0.5f, -0.5f, 0.0f,  // Bottom-left vertex
        0.5f, -0.5f, 0.0f   // Bottom-right vertex
    };

    // Create a vertex buffer and array object
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO and upload the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up vertex attributes (position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO (good practice)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main loop
    bool running = true;
    while (running) {
        // Poll SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Render the triangle
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Set clear color (dark cyan)
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

        glUseProgram(0);  // Default program (no shader program here, just rendering)

        // Draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw 3 vertices (a triangle)
        glBindVertexArray(0);

        // Swap buffers (display rendered content)
        SDL_GL_SwapWindow(window);

        // Delay to manage frame rate
        SDL_Delay(16);  // Approx 60 FPS
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
