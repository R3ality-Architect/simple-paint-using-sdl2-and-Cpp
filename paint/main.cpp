#include <iostream>
#include <SDL.h>

// --- Defines ---
#define WIDTH 900
#define HEIGHT 600
#define TARGET_FPS 60
#define COLOR_RECT_SIZE 40  // Made slightly bigger for easier clicking

// --- Global Variables ---
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
bool done = false;
bool draw = false;
int x_mouse = 0;
int y_mouse = 0;
int radius = 10;            // Brush size
uint32_t current_color = 0xFFFF0000; // Start with Red

// Color palette (AARRGGBB)
uint32_t color_palette[] = {
    0xFF000000, // Black
    0xFFFFFFFF, // White (Eraser)
    0xFFFF0000, // Red
    0xFF00FF00, // Green
    0xFF0000FF, // Blue
    0xFFFFFF00, // Yellow
    0xFF00FFFF, // Cyan
    0xFFFF00FF  // Magenta
};
int color_palette_size = 8;

// --- Function Prototypes ---
void draw_circle(SDL_Surface* surface, int x_center, int y_center, int radius, uint32_t color);
void draw_palette(SDL_Surface* surface, uint32_t colors[], int size);
void check_color_palette_chosen(int x, int y);

// --- Function Definitions ---

/**
 * @brief Draws a circle on an SDL surface using the CPU.
 */
void draw_circle(SDL_Surface* surface, int x_center, int y_center, int radius, uint32_t color) {
    // Lock surface if needed (crucial for some systems)
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

    SDL_Rect pixel = { 0, 0, 1, 1 };
    int r_squared = radius * radius;

    for (int x = x_center - radius; x <= x_center + radius; x++) {
        for (int y = y_center - radius; y <= y_center + radius; y++) {
            // Bounds checking to prevent crashing if drawing outside window
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) continue;

            int dx = x - x_center;
            int dy = y - y_center;

            if ((dx * dx + dy * dy) <= r_squared) {
                // Determine memory address of pixel (Fast direct access)
                // Note: SDL_FillRect is safe but slow. For a simple paint app, it's acceptable.
                pixel.x = x;
                pixel.y = y;
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }

    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
}

/**
 * @brief Draws the color palette rectangles.
 */
void draw_palette(SDL_Surface* surface, uint32_t colors[], int size) {
    for (int i = 0; i < size; i++) {
        SDL_Rect color_rect = { i * COLOR_RECT_SIZE, 0, COLOR_RECT_SIZE, COLOR_RECT_SIZE };
        SDL_FillRect(surface, &color_rect, colors[i]);
    }
}

/**
 * @brief Checks if mouse clicked the palette.
 */
void check_color_palette_chosen(int x, int y) {
    if (y >= 0 && y < COLOR_RECT_SIZE) {
        int chosen_index = x / COLOR_RECT_SIZE;
        if (chosen_index >= 0 && chosen_index < color_palette_size) {
            current_color = color_palette[chosen_index];
        }
    }
}

// --- Main Function ---
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

    window = SDL_CreateWindow("Ultra Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (window == NULL) {
        std::cerr << "Window error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        std::cerr << "Surface error: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // --- INITIAL CANVAS SETUP ---
    // Fill the background white once at the start
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
    SDL_UpdateWindowSurface(window);

    SDL_Event event;

    while (!done) {
        uint32_t start_tick = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_MOUSEMOTION:
                x_mouse = event.motion.x;
                y_mouse = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Only start drawing if we are NOT clicking the palette
                if (event.button.y > COLOR_RECT_SIZE) {
                    draw = true;
                }
                else {
                    // We clicked the palette area
                    check_color_palette_chosen(event.button.x, event.button.y);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                draw = false;
                break;
            }
        }

        // Drawing Logic
        if (draw) {
            draw_circle(surface, x_mouse, y_mouse, radius, current_color);
        }

        // Draw Palette (Always on top)
        draw_palette(surface, color_palette, color_palette_size);

        // Update Screen
        SDL_UpdateWindowSurface(window);

        // Frame Rate Control
        uint32_t frame_ticks = SDL_GetTicks() - start_tick;
        if (frame_ticks < 1000 / TARGET_FPS) {
            SDL_Delay((1000 / TARGET_FPS) - frame_ticks);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}