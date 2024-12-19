Contains the core engine modules, organized into subdirectories based on functionality

Temporary Structure
Engine/
│── Core/                # Core systems (game loop, logging, utility functions)
│── Graphics/            # OpenGL rendering system (shaders, textures, meshes)
│── Input/               # SDL2 input handling (keyboard, mouse, controllers)
│── Physics/             # Physics engine (optional: integrate Box2D)
│── Audio/               # Audio system (e.g., SDL_mixer or OpenAL integration)
│── ECS/                 # Entity-Component-System implementation
│── Resources/           # Resource management (textures, shaders, models)
│── Window/              # SDL2 window and OpenGL context creation
│── Math/                # Math utilities (vectors, matrices, transformations)
│── Build/               # Precompiled headers and platform-specific code

Detailed Structure
Engine/
│── Core/
│    ├── GameLoop.h      # Main game loop logic
│    ├── Logger.h        # Logging utility
│    ├── Timer.h         # Delta time calculations
│    ├── Application.h   # Core engine application class
│── Graphics/
│    ├── Renderer.h      # OpenGL renderer
│    ├── Shader.h        # Shader management
│    ├── Texture.h       # Texture loading and binding
│    ├── Camera.h        # Camera system
│    ├── Mesh.h          # Mesh handling
│── Input/
│    ├── InputManager.h  # Input handling class
│    ├── KeyCodes.h      # SDL2 key definitions
│── ECS/
│    ├── Entity.h        # Entity definition
│    ├── Component.h     # Component base class
│    ├── System.h        # System base class
│    ├── ECSManager.h    # Entity-Component-System manager
│── Resources/
│    ├── ResourceManager.h  # Texture and shader caching
│    ├── ShaderLoader.h     # Helper to compile and link shaders
│    ├── TextureLoader.h    # Helper to load textures
│── Window/
│    ├── Window.h        # SDL2 window creation
│    ├── OpenGLContext.h # OpenGL context management
│── Math/
│    ├── Vector.h        # Vector operations
│    ├── Matrix.h        # Matrix operations
│── Build/
│    ├── Platform.h      # Platform-specific code (if needed)