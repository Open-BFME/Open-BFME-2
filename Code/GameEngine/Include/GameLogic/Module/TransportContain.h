// Target facts (code addresses are RVAs; vftables are VAs):
// The constructor 0x00468559 builds on OpenContain's 0x004649F8, installs
// the +0xFC interface's own table, then TransportContain's ten tables; the
// destructor 0x00467E61 ends in OpenContain's 0x00464692; the deleting
// destructor 0x00468029 is slot 0 of the 31-slot primary 0x00C44278; and
// friend_newModuleInstance 0x0024B861 allocates 0x11C bytes.
// Its own tables are 0x00C44278 (+0), 0x00C441B8 (+0x0C), 0x00C441A8
// (+0x10), 0x00C44030 (+0x20), 0x00C43FFC (+0x30), 0x00C45CEC (+0x34) and
// 0x00C47834 (+0xFC, the registered TransportExtra's one slot); +0x24,
// +0x28 and +0x2C keep OpenContain's 0x00C46064, 0x00C46F78 and 0x00C58790.
// Against OpenContain's tables, the overrides rowed under TransportContain's
// name are primary slots 3 (0x00466DBC) and 4 (0x00467EE1), the added slots
// 27 (0x004671AC), 29 (0x0046740C) and 30 (0x0046760D), update
// (0x00468749), exit slot 0 (0x00466DA9) and the +0xFC slot (0x00466FE0).
// Overrides whose rows do not spell an override of the slot stay
// OpenContain's: primary 1 (0x004783D7, Rva004697E1Contain), 2 (the name
// getter), 9 and contain 24 (0x004672B7/0x00467F33, rowed onCapture(int,
// int) where ObjectModule declares onCapture(Player *, Player *)), 14
// (0x00466E58) and 25 (0x00467F3B, rowed killRidersWhoAreNotFreeToExit,
// which OpenContain.h still spells vslot25); +0x0C slot 45; contain slots
// 22, 23, 27, 28, 38 (rowed slot38(Object *, int, int)), 50, 51, 59 and 60
// (rowed rva004673C0); exit slot 1; create slot 1. Added slot 28
// (0x004670D6) is rowed only as the non-virtual createPayload, so it stays
// a pure position.
// Layout: three ints at +0x100..+0x108 and a bool at +0x10C, cleared by the
// constructor, and the three-word name vector at +0x110 it fills from the
// module data's payload list.
// Donor facts: Zero Hour's TransportContain.h names the class, its
// OpenContain base and the method names the ledger rows carry.

#pragma once

#ifndef __BFME2_TRANSPORTCONTAIN_H_
#define __BFME2_TRANSPORTCONTAIN_H_

#include "OpenContain.h"
#include "../../Common/TransportExtra.h"

class PayloadContainView;
class ThingTemplate;

class TransportContain : public OpenContain, public TransportExtra
{
public:
    TransportContain(Thing *thing, const ModuleData *moduleData);
    virtual ~TransportContain();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

    // Primary table 0x00C44278.
    virtual NameKeyType getModuleNameKey() const;              // slot 4, 0x00467EE1
protected:
    virtual bool isSpecificRiderFreeToExit(Object *obj);       // slot 27, 0x004671AC
public:
    virtual void vslot28() = 0;                                // slot 28, 0x004670D6
protected:
    virtual void rva0046740C();                                // slot 29, 0x0046740C
    virtual void letRidersUpgradeWeaponSet();                  // slot 30, 0x0046760D
public:

    // UpdateModuleInterface table 0x00C441A8 (+0x10).
    virtual UpdateSleepTime update();                          // slot 0, 0x00468749

    // ExitInterface table 0x00C43FFC (+0x30).
    virtual bool isExitBusy() const;                           // slot 0, 0x00466DA9

    // TransportExtra table 0x00C47834 (+0xFC).
    virtual Object *createPayloadMember(const ThingTemplate *what, PayloadContainView *contain,
        Object *parent, const char *name, int index);          // slot 0, 0x00466FE0

    void createPayload();                                      // 0x004670D6
    void UpdateUpgradeCreationTriggers();                      // 0x00468045

protected:
    virtual void xfer(Xfer *xfer);                             // slot 3, 0x00466DBC

    int m_100;
    int m_104;
    int m_108;
    bool m_10C;
    unsigned int m_opaque110[3];    // the payload name vector
};

typedef char TransportContainSizeIs0x11C[sizeof(TransportContain) == 0x11C ? 1 : -1];

#endif // __BFME2_TRANSPORTCONTAIN_H_
