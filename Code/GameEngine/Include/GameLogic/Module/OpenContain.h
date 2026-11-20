// Target facts (code addresses are RVAs; vftables are VAs):
// The constructor 0x004649F8 calls UpdateModule's 0x00253390 and leaves nine
// tables: 0x00C435E8 at +0 (27 primary slots), 0x00C43528 at +0x0C (47
// BehaviorModuleInterface slots), 0x00C43BE8 at +0x10 (3 UpdateModuleInterface
// slots), 0x00C433B0 at +0x20 (94 ContainModuleInterface slots), 0x00C46064 at
// +0x24 (6), 0x00C46F78 at +0x28 (1), 0x00C58790 at +0x2C (3), 0x00C43380 at
// +0x30 (12) and 0x00C48B28 at +0x34 (4). The destructor 0x00464692 restores
// the same nine. The rowed factory news of the contain family (CaveContain's
// 0x0024B797 and its peers) and the constructor's last store (+0xF0, a
// three-word tree) bound the class at 0xFC bytes.
// The +0x0C table's getters return the interfaces at +0x24 (slot 1,
// 0x003730FC), +0x20 (slot 2, 0x004543A9), +0x34 (slot 3, 0x0046644A), +0x2C
// (slot 4, 0x004647C0) and +0x28 (slot 7, 0x004523A9), so +0x24 is the collide
// interface, +0x28 the die interface, +0x2C the damage interface and +0x34
// the create interface. The +0x30 table holds the exit interface's slots
// (exitObjectViaDoor 0x0046525F at 2, exitObjectInAHurry 0x004656DF at 5,
// getNaturalRallyPoint 0x0046363F at 9).
// Primary slots 0-12 are UpdateModule's positions; OpenContain overrides 1
// (0x00463C6E), 3 (0x00465EF1), 4 (0x00464775), 8 (0x00464120) and adds 13-26.
// Slot 2 holds 0x004647BA (the literal name getter), which is rowed as the
// non-virtual ?name@OpenContain@@QBEPBDXZ, so no override is declared there.
// Added slots holding one-instruction bodies shared across classes:
// 14 0x005CB9FA (mov al,1; ret 4), 15 0x0050B238 (ret 8), 16 and 20
// 0x005CB9FF (xor al,al; ret 4), 23 and 25 0x000B3FD0 (ret). Slot 24
// (0x00462E3A, three arguments, ret 0Ch) is rowed only under the placeholder
// ?rva00462E3A@Rva00462E3A@@QAEXPAVObject@@HH@Z and slot 26 (0x00465972) only
// as the non-virtual ?privateRedeployOccupants@OpenContain@@AAE...; both stay
// unnamed positions here.
// Interface slots with no row under OpenContain's name (most of the +0x20
// table, the +0x24 table, the +0x30 table's slots 0, 1, 3, 4, 7, 8, 10 and 11)
// are left to the interfaces' declarations. The +0x34 table's slot 2 (0x000B3FD0)
// is rowed as ?slot02@OpenContain@@UAEXXZ, but ContainModuleInterface's
// void *slot02() takes that name and signature first, so it is not declared.
// Layout: the constructor writes an int at +0x38, constructs three-word trees
// at +0x3C, +0x48, +0x5C and +0xF0, one-word lists at +0x54 and +0x74, the
// 0x4C-byte member at +0x84 (0x00042526, then memset), three floats at
// +0xD0, bytes +0xDC..+0xE1 and ints +0x58, +0x68..+0x70, +0x78..+0x80 and
// +0xE4..+0xEC.
// Donor facts: Zero Hour's OpenContain.h names the class, its UpdateModule,
// ContainModuleInterface, CollideModuleInterface and DieModuleInterface bases,
// and the method names the ledger rows carry. Its field list is not used.

#pragma once

#ifndef __BFME2_OPENCONTAIN_H_
#define __BFME2_OPENCONTAIN_H_

#include "UpdateModule.h"
#include "ContainModule.h"
#include "../../Common/CollideModuleInterface.h"
#include "DieModuleInterface.h"
class DamageInfo;
#include "DamageModuleInterface.h"
#include "ExitInterface.h"
#include "CreateModuleClass.h"

class INI;
class Module;
class ModuleData;
class Object;
class Thing;
class Xfer;
struct Coord3D;
enum BodyDamageType;
enum ExitDoorType;
enum NameKeyType;
enum UpdateSleepTime;

