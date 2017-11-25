/* Projet Invasion 2014 ISN     (option.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
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

//---------------------------------------------------
//
// FONCTION DU MENU OPTION
//
//---------------------------------------------------


void option(SDL_Surface *ecran,int *theme,int *niveau)
{
    SDL_Event event;
    int choix = 1;
    int case_a,case_b,case_c,case_d,case_1,case_2,case_3,case_4,case_5,case_quitter;
    logo_afficher(ecran);

    init_rectangle_option();

    while (choix)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: // veut quitte le programme
                choix = 0;  // sort de option.c
                break;
            case SDL_MOUSEBUTTONUP:
                rectangle_option.Coord_souris.x = event.button.x;
                rectangle_option.Coord_souris.y = event.button.y;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // quitter les reglages
                        menu_afficher(ecran,menu.img_option_quitter); // illumine le bouton quitter du menu option
                        choix = 0;
                        break;
                    case SDLK_q: // theme a (qwerty en azerty)
                        case_a = 1;
                        break;
                    case SDLK_b: // theme b
                        menu_afficher(ecran,menu.img_theme2); // illumine le bouton theme2 du menu option
                        *theme = 1 ;
                        break;
                    case SDLK_c: // theme c
                        menu_afficher(ecran,menu.img_theme3); // illumine le bouton theme3 du menu option
                        *theme = 2 ;
                        break;
                    case SDLK_d: // theme d
                        menu_afficher(ecran,menu.img_theme4); // illumine le bouton theme4 du menu option
                        *theme = 3 ;
                        break;
                    case SDLK_KP1: // niveau 0
                        menu_afficher(ecran,menu.img_niveau0); // illumine le bouton niveau 0 du menu option
                        *niveau = 0 ;
                        break;
                    case SDLK_KP2: // niveau 1
                        menu_afficher(ecran,menu.img_niveau1); // illumine le bouton niveau 1 du menu option
                        *niveau = 1 ;
                        break;
                    case SDLK_KP3: // niveau 2
                        menu_afficher(ecran,menu.img_niveau2); // illumine le bouton niveau 2 du menu option
                        *niveau = 2 ;
                        break;
                    case SDLK_KP4: // niveau 3
                        menu_afficher(ecran,menu.img_niveau3); // illumine le bouton niveau 3 du menu option
                        *niveau = 3 ;
                        break;
                    case SDLK_KP5: // niveau 4
                        menu_afficher(ecran,menu.img_niveau4); // illumine le bouton niveau 4 du menu option
                        *niveau = 4 ;
                        break;
                    case SDLK_KP0: // quitter les reglages
                        menu_afficher(ecran,menu.img_option_quitter); // illumine le bouton quitter du menu option
                        choix = 0;
                        break;
                    default:
                        break;
                } // switch
                    default:
                        break;
                break;
        } // switch

        if (coli_souris_option(&case_a,&case_b,&case_c,&case_d,&case_1,&case_2,&case_3,&case_4,&case_5,&case_quitter) == 1)
        {
            if (case_a == 1)
            {
                menu_afficher(ecran,menu.img_theme1); // illumine le bouton theme1 du menu option
                *theme = 0 ;
                case_a = 0;
            }
            if (case_b == 1)
            {
                menu_afficher(ecran,menu.img_theme2); // illumine le bouton theme1 du menu option
                *theme = 1;
                case_b = 0;
            }
            if (case_c == 1)
            {
                menu_afficher(ecran,menu.img_theme3); // illumine le bouton theme1 du menu option
                *theme = 2;
                case_c = 0;
            }
            if (case_d == 1)
            {
                menu_afficher(ecran,menu.img_theme4); // illumine le bouton theme1 du menu option
                *theme = 3;
                case_d = 0;
            }

            if (case_1 == 1)
            {
                menu_afficher(ecran,menu.img_niveau0); // illumine le bouton niveau 0 du menu option
                *niveau = 0;
                case_1 = 0;
            }
            if (case_2 == 1)
            {
                menu_afficher(ecran,menu.img_niveau1); // illumine le bouton niveau 0 du menu option
                *niveau = 1;
                case_2 = 0;
            }
            if (case_3 == 1)
            {
                menu_afficher(ecran,menu.img_niveau2); // illumine le bouton niveau 0 du menu option
                *niveau = 2;
                case_3 = 0;
            }
            if (case_4 == 1)
            {
                menu_afficher(ecran,menu.img_niveau3); // illumine le bouton niveau 0 du menu option
                *niveau = 3;
                case_4 = 0;
            }
            if (case_5 == 1)
            {
                menu_afficher(ecran,menu.img_niveau4); // illumine le bouton niveau 0 du menu option
                *niveau = 4;
                case_5 = 0;
            }
            if (case_quitter == 1)
            {
                menu_afficher(ecran,menu.img_option_quitter); // illumine le bouton niveau 0 du menu option
                case_quitter = 0;
                choix = 0;
            }
        }

        // Effacement de l'écran affichage du menu mise a jour de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu_option.img, NULL, ecran, &menu_option.pos);
        SDL_Flip(ecran);

    } // while

    logo_afficher(ecran); // on affiche le logo avant de quitter le menu option
} // option()




