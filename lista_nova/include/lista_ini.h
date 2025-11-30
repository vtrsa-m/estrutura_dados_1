#ifndef LISTA_INI_H
#define LISTA_INI_H

struct Estudante 
{
    int ID;
    float nota;
    char nome[20];
};
	
struct No 
{ 
    struct Estudante estudante;
    struct No * proximo; 
};

void  lista_TresNosEstaticos();

#endif

