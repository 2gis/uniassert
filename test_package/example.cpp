#include <iostream>
#include <uniassert/uniassert.h>

int main(int argc, char** argv) {
    UNI_CHECK_RETURN(argc, 1);
    UNI_ENSURE_RETURN(argv, 2);
    return 0;
}
