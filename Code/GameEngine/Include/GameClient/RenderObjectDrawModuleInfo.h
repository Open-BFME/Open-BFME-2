/* Target facts (RVAs unless marked VA): FXParticleSystem::RenderObjectDrawModuleInfo default constructor 0x00562BB1 and copy constructor 0x003A9AD6 install VA 0x00C1C1B8 at +0. Its four slots are vector deleting destructor 0x003A9B97, empty post-load callback 0x000B3FD0, non-const GetSnapshotName 0x003A6151 (returns "RenderObjectDrawModuleInfo" at VA 0x00C1B9DC), and protected xfer(Xfer *) 0x00562871. The vector destructor passes element stride 0x40 at 0x003A9BAF, proving sizeof 0x40.
Destructor 0x003A9A8B releases the narrow strings at +0x30/+0x20/+0x10 through 0x00036410, then restores Snapshot's VA 0x00BBB554 at 0x003A9AC6. Unwind 0x00781D03 calls Snapshot::~Snapshot at 0x0049B47C on the unchanged receiver. This is a four-byte Snapshot base, not another table of this class; its slots are deleting destructor 0x00001750 and three __purecall entries 0x0003B810. Copy constructor 0x003A9AD6 calls StringBase<char> copy 0x000365F0 at +0x10/+0x20/+0x30; assignment 0x003A7D2E calls narrow-string assignment 0x000366F0 at the same offsets. Unwinds 0x00781D0B and 0x00781D16 destroy the +0x10/+0x20 strings through 0x0048BA39.
Default construction 0x00562BB1 stores bytes at +4/+0x0C, floats at +8/+0x18/+0x28/+0x38, zero dwords at +0x14/+0x24/+0x34 and 8 at +0x1C/+0x2C/+0x3C. Transfer 0x00562871 passes those bytes to Xfer's +0x90 bool slot, the strings to +0x6C, +0x14/+0x24/+0x34 to +0x7C int, floats to +0x70, and +0x1C/+0x2C/+0x3C to XferParticleShaderType 0x00306052. Copy and assignment corroborate every offset through +0x3C. Ledger rows prove the namespace, class key and out-of-line special members. Field labels identify offsets, not original source names. */
#pragma once

#ifndef __BFME2_RENDEROBJECTDRAWMODULEINFO_H_
#define __BFME2_RENDEROBJECTDRAWMODULEINFO_H_

#ifndef __SNAPSHOT_H_
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#ifndef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#endif
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfo : public Snapshot
{
public:
    RenderObjectDrawModuleInfo();
    RenderObjectDrawModuleInfo(const RenderObjectDrawModuleInfo &that);
    RenderObjectDrawModuleInfo &operator=(const RenderObjectDrawModuleInfo &that);
    virtual ~RenderObjectDrawModuleInfo();

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
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

    bool m_04;
    float m_08;
    bool m_0C;
    AsciiString m_10;
    int m_14;
    float m_18;
    int m_1C;
    AsciiString m_20;
    int m_24;
    float m_28;
    int m_2C;
    AsciiString m_30;
    int m_34;
    float m_38;
    int m_3C;

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) && defined(BFME_SNAPSHOT_REFERENCE_XFER)
public:
    // Retail export ?DoXfer@RenderObjectDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z (0x00562871).
    virtual void DoXfer(Xfer &xfer);
#else
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void DoXfer(Xfer *xfer);
#else
    virtual void xfer(Xfer *xfer);
#endif
#endif
};

}

using FXParticleSystem::RenderObjectDrawModuleInfo;

#endif
