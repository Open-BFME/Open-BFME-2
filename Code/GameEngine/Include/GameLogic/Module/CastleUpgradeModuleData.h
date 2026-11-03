// Target facts (code addresses are RVAs, table addresses are VAs): constructor 0x00255836 calls registered Rva00253487Base's 0x00253487 at +0, stores 0x00BF3940 at 0x00255841, clears the four-byte string at +0x118 (0x00255847), and stores float zero at +0x11C (0x0025584E). Factory 0x0025585A pushes 0x120 at 0x0025585B and calls this constructor at 0x0025586C. The registered base occupies 0x118 bytes, including ModuleData's eight bytes and the member constructed at +8 by 0x00253493; derived fields begin at +0x118.
// Table 0x00BF3940 contains 31 slots and ends with a zero word at 0x00BF39BC. It matches the base's 0x00BF2558 except slot 0: 0x00256267 calls the shared complete destructor 0x002561EF, which releases the string at +0x118 through 0x00036410 (0x00256204..0x0025620A) and restores Snapshot's 0x00BBB554 at 0x00256212; unwind 0x00771D21 calls the base destructor 0x0049B47C, also storing 0x00BBB554. Snapshot's constructor 0x000053A6 stores that four-slot teardown table. The live interface inherits ModuleData's 31 slots with slot10 returning true (0x0050B5C6); slot2 is 0x00065212, returning the inherited name ModuleData. The destructor remains out of line.
// buildFieldParse (0x004B6847) registers the base parse table at offset 8 and table 0x00C588C4 at offset 0. Its entries name Upgrade at +0x118 with INI::parseAsciiString (0x0002F11E) and WallUpgradeRadius at +0x11C with INI::parseReal (0x0002EFC0); the terminator is at 0x00C588E4. Factory 0x0025587F passes this parse function. CastleUpgrade::upgradeImplementation takes the string's address at 0x004B69DF for UpgradeCenter::findUpgrade (0x004B69E8), then grants that upgrade; its nearby-object helper loads the range-query radius at +0x11C (0x004B6904). These calls support m_upgradeToGrant and m_radius; original member spellings are not asserted. The constructor, factory and parse function have ledger rows and remain declared out of line.
#pragma once

#ifndef BFME2_CASTLEUPGRADEMODULEDATA_H
#define BFME2_CASTLEUPGRADEMODULEDATA_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../Common/ModuleData.h"
#include "Rva00253487Base.h"

class INI;
class MultiIniFieldParse;

class CastleUpgradeModuleData : public Rva00253487Base
{
public:
    CastleUpgradeModuleData();
    virtual ~CastleUpgradeModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    AsciiString m_upgradeToGrant;
    float m_radius;
};

#endif
