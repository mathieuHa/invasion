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

int jouer(SDL_Surface *ecran,int niveau,int theme,int *scor,int *nb_tues,int *nb_tires,int *vie)
{
    // declaration de variables
    SDL_Event event;
    SDL_Rect pos_fond,pos_fond_c,clipper,score_case,vie_case;
    int ind_mis, ind_enemie,ind_tir;
    int trouve;
    int tempsActuel,tempsPrecedent;
    int game = 1;
    int retour;
    int nombre_enemie_niveau;
    int nlig,ncol;
    int rang_tir_enemie;
    int nombre_tue_niveau = 0;
    int nombre_tire_niveau = 0;
    unsigned int checkTime = SDL_GetTicks(); // unsigned pour des nombres positifs
    const unsigned int fps = 60;
    int temps_avant_tir_enemie;
    int temps_apres_tir_enemie;
    int temps_avant_bonus;
    int temps_apres_bonus;
    int t_av_bs,t_ap_bs;
    int t_av,t_ap;
    int taaaa,tpppp;// noob nom a revoir ;)
    int delay_tir = 500;
    int delay_tir_enemie = 800;

    Mix_AllocateChannels(10); //Allouer 10 canaux

    Mix_Volume(1, MIX_MAX_VOLUME);//Mettre à mi-volume le post 1
    Mix_Volume(2, MIX_MAX_VOLUME);
    Mix_Volume(3, MIX_MAX_VOLUME);
    Mix_Volume(4, MIX_MAX_VOLUME);

    Mix_Music *Musique;//Créer un pointeur pour stocker un .mp3
    Mix_Chunk *TIRE;//Créer un pointeur pour stocker un .WAV
    Mix_Chunk *KILL;
    Mix_Chunk *Hit;

    switch(theme) //MUSIQUE
    {
        case 0: //THEME MARIO
        Musique = Mix_LoadMUS("music/mario.mp3"); //Chargement de la musique
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        Mix_PlayMusic(Musique, -1); //Jouer infiniment la musique

        TIRE = Mix_LoadWAV("music/mario_tir.wav"); //son tire
        KILL = Mix_LoadWAV("music/mario_ennemi_touche.wav"); //son KILL
        Hit = Mix_LoadWAV("music/HIT_mario.wav"); //son hit
        break;

        case 1: //THEME ZOMBIE
        Musique = Mix_LoadMUS("music/zombie_musique.mp3"); //Chargement de la musique
        Mix_VolumeMusic(MIX_MAX_VOLUME);
        Mix_PlayMusic(Musique, -1); //Jouer infiniment la musique

        TIRE = Mix_LoadWAV("music/zombie_tir.wav"); //son tire
        KILL = Mix_LoadWAV("music/zombie_ennemi_touche.wav"); //son KILL
        Hit = Mix_LoadWAV("music/HIT_zombie.wav"); //son hit
        break;

        case 2: //THEME RETRO
        Musique = Mix_LoadMUS("music/retro_musique.mp3"); //Chargement de la musique
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        Mix_PlayMusic(Musique, -1); //Jouer infiniment la musique

        TIRE = Mix_LoadWAV("music/retro_tir.wav"); //son tire
        KILL = Mix_LoadWAV("music/retro_ennemi_touche.wav"); //son KILL
        Hit = Mix_LoadWAV("music/HIT_retro.wav"); //son hit
        break;

        case 3: //THEME ZELDA
        Musique = Mix_LoadMUS("music/Zelda_music.mp3"); //Chargement de la musique
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        Mix_PlayMusic(Musique, -1); //Jouer infiniment la musique

        TIRE = Mix_LoadWAV("music/zelda_tir.wav"); //son tire
        KILL = Mix_LoadWAV("music/zelda_ennemi_touche.wav"); //son KILL
        Hit = Mix_LoadWAV("music/HIT_zelda.wav"); //son hit
        break;
    }


    // Initialisation du générateur de nombre aléatoires
    srand(time(NULL));

    // positionner le fond et le tireur

    pos_fond.x = 0;
    pos_fond.y = 0;
    tireur.pos.x = (MAX_X_JEU-Themes[theme].img_tireur->w)/2;  //position du tireur, de départ
    tireur.pos.y = MAX_Y-Themes[theme].img_tireur->h;
    tireur.oldpos.x = (MAX_X_JEU-Themes[theme].img_tireur->w)/2;  //position du tireur, de départ
    tireur.oldpos.y = MAX_Y-Themes[theme].img_tireur->h;
    tireur.alive = 1;

    score_case.x = MAX_X_JEU + MAX_X_JEU / 20;
    score_case.y = MAX_Y / 2;
    score_case.h = 50;
    score_case.w = 160; // taille pour score jusqua 9 999 999
    vie_case.x = MAX_X_JEU + MAX_X_JEU / 20;
    vie_case.y = MAX_Y / 5;
    vie_case.h = 50;    // hauteur pour l'ecriture de TTF
    vie_case.w = 50; // taille jusqua 99 vie

    // initialisation du missile

    for (ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
    {
        missile[ind_mis].pos.x = 0; // position des missiles au depart
        missile[ind_mis].pos.y = 0;
        missile[ind_mis].oldpos.x = 0; // position des missiles au depart
        missile[ind_mis].oldpos.y = 0;
        missile[ind_mis].actif = 0;// le missile est initialisé comme inactif
        missile[ind_mis].vitesse = 4;
        missile[ind_mis].vx = 0;
    }

    // initialisation du tir_enemie

    for (ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
    {
        tir[ind_tir].pos.x = 0; // position des tir au depart
        tir[ind_tir].pos.y = 0;
        tir[ind_tir].oldpos.x = 0; // position des tir au depart
        tir[ind_tir].oldpos.y = 0;
        tir[ind_tir].actif = 0;// le tir est initialisé comme inactif
        tir[ind_tir].vitesse = 3;
    }

    // initialisation de la position des enemies

    for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
    {
        enemie[ind_enemie].alive = 0; //  enemies sont initialisé comme mort
        enemie[ind_enemie].oldpos.x = enemie[ind_enemie].pos.x;
        enemie[ind_enemie].oldpos.y = enemie[ind_enemie].pos.y;
    }

    anim_early_game(ecran,niveau,theme);

    ncol = Niveaux[niveau].ncol_enemie;  // nombre de colonnes d'enemies
    nlig = Niveaux[niveau].nlig_enemie;  // nombre de lignes d'enemies
    nombre_enemie_niveau = ncol * nlig - (nlig / 2);

    SDL_EnableKeyRepeat(10,10);     // activation de la repétition des touches
    tempsActuel = SDL_GetTicks();   // on capture le temps actuel    (initialisation)
    tempsPrecedent = SDL_GetTicks();// on capture le temps precedant (initialisation)
    temps_apres_tir_enemie = SDL_GetTicks();   // on capture le temps apres_tir_enemie (initialisation)
    temps_avant_tir_enemie = SDL_GetTicks();// on capture le temps avant le tir enemie (initialisation)
    temps_apres_bonus = SDL_GetTicks();   // on capture le temps apres_tir_enemie (initialisation)
    temps_avant_bonus = SDL_GetTicks();// on capture le temps avant le tir enemie (initialisation)

    // initialisation des bonus
    bonus.actif = 10;
    bonus.bad_luck = 0;
    bonus.point_supp = 0;
    bonus.super_tir = 0;
    bonus.super_tir_enemie = 0;
    bonus.super_tir_cote = 0;
    bonus.vie_supp = 0;

    (*scor) = score[1].niveau;
    score[1].fail = 0;

    SDL_BlitSurface(Themes[theme].fond, NULL, ecran, &pos_fond); // on blit une première fois le fond(penser a enlever et blittter au dessus

    while (game) // boucle principale de la partie
    {
        // ajout des clippers
        /** chercher une optimisation l'element est il en vie doit on reafficher le fond juste pour lui
        ? pour afficher le background temps d'affichage des explosion ???*/

		for (ind_enemie=0;ind_enemie<nombre_enemie_niveau;ind_enemie++)
        {
            clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_enemie,&enemie[ind_enemie].oldpos,theme);
        }
		for (ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
        {
            clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_missile,&missile[ind_mis].oldpos,theme);
        }
        for (ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
        {
            clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_tir_enemie,&tir[ind_tir].oldpos,theme);
        }
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_tireur,&tireur.oldpos,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,bonus.img_super_tir_enemie,&bonus.oldpos,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,bonus.img_super_tir_cote,&bonus.oldpos,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,bonus.img_super_tir,&bonus.oldpos,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,bonus.img_bad_luck,&bonus.oldpos,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,bonus.img_vie_supp,&bonus.oldpos,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,bonus.img_point_supp,&bonus.oldpos,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_missile_mort,&Themes[theme].pos_explosion_m,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_missile_mort,&Themes[theme].pos_explosion_t,theme);
        clipper_f(ecran,&clipper,&pos_fond,&pos_fond_c,Themes[theme].img_missile_mort,&Themes[theme].pos_explosion_e,theme);
        clipper_sc(ecran,&clipper,&pos_fond,&pos_fond_c,&score_case,theme);
        clipper_sc(ecran,&clipper,&pos_fond,&pos_fond_c,&vie_case,theme);

		SDL_SetClipRect(ecran,NULL); // Enlever le clipper

        if (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:  // si on quitte le jeu
                    retour = 0;
                    game   = 0;
                    break;

                case SDL_KEYDOWN:

                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:   // si on quitte la partie
                            retour = 0;
                            game = 0;
                            break;

                        case SDLK_SPACE:   // appuie sur espace
                            tempsActuel = SDL_GetTicks();
                            if (tempsActuel - tempsPrecedent > delay_tir) /* Si 500 ms se sont écoulées */
                            {
                                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" */

                                // Recherche prochain missile inactif
                                ind_mis = 0;
                                trouve = 0;

                                while ((ind_mis < MAX_MISSILES) &&( trouve == 0))
                                {
                                    if (missile[ind_mis].actif == 0)
                                    {
                                     missile[ind_mis].pos.x = tireur.pos.x + Themes[theme].img_tireur->w / 2 - Themes[theme].img_missile->w / 2;
                                     missile[ind_mis].pos.y = tireur.pos.y;
                                     missile[ind_mis].actif = 1; // activation du missile
                                     trouve = 1;
                                     nombre_tire_niveau++;  // incrementation pour les stats (ratio)
                                    }
                                    ind_mis++;
                                }
                                Mix_PlayChannel(2, TIRE, 0);//Joue le son KILL sur le canal 3 ; le joue une fois (0 + 1)
                            }
                            break;

                        case SDLK_RIGHT: // Flèche droite
                            tireur.pos.x=tireur.pos.x+5;  // on déplace le tireur a droite
                            if (tireur.pos.x >= MAX_X_JEU-Themes[theme].img_tireur->w)
                            {
                                tireur.pos.x=MAX_X_JEU-Themes[theme].img_tireur->w; // on le bloque a droite
                            }
                            break;

                        case SDLK_LEFT: // Flèche gauche
                            tireur.pos.x=tireur.pos.x-5;  // on déplace le tireur a droite
                            if (tireur.pos.x <= 0)
                            {
                                tireur.pos.x=0 ; // on le bloque a gauche
                            }
                            break;

                        default:
                            break;
                        } // switch
                    break;
                default:
                    break;


            } // switch
        } // if Poll event

        score[1].point_inter = 0;   // variable intermédiaire permettant de compter les point a chaque boucle (remis a zero)
        score[1].nombre_tue_niv = 0;// variable intermédiaire permettant de compter les nombre enemies tué a chaque boucle (remis a zero)
        score[1].vie = 0;

        /* affichage des missiles */

        blit_missile(ecran,theme);

        for (ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++) // on actualise oldpos sur pos pour clipper le fond dessus
        {
            missile[ind_mis].oldpos.x = missile[ind_mis].pos.x;
            missile[ind_mis].oldpos.y = missile[ind_mis].pos.y;
        }

        /* affichage des tirs enemies */

        blit_tir_enemie(ecran,theme);

        for (ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
        {
            tir[ind_tir].oldpos.x = tir[ind_tir].pos.x;
            tir[ind_tir].oldpos.y = tir[ind_tir].pos.y;
        }

        /* affichage des enemies */

        blit_enemie(ecran,theme);

        for (ind_enemie=0;ind_enemie<MAX_ENEMIE;ind_enemie++)
        {
            enemie[ind_enemie].oldpos.x = enemie[ind_enemie].pos.x;
            enemie[ind_enemie].oldpos.y = enemie[ind_enemie].pos.y;
        }

        /* affichage du tireur */

        blit_tireur(ecran,theme);

        tireur.oldpos.x = tireur.pos.x;
        tireur.oldpos.y = tireur.pos.y;

        blit_bonus(ecran);

        bonus.oldpos.x = bonus.pos.x;
        bonus.oldpos.y = bonus.pos.y;

        /* affichage du score interactif */

        afficher_score_interactif(ecran,*scor,niveau,*vie);

        if(SDL_GetTicks() > (checkTime + 1000 / fps) ) // temporisation des déplacements.
        {
        /* deplacement des missiles */

        move_missile();

        move_enemie(niveau,theme);

        move_bonus();

        /* deplacement des tir enemies */

        move_tir_enemie();

        /* detection des collision */

        collision(theme,niveau);

        //fprintf(stderr,"vie = %d \n",*vie);
        (*scor) = (*scor) + score[1].point_inter; // le score est modifié
        nombre_tue_niveau = nombre_tue_niveau + score[1].nombre_tue_niv; // ainsi que le nombre d'enemie du niveau
        (*vie) = (*vie) + score[1].vie;


            checkTime = SDL_GetTicks();
                //SON COLISIONS//

            if((score[1].point_inter == 100) || (score[1].point_inter == 20) || (score[1].point_inter == -125))//joue son kill
            {
            Mix_PlayChannel(3, KILL, 0);//Joue le son KILL sur le canal 3 ; le joue une fois (0 + 1)
            }
            if(score[1].point_inter == -10  || (score[1].point_inter == -150))
            {
            Mix_PlayChannel(4, Hit, 0);//Joue le son HIT sur le canal 4 ; le joue une fois (0 + 1)
            }

        }

        /*** problème tempo entres bonus*/

        temps_avant_bonus = SDL_GetTicks();
        if (bonus.actif == 100)
        {
                bonus.actif = 10;
        }
        if(score[1].fail == 1)
        {
            retour = 1;
            game = 0;
        }
        t_av = SDL_GetTicks();
        if(bonus.super_tir_cote == 2)
        {
            t_ap = t_av;
            for(ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
            {
                delay_tir = 150;
                missile[ind_mis].vitesse = 8;
                if (ind_mis%2==0)
                missile[ind_mis].vx = 3;
                else
                missile[ind_mis].vx = -3;
            }

        }
        else if((bonus.super_tir_cote == 0)&& ((t_av-t_ap)>2000))
        {
            t_ap = t_av;
            for(ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
            {
                delay_tir = 500;
                missile[ind_mis].vitesse = 4;
                missile[ind_mis].vx = 0;
            }
        }
        t_av_bs = SDL_GetTicks();
        if(bonus.super_tir == 2)
        {
            t_ap_bs = t_av_bs;
            for(ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
            {
                delay_tir = 150;
                missile[ind_mis].vitesse = 8;
            }
        }
        else if((bonus.super_tir == 0)&& ((t_av_bs-t_ap_bs)>2000))
        {
            t_ap_bs = t_av_bs;
            for(ind_mis=0;ind_mis<MAX_MISSILES;ind_mis++)
            {
                delay_tir = 500;
                missile[ind_mis].vitesse = 4;
            }
        }
        taaaa = SDL_GetTicks();
        if(bonus.super_tir_enemie == 2)
        {
            tpppp = taaaa;
            for(ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
            {
                delay_tir_enemie = 100;
                tir[ind_tir].vitesse = 6;
            }
        }
        else if((bonus.super_tir_enemie == 0)&& ((taaaa-tpppp)>2000))
        {
            tpppp = taaaa;
            for(ind_tir=0;ind_tir<MAX_MISSILES;ind_tir++)
            {
                delay_tir_enemie = 800;
                tir[ind_tir].vitesse = 3;
            }
        }

        //préparation du tir enemie
        temps_avant_tir_enemie = SDL_GetTicks();

        if (temps_avant_tir_enemie - temps_apres_tir_enemie > delay_tir_enemie) // un tir toute les 800 ms
        {
            int compteur;


            temps_apres_tir_enemie = temps_avant_tir_enemie;

            // calcul de l'enemie qui va tirer
            // le rang de l'enemie qui va tirer est choisi aléatoirement parmis le nombre restant
            rang_tir_enemie = rand() % (nombre_enemie_niveau-nombre_tue_niveau);

            ind_enemie = 0;
            compteur = 0;

            // on cherche un enemie vivant
            while ((ind_enemie<nombre_enemie_niveau) && (compteur != (rang_tir_enemie +1)))
            {
                if (enemie[ind_enemie].alive == 1)
                    compteur++;

                ind_enemie++; // on est un cran trop loin
            }
            ind_enemie--;     // on est au bon cran


            // Recherche prochain tir inactif

            ind_tir = 0;
            trouve = 0;

            while ((ind_tir < MAX_MISSILES) &&( trouve == 0)) // meme fonction que pour les missiles
            {
                if (tir[ind_tir].actif == 0)
                {
                 tir[ind_tir].pos.x = enemie[ind_enemie].pos.x + Themes[theme].img_enemie->w / 2;
                 tir[ind_tir].pos.y = enemie[ind_enemie].pos.y + Themes[theme].img_enemie->h;
                 tir[ind_tir].actif = 1;
                 trouve = 1;
                }
                ind_tir++;
            }
        }


        SDL_Flip(ecran); // on met a jour l'ecran

        if ((*vie) == 0) // test du nombre de vie restant 0 = perdu
        {
            retour = 0;
            game = 0;
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
            SDL_BlitSurface(logo.game_over, NULL, ecran, &pos_fond);
            SDL_Flip(ecran);
            SDL_Delay(500);
        }
        if (nombre_enemie_niveau == nombre_tue_niveau)  // test pour savoir si on passe au niv suivant
        {
            retour = 1;
            game = 0;
            score[1].niveau = (*scor);
        }


    } // while

    (*nb_tues) += nombre_tue_niveau;    // calcul pour le ratio
    (*nb_tires) += nombre_tire_niveau;

    Mix_FreeMusic(Musique);     //Libération de la musique
    Mix_FreeChunk(TIRE);
    Mix_FreeChunk(KILL);
    Mix_FreeChunk(Hit);
    logo_afficher(ecran);
    SDL_EnableKeyRepeat(0,0);//desactivation de la repétition des touches

    return retour;
}


