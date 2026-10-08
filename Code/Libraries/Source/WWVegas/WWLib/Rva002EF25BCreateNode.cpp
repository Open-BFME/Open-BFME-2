// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva002EF25B@Rva002F0DD6Tree@@QAEPAXABVRva002F0DD6Value@@@Z @ 0x002EF25B 34B.
// Target evidence: 0x002F0DD6 calls this with the tree as this and consumes the returned node.
// The pool and two-dword copy targets are pinned from retail; type names remain address-derived.
// Leaf _M_create_node: alloc node via rowed pool 0x002EB448 at g_Va00DBD4C8,
// construct pair<const int,int> value at +0x10 via rowed 0x0060C9D9, return node.
// Evidence: callers 0x002F0DFE 0x002F0E17 in Rva002F0DD6Worker.cpp pass value ref;
// node layout +0x10 matches _Rb_tree_node value field; pin spells thiscall void*.
#include <map>

#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"

namespace _STL
{
template <> void _Construct<_STL::pair<const int, int>, _STL::pair<const int, int> >(_STL::pair<const int, int> *, const _STL::pair<const int, int> &);
}

class Rva002F0DD6Value
{
public:
	int first;
	int second;
};

class Rva002F0DD6Tree
{
public:
	void *rva002EF25B(const Rva002F0DD6Value &value);
};

void *Rva002F0DD6Tree::rva002EF25B(const Rva002F0DD6Value &value)
{
	void *node = g_Va00DBD4C8.rva002EB448();
	_STL::_Construct((_STL::pair<const int, int> *)((char *)node + 0x10), (const _STL::pair<const int, int> &)value);
	return node;
}
