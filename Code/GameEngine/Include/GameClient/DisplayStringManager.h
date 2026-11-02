// Target facts (code addresses are RVAs; tables are VAs): constructor 0x00262002 calls SubsystemInterface 0x001B4E63, clears dwords +0x0C/+0x10 and installs 0x00BF9010; destructor 0x0026201C restores that same table and tail-calls ~SubsystemInterface 0x001B4E74. These lifecycle rows are named Rva0026201C in the ledger. The parent's constructor clears byte +4 and the string pointer +8; its destructor releases the string through 0x00036410. W3D constructor 0x00090360 calls 0x00262002, installs 0x00BC7E20 and begins its own ten-pointer array at +0x14, bounding this base to 0x14 bytes; caller 0x0004C55E allocates 0x40 bytes for W3DDisplayStringManager.
// Table 0x00BF9010 has 18 slots, ending at non-code 0x00BF9058: 0 deleting destructor 0x00262077; 1/3/8/9/10/12 empty 0x000B3FD0; 2 loadIniFilesFromLegend 0x001B5384; 4/11 false-ret-4 0x005CB9FF; 5 false 0x0047A699; 6 zero 0x000D43D0; 7/13 ret-4 0x0047A69C; 14-17 purecall 0x0003B810. The registered parent's BFME_SUBSYSTEM_SLOTS form supplies slots 0-13 (parent table 0x00BD77A0). W3D table 0x00BC7E20 ends at text 0x00BC7E68 and proves slots 14 newDisplayString 0x000905F0, 15 freeDisplayString 0x00090381, 16 getGroupNumeralString 0x00090417 and 17 getFormationLetterString (folded +0x3C getter 0x005C4AF1); reset/update/postProcessLoad occupy inherited slots 9/10/3. Retail callers 0x000747E5 and 0x004E624D load TheDisplayStringManager at VA 0x00DFEAD8 and dispatch through +0x38/+0x3C.
// link 0x00262027 reads/writes the head at +0x0C and DisplayString links at +0x0C/+0x10; unLink 0x00262045 updates that head and those links. W3D freeDisplayString 0x00090381 calls unLink and clears matching checkpoint +0x10. Names, protected list fields and helper access follow Zero Hour GeneralsMD DisplayStringManager.h, corroborated by these bodies; the link ledger row proves its protected declaration. Constructor, destructor and unLink are declared out of line; their existing placeholder owners require identity reconciliation before those spellings can resolve.

#pragma once

#ifndef __DISPLAYSTRINGMANAGER_H_
#define __DISPLAYSTRINGMANAGER_H_

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class DisplayString;

class DisplayStringManager : public SubsystemInterface
{
public:
    DisplayStringManager();
    virtual ~DisplayStringManager();

    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}

    virtual DisplayString *newDisplayString() = 0;
    virtual void freeDisplayString(DisplayString *string) = 0;
    virtual DisplayString *getGroupNumeralString(int numeral) = 0;
    virtual DisplayString *getFormationLetterString() = 0;

protected:
    void link(DisplayString *string);
    void unLink(DisplayString *string);

    DisplayString *m_stringList;
    DisplayString *m_currentCheckpoint;
};

extern DisplayStringManager *TheDisplayStringManager;

#endif
