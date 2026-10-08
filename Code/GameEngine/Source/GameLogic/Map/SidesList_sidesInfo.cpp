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
	BuildListInfo *getNext() const { return m_nextBuildList; }
	void setNextBuildList(BuildListInfo *next) { m_nextBuildList = next; }

private:
	char m_body[0x28];
	BuildListInfo *m_nextBuildList; // +0x2C
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

class ScriptList
{
public:
	ScriptList();
	ScriptList(const ScriptList &that);
	virtual ~ScriptList();
	void clear();
	void swap(ScriptList *other);

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
// The faction build-list map's vectors; only the out-of-line push_back
// (0x0032CA14, rowed under the 128-byte placeholder element) is called here.
template <class T, class Alloc = allocator<T> > class vector : public _Vector_base<T, Alloc>
{
public:
	void push_back(const T &x);
};
}

// The faction build-list entry type (128 bytes); its real name is unknown.
struct BfmePod128 { int a[32]; };

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// 0x00148E1A
};

extern NameKeyGenerator *TheNameKeyGenerator;

class SidesInfoStringVector : private _STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> >
{
public:
	__forceinline SidesInfoStringVector() :
		_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> >(
			_STL::allocator<AsciiString>()) {}
	SidesInfoStringVector(const SidesInfoStringVector &that);
	~SidesInfoStringVector();
	void swap(SidesInfoStringVector &other);
	AsciiString *erase(AsciiString *first, AsciiString *last);
	void clear() { erase(m_start, m_finish); }
};

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
	ScriptList *getScriptList() { return &m_scripts; }
	void setScriptList(ScriptList *scripts) { m_scripts.swap(scripts); }	// 0x003297F3 out of line

private:
	BuildListInfo *m_pBuildList;     // +0x00
	Dict m_dict;                     // +0x04
	ScriptList m_scripts;            // +0x08
	SidesInfoStringVector m_strings; // +0x54
};

// Target 0x0032C667..0x0032C6AD: same members as the verified copy ctor,
// with Dict(0), ScriptList(), and the folded empty AsciiString vector base.
// ZH SidesList.cpp (BFME1 6583b3c1) supplies the null build-list initialization; BFME2's
// by-value ScriptList and trailing vector are established by target calls.
SidesInfo::SidesInfo() : m_pBuildList(0) {}

