// Target facts: ActionManager ctor RVA 0x0041B8B5 calls SubsystemInterface's 0x001B4E63 at +0 and stores VA 0x00C3AE60. Its dtor 0x0041B8C7 restores that same table, then jumps to base dtor 0x001B4E74, which restores VA 0x00BD77A0 and destroys AsciiString at +8 through 0x00036410. The base ctor stores that base table, clears byte +4 and dword +8. Allocation at 0x0022FA6C requests 0x0C bytes through 0x0002FDA0, then calls ActionManager's ctor at 0x0022FA81: sizeof 0x0C, one SubsystemInterface base, no additional members.
// Target facts: VA 0x00C3AE60 has fourteen slots and ends at string data VA 0x00C3AE98. Slot 0 is deleting dtor RVA 0x0041BBC8, which calls 0x0041B8C7; slots 1/3/8/9/10/12 are 0x000B3FD0 (ret), slot 2 is SubsystemInterface::loadIniFilesFromLegend 0x001B5384, slots 4/11 are 0x005CB9FF (false, ret 4), slot 5 is 0x0047A699 (false, ret), slot 6 is 0x000D43D0 (zero, ret), and slots 7/13 are 0x0047A69C (ret 4). Base VA 0x00BD77A0 has the same slots except its deleting dtor and pure init/reset/update slots 1/9/10. These are successive base and derived lifetimes, not competing layouts; the registered base supplies the fourteen slots through BFME_SUBSYSTEM_SLOTS.
// Target facts: method names and signatures below are the matched ActionManager ledger rows at RVAs 0x0041B8D2, 0x0041B94A, 0x0041B9B0, 0x0041BA1C, 0x0041BA61, 0x0041BAD2, 0x0041BB26, 0x0041BB49, 0x0041BB87, 0x0041BBE4, 0x0041BCA1, 0x0041BE3A, 0x0041BE93, 0x0041BF47, 0x0041BFA2, 0x0041C001, 0x0041C085, 0x0041C138, 0x0041C21B, 0x0041C5F6, 0x0041C6CF, 0x0041C79C, 0x0041C9C4, 0x0041C9F8, 0x0041CA9E, 0x0041CB10, 0x0041CC65, 0x0041CCD5, 0x0041CE06, 0x0041CE27, 0x0041CE99, 0x0041CFCC, 0x0041D4FA and 0x0041D60B. Lifetimes and query bodies remain out of line. Donor facts: Zero Hour GeneralsMD Common/ActionManager.h names init/reset/update, the named queries and the true default for special-power requirement checks; it supplies no BFME2 layout facts.

#pragma once
#ifndef CANONICAL_ACTIONMANAGER_H
#define CANONICAL_ACTIONMANAGER_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../Common/MessageStream.h"

class Object;
class Player;
class SpecialPowerTemplate;
class DrawableList;
class CapturePowerView;
class Rva0041B8D2Obj;
struct Coord3D;
enum CommandSourceType;
enum WeaponSlotType;
enum AbleToAttackType;
enum CanAttackResult;

class ActionManager : public SubsystemInterface
{
public:
    ActionManager();
    virtual ~ActionManager();
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}

    unsigned char Rva0041B8D2Check(Rva0041B8D2Obj *, Rva0041B8D2Obj *, int);
    bool Rva0041B94AGet(Object *, Object *, int);
    bool canConvertObjectToCarBomb(const Object *, const Object *, CommandSourceType);
    bool canMakeObjectDefector(const Object *, const Object *, CommandSourceType);
    bool rva0041BA61(const Object *);
    bool rva0041BAD2(const Object *, const Object *, CommandSourceType, WeaponSlotType);
    unsigned char canFireWeapon(const Object *, WeaponSlotType, CommandSourceType);
    bool canOverrideSpecialPowerDestination(Object *, const Coord3D *, int, int);
    unsigned char Rva0041BB87IsRelated(Object *, Object *, int);
    bool canGetRepairedAt(const Object *, const Object *, CommandSourceType);
    bool canTransferSuppliesAt(const Object *, const Object *);
    bool canDockAt(const Object *, const Object *, CommandSourceType, bool);
    bool canGetHealedAt(const Object *, const Object *, CommandSourceType);
    bool canResumeConstructionOf(const Object *, const Object *, CommandSourceType);
    CanAttackResult bfmeGetCanAttackContained(const Object *, const Object *, CommandSourceType, AbleToAttackType);
    bool canHijackVehicle(const Object *, const Object *, CommandSourceType);
    bool canFireWeaponAtLocation(const Object *, const Coord3D *, CommandSourceType, WeaponSlotType, const Object *);
    bool rva0041C138(const Object *, const Object *, CommandSourceType);
    bool canPlayerGarrison(const Player *, const Object *, CommandSourceType);
    GameMessage::Type getEnterMessage(const Object *, const DrawableList *);
    CanAttackResult getCanAttackObject(const Object *, const Object *, CommandSourceType, AbleToAttackType);
    bool rva0041C79C(const Object *, const Object *, CommandSourceType, CapturePowerView *);
    bool rva0041C9C4(const Object *, const Coord3D *, const SpecialPowerTemplate *);
    bool validateLocationForForbiddenObjects(const Object *, const Coord3D *, const SpecialPowerTemplate *);
    bool rva0041CA9E(const Coord3D *, const Coord3D *, const SpecialPowerTemplate *);
    bool rva0041CB10(const Coord3D *, const SpecialPowerTemplate *);
    bool rva0041CC65(const SpecialPowerTemplate *, const Coord3D *);
    bool canDoSpecialPower(const Object *, const SpecialPowerTemplate *, CommandSourceType, unsigned int, bool checkSourceRequirements = true);
    GameMessage::Type rva0041CE06(const Object *);
    bool Rva0041CE27Check(Object *, Object *, int);
    bool canRepairObject(const Object *, const Object *, CommandSourceType);
    bool canDoSpecialPowerAtObject(const Object *, const Object *, CommandSourceType, const SpecialPowerTemplate *, unsigned int, bool checkSourceRequirements = true);
    bool validLocationForCastingOnObjectFilter(const Object *, const Coord3D *, const SpecialPowerTemplate *);
    bool canDoSpecialPowerAtLocation(const Object *, const Coord3D *, CommandSourceType, const SpecialPowerTemplate *, const Object *, unsigned int, bool checkSourceRequirements = true);
};

extern ActionManager *TheActionManager;

#endif
