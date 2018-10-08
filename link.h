#define NMAX 200
typedef struct noeud {
  float f;
  int pere, fg, fd;
 char huff[NMAX];
}Noeud;

int min(Noeud*,int);
void parcours(unsigned short int,char*,Noeud*,unsigned short int);


