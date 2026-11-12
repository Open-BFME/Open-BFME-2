// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// Retail 0x00171128..0x001711A6, 126 bytes, RET4: find a pointer-keyed
// atlas entry, insert a counted texture reference with a zero rectangle if
// absent, and return the node's sixteen-byte rectangle at +0x14.
// TexturePacker::UpdateResultTexture at 0x001711A6 calls this helper on its
// map at +8; WB names the parent, while this helper's type and method names
// remain address-derived. The +0x10 node key, unsigned comparison and
// rectangle extent are measured from retail, not inferred from a donor.
// The existing unsigned-pointer map supplies only lower_bound traversal.
// The counted-value constructor and hint insertion use their verified owners.
// A single full expression keeps the constructor return and iterator result
// live exactly as retail; named temporaries change the frame and return slot.
#include <map>

class TextureClass
{
public:
	void Release_Ref();
};

class AssetReference {
    TextureClass *m_object;
public:
    AssetReference(const AssetReference &);
    ~AssetReference() { if (m_object) m_object->Release_Ref(); }
};

#include "../../Include/Common/Rva00170999Data.h"

class Rva00170999
{
	AssetReference m_asset;
	Rva00170999Data m_data;
public:
	Rva00170999(const AssetReference &a, const Rva00170999Data &d);
};

#include "../../Include/Common/Rva00170EFENode.h"

struct Rva00170EFEIter
{
	Rva00170EFENode *node;
	Rva00170EFEIter(Rva00170EFENode *p) : node(p) {}
	Rva00170EFEIter(const Rva00170EFEIter &other) : node(other.node) {}
};

class Rva00170BFF
{
	Rva00170EFENode *m_00Head;
	unsigned int m_04Flag;
public:
	Rva00170EFEIter rva00170EFE(Rva00170EFEIter position,
		const Rva00170999 &value);
	Rva00170EFEIter rva0017110B(Rva00170EFEIter position,
		const Rva00170999 &value);
	Rva00170999Data *rva00171128(const AssetReference &ref);
};

typedef _STL::map<unsigned, void *> MapIntPtr;
typedef _STL::_Rb_tree<unsigned, _STL::pair<const unsigned, void *>,
	_STL::_Select1st<_STL::pair<const unsigned, void *> >, _STL::less<unsigned>,
	_STL::allocator<_STL::pair<const unsigned, void *> > > MapIntPtrTree;

// Retail calls the rowed _M_lower_bound (stlport_map_int_ptr_lower.cpp); this
// declaration binds it instead of instantiating a copy here, whose inlined
// less<unsigned> would also emit this unit's /O1 copy (not retail's 0x00758C50).
namespace _STL {
template <> MapIntPtrTree::_Link_type MapIntPtrTree::_M_lower_bound(const unsigned &) const;
}

Rva00170999Data *Rva00170BFF::rva00171128(const AssetReference &ref)
{
	const unsigned &key = *(const unsigned *)&ref;
	MapIntPtr &mapIntPtr = *(MapIntPtr *)this;
	MapIntPtr::iterator it = mapIntPtr.lower_bound(key);
	if (it == mapIntPtr.end()) {
		goto insert;
	}
	if (key >= it->first) {
		goto found;
	}
insert:
	{
		it._M_node = (MapIntPtr::iterator::_Base_ptr)rva0017110B(Rva00170EFEIter((Rva00170EFENode *)it._M_node), Rva00170999(ref, Rva00170999Data())).node;
	}
found:
	return (Rva00170999Data *)((char *)it._M_node + 0x14);
}
