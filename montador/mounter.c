#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mounterdata.h"

int main(int argc, char *argv[])
{
    mounter m;

    initialize(&m);
    firststep(&m,argv[2]);
    secondstep(&m,argv[2],argv[3]);
    if( (argv[1][0] == 'v') || (argv[1][0] == 'V'))
    {
        printtab(&m);
    }
    return 0;
//    vm virt;
//    initialize(argc, argv, &virt);
//    readmem(&virt,argv[5]);
//    exec(&virt);
//    return 0;
}
