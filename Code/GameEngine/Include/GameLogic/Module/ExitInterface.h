// Target facts (code addresses are RVAs; vftables are VAs):
// 0x004A010E stores 0x00C430B4 at +0x20 before replacing it with Queue's
// 0x00C5198C; 0x0049FFF7 restores only the latter before UpdateModule teardown.
// 0x004649F8 similarly stores 0x00C430B4 at +0x30, then OpenContain's
// 0x00C43380; the next interface starts at +0x34. Queue's fields start at +0x24.
// These stores and Zero Hour's declaration establish a four-byte interface
// with its vptr at +0, no data members, no bases and no virtual destructor.
// 0x00C430B4 has 12 slots, followed by zero at 0x00C430E4. Slots 0-4 and 7-8
// are __purecall (0x0003B810); slot 5 is RET 4 (0x0047A69C), slot 6 returns
// false (0x0047A699), and slot 11 is RET (0x000B3FD0).
// Queue's 0x00C5198C and Default's 0x00C4B1B0 prove setRallyPoint at slot 7
// (0x004A051B / 0x00487F60) and getRallyPoint at slot 8 (0x004A001D /
// 0x00487F75). Slot 6 uses Queue's byte getter 0x004A0107 and Default's false.
// Slot 9 is getNaturalRallyPoint: base 0x004624A7 zeroes three output floats,
// returns false and pops eight bytes; its ledger row proves Coord3D& and bool.
// Slot 10 is getExitPosition: base 0x004624C1 zeroes the angle and three
// position floats, returns false and pops eight bytes; Queue's row 0x004A0194
// proves Coord3D& and float&. Both base methods have out-of-line retail bodies.
// Queue's slot 11 points to notifyProductionBurstFinished (row 0x004A0547).
// Donor facts: Zero Hour UpdateModule.h names slots 0-5 and the rally methods.
// Its useSpawnRallyPoint is slot 8; the BFME2 tables place it at slot 6.

#pragma once

#ifndef __BFME2_EXITINTERFACE_H_
#define __BFME2_EXITINTERFACE_H_

class Object;
class ThingTemplate;
struct Coord3D;
enum ExitDoorType;

class ExitInterface
{
public:
    virtual bool isExitBusy() const = 0;
    virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
    virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
    virtual void exitObjectByBudding(Object *newObj, Object *budHost) = 0;
    virtual void unreserveDoorForExit(ExitDoorType exitDoor) = 0;
    virtual void exitObjectInAHurry(Object *newObj) {}
    virtual bool useSpawnRallyPoint() const { return false; }
    virtual void setRallyPoint(const Coord3D *pos) = 0;
    virtual const Coord3D *getRallyPoint() const = 0;
    virtual bool getNaturalRallyPoint(Coord3D &rallyPoint, bool offset = true) const;
    virtual bool getExitPosition(Coord3D &exitPosition, float &exitAngle) const;
    virtual void notifyProductionBurstFinished() {}
};

#endif
