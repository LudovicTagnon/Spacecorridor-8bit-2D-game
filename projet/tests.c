/**
 * \file tests.c
 * \brief Module de test
 * \author Ludovic Tagnon / Matheo Serrier
 * \version 3.0
 * \date 7 avril 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "constantes.h"

//============================== TEST_..._PARAM ==============================//

void test_init_sprite_param(sprite_t* s){
    init_sprite(s, (SCREEN_WIDTH - SHIP_SIZE) / 2, (SCREEN_HEIGHT - SHIP_SIZE), SHIP_SIZE, SHIP_SIZE);
    print_sprite(s);
    init_sprite(s, 1,2,3,4);
    print_sprite(s);
}


void test_depasse_param(sprite_t* s){
    depasse(s);
    print_sprite(s);
}

void test_sprites_collide_param(sprite_t* sp1, sprite_t* sp2){
    init_sprite(sp1,0,0,2,2);
    init_sprite(sp2, 1,1,2,2);
    printf("%i\n\n", sprites_collide(sp1,sp2));
    init_sprite(sp1,0,0,2,2);
    init_sprite(sp2, 2,2,2,2);
    printf("%i\n\n", sprites_collide(sp1,sp2));
    init_sprite(sp1,0,0,2,2);
    init_sprite(sp2, 3,3,2,2);
    printf("%i\n\n", sprites_collide(sp1,sp2));
    init_sprite(sp1,3,3,2,2);
    init_sprite(sp2, 2,2,2,2);
    printf("%i\n\n", sprites_collide(sp1,sp2));

}

void test_handle_sprites_collision_param(world_t *world, sprite_t* sp1, sprite_t* sp2){
    printf("Vitesse initiale: %i", world->vy);
    handle_sprites_collision(world, sp1, sp2);
    printf("\n\nNouvelle vitesse: %i\n", world->vy);
    }

//============================== TEST_... ==============================//

void test_init_sprite(){
    sprite_t sprite;
    sprite_t* p_sprite = &sprite;
    test_init_sprite_param(p_sprite);
}

void test_depasse(){
    sprite_t Sprite;
    sprite_t* s = &Sprite;
    init_sprite(s, -100,2,3,4);
    print_sprite(s);
    printf("Apres fonction depasse\n\n");
    test_depasse_param(s);
}

void test_sprites_collide(){
    sprite_t Sprite1;
    sprite_t* s1 = &Sprite1;
    sprite_t Sprite2;
    sprite_t* s2 = &Sprite2;
    test_sprites_collide_param(s1,s2);

}

void test_handle_sprites_collision(){
    world_t w;
    world_t* world = &w;
    world->vy=10;
    init_sprite(&world->vaisseau, 0,0,2,2);
    init_sprite(&world->mur, 2,2,3,7);
    test_handle_sprites_collision_param(world, &world->vaisseau, &world->mur);
}

//============================== MAIN ==============================//

int main(){
    //test_init_sprite();
    //test_depasse();
    //test_sprites_collide();
    //test_handle_sprites_collision();
    return 0;
}
