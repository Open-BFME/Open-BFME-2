// cl: /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ?rva00358DC2@Rva00358DC2@@QAEXPAURva00358DC2Node@@@Z @0x00358DC2 (59B):
// Rb erase-one: rebalance-for-erase then destroy Rva00358B65 value at +16 and free.
// Evidence: calls 0x00025620 rebalance-erase plus 0x00358B65 dtor plus _free 0x00030830;
// same 59B shape as Rva00383F9C erase 0x00383F9C.

#include <stdlib.h>
#include <map>

class Rva00358B65
{
public:
	~Rva00358B65();
};

struct Rva00358DC2Node : public _STL::_Rb_tree_node_base
{
};

class Rva00358DC2
{
	_STL::_Rb_tree_node_base *m_header;
	int m_count;
public:
	void rva00358DC2(Rva00358DC2Node *pos);
	void rva00358F33(struct Rva00358F33Iterator pos);
};

void Rva00358DC2::rva00358DC2(Rva00358DC2Node *pos)
{
	_STL::_Rb_tree_node_base *toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		pos, m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((Rva00358B65 *)(toDelete + 1))->~Rva00358B65();
	if (toDelete)
		free(toDelete);
	--m_count;
}

// ?rva00358F33@Rva00358DC2@@QAEXURva00358F33Iterator@@@Z @0x00358F33 (17B):
// the map-level erase(iterator) over the erase-one above (its call at
// 0x00358F3C). Retail copies a by-value iterator class into the argument
// slot; the rowed worker spells that slot as its node pointer (the same
// one-word ABI), so the call goes through the worker's address recast to
// the iterator signature, as Rva003992B0Finish.cpp does for its hidden-return
// worker. Skeleton twin of map<int, void *>::erase(iterator) 0x001DD80B.
struct Rva00358F33Iterator
{
	Rva00358DC2Node *m_node;
	Rva00358F33Iterator(const Rva00358F33Iterator &other) : m_node(other.m_node) {}
};
typedef void (Rva00358DC2::*Rva00358F33EraseFn)(Rva00358F33Iterator);

void Rva00358DC2::rva00358F33(Rva00358F33Iterator pos)
{
	Rva00358F33EraseFn erase = (Rva00358F33EraseFn)&Rva00358DC2::rva00358DC2;
	(this->*erase)(pos);
}
