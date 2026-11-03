// Target facts (code addresses are RVAs, table addresses are VAs): RespawnBodyModuleData constructor 0x004C14DF calls the registered ActiveBodyModuleData constructor 0x004BF59F at 0x004C14F3, installs 0x00C5BA00 at 0x004C1501, constructs the registered four-byte Rva003623E5Member at +64 through 0x003623E5 (0x004C1507), initializes it through 0x00362087 (0x004C1533) and writes byte +68 at 0x004C153C. Factory 0x00251596 allocates 0x6C at 0x002515A2. Destructor 0x004C1569 destroys +64 at 0x004C1581 and calls ActiveBodyModuleData destructor 0x00256CB0 at 0x004C158C; that destructor installs Snapshot's four-slot teardown table 0x00BBB554 at 0x00256CFD. Snapshot constructor 0x000053A6 and destructor 0x0049B47C install the same table, which is not this class's live table. RespawnBodyModuleData slots 1..30 equal ActiveBodyModuleData's; its slot 0 is 0x004C154D.
// Target facts: parent table 0x00C5B8BC, registered by RespawnBodyModuleData::buildFieldParse 0x004C12D0 at 0x004C12E0, identifies the four-byte filter +64 and bool +68. Member source spellings remain unknown, so fields use offsets.
#pragma once

#ifndef BFME2_RESPAWNBODYMODULEDATA_H
#define BFME2_RESPAWNBODYMODULEDATA_H

#include "ActiveBodyModuleData.h"
#include "Rva003623E5Member.h"

class RespawnBodyModuleData : public ActiveBodyModuleData
{
public:
    RespawnBodyModuleData();
    virtual ~RespawnBodyModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    Rva003623E5Member field64;
    bool field68;
};

typedef char RespawnBodyModuleDataSizeCheck[sizeof(RespawnBodyModuleData) == 0x6C ? 1 : -1];

#endif
