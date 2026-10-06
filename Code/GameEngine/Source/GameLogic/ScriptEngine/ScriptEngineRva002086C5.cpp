// cl: /Ireference/shims/bfme2_ascii /EHs
// stlport
// ?rva002086C5@ScriptEngine@@QAEPAXVAsciiString@@@Z @0x002086C5 134B
// Unlock of 5 free functions (2 ready): findTeam-like lookup via resolveName plus Rva0002C4FD plus find.
// Target evidence: caller 0x003E7CE8 sets ecx to ScriptEngine* (g_Va009FE16C), ret 4 with pointer return,
// neighbours ScriptEngine_dtor 0x002086BD and stlport growth 0x00209952. Recipe: EH with AsciiString temps.
#include "ascii_string.h"
#include <utility>

class AsciiString;
class ScriptEngine;

typedef _STL::pair<AsciiString, AsciiString> TeamKey002086C5;

namespace _STL
{
template <class P> struct _Select1st
{
};
template <class T> struct less
{
};
template <class T> class allocator
{
};
template <class V> struct _Rb_tree_node
{
};
template <class Key, class Value, class ExK, class Cmp, class Alloc> class _Rb_tree
{
	friend class ::ScriptEngine;
	typedef _Rb_tree_node<Value> _Node;
private:
	template <class KT> _Node *_M_find(const KT &) const throw();
};
}

struct TeamLess0019B850 : _STL::less<TeamKey002086C5>
{
};

typedef _STL::pair<const TeamKey002086C5, int> TeamValue002086C5;
typedef _STL::_Rb_tree<TeamKey002086C5, TeamValue002086C5, _STL::_Select1st<TeamValue002086C5>, TeamLess0019B850, _STL::allocator<TeamValue002086C5> > TeamTree002086C5;
typedef _STL::_Rb_tree_node<TeamValue002086C5> TeamNode002086C5;

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

struct Rva0002C4FD : public _STL::pair<const AsciiString, AsciiString>
{
	Rva0002C4FD(const StringBase<char> &a, const StringBase<char> &b);
};

class ScriptEngine : public Rva002046C0Owner
{
public:
	void *rva002086C5(AsciiString name);
private:
	char m_pad[0x190A0];
	TeamTree002086C5 m_owner;
};

void *ScriptEngine::rva002086C5(AsciiString name)
{
	AsciiString resolved = resolveName(name);
	Rva0002C4FD key(*(const StringBase<char> *)&resolved, *(const StringBase<char> *)&name);
	TeamTree002086C5 *owner = (TeamTree002086C5 *)((char *)this + 0x190A0);
	TeamNode002086C5 *found = owner->_M_find(*(const TeamKey002086C5 *)&key);
	if (found != *(TeamNode002086C5 **)owner)
		return (void *)((char *)found + 0x18);
	return 0;
}
