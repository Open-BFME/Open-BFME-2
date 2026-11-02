// Target facts (addresses are RVAs unless marked VA): constructor 0x0039AEBC
// stores VA 0x00C1AD20 at +0; deleting destructor 0x0039AF5A calls 0x0039AD56,
// which stores that same table before restoring Snapshot's VA 0x00BBB554.
// The adjacent VA 0x00C1AD34 belongs to Rva0039ADF3: its constructor 0x0039B0C9
// calls 0x0039AEBC, adds fields at +0x34/+0x38/+0x3C, then installs that table;
// its destructor 0x0039ADF3 restores it and jumps to 0x0039AD56.
// VA 0x00C1AD20 has five slots: 0x0039AF5A, 0x0039AC9C, __purecall 0x0003B810,
// xfer 0x0039AFC8, __purecall. Snapshot has four slots; slot 1 forwards through
// the +0x2C object's slot 1 (0x0039AC9C). Slot 2 is the name slot, overridden
// by the derived table's 0x0039ADFE returning "ExperienceTrackerObject".
// Slot 4 receives a level pointer and a bool at 0x0039AC23/0x0039B24F;
// its derived implementation is 0x0039B57F. The base is abstract and polymorphic.
// Constructor stores prove +0x04 template, +0x08 four-byte string storage,
// +0x0C key, floats +0x10/+0x1C, ints +0x14/+0x18/+0x24/+0x28, bool +0x20,
// +0x2C pointer (new 0x14, ctor 0x0039AE30), +0x30 key. Xfer 0x0039AFC8
// confirms those widths; 0x0039AD56 releases the string at +0x08 via 0x00036410.
// The 0x0039AEBC write at +0x30 and both derived constructors (0x0039B0C9,
// 0x005DB08F) starting their members at +0x34 establish sizeof 0x34.
// isTrainable 0x0039ADAF reads template+0x5E7; getCurrentExperience and
// getVeterancyLevel read +0x10/+0x24 at 0x005C3000/0x00473212. Zero Hour's
// ExperienceTracker.h supplies those accessor names and the scalar accessors;
// 0x0039B16F multiplies by +0x1C. Other fields retain neutral offset names.
// Out-of-line declarations follow the ExperienceTracker ledger rows at
// 0x0039ABFF/AC0C/AC23/AD45/ADB9/B16F/B315/B438/B4EC and 0x003B23AF.
// The string is opaque storage here; its lifetime is managed out of line.

#pragma once

#ifndef __BFME2_EXPERIENCETRACKER_H_
#define __BFME2_EXPERIENCETRACKER_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Snapshot;
class AsciiString;
class ThingTemplate;
class Xfer;
class Overridable;
class Rva0039AE75;
struct ExperienceLevelHandle;
enum ObjectID;

class ExperienceTracker : public Snapshot
{
public:
	ExperienceTracker(const ThingTemplate *thingTemplate);
	virtual ~ExperienceTracker();

	bool isTrainable() const;
	bool rva0039ABFF() const;
	ExperienceLevelHandle rva0039AC0C() const;
	int rva0039AC23(bool notify);
	void rva0039AD45();
	float rva0039ADB9(float experience, int rank) const;
	void rva0039B16F(float experience, bool a, bool b, bool c, bool d, float scale);
	void rva0039B315(float experience, bool a, bool b, bool c, bool d);
	void rva0039B438(const AsciiString &name, bool feedback);
	bool rva0039B4EC(int levels, bool a, bool b);
	void setExperienceSink(ObjectID sink);

	float getCurrentExperience() const { return m_10; }
	int getVeterancyLevel() const { return m_24; }
	float getExperienceScalar() const { return m_1C; }
	void setExperienceScalar(float scalar) { m_1C = scalar; }

protected:
	virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
	virtual const char *GetSnapshotName() const = 0;
#else
	virtual void crc(Xfer *xfer) = 0;
#endif
	virtual void xfer(Xfer *xfer);
	virtual void vslot04(const Overridable *level, bool notify) = 0;

public:
	const ThingTemplate *m_04;
	unsigned char m_08[4];
	int m_0C;
	float m_10;
	int m_14;
	int m_18;
	float m_1C;
	bool m_20;
	int m_24;
	int m_28;
	Rva0039AE75 *m_2C;
	int m_30;
};

#endif
