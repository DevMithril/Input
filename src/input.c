#include "input.h"

bool key_update(bool *keys_array, Key *key) {
    bool key_state = keys_array[key->key];
    if (key->delay > 0) {
        key->delay--;
        return false;
    }
    if (key->delay < 0) {
        key->delay = (key_state) ? (key->delay + 1) : 0;
        return false;
    }
    if (key_state) {
        key->delay = key->default_delay;
    }
    return key_state;
}

bool key_is_valid(SDL_Scancode key) {
    return ((key > 3 && key < 57) || 
            (key > 78 && key < 83) || 
            (key > 83 && key < 101) || 
            (key > 223 && key < 232));
}

void input_update(Input *input) {
    SDL_Event event;
    input->mouse_wheel = 0;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT :
            input->quit = true;
            break;
        case SDL_EVENT_KEY_DOWN :
            if (input->to_change && key_is_valid(event.key.scancode)) {
                input->to_change->key = event.key.scancode;
                input->to_change = NULL;
            }
            input->key[event.key.scancode] = true;
            break;
        case SDL_EVENT_KEY_UP :
            input->key[event.key.scancode] = false;
            break;
        case SDL_EVENT_MOUSE_MOTION :
            input->mouse_pos.x = event.motion.x;
            input->mouse_pos.y = event.motion.y;
            break;
        case SDL_EVENT_MOUSE_WHEEL :
            input->mouse_wheel = event.wheel.y;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN :
            if (event.button.button == SDL_BUTTON_LEFT)
                input->left_click = true;
            if (event.button.button == SDL_BUTTON_RIGHT)
                input->right_click = true;
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP :
            if (event.button.button == SDL_BUTTON_LEFT)
                input->left_click = false;
            if (event.button.button == SDL_BUTTON_RIGHT)
                input->right_click = false;
            break;
        }
    }
    input->down = key_update(input->key, &input->key_down);
    input->left = key_update(input->key, &input->key_left);
    input->right = key_update(input->key, &input->key_right);
    input->up = key_update(input->key, &input->key_up);
    input->jump = key_update(input->key, &input->key_jump);
}

void input_save(Input *input, const char filename[]) {
    FILE *file = NULL;
    Input clean_input;
    
    memset(&clean_input, 0, sizeof (Input));
    clean_input.key_down.key = input->key_down.key;
    clean_input.key_jump.key = input->key_jump.key;
    clean_input.key_left.key = input->key_left.key;
    clean_input.key_right.key = input->key_right.key;
    clean_input.key_up.key = input->key_up.key;
    clean_input.key_down.default_delay = input->key_down.default_delay;
    clean_input.key_jump.default_delay = input->key_jump.default_delay;
    clean_input.key_left.default_delay = input->key_left.default_delay;
    clean_input.key_right.default_delay = input->key_right.default_delay;
    clean_input.key_up.default_delay = input->key_up.default_delay;

    file = fopen(filename, "wb");
    if (!file) {
        return;
    }
    fwrite(&clean_input, sizeof (Input), 1, file);
    fclose(file);
}

void input_load(Input *input, const char filename[]) {
    FILE *file = NULL;
    file = fopen(filename, "rb");
    if (!file) {
        input->quit = true;
        return;
    }
    fread(input, sizeof (Input), 1, file);
    fclose(file);
}

void input_key_change(Input *input, Key *key) {
    input->to_change = key;
}
