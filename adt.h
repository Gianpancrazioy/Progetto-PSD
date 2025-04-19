typedef struct list* lista;
typedef struct node* nodo;

lista newlist();
int addfirst(lista l, int value);
int remfirst(lista l);
void printlist(lista l);