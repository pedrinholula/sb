#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mounterdata.h"

/// Inicializa o montador
void initialize(mounter *m)
{
    int x,y;
    for(x=0; x<TABSIZE; x++)
    {
        m->tabela[x].pc = -1;
        for (y=0; y<STRINGSIZE; y++)
        {
        	m->tabela[x].label[y] = '\0';
        }
    }
    m->tam = 0;
    m->desl =0;
    return;
}

/// Faz a primeira passagem no arquivo para a criação da tabela de simbolos
void firststep(mounter *m, char in[])
{
    FILE *fin;
    char line[STRINGSIZE],word[STRINGSIZE];
    int pc = 0,ilc = 0,opvalue;


    fin = fopen(in,"r");
    fgets(line,101,fin);
    comment(line);
    while( (!feof(fin)) && (ilc < TABSIZE) )
    {
        sscanf(line,"%s",word);
        if(verlabel(word))
        {
            strcpy(m->tabela[ilc].label,word);
            m->tabela[ilc].pc = pc;
//            printf("%s, %d\n",m->tabela[ilc].label,pc);
            ilc++;
            sscanf(line,"%*s %s",word);
            m->tam++;
        }
        opvalue = veroperators(word);
        pc += opvalue;
        pc++;
        fgets(line,101,fin);
        comment(line);
    }
    fclose(fin);
    m->desl = pc - 1;
    return;
}


