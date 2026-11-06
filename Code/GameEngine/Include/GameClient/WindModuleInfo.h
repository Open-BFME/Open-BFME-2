// Target facts (RVAs unless marked VA): PE exports identify FXParticleSystem::WindModuleInfo; ctors 0x003A53C4/0x001F35DF install VA 0x00BE15A4. Its four slots are deleting dtor 0x001F36C3, LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x001F35D9 ("WindModuleInfo" at VA 0x00BE1594), and DoXfer(Xfer &) 0x003A547E; the next stored table starts at VA 0x00BE15B4.
// Target facts: destructor 0x0049B47C restores Snapshot VA 0x00BBB554, whose last three slots are purecall; this is base teardown, not the live WindModuleInfo table. The class is polymorphic with one Snapshot base at +0. Vector deleting dtor 0x001F36DB passes element size 0x48 to iterator 0x00629110 and calls the exported destructor out of line at 0x001F36F6.
// Target facts: ctor 0x003A53CC writes integer +0x04; SSE stores cover floats +0x08..+0x38 and +0x40/+0x44; 0x003A546F writes byte +0x3C. DoXfer 0x003A54A1 passes +0x04 to XferWindMotion, uses float slot +0x70 for those floats and char slot +0x8C for +0x3C. Copy 0x001F35DF and assignment 0x001F3654 copy these seventeen fields separately, leaving +0x3D..+0x3F as padding; exported DEFAULT_MOTION_MOVING_TO_END_ANGLE at RVA 0x0081B314 is char. Original member names are unproven.

#pragma once

#ifndef CANONICAL_FXPARTICLESYSTEM_WINDMODULEINFO_H
#define CANONICAL_FXPARTICLESYSTEM_WINDMODULEINFO_H

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

class WindModuleInfo : public ::Snapshot
{
public:
    WindModuleInfo();
    WindModuleInfo(const WindModuleInfo &that);
    WindModuleInfo &operator=(const WindModuleInfo &that);
    virtual ~WindModuleInfo();
    // Snapshot slots, spelled the way the unit selected Snapshot.h's.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
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
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif

    static const float DEFAULT_STRENGTH;
    static const float DEFAULT_FULL_STRENGTH_DIST;
    static const float DEFAULT_ZERO_STRENGTH_DIST;
    static const float DEFAULT_ANGLE_CHANGE;
    static const float DEFAULT_ANGLE_CHANGE_MAX;
    static const float DEFAULT_MOTION_START_ANGLE_MAX;
    static const float DEFAULT_MOTION_END_ANGLE_MIN;

    int m_04;
    float m_08;
    float m_0C;
    float m_10;
    float m_14;
    float m_18;
    float m_1C;
    float m_20;
    float m_24;
    float m_28;
    float m_2C;
    float m_30;
    float m_34;
    float m_38;
    char m_3C;
    float m_40;
    float m_44;
};

}

// The class unqualified: header_adopt_lane's layout probe names the header's classes so.
using FXParticleSystem::WindModuleInfo;

#endif
