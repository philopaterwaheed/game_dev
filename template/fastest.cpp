
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CUBE_SIZE = 20;
const int NUM_CUBES = 10;

class Cube {
public:
    Cube(int x, int y) {
        m_x = x;
        m_y = y;
    }

    int getX() { return m_x; }
    int getY() { return m_y; }

private:
    int m_x;
    int m_y;
};

class Player {
public:
    Player(int x, int y) {
        m_x = x;
        m_y = y;
    }

    int getX() { return m_x; }
    int getY() { return m_y; }

    void move(vector<Cube>& cubes) {
        // Find the nearest cube
        int minDistance = SCREEN_WIDTH + SCREEN_HEIGHT;
        int nearestCube = -1;
        for (int i = 0; i < cubes.size(); ++i) {
            int distance = abs(m_x - cubes[i].getX()) + abs(m_y - cubes[i].getY());
            if (distance < minDistance) {
                minDistance = distance;
                nearestCube = i;
            }
        }

        // Move towards the nearest cube
        if (nearestCube != -1) {
            int cubeX = cubes[nearestCube].getX();
            int cubeY = cubes[nearestCube].getY();

            if (m_x < cubeX) {
                m_x++;
            } else if (m_x > cubeX) {
                m_x--;
            }

            if (m_y < cubeY) {
                m_y++;
            } else if (m_y > cubeY) {
                m_y--;
            }
        }
    }

private:
    int m_x;
    int m_y;
};

int main(int argc, char** argv) {
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Cube Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize SDL2_ttf
    TTF_Init();

    // Load a font
    TTF_Font* font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", 24);
    if (font == NULL) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
        return 1;
    }

    // Generate random cubes
    srand(time(NULL));
    vector<Cube> cubes;
    for (int i = 0; i < NUM_CUBES; ++i) {
        int x = rand() % (SCREEN_WIDTH - CUBE_SIZE);
        int y = rand() % (SCREEN_HEIGHT - CUBE_SIZE);
        cubes.push_back(Cube(x, y));
    }

    // Create a player
    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    // Game loop
    bool quit = false;
    int score = 0;
    int startTime = SDL_GetTicks();
    int fastestTime = -1;
    while (!quit) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Move the player
        player.move(cubes);

        // Check for collisions
        for (int i = 0; i < cubes.size(); ++i) {
            int cubeX = cubes[i].getX();
            int cubeY = cubes[i].getY();

            int playerX = player.getX();
            int playerY = player.getY();

            if (playerX + CUBE_SIZE > cubeX && playerX < cubeX + CUBE_SIZE && playerY + CUBE_SIZE > cubeY && playerY < cubeY + CUBE_SIZE) {
                // Destroy the cube
                cubes.erase(cubes.begin() + i);

                // Increment the player's score
                score++;

                // Check if all cubes have been destroyed
                if (cubes.empty()) {
                    // Calculate the time taken to finish the game
                    int endTime = SDL_GetTicks();
                    int timeTaken = endTime - startTime;

                    // Update the fastest time if it's the first run or if this run is faster
                    if (fastestTime == -1 || timeTaken < fastestTime) {
                        fastestTime= timeTaken;
                    }

                    // Reset the game
                    cubes.clear();
                    for (int i = 0; i < NUM_CUBES; ++i) {
                        int x = rand() % (SCREEN_WIDTH - CUBE_SIZE);
                        int y = rand() % (SCREEN_HEIGHT - CUBE_SIZE);
                        cubes.push_back(Cube(x, y));
                    }
                    player = Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
                    score = 0;
                    startTime = SDL_GetTicks();
                }
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the cubes
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < cubes.size(); ++i) {
            SDL_Rect cubeRect = {cubes[i].getX(), cubes[i].getY(), CUBE_SIZE, CUBE_SIZE};
            SDL_RenderFillRect(renderer, &cubeRect);
        }

        // Draw the player
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect playerRect = {player.getX(), player.getY(), CUBE_SIZE, CUBE_SIZE};
        SDL_RenderFillRect(renderer, &playerRect);

        // Draw the score and fastest time
        SDL_Color textColor = {255, 255, 255};
        string scoreStr = "Score: " + to_string(score);
        string fastestTimeStr = "Fastest Time: " + (fastestTime == -1 ? "N/A" : to_string(fastestTime / 1000) + "." + to_string(fastestTime % 1000));
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
        SDL_Surface* fastestTimeSurface = TTF_RenderText_Solid(font, fastestTimeStr.c_str(), textColor);
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_Texture* fastestTimeTexture = SDL_CreateTextureFromSurface(renderer, fastestTimeSurface);
        SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
        SDL_Rect fastestTimeRect = {10, 10 + scoreSurface->h + 10, fastestTimeSurface->w, fastestTimeSurface->h};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_RenderCopy(renderer, fastestTimeTexture, NULL, &fastestTimeRect);
        SDL_FreeSurface(scoreSurface);
        SDL_FreeSurface(fastestTimeSurface);
        SDL_DestroyTexture(scoreTexture);
        SDL_DestroyTexture(fastestTimeTexture);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
