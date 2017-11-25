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
extern Score        score[MAX_SCORE];

//--------------------------------------------------------------------
//
// FONCTION ANIMATION DU LOGO PENDANT 180 MS
//
//--------------------------------------------------------------------

void logo_afficher(SDL_Surface *ecran)
{
    logo.pos.x = MAX_X/2-logo.img->w/2; // le logo est centrer quelque soit la taille de l'écran
    logo.pos.y = MAX_Y/2-logo.img->h/2;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // effacement de l'écran
    SDL_BlitSurface(logo.img, NULL, ecran, &logo.pos);
    SDL_Flip(ecran); // mise a jour de l'ecran
    SDL_Delay(180);  // mise en veille du programme pendant 180 ms
}

void menu_afficher(SDL_Surface *ecran,SDL_Surface *img)
{
    menu.pos.x = MAX_X / 2 - menu.img->w / 2;  // on centre le menu quelque soit la resolution
    menu.pos.y = MAX_Y / 2 - menu.img->h / 2;  //
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // effacement de l'écran
    SDL_BlitSurface(img, NULL, ecran, &menu.pos);   // on blit l'image du menu selectionné
    SDL_Flip(ecran); // mise a jour de l'ecran
    SDL_Delay(180);  // mise en veille du programme pendant 180ms
}

//--------------------------------------------------------------------
//
// FONCTION QUI TRANSFORME LES LETTRES QWERTY EN AZERTY
//
//--------------------------------------------------------------------

char azerty(char value)
{

    switch (value)              // on test la touche enfoncé par le joueur
    {
        case 'a':
            return 'q';         // on retourne la lettre azerty qui correspond au qwerty
            break;
        case 'z':
            return 'w';
            break;
        case '.':
            return 'm';
            break;
        case 'q':
            return 'a';
            break;
        case ';':
            return 'm';
            break;
        case 'w':
            return 'z';
            break;
        case ' ':               // on transfome les espaces en underscore
            return '_';
            break;
        default :               // ou la lettre est la même et on la renvoi tel quelle
            return value;
        break;
    }
}

//--------------------------------------------------------------------
//
// FONCTION QUI VERIFIE LA CONTACT ENTRE DEUX SURFACE
//
//--------------------------------------------------------------------

int Collision(SDL_Rect *R1 , SDL_Rect *R2)  // elle prend en paramètre les SDL_rect (la taille high largeur weidth
{                                           // et les position .x .y des surfaces R1 R2 ( R pour rectangle ) )
    if ((R1->x + R1->w < R2->x)             // si R1 plus a gauche que R2
      ||(R1->y + R1->h < R2->y)             // si R1 plus bas que R2
      ||(R1->x > R2->x + R2->w)             // si R1 plus a droite de R2
      ||(R1->y > R2->y + R2->h))            // si R1 plus haut que R2
        return 0;                           // 0 = pas de collision
        else
    return 1;                               // sinon il y a une collision
}

void clipper_f(SDL_Surface *ecran,SDL_Rect *clip, SDL_Rect *pos_fond,SDL_Rect *pos_fond_c,SDL_Surface *S1,SDL_Rect *Sold,int theme)
{
        clip->x = Sold->x;
        clip->y = Sold->y;
        clip->h = S1->h;
        clip->w = S1->w;
        SDL_SetClipRect(ecran,clip); // clipper sur les missiles

        pos_fond_c->x = pos_fond->x;
        pos_fond_c->y = pos_fond->y;

        SDL_BlitSurface(Themes[theme].fond, NULL, ecran, pos_fond_c); // effacer les missiles
}
void clipper_sc(SDL_Surface *ecran,SDL_Rect *clip, SDL_Rect *pos_fond,SDL_Rect *pos_fond_c,SDL_Rect *Sold,int theme)
{
        clip->x = Sold->x;
        clip->y = Sold->y;
        clip->h = Sold->h;
        clip->w = Sold->w;
        SDL_SetClipRect(ecran,clip); // clipper sur les missiles

        pos_fond_c->x = pos_fond->x;
        pos_fond_c->y = pos_fond->y;

        SDL_BlitSurface(Themes[theme].fond, NULL, ecran, pos_fond_c); // effacer les missiles
}
