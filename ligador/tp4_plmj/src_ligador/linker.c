#include <stdio.h>
#include <stdlib.h>
#include "linkerdata.h"

int main(int argc,char *argv[])
{
	linker l;
	
	initialize(&l);
	join(&l,argc,argv);
	execute(&l,argc,argv);
	return 0;
}
