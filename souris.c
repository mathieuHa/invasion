/* Projet Invasion 2014 ISN     (usefull.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/

//---------------------------------------------------
//
// FONCTIONS UTILITAIRES
//
//---------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "main.h"
#include "fonction.h"

// on rappelle que les structures sont bien déclarer ailleurs
extern Theme        Themes[4];
extern Niveau       Niveaux[5];
extern Tireur       tireur;
extern Missile      missile[MAX_MISSILES];
extern Tir          tir[MAX_MISSILES];
extern Enemie       enemie[MAX_ENEMIE];
extern Bonus        bonus;
extern Logo         logo;
extern Menu         menu;
extern Menu_Option  menu_option;
extern Rectangle_menu rectangle_menu;
extern Rectangle_option rectangle_option;
extern Score        score[MAX_SCORE];

void coord_souris_0()
{
    rectangle_option.Coord_souris.x = 0;
    rectangle_option.Coord_souris.y = 0;
    rectangle_menu.Coord_souris.x = 0;
    rectangle_menu.Coord_souris.y = 0;
}

void init_rectangle_option()
{
    rectangle_option.Coord_souris.x = 0;
    rectangle_option.Coord_souris.h = 2;
    rectangle_option.Coord_souris.y = 0;
    rectangle_option.Coord_souris.w = 2;

    rectangle_option.rectangle_a.x = 0;
    rectangle_option.rectangle_a.y = 3 * MAX_Y / 13;
    rectangle_option.rectangle_a.h = 1 * MAX_Y / 9;
    rectangle_option.rectangle_a.w = 8 * MAX_X / 23;

    rectangle_option.rectangle_b.x = 0;
    rectangle_option.rectangle_b.y = 5 * MAX_Y / 13;
    rectangle_option.rectangle_b.h = 1 * MAX_Y / 9;
    rectangle_option.rectangle_b.w = 8 * MAX_X / 23;

    rectangle_option.rectangle_c.x = 0;
    rectangle_option.rectangle_c.y = 12 * MAX_Y / 21;
    rectangle_option.rectangle_c.h = 1 * MAX_Y / 9;
    rectangle_option.rectangle_c.w = 8 * MAX_X / 23;

    rectangle_option.rectangle_d.x = 0;
    rectangle_option.rectangle_d.y = 14 * MAX_Y / 19;
    rectangle_option.rectangle_d.h = 1 * MAX_Y / 9;
    rectangle_option.rectangle_d.w = 8 * MAX_X / 23;


    rectangle_option.rectangle_1.x = 14 * MAX_X / 23;
    rectangle_option.rectangle_1.y = 1 * MAX_Y / 4;
    rectangle_option.rectangle_1.h = 13 * MAX_Y / 100;
    rectangle_option.rectangle_1.w = 9 * MAX_X / 23;

    rectangle_option.rectangle_2.x = 14 * MAX_X / 23;
    rectangle_option.rectangle_2.y = 5 * MAX_Y / 13;
    rectangle_option.rectangle_2.h = 13 * MAX_Y / 100;
    rectangle_option.rectangle_2.w = 9 * MAX_X / 23;

    rectangle_option.rectangle_3.x = 14 * MAX_X / 23;
    rectangle_option.rectangle_3.y = 7 * MAX_Y / 13;
    rectangle_option.rectangle_3.h = 13 * MAX_Y / 100;
    rectangle_option.rectangle_3.w = 9 * MAX_X / 23;

    rectangle_option.rectangle_4.x = 14 * MAX_X / 23;
    rectangle_option.rectangle_4.y = 8 * MAX_Y / 12;
    rectangle_option.rectangle_4.h = 13 * MAX_Y / 100;
    rectangle_option.rectangle_4.w = 9 * MAX_X / 23;

    rectangle_option.rectangle_5.x = 14 * MAX_X / 23;
    rectangle_option.rectangle_5.y = 9 * MAX_Y / 11;
    rectangle_option.rectangle_5.h = 13 * MAX_Y / 100;
    rectangle_option.rectangle_5.w = 9 * MAX_X / 23;

    rectangle_option.rectangle_quitter.x = 8 * MAX_X / 23;
    rectangle_option.rectangle_quitter.y = 11 * MAX_Y / 13;
    rectangle_option.rectangle_quitter.h = 2 * MAX_Y / 13;
    rectangle_option.rectangle_quitter.w = 5 * MAX_X / 23;
}

void init_rectangle_menu()
{
    rectangle_menu.Coord_souris.x = 0;
    rectangle_menu.Coord_souris.h = 2;
    rectangle_menu.Coord_souris.y = 0;
    rectangle_menu.Coord_souris.w = 2;

    rectangle_menu.rectangle_jouer.x = 9 * MAX_X / 23;
    rectangle_menu.rectangle_jouer.y = 3 * MAX_Y / 13;
    rectangle_menu.rectangle_jouer.h = 2 * MAX_Y / 13;
    rectangle_menu.rectangle_jouer.w = 5 * MAX_X / 23;

    rectangle_menu.rectangle_option.x = 8 * MAX_X / 11;
    rectangle_menu.rectangle_option.y = 6 * MAX_Y / 13;
    rectangle_menu.rectangle_option.h = 2 * MAX_Y / 13;
    rectangle_menu.rectangle_option.w = 7 * MAX_X / 23;

    rectangle_menu.rectangle_score.x = 1 * MAX_X / 23;
    rectangle_menu.rectangle_score.y = 6 * MAX_Y / 13;
    rectangle_menu.rectangle_score.h = 2 * MAX_Y / 13;
    rectangle_menu.rectangle_score.w = 6 * MAX_X / 23;

    rectangle_menu.rectangle_quitter.x = 9 * MAX_X / 23;
    rectangle_menu.rectangle_quitter.y = 9 * MAX_Y / 13;
    rectangle_menu.rectangle_quitter.h = 2 * MAX_Y / 13;
    rectangle_menu.rectangle_quitter.w = 6 * MAX_X / 23;
}

void clic_menu_option(SDL_Surface *ecran,int *theme,int *niveau,int *case_option)
{
    menu_afficher(ecran,menu.img_options); // illumine le bouton options du menu
    option(ecran,theme,niveau);
}

void clic_menu_score(SDL_Surface *ecran,int *theme,int *niveau,int *case_score)
{
    menu_afficher(ecran,menu.img_score);
    afficher_score(ecran,0,0,0,0);
}

void clic_menu_quitter(SDL_Surface *ecran,int *theme,int *niveau)
{
    menu_afficher(ecran,menu.img_quitter);
}



int coli_souris_option(int *case_a,int *case_b,int *case_c,int *case_d,int *case_1,int *case_2,int *case_3,int *case_4,int *case_5,int *case_quitter)
{
    if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_a) == 1)
    {
        (*case_a) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_b) == 1)
    {
        (*case_b) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_c) == 1)
    {
        (*case_c) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_d) == 1)
    {
        (*case_d) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_1) == 1)
    {
        (*case_1) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_2) == 1)
    {
        (*case_2) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_3) == 1)
    {
        (*case_3) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_4) == 1)
    {
        (*case_4) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_5) == 1)
    {
        (*case_5) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_option.Coord_souris,&rectangle_option.rectangle_quitter) == 1)
    {
        (*case_quitter) = 1;
        coord_souris_0();
        return 1;
    }
    return 0;
}

int coli_souris_menu(int *case_jouer,int *case_score,int *case_quitter,int *case_option)
{

    if (Collision(&rectangle_menu.Coord_souris,&rectangle_menu.rectangle_jouer) == 1)
    {
        (*case_jouer) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_menu.Coord_souris,&rectangle_menu.rectangle_option) == 1)
    {
        (*case_option) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_menu.Coord_souris,&rectangle_menu.rectangle_score) == 1)
    {
        (*case_score) = 1;
        coord_souris_0();
        return 1;
    }
    else if (Collision(&rectangle_menu.Coord_souris,&rectangle_menu.rectangle_quitter) == 1)
    {
        (*case_quitter)= 1;
        coord_souris_0();
        return 1;
    }

    return 0;
}


