// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x004A8201 calls UpdateModule at 0x00253390, installs tables 0x00C5386C at +0, 0x00C5A260 at +0x0C, 0x00C53860 at +0x10 and 0x00C53848 at +0x20. The temporary +0x20 table 0x00C40818 is the pure interface constructor table. Destructor 0x004A8091 restores the same four final tables and jumps to UpdateModule::~UpdateModule at 0x0024A797; its later 0x00BEEA7C and 0x00BEE9C0 stores are inlined BehaviorModule destruction. Scalar deleting destructor 0x004A829E calls 0x004A8091. Factory 0x0024F080 allocates 0x58 at 0x0024F08B and calls the constructor at 0x0024F0A7: sizeof is 0x58, UpdateModule occupies +0..+0x1F and CollideModuleInterface occupies +0x20..+0x23.
// Target facts: 0x00C5386C has UpdateModule's 13 primary slots, with slots 0..4 at 0x004A829E, 0x00497805, 0x004A80B1, 0x004A86E7 and 0x004A812E; slot 12 remains 0x0022C4CB. The +0x10 table has update 0x004A878F, getDisabledTypesToProcess 0x00253376 and wake 0x0044DF8D. The +0x20 table has six slots before that table: onCollide 0x004A82F5 (this is +0x20, ret 12), slot01 0x005CB9FF (false, ret 4) and four 0x0047A699 slots (false, ret); it has no virtual destructor. Behavior table slot 1 is 0x004543A9 (interface this +0x14) and slot 9 is 0x002533D3 (interface this +4). Constructor stores and xfer 0x004A86E7 establish floats +0x24/+0x28, Coord3D +0x2C, four-byte state +0x38, floats +0x3C/+0x40, int +0x44, bool +0x48, uint +0x4C, ObjectID +0x50 and float +0x54; getter 0x004A8125 compares state with zero. applyTopplingForce 0x004A83D7 and update 0x004A878F corroborate those fields. Factory, constructor, update, applyTopplingForce, getModuleNameKey and isAbleToBeToppled have ledger owners; all are declared out of line.
// Donor facts: Zero Hour GeneralsMD ToppleUpdate.h and ToppleUpdate.cpp name the bases, onCollide, the ToppleState values and members through +0x50; retail xfer and the apply/update bodies establish their BFME2 placement. Zero Hour's seven collision slots do not identify which slot BFME2 removed, so only onCollide is named. The BFME2-only float at +0x54 has a neutral name. The registered UpdateModule header supplies the primary slots and inherited interfaces.

#pragma once

#ifndef __BFME2_TOPPLEUPDATECLASS_H_
#define __BFME2_TOPPLEUPDATECLASS_H_

#include "UpdateModule.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectID;

class CollideModuleInterface
{
public:
    virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
    virtual bool slot01(const Object *other) const = 0;
    virtual bool slot02() const = 0;
    virtual bool slot03() const = 0;
    virtual bool slot04() const = 0;
    virtual bool slot05() const = 0;
};

class ToppleUpdate : public UpdateModule, public CollideModuleInterface
{
public:
    ToppleUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~ToppleUpdate();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

    virtual NameKeyType getModuleNameKey() const;
    virtual CollideModuleInterface *getCollide();
    virtual UpdateSleepTime update();
    virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
    virtual bool slot01(const Object *other) const;
    virtual bool slot02() const;
    virtual bool slot03() const;
    virtual bool slot04() const;
    virtual bool slot05() const;

    void applyTopplingForce(const Coord3D *toppleDirection, float toppleSpeed, unsigned int options);
    bool isAbleToBeToppled() const;

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

    enum ToppleState
    {
        TOPPLE_UPRIGHT = 0,
        TOPPLE_FALLING,
        TOPPLE_DOWN
    };

    float m_angularVelocity; // +0x24
    float m_angularAcceleration; // +0x28
    Coord3D m_toppleDirection; // +0x2C
    ToppleState m_toppleState; // +0x38
    float m_angularAccumulation; // +0x3C
    float m_angleDeltaX; // +0x40
    int m_numAngleDeltaX; // +0x44
    bool m_doBounceFX; // +0x48
    unsigned int m_options; // +0x4C
    ObjectID m_stumpID; // +0x50
    float m_field54; // +0x54
};

#endif
