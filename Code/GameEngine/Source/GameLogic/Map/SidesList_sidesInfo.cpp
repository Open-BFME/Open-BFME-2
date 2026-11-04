// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// BFME2 SidesList.cpp bodies. Donor: ZH GameLogic/Map/SidesList.cpp
// (SidesInfo::~SidesInfo/init, SidesList::clear/emptySides/emptyTeams/addSide).
// BFME2 changes, from retail bytes: ScriptList is held by value (+0x08) and a
// vector<AsciiString> follows at +0x54 (SidesInfo is 0x60 bytes); ZH's
// operator= deep copy of the build list lives in a copy ctor wrapped in
// try/catch(...) and operator= is copy-and-swap; addSide returns the index and
// posts a notification through the member at +0x10, clear() also sets the byte
// at +0xF7C and posts. Callee classes are TU-local stand-ins with pins.
// /G7: addSide scales the index with imul (lea/shl under /G5 and /G6).

class BuildListInfo
{
public:
	BuildListInfo(const BuildListInfo &that);
	virtual void *deleteInstance(int pool);
	__declspec(dllimport) __forceinline void setNextBuildList(BuildListInfo *next) { m_nextBuildList = next; }

private:
	char m_body[0x28];
public:
	BuildListInfo *m_nextBuildList; // +0x2C
private:
	char m_tail[0x80 - 0x30];
};

class Dict
{
public:
	Dict(int prealloc = 0);
	Dict(const Dict &src) : m_data(src.m_data)
	{
		if (m_data)
			++*(short *)m_data;
	}
	~Dict() { releaseData(); }
	void clear();
	Dict &operator=(const Dict &src);
	void swap(Dict &other)
	{
		void *data = m_data;
		m_data = other.m_data;
		other.m_data = data;
	}

private:
	void releaseData();
	void *m_data;
};

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class ScriptList : public Snapshot
{
public:
	ScriptList();
	ScriptList(const ScriptList &that);
	virtual ~ScriptList();
	void clear();
	void swap(ScriptList *other);
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *xfer);

private:
	char m_body[0x48];
};

class AsciiString;

namespace _STL
{
template <class T> class allocator { public: allocator() {} };
template <class T, class Alloc> class _Vector_base
{
public:
	// The target's folded 29-byte empty-vector constructor only initializes
	// its three pointers; it cannot throw and adds no cleanup state here.
	_Vector_base(const Alloc &) throw();
protected:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
// The faction build-list map's vectors call only push_back (0x0032CA14, rowed
// under the 128-byte placeholder); SidesInfo's AsciiString vector uses the rest.
template <class T, class Alloc = allocator<T> > class vector : public _Vector_base<T, Alloc>
{
public:
	__forceinline vector() : _Vector_base<T, Alloc>(Alloc()) {}
	vector(const vector &x);
	~vector();
	void push_back(const T &x);
	void swap(vector &x);
	T *erase(T *first, T *last);
	void clear() { erase(this->m_start, this->m_finish); }
};
// SidesList::operator= copies through the out-of-line copy instantiations.
template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result);
}

// The faction build-list entry type (128 bytes); its real name is unknown.
struct BfmePod128 { int a[32]; };

enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class SidesInfo
{
public:
	SidesInfo();
	SidesInfo(const SidesInfo &that);
	~SidesInfo();
	SidesInfo &operator=(const SidesInfo &that);
	void swap(SidesInfo *other);
	void init(const Dict *d);
	void clear() { init(0); }
	const ScriptList *getScriptList() const { return &m_scripts; }
	__declspec(dllimport) __forceinline ScriptList *getScriptList() { return &m_scripts; }
	void setScriptList(ScriptList *scripts) { m_scripts.swap(scripts); }	// 0x003297F3 out of line

private:
	BuildListInfo *m_pBuildList;     // +0x00
	Dict m_dict;                     // +0x04
	ScriptList m_scripts;            // +0x08
	_STL::vector<AsciiString> m_strings; // +0x54
};

