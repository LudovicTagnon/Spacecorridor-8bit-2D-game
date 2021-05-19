/**
 * \file graphics.c
 * \brief Module d'affichage des elements du jeu
 * \author Ludovic Tagnon / Matheo Serrier
 * \version 3.0
 * \date 7 avril 2021
 */


#include "graphics.h"


void init_textures(SDL_Renderer *renderer, resources_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->sprite = load_image( "ressources/spaceship.bmp",renderer);
    textures->finish_line = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorites = load_image( "ressources/meteorite.bmp",renderer);
    textures->font = load_font("ressources/arial.ttf",14) ;
    textures->vies = load_image( "ressources/life.bmp",renderer);
}
void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_data(world);
    init_textures(*renderer,textures);
}

void clean_textures(resources_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->finish_line);
    clean_texture(textures->sprite);
    clean_texture(textures->meteorites);
    clean_font(textures->font);
    clean_texture(textures->vies);
}
void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
        apply_texture(texture, renderer, 0, 0);
    }
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    if(texture != NULL){
        apply_texture(texture, renderer, (sprite->x)-((sprite->w)/2), (sprite->y)-((sprite->h)/2));
    }
}

void apply_walls(SDL_Renderer *renderer, resources_t *textures, world_t *world){
    for(int i=0; i < NUMBER_OF_WALLS; i++){
        handle_wall(renderer, textures, (&world->murs[i]));
    }
}

void handle_wall(SDL_Renderer *renderer, resources_t *textures, sprite_t* mur){
    sprite_t t;
    sprite_t* temp = &t;
    *temp = *mur;

    int H = (mur->h)/METEORITE_SIZE;
    int W = (mur->w)/METEORITE_SIZE;

    for(int y=0 ; y<H; y++){
        for(int x=0 ; x<W ; x++){
            apply_sprite(renderer, textures->meteorites, temp);
            temp->x += METEORITE_SIZE;
        }
        temp->x -= W*METEORITE_SIZE;
        temp->y += METEORITE_SIZE;
    }
}

void apply_lifes(SDL_Renderer *renderer, resources_t *textures, world_t *world){
    for(int i=0; i < world->nb_vies_restantes; i++){
        apply_sprite(renderer, textures->vies, &world->vies[i]);
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *textures){

    //on vide le renderer
    clear_renderer(renderer);

    //application des textures du background dans le renderer
    apply_background(renderer, textures->background);

    //application de la texture du sprite (vaisseau) dans le renderer
    if(world->vaisseau.disappear!=1){
        apply_sprite(renderer, textures->sprite, &world->vaisseau);
    }

    //application de la texture du sprite (finish_line) dans le renderer
    apply_sprite(renderer, textures->finish_line, &world->finish_line);

    //Gere l'affichage des vies
    apply_lifes(renderer, textures, world);

    //Gere l'affichage des murs
    apply_walls(renderer, textures, world);


    char time[12];
    sprintf(time,"%u", SDL_GetTicks());
    apply_text(renderer, 10, 10, 50, 50, time, textures->font);

    if(world->vaisseau.disappear==1){
        apply_text(renderer, (SCREEN_WIDTH-250)/2, (SCREEN_HEIGHT-100)/2, 250, 100, "PERDU!", textures->font);
    }

    if(world->you_won==1){
        apply_text(renderer, (SCREEN_WIDTH-250)/2, (SCREEN_HEIGHT-100)/2, 250, 100, "GAGNE", textures->font);
    }

    // on met à jour l'écran
    update_screen(renderer);
}

void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *textures, world_t * world){
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
                if(world->vy>0){
                    world->vaisseau.x += world->vy*MOVING_STEP;
                }
            }
                //si la touche appuyée est 'fleche haut', la vitesse du vaisseau augment
            else if(event->key.keysym.sym == SDLK_UP){
                    world->vy++;
            }
                //si la touche appuyée est 'fleche gauche', le vaisseau va vers la droite
            else if(event->key.keysym.sym == SDLK_LEFT){
                if(world->vy>0){
                    world->vaisseau.x -= world->vy*MOVING_STEP;
                }
            }
                //si la touche appuyée est 'fleche bas', la vitesse du vaisseau diminue
            else if(event->key.keysym.sym == SDLK_DOWN){
                if(world->vy>0){
                    world->vy--;
                }
            }
                //si la touche appuyée est 'ECHAP', le programme s'arrete
            else if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover=1;
            }

            //print_sprite(&world->vaisseau);

        }
    }
}

