 /* Projet Invasion 2014 ISN     (animation.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/

//---------------------------------------------------
//
// FONCTIONS D'ANIMATIONS
//
//---------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "fonction.h"


extern Theme        Themes[4];
extern Niveau       Niveaux[5];
extern Tireur       tireur;
extern Missile      missile[MAX_MISSILES];
extern Tir          tir[MAX_MISSILES];
extern Enemie       enemie[MAX_ENEMIE];
extern int          sens_enemie;
extern Bonus        bonus;
extern Logo         logo;
extern Menu         menu;
extern Menu_Option  menu_option;
extern Score        score[MAX_SCORE];

// on rappelle que les structures sont bien déclarer ailleurs
//---------------------------------------------------
//
// FONCTION DE DEPLACEMENT DES MISSILES
//
//---------------------------------------------------

void move_missile()
{
    int ind_mis;

    for (ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
        {
            if (missile[ind_mis].actif == 1)  // si le missile est actif
            {
                if (missile[ind_mis].pos.y  <= 0)   // si il est trop haut ( sort de l'ecran )
                {
                    missile[ind_mis].actif = 0; // on le désactive
                }
                else
                {
                    missile[ind_mis].pos.y -= missile[ind_mis].vitesse;    // sinon il se déplace verticalement
                    missile[ind_mis].pos.x += missile[ind_mis].vx;    // sinon il se déplace verticalement
                }
            }
        }
} // move_missile()


void move_tir_enemie()
{
    int ind_tir;

    for (ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
        {
            if (tir[ind_tir].actif == 1)  // si le tir est actif
            {
                if (tir[ind_tir].pos.y  >= MAX_Y)  // si il est trop bas ( sort de l'ecran )
                {
                    tir[ind_tir].actif = 0;     // on le désactive
                }
                else
                {
                    tir[ind_tir].pos.y += tir[ind_tir].vitesse;    // sinon il se déplace verticalement
                }
            }
        }
} // move_tir_enemie()

//---------------------------------------------------
//
// FONCTION DE DEPLACEMENT DES ENNEMIS
//
//---------------------------------------------------

void move_enemie(int niveau,int theme)
{
    int ind_enemie,depasse;

    // deplacement de l'enemie

    for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
    {
            if (enemie[ind_enemie].alive == 1)
            {
                enemie[ind_enemie].pos.x += Niveaux[niveau].dx_enemie * sens_enemie;
            } // if
    } // for

    // test sortie ecran

    depasse = 0;
    for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
    {
            if (enemie[ind_enemie].alive == 1)
            {                       // trop a gauche ou a droite de l'écran
                if ((enemie[ind_enemie].pos.x + Themes[theme].img_enemie->w >= MAX_X_JEU ) || (enemie[ind_enemie].pos.x <= 0))
                {
                   depasse = 1;
                } // if
            } // if
    } // for

    for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
    {
            if (enemie[ind_enemie].alive == 1)
            {                        // trop bas dans l'écran
                if ((enemie[ind_enemie].pos.y + Themes[theme].img_enemie->h >= MAX_Y ) )
                {
                   enemie[ind_enemie].alive = 2; // l'enemie est explosé
                   enemie[ind_enemie].temps_explosion = SDL_GetTicks();
                   score[1].nombre_tue_niv +=1;  // un enemie est tué (pour le changement de niveau)
                   score[1].point_inter = -125;  // on retire des points le joueur a loupé des enemies
                } // if
            } // if
    } // for

    if (depasse == 1)                   // si l'enemie touche un des bord de l'ecran
    {
        sens_enemie = - sens_enemie;    // on change le sens de l'enemie
        for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
        {
            if (enemie[ind_enemie].alive == 1)
            {
                enemie[ind_enemie].pos.y += Niveaux[niveau].dy_enemie; // et on le descent d'un cran
            } // if
        } // for
    } // if

} // move_enemie()

//---------------------------------------------------------
//
// FONCTION DE GESTION DE COLLISION ENTRE ENEMIE ET MISSILE
//
//---------------------------------------------------------

void collision(int theme,int niveau)
{
    int ind_mis;
    int ind_enemie;
    int ind_tir;

    // on parcours les deux tableaux
    for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
    {
        for (ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
        {
            if( (missile[ind_mis].actif == 1) && (enemie[ind_enemie].alive == 1)) // on verifie qu'ils sont en vie et actif
            {
                if ( Collision(&missile[ind_mis].pos,&enemie[ind_enemie].pos) == 1) // si collision
                {
                    missile[ind_mis].actif = 2;                        // on l'explose
                    missile[ind_mis].temps_explosion = SDL_GetTicks(); // mise a jour du debut de l'explosion
                    enemie[ind_enemie].alive = 2;                       // on l'explose
                    score[1].point_inter += 100;                        // on donne des points pour le kill
                    score[1].nombre_tue_niv +=1;                        // un enemie est tué (pour le changement de niveau)
                    enemie[ind_enemie].temps_explosion = SDL_GetTicks(); // mise a jour du debut de l'explosion
                    if (bonus.actif == 10)
                    {
                        bonus.actif = rand()% (6-0);
                        fprintf(stderr,"rang_bonus  = %d \n",bonus.actif);
                        bonus.pos.x = enemie[ind_enemie].pos.x;
                        bonus.pos.y = enemie[ind_enemie].pos.y;
                        switch(bonus.actif)
                        {
                            case 0:
                                bonus.point_supp = 1;
                                break;
                            case 1:
                                bonus.vie_supp = 1;
                                break;
                            case 3:
                                bonus.bad_luck = 1;
                                break;
                            case 2:
                                bonus.super_tir = 1;
                                break;
                            case 4:
                                bonus.super_tir_enemie = 1;
                                break;
                            case 5:
                                bonus.super_tir_cote = 1;
                                break;
                        }
                    }
                } // if
            } // if
        }

    } // for missile vs enemie

    // on parcours les deux tableaux
    for (ind_tir=0;ind_tir<MAX_ENEMIE;ind_tir++)
    {
        for (ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
        {
            if( (missile[ind_mis].actif == 1) && (tir[ind_tir].actif == 1)) // on verifie qu'ils sont en vie et actif
            {
                if ( Collision(&missile[ind_mis].pos,&tir[ind_tir].pos) == 1) // si collision
                {
                    missile[ind_mis].actif = 2;                         // on l'explose
                    missile[ind_mis].temps_explosion = SDL_GetTicks();  // mise a jour du debut de l'explosion
                    tir[ind_tir].actif = 2;                             // on l'explose
                    score[1].point_inter += 20;                         // on donne des points pour le kill
                    tir[ind_tir].temps_explosion = SDL_GetTicks();      // mise a jour du debut de l'explosion
                } // if
            } // if
        }

    } // for missile vs tir_enemie

    // on parcours le tableau
    for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
    {
        if ((tireur.alive == 1) && (enemie[ind_enemie].alive == 1)) // on verifie qu'ils sont en vie et actif
        {
            if ( Collision(&tireur.pos,&enemie[ind_enemie].pos) == 1) // si collision
            {
                tireur.alive = 2;                                       // on l'explose
                tireur.temps_explosion= SDL_GetTicks();                 // mise a jour du debut de l'explosion
                enemie[ind_enemie].alive = 2;                           // on l'explose
                score[1].point_inter += -150;                           // on retire des points le joueur s'est fait touché par un enemie
                score[1].nombre_tue_niv +=1;                            // un enemie est tué (pour le changement de niveau)
                score[1].vie -=1;
                enemie[ind_enemie].temps_explosion = SDL_GetTicks();    // mise a jour du debut de l'explosion
            } // if
        } // if

    } // for enemie vs tireur

    /** bonus*/

    if ((tireur.alive == 1) && (bonus.point_supp == 1)) // on verifie qu'ils sont en vie et actif
    {
        if ( Collision(&tireur.pos,&bonus.pos) == 1) // si collision
        {
            tireur.alive = 2;                                       // on l'explose
            tireur.temps_explosion= SDL_GetTicks();                 // mise a jour du debut de l'explosion
            bonus.point_supp = 2;
            bonus.temps_explosion = SDL_GetTicks();
            score[1].point_inter += 1000;                           // on retire des points le joueur s'est fait touché par un enemie
        } // if
    } // if

    if ((tireur.alive == 1) && (bonus.vie_supp == 1)) // on verifie qu'ils sont en vie et actif
    {
        if ( Collision(&tireur.pos,&bonus.pos) == 1) // si collision
        {
            tireur.alive = 2;                                       // on l'explose
            tireur.temps_explosion= SDL_GetTicks();                 // mise a jour du debut de l'explosion
            bonus.vie_supp = 2;
            bonus.temps_explosion = SDL_GetTicks();
            score[1].vie +=1;                          // on retire des points le joueur s'est fait touché par un enemie
        } // if
    } // if
    if ((tireur.alive == 1) && (bonus.super_tir_enemie == 1)) // on verifie qu'ils sont en vie et actif
    {
        if ( Collision(&tireur.pos,&bonus.pos) == 1) // si collision
        {
            tireur.alive = 2;                                       // on l'explose
            tireur.temps_explosion= SDL_GetTicks();                 // mise a jour du debut de l'explosion
            bonus.super_tir_enemie = 2;
            bonus.temps_explosion = SDL_GetTicks();
        } // if
    } // if
    if ((tireur.alive == 1) && (bonus.super_tir_cote == 1)) // on verifie qu'ils sont en vie et actif
    {
        if ( Collision(&tireur.pos,&bonus.pos) == 1) // si collision
        {
            tireur.alive = 2;                                       // on l'explose
            tireur.temps_explosion= SDL_GetTicks();                 // mise a jour du debut de l'explosion
            bonus.super_tir_cote = 2;
            bonus.temps_explosion = SDL_GetTicks();
        } // if
    } // if

    if ((tireur.alive == 1) && (bonus.super_tir == 1)) // on verifie qu'ils sont en vie et actif
    {
        if ( Collision(&tireur.pos,&bonus.pos) == 1) // si collision
        {
            tireur.alive = 2;                                       // on l'explose
            tireur.temps_explosion= SDL_GetTicks();                 // mise a jour du debut de l'explosion
            bonus.super_tir = 2;
            bonus.temps_explosion = SDL_GetTicks();
        } // if
    } // if

    if ((tireur.alive == 1) && (bonus.bad_luck == 1)) // on verifie qu'ils sont en vie et actif
    {
        if ( Collision(&tireur.pos,&bonus.pos) == 1) // si collision
        {
            tireur.alive = 2;                                       // on l'explose
            tireur.temps_explosion= SDL_GetTicks();                 // mise a jour du debut de l'explosion
            bonus.bad_luck = 2;
            bonus.temps_explosion = SDL_GetTicks();
            score[1].fail =1;                          // on retire des points le joueur s'est fait touché par un enemie
        } // if
    } // if

    // on parcours le tableau
    for (ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
    {
        if( (tir[ind_tir].actif == 1) && (tireur.alive == 1))   // on verifie qu'ils sont en vie et actif
        {
            if ( Collision(&tir[ind_tir].pos,&tireur.pos) == 1) // si collision
            {
                tir[ind_tir].actif = 2;                         // on l'explose
                tir[ind_tir].temps_explosion = SDL_GetTicks();  // mise a jour du debut de l'explosion
                tireur.alive = 2;                               // on l'explose
                score[1].point_inter -= 10;                     // on retire des points le joueur s'est fait touché par un tir enemie
                score[1].vie -=1;
                tireur.temps_explosion = SDL_GetTicks();        // mise a jour du debut de l'explosion
            } // if
        } // if

        } // for tir enemie vs tireur
} //collision()

