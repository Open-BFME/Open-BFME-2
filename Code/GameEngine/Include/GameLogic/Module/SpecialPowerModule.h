// Target facts (BFME2 1.06; code addresses are RVAs, table addresses are VAs):
// 0x00492FB9 stores 0x00C4E2B0 at +0; 0x00493C81 installs that same table at SpecialPowerModule+0x10. It contains 25 __purecall entries (RVA 0x0003B810), followed by zero at VA 0x00C4E314. This is a polymorphic interface without a virtual destructor, bases or data members; its extent is four bytes (the module constructor writes its first member at +0x14 at 0x00493CA2).
// 0x00493C9C replaces the interface table with 0x00C5E080; 0x00493E13 restores that implementation table in ~SpecialPowerModule (0x00493DEF). The purecall table belongs to interface construction, while the implementation table belongs to SpecialPowerModule. Its primary deleting destructor is separate, at VA 0x00C4E868 slot 0 (RVA 0x004941D7).
// Implementation slots 0/1/2/4/5/6/7/8/9 target 0x0049323D/0x004934DE/0x0049355E/0x00493AB7/0x004934B8/0x00493236/0x004933C2/0x0010670B/0x00492FC2. Zero Hour names and retail calls establish isModuleForPower/getPercentReady/getReadyFrame/getSpecialPowerTemplate/setReadyFrame; ledger rows name isReady/getPowerName/onSpecialPowerCreation/pauseCountdown. Slot 3 (0x00251C08) tests signed interface+0x0C > 0 and has no established name.
// Slots 10-15 target the rowed doSpecialPower (0x0049490F), doSpecialPowerAtObject (0x0049495B), doSpecialPowerAtLocation (0x004949D8), doSpecialPowerUsingWaypoints (0x00494A2A), markSpecialPowerTriggered (0x00494591) and startPowerRecharge (0x0049369D). Their ledger signatures prove the arguments; location has no angle, waypoints also takes a location, and recharge takes float (0x004933D6 passes 1.0 to slot 15 at 0x004933D9).
// Slot 16 (0x00493218) returns Rva002390CB by value through its rowed copy constructor 0x002390CB; Zero Hour names this getInitiateSound. Slots 17/19 (0x00251C2C) clear byte interface+0x18 with no arguments; slot 18 is the rowed bool rva0049466D(const Coord3D*) (0x0049466D). Slot 20 (0x0030F2C7) returns the dword at interface+0x1C. Slot 21 (0x004932D5) returns module-data byte +0x0D. Slot 22 (0x0049329E) adjusts pauseCountdown through slot 9. Slots 23/24 (0x004BF893) return interface-0x10. Unproved names remain slotNN.
// At 0x004ADD68/0x004ADD71, slot 23's two results become the argument and receiver of 0x00493BD4 at 0x004ADD76. Its ledger signature is Rva00493BD4::rva00493BD4(Rva00493BD4*), so slot 23 returns that opaque row-owned type; no original class identity is asserted.

#pragma once

#ifndef __BFME2_SPECIALPOWERMODULE_H_
#define __BFME2_SPECIALPOWERMODULE_H_

class AsciiString;
class Object;
class Rva002390CB;
class Rva00493BD4;
class SpecialPowerTemplate;
class Waypoint;
struct Coord3D;

class SpecialPowerModuleInterface
{
public:
    virtual bool isModuleForPower(const SpecialPowerTemplate *power) const = 0;
    virtual bool isReady() const = 0;
    virtual float getPercentReady() const = 0;
    virtual bool slot03() const = 0;
    virtual unsigned int getReadyFrame() const = 0;
    virtual AsciiString getPowerName() const = 0;
    virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
    virtual void onSpecialPowerCreation() = 0;
    virtual void setReadyFrame(unsigned int frame) = 0;
    virtual void pauseCountdown(bool pause) = 0;
    virtual void doSpecialPower(unsigned int commandOptions) = 0;
    virtual void doSpecialPowerAtObject(Object *object, unsigned int commandOptions) = 0;
    virtual void doSpecialPowerAtLocation(const Coord3D *location, unsigned int commandOptions) = 0;
    virtual void doSpecialPowerUsingWaypoints(const Coord3D *location, const Waypoint *waypoint, unsigned int commandOptions) = 0;
    virtual void markSpecialPowerTriggered(const Coord3D *location) = 0;
    virtual void startPowerRecharge(float readyFraction) = 0;
    virtual Rva002390CB getInitiateSound() const = 0;
    virtual void slot17() = 0;
    virtual bool rva0049466D(const Coord3D *location) = 0;
    virtual void slot19() = 0;
    virtual unsigned int slot20() const = 0;
    virtual bool slot21() const = 0;
    virtual void slot22() = 0;
    virtual Rva00493BD4 *slot23() = 0;
    virtual void *slot24() = 0;
};

#endif
