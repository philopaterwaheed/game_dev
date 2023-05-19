#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int CUBE_SIZE = 50;
const int CUBE_SPEED = 10;

const int NUM_CUBES = 10;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // Create an array of rectangles for the cubes
    SDL_Rect cubeRects[NUM_CUBES];

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the cube rectangles with random positions
    for (int i = 0; i < NUM_CUBES; i++) {
        cubeRects[i].x = rand() % (SCREEN_WIDTH - CUBE_SIZE);
        cubeRects[i].y = rand() % (SCREEN_HEIGHT - CUBE_SIZE);
        cubeRects[i].w = CUBE_SIZE;
        cubeRects[i].h = CUBE_SIZE;
    }

    // Create a rectangle for the player cube
    SDL_Rect playerRect = {SCREEN_WIDTH / 2 - CUBE_SIZE / 2, SCREEN_HEIGHT / 2 - CUBE_SIZE / 2, CUBE_SIZE, CUBE_SIZE};

SDL_Rect cameraRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

bool running = true;

while (running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        playerRect.y -= CUBE_SPEED;
                        break;
                    case SDLK_DOWN:
                        playerRect.y += CUBE_SPEED;
                        break;
                    case SDLK_LEFT:
                        playerRect.x -= CUBE_SPEED;
                        break;
                    case SDLK_RIGHT:
                        playerRect.x += CUBE_SPEED;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    // Center the camera on the player cube
    cameraRect.x = playerRect.x + CUBE_SIZE / 2 - SCREEN_WIDTH / 2;
    cameraRect.y = playerRect.y + CUBE_SIZE / 2 - SCREEN_HEIGHT / 2;

    // Clamp the camera position to the screen boundaries
    if (cameraRect.x < 0) {
        cameraRect.x = 0;
    } else if (cameraRect.x > SCREEN_WIDTH -CUBE_SIZE) {
        cameraRect.x = SCREEN_WIDTH - CUBE_SIZE;
    }
    if (cameraRect.y < 0) {
        cameraRect.y = 0;
    } else if (cameraRect.y > SCREEN_HEIGHT - CUBE_SIZE) {
        cameraRect.y = SCREEN_HEIGHT - CUBE_SIZE;
    }

    // Fill the screen with a blue color
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255));

    // Draw the player cube on the screen relative to the camera
    SDL_Rect playerRectRelative = {playerRect.x - cameraRect.x, playerRect.y - cameraRect.y, CUBE_SIZE, CUBE_SIZE};
    SDL_FillRect(screenSurface, &playerRectRelative, SDL_MapRGB(screenSurface->format, 255, 0, 0));

    // Draw the other cubes on the screen relative to the camera
    for (int i = 0; i < NUM_CUBES; i++) {
        SDL_Rect cubeRectRelative = {cubeRects[i].x - cameraRect.x, cubeRects[i].y - cameraRect.y, CUBE_SIZE, CUBE_SIZE};
        SDL_FillRect(screenSurface, &cubeRectRelative, SDL_MapRGB(screenSurface->format, 0, 255, 0));
    }

    // Update the window surface
    SDL_UpdateWindowSurface(window);

   // Delay to control the frame rate
    SDL_Delay(10);
}

SDL_DestroyWindow(window);

SDL_Quit();

return 0;
}
