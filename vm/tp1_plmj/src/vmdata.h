#ifndef VMDATA_H_INCLUDED
#define VMDATA_H_INCLUDED
#define MEMSIZE 1024

typedef struct vm
{
    int mem[MEMSIZE],m,fmem, // Memoria, memoria atual e memoria final
    pc,sp,fp, // Reg Especificos
    reg[4]; // registradores básicos
    short unsigned int rflags[2]; // Flag reg = [zero,negativo]
    char mode;
} vm;

void initialize(int argc, char *argv[], vm *virt);

void readmem(vm *virt, char in[]);

void exec(vm *virt);

int decode(vm *virt,int inst);

int getinst(vm virt);

void incpc(vm *virt);

void verbose(vm virt, int inst);





#endif // VMDATA_H_INCLUDED
