// Target facts (code addresses are RVAs, table addresses are VAs): factory 0x00254E7D allocates 0x38 at 0x00254E89 and calls constructor 0x00253510 at 0x00254E9E. Constructor store 0x00253528 installs the shared ModuleData table 0x00C4ED70 at +0; call 0x0025352E initializes DieMuxData through 0x004CE534 at +8. ModuleFactory writes the module tag at +4 at 0x00257237, so the registered ModuleData base occupies +0..+7 and the member occupies +8..+0x37. Derived constructor 0x0045D176 starts its next member at +0x38 (0x0045D186).
// Target facts: 0x00C4ED70 has 31 slots ending at 0x00C4EDEC: 0=0x004A10FD, 1=0x000B3FD0, 2=0x00065212, 3=0x0047A69C, 4..13/15=0x0047A699, 14=0x000B69A1, 16..29=0x000D43D0, 30=0x0050B5C6, all inherited from ModuleData. Destructor 0x0049B47C stores Snapshot's four-slot table 0x00BBB554; constructor unwind 0x00771C42 and derived unwind 0x0078BFE7 call this teardown at +0. The teardown table is not the live interface; this class adds no virtual slots and suppresses intermediate vptr stores with novtable. All rowed methods remain declarations.
// Target facts: parser 0x002534FE adds the DieMuxData table from 0x004CE52E (0x00C5FFA0) at +8; its member offsets 0/4/0x14/0x24/0x28/0x2C and initializer 0x004CE534 fix the member extent at 0x30. Registration 0x00258AFB binds the factory; the inherited getter 0x00065212 returns ModuleData at 0x00BC5AFC. The 0x38 allocation and member initialization distinguish this object from its eight-byte parent despite their shared table, getter and folded destructor. The member name stays neutral because no target declaration names it.
#pragma once
#ifndef BFME2_DESTROYDIEMODULEDATA_H
#define BFME2_DESTROYDIEMODULEDATA_H

#include "../../Common/ModuleData.h"
#include "DieMuxData.h"

class __declspec(novtable) DestroyDieModuleData : public ModuleData
{
public:
    DestroyDieModuleData();
    virtual ~DestroyDieModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);

private:
    DieMuxData m_08;
};

#endif
