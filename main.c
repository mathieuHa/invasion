/* Projet Invasion 2014 ISN     (main.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/


//---------------------------------------------------
//
// FONCTION PRINCIPALE DU PROGRAMME
//
//---------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "main.h"
#include "fonction.h"

// les structures sont déclarés ici

Theme        Themes[4];
Niveau       Niveaux[5];

Tireur       tireur;
Missile      missile[MAX_MISSILES];
Tir          tir[MAX_MISSILES];
Enemie       enemie[MAX_ENEMIE];
int          sens_enemie;
Logo         logo;
Menu         menu;
Menu_Option  menu_option;
Score        score[MAX_SCORE];
Rectangle_menu rectangle_menu;
Rectangle_option rectangle_option;

int main(int argc, char *argv[])
{
    // declaration des variables surfaces, et autres et initialisation de l'évenement

    SDL_Surface *ecran = NULL;
    SDL_Event event;
    int continuer = 1;
    int scor;
    int vie;
    int r_atio;
    int nb_tues;
    int nb_tires;
    int rang;
    int niveau = 0;
    int theme  = 0;
    char nom_joueur[100];
    int musicon = 2;
    int case_jouer,case_option,case_quitter,case_score;

    // aide au traitement des erreurs affichage console + fenetre

    freopen("CON","w",stdout);
    freopen("CON","r",stdin);
    freopen("CON","w",stderr);

    //initalisation de la sdl chargement de l'écran

    SDL_Init(SDL_INIT_VIDEO);
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        SDL_Quit();       // Fermeture de l'API SDL
        exit(EXIT_FAILURE);
    }
     // Initialisation de l'API mixer chargement des music

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        TTF_Quit();       // Fermeture de l'API SDL_ttf
        SDL_Quit();       // Fermeture de l'API SDL
        printf("%s", Mix_GetError());
    }

    Mix_Music *musique;                     //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS("music/musique.mp3");   //Chargement de la musique
    //Mix_PlayMusic(musique, -1);             //Jouer infiniment la musique

    SDL_WM_SetIcon(chargement_img("img/menu/cb.bmp",0,0,0), NULL); // chargement de l'icone du jeu

    // chargement de l'écran
    ecran = SDL_SetVideoMode(MAX_X,MAX_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);  // On tente d'ouvrir une fenêtre a ajouter pour plein ecran| SDL_FULLSCREEN
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        Mix_CloseAudio(); // Fermeture de l'API SDL_mixer
        TTF_Quit();       // Fermeture de l'API SDL_ttf
        SDL_Quit();       // Fermeture de l'API SDL
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("INVASION", NULL); // titre

    // On initialise le jeu en vérifiant qu'il n'y ait pas de problème sinon on libère les surfaces fermes les API et on quitte

    if (init_jeu() != 0)
    {
        liberer_menu();
        liberer_themes();
        liberer_bonus();
        Mix_CloseAudio(); // Fermeture de l'API SDL_mixer
        TTF_Quit();       // Fermeture de l'API SDL_ttf
        SDL_Quit();       // Fermeture de l'API SDL

        fprintf(stderr, "Impossible d'initialiser le jeu\n");
        exit(EXIT_FAILURE);
    }

    init_rectangle_menu();

    // animation qui affiche le logo 180 ms avant d'entrer dans le menu
    logo_afficher(ecran);

    // boucle principale du menu
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                rectangle_menu.Coord_souris.x = event.button.x;
                rectangle_menu.Coord_souris.y = event.button.y;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // quitte le menu
                        case_quitter = 1;
                        break;

                    case SDLK_0:
                        case_quitter = 1;

                    case SDLK_KP1: // demande à jouer
                        case_jouer = 1;
                        break;

                    case SDLK_KP2:                      // demande a régler les option
                        case_option = 1;
                        break;

                    case SDLK_KP3:                      // demande a voir les top 10 scores
                        case_score = 1;
                    default:
                        break;
                }
                break;
        }


        if (coli_souris_menu(&case_jouer,&case_score,&case_quitter,&case_option) == 1);
        {
            if (case_jouer == 1)
            {
                musicon = 0;
                vie = Niveaux[niveau].vie;
                menu_afficher(ecran,menu.img_jouer); // illumine le bouton jouer du menu
                scor = 0;       // le score est initialisé a 0 au debut de la partie, ainsi que nb_tues et nb tiré
                nb_tues = 0;    // ainsi que nb_tues et nb tiré pour calculer le ratio
                nb_tires = 0;
                // lancement de la partie
                while (jouer(ecran,niveau,theme,&scor,&nb_tues,&nb_tires,&vie) == 1)
                {
                    vie = Niveaux[niveau].vie;
                    if ((niveau < 4) && (score[1].fail==0)) // incrémentaion des niveaux
                    {
                        niveau++;
                        vie = Niveaux[niveau].vie;
                    }
                }
                // fin de la partie on calcul le ratio
                if (nb_tires != 0)
                    r_atio = 100 * ((float)nb_tues / (float)nb_tires);
                else
                    r_atio = 0;
                niveau = 0;                                         // on remet le niveau a 0 pour la prochaine partie
                lire_fichier_score();                               // on ouvre le fichier des scores le copie dans le tableau score
                rang = rang_score(scor);                            // on cherche le rang du score de la partie du score
                demander_nom(ecran,nom_joueur);                     // on demande le nom du joueur quelqu'en soit le score
                inserer_score(rang,nom_joueur,scor,r_atio);         // on insère le score de la partie si le score a un rang <= 10
                ecrire_fichier_score();                             // on copie finalement le tableau dans le fichier score
                afficher_score(ecran,nom_joueur,scor,r_atio,rang);  // on affiche au joueur son score, ainsi que le top 10 score
                musicon = 2;
                case_jouer = 0;
            }

            if (case_option == 1)
            {
                clic_menu_option(ecran,&theme,&niveau,&case_option);
                case_option =0;
            }
            if (case_score == 1)
            {
                clic_menu_score(ecran,&theme,&niveau,&case_score);
                case_score = 0;
            }
            if (case_quitter == 1)
            {
                clic_menu_quitter(ecran,&theme,&niveau);
                continuer = 0;
            }
        } // if




        if ( musicon == 2)
        {
            musicon = 1;
            Mix_PlayMusic(musique, -1);             //Jouer infiniment la musique
        }
        // Effacement de l'écran affichage du menu mise a jour de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu.img, NULL, ecran, &menu.pos);
        SDL_Flip(ecran);
    }

    // animation qui affiche le logo 180 ms avant de quitter
    logo_afficher(ecran);

    // on libère les surfaces avant de quitter
    liberer_themes();
    liberer_menu();
    liberer_bonus();
    Mix_FreeMusic(musique);     //Libération de la musique

    Mix_CloseAudio(); // Fermeture de l'API SDL_mixer
    TTF_Quit();       // Fermeture de l'API SDL_ttf
    SDL_Quit();       // Fermeture de l'API SDL
    return EXIT_SUCCESS * 0;
}


