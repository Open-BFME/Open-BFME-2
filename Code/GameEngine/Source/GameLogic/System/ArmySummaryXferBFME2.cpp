// ?xfer@ArmySummary@@MAEXPAVXfer@@@Z
// Target 40EE89..40F077, complete494 RET4; WB108BB30 and owned
// ArmySummary entry/query/listener siblings establish the transfer identity.
// The local record view preserves key+reference and refcountAC/B0; unused
// full class fields remain uncertain. Canonical Snapshot supplies the base.
// Keeping vector push_back visible (without a declaration-only specialization)
// lets MSVC preserve the load-loop counter and release base across insertion.
// This closes every prior register, frame and reload residue; no alias pin.
// Local reconstruction from native flow; neighbouring proven C++ is structural
// guidance. No donor source spelling is asserted for the reference handle.
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// ?xfer@ArmySummary@@MAEXPAVXfer@@@Z
// Retail 0x0040EE89..0x0040F077 (494 bytes).
// ArmySummary snapshot transfer (version 2): flag +0x14, name +0x18, army id
// +0x1C, name +0x20, words +0x24/+0x28/+0x30/+0x34/+0x38, reinforcement state
// +0x2C, word +0x60, name +0x64, field +0x58 and entry id +0x3C, then (version
// 2) the science list +0x4C; the entry list +0x40 is transferred as a count
// followed by (entry id, entry body) pairs: on load each entry is a new
// 0xC8-byte ArmySummaryEntry that transfers itself (vslot 3) and is appended
// with its id; on save each stored entry's id and body are written.
// Evidence (target): rowed callees XferLivingWorldArmyID 0x00318D1E
// XferReinforcementState 0x0040C96D XferArmySummaryEntryID 0x0056D63B
// Rva0040E19DXfer 0x0040E19D vector<Rva0040CB11Entry>::reserve 0x0040E135 /
// push_back 0x0040E8D1 ArmySummaryEntry ctor 0x0040C351 operator new and
// ReleaseTreeHintRef00217D4C 0x0007DEEF; Xfer slots 10/36/27/31/20/1 as in
// ObjectFilterCollectionXfer.cpp; ArmySummary members and the +0xAC entry
// reference count as in ArmySummary.cpp. WorldBuilder 0x0108BB30 has the same
// transfer order (plus a debug-only player id).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"

struct XferVersionPair
{
	XferVersionPair(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
	unsigned char minimum, current;
};

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

enum ScienceType
{
	SCIENCE_INVALID = -1
};

void XferLivingWorldArmyID(Xfer *xfer, int *armyID);
void XferReinforcementState(Xfer *xfer, void *state);
void XferArmySummaryEntryID(Xfer *xfer, void *entryID);
// ScienceType is the already owned helper instantiation ABI; it does not
// establish payload semantics. Query40CC3C proves delayed carryover object IDs.
Xfer *Rva0040E19DXfer(Xfer *xfer, _STL::vector<ScienceType> *scalarIds);

#include "../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct ArmySummaryEntryPrimary
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void xfer(Xfer *xfer);
	unsigned char m_pad04[0xAC - 4];
};

class ArmySummaryEntry : public ArmySummaryEntryPrimary, public TargetRef00217D4C
{
public:
	ArmySummaryEntry();
	unsigned char m_padB4[0xC8 - 0xB4];
};

struct ArmySummaryEntryRef
{
	ArmySummaryEntry *value;
	ArmySummaryEntryRef(ArmySummaryEntry *armySummaryEntry) : value(armySummaryEntry) { if (value) ++static_cast<TargetRef00217D4C *>(value)->references; }
	ArmySummaryEntryRef(const ArmySummaryEntryRef &armySummaryEntryRef) : value(armySummaryEntryRef.value) { if (value) ++static_cast<TargetRef00217D4C *>(value)->references; }
	~ArmySummaryEntryRef() { if (value) ReleaseTreeHintRef00217D4C(static_cast<TargetRef00217D4C *>(value)); }
	ArmySummaryEntry *operator->() const { return value; }
};

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry(int id, const ArmySummaryEntryRef &entry) : m_id(id), m_entry(entry) {}
	int m_id;
	ArmySummaryEntryRef m_entry;
};

namespace _STL
{
template <> void vector<Rva0040CB11Entry, allocator<Rva0040CB11Entry> >::reserve(size_t n);

}


#include "Common/Snapshot.h"
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@VRva0040CB11Entry@@V?$allocator@VRva0040CB11Entry@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva0040CB11Entry;
namespace _STL { template <> void vector<Rva0040CB11Entry,allocator<Rva0040CB11Entry> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VRva0040CB11Entry@@@_STL@@QBEXPAVRva0040CB11Entry@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva0040CB11Entry;
namespace _STL { template <> void allocator<Rva0040CB11Entry>::deallocate(Rva0040CB11Entry *,unsigned int) const; }

class ArmySummary : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad04[0x14 - 0x04];
	bool m_flag14;                                // +0x14
	unsigned char m_pad15[3];
	AsciiString m_name18;                         // +0x18
	int m_armyID;                                 // +0x1C
	AsciiString m_name20;                         // +0x20
	int m_24;                                     // +0x24
	int m_28;                                     // +0x28
	int m_reinforcement;                          // +0x2C
	int m_30;                                     // +0x30
	int m_34;                                     // +0x34
	int m_38;                                     // +0x38
	int m_entryID;                                // +0x3C
	_STL::vector<Rva0040CB11Entry> m_entries;     // +0x40
	_STL::vector<ScienceType> m_delayedCarryoverIds; // +4C: existing helper ABI view; query40CC3C proves delayed Object IDs
	int m_58;                                     // +0x58
	unsigned char m_pad5C[0x60 - 0x5C];
	int m_60;                                     // +0x60
	AsciiString m_name64;                         // +0x64
};

void ArmySummary::xfer(Xfer *xfer)
{
	XferVersionPair version(1, 2);
	xfer->operator==(reinterpret_cast<Xfer::Version &>(version));
	xfer->operator==(m_flag14);
	xfer->operator==(m_name18);
	XferLivingWorldArmyID(xfer, &m_armyID);
	xfer->operator==(m_name20);
	xfer->operator==(m_24);
	xfer->operator==(m_28);
	xfer->operator==(m_30);
	xfer->operator==(m_34);
	xfer->operator==(m_38);
	XferReinforcementState(xfer, &m_reinforcement);
	xfer->operator==(m_60);
	xfer->operator==(m_name64);
	xfer->operator==(reinterpret_cast<Coord2D &>(m_58));
	XferArmySummaryEntryID(xfer, &m_entryID);
	if (version.current >= 2)
		Rva0040E19DXfer(xfer, &m_delayedCarryoverIds);
	if (xfer->IsLoading())
	{
		int count;
		xfer->operator==(count);
		m_entries.reserve(count);
		for (int i = 0; i < count; ++i)
		{
			int id;
			XferArmySummaryEntryID(xfer, &id);
			ArmySummaryEntryRef entry(new ArmySummaryEntry);
			entry->xfer(xfer);
			m_entries.push_back(Rva0040CB11Entry(id, entry));
		}
	}
	else
	{
		int count = m_entries.size();
		xfer->operator==(count);
		for (int i = 0; i < count; ++i)
		{
			XferArmySummaryEntryID(xfer, &m_entries[i].m_id);
			m_entries[i].m_entry->xfer(xfer);
		}
	}
}
