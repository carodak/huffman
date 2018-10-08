/**
 * \file huffman.c
 * \author : Binome composé de Caroline Dakouré & Lyes Meghara
 * \teacher: Supervisé par Monsieur Pierre Pompidor
 * \date : 06/12/2015
 *
 * Programme de compression de fichiers en utilisant l'algorithme de Huffman.
 * Projet de licence 2 Informatique de HLIN303 (Systèmes et réseaux) de la faculté des sciences de Montpellier 2.
 */




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"


/**On déclare un tableau de floats globalement qui receuilli les fréquences */
float*freq;
int nbre_car_2; /** On le déclare en globale pour pouvoir afficher les stats à la fin */
unsigned int go;
float* frequences;
char buffer[5000];
/**
  On crée une fonction qui renvoie un tableau de fréquences
*/
float *calculFreq(char*fichier){
  /** fonction travaille par elle même (copie) */
   
  unsigned int z ;
  for(z=0; z<256; z++){
    frequences[z]=0.0;
  }
  FILE* F ;
  if ((F=fopen(fichier,"r"))!=NULL){
    unsigned int i, j ;
    unsigned int c ;
    char k;
    k=fgetc(F);
    i = 0 ;
    while ((c=fgetc(F))!=EOF){
      /*printf("'%c'",c) ;*/
      frequences[c]=frequences[c]+1;
      i++;
    }
    fclose(F) ;
    for (j=0 ; j<256 ; j++){
      frequences[j]=frequences[j]/i;
      if(frequences[j]==1.) {
	printf("\n\n");
	printf("===============Cas particulier !=============== \n\n");
	printf("Votre fichier source contient un seul char ! \n\n");
     
	printf("Nous sommes dans un cas particulier \n\nLe mieux en complexité est de ne pas passer par un arbre \n\n");


	printf("Votre fichier a été compressé sous le nom de Cas_Particulier_C \n\n");
	
	FILE* cas=fopen("Cas_Particulier_C","w+");
	fprintf(cas,"-%i %c",i,k);
	exit(1);
      }

    }
    return frequences ;
   

  }
  else{
    printf("Le fichier ne s'ouvre pas\n");
    exit(1);
  }
}

/**Cherche les 2 minimums de l'arbre */
int min(Noeud* B, int differentde){
  int minimum=-1; float fmin=1;
  unsigned int i=0;
  while (i<511){
    if (i==differentde){
      i++;
    }
    if (B[i].pere==-1 && B[i].f<fmin && B[i].f>0){
      fmin=B[i].f;
      minimum=i;
    }
    i++;
  }
  return minimum;
}

/**Construction de l'arbre binaire*/
void construct(Noeud* arbre, float* freq) {

  unsigned int racine=256;

  for (int i=0;i<511;i++){
    if (i < 256) {
      arbre[i].f=freq[i];
    }
    else {
      arbre[i].f = 0;
    }
    arbre[i].pere=-1;
    arbre[i].fg=-1;
    arbre[i].fd=-1;
  }
  int min1,min2;
  do{

    min1=min(arbre,-1);
    min2=min(arbre,min1);
    printf("Premier min = %i, second min = %i\n", min1, min2);  

    arbre[min1].pere=racine;
    arbre[min2].pere=racine;

    arbre[racine].fd=min1;
    arbre[racine].fg=min2;
    arbre[racine].f=arbre[min1].f+arbre[min2].f;

    racine++;
  }
  while(arbre[racine-1].f !=1);


}

void affiche(Noeud *arbre) {

  for (unsigned short int i=0; i < 511; i++) {
    if (arbre[i].f > 0. )
      printf("Indice .:: %i ::. Frequence : %f Pere=%i Fd=%i Fg=%i\n", i,  arbre[i].f, arbre[i].pere, arbre[i].fd, arbre[i].fg);

  }
}

/**On cherche la racine de l'arbre car elle a été précedemment trouvé dans une fonction pas dans le main*/
int getRacine(Noeud *arbre){
  unsigned short int j=511;

  while (arbre[j].f != 1.) {

    j--;

  }

  return j;
}

/**Code est le tableau qui va contenir le code binaire de chaque caractère*/ 

void parcours(unsigned short int indiceNoeud, char *code, Noeud*arbre,unsigned short int indiceTab)
{
  if(arbre[indiceNoeud].fg==-1)
    {
      //Quand on tombe sur le noeud final rajoute \0 au tableau code pour préciser qu'il n'y aura pas d'autres valeurs après
      code[indiceTab]='\0';
      strcpy(arbre[indiceNoeud].huff, code); //On copie le contenu de code dans l'arbre, plus précisement à l'indice du Noeud
    
      printf("Code de %c(%i)=%s\n",indiceNoeud,indiceNoeud,arbre[indiceNoeud].huff);
      
    }
  else
    {
      //Si il y a un fils, on parcourt récursivement l'arbre
      if(arbre[indiceNoeud].fg!=-1){ 
        code[indiceTab]='0'; //on rajoute le caractère 0 à code si on trouve un fg
        parcours(arbre[indiceNoeud].fg, code, arbre, indiceTab+1); //indiceTab est initialisé à 0 et me permet d'incrémenter l'indice du tableau code
      }
      if(arbre[indiceNoeud].fd!=-1){
	code[indiceTab]='1'; //on rajoute le caractère 1 à code si on trouve un fd
        parcours(arbre[indiceNoeud].fd, code, arbre, indiceTab+1);
      }
    }
 
}

