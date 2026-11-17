// Native ctor 005896B0 installs the common 31-slot ModuleData table, clears
// the word at +8 and sets the byte at +0C. The MonsterDock constructor places
// its filter at +10, proving this base is 0x10 bytes.
#ifndef CANONICAL_DOCKUPDATEMODULEDATA_H
#define CANONICAL_DOCKUPDATEMODULEDATA_H

#include "../../Common/ModuleData.h"

class MultiIniFieldParse;

class DockUpdateModuleData : public ModuleData
{
public:
    DockUpdateModuleData();
    virtual ~DockUpdateModuleData() {}
    static void buildFieldParse(MultiIniFieldParse &parse);

    int m_numberApproachPositionsData;
    bool m_isAllowPassthrough;
};

#endif // CANONICAL_DOCKUPDATEMODULEDATA_H
