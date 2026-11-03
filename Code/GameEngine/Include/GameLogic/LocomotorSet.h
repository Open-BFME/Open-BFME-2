// Target facts: ctor RVA 0x001E7087 and dtor 0x001E86D0 both store VA 0x00BDE950; the dtor finishes with Snapshot's VA 0x00BBB554 (also restored by RVA 0x0049B47C). The four table entries are deleting dtor 0x001E8F03, empty postprocess 0x000B3FD0, name getter 0x001E70BC ("LocomotorSet" at VA 0x00BDE960), and DoXfer 0x001E8730. There is one Snapshot base at +0 and no additional virtual slots.
// Target facts: ctor 0x001E7087 initializes the pointer vector at +4 (0x00211E58), word +0x10, bytes +0x14/+0x15, words +0x18/+0x1C and float +0x20. Dtor 0x001E86D0 releases the +0x1C/+0x18 strings through 0x00036410. DoXfer 0x001E8730 and addLocomotor 0x001E88CE prove the pointer-vector element and the scalar widths; its three pointers occupy 12 bytes, represented here as opaque storage. setLocomotorAndBaseSpeed 0x001EA2CF consumes strings +0x18/+0x1C and float +0x20. AIUpdateInterface::chooseLocomotorSetExplicit 0x00268A37 places the set at +0x1CC and the next pointer at +0x1F0, bounding sizeof to 0x24.
// Names: Zero Hour's LocomotorSet.h proves m_locomotors, m_validLocomotorSurfaces, m_downhillOnly, getValidSurfaces and isDownhillOnly. FieldParse RVA 0x007DE858 names template +0x150 "ScalesWalls"; 0x001E8917 tests it and 0x001E8920 raises set +0x15, proving m_scalesWalls' property. Other fields retain neutral offset names. Out-of-line methods follow ledger rows 0x001E70C2/0x001E8730/0x001E88CE/0x001EA2CF; clear is called at 0x00268A37 and targets 0x001E7E25. Lifetime bodies remain rowed under Rva001E7087; their declarations emit no replacement bodies.
#pragma once

#ifndef __BFME2_LOCOMOTORSET_H_
#define __BFME2_LOCOMOTORSET_H_

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#if defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_REFERENCE_XFER)
#error LocomotorSet requires Snapshot's const name getter and pointer transfer slot
#endif

class INI;
class Locomotor;
class LocomotorTemplate;
class ThingTemplate;

class LocomotorSet : public Snapshot
{
public:
    LocomotorSet();
    virtual ~LocomotorSet();

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void DoXfer(Xfer *xfer);
#else
    virtual void xfer(Xfer *xfer);
#endif

    void clear();
    void addLocomotor(const LocomotorTemplate *lt, bool flag);
    void xferSelfAndCurLocoPtr(Xfer *xfer, Locomotor **loco);
    void setLocomotorAndBaseSpeed(INI *ini, ThingTemplate *instance);

    int getValidSurfaces() const { return m_validLocomotorSurfaces; }
    bool isDownhillOnly() const { return m_downhillOnly; }

    unsigned char m_locomotors[0x0C];
    int m_validLocomotorSurfaces;
    bool m_downhillOnly;
    bool m_scalesWalls;
    AsciiString m_string18;
    AsciiString m_string1C;
    float m_float20;

private:
    LocomotorSet(const LocomotorSet &);
    LocomotorSet &operator=(const LocomotorSet &);
};

#endif
