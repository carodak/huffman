#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int indicebuffer=0;
/**indice du dernier element du buffer*/

int nombre_caractere;

/**On récupère l'entete (séparateur compris)*/



void cap(char* fich) {


  FILE* jh=fopen(fich,"r+");

  if( fgetc(jh)=='-') {

    fscanf(jh,"%i", &nombre_caractere);

  }
  char help;
  int k=0;
  while(k=fgetc(jh) != EOF ){

    help=fgetc(jh);
}

  FILE* gh=fopen("Cas_particulier_D","w+");
  for(int k=0;k<=nombre_caractere;k++){
    fputc(help,gh);
  }
    
  
}



  


void remplirBuffer(int n,char* buffer){
  int i=7;
  char codeBin[8];
  while (n!=0){
    if (n%2==0){
      codeBin[i]='0';
    }
    if (n%2==1){
      codeBin[i]='1';
    }
    n=n/2;
    i--;
  }
  while(i!=-1){
    codeBin[i]='0';
    i--;
  }
  for (int i=0;i<8;i++){
    buffer[indicebuffer]=codeBin[i];
    indicebuffer++;
  }
}



/**Je calcule le codebinaire de n et rempli le buffer*/
void lectureFichier(char* fichier,char* buffer, char* entete){
  
  int c; FILE* fd ; long position_separateur;
  int trouve=0; /**on fait en sorte qu'on ne trouve qu'une fois (la première) le séparateur car il est également possible de le trouver dans la partie compressée*/

  fd=fopen(fichier, "r");
  if(fd != NULL){
    while((c = fgetc(fd)) != EOF) {
      /** cette première condition n'a que pour unique but de trouver la position de notre séparateur, afin de copier le code compressé à partir de cette position
	 il faut faire attention car le séparateur utilisé peut etre trouvé dans le code compressé
	 on fait en sorte de ne rentrer qu'une seule fois dans la condition*/
      if (c == ']' && trouve==0) {
	position_separateur=ftell(fd);
	trouve=1;
      }
      /*si la position courante du curseur est supérieure à celle du séparateur alors on est dans la partie à décompresser*/
      if(ftell(fd)>position_separateur) {

	/**On vérifie qu'on obtient bien les entiers correspondants au code binaire */

	remplirBuffer(c, buffer);
      }
    }


    /**On replace le curseur au début et on récupère le seul entier du fichier : le nombre de caractères ainsi que le reste de l'entete (séparateur inclus)*/
    rewind(fd);
    fscanf(fd,"%i", &nombre_caractere);
    trouve=0; long position_separateur2=position_separateur; int b=0;
    while((c = fgetc(fd)) != EOF && ftell(fd)!=position_separateur+1) {
      if(c == '[' && trouve==0){
	position_separateur2=ftell(fd);
	trouve=1;
      }
      if(ftell(fd)>=position_separateur2){
	entete[b]=c;
	b++;
      }
    }

  }
}

void decryptagee(char* buffer,char * entete,char code [256][200]){


  
  /** on copie notre entete k dans un tableau à deux dimensions ce qui facilitera la tache pour comparer le buffer à ce tableau */
  int i=-1; int j=1; int k=0;
  
  while(entete[k]!=']'){
    
    if(entete[k+1]==':'){
      i++;
      j=0;
      code[i][j]=entete[k];
      j++;
      k++;
    }
    else{
      if(entete[k]!=':' ){
	code[i][j]=entete[k];
	j++;
      }
      k++;
    }
  }
  
  /** On vérifie que notre tableau à 2 dimensions est bien rempli*/


  FILE *fichier2;
  fichier2 = fopen("fichier_decompresse", "a+");

  int e=0; int f=1;int copie_e=e; int d=0; int cpt=0;

  //Tant qu'on arrive pas à la fin du buffer ou que notre cpt n'est pas égal au nombre de caractères on continue

  while(buffer[e]!='\0'&& cpt!=nombre_caractere){
	    
    /**Si le caractère dans mon tableau est égal à celui du buffer, on incrémente l'indice du buffer et l'indice du tableau*/
	 
    while(code[d][f]==buffer[copie_e]){
      //  printf("code[d][f]= %c, buffer[copie_e]=%c, d = %i, f = %i , copie_e = %i\n",code[d][f], buffer[copie_e], d,f,copie_e);
      copie_e++;
      f++;  
    }


    /**Soit on s'est arreté parce que le caractere de mon tableau code était différent de celui du buffer, soit parce qu'on est arrivé sur la fin du tableau code à l'indice d
      Ici, on s'intéresse au fait que les caractères étaient différents
      On incrémente l'indice de d pour comparer de nouveau, d varie de 0 à 256. On remet l'indice du buffer e là où il était au début de la comparaison
      on remet f l'indice de mon sous-tableau à 1 et non à 0 car à 0 il y a le caractère codé : par exemple a
    */

    if(code[d][f]!='\0'){
      copie_e=e;
      f=1;
      d++;
	     
    }
  
    /** Ici, on s'est arreté parce qu'on est arrivé sur à la fin du sous-tableau, code[d][f]='\0'. On copie le caractère stoqué dans mon sous-tableau à l'indice 0
      On remet ensuite l'indice d de mon tableau à 0 et l'indice f de mon sous-tableau à 1
      On enregistre la valeur de e dans une copie, afin de pouvoir revenir (si les éléments du buffer et du sous-tableau sont différents) et comparer les éléments se trouvant à l'indice suivant de mon tableau  */
    if(code[d][f]=='\0') {
      e=copie_e;
      fprintf(fichier2, "%c", code[d][0]); 
      d=0;
      f=1;
      cpt++;
    }
 
  }
}
 
int main(int argc,char** argv){

  FILE* test=fopen(argv[1],"r+");
  if (fgetc(test)=='-') {
    printf("\n\n");
     printf("===============Cas particulier !=============== \n\n");
    
    printf("Nous sommes dans un cas particulier \n\nLe mieux en complexité est de ne pas passer par un arbre \n\n");
    cap(argv[1]);

    printf("Votre fichier a été décompressé sous le nom de Cas_Particulier_D \n\n");
  }
  else{
char entete[1000];
char buffer[5000];
char code[256][200];

  
 lectureFichier(argv[1],buffer,entete);
 
  printf("Voici le buffer : %s\n",buffer);


  //On vérifie s'il n'y a pas déjà un fichier décompressé 
   
  if (fopen("fichier_decompresse","r")!=NULL){
    remove("fichier_decompresse");
  }
  decryptagee(buffer,entete, code);
  }

  printf("==============Decompression réalisée avec succès !============== \n\n");


  return 0;
}



 