// Target 0x0032C667..0x0032C6AD: same members as the verified copy ctor,
// with Dict(0), ScriptList(), and the folded empty AsciiString vector base.
// ZH SidesList.cpp (BFME1 6583b3c1) supplies the null build-list initialization; BFME2's
// by-value ScriptList and trailing vector are established by target calls.
SidesInfo::SidesInfo() : m_pBuildList(0) {}

void SidesInfo::init(const Dict *dict)
{
	::operator delete(m_pBuildList ? m_pBuildList->deleteInstance(0) : 0);
	m_pBuildList = 0;
	m_dict.clear();
	m_scripts.clear();
	m_strings.clear();
	if (dict)
		m_dict = *dict;
}

SidesInfo::~SidesInfo()
{
	clear();
}

SidesInfo::SidesInfo(const SidesInfo &that) :
	m_pBuildList(0),
	m_dict(that.m_dict),
	m_scripts(that.m_scripts),
	m_strings(that.m_strings)
{
	try {
		BuildListInfo *tail = 0;
		for (BuildListInfo *thatBL = that.m_pBuildList; thatBL; thatBL = thatBL->m_nextBuildList) {
			BuildListInfo *thisBL = new BuildListInfo(*thatBL);
			thisBL->setNextBuildList(0);
			if (tail)
				tail->setNextBuildList(thisBL);
			else
				m_pBuildList = thisBL;
			tail = thisBL;
		}
	} catch (...) {
		::operator delete(m_pBuildList ? m_pBuildList->deleteInstance(0) : 0);
		throw;
	}
}

void SidesInfo::swap(SidesInfo *other)
{
	BuildListInfo *buildList = m_pBuildList;
	m_pBuildList = other->m_pBuildList;
	other->m_pBuildList = buildList;
	m_dict.swap(other->m_dict);
	m_scripts.swap(&other->m_scripts);
	m_strings.swap(other->m_strings);
}

SidesInfo &SidesInfo::operator=(const SidesInfo &that)
{
	SidesInfo(that).swap(this);
	return *this;
}

#include "../../../Include/Common/SidesListNotifier.h"

void SidesListNotifier::post(void (*callback)(), void *owner)
{
	Post p;
	p.callback = callback;
	p.owner = owner;
	dispatch(&p);
}

void SidesListNotifier::post(void (*callback)(), void *owner, int index)
{
	PostIndexed p;
	p.callback = callback;
	p.owner = owner;
	p.index = index;
	dispatchIndexed(&p);
}

// Address-derived callback names: the retail DIR32 operands identify the
// callback addresses, but their semantic names are not established.
void Rva005CB260();
void Rva005CB26A();

// The removal and copy notifications push MSVC's generic vcall thunks for
// listener slots +0x08 and +0x0C (??_9@$B7AE, ??_9@$BM@AE), which retail
// folds with the forwarders at 0x005CC208 and 0x005CB265.
class SidesListListener
{
public:
	virtual void notify00();
	virtual void notify04();
	virtual void notify08();
	virtual void notify0C();
};

typedef void (*SidesListCallback)();
typedef void (SidesListListener::*SidesListListenerSlot)();

inline SidesListCallback sidesListCallback(SidesListListenerSlot slot)
{
	union { SidesListListenerSlot slot; SidesListCallback callback; } u;
	u.slot = slot;
	return u.callback;
}

// SidesList::FactionBuildLists 0x0032DD66 is rowed as Rva0032DD66RangeForward.
struct Rva0032DD66Input;
struct Rva0032DD66Output;
Rva0032DD66Output *__cdecl Rva0032DD66RangeForward(Rva0032DD66Input *first, Rva0032DD66Input *last, Rva0032DD66Output *result);

