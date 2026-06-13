#include "../input.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct App {
    Input input;
    SDL_FRect position;
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool binding_keys;
    int key_to_bind;
} App;

void app_quit(App *app, int status) {
    if (app->renderer)
        SDL_DestroyRenderer(app->renderer);
    if (app->window)
        SDL_DestroyWindow(app->window);
    SDL_Quit();
    exit(status);
}

void app_init(App *app, const char window_name[], int res_x, int res_y, bool fullscreen) {
    if (!SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)) {
        printf("SDL_Init() : %s\n", SDL_GetError());
        app_quit(app, EXIT_FAILURE);
    }
    if (fullscreen) {
        app->window = SDL_CreateWindow(window_name, res_x, res_y, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    } else {
        app->window = SDL_CreateWindow(window_name, res_x, res_y, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    }
    if (!app->window) {
        printf("SDL_CreateWindow() : %s\n", SDL_GetError());
        app_quit(app, EXIT_FAILURE);
    }
    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (!app->renderer) {
        printf("SDL_CreateRenderer() : %s\n", SDL_GetError());
        app_quit(app, EXIT_FAILURE);
    }
    SDL_SetRenderLogicalPresentation(app->renderer, res_x, res_y, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

void render_demo(App *app) {
    SDL_Point m = app->input.mouse_pos;
    SDL_RenderRect(app->renderer, &app->position);

    SDL_RenderLine(app->renderer, m.x-5, m.y, m.x+5, m.y);
    SDL_RenderLine(app->renderer, m.x, m.y-5, m.x, m.y+5);

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
}

void bind_keys(App *app) {
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);

    switch (app->key_to_bind) {
    case 0 :
        if (is_binding_key(&app->input)) {
            SDL_RenderDebugTextFormat(app->renderer, 100, 100, "PRESS UP");
        } else {
            app->key_to_bind++;
            change_input_key(&app->input, &app->input.down_key);
        }
        break;
    case 1 :
        if (is_binding_key(&app->input)) {
            SDL_RenderDebugTextFormat(app->renderer, 100, 100, "PRESS DOWN");
        } else {
            app->key_to_bind++;
            change_input_key(&app->input, &app->input.right_key);
        }
        break;
    case 2 :
        if (is_binding_key(&app->input)) {
            SDL_RenderDebugTextFormat(app->renderer, 100, 100, "PRESS RIGHT");
        } else {
            app->key_to_bind++;
            change_input_key(&app->input, &app->input.left_key);
        }
        break;
    case 3 :
        if (is_binding_key(&app->input)) {
            SDL_RenderDebugTextFormat(app->renderer, 100, 100, "PRESS LEFT");
        } else {
            app->binding_keys = false;
        }
        break;
    }
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
}

int main(void) {
    App app;

    app_init(&app, "Demo Input", 800, 800, false);

    app.position = (SDL_FRect){395,395,10,10};
    app.binding_keys = true;
    app.key_to_bind = 0;
    memset(&app.input, 0, sizeof(Input));
    change_input_key(&app.input, &app.input.up_key);

    set_key_delay(&app.input.up_key, 0, false);
    set_key_delay(&app.input.down_key, 5, false);
    set_key_delay(&app.input.right_key, 30, false);
    set_key_delay(&app.input.left_key, 30, true);

    while (!app.input.quit) {
        update_input(&app.input);
        SDL_RenderClear(app.renderer);
        if (!app.binding_keys) {
            if (app.input.up) {
                app.position.y -= 10;
            }
            if (app.input.down) {
                app.position.y += 10;
            }
            if (app.input.right) {
                app.position.x += 10;
            }
            if (app.input.left) {
                app.position.x -= 10;
            }
            SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 255);
            if (app.input.right_click) {
                SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
            }
            if (app.input.left_click) {
                SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, 255);
            }

            render_demo(&app);
        } else {
            bind_keys(&app);
        }
        SDL_RenderPresent(app.renderer);

        SDL_Delay((int)(1000 / 60));
    }

    app_quit(&app, EXIT_SUCCESS);
}
