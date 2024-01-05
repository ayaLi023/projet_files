#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// definition de la structure d`un noeud 
typedef struct noeud {
    int info ;
    struct noeud* suiv ;
}noeud ;
// definition d`une structure pour la file 
typedef struct file {
    noeud* tete ;
    noeud* queue ;
}file;
// initialisation  d`une file vide 
file initfile (){
    file f ;
    f.tete=NULL;
    f.queue=NULL;
    return f ;
}
// fonction pour verifier si la file est vide 
int filevide (file f ){
    return f.tete==NULL && f.queue==NULL ;
}
// fonction pour consulter la valeur en tete de file 
int tetefile (file f){
return f.tete ->info;
}
// fonction pour enfiler un element dans la file 
void enfiler ( file *f , int x ){
    // creation d`un nouveau noeud 
    noeud* tmp = malloc (sizeof(noeud));
    tmp->info = x;
    tmp->suiv=NULL;
    // cas ou la file est vide 
    if (filevide(*f)==1)
    {
        f->tete=tmp;
        f->queue=tmp;
    }
    else  // ajouter a la fin  de file 
    {
        f->queue->suiv=tmp;
        f->queue=tmp;
    }
}
//fonction pour difeler la file 
void defiler ( file* f ,int x ){
    noeud *tmp ;
    // recuperer la valeur en tete de file 
6    x=f->tete->info;
    tmp=f->tete;
    if (f->tete==f->queue)
    {
        f->tete=NULL;
        f->queue=NULL;
    }
    else {
        // supression de noeud en tete 
        f->tete=f->tete->suiv;
    }
    // liberation de la memoire du noeud de tete 
    free(tmp);
}
int chercherValeur(file *f, int val) {
    noeud *tmp = f->tete;
    int pos=1;
    while (tmp != NULL) {
        if (tmp->info == val) {
            printf("La valeur %d a ete trouvee dans la file.\n", val);
            return pos ;  // La valeur a été trouvée
        }
        tmp =tmp->suiv;
        pos++;
    } 
    return -1;// la valeur n'existe pas 
    }
    // afficher la file 
    void affichfile(file*f){
        noeud*tmp=f->tete;
        while (tmp!=NULL){
            printf ("%d",tmp->info);
            tmp=tmp->suiv;// indique la fin de file 
        }
        printf ("\n");
    }
int main() {
    file f=initfile();

    srand(time(NULL)); 
int i ;
    for (i = 0; i < 10; i++) {
        // Enfiler une valeur aléatoire
        if (rand() % 2 == 0) {
            int val,val2,val3 = rand() % 10+ 1;
            enfiler(&f,val);
            enfiler (&f,val2);
             enfiler (&f,val3);
            printf("Enfiler : %d %d %d \n",val,val2,val3);
        }

        // Défiler aléatoirement
        if (rand() % 2 == 0) {
            int val = rand() % 10+ 1;
            defiler(&f,val);
            printf("defiler\n");
        }

        // Rechercher une valeur specifique saisie par l'utilisateur 
        int valeur ;
        printf (" entrer la valeur rechercher ");
        scanf ("%d",&valeur);
        if(chercherValeur(&f,valeur)==1)
        { 
            printf ("la valeur %d a ete trouver .\n",valeur);
        }
        else {
            printf (" la valeur %d na pas ete trouver .\n",valeur);
        }

        

        // Afficher la file après chaque opération
        affichfile(&f);
        printf("\n");
    }

    // Libérer la mémoire occupée par la file à la fin du programme
    noeud* tmp = f.tete;

    while (tmp != NULL) {
       noeud* suiv = tmp->suiv;
        free(tmp);
        tmp= suiv ;
    }

    return 0;
}
