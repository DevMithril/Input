#include "types.h"

void set_key_delay(Key *key, int delay, bool is_cancelable) {
    if (is_cancelable) {
        delay *= -1;
    }
    key->default_delay = delay;
}
