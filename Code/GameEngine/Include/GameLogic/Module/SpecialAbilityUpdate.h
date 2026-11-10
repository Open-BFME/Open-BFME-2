// Target facts (code addresses are RVAs; table addresses are VAs):
// 0x0024A847 allocates 0x88 bytes and calls 0x0044EF5E (rowed Rva0044EF5E).
// 0x0044EF76 calls UpdateModule (0x00253390); its 0x20-byte layout is inherited.
// 0x0044EF7E first installs the interface construction table 0x00C6F248 at +0x20;
// 0x0044EF89..0x0044EF9D install the complete-class tables 0x00C3FBA8 at +0,
// 0x00C4D640 at +0x0C, 0x00C4DEE8 at +0x10 and 0x00C552A4 at +0x20.
// 0x00451F56..0x00451F6A restore those same four complete-class tables.
// 0x00451F79 calls onExit(true,true), 0x00451F85 destroys list<int> at +0x64,
// and 0x00451F90 calls UpdateModule's destructor (0x0024A797). Its later
// BehaviorModule table stores are base teardown, not SpecialAbilityUpdate tables.
// 0x00C3FBA8 has 23 slots, followed by zero at 0x00C3FC04: inherited slots
// 0..12, then onExit (0x004502CE), 0x00450AE9, startPreparation (0x00450D9A),
// continuePreparation (0x0044FC52), triggerAbilityEffect (0x0045108D), a +0x2C
// clearer (0x004C12CB), finishAbility (0x00451B92), 0x0044F0B3, startPacking
// (0x00450635) and startUnpacking (0x004508B7). Destructor 0x00451F45 and
// deleting destructor 0x004522F0 are out of line; the latter occupies slot 0.
// 0x00C4D640 has 47 BehaviorModuleInterface slots: 9 returns the update
// interface (0x002533D3), 25 returns +0x20 (0x004543A9), and the rest agree
// with BehaviorModule. 0x00C4DEE8 has update (0x00451FA2), disabled-mask getter
// (0x004A2D67) and wake (0x0044DF8D); update receives this at +0x10.
// 0x00C552A4 has nine slots before the next stored table at 0x00C552C8:
// initiateIntentToDoSpecialPower (0x004500A3, this at +0x20, ret 20), true
// (0x0050B5C6), byte +0x74 (0x005C4AE5), zero (0x000D43D0), false
// (0x0047A699), ret 4 (0x0047A69C), 0x0044EECA (ret 4), 0x0044F09F
// (ret 4) and 0x0044EDA6 (ret 4); SpecialPowerUpdateInterface.h names them.
// 0x0044EFA4..0x0044F037 write dwords +0x24..+0x40, floats +0x44..+0x58,
// dwords +0x5C/+0x60, the list anchor +0x64, dwords +0x68/+0x6C, float +0x70,
// byte +0x74, dword +0x78, bytes +0x7C..+0x83 and dword +0x84.
// Named out-of-line helpers: getSpecialPowerType 0x0044EF2C, rva0044EE07
// 0x0044EE07, rva0044EE80 0x0044EE80, killSpecialObjects 0x0044F72E,
// validateSpecialObjects 0x0044F7A4, endPreparation 0x0044F81E, initLaser
// 0x0044FB28, isWithinStartAbilityRange 0x0044F28E, isWithinAbilityAbortRange
// 0x0044F4F7, rva0044F679 0x0044F679, rva0044F6D0 0x0044F6D0, rva0044F881
// 0x0044F881, rva0044E85E 0x0044E85E and rva0044FEB6 0x0044FEB6.
// getModuleNameKey is rowed at 0x0044F054; xfer is rowed at 0x0044F996.
// Donor facts: Zero Hour SpecialPowerUpdateModule.h names the extra interface
// and its overridden slots. BFME2's four vptr offsets come from retail above.
// Zero Hour also names m_animFrames, m_packingState, m_prepFrames, m_targetID,
// m_targetPos, m_active, m_noTargetCommand, m_withinStartAbilityRange and
// m_specialObjectIDList, and types m_targetID as ObjectID. Retail intent
// (0x004500A3) stores the target, command flags and packing state; preparation
// (0x00450D9A) sets the preparation timer; packing (0x00450635) sets the
// animation timer. The active getter above reads +0x74; range checking
// (0x0044F28E) reads +0x80. Other field names are neutral.

