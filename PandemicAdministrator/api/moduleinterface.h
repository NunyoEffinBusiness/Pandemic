#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

#include <QString>

class ModuleInterface
{
public:
    virtual QString name() const = 0;
};

#define PluginInterface_iid "pandemic.plugin.module"

Q_DECLARE_INTERFACE(ModuleInterface, PluginInterface_iid)

#endif // MODULEINTERFACE_H