//---------------------------------------------------------
//
// FONCTION D'AFFICHAGE DES MISSILES ET EXPLOSION
//
//---------------------------------------------------------


void blit_missile(SDL_Surface *ecran,int theme)
{
    int ind_mis;
    int tempsActuel;

    for (ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
    {
        SDL_Rect pos_explosion;
        switch (missile[ind_mis].actif)
            {
            case 1 :    // si le missile est actif est en vie
                SDL_BlitSurface(Themes[theme].img_missile, NULL, ecran, &missile[ind_mis].pos); // On l'affiche
                break;
            case 2 :    // si le missile est actif est touché
                pos_explosion.x = (2*missile[ind_mis].pos.x + Themes[theme].img_missile->w - Themes[theme].img_missile_mort->w)/2;
                pos_explosion.y = (2*missile[ind_mis].pos.y + Themes[theme].img_missile->h - Themes[theme].img_missile_mort->h)/2;
                SDL_BlitSurface(Themes[theme].img_missile_mort, NULL, ecran, &pos_explosion);  // On affiche une explosion a l'endroit de la collision
                Themes[theme].pos_explosion_m = pos_explosion;
                tempsActuel = SDL_GetTicks();
                if (tempsActuel - missile[ind_mis].temps_explosion >= 150)  // le temps de l'explosion est dépassé on le désactive
                    missile[ind_mis].actif = 0;
                break;
            } // switch
    } // for
} // blit_enemie()

//---------------------------------------------------------
//
// FONCTION D'AFFICHAGE DES TIRS ENEMIES ET EXPLOSION
//
//---------------------------------------------------------

void blit_tir_enemie(SDL_Surface *ecran,int theme)
{
    int ind_tir;
    int tempsActuel;

    for (ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
    {
        SDL_Rect pos_explosion;
        switch (tir[ind_tir].actif)
            {
            case 1 : // si le tir enemie est en vie
                SDL_BlitSurface(Themes[theme].img_tir_enemie, NULL, ecran, &tir[ind_tir].pos); // On l'affiche
                break;
            case 2 :
                pos_explosion.x = (2*tir[ind_tir].pos.x + Themes[theme].img_tir_enemie->w - Themes[theme].img_tir_enemie_mort->w)/2;
                pos_explosion.y = (2*tir[ind_tir].pos.y + Themes[theme].img_tir_enemie->h - Themes[theme].img_tir_enemie_mort->h)/2;
                SDL_BlitSurface(Themes[theme].img_tir_enemie_mort, NULL, ecran, &pos_explosion); // On affiche une explosion a l'endroit de la collision
                Themes[theme].pos_explosion_t = pos_explosion;
                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tir[ind_tir].temps_explosion >= 150)  // le temps de l'explosion est dépassé on le désactive
                    tir[ind_tir].actif = 0;
                break;
            } // switch
    } // for
} // blit_tir_enemie()

//---------------------------------------------------------
//
// FONCTION D'AFFICHAGE DES ENEMIES ET ENEMIES MORTS
//
//---------------------------------------------------------

void blit_enemie(SDL_Surface *ecran,int theme)
{
    int tempsActuel;
    int ind_enemie;

    for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
    {
        switch (enemie[ind_enemie].alive)
        {
        case 1 :    // si l'enemie est en vie
            SDL_BlitSurface(Themes[theme].img_enemie, NULL, ecran, &enemie[ind_enemie].pos); // On l'affiche
            break;
        case 2 :    // si l'enemie est touché
            SDL_BlitSurface(Themes[theme].img_enemie_mort, NULL, ecran, &enemie[ind_enemie].pos); // on affiche l'enemie mort
            Themes[theme].pos_explosion_e = enemie[ind_enemie].pos;
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - enemie[ind_enemie].temps_explosion >= 150)    // le temps de l'explosion est dépassé on le désactive
                enemie[ind_enemie].alive = 0;
            break;
        } // switch
    } // for
} // blit_enemie()

//---------------------------------------------------------
//
// FONCTION D'AFFICHAGE DU TIREUR ET TIREUR MORT
//
//---------------------------------------------------------

void blit_tireur(SDL_Surface *ecran,int theme)
{
    int tempsActuel;

    switch (tireur.alive)
    {
    case 1 :    // si l'enemie est en vie
        SDL_BlitSurface(Themes[theme].img_tireur, NULL, ecran, &tireur.pos); // On l'affiche
        break;
    case 2 :    // si l'enemie est en touché
        SDL_BlitSurface(Themes[theme].img_tireur_mort, NULL, ecran, &tireur.pos);   // on affiche le tireur mort
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tireur.temps_explosion >= 150)    // le temps de l'explosion est dépassé on le réactive
            tireur.alive = 1;
        break;
    } // switch

} // blit_enemie()
