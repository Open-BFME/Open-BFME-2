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


enum ObjectID
{
	INVALID_ID = 0
};

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

class Object
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct BfmePod12 { int a[3]; };
inline bool operator==(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] == y.a[0]; }

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
