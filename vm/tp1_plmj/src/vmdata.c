#include <stdio.h>
#include <stdlib.h>
#include "vmdata.h"


// Inicializa a máquina virtual
void initialize(int argc, char *argv[], vm *virt)
{
    int x;
    virt->pc = atoi(argv[1]);
    virt->sp = atoi(argv[2]);
    virt->fp = 0;
    virt->m = atoi(argv[3]);
    virt->fmem = virt->m;
    virt->mode = argv[4][0];
    virt->rflags[0] = 0;
    virt->rflags[1] = 0;
    for (x=0; x<4; x++)
    {
    	virt->reg[x] = 0;
    }
    for (x=0; x<MEMSIZE; x++)
    {
    	virt->mem[x] = 0;
    }
    return;
}

// Lê a memoria da máquina virtual
void readmem(vm *virt, char in[])
{
    int x;
    FILE *fin;
    fin = fopen(in,"r");
    x = virt->m;
    while( (!feof(fin) ) && (x < MEMSIZE) )
    {
        fscanf(fin,"%d\n",&virt->mem[x]);
        x++;
    }
    virt->fmem = x;
    fclose(fin);
    return;
}


// Carrega a próxima instrução
int getinst(vm virt)
{
    int pos,inst;

    pos = virt.m + virt.pc;
    if (pos == virt.fmem)
    {
        return -1;
    }
    else
    {
        inst = virt.mem[pos];
        return inst;
   }
}

void exec(vm *virt)
{
    int inst,ret=1;
    inst = getinst(*virt);
    while ( (inst >= 0) &&  (ret >= 0))
    {
        incpc(virt);
        ret = decode(virt, inst);
        if(virt->mode == 'v')
        {
            verbose(*virt, inst);
        }
        inst = getinst(*virt);
    }
    return;
}

int decode(vm *virt, int inst)
{
    int M,value,
    R1,R2;
    int ret;
    ret = 1;
    switch(inst)
    {
        case 01:    //read
        {
            M = getinst(*virt);
            scanf("%d",&value);
            incpc(virt);
            virt->mem[virt->pc + M] = value;
            break;
        }

        case 02: // write
        {
            M = getinst(*virt);
            incpc(virt);
            printf("%d\n", virt->mem[virt->pc + M]);
            break;
        }

        case 10: //move
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] = virt->reg[R2];
            break;
        }

        case 11: //load
        {
            R1 = getinst(*virt);
            incpc(virt);
            M = getinst(*virt);
            incpc(virt);
            virt->reg[R1] = virt->mem[virt->pc + M];
            break;
        }

        case 12: //store
        {
            M = getinst(*virt);
            incpc(virt);
            R1 = getinst(*virt);
            incpc(virt);
            virt->mem[virt->pc + M] = virt->reg[R1];
            break;
        }

        case 21: // ADD
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] += virt->reg[R2];
            break;
        }

        case 22: // Sub
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] -= virt->reg[R2];
            break;
        }


        case 23: //Neg
        {
            R1 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] *= -1;
            break;
        }

        case 31: //not
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] = ~(virt->reg[R2]);
            break;
        }
        case 32: //and
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] = (virt->reg[R2] & virt->reg[R1]);
            break;
        }

        case 33: //or
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] = (virt->reg[R2] | virt->reg[R1]);
            break;
        }

        case 34: //xor
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] = (virt->reg[R2] ^ virt->reg[R1]);
            break;
        }

        case 41: //test
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            value = (virt->reg[R2] & virt->reg[R1]);
            if (value == 0)
            {
                virt->rflags[0] = 1;
                virt->rflags[1] = 0;
            }
            if(value < 0)
            {
                virt->rflags[1] = 1;
                virt->rflags[0] = 0;
            }
            break;
        }

        case 42: //comp
        {
            R1 = getinst(*virt);
            incpc(virt);
            R2 = getinst(*virt);
            incpc(virt);
            value = (virt->reg[R2] - virt->reg[R1]);
            if (value == 0)
            {
                virt->rflags[0] = 1;
                virt->rflags[1] = 0;
            }
            if(value < 0)
            {
                virt->rflags[1] = 1;
                virt->rflags[0] = 0;
            }
            break;
        }

        case 51: // BEZ
        {
            M = getinst(*virt);
            incpc(virt);
            if(virt->rflags[0] == 1)
            {
                virt->pc += M;
            }
            break;
        }

        case 52: // BNZ
        {
            M = getinst(*virt);
            incpc(virt);
            if(virt->rflags[0] == 0)
            {
                virt->pc += M;
            }
            break;
        }

        case 53: // BLZ
        {
            M = getinst(*virt);
            incpc(virt);
            if(virt->rflags[1] == 1)
            {
                virt->pc += M;
            }
            break;
        }

        case 60: // JMP
        {
            M = getinst(*virt);
            incpc(virt);
            virt->pc += M;
            break;
        }

        case 71: //PUSH
        {
            R1 = getinst(*virt);
            incpc(virt);
            virt->sp--;
            virt->mem[virt->sp] = virt->reg[R1];
            break;
        }

        case 72: //POP
        {
            R1 = getinst(*virt);
            incpc(virt);
            virt->reg[R1] = virt->mem[virt->sp];
            virt->sp++;
            break;
        }

        case 81: //CALL
        {
            M = getinst(*virt);
            incpc(virt);
            virt->sp--;
            virt->mem[virt->sp] = virt->pc;
            virt->sp--;
            virt->mem[virt->sp] = virt->fp;
            virt->fp = virt->sp;
            virt->pc += M;
            break;
        }

        case 82: //RET
        {
            virt->sp = virt->fp;
            virt->fp = virt->mem[virt->sp];
            virt->sp++;
            virt->pc = virt->mem[virt->sp];
            virt->sp++;
            break;
        }

        case 90: //HALT
        {
            ret = -1;
            break;
        }

        default:
        {
            ret = 0;
        }

    }
    return ret;
}


void incpc(vm *virt)
{
    virt->pc++;
}

void verbose(vm virt, int inst)
{
    printf("INST: %d; PC: %d; SP: %d; FP: %d; Flag.Zero: %d; Flag.Neg: %d; RA: %d; RB: %d; RC: %d; RD: %d;\n",inst,virt.pc,virt.sp, virt.fp,virt.rflags[0],virt.rflags[1],virt.reg[0],virt.reg[1],virt.reg[2],virt.reg[3]);
}
