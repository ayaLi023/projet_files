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
    x=f->tete->info;
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
            printf("La valeur %d a été trouvée dans la file.\n", val);
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
    file f ;
    initfile(&f);
srand(time(NULL));// initialiser
    for (int i = 0; i < 10; i++) {
        // enfiler une  valeur aleatoire 
if (rand)
        int x = rand() % 100;  // Valeur aléatoire
        enfiler(&f, x);
    }

    int valRecherchee;
    printf("Entrez la valeur que vous souhaitez rechercher dans la file : ");
    scanf("%d", &valRecherchee);

    chercherValeur(&f, valRecherchee);

    // Libérer la mémoire utilisée par la file
    noeud *tmp = f.tete;
    while (tmp != NULL) {
        noeud *suiv = tmp->suiv;
        free(tmp);
        tmp = suiv;
    }

    return 0;
}