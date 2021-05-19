/**
 * \file data.c
 * \brief Module d'initialisation
 * \author Ludovic Tagnon / Matheo Serrier
 * \version 3.0
 * \date 7 avril 2021
 */

//#include "sdl2-light.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>


//============================== INITIALISATION ==============================//



void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite->x=x;
    sprite->y=y;
    sprite->h=h;
    sprite->w=w;
}



void init_data(world_t * world) {

    //initialise vaisseau
    init_sprite(&world->vaisseau, (SCREEN_WIDTH - SHIP_SIZE) / 2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);

    //initialise ligne de fin
    init_sprite(&world->finish_line, SCREEN_WIDTH/2, -2000, SCREEN_WIDTH, FINISH_LINE_HEIGHT);

    //init_sprite(&world->mur, 0, 100, 3 * METEORITE_SIZE, 7 * METEORITE_SIZE);

    //initialise murs
    init_walls(world);

    //initialise vies
    init_lifes(world);

    world->vy = INITIAL_SPEED;
    world->you_won = 0;
    world->ini_trois_secondes = 10000000;

    //pas à la fin du jeu
    world->gameover = 0;

    world->nb_vies_restantes = 3;

}

void init_walls(world_t * world){



	init_sprite(&world->murs[0], 48, 0, 96, 192);
	init_sprite(&world->murs[1], 252, 0, 96, 192);
	init_sprite(&world->murs[2], 16, -352, 32, 160);
	init_sprite(&world->murs[3], 188, -352, 224, 160);
	init_sprite(&world->murs[4], 48, -672, 96, 192);
	init_sprite(&world->murs[5], 252, -672, 96, 192);

    init_sprite(&world->murs[6], 48, -1024, 96, 192);
    init_sprite(&world->murs[7], 252, -1024, 96, 192);
    init_sprite(&world->murs[8], 16, -1376, 32, 160);
    init_sprite(&world->murs[9], 188, -1376, 224, 160);
    init_sprite(&world->murs[10], 48, -1728, 96, 192);
    init_sprite(&world->murs[11], 252, -1728, 96, 192);
}

void init_lifes(world_t * world){
    for(int i=0; i<NUMBER_OF_LIFES; i++){
        init_sprite(&world->vies[i], SCREEN_WIDTH- (i+1)*SHIP_SIZE, 16, 32, 32);
    }
}


//============================== MODIFICATIONS ==============================//


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}


void update_data(world_t *world){
    world->finish_line.y += world->vy;
    world->mur.y +=  world->vy;
    depasse(&world->vaisseau);

    //decale les murs de vy
    update_walls(world);

    //collision
        //murs et vaisseau
    for(int i=0; i<NUMBER_OF_WALLS; i++){
        handle_sprites_collision(world, &world->murs[i], &world->vaisseau);
    }
        //finishline et vaisseau
    handle_sprites_collision(world, &world->finish_line, &world->vaisseau);

    print_sprite(&world->vaisseau);
    for(int i=0; i<NUMBER_OF_WALLS; i++){
        printf("\n%i", i);
        print_sprite(&world->murs[i]);
    }

    printf("%i\n",SDL_GetTicks());
    if((world->you_won==1 || world->vaisseau.disappear==1) && (SDL_GetTicks()-world->ini_trois_secondes)>3000){
        world->gameover=1;
    }
}


int is_game_over(world_t *world){
    return world->gameover;
}

void depasse(sprite_t* sprite){
    if (sprite->x<SHIP_SIZE/2){
        sprite->x = SHIP_SIZE/2;
    }
    else if(sprite->x > SCREEN_WIDTH-SHIP_SIZE/2){
        sprite->x = SCREEN_WIDTH-SHIP_SIZE/2;
    }
}

void handle_sprites_collision(world_t *world, sprite_t* sp1, sprite_t* sp2){
    if(sprites_collide(sp1,sp2)){

        if(world->nb_vies_restantes==0) {
            world->vy = 0;
            if (sp1->h % METEORITE_SIZE == 0) {
                sp2->disappear = 1;
            } else if (sp1->h % FINISH_LINE_HEIGHT == 0) {
                world->you_won = 1;
            }
            world->vaisseau.y = 10000;
            world->ini_trois_secondes = SDL_GetTicks();
        }
        else{
            world->nb_vies_restantes -=1;
            for(int i=0; i<NUMBER_OF_WALLS; i++){
                world->murs[i].y -= 4*METEORITE_SIZE;
            }
            world->finish_line.y -= 4*METEORITE_SIZE;
        }
    }
}

void update_walls(world_t *world){
	for(int i=0; i<NUMBER_OF_WALLS; i++){
		world->murs[i].y += world->vy;
	}
}

//============================== AFFICHAGE ==============================//


void print_sprite(sprite_t* sprite){
    printf("Sprite: (x,y) = (%i,%i) ; (w,h) = (%i,%i)\n\n",sprite->x,sprite->y,sprite->w,sprite->h);
}

//============================== CHECK ==============================//

int sprites_collide(sprite_t* sp1, sprite_t* sp2){

    sprite_t s1 = *sp1;

    //Vaisseau (S2)
    sprite_t v = *sp2;

    if( ( ( ( s1.x - s1.w/2 <= v.x + v.w/2 )&&( v.x + v.w/2 <= s1.x + s1.w/2 ) ) || ( ( s1.x - s1.w/2 <= v.x - v.w/2 )&&( v.x - v.w/2 <= s1.x + s1.w/2 ) ) )
    && ( ( ( ( s1.y - s1.h/2 <= v.y + v.h/2 )&&( v.y + v.h/2 <= s1.y + s1.h/2 ) ) || ( ( s1.y - s1.h/2 <= v.y - v.h/2 )&&( v.y - v.h/2 <= s1.y + s1.h/2 ) ) ) ) ){
    return 1;
    }

    return 0;
}
