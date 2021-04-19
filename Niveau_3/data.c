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


    init_sprite(&world->vaisseau, (SCREEN_WIDTH - SHIP_SIZE) / 2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    init_sprite(&world->finish_line, 0, -960, SCREEN_WIDTH, FINISH_LINE_HEIGHT);
    //init_sprite(&world->mur, 0, 100, 3 * METEORITE_SIZE, 7 * METEORITE_SIZE);
    init_walls(world);

    world->vy = INITIAL_SPEED;
    //on n'est pas à la fin du jeu
    world->gameover = 0;

}

void init_walls(world_t * world){
	init_sprite(&world->murs[0], 48, 0, 96, 192);
	init_sprite(&world->murs[1], 252, 0, 96, 192);
	init_sprite(&world->murs[2], 16, -352, 32, 160);
	init_sprite(&world->murs[3], 188, -352, 224, 160);
	init_sprite(&world->murs[4], 48, -672, 96, 192);
	init_sprite(&world->murs[5], 252, -672, 96, 192);
}




//============================== MODIFICATIONS ==============================//


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}


void update_data(world_t *world){
    world->finish_line.y += world->vy;
    world->mur.y +=  world->vy;
    depasse(&world->vaisseau);

    //murs
    update_walls(world);

    //collision
    for(int i=0; i<NUMBER_OF_WALLS; i++){
        handle_sprites_collision(world, &world->murs[i], &world->vaisseau, 2);
    }

    handle_sprites_collision(world, &world->finish_line, &world->vaisseau, 2);
    print_sprite(&world->vaisseau);
    for(int i=0; i<NUMBER_OF_WALLS; i++){
        printf("\n%i", i);
        print_sprite(&world->murs[i]);
    }

}


int is_game_over(world_t *world){
    return world->gameover;
}


void depasse(sprite_t* sprite){
    if (sprite->x<0){
        sprite->x = 0;
    }
    else if(sprite->x > SCREEN_WIDTH-SHIP_SIZE){
        sprite->x = SCREEN_WIDTH-SHIP_SIZE;
    }
}

void handle_sprites_collision(world_t *world, sprite_t* sp1, sprite_t* sp2, int make_disappear){
    if(sprites_collide(sp1,sp2)){
        world->vy=0;
        if(make_disappear != 0){
            sp2->x=-10000;
        }
    }
}

void update_walls(world_t *world){
	for(int i=0; i<6; i++){
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
    s1.x+=s1.w/2;
    s1.y+=s1.h/2;

    //Vaisseau (S2)
    sprite_t v = *sp2;
    v.x+=v.w/2;
    v.y+=v.h/2;


    if( ( ( ( s1.x - s1.w/2 <= v.x + v.w/2 )&&( v.x + v.w/2 <= s1.x + s1.w/2 ) ) || ( ( s1.x - s1.w/2 <= v.x - v.w/2 )&&( v.x - v.w/2 <= s1.x + s1.w/2 ) ) )
    && ( ( ( ( s1.y - s1.h/2 <= v.y + v.h/2 )&&( v.y + v.h/2 <= s1.y + s1.h/2 ) ) || ( ( s1.y - s1.h/2 <= v.y - v.h/2 )&&( v.y - v.h/2 <= s1.y + s1.h/2 ) ) ) ) ){
    return 1;
    }



    return 0;
}
