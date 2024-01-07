#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"

// definition de la structure d`un noeud 
typedef struct noeud {
    int donnee;
    struct noeud* suiv ;//pointeur vers le noeud suiv dans la file
}noeud ;
// definition d`une structure pour la file 
typedef struct File {
    noeud* tete ;// Pointeur vers le premier élément de la file
    noeud* queue ;// Pointeur vers le dernier élément de la file
    int tailleMax;//la taille maximale de la file 
     Vector2 tetePosition; // Position de la tête
    Vector2 queuePosition; // Position de la queue
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
    file->tetePosition = (Vector2){0,0};
    file->queuePosition = (Vector2){0, 0};
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
// fonction pour enfiler/ajouter  un element a la file 
void enfiler ( File *file , int donnee){
   if (file->queue == NULL) 
   {// Si la file est vide
        file->tete = file->queue = creerNoeud(donnee);
         file->tetePosition = (Vector2){200, 200}; // Mettez à jour la position de la tête
        file->queuePosition = (Vector2){200, 200}; // Mettez à jour la position de la queue
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
         // Mettre à jour la position de la queue
        int startX = 200;
        int espacement = 42;
        noeud* temp = file->tete;
        while (temp != NULL) {
            startX += espacement;
            temp = temp->suiv;
        }
        file->queuePosition = (Vector2){startX, 200}; // Mettez à jour la position de la queue
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
 // Mettre à jour la position de la queue
    int startX = 200;
    int espacement = 42;
    noeud* tempQueue = file->tete;
    while (tempQueue != NULL) {
        startX += espacement;
        tempQueue = tempQueue->suiv;
    }
    file->queuePosition = (Vector2){startX, 200}; // Mettez à jour la position de la queue
    // Si la file devient vide, mettre à jour le pointeur de l'arrière
    if (file->tete == NULL) {
        file->queue = NULL;
         file->tetePosition = (Vector2){0,0}; // Mettez à jour la position de la tête
    }
}
// Fonction pour rechercher une valeur dans la file et retourner sa position
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
    int startX = 200;
    int startY = 200;
    int espacement = 42;

    noeud* actuel = file->tete;

    while (actuel != NULL) {
           if (actuel->donnee == valeurRecherchee && actuel == file->tete) {
            // dessiner un cadre rouge autour de la valeur recherchee
            DrawRectangle(startX - 5, startY - 5, 50, 50, RED);
        }
        DrawRectangle(startX, startY, 40, 40, PURPLE);
        DrawText(TextFormat("%d", actuel->donnee), startX + 20, startY + 20, 8, BLACK);

        startX += espacement;
        actuel = actuel->suiv;
    }
    
    // Dessiner une flèche verticale à la tête de la file
    if (file->tete != NULL) {
        // Dessiner la tige de la flèche
        DrawLine(file->tetePosition.x, file->tetePosition.y, file->tetePosition.x - 40, file->tetePosition.y, BLACK);

        // Dessiner la pointe de la flèche
        DrawTriangleLines((Vector2){file->tetePosition.x - 10, file->tetePosition.y - 4.5},
                          (Vector2){file->tetePosition.x - 10, file->tetePosition.y + 4.5},
                          (Vector2){file->tetePosition.x + 2, file->tetePosition.y}, BLACK);

        // Dessiner un cadre autour du texte "Tête"
        DrawRectangle(file->tetePosition.x - 95, file->tetePosition.y - 25, 60, 40, SKYBLUE);
        // Afficher le texte "Tête"
        DrawText("Tête", file->tetePosition.x - 95, file->tetePosition.y - 15, 20, BLACK);
    }
     // Dessiner une flèche verticale à la queue de la file
    if (file->queue != NULL) {
        // Dessiner la tige de la flèche
        DrawLine(file->queuePosition.x, file->queuePosition.y, file->queuePosition.x + 50, file->queuePosition.y, BLACK);

        // Dessiner la pointe de la flèche
        DrawTriangleLines((Vector2){file->queuePosition.x + 10, file->queuePosition.y - 4.5},
                          (Vector2){file->queuePosition.x + 10, file->queuePosition.y + 4.5},
                          (Vector2){file->queuePosition.x - 2, file->queuePosition.y}, BLACK);

        // Dessiner un cadre autour du texte "Queue"
        DrawRectangle(file->queuePosition.x, file->queuePosition.y - 45, 60, 40, LIGHTGRAY);
        // Afficher le texte "Queue"
        DrawText("Queue", file->queuePosition.x, file->queuePosition.y -39, 20, BLACK);
    }
}


int main() {
    const int largeurEcran = 800;
    const int hauteurEcran = 600;

    InitWindow(largeurEcran, hauteurEcran, "VISUALISATION- DE FILE AVEC RAYLIB");

    // Taille maximale de la file
    int tailleMax = 10;
    File* file = FileVide(tailleMax);

    SetTargetFPS(3);
     while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Enfiler et défiler
        enfiler(file, GetRandomValue(0, 20));
        if (GetRandomValue(0, 20) < 15) {
            defiler(file);
          int valeurRecherchee = GetRandomValue(0, 20);
            chercherValeur(file, valeurRecherchee);
            // Dessiner la file avec mise en surbrillance de la valeur recherchee
            dessinerFile(file, valeurRecherchee);
        } else {
            // Dessiner la file sans mise en surbrillance
            dessinerFile(file, -1);
        }
        // Afficher la taille de la file
        DrawText(TextFormat("Taille de la file: %d", CountNodes(file)), 12, 12, 20, BLACK);
DrawText("La valeur recherchée égale a un élément de la File sera encadrée", 20, 70, 20, GRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
