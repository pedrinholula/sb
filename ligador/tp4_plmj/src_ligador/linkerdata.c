#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkerdata.h"

/// OK
void initialize(linker *l)
{
    int i,j;
    i = 0;
    j = 0;

	//inicializa tabela de simbolos
	for(i=0;i<TABSIZE;i++)
	{
		l->tabela[i].pc=0;
		for(j=0;j<STRINGSIZE;j++)
		{
            l->tabela[i].label[j]='\0';
		}
	}
	return;
}

void join(linker *l,int argc,char *argv[]) //OK
{
    int i,j,
    mpos,pdesl, adesl,
    tsize, pc, ilc;

    char word[STRINGSIZE];
    FILE *fin;

    pdesl=0;
    adesl=0;
    tsize=0;
    pc=0;
    ilc=0;

    /// Abre a main.o - OK
    for(mpos=1;mpos < argc;mpos++)
    {
      if((strcmp(argv[mpos],"-m")==0))
      {
        fin=fopen(argv[mpos+1],"r");
        break;
      }
    }
    /// Procura info da tabela de simbolos - OK
    fgets(word,STRINGSIZE,fin);
    while(strcmp(word,"###\n")!=0)
    {
      fgets(word,STRINGSIZE,fin);
    }
    fscanf(fin,"%d",&pdesl);
    fscanf(fin,"%d",&tsize);
    /// copia a tabela de simbolos - OK
    for(i=0;i<tsize;i++)
    {
        fscanf(fin,"%s",word);
        fscanf(fin,"%d",&ilc);
        strcpy(l->tabela[pc].label,word);
        l->tabela[pc].pc = ilc;
        pc++;
    }
    fclose(fin);
    /// Add a info de cada modulo na tabela de simbolos
    for(j=1;j<mpos-1;j++)
    {
        fin=fopen(argv[j],"r");
        fgets(word,STRINGSIZE,fin);
        while(strcmp(word,"###\n")!=0)
        {
          fgets(word,STRINGSIZE,fin);
        }
        fscanf(fin,"%d",&pdesl);
        fscanf(fin,"%d",&tsize);

       for(i=0;i<tsize;i++)
        {
          fscanf(fin,"%s",word);
          fscanf(fin,"%d",&ilc);
          strcpy(l->tabela[pc].label,word);
          l->tabela[pc].pc = ilc;
          pc++;
        }
        fclose(fin);
        //atualiza o valor de deslocamento
        pdesl+=adesl;
        fclose(fin);
    }
    return;
}

void execute(linker *l,int argc,char *argv[])
{
    int i,
    mpos, pout,
    pc;
    char word[STRINGSIZE], pword[STRINGSIZE];
    FILE *fin, *fout;
    pc=1;

    /// Arquivo de saída - OK
    for(pout=1; pout<argc; pout++)
    {
      if(strcmp(argv[pout],"-o")==0)
      {
        fout=fopen(argv[pout+1],"w");
        break;
      }
    }
    /// Abre a main.o - OK
    for(mpos=1;mpos < argc;mpos++)
    {
      if((strcmp(argv[mpos],"-m")==0))
      {
        fin=fopen(argv[mpos+1],"r");
        break;
      }
    }
    /// Escreve a main.o na saida
    fscanf(fin,"%s",word);
    while(strcmp(word,"###"))
    {
        if(verify(word)==1)
        {
          fprintf(fout,"%d\n",search(l,word)-pc);
        }
        else
        {
          fprintf(fout,"%s\n",word);
        }
        pc++;
        fscanf(fin,"%s",word);
    }
    fclose(fin);

    //Escreve os demais módulos na saída
    for(i=1;i<mpos-1;i++)
    {
      fin=fopen(argv[i],"r");
      fscanf(fin,"%s",word);
      while(strcmp(word,"#"))
      {
        if(verify(word)==1)
        {
          if(strcmp("12", pword) == 0)
          {
             fprintf(fout,"%d\n",search(l,word)-pc-1);
          }
          else
          {
            fprintf(fout,"%d\n",search(l,word)-pc);
          }
        }
        else
        {
          fprintf(fout,"%s\n",word);
        }
        pc++;
        strcpy(pword, word);
        fscanf(fin,"%s",word);
      }
      fclose(fin);
    }
    fclose(fout);
}

//retorna o ilc do label
int search(linker *l,char *word)
{
	int i=0;
  //trata o label
	for(i=0;i<STRINGSIZE-1;i++)
  {
    word[i]=word[i+1];
  }

  i=0;
	while(strcmp(word,l->tabela[i].label))
	{
    i++;
    if(i>=TABSIZE)
    {
      break;
    }
	}
  if(i<TABSIZE)
  {
    return l->tabela[i].pc;
  }
  else
  {
    return -1;
  }
}

//verifica se a linha é um símbolo
int verify(char *word)
{
	if(word[0]==':')
	{
    return 1;
  }
	else
	{
		return 0;
	}
}
