/* Projet Invasion 2014 ISN     (main.h)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/

//---------------------------------------------------
//
// DEFINITION DES CONSTANTES ET VARIABLES GLOBALES
//
//---------------------------------------------------

#ifndef DEF_CONSTANTES // Pour éviter des inclusions infinies
#define DEF_CONSTANTES

// Taille de l'ecran

#define MAX_X_JEU   1024    // largeur réservé au jeu pour ne pas empiéter sur les score_intéractif MAX_X_JEU = 4 MAX_X / 5
#define MAX_X       1280    // largeur total de l'écran lors de l'ouverture de la fenêtre
#define MAX_Y       720     // hauteur total de l'écran lors de l'ouverture de la fenêtre

// nombre max de missiles et enemies

#define MAX_MISSILES 50     // nombre max de missiles pour le tableau
#define MAX_ENEMIE 200      // nombre max d'enemies pour le tableau

// nombre max de scores enregistrés

#define MAX_SCORE 10              // nombre de scores max
#define FICHIER_SCORE "score.txt"   // nom du fichier d'enregistrement des scores

//---------------------------------------------------
//
// DEFINITION DES STRUCTURES
//
//---------------------------------------------------

typedef struct Enemie Enemie;  // structure des Enemies qui comporte leur position, leur état (mort ou vivant),
struct Enemie                  // et le temps qu'ils explosent lors d'une collision
{
    SDL_Rect pos;
    SDL_Rect oldpos;
    int alive;
    int temps_explosion;
};

typedef struct Missile Missile;// structure des Missiles qui comporte leur position, leur état (mort ou vivant),
struct Missile                 // le temps qu'ils explosent lors d'une collision
{
    SDL_Rect pos;
    SDL_Rect oldpos;
    int actif;
    int temps_explosion;
    int vitesse;
    int vx;
};

typedef struct Tir Tir;         // structure des Tir (enemies) qui comporte leur position, leur état (mort ou vivant),
struct Tir                      // le temps qu'ils explosent lors d'une collision
{
    SDL_Rect pos;
    SDL_Rect oldpos;
    int actif;
    int temps_explosion;
    int vitesse;
};

typedef struct Bonus Bonus;         // structure des Tir (enemies) qui comporte leur position, leur état (mort ou vivant),
struct Bonus                      // le temps qu'ils explosent lors d'une collision
{
    SDL_Rect pos;
    SDL_Rect oldpos;
    int actif;
    SDL_Surface *img_point_supp;
    SDL_Surface *img_vie_supp;
    SDL_Surface *img_super_tir;
    SDL_Surface *img_super_tir_cote;
    SDL_Surface *img_super_tir_enemie;
    SDL_Surface *img_bad_luck;
    int temps_explosion;
    int vie_supp;
    int point_supp;
    int super_tir;
    int super_tir_cote;
    int bad_luck;
    int super_tir_enemie;
};

typedef struct Tireur Tireur;   // structure du Tireur qui comporte sa position,son état (mort ou vivant),
struct Tireur                   // le temps qu'il explose lors d'une collision
{
    SDL_Rect pos;
    SDL_Rect oldpos;
    int alive;
    int temps_explosion;
};

typedef struct Logo Logo;       // structure du Logo du jeu qui comporte sa position, et sa surface associée
struct Logo
{
    SDL_Rect pos;
    SDL_Surface *img;
    SDL_Surface *game_over;
};

typedef struct Menu Menu;       // structure du Menu du jeu qui comporte sa position, et sa surface associée et celles des images menu illuminé
struct Menu
{
    SDL_Rect pos;
    SDL_Surface *img;
    SDL_Surface *img_jouer;
    SDL_Surface *img_options;
    SDL_Surface *img_score;
    SDL_Surface *img_quitter;
    SDL_Surface *img_option_quitter;
    SDL_Surface *img_theme1;
    SDL_Surface *img_theme2;
    SDL_Surface *img_theme3;
    SDL_Surface *img_theme4;
    SDL_Surface *img_niveau0;
    SDL_Surface *img_niveau1;
    SDL_Surface *img_niveau2;
    SDL_Surface *img_niveau3;
    SDL_Surface *img_niveau4;
};

typedef struct Menu_Option Menu_Option; // structure du Menu des options du jeu qui comporte sa position, et ses surfaces associées
struct Menu_Option
{
    SDL_Rect pos;
    SDL_Surface *img;
};

typedef struct Rectangle_menu Rectangle_menu;
struct Rectangle_menu
{
    SDL_Rect Coord_souris;
    SDL_Rect rectangle_jouer,rectangle_quitter,rectangle_score,rectangle_option;
};

typedef struct Rectangle_option Rectangle_option;
struct Rectangle_option
{
    SDL_Rect Coord_souris;
    SDL_Rect rectangle_a,rectangle_b,rectangle_c,rectangle_d,rectangle_1,rectangle_2,rectangle_3,rectangle_4,rectangle_5,rectangle_quitter;

};

typedef struct Theme Theme;              // structure des Themes du jeu qui comporte les différentes surfaces de chaque thème
struct Theme
{
    SDL_Rect pos_explosion_t;
    SDL_Rect pos_explosion_m;
    SDL_Rect pos_explosion_e;
    SDL_Surface *fond;
    SDL_Surface *img_tireur;
    SDL_Surface *img_tireur_mort;
    SDL_Surface *img_enemie;
    SDL_Surface *img_enemie_mort;
    SDL_Surface *img_missile;
    SDL_Surface *img_tir_enemie;
    SDL_Surface *img_missile_mort;
    SDL_Surface *img_tir_enemie_mort;

};

typedef struct Niveau Niveau;  // structure des Niveaux du jeu qui comporte les différentes paramètres adapté à chaque difficulté
struct Niveau
{
    int dx_enemie;          // déplacement en x
    int dy_enemie;          // déplacement en y
    int ncol_enemie;        // nombre d'enemies par colonnes
    int nlig_enemie;        // nombre d'enemies par lignes
    int vie;
};

typedef struct Score Score;             // structure des Score du jeu qui comporte les différentes paramètres adapté à chaque difficulté
struct Score
{
    char *nom[20];                      // nom de l'utilisateur
    int point_inter;                    // pour incrémenter les scores dans jeu.c
    int score;                          // variable de score
    int r_atio;                         // variable de ratio
    int nombre_tue_niv;                 // nombre d'enemie tué au niveau (pour gérer le passage à un autre niveau des que tous sont tué)
    int vie;
    int niveau;
    int fail;
};

#endif
