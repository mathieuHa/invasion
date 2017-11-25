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

//--------------------------------------------------------------------
//
// FONCTION ANIMATION DES BONUS
//
//--------------------------------------------------------------------


void move_bonus()
{
    if (bonus.point_supp == 1)  // si le tir est actif
    {
        if (bonus.pos.y  >= MAX_Y)  // si il est trop bas ( sort de l'ecran )
        {
            bonus.point_supp = 0;     // on le désactive
            bonus.actif = 100;
        }
        else
        {
            bonus.pos.y += 2;    // sinon il se déplace verticalemen
        }
    }

    else if (bonus.vie_supp == 1)  // si le tir est actif
    {
        if (bonus.pos.y  >= MAX_Y)  // si il est trop bas ( sort de l'ecran )
        {
            bonus.vie_supp = 0;     // on le désactive
            bonus.actif = 100;
        }
        else
        {
            bonus.pos.y += 2;    // sinon il se déplace verticalemen
        }
    }

    else if (bonus.super_tir == 1)  // si le tir est actif
    {
        if (bonus.pos.y  >= MAX_Y)  // si il est trop bas ( sort de l'ecran )
        {
            bonus.super_tir = 0;     // on le désactive
            bonus.actif = 100;
        }
        else
        {
            bonus.pos.y += 2;    // sinon il se déplace verticalemen
        }
    }

    else if (bonus.super_tir_enemie == 1)  // si le tir est actif
    {
        if (bonus.pos.y  >= MAX_Y)  // si il est trop bas ( sort de l'ecran )
        {
            bonus.super_tir_enemie = 0;     // on le désactive
            bonus.actif = 100;
        }
        else
        {
            bonus.pos.y += 2;    // sinon il se déplace verticalemen
        }
    }
    else if (bonus.super_tir_cote == 1)  // si le tir est actif
    {
        if (bonus.pos.y  >= MAX_Y)  // si il est trop bas ( sort de l'ecran )
        {
            bonus.super_tir_cote = 0;     // on le désactive
            bonus.actif = 100;
        }
        else
        {
            bonus.pos.y += 2;    // sinon il se déplace verticalemen
        }
    }

    else if (bonus.bad_luck == 1)  // si le tir est actif
    {
        if (bonus.pos.y >= MAX_Y)  // si il est trop bas ( sort de l'ecran )
        {
            bonus.bad_luck = 0;     // on le désactive
            bonus.actif = 100;
        }
        else
        {
            bonus.pos.y += 2;    // sinon il se déplace verticalemen
        }
    }

} // move_tir_enemie()

void blit_bonus(SDL_Surface *ecran)
{
    int tempsActuel;
    //switch(bonus.actif)
    //{
   // case 0 :
        switch (bonus.point_supp)
        {
        case 1 :    // si l'enemie est en vie
            SDL_BlitSurface(bonus.img_point_supp, NULL, ecran, &bonus.pos); // On l'affiche
            break;
        case 2 :    // si l'enemie est en touché

            SDL_BlitSurface(bonus.img_point_supp, NULL, ecran, &bonus.pos);   // on affiche le tireur mort*/
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - bonus.temps_explosion >= 150)    // le temps de l'explosion est dépassé on le réactive
            {
                bonus.actif = 100;
                bonus.point_supp = 0;
            }

            break;
        } // switch
     //   break; // case 0

    //case 1 :
        switch (bonus.vie_supp)
        {
        case 1 :    // si l'enemie est en vie
            SDL_BlitSurface(bonus.img_vie_supp, NULL, ecran, &bonus.pos); // On l'affiche
            break;
        case 2 :    // si l'enemie est en touché

            SDL_BlitSurface(bonus.img_vie_supp, NULL, ecran, &bonus.pos);   // on affiche le tireur mort*/
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - bonus.temps_explosion >= 150)    // le temps de l'explosion est dépassé on le réactive
            {
                bonus.actif = 100;
                bonus.vie_supp = 0;
            }

            break;
        } // switch
    //    break; // case 1

    //case 2 :
        switch (bonus.super_tir)
        {
        case 1 :    // si l'enemie est en vie
            SDL_BlitSurface(bonus.img_super_tir, NULL, ecran, &bonus.pos); // On l'affiche
            break;
        case 2 :    // si l'enemie est en touché
            SDL_BlitSurface(bonus.img_super_tir, NULL, ecran, &bonus.pos);   // on affiche le tireur mort*/
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - bonus.temps_explosion >= 150)    // le temps de l'explosion est dépassé on le réactive
            {
                bonus.actif = 100;
                bonus.super_tir = 0;
            }

            break;
        } // switch

        switch (bonus.super_tir_enemie)
        {
        case 1 :    // si l'enemie est en vie
            SDL_BlitSurface(bonus.img_super_tir_enemie, NULL, ecran, &bonus.pos); // On l'affiche
            break;
        case 2 :    // si l'enemie est en touché
            SDL_BlitSurface(bonus.img_super_tir_enemie, NULL, ecran, &bonus.pos);   // on affiche le tireur mort*/
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - bonus.temps_explosion >= 150)    // le temps de l'explosion est dépassé on le réactive
            {
                bonus.actif = 100;
                bonus.super_tir_enemie = 0;
            }

            break;
        } // switch

        switch (bonus.super_tir_cote)
        {
        case 1 :    // si l'enemie est en vie
            SDL_BlitSurface(bonus.img_super_tir_cote, NULL, ecran, &bonus.pos); // On l'affiche
            break;
        case 2 :    // si l'enemie est en touché
            SDL_BlitSurface(bonus.img_super_tir_cote, NULL, ecran, &bonus.pos);   // on affiche le tireur mort*/
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - bonus.temps_explosion >= 150)    // le temps de l'explosion est dépassé on le réactive
            {
                bonus.actif = 100;
                bonus.super_tir_cote = 0;
            }

            break;
        } // switch
     //   break; // case 2
  //  case 3 :
        switch (bonus.bad_luck)
        {
        case 1 :    // si l'enemie est en vie
            SDL_BlitSurface(bonus.img_bad_luck, NULL, ecran, &bonus.pos); // On l'affiche
            break;
        case 2 :    // si l'enemie est en touché
            SDL_BlitSurface(Themes[1].img_missile_mort, NULL, ecran, &bonus.pos);   // on affiche le tireur mort*/
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - bonus.temps_explosion >= 150)    // le temps de l'explosion est dépassé on le réactive
            {
                bonus.actif = 100;
                bonus.bad_luck = 0;
            }

            break;
        } // switch
        bonus.oldpos.x = bonus.pos.x;
        bonus.oldpos.y = bonus.pos.y;



} // blit_enemie()

