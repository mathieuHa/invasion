/* Projet Invasion 2014 ISN     (score.c)

             auteur :          role :
             HANOTAUX MATHIEU : le coeur du programme
             DLW BENJAMIN    : la musique
             ANNOCQUE COME   : les images, les thèmes
             LORENTZ CHARLES : le site web
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
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
extern int          sens_enemie;
extern Logo         logo;
extern Menu         menu;
extern Menu_Option  menu_option;
extern Score        score[MAX_SCORE];

//---------------------------------------------------
//
// FONCTION LECTURE DU FICHIER SCORE
//
//---------------------------------------------------

void lire_fichier_score()
{
    FILE* fscore = NULL;

    fscore = fopen(FICHIER_SCORE, "r"); // ouverture du fichier en lecture

    if (fscore != NULL)                 // si le fichier est bien ouvert
    {
        int i = 0;
        int j;
        int continuer = 3;

        while ((continuer == 3) && (i <= MAX_SCORE))    // on attend 3 entrées
        {
            // on lit les informations du fichier et on les copie dans les tableaux
            continuer = fscanf(fscore,"%s %d %d",score[i].nom,&(score[i].score),&(score[i].r_atio));

            if (continuer == 3)
                i++;
        } // while

        for (j=i; j<MAX_SCORE; j++)     // si le nombre d'information est différents de 3 on copie
        {                               // AAA pour le nom et 0 0 dans les tableau respectifs
            strcpy(score[j].nom,"AAA");
            score[j].score  = 0;
            score[j].r_atio = 0;
        }

        fclose(fscore); // On ferme le fichier qui a été ouvert
    } // if
} // lire_fichier_score()

//---------------------------------------------------
//
// FONCTION ECRITURE DU FICHIER SCORE
//
//---------------------------------------------------

void ecrire_fichier_score()
{
    FILE* fscore = NULL;

    fscore = fopen(FICHIER_SCORE, "w"); // ouverture du fichier en lecture

    if (fscore != NULL)                 // si le fichier est bien ouvert
    {
        int i;

        for (i=0; i <MAX_SCORE;i++)     // on lit les informations des tableaux et on les ecrit dans le fichier
        {
            fprintf(fscore,"%s %d %d\n",
                   score[i].nom,
                   score[i].score,
                   score[i].r_atio);
        }
        fclose(fscore); // On ferme le fichier qui a été ouvert
    } // if
} // ecrire_fichier_score()

//---------------------------------------------------
//
// FONCTION RECHERCHE DU RANG SCORE ACTUELLE
//
//---------------------------------------------------


int rang_score(int scor)
{
    int rang = 0;       // compare le rang du dernier score avec le tableau de score
    while ((rang < MAX_SCORE) && (scor <= score[rang].score))
    {
        rang++;
    }
    return rang;        // et retourne le rang fixé
} // rang_score()

//------------------------------------------------------------
//
// FONCTION INSERTION DU NOUVEAU SCORE EN FONCTION DE SON RANG
//
//------------------------------------------------------------

void inserer_score(int rang,char *nom,int scor,int r_atio)
{
    if (rang <= MAX_SCORE) // on decale le bas du tableau
    {
        int i;

        for (i=MAX_SCORE; i>rang; i--)  // on va du bas vers le haut du tableau (MAX_SCORE a 0)
        {
            strcpy(score[i].nom,score[i-1].nom);    // on décale les informations du rang i au rang i-1
            score[i].score = score[i-1].score;
            score[i].r_atio = score[i-1].r_atio;
        } // for
        strcpy(score[rang].nom,nom);                // et arrivé a rang on remplace avec le dernier score obtenu
        score[rang].score = scor;
        score[rang].r_atio = r_atio;
    } // if
} // inserer_score()

//--------------------------------------------
//
// FONCTION AFFICHAGE DES SCORES DU TABLEAU
//
//---------------------------------------------

void afficher_score(SDL_Surface *ecran,char *nom_joueur,int scor,int r_atio,int rang)
{
    SDL_Event event;
    SDL_Surface *texte = NULL;      // surface de texte
    TTF_Font *police = NULL;
    SDL_Color couleurBleu    = {53, 255, 255};   // choix des différentes couleur avec RGB
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Color couleurRouge   = {255, 0 , 0};
    SDL_Color couleurVert    = {128,255,128};
    SDL_Color couleurViolet  = {255,128,255};
    SDL_Color couleur;
    SDL_Rect pos_text;
    char ch[500] ;           // chaine de caractère permettant de stocker les noms ou les nombre ratio, score
    int choix = 1;
    int i;

    police = TTF_OpenFont("comic.ttf", 40); // chargement de la police comic dans police

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // on efface l'ecran affiche le logo réefface l'ecran
    logo_afficher(ecran);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // écriture des entetes des colonnes
    pos_text.y = 25;
    texte = TTF_RenderText_Blended(police,"NOM ", couleurBleu); // colonne NOM
    pos_text.x = MAX_X / 4 - 50;
    SDL_BlitSurface(texte, NULL, ecran, &pos_text);             // on ecrit texte a l'écran
    texte = TTF_RenderText_Blended(police,"SCORE ", couleurBleu);// colonne SCORE
    pos_text.x = MAX_X / 2 - 50;
    SDL_BlitSurface(texte, NULL, ecran, &pos_text);
    texte = TTF_RenderText_Blended(police,"RATIO ", couleurBleu);// colonne RATIO
    pos_text.x = 3 * (MAX_X / 4) - 50 ;
    SDL_BlitSurface(texte, NULL, ecran, &pos_text);


    lire_fichier_score();           // on lit le fichier score pour pouvoir ecrire les valeurs entrées dans le tableau a l'écran

    for (i=0;i<MAX_SCORE;i++)       // fonction a affiche optimisé pour MAX_SCORE E [ 10 ; 15 ]
    {
        /*on s'occupe ici du nom*/
        // si c'est le rang max couleur violet sinon couleur rouge
        if (i == rang) couleur = couleurViolet; else couleur = couleurRouge;
        sprintf(ch, "%s", score[i].nom);                            // on copie le nom du tableau score dans la chaine "ch"
        texte = TTF_RenderText_Blended(police, ch, couleur);        // on rentre ch dans la surface texte
        pos_text.x = MAX_X / 4 - 50 ;                               // on positionne les noms en colonnes
        pos_text.y = i * ((MAX_Y - 100) / (MAX_SCORE + 1)) + 100;   // on positionne les noms équitablement répartie en fonction du nombre de lignes (MAX_SCORE)
        SDL_BlitSurface(texte, NULL, ecran, &pos_text);             // on ecrit texte a l'écran (le nom)

        /*on s'occupe ici du score*/ // même fonctionnement que précisé au dessus pour la suite
        if (i == rang) couleur = couleurViolet; else couleur = couleurVert;
        sprintf(ch, "%d", score[i].score);
        texte = TTF_RenderText_Blended(police, ch, couleur);
        pos_text.x = MAX_X / 2 - 50 ;
        SDL_BlitSurface(texte, NULL, ecran, &pos_text);

        /*on s'occupe ici du ratio*/
        if (i == rang) couleur = couleurViolet; else couleur = couleurBlanche;
        sprintf(ch, "%d", score[i].r_atio);
        texte = TTF_RenderText_Blended(police, ch, couleur);
        pos_text.x = 3 * (MAX_X / 4) - 50 ;
        SDL_BlitSurface(texte, NULL, ecran, &pos_text);
    }

    /* Si le joueur a fait un score qui ne rentre pas dans le top 10 on affiche quand même
    mais seulement en fin de partie et de couleur violet pour différencier des autres scores*/

    if ((nom_joueur != NULL) && (rang >= MAX_SCORE))
    {
        sprintf(ch, "%s", nom_joueur);
        texte = TTF_RenderText_Blended(police, ch, couleurViolet);
        pos_text.x = MAX_X / 4 - 50 ;
        pos_text.y = MAX_SCORE * ((MAX_Y - 100) / (MAX_SCORE + 1)) + 100;
        SDL_BlitSurface(texte, NULL, ecran, &pos_text);

        sprintf(ch, "%d", scor);
        texte = TTF_RenderText_Blended(police, ch, couleurViolet);
        pos_text.x = MAX_X / 2 - 50 ;
        SDL_BlitSurface(texte, NULL, ecran, &pos_text);

        sprintf(ch, "%d", r_atio);
        texte = TTF_RenderText_Blended(police, ch, couleurViolet);
        pos_text.x = 3 * (MAX_X / 4) - 50 ;
        SDL_BlitSurface(texte, NULL, ecran, &pos_text);
    }


    SDL_Flip(ecran); // mise a jour de l'ecran



    while (choix)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:  // veux quitter le programme
                choix = 0;  // on sort de la page score
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // veut quitter les scores
                        choix = 0;
                        break;
                    case SDLK_KP0: //  veut quitter les scores
                        choix = 0;
                        break;
                    default:
                        break;
                } // switch
                    default:
                        break;
                break;
        } // switch

    } // while

    logo_afficher(ecran);   // on affiche le logo avant de quitter les scores

    if (texte != NULL)
        SDL_FreeSurface(texte); // on supprime la surface crée
    TTF_CloseFont(police); // on efface la police
}