/// Faz a segunda passagem no arquivo
void secondstep(mounter *m, char in[], char out[])
{
    FILE *fin,*fout;
    char line[STRINGSIZE],word[STRINGSIZE],*c;
    int pc = 0, reg, i;

    fin = fopen(in,"r");
    fout = fopen(out,"w+");

    fgets(line,101,fin);
    comment(line);
    while( !feof(fin) )
    {
        sscanf(line,"%s",word);
        // Verifica label e tira
        if(verlabel(word))
        {
            c = strstr(line,":") + 1;
            if(c[0] == ' ')
            {
                c++;
            }
            strcpy(line,c);
            sscanf(line,"%s",word);
        }

        if(!strcasecmp(word,"WORD"))
		{
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%s\n",word);
			pc++;
		}

        if(!strcasecmp(word,"END"))
        {
           break;
        }

        if(!strcasecmp(word,"READ"))
        {
            fprintf(fout,"01\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%d\n",vertab(m,word)-pc);
        }

        if(!strcasecmp(word,"WRITE"))
		{
			fprintf(fout,"02\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%d\n",vertab(m,word)-pc);
		}

		if(!strcasecmp(word,"MOVE"))
		{
			fprintf(fout,"10\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

			sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"LOAD"))
		{
			fprintf(fout,"11\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

			sscanf(line,"%*s %*s %s",word);
            fprintf(fout,"%d\n",vertab(m,word)-pc);
		}

        if(!strcasecmp(word,"STORE"))
		{
			fprintf(fout,"12\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            fprintf(fout,"%d\n",vertab(m,word)-pc);

			sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"ADD"))
		{
			fprintf(fout,"21\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"SUB"))
		{
            fprintf(fout,"22\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"NEG"))
		{
			fprintf(fout,"23\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"NOT"))
		{
			fprintf(fout,"31\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"AND"))
		{
			fprintf(fout,"32\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"OR"))
		{
			fprintf(fout,"33\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
        }

        if(!strcasecmp(word,"XOR"))
		{
            fprintf(fout,"34\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"TEST"))
		{
			fprintf(fout,"41\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"COMP"))
		{
			fprintf(fout,"42\n");
			pc+=3;

			sscanf(line,"%*s %s %*s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);

            sscanf(line,"%*s %*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
        }

        if(!strcasecmp(word,"BEZ"))
		{
			fprintf(fout,"51\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%d\n",vertab(m,word)-pc);
		}

        if(!strcasecmp(word,"BNZ"))
		{
			fprintf(fout,"52\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%d\n",vertab(m,word)-pc);
		}

        if(!strcasecmp(word,"BLZ"))
		{
			fprintf(fout,"53\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%d\n",vertab(m,word)-pc);
		}

        if(!strcasecmp(word,"JMP"))
		{
			fprintf(fout,"60\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%d\n",vertab(m,word)-pc);
		}

        if(!strcasecmp(word,"PUSH"))
		{
			fprintf(fout,"71\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"POP"))
		{
			fprintf(fout,"72\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
            reg = verreg(word);
			fprintf(fout,"0%d\n",reg);
		}

        if(!strcasecmp(word,"CALL"))
		{
			fprintf(fout,"81\n");
			pc+=2;
			sscanf(line,"%*s %s",word);
			fprintf(fout,"%d\n",vertab(m,word)-pc);
		}

        if(!strcasecmp(word,"RET"))
		{
			fprintf(fout,"82\n");
			pc++;
		}

        if(!strcasecmp(word,"HALT"))
		{
			fprintf(fout,"90\n");
			pc++;
		}

        fgets(line,101,fin);
        comment(line);
    }
    
    fprintf(fout, "###\n%d %d",m->desl,m->tam);
    for (i = 0; i < m->tam; i++)
    {
        fprintf(fout, "\n%s %d", m->tabela[i].label, m->tabela[i].pc);
    }
    
    fclose(fin);
    fclose(fout);
    return;
}

///Verifica se há Label
int verlabel(char label[])
{
    int size = strlen(label);

    if(label[size -1] == ':')
    {
        label[size-1] = '\0';
        return 1;
    }
    else
    {
        return 0;
    }

}

/// Verifica quantos operadores tem a operação
int veroperators(char operation[])
{
    if( !strcasecmp(operation, "MOVE") || !strcasecmp(operation, "LOAD") ||
        !strcasecmp(operation, "STORE") || !strcasecmp(operation, "ADD") ||
        !strcasecmp(operation, "SUB") || !strcasecmp(operation, "NOT") ||
        !strcasecmp(operation, "AND") || !strcasecmp(operation, "OR")  ||
        !strcasecmp(operation, "XOR") || !strcasecmp(operation, "TEST") ||
        !strcasecmp(operation, "COMP"))
    {
        return 2;
    }
    else
    {
        if( !strcasecmp(operation, "READ") || !strcasecmp(operation, "WRITE") ||
            !strcasecmp(operation, "NEG") || !strcasecmp(operation, "BEZ") ||
            !strcasecmp(operation, "BNZ") || !strcasecmp(operation, "BLZ") ||
            !strcasecmp(operation, "JMP") || !strcasecmp(operation, "PUSH")  ||
            !strcasecmp(operation, "POP") || !strcasecmp(operation, "CALL") )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

/// Verifica a existencia de comentários
void comment(char word[])
{
    int i;

    for (i=0; i<STRINGSIZE; i++)
    {
    	if(word[i] == ';')
    	{
    	    word[i] = '\n';
    	    word[i+1] = '\0';
    	    return;
    	}
    }
}

/// Busca na tabela de simbolos
int vertab(mounter *m, char label[])
{
    int i;

    for (i=0; i<TABSIZE; i++)
    {
    	if(!strcasecmp(m->tabela[i].label,label))
    	{
    	    return m->tabela[i].pc;
    	}
    }
    return -1;
}

/// Decodifica o registrador
int verreg(char reg[])
{
    if(!strcasecmp(reg,"RA"))
    {
        return 0;
    }
    if(!strcasecmp(reg,"RB"))
    {
        return 1;
    }
    if(!strcasecmp(reg,"RC"))
    {
        return 2;
    }
    if(!strcasecmp(reg,"RD"))
    {
        return 3;
    }
    return -1;
}


/// Imprime a tabela de símbolos no modo verbose
void printtab(mounter *m)
{
    int i = 0;
    printf("Label \t Endereço\n");
    while(m->tabela[i].pc != -1)
    {
        printf("%s \t %d\n",m->tabela[i].label,m->tabela[i].pc);
        i++;
    }
    return;
}

