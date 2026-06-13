#ifndef INPUT_LIB_H
#define INPUT_LIB_H
#include <SDL3/SDL.h>

/*
================================================================================
    Input
================================================================================
*/

typedef struct Key {
    unsigned int key;
    int _delay;
    int _default_delay;
} Key;

typedef struct Input {
    Key up_key, down_key, left_key, right_key, jump_key;
    Key *_to_change;
    SDL_Point mouse_pos;
    int mouse_wheel;
    bool right_click, middle_click, left_click, x1_click, x2_click;
    bool _key_states[SDL_SCANCODE_COUNT];
    bool quit;
    bool up, down, left, right, jump;
} Input;

/**
 * Met à jour une structure Input avec les nouveaux inputs reçus
 * \param input Input à mettre à jour
 */
void update_input(Input *input);

/**
 * Charge une structure Input depuis un fichier binaire
 * \param input Input à charger
 * \param filename chemin du fichier contenant la sauvegarde de la structure
 * \return `true` en cas de succès, `false` sinon
 */
bool load_input(Input *input, const char filename[]);

/**
 * Sauvegarde une structure Input dans un fichier binaire
 * \param input Input à sauvegarder
 * \param filename chemin du fichier recevant la sauvegarde de la structure
 * \return `true` en cas de succès, `false` sinon
 */
bool save_input(Input *input, const char filename[]);

/**
 * Permet de changer une Key
 * L'input lié à `key` sera remplacé par le prochain input reçu
 * \param input structure Input où le changement doit avoir lieu
 * \param key adresse mémoire de la Key devant être modifiée
 */
void change_input_key(Input *input, Key *key);

/**
 * Définit le temps de désactivation de `key` après un input réussi
 * \param key adresse mémoire de la Key devant être modifiée
 * \param delay nombre de frames de désactivation de l'input
 * \param is_cancelable indique que le delai est annulé si l'input est relaché
 * \note `delay` est présumé positif ou nul
 */
void set_key_delay(Key *key, int delay, bool is_cancelable);

/**
 * Définit l'input pour une Key
 * \param key structure Key dont on souhaite définir l'input
 * \param scancode scancode de la touche du clavier utilisée comme input
 * \param button clic de souris utilisé comme input
 * \return `true` en cas de succès, `false` sinon
 * \note `scancode` ou `button` est présumé égal à 0, l'autre étant l'input
 */
bool set_key(Key *key, SDL_Scancode scancode, SDL_MouseButtonFlags button);

/**
 * Indique que l'on modifie actuellement l'input d'une Key
 * \param input structure concernée
 * \return `true` si une Key est en cours de modification, `false` sinon
 */
bool is_binding_key(Input *input);

#endif
