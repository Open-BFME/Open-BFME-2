// cl: /Ireference/shims/bfme2_ascii /Oy- /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00396B25@Rva00396B25@@QAEXXZ @0x00396B25 160B update from Object controlling player name via NameKey map find and Money call stores float evidence callers 0x00399CD9 neighbours 0x0039695E construct and 0x00396E4A remove
#include "ascii_string.h"
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

class Object;
class Player;
class Rva0039B795;
class Rva003B0D7C;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class AsciiString;

class Player
{
public:
	char m_pad00[0x58];
	AsciiString m_name58;
	char m_pad5C[0x360];
};

class Rva003B0D7C
{
public:
	unsigned int rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag);
};

class MapHolder
{
public:
	char m_pad00[0x68];
	_STL::map<int, void *> m_map68;
};

struct AmountAt18
{
	void *m_pad00;
	int m_amount;
};

class Rva00396B25
{
public:
	void rva00396B25();
private:
	char m_pad00[4];
	MapHolder *m_holder04;
	Object *m_object08;
	char m_pad0C[0x40];
	float m_value4C;
};

void Rva00396B25::rva00396B25()
{
	MapHolder *holder = m_holder04;
	Object *obj = m_object08;
	if (obj == 0)
		return;
	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return;
	AsciiString name(player->m_name58);
	int key = TheNameKeyGenerator->nameToKey(name);
	_STL::map<int, int>::iterator it_int = ((_STL::map<int, int> *)&holder->m_map68)->find(key);
	_STL::map<int, AmountAt18>::iterator it = *(_STL::map<int, AmountAt18>::iterator *)&it_int;
	if (it == ((_STL::map<int, AmountAt18> *)&holder->m_map68)->end())
		return;
	int amount = it->second.m_amount;
	((Rva003B0D7C *)((char *)player + 0x90))->rva003B0CB3((unsigned int)amount, (Rva0039B795 *)((char *)player + 0x3BC), true);
	m_value4C = (float)(unsigned int)amount;
}
