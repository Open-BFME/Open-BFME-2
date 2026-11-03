/* Target facts (RVAs unless marked VA): FXParticleSystem::DefaultPhysicsModuleInfo default constructor 0x0055EE5E and copy constructor 0x003A7736 install its exported table VA 0x00C1BCB0 at +0. Its four slots are vector deleting destructor 0x003A77A7, LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x003A612D ("DefaultPhysicsModuleInfo" at VA 0x00C1B950), and DoXfer(Xfer &) 0x0055EECB. The vector destructor passes element stride 0x24, proving sizeof 0x24. Destructor 0x0049B47C restores Snapshot's exported table VA 0x00BBB554; constructor unwind 0x00799A5F invokes that destructor with the unchanged receiver, establishing the four-byte Snapshot base rather than another class table.
Default construction 0x0055EE5E zeros floats +4/+8/+0x0C/+0x10, initializes the three-dword value at +0x14 and calls GameClientRandomVariable::setRange 0x002341E7 on it, then clears bytes +0x20/+0x21. DoXfer 0x0055EECB transfers +0x10 as float, +4 as a coordinate, +0x14 through xferRandomVariable 0x00306183, and +0x20/+0x21 as bool. Assignment 0x003A7776 copies three-dword groups at +4 and +0x14, one dword at +0x10 and the two bytes. Copy construction 0x003A7736 copies the same fields. The exported constructors, assignment, destructor and slot bodies remain out of line. Field names identify offsets rather than original source spellings. */
#pragma once

#ifndef __BFME2_DEFAULTPHYSICSMODULEINFO_H_
#define __BFME2_DEFAULTPHYSICSMODULEINFO_H_

#if !defined(__SNAPSHOT_H_)
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
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "GameClientRandomVariable.h"

namespace FXParticleSystem
{

class DefaultPhysicsModuleInfo : public Snapshot
{
public:
    DefaultPhysicsModuleInfo();
    DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &that);
    DefaultPhysicsModuleInfo &operator=(const DefaultPhysicsModuleInfo &that);
    virtual ~DefaultPhysicsModuleInfo();

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

    Coord3D m_04;
    float m_10;
    GameClientRandomVariable m_14;
    bool m_20;
    bool m_21;
};

}

using FXParticleSystem::DefaultPhysicsModuleInfo;

#endif
