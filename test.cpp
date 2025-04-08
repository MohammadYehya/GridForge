#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>

// Function to initialize SDL and OpenGL
bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    return true;
}

// Function to initialize GLAD
bool initializeGLAD(SDL_Window* window) {
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "GLAD loading OpenGL failed!" << std::endl;
        return false;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    return true;
}

// Function to initialize the isometric grid
void drawIsometricGrid(int rows, int cols, float gridSize) {
    std::vector<float> vertices;

    // Calculate grid vertices in isometric projection
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = (col - row) * gridSize;
            float y = (col + row) * gridSize / 2;
            
            // Push vertices for the grid lines (we draw them as lines)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0.0f); // z-coordinate, we don't need depth for a simple 2D grid

            // Right line
            if (col + 1 < cols) {
                float x2 = ((col + 1) - row) * gridSize;
                float y2 = ((col + 1) + row) * gridSize / 2;
                vertices.push_back(x2);
                vertices.push_back(y2);
                vertices.push_back(0.0f);
            }

            // Down line
            if (row + 1 < rows) {
                float x2 = (col - (row + 1)) * gridSize;
                float y2 = (col + (row + 1)) * gridSize / 2;
                vertices.push_back(x2);
                vertices.push_back(y2);
                vertices.push_back(0.0f);
            }
        }
    }

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Draw the grid
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertices.size() / 3); // Drawing lines
    glBindVertexArray(0);
}

// Function to draw the player
void drawPlayer(float playerX, float playerY, float gridSize) {
    float size = gridSize * 0.5f;  // Player size (adjustable)
    float x1 = playerX - size;
    float y1 = playerY - size;
    float x2 = playerX + size;
    float y2 = playerY + size;

    std::vector<float> playerVertices = {
        x1, y1, 0.0f,  // Bottom-left corner
        x2, y1, 0.0f,  // Bottom-right corner
        x2, y2, 0.0f,  // Top-right corner
        x1, y2, 0.0f,  // Top-left corner
        x1, y1, 0.0f,  // Closing the square (back to bottom-left)
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * playerVertices.size(), playerVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Draw the player (as a square)
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, playerVertices.size() / 3);
    glBindVertexArray(0);
}

int main(int argc, char* argv[]) {
    if (!initializeSDL()) {
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Isometric Grid with Movable Player", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        800, 600, 
        SDL_WINDOW_OPENGL
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    if (!initializeGLAD(window)) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // OpenGL configuration
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set background color

    // Player position (initially in the center of the grid)
    float playerX = 0.0f;
    float playerY = 0.0f;
    float gridSize = 50.0f; // Grid cell size

    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Handle player movement using keyboard input (WASD)
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W]) {
            playerY -= gridSize * 0.5f;
        }
        if (state[SDL_SCANCODE_S]) {
            playerY += gridSize * 0.5f;
        }
        if (state[SDL_SCANCODE_A]) {
            playerX -= gridSize * 0.5f;
        }
        if (state[SDL_SCANCODE_D]) {
            playerX += gridSize * 0.5f;
        }

        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

        // Draw the isometric grid
        drawIsometricGrid(10, 10, gridSize); // 10x10 grid

        // Draw the player
        drawPlayer(playerX, playerY, gridSize); // Draw player at current position

        SDL_GL_SwapWindow(window); // Swap buffer
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