int puissance(int a, int b){
  int prod=1;
  for (int i=0;i<b;i++){
    prod=prod*a;
  }
  return prod;
}

void createFichierCompresse(char* fichier,Noeud *arbre,char* dest){

  /** ETAPE 1: On lit chaque caractère du fichier source (les aaabbbbccc...) et *on le stoque dans le buffer
   */

  int c;
  FILE* fd;
  FILE* fichier2;
  fd=fopen(fichier, "r");
  int i=0; int nbre_car=0;
  while ((c = fgetc(fd)) != EOF)
    {
      int j=0;
      while(arbre[c].huff[j]!='\0'){
	buffer[i]=arbre[c].huff[j];
	i++;
	j++;
      }
      nbre_car++;
    }
	printf("Il y'a %i char \n",nbre_car);
  nbre_car_2=nbre_car;
  /*
    On peut afficher le buffer pour vérifier que tout a bien été copié:

  */
 
  printf("Affichage du buffer avant la reduction:%s\n",buffer); 
 






  /**On rajoute l'entête*/
  fichier2 = fopen(dest, "a+");
  fprintf(fichier2,"%d",nbre_car);
  fprintf(fichier2,"[");

  
  for(int i=0;i<256;i++){
    if((arbre[i].f)>0){
      fprintf(fichier2,"%c:%s",i,arbre[i].huff);
      go++;
    }
  }
  //On sépare l'entete de la partie compressée
  fprintf(fichier2,"]");




  /** ETAPE 2: si le nombre de caractères stockés dans le buffer >=8
  *     - on calcule la valeur entière des 8 premiers caractères
  * - on stocke dans le fichier compressé le caractère ASCII correspondant à cet*te valeur ent
  *    - on enlève les 8 premiers caractères du buffer et on continue
  */
  unsigned int cpt,som;
  int j;
  while(buffer[0]!='\0'){

   
    int u=7;
    while(buffer[u]=='\0'){
      buffer[u]='0';
      u--;
    }


    /**Calcul de la valeur entière du code binaire des 8 premiers caractères*/
    cpt=0; som=0;
    for(int i=7;i>=0;i--){
      /* if(buffer[i]=='0'){
	 som=som+(0*(puissance(2,cpt)));
	 } 0 * 0 donne 0 , donc autant ne rien faire
      */ 
      if(buffer[i]=='1'){
	som=som+(1*(puissance(2,cpt)));
      }
      cpt++;
    }


    /**
     * On peut afficher la valeur entière correspondant au code binaire des 8 pr*emiers caractères pour vérifier qu'elle est bien calculée
    */
    printf("%u\n",som);
   


    fprintf(fichier2,"%c",som);
    
    for(j=0;(j+8)!=sizeof(buffer)/sizeof(buffer[0]);j++){
      buffer[j]=buffer[j+8];
    }

    for (int i=j;i<263;i++)
      buffer[i]='\0';


    /** On peut afficher la valeur de k qui est la l'indice du dernier élément d*u nouveau tableau
     *      et le nouveau buffer réduit de 8 éléments 
     * printf("%i\n",k);
    */
    printf("%s\n",buffer);

 
 
  }



    fclose(fd);
    fclose(fichier2);
}


int main(int argc, char**argv){

 
  go=0;

  frequences = (float*) malloc(256*sizeof(float)) ;
  printf("\n");
  printf("Nous allons calculer les fréquences , et les afficher \n\n");
  float *freq=calculFreq(argv[1]);
  for(int i=0;i<256;i++){
    if (freq[i]>0){
      printf(".:: %c ::. ASCII %i Freq : %f \n", i, i, freq[i]);
      /**Afin de vérifier que la fréquence est bien calculée, on affiche i en ca*ractères (ex a), i en code ascii(97) et sa fréquence*/
    }      
  }
  printf("\n");

  printf("Construction récursive de l'arbre \n\n");
  Noeud arbre[511] ;
     

  
  construct(arbre, freq);
  affiche(arbre);
  int j;
  j= getRacine(arbre);
  int b=0;
  char code[257];

  printf("\n");
  printf("Voila notre dictionnaire \n\n");
  parcours(j,code,arbre,b);
  printf("\n");
  //On vérifie s'il n'y a pas déjà un fichier compressé 
   
  if (fopen(argv[2],"r")!=NULL){
    remove(argv[2]);
  }

  printf("Impression du buffer , et soustraction de 8 char à chaque fois ,et conversion en partie entière :\n\n");
  createFichierCompresse(argv[1],arbre,argv[2]);
  printf("===============Compression réalisée avec succès !=============== \n\n");
  int gain=(go*100)/nbre_car_2;
   printf("On a reussi à passer de %i octets à %i octets ! Gain de %i pourcent \n\n ",nbre_car_2,go,gain);


   free(frequences);

  
  return 0;
}
  