class TeamsInfoRec
{
public:
	TeamsInfoRec &operator=(const TeamsInfoRec &that);	// 0x0032DDB3, copy-and-swap
	void clear();

private:
	char m_body[0x1C];
};

// DoXfer's bases: the subsystem interface (vptr plus two words) at +0x00
// and the Snapshot interface at +0x0C, whose DoXfer runs with this at +0x0C.
class Xfer;

class Snapshot;
class UnicodeString;
class PooledString;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current) : m_version(current), m_currentVersion(current) {}
	unsigned char m_version;
	unsigned char m_currentVersion;
};

#include "../../../Include/Common/XferException.h"

enum { XFER_INVALID_DATA = 5 };

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class SidesListSnapshotBase
{
public:
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *xfer) = 0;
};

class SidesList : public SubsystemInterface, public SidesListSnapshotBase
{
public:
	virtual ~SidesList();
	SidesList &operator=(const SidesList &that);
	int addSide(const Dict *d);
	SidesInfo *getSideInfo(int side);				// 0x002035BA
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer *xfer);
	void removeSide(int index);
	void duplicateScripts(const SidesList &other);
	void addToFactionBuildListMap(NameKeyType faction, const BfmePod128 &entry, int listType);
	void clear();
	void emptySides();
	void emptyTeams();

private:
	SidesListNotifier m_notifier;             // +0x10
	char m_pad[0x3C - 0x20];
	int m_numSides;                           // +0x3C
	SidesInfo m_sides[20];                    // +0x40
	int m_numSkirmishSides;                   // +0x7C0
	SidesInfo m_skirmishSides[20];            // +0x7C4
	TeamsInfoRec m_teamrec;                   // +0xF44
	TeamsInfoRec m_skirmishTeamrec;           // +0xF60
	bool m_cleared;                           // +0xF7C
	struct FactionBuildLists
	{
		NameKeyType m_faction;                 // "UNASSIGNED" when free
		_STL::vector<BfmePod128> m_lists[2];   // by list type 0 and 1
	};
	FactionBuildLists m_factionBuildLists[20]; // +0xF80, 0x1C each
};

int SidesList::addSide(const Dict *dict)
{
	int index = m_numSides;
	if (index < 20) {
		m_numSides = index + 1;
		m_sides[index].init(dict);
		m_notifier.post(Rva005CB260, this, index);
		return index;
	}
	return -1;
}

// SidesList::removeSide, retail 0x0032D850 (117 bytes): WB names it in
// SidesList.cpp and asserts 0 <= index < m_numSides and m_numSides > 1. The
// later sides swap down one slot, every slot from there on is cleared, and
// the removal is posted with the side's index.
void SidesList::removeSide(int index)
{
	int i;
	for (i = index; i < m_numSides - 1; i++) {
		m_sides[i].swap(&m_sides[i + 1]);
	}
	for (; i < 20; i++) {
		m_sides[i].clear();
	}
	m_numSides--;
	m_notifier.post(sidesListCallback(&SidesListListener::notify08), this, index);
}

// SidesList::duplicateScripts, retail 0x00329A80 (106 bytes): WB names it
// in SidesList.cpp and asserts both lists hold as many sides; each side takes
// a copy of the other list's scripts.
void SidesList::duplicateScripts(const SidesList &other)
{
	for (int i = 0; i < m_numSides; i++) {
		ScriptList scripts(*other.m_sides[i].getScriptList());
		m_sides[i].setScriptList(&scripts);
	}
}

