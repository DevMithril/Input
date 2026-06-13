## Input
Une librairie de gestion des inputs avec la librairie SDL3.

Cette librairie fournit une structure `Input` permettant de :

 - consulter l'état d'un input voulu.
 - choisir les inputs à utiliser.
 - choisir le délai de 'blocage' d'un input, i.e. : le nombre de frames
 durant lesquelles l'input sera considéré faux, quelque soit son état physique.
 Ce délai peut aussi être définit comme étant 'annulable' en cas de relachement
 de l'input.
 - gérer la réception de l'input de fermeture de l'application (SDL_QUIT).

Actuellement, cette librairie ne gère que les saisies du clavier et de la souris.

Vous pouvez modifier les noms des champs de la structure dans `input.h` à votre
convenance.
Pour que plus d'inputs soient disponibles, modifiez la constante `KEY_COUNT`
dans `src/types.h` puis recompilez la librairie (n'oubliez pas d'ajouter les champs
d'input supplémentaires dans `input.h`).

#### Compilation :

(Re)Compilez `libinput.so` avec :

    $ make lib

#### Utilisation :

Copiez `input.h` et `libinput.so` dans votre projet, `#include "input.h"` dans votre code.

Puis compilez avec les flags adéquats :

    $ gcc -o your_project your_project.c -L./ -Wl,-rpath=./ -linput

#### Demo :

    $ cd demo
    $ make run
Permet de choisir 4 inputs (`up`, `down`, `right` et `left`), puis de contrôler
un petit carré avec. Les délais sont différents en fonction de l'input, et
celui de l'input `left` peut être annulé en relachant la touche. Les clics
droit et gauche change temporairement la couleur de rendu. Une croix est
affichée à l'emplacement du curseur.
