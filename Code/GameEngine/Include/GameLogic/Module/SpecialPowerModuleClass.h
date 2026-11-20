// Target facts (code addresses are RVAs; vftables are VAs):
// The constructor 0x00493C5A calls BehaviorModule's 0x00253330, stores the
// SpecialPowerModuleInterface table 0x00C4E2B0 at +0x10, then the class's
// own tables: 0x00C4E868 at +0 (14 primary slots), 0x00BEFCF8 at +0x0C (47
// BehaviorModuleInterface slots) and 0x00C5E080 at +0x10 (25 interface
// slots); it writes its first member at +0x14. The destructor 0x00493DEF
// restores the same three. friend_newModuleInstance 0x0024DC54 allocates
// 0x34 bytes.
// Primary slots 0-11 are BehaviorModule's positions; SpecialPowerModule
// overrides 0 (0x004941D7), 1 (0x00493B1E) and 4 (0x00493DAA) and adds 12
// (0x00493805) and 13 (0x00493EA7). Slot 2 holds 0x00493DA4 (rowed only as
// the free ?Rva00493DA4Get@@YAHXZ) and slot 3 holds 0x00493009 (rowed only
// as ?xfer@Rva00493009@@MAEXPAVXfer@@@Z), so neither is declared here.
// The +0x0C table differs from BehaviorModule's defaults at slot 8
// (0x002533D3, the +0x10 interface) and slots 43/44 (0x00251C11,
// 0x00251C24).
// The +0x10 table's slots 1, 2, 5, 6, 7, 9-15 and 18 are rowed under
// SpecialPowerModule's name; slots 0, 3, 4, 8, 16, 17 and 19-24 hold bodies
// rowed under other classes or none, and stay the interface's pure entries.
// Layout: the constructor writes the dwords at +0x14..+0x24 (the float at
// +0x24), the bool at +0x28, the int at +0x2C and the bool at +0x30.
// Donor facts: Zero Hour's SpecialPowerModule.h names the class, its
// BehaviorModule and SpecialPowerModuleInterface bases and the method names
// the ledger rows carry; BFME2's slot order and signatures follow retail.
// The field names are the byte-matched constructor view's
// (SpecialPowerModuleCtor.cpp). The class sits beside the interface's
// registered SpecialPowerModule.h as DamageModule and CreateModule sit in
// DamageModuleClass.h and CreateModuleClass.h.

#pragma once

#ifndef __BFME2_SPECIALPOWERMODULECLASS_H_
#define __BFME2_SPECIALPOWERMODULECLASS_H_

#include "BehaviorModule.h"
#include "SpecialPowerModule.h"

template <int N> class BitFlags;
class INI;
class Module;
class ModuleData;
class Thing;
enum NameKeyType;

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
    SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
    virtual ~SpecialPowerModule();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

    // Primary table 0x00C4E868.
    virtual NameKeyType getModuleNameKey() const;                  // slot 4, 0x00493DAA
    virtual void rva00493805();                                    // slot 12, 0x00493805
    virtual void ApplyPowerToObject(Object *object, int level,
        const BitFlags<11> *mask);                                 // slot 13, 0x00493EA7

    // BehaviorModuleInterface table 0x00BEFCF8 (+0x0C).
    virtual SpecialPowerModuleInterface *getSpecialPower() { return this; } // slot 8, 0x002533D3
    virtual void slot43(float readyFraction);                      // slot 43, 0x00251C11
    virtual void slot44();                                         // slot 44, 0x00251C24

    // SpecialPowerModuleInterface table 0x00C5E080 (+0x10).
    virtual bool isReady() const;                                  // slot 1, 0x004934DE
    virtual float getPercentReady() const;                         // slot 2, 0x0049355E
    virtual AsciiString getPowerName() const;                      // slot 5, 0x004934B8
    virtual void onSpecialPowerCreation();                         // slot 7, 0x004933C2
    virtual void pauseCountdown(bool pause);                       // slot 9, 0x00492FC2
    virtual void doSpecialPower(unsigned int commandOptions);      // slot 10, 0x0049490F
    virtual void doSpecialPowerAtObject(Object *object, unsigned int commandOptions); // slot 11, 0x0049495B
    virtual void doSpecialPowerAtLocation(const Coord3D *location, unsigned int commandOptions); // slot 12, 0x004949D8
    virtual void doSpecialPowerUsingWaypoints(const Coord3D *location, const Waypoint *waypoint,
        unsigned int commandOptions);                              // slot 13, 0x00494A2A
    virtual void markSpecialPowerTriggered(const Coord3D *location); // slot 14, 0x00494591
    virtual void startPowerRecharge(float readyFraction);          // slot 15, 0x0049369D
    virtual bool rva0049466D(const Coord3D *location);             // slot 18, 0x0049466D

    void initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos,
        unsigned int commandOptions, const Waypoint *way);         // 0x004946F3
    void triggerSpecialPower(const Coord3D *location);             // 0x004941F3
    bool rva00493251();                                            // 0x00493251
    bool rva004932DC();                                            // 0x004932DC
    bool rva00493620();                                            // 0x00493620
    bool rva00494599(const Coord3D *location);                     // 0x00494599

protected:
    virtual void loadPostProcess();                                // slot 1, 0x00493B1E
    virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const; // +0x10 slot 6, 0x00493236
    void createViewObject(const Coord3D *location);                // 0x00493845
    void aboutToDoSpecialPower(const Coord3D *location);           // 0x004939AB

    unsigned int m_rechargeFrames;  // +0x14
    unsigned int m_availableOnFrame; // +0x18
    int m_pausedCount;              // +0x1C
    unsigned int m_pausedOnFrame;   // +0x20
    float m_pausedPercent;          // +0x24
    bool m_28;
    int m_2c;
    bool m_30;
};

typedef char SpecialPowerModuleSizeIs0x34[sizeof(SpecialPowerModule) == 0x34 ? 1 : -1];

#endif // __BFME2_SPECIALPOWERMODULECLASS_H_
