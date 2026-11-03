// Target facts (RVAs unless marked VA): constructor 0x0049D162 and destructor 0x0049D1B1, rowed as Rva0049D1B1, both store VA 0x00C5146C at +0; its sole slot is scalar deleting destructor 0x0049D84B. VA 0x00C51470 is a separate ProductionUpdate +0x24 table, stored at 0x0049E096. Allocations at 0x0049D904, 0x0049DB14 and 0x0049FB09 request 0x54 bytes before calling 0x0049D162. The constructor writes dwords +4..+0x30, +0x38, +0x3C, +0x40, +0x48 and +0x4C, bytes +0x34/+0x44, and float zeroes +0x14/+0x18; +0x50..+0x53 has no established member type.
// Target facts: 0x00327C1B returns whether the dword +4 equals 1 or 3; its ledger spelling is bool getProductionObject() const. queueUpgrade 0x0049D867 sets +4=2 and the upgrade pointer +0x0C; queueCreateUnit 0x0049DA34 sets the object pointer +8. Destructor 0x0049D1B1 clears +0x38/+0x48/+0x4C and releases the AsciiString at +0x40 through 0x00036410. Queue insertion 0x0049D526 and removal 0x0049D57F establish next/previous pointers at +0x48/+0x4C.
// Donor facts: Zero Hour ProductionUpdate.h names the MemoryPoolObject base, m_type, m_objectToProduce, m_upgradeToResearch, m_next and m_prev. Its one-slot base agrees with retail; its object/upgrade union and remaining offsets do not describe BFME2. Other field names remain neutral, and rowed constructor/destructor bodies remain out of line.
#pragma once

#ifndef __BFME2_PRODUCTIONENTRY_H_
#define __BFME2_PRODUCTIONENTRY_H_

#include "../../Common/MemoryPoolObject.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class ThingTemplate;
class UpgradeTemplate;

class ProductionEntry : public MemoryPoolObject
{
public:
    ProductionEntry();
    virtual ~ProductionEntry();

    bool getProductionObject() const;

    int m_type;                              // +0x04
    ThingTemplate *m_objectToProduce;                   // +0x08
    const UpgradeTemplate *m_upgradeToResearch;         // +0x0C
    int m_field10;
    float m_field14;
    float m_field18;
    int m_field1C;
    int m_field20;
    int m_field24;
    int m_field28;
    int m_field2C;
    int m_field30;
    unsigned char m_field34;
    int m_field38;
    int m_field3C;
    AsciiString m_field40;
    unsigned char m_field44;
    ProductionEntry *m_next;                  // +0x48
    ProductionEntry *m_prev;                  // +0x4C
    char m_unknown50[4];
};

#endif
