#include<stdio.h>
#include<stdlib.h>
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
int rechercherValeur(file f, int val) {
    noeud* tmp = f.tete;
    int pos = 0;

    while (tmp != NULL) {
        if (tmp->info == val) {
            return pos;
        }
        tmp = tmp->suiv;
        pos++;
    }

    return -1; // La valeur n'est pas trouvée
}
void afficherfile(file f){
    if (filevide(f)){
        printf("la file est vide \n ");
    }
    printf ("contenu de la file :\n");
    noeud* tmp=f.tete;
    while (tmp!=NULL){
        printf ("%d",tmp->info);
        tmp=tmp->suiv;
    }
    printf("\n");
}
int main() {
   file f= initfile();
 enfiler(&f,10);
    enfiler(&f, 20);
    enfiler(&f, 30);
    enfiler(&f,40);
enfiler(&f, 50);
    enfiler(&f,60);
  defiler(&f,20);
    defiler(&f,30);
      defiler(&f,40);
    defiler(&f,50);
afficherfile(f);
return 0;
}