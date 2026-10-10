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
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
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
#include <vector>
#include "ascii_string.h"

struct XferVersionPair
{
	XferVersionPair(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
	unsigned char minimum, current;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersionPair *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual Xfer &xferSlot20(void *value);
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual Xfer &xferAsciiString(AsciiString *value);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Xfer &xferInt(int *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferBool(bool *value);
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

void XferLivingWorldArmyID(Xfer *xfer, int *armyID);
void XferReinforcementState(Xfer *xfer, void *state);
void XferArmySummaryEntryID(Xfer *xfer, void *entryID);
Xfer *Rva0040E19DXfer(Xfer *xfer, _STL::vector<ScienceType> *sciences);

struct TargetRef00217D4C { void *vtable; int references; };
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
	ArmySummaryEntryRef(ArmySummaryEntry *p) : value(p) { if (value) ++static_cast<TargetRef00217D4C *>(value)->references; }
	ArmySummaryEntryRef(const ArmySummaryEntryRef &x) : value(x.value) { if (value) ++static_cast<TargetRef00217D4C *>(value)->references; }
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
	_STL::vector<ScienceType> m_sciences;         // +0x4C
	int m_58;                                     // +0x58
	unsigned char m_pad5C[0x60 - 0x5C];
	int m_60;                                     // +0x60
	AsciiString m_name64;                         // +0x64
};

void ArmySummary::xfer(Xfer *xfer)
{
	XferVersionPair version(1, 2);
	xfer->xferVersion(&version);
	xfer->xferBool(&m_flag14);
	xfer->xferAsciiString(&m_name18);
	XferLivingWorldArmyID(xfer, &m_armyID);
	xfer->xferAsciiString(&m_name20);
	xfer->xferInt(&m_24);
	xfer->xferInt(&m_28);
	xfer->xferInt(&m_30);
	xfer->xferInt(&m_34);
	xfer->xferInt(&m_38);
	XferReinforcementState(xfer, &m_reinforcement);
	xfer->xferInt(&m_60);
	xfer->xferAsciiString(&m_name64);
	xfer->xferSlot20(&m_58);
	XferArmySummaryEntryID(xfer, &m_entryID);
	if (version.current >= 2)
		Rva0040E19DXfer(xfer, &m_sciences);
	if (xfer->IsLoading())
	{
		int count;
		xfer->xferInt(&count);
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
		xfer->xferInt(&count);
		for (int i = 0; i < count; ++i)
		{
			XferArmySummaryEntryID(xfer, &m_entries[i].m_id);
			m_entries[i].m_entry->xfer(xfer);
		}
	}
}
