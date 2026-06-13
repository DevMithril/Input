#include "types.h"

bool load_input(Input *input, const char filename[]) {
    FILE *file = NULL;
    file = fopen(filename, "rb");
    if (file) {
        fread(input, sizeof (Input), 1, file);
        fclose(file);
    }
    return file;
}
