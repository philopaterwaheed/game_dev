#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CUBE_SIZE = 50;
const int NUM_WALLS = 10;

class Cube {
public:
    Cube(int x, int y) : x(x), y(y) {}
    int x, y;
};

class Camera {
public:
    Camera(int x, int y) : x(x), y(y) {}
    int x, y;
};

bool checkCollision(int x1, int y1, int x2, int y2, int size) {
    if (x2 >= x1 && x2 < x1 + size && y2 >= y1 && y2 < y1 + size) {
        return true;
    }
    return false;
}

bool checkWallCollision(int x, int y, const std::vector<Cube>& walls) {
    for (const auto& wall : walls) {
        if (checkCollision(wall.x, wall.y, x, y, CUBE_SIZE)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Cube Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Seed random number generator
    std::srand(std::time(nullptr));

    // Generate walls
    std::vector<Cube> walls;
    for (int i = 0; i < NUM_WALLS; i++) {
        int x = std::rand() % (SCREEN_WIDTH - CUBE_SIZE);
        int y = std::rand() % (SCREEN_HEIGHT - CUBE_SIZE);
        walls.push_back(Cube(x, y));
    }

    // Set up player cube
    Cube player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    // Set up camera
    Camera camera(player.x - SCREEN_WIDTH / 2, player.y - SCREEN_HEIGHT / 2);

    // Main game loop
    bool quit = false;
    while (!quit) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Move player based on keyboard input
        const Uint8* keystates = SDL_GetKeyboardState(nullptr);
        if (keystates[SDL_SCANCODE_UP] && !checkWallCollision(player.x, player.y - 1, walls)) {
            player.y--;
        }
        if (keystates[SDL_SCANCODE_DOWN] && !checkWallCollision(player.x, player.y + 1, walls)) {
            player.y++;
        }
        if (keystates[SDL_SCANCODE_LEFT] && !checkWallCollision(player.x - 1, player.y, walls)) {
            player.x--;
        }
        if (keystates[SDL_SCANCODE_RIGHT] && !checkWallCollision(player.x + 1, player.y, walls)) {
            player.x++;
        }

        // Update camera position
        camera.x = player.x - SCREEN_WIDTH / 2;
        camera.y = player.y - SCREEN_HEIGHT / 2;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render walls
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        for (const auto& wall : walls) {
            SDL_Rect wallRect = { wall.x - camera.x, wall.y - camera.y, CUBE_SIZE, CUBE_SIZE };
            SDL_RenderFillRect(renderer, &wallRect);
        }

        // Render player
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_Rect playerRect = { player.x - camera.x, player.y - camera.y, CUBE_SIZE, CUBE_SIZE };
        SDL_RenderFillRect(renderer, &playerRect);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