class OpenContain : public UpdateModule, public ContainModuleInterface, public CollideModuleInterface,
    public DieModuleInterface, public DamageModuleInterface, public ExitInterface, public CreateModuleInterface
{
public:
    OpenContain(Thing *thing, const ModuleData *moduleData);
    virtual ~OpenContain();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static ModuleData *friend_newModuleData(INI *ini);

    // Primary table 0x00C435E8.
    virtual NameKeyType getModuleNameKey() const;              // slot 4, 0x00464775
    virtual void onDelete();                                   // slot 8, 0x00464120
    virtual void removeFromContainList(Object *obj);           // slot 13, 0x00462F75
    virtual bool vslot14(int) { return true; }                 // slot 14, 0x005CB9FA
    virtual void vslot15(int, int) { }                         // slot 15, 0x0050B238
    virtual bool vslot16(int) { return false; }                // slot 16, 0x005CB9FF
protected:
    virtual void monitorConditionChanges();                    // slot 17, 0x00462C72
    virtual void redeployOccupants();                          // slot 18, 0x00464286
public:
    virtual bool rva00464EE7(Object *obj);                     // slot 19, 0x00464EE7
    virtual bool vslot20(int) { return false; }                // slot 20, 0x005CB9FF
protected:
    virtual void doLoadSound();                                // slot 21, 0x0046279C
    virtual void doUnloadSound();                              // slot 22, 0x0046282B
public:
    virtual void vslot23() { }                                 // slot 23, 0x000B3FD0
    virtual void vslot24(Object *, int, int) = 0;              // slot 24, 0x00462E3A
    virtual void vslot25() { }                                 // slot 25, 0x000B3FD0
    virtual void vslot26(const void *, void *) = 0;            // slot 26, 0x00465972

    // BehaviorModuleInterface table 0x00C43528 (+0x0C).
    virtual CollideModuleInterface *getCollide();              // slot 1, 0x003730FC
    virtual ContainModuleInterface *getContain();              // slot 2, 0x004543A9
    virtual CreateModuleInterface *getCreate();                // slot 3, 0x0046644A
    virtual DamageModuleInterface *getDamage();                // slot 4, 0x004647C0
    virtual DieModuleInterface *getDie();                      // slot 7, 0x004523A9

    // UpdateModuleInterface table 0x00C43BE8 (+0x10).
    virtual UpdateSleepTime update();                          // slot 0, 0x004640BE

    // ContainModuleInterface table 0x00C433B0 (+0x20).
    virtual void containReactToTransformChange();              // slot 3, 0x004624E3
    virtual void onContaining(Object *obj, bool wasSelected);  // slot 22, 0x00463097
    virtual void onRemoving(Object *obj);                      // slot 23, 0x00464D02
    virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool flag); // slot 38, 0x00462977
    virtual void addToContain(Object *obj);                    // slot 39, 0x00464830
    virtual void addToContainList(Object *obj);                // slot 40, 0x004638F1
    virtual void removeAllContained(bool exposeStealthUnits = false); // slot 42, 0x004635C0
    virtual Object *getClosestRider(const Coord3D *pos);       // slot 61, 0x004632E0

    // DieModuleInterface table 0x00C46F78 (+0x28).
    virtual void onDie(const DamageInfo *damageInfo);          // slot 0, 0x004641B1

    // DamageModuleInterface table 0x00C58790 (+0x2C).
    virtual void onDamage(DamageInfo *damageInfo);             // slot 0, 0x0047A69C
    virtual void onHealing(DamageInfo *damageInfo);            // slot 1, 0x0047A69C
    virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState,
        BodyDamageType newState);                              // slot 2, 0x000D1407

    // ExitInterface table 0x00C43380 (+0x30).
    virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor); // slot 2, 0x0046525F
    virtual void exitObjectInAHurry(Object *newObj);           // slot 5, 0x004656DF
    virtual bool getNaturalRallyPoint(Coord3D &rallyPoint, bool offset = true) const; // slot 9, 0x0046363F
    // Slot 10 holds OpenContain's own body 0x004624C1, rowed only under the placeholder
    // ?rva004624C1@Rva004624C1@@QAE_NPAURva00597372Triple@@PAM@Z; nothing defines
    // ExitInterface's default, so the position stays unbound here.
    virtual bool getExitPosition(Coord3D &exitPosition, float &exitAngle) const = 0; // slot 10, 0x004624C1

    // CreateModuleInterface table 0x00C48B28 (+0x34).
    virtual void onCreate();                                   // slot 0, 0x000B3FD0
    virtual void onBuildComplete();                            // slot 1, 0x000B3FD0
    virtual bool shouldDoOnBuildComplete() const;              // slot 3, 0x0047A699

    void rva00462F34();                                        // 0x00462F34
    void privateRemoveFromContain(Object *obj, bool exposeStealthUnits); // 0x00462FB3

protected:
    virtual void loadPostProcess();                            // slot 1, 0x00463C6E
    virtual void xfer(Xfer *xfer);                             // slot 3, 0x00465EF1

    int m_38;
    unsigned int m_opaque3C[3];     // tree constructed by the rowed 0x0033C432 spelling
    unsigned int m_opaque48[3];     // tree keyed by object ID (0x00286852 family)
    unsigned int m_opaque54;        // list (0x004EC36C spelling)
    int m_58;
    unsigned int m_opaque5C[3];     // tree, as at +0x3C
    int m_68;
    int m_6C;
    int m_70;
    unsigned int m_opaque74;        // list, as at +0x54
    int m_78;
    int m_7C;
    int m_80;
    unsigned int m_opaque84[0x13];  // 0x4C bytes, constructed by 0x00042526
    float m_D0;
    float m_D4;
    float m_D8;
    unsigned char m_DC;
    unsigned char m_DD;
    unsigned char m_DE;
    unsigned char m_DF;
    unsigned char m_E0;
    unsigned char m_E1;
    int m_E4;
    int m_E8;
    int m_EC;
    unsigned int m_opaqueF0[3];     // tree, constructed in the constructor body
};

typedef char OpenContainSizeIs0xFC[sizeof(OpenContain) == 0xFC ? 1 : -1];

#endif // __BFME2_OPENCONTAIN_H_
