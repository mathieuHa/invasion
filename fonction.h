/* Projet Invasion 2014 ISN     (fonction.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les th�mes
             LORENTZ CHARLES : le site web
*/

//---------------------------------------------------
//
// DEFINITION DES PROTOTYPES
//
//---------------------------------------------------
#ifndef DEF_JEU
#define DEF_JEU

// fonctions utilitaires        dans(usefull.c)

void logo_afficher(SDL_Surface *);                           // fonction affichant le logo invasion 180ms
void menu_afficher(SDL_Surface *,SDL_Surface *img);                           // fonction affichant le menu selectionn� 180ms
char azerty(char);                                           // fonction transformant le qwerty en azerty
int Collision(SDL_Rect *,SDL_Rect *);                        // fonction controllant les collisions entres deux rectangles (utilis� dans collision)
void clipper_f(SDL_Surface *,SDL_Rect *,SDL_Rect *,SDL_Rect *,SDL_Surface *,SDL_Rect *,int);
void clipper_sc(SDL_Surface *,SDL_Rect *,SDL_Rect *,SDL_Rect *,SDL_Rect *,int);

//fonction pour le bonus

void move_bonus();
void blit_bonus(SDL_Surface *);

// fonctions de la souris

void coord_souris_0();
void init_rectangle_menu();
void init_rectangle_option();
int coli_souris_menu(int*,int*,int*,int*);
int coli_souris_option(int*,int*,int*,int*,int*,int*,int*,int*,int*,int*);

// fonctions d'animations       dans(animation.c)

void move_missile();                                         // fonction qui d�place le missile
void move_enemie(int,int);                                   // fonction qui d�place les enemies
void move_tir_enemie();                                      // fonction qui d�place les tirs enemies
void collision(int,int);                                     // fonction g�rant les collisions
void blit_missile(SDL_Surface *,int);                        // fonction affichant les missiles a l'�cran
void blit_tir_enemie(SDL_Surface *,int);                     // fonction affichant les tirs enemies a l'�cran
void blit_enemie(SDL_Surface *,int);                         // fonction affichant les enemies a l'�cran
void blit_tireur(SDL_Surface *,int);                         // fonction affichant le tireur a l'�cran

// fonctions de chargement du jeu   dans(chargement.c)

SDL_Surface *chargement_img(char *,int,int,int);             // fonction facilitant le chargement des images, g�re la transparance
int init_themes();                                           // charges les th�mes (toutes les images du jeu)
int init_menu();                                           // charges les menus (toutes les images du menu)
int init_bonus();
void init_niveaux();                                         // charges les niveaux (r�glages)
int init_jeu();                                              // appelle init_theme et init _niveau, charges d'autres images
void liberer_themes();                                       // lib�re toute les surfaces des th�mes d'un coup
void liberer_menu();                                         // lib�re toute les surfaces des menus d'un coup
void liberer_bonus();

// fonction principale, elle g�re une partie    dans(jeu.c)

int jouer(SDL_Surface *,int,int,int *,int *,int *,int *);

// fonction animation en d�but de partie

void anim_early_game(SDL_Surface *,int,int);

// fonctions permettant au joueur de choisir ses options (niveau,themes)   dans(option.c)

void option(SDL_Surface *,int *,int *);

// fonctions g�rant le score    dans(score.c)

void lire_fichier_score();                                      // lis le fichier score l'enregistre dans le tableau score
void ecrire_fichier_score();                                    // copie le tableau score dans le fichier score
int rang_score(int);                                            // cherche le rang du score a ajouter
void inserer_score(int,char *,int,int);                         // modifie le tableau ajoute un score si dans top 10
void afficher_score(SDL_Surface *,char *,int,int,int);          // affiche le tableau de score en fin de partie
void demander_nom(SDL_Surface *,char *);                        // demande le nom � l'utilisateur en fin de partie
void afficher_score_interactif(SDL_Surface *,int,int,int);          // affiche le score et le niveau pendant une partie



#endif
