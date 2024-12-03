#include <stdio.h>
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <math.h> //required for Windows

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

#define SPEED (300)

int main(int argc, char *argv[]) //SDL2 expects "int argc, char *argv[]" for Windows
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;

    // Initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Interactive Mouse Event",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!window)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (!renderer)
    {
        printf("Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Load image into memory
    surface = IMG_Load("img/redghost_right.png");
    if (!surface)
    {
        printf("Could not create surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load image data into the graphics hardware's memory
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        printf("Could not create texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // hold the position and size of the sprite
    SDL_Rect img_rect;

    // get the dimensions of texture
    SDL_QueryTexture(texture, NULL, NULL, &img_rect.w, &img_rect.h);
    float x_pos = (WINDOW_WIDTH - img_rect.w) / 2;
    float y_pos = (WINDOW_HEIGHT - img_rect.h) / 2;

    // sprite initial velocity values
    float x_vel = 0;
    float y_vel = 0;

    // control variables
    int close_requested = 0;

    while (close_requested == 0)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                close_requested = 1;
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_q)
                    close_requested = 1;
            }
        }

        // get cursor position relative to window
        int mouse_x, mouse_y;
        int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

        // determine velocity toward mouse
        int target_x = mouse_x - img_rect.w / 2;
        int target_y = mouse_y - img_rect.h / 2;
        float delta_x = target_x - x_pos;
        float delta_y = target_y - y_pos;
        float distance = sqrt((delta_x * delta_x) + (delta_y * delta_y));

        // avoid jittering
        if (distance < 5)
            x_vel = y_vel = 0;
        else
        {
            x_vel = delta_x * SPEED / distance;
            y_vel = delta_y * SPEED / distance;
        }

        // reverse velocity and update image if mouse button 1 is pressed
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            x_vel = -x_vel;
            y_vel = -y_vel;
            surface = IMG_Load("img/ghost_vulnerable.png");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
        else
        { 
            if (x_pos >= mouse_x)
            {
                surface = IMG_Load("img/redghost_left.png");
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
            }
            else if (x_pos < mouse_x)
            {
                surface = IMG_Load("img/redghost_right.png");
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
            } 
        }
        
        // calculate new position
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // detect collision with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - img_rect.w)
            x_pos = WINDOW_WIDTH - img_rect.w;
        if (y_pos >= WINDOW_HEIGHT - img_rect.h)
            y_pos = WINDOW_HEIGHT - img_rect.h;
        
        // update position
        img_rect.x = (int) x_pos;
        img_rect.y = (int) y_pos;
        
        // clear the window
        SDL_RenderClear(renderer);

        // draw image
        SDL_RenderCopy(renderer, texture, NULL, &img_rect);
        SDL_RenderPresent(renderer);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }

    // clean up resources before exiting
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