//-----------------------------------------------------
//
// FONCTION DEMANDER LE NOM AU JOUEUR EN FIN DE PARTIE
//
//-----------------------------------------------------

void demander_nom(SDL_Surface *ecran,char *nom_joueur)
{
    SDL_Event event;
    SDL_Surface *texte = NULL;  // création des surfaces texte chargement des polices
    SDL_Surface *lol   = NULL;
    TTF_Font *police   = NULL;
    SDL_Color couleurBlanche = {255, 255, 255}; // choix des couleurs
    SDL_Color couleurRouge   = {255, 0 , 0};
    SDL_Rect pos_text;
    SDL_Rect pos_lol;
    char car;
    int choix = 1;
    int i;

    police = TTF_OpenFont("comic.ttf", 40);

    // on efface l'ecran affiche le logo réefface l'ecran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    logo_afficher(ecran);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    texte = TTF_RenderText_Blended(police,"entrer votre nom : ", couleurRouge); // on demande au joueur d'entrer son nom
    pos_text.x = MAX_X / 4 - 50 ;
    pos_text.y = MAX_Y / 2;
    pos_lol.x = pos_text.x + 350;   // centrage et alignement de entrer votre nom : et du nom entré
    pos_lol.y = pos_text.y;

    SDL_BlitSurface(texte, NULL, ecran, &pos_text);
    SDL_Flip(ecran);

    i = 0;
    nom_joueur[i] = '\0';   // le nom du joueur est initialisé au caractère NULL '\0'

    while (choix)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                choix = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut sortir du menu
                        if (nom_joueur[0] != '\0')  // on l'y autorise seulement si il a rentré au moins un caractère
                            choix = 0;
                        else
                            SDL_BlitSurface(texte, NULL, ecran, &pos_text); // sinon on lui réaffiche "entrer votre nom : "

                        break;
                    case SDLK_RETURN:               // quitter les scores une fois le nom entré
                        if (nom_joueur[0] != '\0')  // on l'y autorise seulement si il a rentré au moins un caractère
                            choix = 0;
                        else
                            SDL_BlitSurface(texte, NULL, ecran, &pos_text); // sinon on lui réaffiche "entrer votre nom : "

                        break;
                    case SDLK_BACKSPACE:    // autorise la correction avec la touche backspace
                        if (i > 0)          // on efface la dernière lettre
                        {                   // seulement si il y a deja un caractère d'écrit
                            i--;
                            nom_joueur[i] = '\0';   // on remplace par le caractère null
                            if (lol != NULL)
                                SDL_FreeSurface(lol);// on efface la dernière lettre
                            lol = TTF_RenderText_Blended(police,nom_joueur, couleurBlanche); // on réaffiche le tout
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_BlitSurface(texte, NULL, ecran, &pos_text);
                            SDL_BlitSurface(lol, NULL, ecran, &pos_lol);
                        }

                        break;
                    default:    // pour tout autre caractère entré
                        car = azerty(event.key.keysym.sym);     // on le test avec azerty() (qwerty en azerty)
                        if ((((car >= 'a') && (car <= 'z')) || (car == '_')) && (i < 12)) // on accepte seulement certain caractères
                        {
                            nom_joueur[i] = car;    // ajout du caractère
                            i++;
                            nom_joueur[i] = '\0';   // on initialise le prochain au caractère null
                            if (lol != NULL)
                                SDL_FreeSurface(lol);
                            lol = TTF_RenderText_Blended(police,nom_joueur, couleurBlanche);    // on réaffiche le tout
                            SDL_BlitSurface(lol, NULL, ecran, &pos_lol);
                        } //if ()
                        break;
                } // switch
                    default:
                        break;
                break;
        } // switch
        SDL_Flip(ecran); // met a jour l'écran
    } // while

    logo_afficher(ecran); // affiche le logo avant de quitter

    // on libère les surfaces crées
    if (lol != NULL)
        SDL_FreeSurface(lol);
    if (texte != NULL)
        SDL_FreeSurface(texte);
    TTF_CloseFont(police); // fermeture de la police
}

