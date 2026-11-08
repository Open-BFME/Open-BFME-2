// Target facts (code addresses are RVAs; table addresses are VAs):
// OpenContain's constructor 0x004649F8 stores 0x00C430E8 at +0x20 at
// 0x00464A16, then 0x00C433B0 there at 0x00464A5C. The former is the
// interface's 94 __purecall entries (0x0003B810), ending at 0x00C43260.
// The latter has 94 implementations and ends before the +0x0C table
// 0x00C43528. The destructor 0x00464692 restores 0x00C433B0 at
// 0x004646B9: this is the derived table, not a second interface layout.
// The adjacent interface at +0x24 bounds this base to four bytes. There
// are no data members or base classes in this interface. It has virtual
// functions, but no virtual destructor (also absent from the donor).
// Slots 3, 22, 23, 38, 39, 40, 41, 42, 68 and 76 are established by
// 0x004624E3, 0x00463097, 0x00464D02, 0x00462977, 0x00464830,
// 0x004638F1, 0x00463509, 0x004635C0, 0x004635EC and 0x00478547.
// Slot 38's row takes Object*, bool, bool; slot 68 tests DWORD flags
// 1 and 8, with HordeContain's 0x0046DD67 additionally testing 0x10.
// Slot 69 (0x00462DE0) takes a filter pointer, returning +0x38 for null;
// otherwise it counts matches through the predicate at 0x00362437.
// Its unsigned result is established by evaluateIsBuildingEmpty at
// 0x003E4079, which tests it against zero with an unsigned comparison.
// Slots 70/71 (0x004647D8/0x004624EB) return two-pointer aggregates
// through a hidden result pointer, containing this and a list address.
// Slot 53's HordeSiegeEngineContain override 0x0047CADB returns float;
// slot 58 is 0x004631FA (ObjectID test). Slots 86/87 are distinct
// Coord3D* getters at 0x004626CA/0x004626AF, not one shared name.
// Object::releaseWeaponLock (0x0028D8B6) calls slot 91 with its lock type.
// Slot 1 (0x004647CD) returns the OpenContain object at this-0x20;
// slot 2 is a separate null-returning query. Slot 21 receives Team* in
// Player::transferAssetsFromThat (0x002AEA9F). Slot 45 (0x00462B4A) is the
// no-argument passenger-fire query used by WeaponSet (0x002C7907).
// Slot 61 is the rowed getClosestRider (0x004632E0). Slot 63's byte
// setter (0x00464810) takes true in GarrisonUpgrade (0x004B5886). Slot 81's
// mask getter (0x003F3FCE) is compared with the player's mask in
// Player::garrisonAllUnits (0x002AEEA7); slot 83 is 0x004647FD's byte setter.
// HordeContain's constructor 0x0046F543 stores 0x00C44EC8 at +0x20 (0x0046F589).
// Its slot 31 (0x0046F7B9) returns this+0xFC, the +0x11C HordeContainInterface,
// or null; Object 0x0028C197 forwards it. OpenContain's slot 31 returns null.
// Slot 43 is 0x0046274C (void*, int, void*; ret 0xC); slot 48 is 0x00462BFF
// (const char query of two const Object*); slot 52 is 0x0050B5C6 (mov al,1).
// ControlBar 0x0031D230 tests slot 54's byte (0x0031D38D) and compares slot
// 56's pointer with the local player (0x0031D39B). Slot 59 takes Object* in
// HordeContain's 0x0046731A (ret 4). Slot 66 is 0x00463191 (Object*, bool;
// HordeContain's 0x0046BA56 row spells the flag int). Slot 79 is 0x00463291
// (Object* from a Rva2225E0Filter*).
// Donor facts: Zero Hour's ContainModule.h supplies the containment method
// names and has no parent or destructor. BFME2's table and call sites,
// rather than the donor's shorter slot order, place the named methods.

#pragma once

