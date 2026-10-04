// ?remove@GameWindowTransitionsHandler@@QAEXVAsciiString@@_N@Z
// partial score=0.95 date=2026-10-04
// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// class-gate: allow AsciiString the shared header's compareNoCase may throw, which adds an EH state store retail's 98-byte findGroup lacks (measured 101B); this view declares it non-throwing
//
// GameWindowTransitionsHandler::findGroup (0x001DC01C, 98B) and getNewGroup
// (0x001DC4D2, 170B), ported from Zero Hour's
// GameClient/GUI/GameWindowTransitions.cpp; reverse/symbols.csv pins both
// names at these addresses.
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
#include <list>

typedef bool Bool;
#define FALSE 0

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

// TransitionGroup's window-list walks, rowed on the address-named view.
class Rva001DBDA4
{
public:
	void rva001DBE17(); // after skip: BFME 2's extra per-window step
	void rva001DBE34(); // skip
};

class TransitionGroup
{
public:
	void skip() { ((Rva001DBDA4 *)this)->rva001DBE34(); }
	void bfmeAfterSkip() { ((Rva001DBDA4 *)this)->rva001DBE17(); }
	char m_pad[12];
	AsciiString m_name; // +0x0C
};
typedef _STL::list<TransitionGroup *> TransitionGroupList;

class GameWindowTransitionsHandler
{
public:
	void remove( AsciiString groupName,  Bool skipPending = FALSE );
	TransitionGroup *getNewGroup( AsciiString name );
private:
	TransitionGroup *findGroup( AsciiString groupName );
	char m_pad[0x20];
	TransitionGroupList m_transitionGroupList; // +0x20
	TransitionGroup *m_currentGroup; // +0x24
	TransitionGroup *m_pendingGroup; // +0x28
	char m_pad2C[0x38 - 0x2C];
	char m_lock[0x18]; // +0x38 CRITICAL_SECTION
};

void GameWindowTransitionsHandler::remove( AsciiString groupName,  Bool skipPending )
{
	BfmeTransitionsLock lock(m_lock);
	TransitionGroup *g = findGroup(groupName);
	if(!g)
		return; // BFME 2 (target evidence): an unknown group changes nothing
	if(m_pendingGroup == g)
	{
		if(skipPending)
			m_pendingGroup->skip();
		m_pendingGroup->bfmeAfterSkip();

		m_pendingGroup = NULL;
	}
	if(m_currentGroup == g)
	{
		m_currentGroup->skip();
		m_currentGroup->bfmeAfterSkip();
		m_currentGroup = NULL;
		if(m_pendingGroup)
			m_currentGroup = m_pendingGroup;
	}
}

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