//-----------------------------------------------------
//
// FONCTION AFFICHAGE DU SCORE NIVEAU EN JEU
//
//-----------------------------------------------------

void afficher_score_interactif(SDL_Surface *ecran,int scor,int niveau,int vie)
{
    SDL_Surface *score = NULL;      // création des surfaces , choix des couleurs
    SDL_Surface *niv = NULL;
    SDL_Surface *vi = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Rect pos_score;
    SDL_Rect pos_niv;
    SDL_Rect pos_vi;
    char ch[500];

    police = TTF_OpenFont("comic.ttf", 40);

    /* même fonctionnement que pour les autres fonctions on récupère le score
    on le transforme en caractère on l'affiche a l'écran*/
    sprintf(ch, "%d", scor);
    score = TTF_RenderText_Blended(police, ch, couleurBlanche);
    pos_score.x = MAX_X_JEU + MAX_X_JEU / 20;   // dans la zone qui lui est réservé
    pos_score.y = MAX_Y / 2;
    SDL_BlitSurface(score, NULL, ecran, &pos_score);

    sprintf(ch, "%d", niveau);
    niv = TTF_RenderText_Blended(police, ch, couleurBlanche);
    pos_niv.x = MAX_X_JEU + MAX_X_JEU / 20;
    pos_niv.y =  4 * (MAX_Y / 5) ;
    SDL_BlitSurface(niv, NULL, ecran, &pos_niv);

    sprintf(ch, "%d", vie);
    vi = TTF_RenderText_Blended(police, ch, couleurBlanche);
    pos_vi.x = MAX_X_JEU + MAX_X_JEU / 20;
    pos_vi.y =    MAX_Y / 5 ;
    SDL_BlitSurface(vi, NULL, ecran, &pos_vi);

    // on libère les surfaces et on sort de la fonction
    if (score != NULL)
        SDL_FreeSurface(score);
    if (niv != NULL)
        SDL_FreeSurface(niv);
    if (vi != NULL)
        SDL_FreeSurface(vi);
    TTF_CloseFont(police);
}
