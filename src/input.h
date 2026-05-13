#ifndef INPUT_LIB_H
#define INPUT_LIB_H
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 32767

typedef struct Key {
    SDL_Scancode key;
    int delay;
    /* 
    nb de frame de désactivation de la touche (input à false quel que soit l'état physique)
    n > 0 : n frame de delai minimal entre deux inputs réussi
    -n < 0 : n frame de delai entre deux inputs réussi, avec remise à zéro si la touche est relachée par l'utilisateur
    */
    int default_delay;
} Key;

typedef struct Input {
    bool key[SDL_SCANCODE_COUNT];
    Key key_up, key_down, key_left, key_right, key_jump;
    SDL_Point mouse_pos;
    Key *to_change;
    int mouse_wheel;
    bool quit;
    bool up, down, left, right, jump, right_click, left_click;
} Input;

/* met à jour la structure input */
void input_update(Input *input);

/* charge une structure Input depuis un fichier binaire */
void input_load(Input *input, const char filename[]);

/* sauvegarde une structure Input dans un fichier binaire */
void input_save(Input *input, const char filename[]);

/* permet d'indiquer la key qui doit être remplacée par le prochain input */
void input_key_change(Input *input, Key *key);

#endif
