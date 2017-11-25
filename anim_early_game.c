/* Projet Invasion 2014 ISN    (jeu.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/

//---------------------------------------------------
//
// FONCTION JEU
//
//---------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // bibliothèque de l'aléa rand()
#include <SDL/SDL.h>
#include "main.h"
#include "fonction.h"
#include <SDL/SDL_mixer.h>

// on rappelle que les structures sont bien déclarer ailleurs
extern Theme        Themes[4];
extern Niveau       Niveaux[5];
extern Tireur       tireur;
extern Missile      missile[MAX_MISSILES];
extern Tir          tir[MAX_MISSILES];
extern Enemie       enemie[MAX_ENEMIE];
extern int          sens_enemie;
extern Logo         logo;
Bonus        bonus;
extern Menu         menu;
extern Menu_Option  menu_option;
extern Score        score[MAX_SCORE];

void anim_early_game(SDL_Surface *ecran,int niveau,int theme)
{
    SDL_Rect pos_fond,pos_fond_c,clipper;
    int ind_enemie;
    int ncol, nlig;
    int lx1,lx2,ly;
    double R;
    double Rx;
    double Ry;
    double dR;
    double dRx,dRy;
    double dt;
    double t;
    int nb_deplacements;
    double d_angle_enemies;
    double d_angle_rotation;
    double angle;
    int tempsPrecedent;
    int nombre_enemie_niveau;
    int ligne, colonne;
    double Tab_angle[MAX_ENEMIE];
    SDL_Rect Tab_pos_cercle[MAX_ENEMIE];
    SDL_Rect Tab_pos_fin[MAX_ENEMIE];
    int Tab_Vx[MAX_ENEMIE];
    int Tab_Vy[MAX_ENEMIE];

    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond_c.x = 0;
    pos_fond_c.y = 0;

    sens_enemie = 1;
    ncol = Niveaux[niveau].ncol_enemie;  // nombre de colonnes d'enemies
    nlig = Niveaux[niveau].nlig_enemie;  // nombre de lignes d'enemies
    lx1 = ((MAX_X_JEU - ( ncol * Themes[theme].img_enemie->w )) / (ncol + 1));                // calcul de la distance entre les enemies sur une ligne impaire
    lx2 = (MAX_X_JEU - (lx1 * (ncol - 2)) - ((ncol - 1) * Themes[theme].img_enemie->w)) / 2;  // calcul de la distance entre les enemies sur une ligne paire
    ly  = (1 * MAX_Y / 2 - (nlig - 1) * Themes[theme].img_enemie->h) / nlig;                  // calcul de la distance entre les enemies sur une colonne
    nombre_enemie_niveau = ncol * nlig - (nlig / 2);
    ind_enemie = 0;

    for (ligne = 1 ; ligne <= nlig ; ligne++) // on parcourt les lignes
    {
        if ( (ligne % 2) == 1 ) // on est sur un ligne impaire
        {
            for (colonne = 1 ; colonne <= ncol ; colonne ++) // on parcourt les colonnes
            {
                enemie[ind_enemie].pos.x = lx1 * colonne + ( colonne - 1 ) * Themes[theme].img_enemie->w; // on positionne le prochain enemie en x
                enemie[ind_enemie].pos.y = (ly * ligne) + (Themes[theme].img_enemie->h * (ligne - 1));    // on positionne le prochain enemie en y
                enemie[ind_enemie].alive = 1; // on met les enemies en vie
                ind_enemie++; // on passe a l'enemie suivant
            } // for
        } // if
        else                     // on est sur un ligne paire
        {
            for (colonne = 1 ; colonne <= ncol - 1 ; colonne ++) // on parcourt les colonnes
            {
                enemie[ind_enemie].pos.x = lx2 + ( colonne - 1 ) * (Themes[theme].img_enemie->w + lx1); // on positionne le prochain enemie en x
                enemie[ind_enemie].pos.y = (ly * ligne) + (Themes[theme].img_enemie->h * (ligne - 1));  // on positionne le prochain enemie en y
                enemie[ind_enemie].alive = 1; // on met les enemies en vie
                ind_enemie++;
            } // for
        } // else
    } // for

    for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
    {
        Tab_pos_fin[ind_enemie].x = enemie[ind_enemie].pos.x;
        Tab_pos_fin[ind_enemie].y = enemie[ind_enemie].pos.y;
        enemie[ind_enemie].oldpos.x = enemie[ind_enemie].pos.x;
        enemie[ind_enemie].oldpos.y = enemie[ind_enemie].pos.y;
    }

    tempsPrecedent = SDL_GetTicks();// on capture le temps precedant (initialisation)

    logo_afficher(ecran);

    SDL_BlitSurface(Themes[theme].fond, NULL, ecran, &pos_fond); // on blit une première fois le fond
    SDL_Flip(ecran);

    R = 200;
    Rx = 200;
    Ry = 200;
    dR = 2;
    dRx = 4;
    dRy = 2;
    d_angle_enemies = (2.0*M_PI) / (double)nombre_enemie_niveau;

    d_angle_rotation = (2.0*M_PI) / (double)360;

    for(ind_enemie=0,angle=0.0;ind_enemie<nombre_enemie_niveau;ind_enemie++,angle+=d_angle_enemies)
    {
        if(nombre_enemie_niveau<=10)
            Tab_angle[ind_enemie] = angle;
        else if (nombre_enemie_niveau<=20)
            Tab_angle[ind_enemie] = 2*angle;
        else if (nombre_enemie_niveau<=40)
            Tab_angle[ind_enemie] = 3*angle;
        else if (nombre_enemie_niveau<=58)
            Tab_angle[ind_enemie] = 4*angle;
        else
            Tab_angle[ind_enemie] = 5*angle;
    }

        for(nb_deplacements=0;nb_deplacements<360;nb_deplacements++)
        {
            for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
            {
                clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_enemie,&enemie[ind_enemie].oldpos,theme);
            }
            SDL_SetClipRect(ecran,NULL); // Enlever le clipper

            tempsPrecedent = SDL_GetTicks();// on capture le temps precedant (initialisation)
            if (nb_deplacements % 2)
            {
                R += dR;
                if (R > 200) dR = -dR; else if (R < 50) dR = -dR;
                Rx += dRx;
                if (Rx > 200) dRx = -dRx; else if (Rx < 50) dRx = -dRx;
                Ry += dRy;
                if (Ry > 200) dRy = -dRy; else if (Ry < 50) dRy = -dRy;
            }
            if(nombre_enemie_niveau<=10)
            {
                for(ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 2 + R * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 2 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
            }
            else if (nombre_enemie_niveau <= 20)
            {
                for(ind_enemie=0;ind_enemie<(nombre_enemie_niveau/2);ind_enemie++)
                {
                enemie[ind_enemie].pos.x =  MAX_X_JEU / 3 + R * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 2 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=nombre_enemie_niveau/2;ind_enemie<nombre_enemie_niveau;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = 2 * MAX_X_JEU / 3 + R * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 2 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
            }
            else if (nombre_enemie_niveau <= 40)
            {
                for(ind_enemie=0;ind_enemie<(nombre_enemie_niveau/3);ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 3 + R * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 3 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=nombre_enemie_niveau/3;ind_enemie<2*nombre_enemie_niveau/3;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = 2 * MAX_X_JEU / 3 + R * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 3 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=2*nombre_enemie_niveau/3;ind_enemie<nombre_enemie_niveau;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 2 + R * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = 2 * MAX_Y / 3 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
            }
            else if (nombre_enemie_niveau <= 58)
            {
                for(ind_enemie=0;ind_enemie<(nombre_enemie_niveau/4);ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 4 + R * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 4 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=nombre_enemie_niveau/4;ind_enemie<nombre_enemie_niveau/2;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = 3 * MAX_X_JEU / 4 + R *cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 4 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=nombre_enemie_niveau/2;ind_enemie<3*nombre_enemie_niveau/4;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 4 + R *cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = 3 * MAX_Y / 4 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=3*nombre_enemie_niveau/4;ind_enemie<nombre_enemie_niveau;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = 3 * MAX_X_JEU / 4 + R *cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = 3 * MAX_Y / 4 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
            }
            else
            {
                for(ind_enemie=0;ind_enemie<(nombre_enemie_niveau/5);ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 4 + Rx * cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 4 + Ry * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=nombre_enemie_niveau/5;ind_enemie<2*nombre_enemie_niveau/5;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = 3 * MAX_X_JEU / 4 + Ry *cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 4 + Rx * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=2*nombre_enemie_niveau/5;ind_enemie<3*nombre_enemie_niveau/5;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 4 + Ry *cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = 3 * MAX_Y / 4 + Rx * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=3*nombre_enemie_niveau/5;ind_enemie<4*nombre_enemie_niveau/5;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = 3 * MAX_X_JEU / 4 + Rx *cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = 3 * MAX_Y / 4 + Ry * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
                for(ind_enemie=4*nombre_enemie_niveau/5;ind_enemie<nombre_enemie_niveau;ind_enemie++)
                {
                enemie[ind_enemie].pos.x = MAX_X_JEU / 2 + R *cos(Tab_angle[ind_enemie]);
                enemie[ind_enemie].pos.y = MAX_Y / 2 + R * sin(Tab_angle[ind_enemie]);
                Tab_angle[ind_enemie] += d_angle_rotation;
                }
            }
            blit_enemie(ecran,theme);
            for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
            {
                enemie[ind_enemie].oldpos.x = enemie[ind_enemie].pos.x;
                enemie[ind_enemie].oldpos.y = enemie[ind_enemie].pos.y;
            }
            SDL_Flip(ecran); // on met a jour l'ecran

            while(SDL_GetTicks() - tempsPrecedent < 8); /* Si 500 ms se sont écoulées */
            tempsPrecedent = SDL_GetTicks(); /* Le temps "actuel" devient le temps "precedent" */
        }

    for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
    {
        Tab_pos_cercle[ind_enemie].x = enemie[ind_enemie].pos.x;
        Tab_pos_cercle[ind_enemie].y = enemie[ind_enemie].pos.y;
    }

    // calcul des vecteurs
    for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
    {
        Tab_Vx[ind_enemie] = Tab_pos_fin[ind_enemie].x - Tab_pos_cercle[ind_enemie].x;
        Tab_Vy[ind_enemie] = Tab_pos_fin[ind_enemie].y - Tab_pos_cercle[ind_enemie].y;
    }

    dt = 0.01;

    for(t=dt;t<1;t+=dt)
    {
        for(ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
        {
            enemie[ind_enemie].pos.x = Tab_pos_cercle[ind_enemie].x + t * Tab_Vx[ind_enemie];
            enemie[ind_enemie].pos.y = Tab_pos_cercle[ind_enemie].y + t * Tab_Vy[ind_enemie];
        }
            for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
            {
                clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_enemie,&enemie[ind_enemie].oldpos,theme);
            }
            SDL_SetClipRect(ecran,NULL); // Enlever le clipper
            blit_enemie(ecran,theme);
            for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
            {
                enemie[ind_enemie].oldpos.x = enemie[ind_enemie].pos.x;
                enemie[ind_enemie].oldpos.y = enemie[ind_enemie].pos.y;
            }
            SDL_Flip(ecran); // on met a jour l'ecran
            while(SDL_GetTicks() - tempsPrecedent < 4); /* Si 500 ms se sont écoulées */
            tempsPrecedent = SDL_GetTicks(); /* Le temps "actuel" devient le temps "precedent" */
    }

    for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
    {
        enemie[ind_enemie].pos.x = Tab_pos_fin[ind_enemie].x;
        enemie[ind_enemie].pos.y = Tab_pos_fin[ind_enemie].y;
    }

}

