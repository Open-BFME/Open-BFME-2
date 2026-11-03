/* Target facts (RVAs unless marked VA): FXParticleSystem::RenderObjectUpdateModuleInfo has a primary vptr and four virtual slots. Its copy constructor 0x003A7F3E and default constructor 0x00561F99 store VA 0x00C1BDB0 at +0. This table contains the vector deleting destructor 0x003A805A, the empty post-load callback 0x000B3FD0, the non-const GetSnapshotName 0x003A6163 and protected xfer(Xfer *) 0x00562182. The name getter returns "RenderObjectUpdateModuleInfo". The folded complete destructor 0x0049B47C stores only Snapshot's VA 0x00BBB554, whose deleting destructor 0x00001750 has a 4-byte stride and whose other three slots are purecall 0x0003B810. This is Snapshot teardown at +0; the constructor table belongs to this derived class. The derived deleting destructor passes element size 0x98, agreeing with the constructors' final dword at +0x94.
The default constructor calls GameClientRandomVariable::setRange (0x002341E7) on twelve 12-byte members at +0x04, +0x10, +0x1C, +0x28, +0x34, +0x40, +0x4C, +0x58, +0x64, +0x70, +0x7C and +0x88, and sets the dword at +0x94 to 1. xfer (0x00562182) transfers those members and passes +0x94 to XferRotationType (0x00306082), establishing the rotation mode. Copy construction (0x003A7F3E) and assignment (0x003A7FCF) copy twelve 12-byte groups and the final dword. The template copy constructor (0x003A80FF) and default constructor (0x003A80A8, call at 0x003A80D7) call the rowed info constructors at subobject +8; 0x005624DE calls the default constructor at +0x1C. Special members remain out of line. The indexed member names are neutral placeholders. Donor fact: Zero Hour's GeneralsMD Snapshot.h supplies the spelling loadPostProcess; the virtual destructor and slot order are retail facts.
*/
#pragma once

#ifndef __BFME2_RENDEROBJECTUPDATEMODULEINFO_H_
#define __BFME2_RENDEROBJECTUPDATEMODULEINFO_H_

#if !defined(__SNAPSHOT_H_)
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class RenderObjectUpdateModuleInfo : public Snapshot
{
public:
    RenderObjectUpdateModuleInfo();
    RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that);
    RenderObjectUpdateModuleInfo &operator=(const RenderObjectUpdateModuleInfo &that);
    virtual ~RenderObjectUpdateModuleInfo();

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess() {}
#else
    virtual void loadPostProcess() {}
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif

public:
    GameClientRandomVariable m_var0;  // +0x04
    GameClientRandomVariable m_var1;  // +0x10
    GameClientRandomVariable m_var2;  // +0x1C
    GameClientRandomVariable m_var3;  // +0x28
    GameClientRandomVariable m_var4;  // +0x34
    GameClientRandomVariable m_var5;  // +0x40
    GameClientRandomVariable m_var6;  // +0x4C
    GameClientRandomVariable m_var7;  // +0x58
    GameClientRandomVariable m_var8;  // +0x64
    GameClientRandomVariable m_var9;  // +0x70
    GameClientRandomVariable m_var10; // +0x7C
    GameClientRandomVariable m_var11; // +0x88
    int m_mode;                     // +0x94
};

}

using FXParticleSystem::RenderObjectUpdateModuleInfo;

#endif
