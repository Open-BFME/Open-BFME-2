// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ObjectGuardingHelper::disbandAllGuarders, retail 0x004DF4D5 (89 bytes):
// ?disbandAllGuarders@ObjectGuardingHelper@@QAEXXZ
// Identity (target): WorldBuilder's debug ObjectGuardingHelper.cpp
// ObjectGuardingHelper::disbandAllGuarders calls GameLogic::findObjectByID,
// the guarder list's remove and AICommandInterface::aiIdle, as retail does.
// Body (target): while the guarder id list (+0x24) is not empty, look up its
// first guarder; a vanished one is removed from the list, a live one is
// told to idle (CMD_FROM_AI), which takes it off the list.
// Layout (target): the list's remove is the rowed 12-byte-element body
// 0x002ABFC3 (BfmePod12, equal on the first word), and retail hands it the
// address of the 4-byte id it read from the front node, so the guard
// records are modelled as that 12-byte element keyed by their first word.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "../../Common/GameLogicObjectLookupView.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	AICommandInterface *getCommands() { return &m_commands; }

private:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands; // +0x20
};

#include "object.h"


extern GameLogic *TheGameLogic;

struct BfmePod12 { int a[3]; };
inline bool operator==(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] == y.a[0]; }
// Retail erase(iterator) relinks the node onto the freelist pool head inline
// (pool at VA 0x00DA60E8, head at +0x08; retail 0x002ABB20).
class FreelistPool { public: void *pop(); int m_00; void *m_04; void *m_head; };
extern FreelistPool g_freelistPool;
namespace _STL {
template <> list<BfmePod12>::iterator list<BfmePod12>::erase(iterator __position)
{
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_List_node_base *__next_node = __position._M_node->_M_next;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	*(void **)__position._M_node = g_freelistPool.m_head;
	g_freelistPool.m_head = __position._M_node;
	return iterator((_List_node<BfmePod12> *)__next_node);
}
}

class ObjectGuardingHelper
{
public:
	void disbandAllGuarders();

private:
	unsigned char m_pad00[0x24];
	_STL::list<BfmePod12> m_guarders; // +0x24
};

void ObjectGuardingHelper::disbandAllGuarders()
{
	while (m_guarders.size() > 0)
	{
		ObjectID id = (ObjectID)m_guarders.front().a[0];
		Object *obj = TheGameLogic->findObjectByID(id);
		if (obj == 0)
		{
			m_guarders.remove(*(const BfmePod12 *)&id);
			continue;
		}
		obj->getAI()->getCommands()->aiIdle(CMD_FROM_AI);
	}
}
