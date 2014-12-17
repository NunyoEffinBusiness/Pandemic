#include "core/application.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    a.initialize();
    return a.exec();
}
