#ifndef _TYPES_H
#define _TYPES_H
#include <SDL3/SDL.h>
#include <stdio.h>

#define KEY_COUNT 5
#define CLICK_COUNT 5

typedef struct Key {
    unsigned int key;
    /*
    delay corresponds au nb de frame de désactivation de la touche
    (i.e. : input défini à false quel que soit son état physique)
    n > 0 : n frame de delai minimal entre deux inputs réussi
    n < 0 : n frame de delai entre deux inputs réussi,
            avec remise à zéro si la touche est relachée par l'utilisateur
    */
    int delay;
    int default_delay;
} Key;

typedef struct Input {
    Key keys[KEY_COUNT];
    Key *to_change;
    SDL_Point mouse_pos;
    int mouse_wheel;
    bool clicks[CLICK_COUNT];
    bool key_states[SDL_SCANCODE_COUNT];
    bool quit;
    bool states[KEY_COUNT];
} Input;

#endif
