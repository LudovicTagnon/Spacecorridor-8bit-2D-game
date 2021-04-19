/**
 * \file data.h
 * \brief Module d'initialisation
 * \author Ludovic Tagnon / Matheo Serrier
 * \version 3.0
 * \date 7 avril 2021
 */

#ifndef DATA_H
#define DATA_H

#include "constantes.h"

//============= STRUCTURES =============//



/**
 * \brief Représentation des parametres du sprite du jeu
*/
struct sprite_s{
    int x;
    int y;
    int h;
    int w;

};
/**
 * \brief Type qui correspond au sprite
*/
typedef struct sprite_s sprite_t;





/**
 * \brief Représentation du monde du jeu
*/
struct world_s{

    sprite_t vaisseau;
    sprite_t finish_line;
    sprite_t mur;
    sprite_t murs[NUMBER_OF_WALLS];
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int vy; /*! Vitesse de deplacement de la ligne d'arrivee et des meteorites*/

};
/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;





//============= FONCTIONS =============//

//============================== INITIALISATION ==============================//

/**
 * \brief La fonction initialise les parametres nécessaires à l'affichage graphique du sprite
 * \param sprite: Le sprite
 * \param x,y: la position du sprite
 * \param w,h: taille du sprite
*/
void init_sprite(sprite_t *sprite, int x, int y, int w,  int h);


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);


void init_walls(world_t * world);




//============================== MODIFICATIONS ==============================//


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world);

void update_walls(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world);

/**
 * \brief La fonction teste si le sprite est sorti du cadre de jeu, et replace le sprite si c'est le cas
 * \param sprite: Le sprite
*/
void depasse(sprite_t* sprite);

/**
 * \brief La fonction appelle la fonction de detection de collisions entre les sprites sp1 et sp2.
 * Si ils sont en collision, la vitesse du monde devient 0
 * \param world les données du monde
 * \param sp1: Le 1er sprite
 * \param sp2: Le 2eme sprite
 * \param make_disappear: la condition qui fait disparraitre le vaisseau si il est en collision
 */
void handle_sprites_collision(world_t *world, sprite_t* sp1, sprite_t* sp2, int make_disappear);

//============================== AFFICHAGE ==============================//
/**
 * \brief La fonction affiche les coordonnees et la taille du sprite
 * \param sprite: Le sprite
*/
void print_sprite(sprite_t* sprite);

//============================== CHECK ==============================//
/**
 * \brief La fonction de detection de collisions entre les sprites sp1 et sp2.
 * \param sp1: Le 1er sprite
 * \param sp2: Le 2eme sprite
 */
int sprites_collide(sprite_t* sp1, sprite_t* sp2);

#endif //DATA_H
