#include "core/application.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    if(a.initialize())
        return a.exec();
    return 1056;
}
