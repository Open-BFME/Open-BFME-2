// ?rva00599825@AIDozerManager@@QAEXH@Z
// partial score=0.92 date=2026-09-29
// cl: /GX- /MD
//
// ?rva00599825@AIDozerManager@@QAEXH@Z, retail 0x00599825, 75 bytes.
// Guarded list add: resolve the id via TheGameLogic::findObjectByID, require
// object+0x304 to equal cmp+0x2EC, skip when the id is already in the list
// at +0, else push it. Evidence: rowed findObjectByID 0x00049DC5 and list
// push_back 0x0005548F; TheGameLogic at 0x00DFE78C; unblocks 4.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Object
{
public:
	unsigned char m_pad00[0x94];
	unsigned char m_flag94;
	unsigned char m_pad95[0x304 - 0x95];
	int m_key;
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_flag438;
};

struct Rva599825Cmp
{
	unsigned char m_pad[0x2EC];
	int m_key;
};

namespace _STL
{
template <class T> struct _Nonconst_traits;
template <class T, class Traits> struct _List_iterator
{
	_List_iterator(void *node) : m_node(node) {}
	_List_iterator(const _List_iterator &other) : m_node(other.m_node) {}
	void *m_node;
};
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class _List_base
{
public:
	void clear();
protected:
	void *m_node; // native sentinel pointer at list offset +0
};
template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
public:
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;
	void push_back(const T &x);
	iterator erase(iterator position);
	void pop_front();
};
}

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
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
class Snapshot;
class Thing;
class ModuleData;

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

struct DozerListNode
{
	DozerListNode *m_next;
	DozerListNode *m_prev;
	int m_value;
};

class AIDozerManager
{
public:
	void rva00599825(int id);
	void DoXfer(Xfer *xfer);
	void rva00599EDC();
	void preEmptivelyBuildDozers();
private:
	_STL::list<int> m_ids;
	unsigned char m_pad[0xC - sizeof(_STL::list<int>)];
	Rva599825Cmp *m_cmp;
	bool m_flag10;
};

void AIDozerManager::rva00599825(int id)
{
	int myId = id;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj == 0)
		return;
	if (obj->m_key != m_cmp->m_key)
		return;
	DozerListNode *head = *(DozerListNode **)&m_ids;
	for (DozerListNode *cur = head->m_next; cur != head; cur = cur->m_next) {
		if (cur->m_value == myId)
			return;
	}
	m_ids.push_back(id);
}

// AIDozerManager::DoXfer, retail 0x0059992A, 177 bytes (WorldBuilder name: WB's
// SkirmishAI/AIDozerManager.cpp body carries the __FUNCTION__ string
// "AIDozerManager::DoXfer", asserts numDozers == m_dozers.size() and calls
// XferObjectID, list clear and findObjectByID as retail does).
// Xfer with Version(1,1) plus bool at +0x10 plus uint count plus list<int>
// at +0 via rowed XferObjectID 0x003060B2 with IsStoring/IsLoading split.
// Evidence: rowed clear 0x0023DAA5 and push_back 0x0005548F; same class and
// TU as rowed 0x00599825; caller 0x004EC1D9.
void AIDozerManager::DoXfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_flag10;
	unsigned int count;
	{
		int numDozers = 0;
		DozerListNode *head = *(DozerListNode **)&m_ids;
		for (DozerListNode *cur = head->m_next; cur != head; cur = cur->m_next)
			++numDozers;
		count = (unsigned int)numDozers;
	}
	*xfer == count;
	if (xfer->IsStoring()) {
		DozerListNode *head = *(DozerListNode **)&m_ids;
		for (DozerListNode *cur = head->m_next; cur != head; cur = cur->m_next)
			XferObjectID(xfer, (ObjectID *)&cur->m_value);
	} else if (xfer->IsLoading()) {
		m_ids.clear();
		for (unsigned int i = 0; i < count; ++i) {
			int dozerID = 0;
			XferObjectID(xfer, (ObjectID *)&dozerID);
			m_ids.push_back(dozerID);
		}
	}
}

// Native 0x00599EDC..0x00599F51: discard missing objects and entries whose
// object flags at +0x94 or +0x438 have bit 0. The first node is removed after
// iteration; other nodes are erased while retaining their predecessor.
// Target identity comes from this unit's manager list and GameLogic lookup;
// WB 0x01530830 supplies the same iterator flow. Its subsequent call is named
// preEmptivelyBuildDozers at WB 0x01530980, and native 0x00599D56 is rowed
// under that name in AIDozerManager.cpp.
void AIDozerManager::rva00599EDC()
{
    bool removeFirst = false;
    DozerListNode *head = *(DozerListNode **)&m_ids;
    for (DozerListNode *node = head->m_next; node != head;
         node = node->m_next, head = *(DozerListNode **)&m_ids) {
        Object *obj = TheGameLogic->findObjectByID((ObjectID)node->m_value);
        if (obj == 0 || (obj->m_flag94 & 1) || (obj->m_flag438 & 1)) {
            if (node != head->m_next) {
                node = node->m_prev;
                _STL::list<int>::iterator position(node->m_next);
                m_ids.erase(position);
            } else {
                removeFirst = true;
            }
        }
    }
    if (removeFirst)
        m_ids.pop_front();
    preEmptivelyBuildDozers();
}
