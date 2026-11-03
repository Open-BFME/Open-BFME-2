// Target facts (code addresses are RVAs, table addresses are VAs): constructors 0040C351 and 0040D688 call CarryoverUnit at 0037DF2C and 001EB79E, then initialize the secondary base at +AC through BC6F20 and zero +B0. Both install C3944C at +0 and C3945C at +AC; the default constructor installs the secondary table first, the copy constructor installs the primary first. Destructor 0040C39E restores both derived tables, then BC6F20 at +AC, and jumps to CarryoverUnit destructor 0037DEE4. Adjustor 0040C5D3 subtracts AC and jumps to deleting destructor 0040C5DE, proving secondary-base inheritance.
// C3944C has exactly four slots: deleting destructor 0040C5DE, loadPostProcess 000B3FD0, const GetSnapshotName 0040C586, xfer 0040C4FE. C3945C has one slot, adjustor 0040C5D3, followed by the ArmySummaryEntry literal at C39460. Rva0007DF07 constructor 0007DF07 and destructor 004E84A4 establish its BC6F20 table and word +4; its original class name remains unknown. Allocation 0040F083 pushes C8, allocator call 0040F088 feeds constructor call 0040F09B; copy allocation 0040EA53 likewise feeds 0040EA6E. The complete object is C8 bytes, with CarryoverUnit occupying AC and Rva0007DF07 occupying 8.
// Constructors 0040C351/0040D688 and equality 0040C3BB prove dwords +B4/+B8/+BC/+C0 and bytes +C4/+C5; xfer 0040C4FE passes both bytes to the bool-transfer slot. Out-of-line API rows are Parse 0040C5FA, MarkForUpgrades 0040C430, CancelUpgrades 0040C45C, ApplyWorldMapUpgrades 0040C6A5, rva0040C495 0040C495 and rva0040C3BB 0040C3BB. Constructors, copy constructor and virtual destructor remain declarations so callers use their rowed bodies. Tail field names identify offsets only; the registered base headers supply the inherited layout and methods.
#pragma once

#ifndef BFME2_ARMYSUMMARYENTRY_H
#define BFME2_ARMYSUMMARYENTRY_H

#include "../GameLogic/CarryoverUnit.h"
#include "Rva0007DF07.h"

class INI;
class Rva004E0632;

class ArmySummaryEntry : public CarryoverUnit, public Rva0007DF07
{
public:
    ArmySummaryEntry();
    ArmySummaryEntry(const ArmySummaryEntry &);
    virtual ~ArmySummaryEntry();

    bool hasUpgrade() const { return m_bc != 0; }
    int getMoveTarget() const { return m_b8; }

    void Parse(INI *);
    void MarkForUpgrades(const Rva004E0632 *);
    void CancelUpgrades();
    void ApplyWorldMapUpgrades();
    Object *rva0040C495(Player *, int);
    bool rva0040C3BB(const ArmySummaryEntry *);

protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);

public:
    int m_b4;
    int m_b8;
    int m_bc;
    int m_c0;
    bool m_c4;
    bool m_c5;
};

typedef char ArmySummaryEntrySizeCheck[sizeof(ArmySummaryEntry) == 0xC8 ? 1 : -1];

#endif
