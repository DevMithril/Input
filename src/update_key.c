#include "types.h"

bool update_key(Input *input, Key *key) {
    bool key_state;

    if (key->key < SDL_SCANCODE_COUNT) {
        key_state = input->key_states[key->key];
    } else {
        key_state = input->clicks[(key->key - SDL_SCANCODE_COUNT) - 1];
    }

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
