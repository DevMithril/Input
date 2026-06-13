#include "types.h"

bool save_input(Input *input, const char filename[]) {
    FILE *file = NULL;
    Input clean_input;
    
    memset(&clean_input, 0, sizeof (Input));
    for (int i = 0; i < KEY_COUNT; i++) {
        clean_input.keys[i].key = input->keys[i].key;
        clean_input.keys[i].default_delay = input->keys[i].default_delay;
    }

    file = fopen(filename, "wb");
    if (file) {
        fwrite(&clean_input, sizeof (Input), 1, file);
        fclose(file);
    }
    return file;
}
