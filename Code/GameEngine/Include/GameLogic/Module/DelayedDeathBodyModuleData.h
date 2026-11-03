// Target facts (code addresses are RVAs, table addresses are VAs): factory 0x00251622 pushes 0x80 at 0x0025162E, calls constructor 0x004C180A at 0x00251646 and supplies buildFieldParse 0x004C159E at 0x0025165C. Constructor 0x004C180A calls RespawnBodyModuleData 0x004C14DF at 0x004C180D, writes dwords +6C/+74/+7C at 0x004C1814/17/1A, installs 0x00C5BC48 at 0x004C181D and writes byte flags +70/+78 at 0x004C1823/27. Table 0x00C5BC48 has 31 slots and ends at the string at 0x00C5BCC4; slot 0 is deleting destructor 0x004C182F, whose call at 0x004C1832 reaches the shared destructor 0x004C1B7B, a jump to RespawnBodyModuleData destructor 0x004C1569. Slots 1..30 equal ActiveBodyModuleData's 0x00C5AFB8, including true-returning slot 7; no slots are added.
// Target facts: RespawnBodyModuleData constructor 0x004C14DF calls the registered ActiveBodyModuleData constructor 0x004BF59F at 0x004C14F3, installs 0x00C5BA00 at 0x004C1501, constructs the registered four-byte Rva003623E5Member at +64 through 0x003623E5 (0x004C1507), initializes it through 0x00362087 (0x004C1533) and writes byte +68 at 0x004C153C. Factory 0x00251596 allocates 0x6C at 0x002515A2. Destructor 0x004C1569 destroys +64 at 0x004C1581 and calls ActiveBodyModuleData destructor 0x00256CB0 at 0x004C158C; that destructor installs Snapshot's four-slot teardown table 0x00BBB554 at 0x00256CFD. Snapshot constructor 0x000053A6 and destructor 0x0049B47C install the same table, which is not this class's live table. RespawnBodyModuleData slots 1..30 equal ActiveBodyModuleData's; its slot 0 is 0x004C154D.
// Target facts: buildFieldParse 0x004C159E calls RespawnBodyModuleData::buildFieldParse 0x004C12D0 at 0x004C15A2 and registers 0x00C5BAE8 at 0x004C15AE. Its five records identify unsigned duration +6C (parser 0x00338B30), bool +70/+78 (0x0002E850), const FXList* +74 (0x00338A09) and const UpgradeTemplate* +7C (0x00339679). Parent table 0x00C5B8BC, registered at 0x004C12E0, identifies the four-byte filter +64 and bool +68. Member source spellings remain unknown, so fields use offsets. The constructor, virtual destructor and rowed static methods are declared out of line. FreeLifeBodyModuleData constructor 0x004C1B3B shares 0x00C5BC48 but its factory 0x002516B1 allocates 0x88 and its fields differ; table sharing alone does not identify the types.
#pragma once

#ifndef BFME2_DELAYEDDEATHBODYMODULEDATA_H
#define BFME2_DELAYEDDEATHBODYMODULEDATA_H

#include "RespawnBodyModuleData.h"

class UpgradeTemplate;

class DelayedDeathBodyModuleData : public RespawnBodyModuleData
{
public:
    DelayedDeathBodyModuleData();
    virtual ~DelayedDeathBodyModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    unsigned int field6C;
    bool field70;
    const FXList *field74;
    bool field78;
    const UpgradeTemplate *field7C;
};

typedef char DelayedDeathBodyModuleDataSizeCheck[sizeof(DelayedDeathBodyModuleData) == 0x80 ? 1 : -1];

#endif
