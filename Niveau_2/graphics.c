/**
 * \file graphics.c
 * \brief Module d'affichage des elements du jeu
 * \author Ludovic Tagnon / Matheo Serrier
 * \version 3.0
 * \date 7 avril 2021
 */

#include "sdl2-light.h"
#include "constantes.h"
#include "graphics.h"



void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->sprite = load_image( "ressources/spaceship.bmp",renderer);
    textures->finish_line = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorites = load_image( "ressources/meteorite.bmp",renderer);
}



void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}


void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->finish_line);
    clean_texture(textures->sprite);
    clean_texture(textures->meteorites);
}



void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
        apply_texture(texture, renderer, 0, 0);
    }
}



void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    if(texture != NULL){
        apply_texture(texture, renderer, sprite->x, sprite->y);
    }
}



void handle_wall(SDL_Renderer *renderer, textures_t *textures, world_t *world, sprite_t temp[world->mur.w/METEORITE_SIZE][world->mur.h/METEORITE_SIZE]){

    for(int y=0; y<7; y++){
        for(int x=0; x<3; x++){
            temp[x][y] = world->mur;
            temp[x][y].x += x*METEORITE_SIZE;
            temp[x][y].y += y*METEORITE_SIZE;
            apply_sprite(renderer, textures->meteorites, &temp[x][y]);

        }
    }
}



void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){

    //on vide le renderer
    clear_renderer(renderer);

    //application des textures du background dans le renderer
    apply_background(renderer, textures->background);

    //application de la texture du sprite dans le renderer
    apply_sprite(renderer, textures->sprite, &world->vaisseau);

    //application de la texture de la finish_line dans le renderer
    apply_sprite(renderer, textures->finish_line, &world->finish_line);

    sprite_t temp[world->mur.w/METEORITE_SIZE][world->mur.h/METEORITE_SIZE];
    handle_wall(renderer, textures, world, temp);

    // on met à jour l'écran
    update_screen(renderer);
}



void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {

        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'fleche droite', le vaisseau va vers la droite
            if(event->key.keysym.sym == SDLK_RIGHT){
                world->vaisseau.x += MOVING_STEP;
            }
                //si la touche appuyée est 'fleche haut', la vitesse du vaisseau augment
            else if(event->key.keysym.sym == SDLK_UP){
                world->vy++;
            }
                //si la touche appuyée est 'fleche gauche', le vaisseau va vers la droite
            else if(event->key.keysym.sym == SDLK_LEFT){
                world->vaisseau.x -= MOVING_STEP;
            }
                //si la touche appuyée est 'fleche bas', la vitesse du vaisseau diminue
            else if(event->key.keysym.sym == SDLK_DOWN){
                world->vy--;
            }
                //si la touche appuyée est 'ECHAP', le programme s'arrete
            else if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover=1;
            }

            //print_sprite(&world->vaisseau);

        }
    }
}