void SidesInfo::init(const Dict *d)
{
	::operator delete(m_pBuildList ? m_pBuildList->deleteInstance(0) : 0);
	m_pBuildList = 0;
	m_dict.clear();
	m_scripts.clear();
	m_strings.clear();
	if (d)
		m_dict = *d;
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
		for (BuildListInfo *thatBL = that.m_pBuildList; thatBL; thatBL = thatBL->getNext()) {
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

class SidesListNotifier
{
public:
	struct Post
	{
		void (*callback)();
		void *owner;
	};
	struct PostIndexed
	{
		void (*callback)();
		void *owner;
		int index;
	};
	void dispatch(const Post *p);
	void dispatchIndexed(const PostIndexed *p);
	void post(void (*callback)(), void *owner, int index);
	void post(void (*callback)(), void *owner);
};

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
void Rva005CC208();

class TeamsInfoRec
{
public:
	void clear();

private:
	char m_body[0x1C];
};

// DoXfer's bases: the subsystem interface (vptr plus two words) at +0x00
// and the Snapshot interface at +0x0C, whose DoXfer runs with this at +0x0C.
class Xfer;

struct XferVersion
{
	XferVersion(unsigned char current) : m_version(current), m_currentVersion(current) {}
	unsigned char m_version;
	unsigned char m_currentVersion;
};

// The Xfer slots DoXfer calls (BFME 2 order).
class Xfer
{
public:
#define SIDES_XFER_SLOT(n) virtual void slot##n();
	SIDES_XFER_SLOT(00) SIDES_XFER_SLOT(01) SIDES_XFER_SLOT(02) SIDES_XFER_SLOT(03)
	virtual bool skipsTransfer();				// +0x10, name unknown: true skips the body
	SIDES_XFER_SLOT(05) SIDES_XFER_SLOT(06) SIDES_XFER_SLOT(07) SIDES_XFER_SLOT(08)
	SIDES_XFER_SLOT(09)
	virtual void xferVersion(XferVersion *version);		// +0x28
	SIDES_XFER_SLOT(11)
	virtual void xferSnapshot(void *snapshot);		// +0x30
	SIDES_XFER_SLOT(13) SIDES_XFER_SLOT(14) SIDES_XFER_SLOT(15) SIDES_XFER_SLOT(16)
	SIDES_XFER_SLOT(17) SIDES_XFER_SLOT(18) SIDES_XFER_SLOT(19) SIDES_XFER_SLOT(20)
	SIDES_XFER_SLOT(21) SIDES_XFER_SLOT(22) SIDES_XFER_SLOT(23) SIDES_XFER_SLOT(24)
	SIDES_XFER_SLOT(25) SIDES_XFER_SLOT(26) SIDES_XFER_SLOT(27) SIDES_XFER_SLOT(28)
	SIDES_XFER_SLOT(29) SIDES_XFER_SLOT(30)
	virtual void xferInt(int *value);			// +0x7C
	SIDES_XFER_SLOT(32) SIDES_XFER_SLOT(33) SIDES_XFER_SLOT(34) SIDES_XFER_SLOT(35)
	virtual void xferBool(bool *value);			// +0x90
#undef SIDES_XFER_SLOT
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);	// 0x0060C36E
	XferException(const XferException &that);
	~XferException();

	void *text;
	int tag;
};

enum { XFER_INVALID_DATA = 5 };

class SidesListSubsystemBase
{
public:
	virtual ~SidesListSubsystemBase();
private:
	int m_subsystemData[2];
};

class SidesListSnapshotBase
{
public:
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer) = 0;
	virtual void loadPostProcess();
};

class SidesList : public SidesListSubsystemBase, public SidesListSnapshotBase
{
public:
	virtual ~SidesList();
	int addSide(const Dict *d);
	SidesInfo *getSideInfo(int side);				// 0x002035BA
	virtual void DoXfer(Xfer *xfer);
	void removeSide(int index);
	void duplicateScripts(const SidesList &other);
	void addToFactionBuildListMap(NameKeyType faction, const BfmePod128 &entry, int listType);
	void clear();
	void emptySides();
	void emptyTeams();

private:
	SidesListNotifier m_notifier;             // +0x10
	char m_pad[0x3C - 0x11];
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

int SidesList::addSide(const Dict *d)
{
	int index = m_numSides;
	if (index < 20) {
		m_numSides = index + 1;
		m_sides[index].init(d);
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
	m_notifier.post(Rva005CC208, this, index);
}

// SidesList::getSideInfo, retail 0x002035BA: rowed in SidesList_getSideInfo.cpp
// under the struct-key spelling; this class-key copy reproduces the same body
// and is pinned onto it as a proven fold (fold-proof) for DoXfer's call.
SidesInfo *SidesList::getSideInfo(int side)
{
	return (side >= 0 && side < m_numSides) ? &m_sides[side] : 0;
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
	if (xfer->skipsTransfer())
		return;

	XferVersion version(1);
	xfer->xferVersion(&version);

	int i;
	int sideCount = m_numSides;
	xfer->xferInt(&sideCount);
	if (sideCount != m_numSides)
		throw XferException(XFER_INVALID_DATA, 0);

	for (i = 0; i < sideCount; ++i) {
		SidesInfo *sideInfo = getSideInfo(i);
		ScriptList *scriptList = sideInfo->getScriptList();
		bool scriptListPresent = scriptList != 0;
		xfer->xferBool(&scriptListPresent);
		if ((scriptList == 0 && scriptListPresent == true) ||
			(scriptList != 0 && scriptListPresent == false))
			throw XferException(XFER_INVALID_DATA, 0);
		if (scriptListPresent)
			xfer->xferSnapshot(scriptList);
	}

	xfer->xferBool(&m_cleared);
}

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