#ifndef __BFME2_CONTAINMODULE_H_
#define __BFME2_CONTAINMODULE_H_

class Object;
class OpenContain;
class Player;
class ExitInterface;
class Team;
class Rva2225E0Filter;
class HordeContainInterface;
class ContainModuleInterface;
struct Coord3D;
enum ObjectEnterExitType;
enum WeaponLockType;

typedef void (*ContainIterateFunc)(Object *object, void *userData);

struct ContainModuleInterfaceItems
{
    ContainModuleInterface *field00;
    const void *field04;
};

class ContainModuleInterface
{
public:
    virtual void slot00(bool) = 0;
    virtual OpenContain *asOpenContain() = 0;
    virtual void *slot02() = 0;
    virtual void containReactToTransformChange() = 0;
    virtual bool isGarrisonable() const = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual bool onObjectWantsToEnterOrExit(Object *object, ObjectEnterExitType wants) = 0;
    virtual void slot18() = 0;
    virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const = 0;
    virtual void recalcApparentControllingPlayer() = 0;
    virtual void slot21(Team *team) = 0;
    virtual void onContaining(Object *object, bool wasSelected) = 0;
    virtual void onRemoving(Object *object) = 0;
    virtual void slot24() = 0;
    virtual void onSelling() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual int getContainMax() const = 0;
    virtual ExitInterface *getContainExitInterface() = 0;
    virtual void slot30() = 0;
    virtual HordeContainInterface *slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual bool isValidContainerFor(Object *object, bool checkCapacity, bool flag) = 0;
    virtual void addToContain(Object *object) = 0;
    virtual void addToContainList(Object *object) = 0;
    virtual void removeFromContain(Object *object, bool exposeStealthUnits = false) = 0;
    virtual void removeAllContained(bool exposeStealthUnits = false) = 0;
    virtual void slot43(void *, int, void *) = 0;
    virtual void slot44() = 0;
    virtual bool isPassengerAllowedToFire() const = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual char slot48(const Object *, const Object *) const = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual bool slot52() = 0;
    virtual float slot53() = 0;
    virtual bool slot54() const = 0;
    virtual void slot55() = 0;
    virtual const Player *slot56() const = 0;
    virtual void slot57() = 0;
    virtual bool slot58(int objectId) = 0;
    virtual void slot59(Object *object) = 0;
    virtual void slot60() = 0;
    virtual Object *getClosestRider(const Coord3D *position) = 0;
    virtual void slot62() = 0;
    virtual void slot63(bool flag) = 0;
    virtual void slot64() = 0;
    virtual void slot65() = 0;
    virtual void slot66(Object *object, bool flag) = 0;
    virtual void slot67() = 0;
    virtual void iterateContained(ContainIterateFunc func, void *userData, int flags) = 0;
    virtual unsigned int getContainCount(Rva2225E0Filter *filter = 0) = 0;
    virtual ContainModuleInterfaceItems slot70() = 0;
    virtual ContainModuleInterfaceItems slot71() = 0;
    virtual void slot72() = 0;
    virtual void slot73() = 0;
    virtual void slot74() = 0;
    virtual void slot75() = 0;
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos) = 0;
    virtual void slot77() = 0;
    virtual void slot78() = 0;
    virtual Object *slot79(Rva2225E0Filter *filter) = 0;
    virtual void slot80() = 0;
    virtual unsigned int getPlayerWhoEntered() const = 0;
    virtual void slot82() = 0;
    virtual void enableLoadSounds(bool enable) = 0;
    virtual void slot84() = 0;
    virtual void slot85() = 0;
    virtual const Coord3D *slot86() = 0;
    virtual const Coord3D *slot87() = 0;
    virtual void slot88() = 0;
    virtual void slot89() = 0;
    virtual void slot90() = 0;
    virtual void releaseWeaponLock(WeaponLockType lockType) = 0;
    virtual void slot92() = 0;
    virtual void slot93() = 0;
};

#endif
