// Target facts (code addresses are RVAs; table addresses are VAs):
// 0x00374B02 calls UpdateModule's 0x00253390, then installs 0x00C17F20 at
// +0, 0x00BEFF90 at +0x0C and 0x00C17F14 at +0x10. The destructor at
// 0x00373CB1 installs the same three tables and jumps to 0x0024A797.
// That base destructor restores 0x00BFBCE4, then BehaviorModule's tables
// 0x00BEEA7C/0x00BEE9C0; these are base destruction, not StealthUpdate tables.
// The base constructor writes through +0x1C; StealthUpdate starts at +0x20.
// Factory 0x0024EC25 pushes 0x14C at 0x0024EC30 before calling 0x00374B02.
// 0x00C17F20 has 13 slots: 0=0x00373F3D, 1=0x00374AE8, 2=0x00373D0F,
// 3=0x00374942, 4=0x00373CCA, 5=0x00374FD0, 6-8=0x000B3FD0,
// 9=0x0050B238, 10-11=0x000D43D0, 12=0x0022C4CB. The next word is data.
// 0x00C17F14 has update (0x003756A8), the mask return at 0x004A2D67 and
// UpdateModule's wake method (0x0044DF8D); neither interface adds a destructor.
// 0x003756A8 receives this+0x10 (Object is read at -8, base calls use -0x10).
// 0x00BEFF90 is the inherited 47-slot BehaviorModuleInterface table, with
// only its update getter at slot 9. StealthUpdate adds no virtual slots.
// Constructor 0x00374B02 writes dwords +0x20/+0x24/+0x28/+0x2C/+0x38/
// +0x3C/+0x40, bytes +0x30..+0x34/+0x44..+0x47/+0x148, and calls the
// 0x80-byte clear 0x001EAE6F at +0x48/+0xC8. Remaining bytes are padding.
// Xfer 0x00374942 proves the uint/int/bool widths and versioned fields;
// 0x00374AE8 sets +0x47 when the +0x3C template is present. 0x00373D15
// reads +0x2C, then module-data +0x0C; 0x0004D65B tests the +0x3C pointer.
// These accessors, the constructor and destructor have out-of-line owners.
// Other declared method names/signatures come from their StealthUpdate ledger
// rows (0x00373D23..0x003756A8, 0x0024EC25); unknown fields stay neutral.
// Donor facts: Zero Hour StealthUpdate.h names the frame, enabled and disguise
// members. Its pulse fields and stealth interface getter are absent here.

#pragma once

#ifndef __BFME2_STEALTHUPDATE_H_
#define __BFME2_STEALTHUPDATE_H_

#include "UpdateModule.h"

struct Coord3D;
class ThingTemplate;
enum StealthLookType;

class StealthUpdate : public UpdateModule
{
public:
    StealthUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~StealthUpdate();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static NameKeyType rva000373CCA();
    virtual NameKeyType getModuleNameKey() const;
    virtual void onObjectCreated();
    virtual UpdateSleepTime update();
    virtual DisabledMaskType getDisabledTypesToProcess() const;

    bool isDisguised() const;
    unsigned int getStealthLevel() const;
    void markAsDetected(unsigned int numFrames, int feedback, Object *detector, bool throughContainer);
    void disguiseAsObject(const Object *target);
    StealthLookType calcStealthedStatusForPlayer(const Object *obj, const Player *player);
    void changeVisualDisguise();
    void rva00373D23();
    StealthUpdate *rva00373D28(Object *obj);
    void rva00373D5E();
    void rva00373EEC(unsigned int numFrames);
    bool rva00373F59(const Coord3D *pos, const Coord3D *ownerPos);
    bool rva003742B1();
    void rva003748BD();
    UpdateSleepTime rva00374FD5();

    unsigned int m_stealthAllowedFrame; // +0x20
    unsigned int m_detectionExpiresFrame; // +0x24
    unsigned int m_framesGranted; // +0x28
    int m_field2C;
    bool m_enabled; // +0x30
    bool m_field31;
    bool m_field32;
    bool m_field33;
    bool m_field34;
    int m_disguiseAsPlayerIndex; // +0x38
    const ThingTemplate *m_disguiseAsTemplate; // +0x3C
    unsigned int m_disguiseTransitionFrames; // +0x40
    bool m_disguiseHalfpointReached; // +0x44
    bool m_transitioningToDisguise; // +0x45
    bool m_disguised; // +0x46
    bool m_xferRestoreDisguise; // +0x47
    unsigned char m_field48[0x80];
    unsigned char m_fieldC8[0x80];
    bool m_field148;

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);
    void hintDetectableWhileUnstealthed();
    UpdateSleepTime calcSleepTime() const;
};

#endif
