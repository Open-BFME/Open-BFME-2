// Target facts (code addresses are RVAs; vftables are VAs):
// The constructor 0x00477F06 builds on OpenContain's 0x004649F8 and the
// destructor 0x00478067 ends in OpenContain's 0x00464692; the deleting
// destructor 0x0047860D sits in slot 0 of the 28-slot primary 0x00C461F8,
// and friend_newModuleInstance 0x0024BA5B allocates 0x9E0 bytes.
// GarrisonContain's own tables are 0x00C461F8 (+0), 0x00C46560 (+0x10),
// 0x00C46080 (+0x20), 0x00C463D8 (+0x2C) and 0x00C46034 (+0x30); at +0x0C,
// +0x24, +0x28 and +0x34 it keeps OpenContain's 0x00C43528, 0x00C46064,
// 0x00C46F78 and 0x00C48B28.
// Against OpenContain's tables it overrides primary slots 3 (0x00478260),
// 4 (0x0047801C), 5 (0x004787B0) and 18 (0x00479395) and adds slot 27
// (0x00479292); update (0x00479643); contain slots 20 (0x00479432), 22
// (0x00478C2C), 23 (0x00478D0A), 38 (0x00478699) and 76 (0x00478547);
// damage slot 2 (0x0047876A) and exit slot 2 (0x0047983A), each rowed under
// GarrisonContain's name. Slots it overrides with bodies rowed under other
// names stay OpenContain's here: primary 1 (0x004783D7,
// Rva004697E1Contain::rva004783D7) and 2 (the name getter), and contain
// slots 4, 7, 19, 21, 42, 45, 50 and 77/78 (the two rowed
// attemptBestFirePointPosition overloads, which ContainModuleInterface
// spells slot77/slot78).
// Layout (the byte-matched GarrisonContain.cpp view): the team ID at +0xFC,
// point records +0x100..+0x420, the in-use count at +0x420, the three
// conditions' 12-byte points +0x424..+0x9C4, their counts at +0x9C4, the exit
// rally point at +0x9D0 and three flags at +0x9DC..+0x9DE.
// Donor facts: Zero Hour's GarrisonContain.h names the class, its
// OpenContain base and the method names the ledger rows carry. The field
// names are the byte-matched GarrisonContain.cpp view's.

#pragma once

#ifndef __BFME2_GARRISONCONTAIN_H_
#define __BFME2_GARRISONCONTAIN_H_

#include "OpenContain.h"

class Weapon;
enum ObjectID;

class GarrisonContain : public OpenContain
{
public:
    GarrisonContain(Thing *thing, const ModuleData *moduleData);
    virtual ~GarrisonContain();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

    // Primary table 0x00C461F8.
    virtual NameKeyType getModuleNameKey() const;              // slot 4, 0x0047801C
    virtual void onObjectCreated();                            // slot 5, 0x004787B0
    virtual int getObjectGarrisonPointIndex(ObjectID id);      // slot 27, 0x00479292

    // UpdateModuleInterface table 0x00C46560 (+0x10).
    virtual UpdateSleepTime update();                          // slot 0, 0x00479643

    // ContainModuleInterface table 0x00C46080 (+0x20).
    virtual void recalcApparentControllingPlayer();            // slot 20, 0x00479432
    virtual void onContaining(Object *obj, bool wasSelected);  // slot 22, 0x00478C2C
    virtual void onRemoving(Object *obj);                      // slot 23, 0x00478D0A
    virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool flag); // slot 38, 0x00478699
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos); // slot 76, 0x00478547

    // DamageModuleInterface table 0x00C463D8 (+0x2C).
    virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState,
        BodyDamageType newState);                              // slot 2, 0x0047876A

    // ExitInterface table 0x00C46034 (+0x30).
    virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor); // slot 2, 0x0047983A

    void rva00478BE0();                                        // 0x00478BE0
    void rva00478FD7();                                        // 0x00478FD7

protected:
    virtual void xfer(Xfer *xfer);                             // slot 3, 0x00478260
    virtual void redeployOccupants();                          // slot 18, 0x00479395

    void loadGarrisonPoints();                                 // 0x0047901B
    void trackTargets();                                       // 0x00478ADB
    int findConditionIndex();                                  // 0x00477E50
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *pos); // 0x00478445
    void removeObjectFromGarrisonPoint(Object *obj, int index); // 0x00477E82
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int index); // 0x00477DA1
    void validateRallyPoint();                                 // 0x00478141
    void healSingleObject(Object *obj, float framesForFullHeal); // 0x004786F8
    void putObjectAtBestGarrisonPoint(Object *obj, Object *target, const Coord3D *targetPos); // 0x004785A2
    void addValidObjectsToGarrisonPoints();                    // 0x0047894C
    void removeInvalidObjectsFromGarrisonPoints();             // 0x0047933C

    unsigned int m_originalTeamID;              // +0xFC
    unsigned int m_garrisonPointData[0xC8];     // +0x100, 0x320 bytes of point records
    int m_garrisonPointsInUse;                  // +0x420
    unsigned int m_garrisonPoint[0x168];        // +0x424, 0x5A0 bytes: three conditions of 12-byte points
    int m_numGarrisonPoints[3];                 // +0x9C4
    float m_exitRallyPoint[3];                  // +0x9D0
    bool m_garrisonPointsInitialized;           // +0x9DC
    bool m_hideGarrisonedStateFromNonallies;    // +0x9DD
    bool m_rallyValid;                          // +0x9DE
};

typedef char GarrisonContainSizeIs0x9E0[sizeof(GarrisonContain) == 0x9E0 ? 1 : -1];

#endif // __BFME2_GARRISONCONTAIN_H_
