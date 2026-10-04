// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// class-gate: allow AsciiString the shared header's compareNoCase may throw, which adds an EH state store retail's 98-byte findGroup lacks (measured 101B); this view declares it non-throwing
//
// GameWindowTransitionsHandler::findGroup (0x001DC01C, 98B), getNewGroup
// (0x001DC4D2, 170B), setGroup (0x001DC252, 243B) and reverse (0x001DC345,
// 231B), ported from Zero Hour's GameClient/GUI/GameWindowTransitions.cpp;
// reverse/symbols.csv pins findGroup, getNewGroup and setGroup at these
// addresses. 0x001DC1FD (85B) is a BFME 2-only handler query with an
// address name: the named group's total frames (TransitionGroup row
// 0x001DBDA4), or 0.
// Target evidence: by-value AsciiString params with EH_prolog and the
// releaseBuffer row 0x00036410; isEmpty early-outs (null plus length
// check); the STLport group list at +0x20; compareNoCase (row 0x00006A00)
// against the group's name at +0xC; getNewGroup news 0x14 bytes, builds
// them with the rowed ctor 0x001DC0C7, names them through the folded
// AsciiString setter rowed as BuildListInfo::setTemplateName (0x001DBC2D)
// and appends through the folded list<int>::push_back.
// ZH's iterator loop gives retail's register assignment; compareNoCase is
// declared non-throwing (it allocates nothing), as retail's missing EH
// state store in findGroup shows; ~StringBase stays out of line (retail
// folds it onto releaseBuffer), so this unit emits no copy of it.
// BFME 2 additions in setGroup and reverse (target evidence): the whole call
// holds the critical section at +0x38 (EnterCriticalSection and
// LeaveCriticalSection imports, EH state 1); +0x54 and +0x58 are cleared and
// +0x5C and +0x60 take TheDisplay's vslots 0x40 and 0x44; a group that is
// dropped gets the rowed rva001DBE17 after (or instead of) its skip; reverse
// returns early on an unknown group and only clears the pending group when
// one was set. /EHsc: retail stores no EH state around the C imports.
#include <list>

template <typename T> class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const throw();
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	~StringBase();
private:
	friend class AsciiString;
	StringBase(const StringBase<T> &src);
	void releaseBuffer();
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &src) : StringBase<char>(src) {}
};

// The 0x14-byte group object and its rowed ctor 0x001DC0C7.
class Rva001DC0EC
{
public:
	Rva001DC0EC();
	char m_pad[0x14];
};
class BuildListInfo
{
public:
	void setTemplateName(AsciiString name); // folded AsciiString setter
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);

typedef bool Bool;

// BFME 2 guards the handler's group pointers with a critical section at
// +0x38, held for the whole call (EH state 1 while it is held).
class BfmeTransitionsLock
{
public:
	BfmeTransitionsLock(void *cs) : m_cs(cs) { EnterCriticalSection(cs); }
	~BfmeTransitionsLock() { LeaveCriticalSection(m_cs); }
private:
	void *m_cs;
};

// TheDisplay's two size queries at vslots 0x40 and 0x44 (BFME 2 layout).
class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
	virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
	virtual int v10(); // +0x40
	virtual int v11(); // +0x44
};
extern Display *TheDisplay;

// TransitionGroup's rowed bodies, on the address-named view.
class Rva001DBDA4
{
public:
	int rva001DBDA4() const; // getTotalFrames
	void rva001DBDC6();      // reverse
	void rva001DBE17();      // BFME 2's step after skip
	void rva001DBE34();      // skip
	void rva001DC164();      // init
};

class TransitionGroup
{
public:
	void init() { ((Rva001DBDA4 *)this)->rva001DC164(); }
	void reverse() { ((Rva001DBDA4 *)this)->rva001DBDC6(); }
	void skip() { ((Rva001DBDA4 *)this)->rva001DBE34(); }
	void bfmeAfterSkip() { ((Rva001DBDA4 *)this)->rva001DBE17(); }
	int getTotalFrames() { return ((Rva001DBDA4 *)this)->rva001DBDA4(); }
	Bool isReversed() { return m_directionMultiplier < 0; }
	Bool isFireOnce() { return m_fireOnce; }
	char m_pad[4];
	int m_directionMultiplier; // +0x04
	int m_currentFrame;        // +0x08
	AsciiString m_name;        // +0x0C
	Bool m_fireOnce;           // +0x10
};
typedef _STL::list<TransitionGroup *> TransitionGroupList;

