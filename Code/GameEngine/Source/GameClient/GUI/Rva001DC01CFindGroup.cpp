// cl: /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva001DC01C@Rva001DC01C@@QAEPAXV?$StringBase@D@@@Z @0x001DC01C 98B: find a
// group by name. Evidence: by-value AsciiString param with EH_prolog plus
// releaseBuffer row 0x00036410, isEmpty early-out (null plus length check),
// the STLport list at +0x20, compareNoCase row 0x00006A00 against the
// group's name at +0xC, returns the group or null. Callers 0x001DC1FD
// 0x001DC252 0x001DC42C 0x001DC4D2.
// Shape: Zero Hour's GameWindowTransitionsHandler::findGroup
// (GameClient/GUI/GameWindowTransitions.cpp), which the symbols.csv pin
// names; the address name stays until the class identity is proven (the
// neighbouring rows are AudioManager views). The list walk is ZH's
// iterator loop, which gives retail's register assignment; compareNoCase
// is declared non-throwing (it allocates nothing), as retail's missing EH
// state store shows.
#include <list>

template <typename T> class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const throw();
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	// Out of line: retail folds ~StringBase onto releaseBuffer (pinned at
	// 0x00036410), so this unit emits no private copy of it.
	~StringBase();
private:
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


class TransitionGroup
{
public:
	char m_pad[12];
	StringBase<char> m_name;
};
typedef _STL::list<TransitionGroup *> TransitionGroupList;

class Rva001DC01C
{
public:
	void *rva001DC01C(StringBase<char> groupName);
	char m_pad[0x20];
	TransitionGroupList m_transitionGroupList;
};

void *Rva001DC01C::rva001DC01C(StringBase<char> groupName)
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