// SidesList::addToFactionBuildListMap, retail 0x0032CDFE (160 bytes): WB
// names it in SidesList.cpp. The entry joins list 0 or 1 of the faction's
// slot, claiming the first "UNASSIGNED" slot for a new faction.
void SidesList::addToFactionBuildListMap(NameKeyType faction, const BfmePod128 &entry, int listType)
{
	int i;
	for (i = 0; i < 20; i++) {
		if (m_factionBuildLists[i].m_faction == faction) {
			if (listType == 0)
				m_factionBuildLists[i].m_lists[0].push_back(entry);
			else if (listType == 1)
				m_factionBuildLists[i].m_lists[1].push_back(entry);
			return;
		}
	}
	for (i = 0; i < 20; i++) {
		if (m_factionBuildLists[i].m_faction == TheNameKeyGenerator->nameToKey("UNASSIGNED")) {
			m_factionBuildLists[i].m_faction = faction;
			if (listType == 0)
				m_factionBuildLists[i].m_lists[0].push_back(entry);
			else if (listType == 1)
				m_factionBuildLists[i].m_lists[1].push_back(entry);
			return;
		}
	}
}

// SidesList::DoXfer, retail 0x00329AEA (212 bytes), the Snapshot override
// (this at SidesList+0x0C): WB names it. Zero Hour's SidesList::xfer body —
// version 1, the side count, each side's script list presence and script
// list — skipped when slot +0x10 says so and followed by the cleared flag.
void SidesList::DoXfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1);
	*xfer == version;

	int i;
	int sideCount = m_numSides;
	*xfer == sideCount;
	if (sideCount != m_numSides)
		throw XferException(XFER_INVALID_DATA, 0);

	for (i = 0; i < sideCount; ++i) {
		SidesInfo *sideInfo = getSideInfo(i);
		ScriptList *scriptList = sideInfo->getScriptList();
		bool scriptListPresent = scriptList != 0;
		*xfer == scriptListPresent;
		if ((scriptList == 0 && scriptListPresent == true) ||
			(scriptList != 0 && scriptListPresent == false))
			throw XferException(XFER_INVALID_DATA, 0);
		if (scriptListPresent)
			*xfer == *scriptList;
	}

	*xfer == m_cleared;
}

// SidesList::LoadPostProcess is the matched empty body in SidesListCtor.cpp.

void SidesList::emptySides()
{
	int i;

	m_numSides = 0;
	m_numSkirmishSides = 0;
	for (i = 0; i < 20; i++) {
		m_sides[i].clear();
		m_skirmishSides[i].clear();
	}
}

void SidesList::emptyTeams()
{
	m_teamrec.clear();
	m_skirmishTeamrec.clear();
}

void SidesList::clear()
{
	emptySides();
	emptyTeams();
	m_cleared = true;
	m_notifier.post(Rva005CB26A, this);
}

// The side arrays copy only their live entries; the notifier is not copied
// and posts the change instead. The folded copy helpers are held under their
// non-const instantiations, which is why the source drops const.
SidesList &SidesList::operator=(const SidesList &that)
{
	if (&that != this) {
		SidesList &src = const_cast<SidesList &>(that);
		SubsystemInterface::operator=(that);
		SidesListSnapshotBase::operator=(that);
		m_numSides = src.m_numSides;
		_STL::copy(src.m_sides, src.m_sides + src.m_numSides, m_sides);
		m_numSkirmishSides = src.m_numSkirmishSides;
		_STL::copy(src.m_skirmishSides, src.m_skirmishSides + src.m_numSkirmishSides, m_skirmishSides);
		m_teamrec = src.m_teamrec;
		m_skirmishTeamrec = src.m_skirmishTeamrec;
		m_cleared = src.m_cleared;
		Rva0032DD66RangeForward((Rva0032DD66Input *)src.m_factionBuildLists, (Rva0032DD66Input *)(src.m_factionBuildLists + 20), (Rva0032DD66Output *)m_factionBuildLists);
		m_notifier.post(sidesListCallback(&SidesListListener::notify0C), this);
	}
	return *this;
}

SidesInfo *Rva0032DD81Copy(SidesInfo *first, SidesInfo *last, SidesInfo *result)
{
	int n = last - first;
	if (n <= 0)
		return result;
	for (; n > 0; --n) {
		*result = *first;
		++first;
		++result;
	}
	return result;
}
