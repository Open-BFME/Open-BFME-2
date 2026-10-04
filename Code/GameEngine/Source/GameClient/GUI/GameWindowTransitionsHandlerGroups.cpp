// cl: /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

class TransitionGroup
{
public:
	char m_pad[12];
	AsciiString m_name; // +0x0C
};
typedef _STL::list<TransitionGroup *> TransitionGroupList;

class GameWindowTransitionsHandler
{
public:
	TransitionGroup *getNewGroup( AsciiString name );
private:
	TransitionGroup *findGroup( AsciiString groupName );
	char m_pad[0x20];
	TransitionGroupList m_transitionGroupList; // +0x20
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