class GameWindowTransitionsHandler
{
public:
	void setGroup( AsciiString groupName, Bool immidiate );
	void reverse( AsciiString groupName );
	int rva001DC1FD( AsciiString groupName );
	TransitionGroup *getNewGroup( AsciiString name );
private:
	TransitionGroup *findGroup( AsciiString groupName );
	char m_pad[0x20];
	TransitionGroupList m_transitionGroupList; // +0x20
	TransitionGroup *m_currentGroup; // +0x24
	TransitionGroup *m_pendingGroup; // +0x28
	char m_pad2C[0x38 - 0x2C];
	char m_lock[0x18]; // +0x38 CRITICAL_SECTION
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
};

TransitionGroup *GameWindowTransitionsHandler::getNewGroup( AsciiString name )
{
	if(name.isEmpty())
		return NULL;

	// test to see if we're trying to add an already exisitng group.
	if(findGroup(name))
	{
		return NULL;
	}
	TransitionGroup *g = (TransitionGroup *)new Rva001DC0EC;
	((BuildListInfo *)g)->setTemplateName(name);
	((_STL::list<int> *)&m_transitionGroupList)->push_back(*(int *)&g);
	return g;
}

TransitionGroup *GameWindowTransitionsHandler::findGroup( AsciiString groupName )
{
	if(groupName.isEmpty())
		return NULL;

	TransitionGroupList::iterator it = m_transitionGroupList.begin();
	while (it != m_transitionGroupList.end())
	{
		TransitionGroup *g = *it;
		if(groupName.compareNoCase(g->m_name) == 0)
			return g;
		it++;
	}
	return NULL;
}

int GameWindowTransitionsHandler::rva001DC1FD( AsciiString groupName )
{
	int frames = 0;
	TransitionGroup *g = findGroup(groupName);
	if(g)
		frames = g->getTotalFrames();
	return frames;
}

void GameWindowTransitionsHandler::setGroup(AsciiString groupName, Bool immidiate )
{
	BfmeTransitionsLock lock(m_lock);
	m_54 = 0;
	m_58 = 0;
	m_5C = TheDisplay->v10();
	m_60 = TheDisplay->v11();
	if(groupName.isEmpty() && immidiate)
	{
		if(m_currentGroup)
		{
			m_currentGroup->bfmeAfterSkip();
			m_currentGroup = NULL;
		}
	}
	if(immidiate && m_currentGroup)
	{
		m_currentGroup->skip();
		m_currentGroup = findGroup(groupName);
		if(m_currentGroup)
			m_currentGroup->init();
		return;
	}

	if(m_currentGroup)
	{
		if(!m_currentGroup->isFireOnce() && !m_currentGroup->isReversed())
			m_currentGroup->reverse();
		m_pendingGroup = findGroup(groupName);
		if(m_pendingGroup)
			m_pendingGroup->init();
		return;
	}

	m_currentGroup = findGroup(groupName);
	if(m_currentGroup)
		m_currentGroup->init();
}

void GameWindowTransitionsHandler::reverse( AsciiString groupName )
{
	BfmeTransitionsLock lock(m_lock);
	m_54 = 0;
	m_58 = 0;
	m_5C = TheDisplay->v10();
	m_60 = TheDisplay->v11();
	TransitionGroup *g = findGroup(groupName);
	if(!g)
		return;
	if( m_currentGroup == g )
	{
		m_currentGroup->reverse();
		return;
	}
	if( m_pendingGroup == g)
	{
		m_pendingGroup->bfmeAfterSkip();
		m_pendingGroup = NULL;
		return;
	}
	if(m_currentGroup)
	{
		m_currentGroup->skip();
		m_currentGroup->bfmeAfterSkip();
	}
	if(m_pendingGroup)
	{
		m_pendingGroup->skip();
		m_pendingGroup->bfmeAfterSkip();
		m_pendingGroup = NULL;
	}

	m_currentGroup = g;
	m_currentGroup->init();
	m_currentGroup->skip();
	m_currentGroup->reverse();
}
