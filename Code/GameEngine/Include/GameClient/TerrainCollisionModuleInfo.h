/* Target facts (RVAs unless marked VA): FXParticleSystem::TerrainCollisionModuleInfo constructors 0x003A9FBA and 0x0056459E install VA 0x00C1C218 at +0; its four slots are vector deleting destructor 0x003AA02D (stride 0x1C, sizeof 0x1C), LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x003A6169 ("TerrainCollisionModuleInfo", VA 0x00C1BA44), and DoXfer(Xfer &) 0x0056445E.
Destructor 0x003A9F8A releases the narrow string at +4 through 0x00036410 and restores Snapshot's VA 0x00BBB554; this is the base table, not a competing class table. Constructor unwind 0x00799DA3 calls Snapshot::~Snapshot (0x0049B47C); 0x00799DAB destroys AsciiString at +4 through 0x0048BA39. The +8 GameClientRandomVariable is initialized as three dwords and passed to setRange 0x002341E7 and xferRandomVariable 0x00306183. Copy construction 0x003A9FBA and assignment 0x003A81AE call string operations 0x000365F0 and 0x000366F0, copy the twelve bytes at +8, the byte at +0x14 and the dword at +0x18. The default constructor clears +0x14 and +0x18. DoXfer transfers the +4 string and +0x14 bool through Xfer slots +0x6C and +0x90. Field names identify offsets; the dword's semantic type is unproven.
The folded primary destructor also serves LifeEventModuleInfo, whose table VA 0x00C1C188 has stride 0x18 at 0x003A9951 and a different name getter 0x003A6139 ("LifeEventModuleInfo", VA 0x00C1B984). The distinct tables, names and strides establish separate identities. All declared method bodies remain out of line. */
#pragma once

#ifndef __BFME2_TERRAINCOLLISIONMODULEINFO_H_
#define __BFME2_TERRAINCOLLISIONMODULEINFO_H_

#ifndef __SNAPSHOT_H_
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_REFERENCE_XFER
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "GameClientRandomVariable.h"

class FXList;

namespace FXParticleSystem
{

class TerrainCollisionModuleInfo : public Snapshot
{
public:
    TerrainCollisionModuleInfo();
    TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &that);
    TerrainCollisionModuleInfo &operator=(const TerrainCollisionModuleInfo &that);
    virtual ~TerrainCollisionModuleInfo();

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

    const FXList *getEventFX();

    AsciiString m_04;
    GameClientRandomVariable m_08;
    bool m_14;
    const FXList *m_18;
};

}

using FXParticleSystem::TerrainCollisionModuleInfo;

#endif
