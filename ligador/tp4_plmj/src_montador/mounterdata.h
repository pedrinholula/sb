#ifndef MOUNTERDATA_H_INCLUDED
#define MOUNTERDATA_H_INCLUDED
#define TABSIZE 100
#define STRINGSIZE 100

typedef struct simbol
{
    char label[STRINGSIZE];
    int pc;
} simbol;

typedef struct mounter
{
    simbol tabela[TABSIZE];
    int desl;
    int tam;
} mounter;

void initialize(mounter *m);

void firststep(mounter *m, char in[]);

int verlabel(char label[]);

int veroperators(char operation[]);

void comment(char word[]);

void secondstep(mounter *m, char in[], char out[]);

int vertab(mounter *m, char label[]);

int verreg(char reg[]);

void printtab(mounter *m);

#endif // MOUNTERDATA_H_INCLUDED
