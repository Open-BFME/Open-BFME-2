// Target facts (RVAs unless marked VA): constructors 0x001F353D and 0x001F3550 install VA 0x00BE1548 and write one byte at +0x04; assignment 0x001F3565 copies only that byte. The deleting destructor 0x001F3574 uses an 8-byte element stride, so sizeof is 0x08 with a vptr at +0 and padding at +0x05..+0x07.
// Table VA 0x00BE1548 has four slots: deleting destructor 0x001F3574, LoadPostProcess 0x000B3FD0, non-const GetSnapshotName 0x001F354A ("EmissionVolumeInfo", VA 0x00BE1558), and DoXfer(Xfer &) 0x0047A69C. Destructor 0x0049B47C restores Snapshot's VA 0x00BBB554, whose deleting destructor 0x00001750 uses a 4-byte stride and whose remaining slots are purecall; the derived table store is dead during base teardown.
// Retail 0x003A64D0 and 0x003A6E19 call the copy constructor out of line. TerrainFireEmissionInfo's default constructor 0x003A6D5F inlines the base byte initialization before its own vptr store. The ledger places these members in FXParticleSystem; the byte at +0x04 has no proven source name.

#pragma once

#ifndef CANONICAL_EMISSIONVOLUMEINFO_H
#define CANONICAL_EMISSIONVOLUMEINFO_H

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

class EmissionVolumeInfo : public ::Snapshot
{
public:
	EmissionVolumeInfo() : m_04(false) {}
	EmissionVolumeInfo(const EmissionVolumeInfo &that);
	EmissionVolumeInfo &operator=(const EmissionVolumeInfo &that);
	virtual ~EmissionVolumeInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(::Xfer &xfer);

	bool m_04;
};

}

using FXParticleSystem::EmissionVolumeInfo;

#endif
