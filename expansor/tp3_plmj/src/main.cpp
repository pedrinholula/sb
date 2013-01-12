#include <iostream>
#include "expansor.h"

using namespace std;

int main(int argc, char *argv[])
{
    string in,out;
    macro_t macro;
    macro_i ti;

    in = argv[1];
    out = argv[2];

    first_step(in, macro);
        second_step(in, out, macro);
//    print_macro(macro);
    return 0;
}
