#ifndef _IS_VALID_KEY
#define _IS_VALID_KEY
#include "types.h"

/**
 * Indique si `key` est un input valide ou non
 * \param key code de la touche voulue
 * \return `true` si `key` est valide, `false` sinon
 */
bool is_valid_key(SDL_Scancode key);

#endif
