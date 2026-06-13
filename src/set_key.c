#include "types.h"
#include "is_valid_key.h"

bool set_key(Key *key, SDL_Scancode scancode, SDL_MouseButtonFlags button) {
    if (is_valid_key(scancode)) {
        key->key = scancode;
    } else if (button > 0 && button < CLICK_COUNT){
        key->key = button + SDL_SCANCODE_COUNT;
    } else {
        return false;
    }
    return true;
}
