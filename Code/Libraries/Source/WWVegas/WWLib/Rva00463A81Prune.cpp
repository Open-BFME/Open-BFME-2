// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00463A81@Rva00463A81@@QAEXXZ @0x00463A81 (82B):
// Purges map<int,void*> at +0x5C erasing entries whose GameLogic::findObjectByID
// returns null or whose Object byte at +0x438 bit0 is set via rowed Rb increment
// and map erase. Evidence: leaf lane 1 caller 0x0046410E TheGameLogic extern
// unblocks 0x004640BE; same shape as Rva0025C010 vector prune but map erase-void.
#pragma optimize("t", on)
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#pragma optimize("", on)

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	unsigned char m_pad438[0x438];
	unsigned char m_flag438;
};

class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva00463A81
{
public:
	void rva00463A81();
private:
	char m_pad5C[0x5C];
	_STL::map<int, void *> m_map5C;
};

void Rva00463A81::rva00463A81()
{
	_STL::map<int, void *>::iterator it = m_map5C.begin();
	while (it != m_map5C.end())
	{
		int key = (*it).first;
		Object *obj = TheGameLogic->findObjectByID((ObjectID)key);
		if (obj == 0 || (obj->m_flag438 & 1) != 0)
		{
			_STL::map<int, void *>::iterator cur = it;
			++it;
			m_map5C.erase(cur);
		}
		else
			++it;
	}
}
