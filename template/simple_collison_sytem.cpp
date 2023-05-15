#include <SDL2/SDL.h>
// #include <cstdlib>
// #include <ctime>

// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;
// const int NUM_WALLS = 10;
// const int WALL_SIZE = 50;

// // Generate a random integer between min and max, inclusive
// int random_int(int min, int max) {
//     return rand() % (max - min + 1) + min;
// }

// int main(int argc, char* args[]) {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window* window = SDL_CreateWindow("Move Cube with Arrow Keys",
//                                           SDL_WINDOWPOS_UNDEFINED,
//                                           SDL_WINDOWPOS_UNDEFINED,
//                                           SCREEN_WIDTH,
//                                           SCREEN_HEIGHT,
//                                           SDL_WINDOW_SHOWN);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     SDL_Rect cube = { SCREEN_WIDTH/2 - 25, SCREEN_HEIGHT/2 - 25, 50, 50 };
//     SDL_Rect walls[NUM_WALLS];

//     srand(time(NULL));
//     for (int i = 0; i < NUM_WALLS; i++) {
//         walls[i].x = random_int(0, SCREEN_WIDTH - WALL_SIZE);
//         walls[i].y = random_int(0, SCREEN_HEIGHT - WALL_SIZE);
//         walls[i].w = WALL_SIZE;
//         walls[i].h = WALL_SIZE;
//     }

//     bool quit = false;
//     while (!quit) {
//         SDL_Event e;
//         while (SDL_PollEvent(&e) != 0) {
//             if (e.type == SDL_QUIT) {
//                 quit = true;
//             }
//             else if (e.type == SDL_KEYDOWN) {
//                 switch (e.key.keysym.sym) {
//                     case SDLK_UP:
//                         cube.y -= 10;
//                         break;
//                     case SDLK_DOWN:
//                         cube.y += 10;
//                         break;
//                     case SDLK_LEFT:
//                         cube.x -= 10;
//                         break;
//                     case SDLK_RIGHT:
//                         cube.x += 10;
//                         break;
//                     default:
//                         break;
//                 }
//             }
//         }

//         // Check for collisions with walls
//         for (int i = 0; i < NUM_WALLS; i++) {
//             if (SDL_HasIntersection(&cube, &walls[i])) {
//                 // Move cube back to previous position
//                 cube.x -= 10 * (e.key.keysym.sym == SDLK_RIGHT) - 10 * (e.key.keysym.sym == SDLK_LEFT);
//                 cube.y -= 10 * (e.key.keysym.sym == SDLK_DOWN) - 10 * (e.key.keysym.sym == SDLK_UP);

//                 // Adjust position to prevent overlap
//                 if (cube.x < walls[i].x) {
//                     cube.x = walls[i].x - cube.w;
//                 }
//                 else if (cube.x > walls[i].x) {
//                     cube.x = walls[i].x + walls[i].w;
//                 }
//                 if (cube.y < walls[i].y) {
//                     cube.y = walls[i].y - cube.h;
//                 }
//                 else if (cube.y > walls[i].y) {
//                     cube.y = walls[i].y + walls[i].h;
//                 }
//             }
//         }

//         // Clear screen
//         SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//         SDL_RenderClear(renderer);

//         // Draw walls
//         SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
//         for (int i = 0; i < NUM_WALLS; i++) {
//             SDL_RenderFillRect(renderer, &walls[i]);
//         }

//         // Draw cube
//         SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
//         SDL_RenderFillRect(renderer, &cube);

//         // Update screen
//         SDL_RenderPresent(renderer);
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
//     return 0;
// }

#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int NUM_WALLS = 10;
const int WALL_SIZE = 50;

// Generate a random integer between min and max, inclusive
int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Move Cube with Arrow Keys",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect cube = { SCREEN_WIDTH/2 - 25, SCREEN_HEIGHT/2 - 25, 50, 50 };
    SDL_Rect walls[NUM_WALLS];

    srand(time(NULL));
    for (int i = 0; i < NUM_WALLS; i++) {
        walls[i].x = random_int(0, SCREEN_WIDTH - WALL_SIZE);
        walls[i].y = random_int(0, SCREEN_HEIGHT - WALL_SIZE);
        walls[i].w = WALL_SIZE;
        walls[i].h = WALL_SIZE;
    }

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        cube.y -= 10;
                        break;
                    case SDLK_DOWN:
                        cube.y += 10;
                        break;
                    case SDLK_LEFT:
                        cube.x -= 10;
                        break;
                    case SDLK_RIGHT:
                        cube.x += 10;
                        break;
                    default:
                        break;
                }
            }
        }

        // Check for collisions with walls
        for (int i = 0; i < NUM_WALLS; i++) {
            if (SDL_HasIntersection(&cube, &walls[i])) {
                int overlapX = std::min(cube.x + cube.w, walls[i].x + walls[i].w) - std::max(cube.x, walls[i].x);
                int overlapY = std::min(cube.y + cube.h, walls[i].y + walls[i].h) - std::max(cube.y, walls[i].y);

                // Move cube back to previous position
                cube.x -= 10 * (e.key.keysym.sym == SDLK_RIGHT) - 10 * (e.key.keysym.sym == SDLK_LEFT);
                cube.y -= 10 * (e.key.keysym.sym == SDLK_DOWN) - 10 * (e.key.keysym.sym == SDLK_UP);

                // Adjust position to prevent overlap
                if (overlapX < overlapY) {
                    if (cube.x < walls[i].x) {
                        cube.x = walls[i].x - cube.w;
                    }
                    else {
                        cube.x = walls[i].x + walls[i].w;
                    }
                }
                else {
                    if (cube.y < walls[i].y) {
                        cube.y = walls[i].y - cube.h;
                    }
                    else {
                        cube.y = walls[i].y + walls[i].h;
                    }
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Draw walls
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < NUM_WALLS; i++) {
            SDL_RenderFillRect(renderer, &walls[i]);
        }

        // Draw cube
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &cube);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
