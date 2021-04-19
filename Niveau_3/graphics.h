/**
 * \file graphics.h
 * \brief Module d'affichage des elements du jeu
 * \author Ludovic Tagnon / Matheo Serrier
 * \version 3.0
 * \date 7 avril 2021
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "data.h"


//============= STRUCTURES =============//

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* sprite;
    SDL_Texture* finish_line;
    SDL_Texture* meteorites;
};
/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct textures_s textures_t;



//============= FONCTIONS =============//

/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void init_textures(SDL_Renderer *renderer, textures_t *textures);


/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);


/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(textures_t *textures);


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/
void apply_background(SDL_Renderer *renderer, SDL_Texture *texture);


/**
 * \brief La fonction applique la texture du sprite sur le renderer
 * \param renderer le renderer
 * \param texture la texture liée au fond
* \param sprite le sprite a afficher
*/
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);


void apply_walls(SDL_Renderer *renderer, textures_t *textures, world_t *world);

/**
 * \brief La fonction copie les coordonnees intiales de la 1ere meteorite et ajuste les coordonnees des autres (chaque case du tableau) avant de les afficher
 * \param renderer le renderer
 * \param world les données du monde
 * \param textures les textures
 * \param sprite[w][h] les meteorites/sprites a afficher
 */
void handle_wall(SDL_Renderer *renderer, textures_t *textures, sprite_t* mur);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);


/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world);




#endif //GRAPHICS_H
