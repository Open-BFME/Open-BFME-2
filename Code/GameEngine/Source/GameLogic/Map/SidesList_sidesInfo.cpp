// cl: /O1 /G7
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
	ScriptList(const ScriptList &that);
	virtual ~ScriptList();
	void clear();
	void swap(ScriptList *other);

private:
	char m_body[0x48];
};

class AsciiString;

class SidesInfoStringVector
{
public:
	SidesInfoStringVector(const SidesInfoStringVector &that);
	~SidesInfoStringVector();
	void swap(SidesInfoStringVector &other);
	AsciiString *erase(AsciiString *first, AsciiString *last);
	void clear() { erase(m_start, m_finish); }

private:
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

class SidesInfo
{
public:
	SidesInfo(const SidesInfo &that);
	~SidesInfo();
	SidesInfo &operator=(const SidesInfo &that);
	void swap(SidesInfo *other);
	void init(const Dict *d);
	void clear() { init(0); }

private:
	BuildListInfo *m_pBuildList;     // +0x00
	Dict m_dict;                     // +0x04
	ScriptList m_scripts;            // +0x08
	SidesInfoStringVector m_strings; // +0x54
};

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
	void post(void (*callback)(), void *owner, int index);
	void post(void (*callback)(), void *owner);
};

// Address-derived callback names: the retail DIR32 operands identify the
// callback addresses, but their semantic names are not established.
void Rva005CB260();
void Rva005CB26A();

class TeamsInfoRec
{
public:
	void clear();

private:
	char m_body[0x1C];
};

class SidesList
{
public:
	int addSide(const Dict *d);
	void clear();
	void emptySides();
	void emptyTeams();

private:
	char m_head[0x10];
	SidesListNotifier m_notifier;             // +0x10
	char m_pad[0x3C - 0x11];
	int m_numSides;                           // +0x3C
	SidesInfo m_sides[20];                    // +0x40
	int m_numSkirmishSides;                   // +0x7C0
	SidesInfo m_skirmishSides[20];            // +0x7C4
	TeamsInfoRec m_teamrec;                   // +0xF44
	TeamsInfoRec m_skirmishTeamrec;           // +0xF60
	bool m_cleared;                           // +0xF7C
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