#pragma once
#ifndef __BFME2_SPECIALABILITYUPDATE_H_
#define __BFME2_SPECIALABILITYUPDATE_H_

#include "UpdateModule.h"
#include "SpecialPowerUpdateInterface.h"
#include "../../Common/BitFlags11.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class SpecialPowerTemplate;
class Waypoint;
class CommandButton;
enum SpecialPowerType;
enum ObjectID;

class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
    SpecialAbilityUpdate(Thing *, const ModuleData *);
    virtual ~SpecialAbilityUpdate();
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);

    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    // 0x004A2D67, folded with AIUpdateInterface's: bit 3.
    virtual DisabledMaskType getDisabledTypesToProcess() const
    {
        return DisabledMaskType(DisabledMaskType::kInit, 3);
    }
    // 0x004543A9, from the +0x0C interface: the +0x20 interface, null-checked.
    virtual void *slot25() { return static_cast<SpecialPowerUpdateInterface *>(this); }
    virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *, const Object *,
        const Coord3D *, unsigned int, const Waypoint *);
    // Retail's one-instruction bodies at +0x20: 0x0050B5C6 (mov al,1), 0x005C4AE5 (the byte at +0x74),
    // 0x000D43D0 (xor eax,eax), 0x0047A699 (xor al,al) and 0x0047A69C (ret 4), most of them folded with other classes'.
    virtual bool isSpecialAbility() const { return true; }
    virtual bool isActive() const { return m_active; }
    virtual CommandOption getCommandOption() const { return (CommandOption)0; }
    virtual bool doesSpecialPowerHaveOverridableDestinationActive() const { return false; }
    virtual void setSpecialPowerOverridableDestination(const Coord3D *) {}
    virtual bool isPowerCurrentlyInUse(const CommandButton *) const;
    virtual bool vslot07(int);
    virtual bool vslot08(int);

protected:
    virtual void onExit(bool, bool);
public:
    virtual bool rva00450AE9(); // slot 14, 0x00450AE9
    virtual void startPreparation();
    virtual bool continuePreparation();
    virtual void triggerAbilityEffect();
    virtual void vslot18() { m_2C = 0; } // 0x004C12CB: and [ecx+0x2c],0
    virtual void finishAbility();
protected:
    virtual bool handlePackingProcessing(); // slot 20, 0x0044F0B3
public:
    virtual void startPacking(bool);
    virtual void startUnpacking();

    SpecialPowerType getSpecialPowerType() const;
    bool rva0044E85E(Coord3D *, float);
    void rva0044EE07();
    void rva0044EE80();
    void killSpecialObjects();
    Object *rva0044FEB6();
    bool rva0044F679();
    void rva0044F6D0();
    UpdateSleepTime rva0044F881();

protected:
    virtual void loadPostProcess() { UpdateModule::loadPostProcess(); } // 0x00497805, a jmp to UpdateModule's
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const { return "SpecialAbilityUpdate"; } // 0x0044F099
#endif
    virtual void xfer(Xfer *);
    void validateSpecialObjects();
    void endPreparation();
    bool initLaser(Object *, Object *);
    bool isWithinStartAbilityRange();
    bool isWithinAbilityAbortRange() const;

    int m_24;
    unsigned int m_animFrames;
    unsigned int m_2C;
    unsigned int m_packingState;
    unsigned int m_34;
    unsigned int m_38;
    unsigned int m_prepFrames;
    ObjectID m_targetID;
    Coord3D m_targetPos;
    Coord3D m_50;
    int m_5C;
    int m_60;
    // STLport's list where the unit included it (every unit that touches the list or destroys it does);
    // elsewhere the same four bytes stay opaque, so non-STLport includers compile unchanged (AI.h's form).
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<int> m_specialObjectIDList;
#else
    unsigned int m_opaque64;
#endif
    unsigned int m_68;
    unsigned int m_6C;
    float m_70;
    bool m_active;
    unsigned int m_78;
    bool m_7C;
    bool m_noTargetCommand;
    bool m_7E;
    bool m_7F;
    bool m_withinStartAbilityRange;
    bool m_81;
    bool m_82;
    bool m_83;
    unsigned int m_84;
};

#endif
