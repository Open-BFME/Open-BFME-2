// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00171067@TexturePacker@@QAEXABVBFME2ParticleTextureHandle@@@Z @0x00171067 164B:
// find-or-create on the embedded Rva00170BFF tree at +8 (header pointer plus
// count, same layout as the rowed int_ptr tree so the rowed _M_find serves);
// on a miss it builds a zero-Data Rva00170999 through the rowed Get wrapper
// 0x00170A58, copies it (rowed copy ctor 0x001709D7) and inserts the copy
// through the unique-search worker 0x00170DB7, then refreshes the current
// position at +0x14 to the tree's leftmost node and sets the flag at +0x1C.
// Evidence: callees rowed; boundary from int3 padding.
//
// Two live objects in retail, EH state 0 for the Get() temporary and state 1
// for its copy: the copy is made by a helper that takes the temporary by
// const reference, so the ctor argument is the sret call's returned pointer
// and the copy keeps its own frame slot (a named local or a functional cast
// makes the compiler re-materialise the address or elide the copy).
#include <map>
// Inlined here; imported, this unit emits no non-retail out-of-line copies (STLport
// bodies verbatim). A declaration-only form left _M_find calling it out of line.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(const unsigned int &x, const unsigned int &y) const { return x < y; }
}
// Compare tree nodes locally so this TU does not emit an iterator-base operator!= copy.
namespace _STL {
template <class V, class Traits>
static inline bool operator!=(const _Rb_tree_iterator<V, Traits> &a, const _Rb_tree_iterator<V, Traits> &b)
{ return a._M_node != b._M_node; }
}

class TextureClass
{
public:
	void Release_Ref();
};

class AssetReference
{
public:
	__declspec(noinline) AssetReference(const AssetReference &that) : m_object(that.m_object)
	{
		if (m_object)
			++*(unsigned short *)((char *)m_object + 4);
	}
	TextureClass *m_object;
};

#include "../../Include/Common/Rva00170999Data.h"

class Rva00170999
{
	AssetReference m_asset;
	Rva00170999Data m_data;
public:
	__declspec(noinline) Rva00170999(const AssetReference &a, const Rva00170999Data &d) : m_asset(a), m_data(d) {}
	__declspec(noinline) Rva00170999(const Rva00170999 &that) : m_asset(that.m_asset), m_data(that.m_data) {}
	~Rva00170999()
	{
		if (m_asset.m_object) {
			m_asset.m_object->Release_Ref();
		}
	}
};

__declspec(noinline) inline Rva00170999 __cdecl Rva00170A58Get(const AssetReference &a, const Rva00170999Data &d)
{
	return Rva00170999(a, d);
}

#include "../../Include/Common/Rva00170EFENode.h"

struct Rva00170EFEIter
{
	Rva00170EFENode *node;
	Rva00170EFEIter(Rva00170EFENode *p) : node(p) {}
	Rva00170EFEIter(const Rva00170EFEIter &other) : node(other.node) {}
};

struct Rva00170DB7Out
{
	Rva00170EFENode *node;
	bool inserted;
	Rva00170DB7Out(const Rva00170EFEIter &iter, bool flag)
		: node(iter.node), inserted(flag) {}
};

class Rva00170BFF
{
public:
	Rva00170EFENode *m_00Head;
	unsigned int m_04Flag;
	Rva00170DB7Out rva00170DB7(const Rva00170999 &value);
};

__forceinline void rva00171067Insert(Rva00170BFF &tree, const Rva00170999 &temporary)
{
	Rva00170999 copy(temporary);
	tree.rva00170DB7(copy);
}

// One-pointer texture handle view: the pointer at +0 is the atlas key.
class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
};

class TexturePacker
{
	int m_00;
	int m_04;
	Rva00170BFF m_bff;
	void *m_10;
	void *m_14;
	int m_18;
	bool m_1C;
public:
	void rva00171067(const BFME2ParticleTextureHandle &texture);
};

void TexturePacker::rva00171067(const BFME2ParticleTextureHandle &texture)
{
	if (texture.Ptr == 0) {
		return;
	}
	typedef _STL::map<unsigned, void *> MapIntPtr;
	const unsigned &key = *(const unsigned *)&texture;
	MapIntPtr &mapIntPtr = *(MapIntPtr *)&m_bff;
	if (mapIntPtr.find(key) != mapIntPtr.end()) {
		return;
	}
	rva00171067Insert(m_bff, Rva00170A58Get((const AssetReference &)texture, Rva00170999Data()));
	m_14 = m_bff.m_00Head->_left;
	m_1C = true;
}
