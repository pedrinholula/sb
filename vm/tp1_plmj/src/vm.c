#include <stdio.h>
#include <stdlib.h>
#include "vmdata.h"

int main(int argc, char *argv[])
{
    vm virt;
    initialize(argc, argv, &virt);
    readmem(&virt,argv[5]);
    exec(&virt);
    return 0;
}
