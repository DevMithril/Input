#ifndef _UPDATE_KEY
#define _UPDATE_KEY
#include "types.h"

/**
 * Met à jour le delai de `key`
 * \param input structure Input contenant `key`
 * \param key Key à mettre à jour
 * \return Nouvel état de l'input correspondant à `key`
 */
bool update_key(Input *input, Key *key);

#endif
