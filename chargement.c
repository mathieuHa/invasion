/* Projet Invasion 2014 ISN     (chargement.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/

//---------------------------------------------------
//
// FONCTIONS D'INITIALISATION
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

//---------------------------------------------------
//
// FONCTION DE CHARGEMENT D'UNE IMAGE
//
//---------------------------------------------------

SDL_Surface *chargement_img(char* nom_img,int r,int g,int b) // prend en paramètre le nom de l'image et la transparance a lui donner
{
    SDL_Surface* img;

    img = SDL_LoadBMP(nom_img); // chargement de l'image (nom_img)
    if (img == NULL)
    {
        fprintf(stderr, "Impossible de charger l'image '%s' : %s\n", nom_img,SDL_GetError());
        return NULL;
    }
    else
    {
        SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format, r, g, b)); // on applique la transparence
        return img;                                                              // on retourne l'image chargé
    }
} // chargement_img()

//---------------------------------------------------
//
// FONCTION D'INITIALISATION DES THEMES
//
//---------------------------------------------------

int init_themes()
{
    // on initialise tout les images des themes a NULL

    int ind_theme;

    for (ind_theme = 0 ; ind_theme < 4 ; ind_theme ++)
    {
        Themes[ind_theme].fond                  = NULL;
        Themes[ind_theme].img_tireur            = NULL;
        Themes[ind_theme].img_tireur_mort       = NULL;
        Themes[ind_theme].img_enemie            = NULL;
        Themes[ind_theme].img_enemie_mort       = NULL;
        Themes[ind_theme].img_missile           = NULL;
        Themes[ind_theme].img_tir_enemie        = NULL;
        Themes[ind_theme].img_tir_enemie_mort   = NULL;
        Themes[ind_theme].img_missile_mort      = NULL;
    }

    // on charge les images des thèmes dans les surfaces

    // Theme 0

    if ( (Themes[0].fond = chargement_img("img/theme_1/fond.bmp",255,255,255))  == NULL) // chargement d'une image du theme avec chargement_img()
        return -1;                                                                       // on verifie quelle est bien chargé sinon on retourne une erreur
    if ( (Themes[0].img_tireur = chargement_img("img/theme_1/tireur.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[0].img_tireur_mort = chargement_img("img/theme_1/tireur_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[0].img_enemie = chargement_img("img/theme_1/enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[0].img_enemie_mort = chargement_img("img/theme_1/enemie_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[0].img_missile = chargement_img("img/theme_1/missile.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[0].img_tir_enemie = chargement_img("img/theme_1/tir_enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[0].img_missile_mort = chargement_img("img/theme_1/explosion.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[0].img_tir_enemie_mort = chargement_img("img/theme_1/explosion.bmp",255,255,255))  == NULL)
        return -1;

    // Theme 1

    if ( (Themes[1].fond = chargement_img("img/theme_2/fond.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_tireur = chargement_img("img/theme_2/tireur.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_tireur_mort = chargement_img("img/theme_2/tireur_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_enemie = chargement_img("img/theme_2/enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_enemie_mort = chargement_img("img/theme_2/enemie_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_missile = chargement_img("img/theme_2/missile.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_tir_enemie = chargement_img("img/theme_2/tir_enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_missile_mort = chargement_img("img/theme_2/explosion.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[1].img_tir_enemie_mort = chargement_img("img/theme_2/explosion.bmp",255,255,255))  == NULL)
        return -1;

    // Theme 3

    if ( (Themes[2].fond = chargement_img("img/theme_3/fond.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[2].img_tireur = chargement_img("img/theme_3/tireur.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[2].img_tireur_mort = chargement_img("img/theme_3/tireur_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[2].img_enemie = chargement_img("img/theme_3/enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[2].img_enemie_mort = chargement_img("img/theme_3/enemie_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[2].img_missile = chargement_img("img/theme_3/missile.bmp",0,0,0))  == NULL)
        return -1;
    if ( (Themes[2].img_tir_enemie = chargement_img("img/theme_3/tir_enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[2].img_missile_mort = chargement_img("img/theme_3/explosion.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[2].img_tir_enemie_mort = chargement_img("img/theme_3/explosion.bmp",255,255,255))  == NULL)
        return -1;

    // Theme 4

    if ( (Themes[3].fond = chargement_img("img/theme_4/fond.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_tireur = chargement_img("img/theme_4/tireur.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_tireur_mort = chargement_img("img/theme_4/tireur_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_enemie = chargement_img("img/theme_4/enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_enemie_mort = chargement_img("img/theme_4/enemie_mort.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_missile = chargement_img("img/theme_4/missile.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_tir_enemie = chargement_img("img/theme_4/tir_enemie.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_missile_mort = chargement_img("img/theme_4/explosion.bmp",255,255,255))  == NULL)
        return -1;
    if ( (Themes[3].img_tir_enemie_mort = chargement_img("img/theme_4/explosion.bmp",255,255,255))  == NULL)
        return -1;

        return 0;

} // init_themes()

//---------------------------------------------------
//
// FONCTION D'INITIALISATION DES MENUS
//
//---------------------------------------------------

int init_menu()
{
    // on initialise tout les surfaces de menu a NULL et le logo

    menu.img                    = NULL;
    menu.img_jouer              = NULL;
    menu.img_niveau0            = NULL;
    menu.img_niveau1            = NULL;
    menu.img_niveau2            = NULL;
    menu.img_niveau3            = NULL;
    menu.img_niveau4            = NULL;
    menu.img_options            = NULL;
    menu.img_option_quitter     = NULL;
    menu.img_quitter            = NULL;
    menu.img_score              = NULL;
    menu.img_theme1             = NULL;
    menu.img_theme2             = NULL;
    menu.img_theme3             = NULL;
    menu.img_theme4             = NULL;

    /*les différentes images du menu servent a indiquer a l'utilisateur quel paramètre il entre*/
    if ( (menu.img = chargement_img("img/menu/menu.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_score = chargement_img("img/menu/menu_score.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_options = chargement_img("img/menu/menu_options.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_quitter = chargement_img("img/menu/menu_quitter.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_jouer = chargement_img("img/menu/menu_jouer.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_option_quitter = chargement_img("img/menu/menu_option_quitter.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_niveau0 = chargement_img("img/menu/menu_niveau1.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_niveau1 = chargement_img("img/menu/menu_niveau2.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_niveau2 = chargement_img("img/menu/menu_niveau3.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_niveau3 = chargement_img("img/menu/menu_niveau4.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_niveau4 = chargement_img("img/menu/menu_niveau5.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_theme1 = chargement_img("img/menu/menu_theme1.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_theme2 = chargement_img("img/menu/menu_theme2.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_theme3 = chargement_img("img/menu/menu_theme3.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu.img_theme4 = chargement_img("img/menu/menu_theme4.bmp",255,255,255)) == NULL )
        return -1;
    if ( (menu_option.img = chargement_img("img/menu/menu_option.bmp",20,20,20)) == NULL )
        return -1;

    menu_option.pos.x = MAX_X / 2 - menu_option.img->w / 2;  // on centre le menu option quelque soit la resolution
    menu_option.pos.y = MAX_Y / 2 - menu_option.img->h / 2;  //

    return 0;

} // init_menu()

//---------------------------------------------------
//
// FONCTION D'INITIALISATION DES BONUS
//
//---------------------------------------------------

int init_bonus()
{
    logo.img                    = NULL;
    logo.game_over              = NULL;
    bonus.img_point_supp        = NULL;
    bonus.img_vie_supp          = NULL;
    bonus.img_bad_luck          = NULL;
    bonus.img_super_tir         = NULL;
    bonus.img_super_tir_enemie  = NULL;
    bonus.img_super_tir_cote    = NULL;

    // on charge les images des bonus dans les surfaces

    if ( (logo.img = chargement_img("img/bonus/logo.bmp",20,20,20)) == NULL )
        return -1;
    if ( (logo.game_over = chargement_img("img/bonus/game_over.bmp",20,20,20)) == NULL)
        return -1;
    if ( (bonus.img_point_supp = chargement_img("img/bonus/point_supp.bmp",20,20,20)) == NULL )
        return -1;
    if ( (bonus.img_vie_supp = chargement_img("img/bonus/vie_supp.bmp",20,20,20)) == NULL )
        return -1;
    if ( (bonus.img_bad_luck = chargement_img("img/bonus/bad_luck.bmp",20,20,20)) == NULL )
        return -1;
    if ( (bonus.img_super_tir = chargement_img("img/bonus/super_tir.bmp",20,20,20)) == NULL )
        return -1;
    if ( (bonus.img_super_tir_enemie = chargement_img("img/bonus/super_tir_enemie.bmp",20,20,20)) == NULL )
        return -1;
    if ( (bonus.img_super_tir_cote = chargement_img("img/bonus/super_tir_cote.bmp",20,20,20)) == NULL )
        return -1;

    return 0;
} // init_bonus()

//---------------------------------------------------
//
// FONCTION DE LIBERATION DES SURFACES DES THEMES
//
//---------------------------------------------------

void liberer_themes()
{
    int ind_theme;

    for (ind_theme = 0 ; ind_theme < 4 ; ind_theme ++)
    {
        if (Themes[ind_theme].fond != NULL)             // on verifie que l'image n'est pas NULL (de l'initialisation)
            SDL_FreeSurface(Themes[ind_theme].fond );   // on libère la surface

        if (Themes[ind_theme].img_tireur != NULL)
            SDL_FreeSurface(Themes[ind_theme].img_tireur );

        if (Themes[ind_theme].img_tireur_mort != NULL)
            SDL_FreeSurface(Themes[ind_theme].img_tireur_mort );

        if (Themes[ind_theme].img_enemie != NULL)
            SDL_FreeSurface(Themes[ind_theme].img_enemie );

        if (Themes[ind_theme].img_enemie_mort != NULL)
            SDL_FreeSurface(Themes[ind_theme].img_enemie_mort );

        if (Themes[ind_theme].img_missile != NULL)
            SDL_FreeSurface(Themes[ind_theme].img_missile );

        if (Themes[ind_theme].img_missile_mort != NULL)
            SDL_FreeSurface(Themes[ind_theme].img_missile_mort );

        if (Themes[ind_theme].img_tir_enemie != NULL)
            SDL_FreeSurface(Themes[ind_theme].img_tir_enemie );
    } // for

} // liberer_themes()

//---------------------------------------------------
//
// FONCTION DE LIBERATION DES SURFACES DES MENUS
//
//---------------------------------------------------

void liberer_menu()
{
    if (menu.img != NULL)
        SDL_FreeSurface(menu.img);
    if (menu_option.img != NULL)
        SDL_FreeSurface(menu_option.img);
    if (menu.img_score !=NULL)
        SDL_FreeSurface(menu.img_score);
    if (menu.img_quitter !=NULL)
        SDL_FreeSurface(menu.img_quitter);
    if (menu.img_option_quitter !=NULL)
        SDL_FreeSurface(menu.img_option_quitter);
    if (menu.img_options !=NULL)
        SDL_FreeSurface(menu.img_options);
    if (menu.img_niveau0 !=NULL)
        SDL_FreeSurface(menu.img_niveau0);
    if (menu.img_niveau1 !=NULL)
        SDL_FreeSurface(menu.img_niveau1);
    if (menu.img_niveau2 !=NULL)
        SDL_FreeSurface(menu.img_niveau2);
    if (menu.img_niveau3 !=NULL)
        SDL_FreeSurface(menu.img_niveau3);
    if (menu.img_niveau4 !=NULL)
        SDL_FreeSurface(menu.img_niveau4);
    if (menu.img_theme1 !=NULL)
        SDL_FreeSurface(menu.img_theme1);
    if (menu.img_theme2 !=NULL)
        SDL_FreeSurface(menu.img_theme2);
    if (menu.img_theme3 !=NULL)
        SDL_FreeSurface(menu.img_theme3);
    if (menu.img_theme4 !=NULL)
        SDL_FreeSurface(menu.img_theme4);

} // liberer_themes()

//---------------------------------------------------
//
// FONCTION DE LIBERATION DES SURFACES DES MENUS
//
//---------------------------------------------------

void liberer_bonus()
{
    if (logo.img != NULL)
        SDL_FreeSurface(logo.img);
    if (logo.game_over != NULL)
        SDL_FreeSurface(logo.game_over);

    if (bonus.img_bad_luck !=NULL)
        SDL_FreeSurface(bonus.img_bad_luck);
    if (bonus.img_point_supp !=NULL)
        SDL_FreeSurface(bonus.img_point_supp);
    if (bonus.img_vie_supp !=NULL)
        SDL_FreeSurface(bonus.img_vie_supp);
    if (bonus.img_super_tir !=NULL)
        SDL_FreeSurface(bonus.img_super_tir);
    if (bonus.img_super_tir_enemie !=NULL)
        SDL_FreeSurface(bonus.img_super_tir_enemie);
    if (bonus.img_super_tir_cote !=NULL)
        SDL_FreeSurface(bonus.img_super_tir_cote);

} // liberer_bonus()

//---------------------------------------------------
//
// FONCTION D'INITIALISATION DES NIVEAUX
//
//---------------------------------------------------

void init_niveaux()
{

    // Niveau 1

    Niveaux[0].dx_enemie   = 4;  // déplacement en x des enemies du niveau 0
    Niveaux[0].dy_enemie   = 3;  // déplacement en y des enemies du niveau 0
    Niveaux[0].ncol_enemie = 2;  // nombre de colonnes d'enemies au niveau 0
    Niveaux[0].nlig_enemie = 3;  // nombre de lignes d'enemies  au niveau 0
    Niveaux[0].vie         = 1;  // nombre de vies  au niveau 0

    // Niveau 2

    Niveaux[1].dx_enemie   = 5;
    Niveaux[1].dy_enemie   = 3;
    Niveaux[1].ncol_enemie = 5;
    Niveaux[1].nlig_enemie = 4;
    Niveaux[1].vie         = 1;

    // Niveau 3

    Niveaux[2].dx_enemie   = 6;
    Niveaux[2].dy_enemie   = 3;
    Niveaux[2].ncol_enemie = 7;
    Niveaux[2].nlig_enemie = 6;
    Niveaux[2].vie         = 2;

    // Niveau 4

    Niveaux[3].dx_enemie   = 5;
    Niveaux[3].dy_enemie   = 4;
    Niveaux[3].ncol_enemie = 8;
    Niveaux[3].nlig_enemie = 7;
    Niveaux[3].vie         = 3;

    // Niveau 5

    Niveaux[4].dx_enemie   = 5;
    Niveaux[4].dy_enemie   = 4;
    Niveaux[4].ncol_enemie = 9;
    Niveaux[4].nlig_enemie = 7;
    Niveaux[4].vie         = 4;

} // init_niveaux()

//---------------------------------------------------
//
// FONCTION D'INITIALISATION DU JEU
//
//---------------------------------------------------

int init_jeu()
{
    // on appelle les autres fonctions de chargements

    if (init_themes() != 0)
    {
        liberer_themes();
        return -1;
    }
    if (init_menu() != 0)
    {
        liberer_menu();
        return -1;
    }
    if (init_bonus() != 0)
    {
        liberer_bonus();
        return -1;
    }
    init_niveaux();
    return 0;

} // init_jeu()
