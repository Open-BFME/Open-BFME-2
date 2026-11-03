// Target facts (RVAs unless marked VA): PE exports name FXParticleSystem::GpuDrawModuleInfo, its default constructor 0x00563981, copy constructor 0x003A9D73, assignment 0x003A7EF0 and virtual destructor 0x003A9D43. Both constructors install VA 0x00C1C1E8 at +0; its four slots are vector deleting destructor 0x003A9DDE, LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x003A615D ("GpuDrawModuleInfo" at VA 0x00C1BA10) and DoXfer(Xfer &) 0x0056390A. The next exported table starts at VA 0x00C1C1F8. The vector deleting destructor passes stride 0x14 at 0x003A9DF6 to iterator 0x00629110, proving sizeof 0x14.
// Target facts: destructor 0x003A9D43 destroys the narrow string at +0x0C through StringBase<char>::releaseBuffer 0x00036410, then stores Snapshot's VA 0x00BBB554 at 0x003A9D63. Snapshot::~Snapshot 0x0049B47C restores that same table; its slots 1..3 are purecall 0x0003B810. This is base teardown. The live object has one Snapshot base at +0 and four virtual slots. Copy 0x003A9D73 calls StringBase<char>'s copy 0x000365F0 at +0x0C; assignment 0x003A7EF0 calls StringBase<char>::set 0x000366F0 there. These methods remain out of line.
// Target facts: default construction 0x00563981 writes integer 1 at +0x04/+0x08, null at +0x0C and float 1.0 at +0x10 (VA 0x00BBB8D8). Copy and assignment move the two integer dwords and the speed dword separately. DoXfer 0x0056390A passes +0x04/+0x08 to Xfer's int slot +0x7C, +0x0C to its AsciiString slot +0x6C and +0x10 to its float slot +0x70. Template ctor 0x003A9E29 forms this+8 at 0x003A9E53 and calls 0x00563981 at 0x003A9E58. Template writer 0x00563D3F addresses that info at +8: 0x00563D76/0x00563D8E label +0x04 "FramesPerRow" (VA 0x00C6CA10) and +0x08 "TotalFrames" (VA 0x00C6CA04); 0x00563DA6/0x00563DCF label +0x0C "DetailTexture" (VA 0x00BE17F4) and +0x10 "SpeedMultiplier" (VA 0x00BE17D4). Member identifiers below denote offsets.

#pragma once

#ifndef CANONICAL_FXPARTICLESYSTEM_GPUDRAWMODULEINFO_H
#define CANONICAL_FXPARTICLESYSTEM_GPUDRAWMODULEINFO_H

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

namespace FXParticleSystem
{

class GpuDrawModuleInfo : public ::Snapshot
{
public:
    GpuDrawModuleInfo();
    GpuDrawModuleInfo(const GpuDrawModuleInfo &that);
    GpuDrawModuleInfo &operator=(const GpuDrawModuleInfo &that);
    virtual ~GpuDrawModuleInfo();

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

    int m_04;
    int m_08;
    AsciiString m_0C;
    float m_10;
};

}

using FXParticleSystem::GpuDrawModuleInfo;

#endif
