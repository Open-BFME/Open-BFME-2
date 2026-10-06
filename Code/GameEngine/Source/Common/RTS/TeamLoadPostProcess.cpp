// cl: /Ireference/shims/bfmelist /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?loadPostProcess@Team@@MAEXXZ, retail 0x003A2339 (107 bytes).
// Identity (target): WorldBuilder's debug Team.cpp:4833..4848 body
// Team::LoadPostProcess sits in the same Team vtable slot (0x0081AF00, after
// ??_GTeam), and retail's callee order agrees: GameLogic::findObjectByID
// over the transfer list, the member-list test
// Object::dlink_isInList_TeamMemberList (0x0028A6C7) against the +0x38 head,
// then the list clear (rowed folded _List_base clear 0x0023DAA5).
// Donor (Zero Hour Team::loadPostProcess): each saved member ID must resolve
// to an object already in the team, else throw SC_INVALID_DATA, which BFME 2
// spells XferException(5, 0) (ctor 0x0060C36E). Layout (target): the
// saved-ID list at +0x12C; ObjectID is held as int, as the folded clear is.
// Shape (inference): retail tests against an end() read once before the loop.
#include <list>

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	bool dlink_isInList_TeamMemberList(Object * const *pListHead) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class Team
{
public:
	virtual void *deleteInstance(int flags);

protected:
	virtual void loadPostProcess();

public:
	bool isInList_TeamMemberList(Object *o) const
	{
		return o->dlink_isInList_TeamMemberList(&m_dlinkhead_TeamMemberList);
	}

private:
	unsigned char m_pad04[0x38 - 0x04];
	Object *m_dlinkhead_TeamMemberList; // +0x38
	unsigned char m_pad3C[0x12C - 0x3C];
	_STL::list<int, _STL::allocator<int> > m_xferMemberIDList; // +0x12C
};

void Team::loadPostProcess()
{
	_STL::list<int, _STL::allocator<int> >::const_iterator it;
	Object *obj;
	_STL::list<int, _STL::allocator<int> >::const_iterator end = m_xferMemberIDList.end();
	for (it = m_xferMemberIDList.begin(); it != end; ++it)
	{
		obj = TheGameLogic->findObjectByID((ObjectID)*it);
		if (obj == 0)
			throw XferException(5, 0);
		if (isInList_TeamMemberList(obj) == false)
			throw XferException(5, 0);
	}
	m_xferMemberIDList.clear();
}
