#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"

// definition de la structure d`un noeud 
typedef struct noeud {
    int donnee;
    struct noeud* suiv ;
}noeud ;
// definition d`une structure pour la file 
typedef struct File {
    noeud* tete ;
    noeud* queue ;
    int tailleMax;//la taille maximale de la file 
}File;
// FONCTION POUR CREER UN NOUVEAU NOEUD 
noeud* creerNoeud(int donnee) {
    noeud* nouveauNoeud = (noeud*)malloc(sizeof(noeud));
    nouveauNoeud->donnee = donnee;
    nouveauNoeud->suiv = NULL;
    return nouveauNoeud;
}
// fonction pour creer une  file vide avec une taille max 
File* FileVide (int tailleMax ){
   File* file = (File*)malloc(sizeof(File));
    file->tete = file->queue = NULL;
    file->tailleMax = tailleMax;
    return file;
}
// initialisation  d`une file vide 
File initfile (int tailleMax){
    File file ;
    file.tete=NULL;
    file.queue=NULL;
    file.tailleMax=tailleMax;
    return file ;
}

// fonction pour consulter la valeur en tete de file 
int teteFile (File* file){
 if (file->tete != NULL) {
        return file->tete->donnee;
    } else {
       
        return -1; // file vide
    }
}
// fonction pour enfiler/ajouter  un element a la file 
void enfiler ( File *file , int donnee){
   if (file->queue == NULL) 
   {// Si la file est vide
        file->tete = file->queue = creerNoeud(donnee);
    } else
        if (file->tailleMax > 0 && file->tailleMax == CountNodes(file)) {
        // Si la file atteint sa taille maximale, retirer l'element en tete
        defiler(file);
        // Enfiler le nouveau nœud
        enfiler(file, donnee);
    } else {
        // Ajouter le nouveau nœud à la fin de la file
        file->queue->suiv = creerNoeud(donnee);
        file->queue = file->queue->suiv;
    }
}
//fonction pour difeler/supprimer un element de la file 
void defiler ( File* file ){
   if (file->tete == NULL) {
        // Si la file est vide
        return -1;
}
// Retirer le nœud de la file
    noeud* temp = file->tete;
    int donnee = temp->donnee;

    file->tete = temp->suiv;
    free(temp);

    // Si la file devient vide, mettre à jour le pointeur de l'arrière
    if (file->tete == NULL) {
        file->queue = NULL;
    }

    return donnee;
}

int chercherValeur(File *file, int valeur) {
    noeud *temp = file->tete;
    int pos=1;
    while (temp != NULL) {
        if (temp->donnee == valeur) {
            return pos ;  // La valeur a été trouvée
        }
        temp =temp->suiv;
        pos++;
    } 
    return -1;// la valeur n'existe pas 
    }
    // Fonction pour dessiner la file
void dessinerFile(File* file) {
    int startX = 100;
    int startY = 200;
    int espacement = 60;

    noeud* actuel = file->tete;

    while (actuel != NULL) {
        DrawRectangle(startX, startY, 40, 40, PURPLE);
        DrawText(TextFormat("%d", actuel->donnee), startX + 15, startY + 15, 10, BLACK);

        startX += espacement;
        actuel = actuel->suiv;
    }
}
// Fonction pour compter le nombre de nœuds dans la file
int CountNodes(File* file) {
    int count = 0;
    noeud* temp = file->tete;
    while (temp != NULL) {
        count++;
        temp = temp->suiv;
    }
    return count;
}

int main() {
    const int largeurEcran = 800;
    const int hauteurEcran = 600;

    InitWindow(largeurEcran, hauteurEcran, "VISUALISATION- DE FILE AVEC RAYLIB");

    // Taille maximale de la file
    int tailleMax = 5;
    File* file = FileVide(tailleMax);

    SetTargetFPS(8);
     while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Enfiler et défiler à des fins de démonstration
        enfiler(file, GetRandomValue(0, 20));
        if (GetRandomValue(0, 100) < 15) {
            defiler(file);
            chercherValeur(file, GetRandomValue(0, 5));
        }

        // Dessiner la file
        dessinerFile(file);

        // Afficher la taille de la file
        DrawText(TextFormat("Taille de la file: %d", CountNodes(file)), 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
