#ifndef LINKERDATA_H_INCLUDED
#define LINKERDATA_H_INCLUDED
#define TABSIZE 1000
#define STRINGSIZE 100

typedef struct simbol
{
    char label[STRINGSIZE];
    int pc;
} simbol;

typedef struct linker
{
    simbol tabela[TABSIZE];
} linker;

void initialize(linker *l);

void join(linker *l,int argc,char *argv[]);

int search(linker *l,char *string);

int verify(char *string);

void execute(linker *l,int argc,char *argv[]);

#endif // linkerdata_H_INCLUDED
