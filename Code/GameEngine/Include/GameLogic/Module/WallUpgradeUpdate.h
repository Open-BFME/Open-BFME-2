// Target facts (code addresses are RVAs; table addresses are VAs): factory 0x0024F2EF allocates 0x34 at 0x0024F2FA and calls constructor 0x004AB317 at 0x0024F316. The constructor calls UpdateModule 0x00253390, whose fields end at +0x20, then installs tables 0x00C54780/+0, 0x00C49800/+0x0C, 0x00C54774/+0x10, 0x00C54768/+0x20 and 0x00C54764/+0x24. Destructor 0x004AB246 (rowed as Rva004AB246) restores those same tables and jumps to UpdateModule destruction 0x0024A797; its later BehaviorModule table stores destroy the parent. The earlier constructor stores 0x00BE2B78/+0x20 and 0x00C1C780/+0x24 construct the interfaces, not the complete class.
// The primary table has 13 slots: 0=deleting destructor 0x004AB392 (calls 0x004AB246), 1=loadPostProcess 0x00497805 (jumps to 0x0058B03E), 2=name getter 0x004AB26D (returns "WallUpgradeUpdate" at 0x00BF4F30), 3=xfer 0x004AB273, 4=getModuleNameKey 0x004AB2D2, 5-8=0x000B3FD0, 9=0x0050B238, 10-11=0x000D43D0, 12=0x0022C4CB. The 47-slot +0x0C table changes getDamage (slot 4, 0x004543A9, returns complete +0x20) and retains getUpdate (slot 9, 0x002533D3). The +0x10 table has update 0x004AB4D8 and the parent's two other slots. The +0x20 table is DamageModuleInterface's: two ret-4 slots (0x0047A69C, empty onDamage and onHealing) then onBodyDamageStateChange 0x004AB3EB; the +0x24 table has only bool rva004AB3AE 0x004AB3AE, and that interface's name is a neutral placeholder.
// Constructor writes 0 to dwords +0x28/+0x2C and 1/0 to bytes +0x30/+0x31. xfer 0x004AB273 transfers +0x28 through XferObjectID 0x003060B2, +0x2C through the int slot and +0x30/+0x31 through the bool slot. scanForBuildingAndPossess 0x004AB415 reads/writes +0x28; update 0x004AB4D8 reads signed +0x2C and both flags with a +0x10 receiver; onBodyDamageStateChange 0x004AB3EB writes complete +0x2C with a +0x20 receiver. The static lookup 0x004AB1F5 uses the same class-name literal; GeometryUpgrade 0x004B6C8A calls lookup and rva004AB57E out of line. The constructor, destructor and rowed methods are declared out of line.

#pragma once
#ifndef __BFME2_WALLUPGRADEUPDATE_H_
#define __BFME2_WALLUPGRADEUPDATE_H_

#include "UpdateModule.h"
#include "DamageModuleClass.h"

class DamageInfo;
enum BodyDamageType;
enum ObjectID;

class WallUpgradeUpdateInterface24
{
public:
    virtual bool rva004AB3AE() = 0;
};

class WallUpgradeUpdate : public UpdateModule,
    public DamageModuleInterface, public WallUpgradeUpdateInterface24
{
public:
    WallUpgradeUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~WallUpgradeUpdate();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static Module *rva004AB1F5(Object *object);
    virtual NameKeyType getModuleNameKey() const;
    virtual DamageModuleInterface *getDamage() { return this; }
    virtual UpdateSleepTime update();
    virtual void onDamage(DamageInfo *damageInfo) { }
    virtual void onHealing(DamageInfo *damageInfo) { }
    virtual void onBodyDamageStateChange(const DamageInfo *damageInfo,
        BodyDamageType oldState, BodyDamageType newState);
    virtual bool rva004AB3AE();

    void scanForBuildingAndPossess();
    void rva004AB57E();

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

private:
    ObjectID m_28;
    int m_2C;
    bool m_30;
    bool m_31;
};

#endif
