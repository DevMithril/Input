#include "types.h"
#include "set_key.h"
#include "update_key.h"

void update_input(Input *input) {
    SDL_Event event;
    input->mouse_wheel = 0;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT :
            input->quit = true;
            break;
        case SDL_EVENT_KEY_DOWN :
            if (input->to_change) {
                if (set_key(input->to_change, event.key.scancode, 0)) {
                    input->to_change = NULL;
                }
            }
            input->key_states[event.key.scancode] = true;
            break;
        case SDL_EVENT_KEY_UP :
            input->key_states[event.key.scancode] = false;
            break;
        case SDL_EVENT_MOUSE_MOTION :
            input->mouse_pos.x = event.motion.x;
            input->mouse_pos.y = event.motion.y;
            break;
        case SDL_EVENT_MOUSE_WHEEL :
            input->mouse_wheel = event.wheel.y;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN :
            if (input->to_change) {
                if (set_key(input->to_change, 0, event.button.button)) {
                    input->to_change = NULL;
                }
            }
            input->clicks[event.button.button - 1] = true;
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP :
            input->clicks[event.button.button - 1] = false;
            break;
        }
    }
    for (int i = 0; i < KEY_COUNT; i++) {
        input->states[i] = update_key(input, &input->keys[i]);
    }
}
