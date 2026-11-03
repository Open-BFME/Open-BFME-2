// Target facts (code addresses are RVAs, tables are VAs): constructor 0x00498E2E stores 0x00C501B0 at 0x00498E45; destructor 0x00498D46 restores it at 0x00498D57, destroys the members, then stores Snapshot's 0x00BBB554 at 0x00498DC7. The latter is base teardown. The live table ends before string data at 0x00C5022C and has 31 slots: 0 is deleting destructor 0x00498DD7 (calls 0x00498D46), 1=0x000B3FD0, 2=0x00065212 (inherited "ModuleData" at 0x00BC5AFC), 3=0x0047A69C, 4..13/15=0x0047A699, 14=0x000B69A1, 16..29=0x000D43D0, 30=0x0050B5C6. Slots 1..30 equal registered ModuleData's 0x00C4ED70. ModuleData supplies the eight-byte prefix; no additional virtual slot or intermediate base name is established.
// Target facts: factory 0x00253F1F requests 0x4C bytes at 0x00253F2B and calls the constructor at 0x00253F40. Constructor stores 0x00498E4E..0x00498E5A initialize the four-byte string/+0x14 and four reference handles/+0x1C..+0x28; destructor 0x00498D78..0x00498DBF releases the handles through 0x00050ED3 and the string through 0x00036410. Vector-base calls 0x00498E66/0x00498E74 construct twelve-byte headers/+0x2C/+0x38; destructor calls 0x00498D67/0x00498D73 destroy them through vector<AsciiString> body 0x0002CC70. Their storage remains opaque. Constructor 0x00498E83..0x00498E9A writes bool/+8, unsigned words/+0xC/+0x10, bool/+0x18; 0x00498F0B/0x00498F11 write the final words/+0x44/+0x48.
// Target facts and names: FieldParse 0x00BF19F8..0x00BF1AC8 names OpenByDefault/+8, ResetTimeInMilliseconds/+0xC, PercentOpenForPathing/+0x10, Proxy/+0x14, RepelCollidingUnits/+0x18, GeometryForOpen/+0x2C, GeometryForClosed/+0x38, SoundOpeningGateLoop/+0x1C, SoundFinishedOpeningGate/+0x20, SoundClosingGateLoop/+0x24, SoundFinishedClosingGate/+0x28, TimeBeforePlayingOpenSound/+0x44 and TimeBeforePlayingClosedSound/+0x48. The last two use parseDurationUnsignedInt (0x00338B30). Rowed buildFieldParse 0x00253F0E registers this table; the factory passes that parser at 0x00253F56. These static methods, the constructor and the virtual destructor remain out of line. GateProxy constructor 0x0024E359 calls this constructor, then installs its distinct table 0x00BEF380 at 0x0024E361; its destructor 0x00254045 jumps to 0x00498D46. Zero Hour has no declaration for this class; names are established by the target table and ledger.
#pragma once

#ifndef BFME2_GATEOPENANDCLOSEBEHAVIORMODULEDATA_H
#define BFME2_GATEOPENANDCLOSEBEHAVIORMODULEDATA_H

#include "../../Common/ModuleData.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../Common/OpaqueRefElement4.h"

class INI;
class MultiIniFieldParse;
struct FieldParse;

class GateOpenAndCloseBehaviorModuleData : public ModuleData
{
public:
    GateOpenAndCloseBehaviorModuleData();
    virtual ~GateOpenAndCloseBehaviorModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);
    static const FieldParse m_fieldParse[];

    bool m_openByDefault;
    unsigned int m_resetTimeInMilliseconds;
    unsigned int m_percentOpenForPathing;
    AsciiString m_proxy;
    bool m_repelCollidingUnits;
    OpaqueRefElement4 m_soundOpeningGateLoop;
    OpaqueRefElement4 m_soundFinishedOpeningGate;
    OpaqueRefElement4 m_soundClosingGateLoop;
    OpaqueRefElement4 m_soundFinishedClosingGate;
    unsigned int m_geometryForOpen[3];
    unsigned int m_geometryForClosed[3];
    unsigned int m_timeBeforePlayingOpenSound;
    unsigned int m_timeBeforePlayingClosedSound;
};

typedef char GateOpenAndCloseBehaviorModuleDataSizeCheck[sizeof(GateOpenAndCloseBehaviorModuleData) == 0x4C ? 1 : -1];

#endif
