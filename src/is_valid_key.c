#include "types.h"

bool is_valid_key(SDL_Scancode key) {
    return ((key > 3 && key < 57) || 
            (key > 78 && key < 83) || 
            (key > 83 && key < 101) || 
            (key > 223 && key < 232));
}
