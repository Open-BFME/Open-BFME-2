// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003EDD68@Rva0020DXXXElem@@QAE?AVRva003ED658@@XZ @0x003EDD68 108B ret 4.
// Elem range at +0x1C/+0x20 merged into ObjectCreationList then copy-constructed to out.
// Unblocks 0x0020D86C. Callees rowed or pinned. Offsets match Rva0020DXXXElem in ScriptGlueRva003EDC31.

#include <set>

class Rva003ED9B1
{
public:
	void rva003ED9B1(Rva003ED9B1 const &src);
};

#include "../../../Include/GameLogic/Rva003ED658.h"

class Rva003ED94FDtor
{
public:
    Rva003ED94FDtor();
    ~Rva003ED94FDtor();
    unsigned char m_storage[12];
};


// Native locals use the existing folded19B constructor1F81BF and full58B
// destructor3ED94F directly; a derived cleanup wrapper is not retail.
class Rva0020DXXXElem
{
public:
	Rva003ED658 rva003EDD68();
private:
	char m_pad00[0x1C];
	void **m_begin;
	void **m_end;
};

Rva003ED658 Rva0020DXXXElem::rva003EDD68()
{
	Rva003ED94FDtor list;
	for (void **it = m_begin, *end = m_end; it != end; ++it)
		((Rva003ED9B1 *)&list)->rva003ED9B1(*(Rva003ED9B1 const *)*it);
	return *(Rva003ED658 const *)&list;
}

// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f clean source lead:
// LargeGroupAudioUpdateModuleDataCollectRegisteredKeyMap.cpp. Its key-map
// merge walk guides this recovery; target WB 0x01223730 is in
// LargeGroupAudioUpdate.cpp and asserts per-node UnitWeight/key-list validity.
// Native 0x004ABDDC..0x004ABE51 returns the 12-byte aggregate by hidden pointer,
// visits the tree at this+4, and merges each pointed-to object's member +8.
// Existing opaque helper types are retained; their original spellings are
// not inferred from the donor or from the ObjectCreationList folded ctor.
struct Rva004ABDDCEntry
{
    char pad[8];
    Rva003ED9B1 keys;
};
typedef _STL::_Rb_tree_node<Rva004ABDDCEntry *> Rva004ABDDCNode;
#include "../../../Include/Common/ModuleKeyRegistry.h"
Rva003ED658 Rva004ABE53Dtor::rva004ABDDC()
{
    Rva003ED94FDtor list;
    _STL::_Rb_tree_node_base *end = *reinterpret_cast<_STL::_Rb_tree_node_base **>(&m_entries);
    Rva004ABDDCNode *it = (Rva004ABDDCNode *)end->_M_left;
    for (; it != end; it = (Rva004ABDDCNode *)_STL::_Rb_global<bool>::_M_increment(it))
        ((Rva003ED9B1 *)&list)->rva003ED9B1(it->_M_value_field->keys);
    return *(Rva003ED658 const *)&list;
}
