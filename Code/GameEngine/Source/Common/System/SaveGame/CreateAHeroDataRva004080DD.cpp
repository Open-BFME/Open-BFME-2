// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?GetStat@CreateAHeroData@@QAE_NABVAsciiString@@PAI@Z @0x004080DD 44B. Identity: CreateAHeroData try-get via StringPayloadMap at +0x50; copies second.value at node+0x14 to out and returns true else false.
// Evidence: map50 at +0x50 in CreateAHeroDataDtor layout; callers 0x408109/0x40A99A pass key and out int and test al; callee _M_find rowed.
#include <map>
#include <vector>
#include <new>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

#include "../../../../Include/Common/TreeHintPayload001F8ACB.h"

typedef _STL::map<AsciiString, TreeHintPayload001F8ACB> StringPayloadMap;

// Home packing (U1 r5): the _Vector_base<BfmeVectorRecord00319C84> constructor (rowed
// 0x00211E58, owner LivingWorldArmy.cpp) is instantiated from the header, out of
// line, ahead of the function; cl then gives the dead allocator temporary no slot
// (retail lea eax,[ebp+0xb]) and keeps the vec home at [ebp-4]. The null path is an
// explicit if/else assignment so the xor edi,edi survives.
// Lazy map-of-vectors at +0x20: find the key in the TreeHint map, else heap a
// 12B vector header (operator new + rowed _Vector_base 0x00211E58), publish it
// through the rowed TreeHint operator[] 0x00218AA4 (explicit specialization
// below, defined in its hint TU), re-find and return the payload vector at
// node+0x14. map::find/end/iterator traffic inlines (this TU's /Ob2, same as
// the StringPayloadMap user above); the _M_find leaf resolves through this
// TU's pinned TreeHintPayload001F8ACB spelling (same 78B key-only ICF body at
// 0x001F8437). Evidence: retail lea/push/call order, and-zero home, re-find
// convergence, [eax+0x14] payload return.
struct TreeHintPayload00217DE3 { int m_val; TreeHintPayload00217DE3() : m_val(0) {} TreeHintPayload00217DE3(const TreeHintPayload00217DE3 &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload00217DE3> TreeHintPair00217DE3;
typedef _STL::map<AsciiString, TreeHintPayload00217DE3, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00217DE3> > TreeHintMap00217DE3;
namespace _STL {
template<> TreeHintPayload00217DE3 &TreeHintMap00217DE3::operator[](const AsciiString &);
}
struct BfmeVectorRecord00319C84;
template _STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::_Vector_base(const _STL::allocator<BfmeVectorRecord00319C84> &);
#include <new>
class Rva00218C2B {
public:
	int rva00218C2B(const AsciiString &key);
private:
	char m_pad[0x20];
	TreeHintMap00217DE3 m_map;
};

int Rva00218C2B::rva00218C2B(const AsciiString &key)
{
	StringPayloadMap::iterator it = ((StringPayloadMap *)&m_map)->find(key);
	if (it != ((StringPayloadMap *)&m_map)->end())
		return it->second.value;
	_STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > *mem = (_STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > *)operator new(sizeof(_STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >));
	_STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > *vec;
	if (mem) { new (mem) _STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >(_STL::allocator<BfmeVectorRecord00319C84>()); vec = mem; } else vec = 0;
	((TreeHintMap00217DE3 *)&m_map)->operator[](key).m_val = (int)vec;
	it = ((StringPayloadMap *)&m_map)->find(key);
	return it->second.value;
}

class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

enum NameKeyType;

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class CreateAHeroData : public Snapshot
{
public:
	bool GetStat(const AsciiString &key, unsigned int *out);
	unsigned int GetStatValue(const NameKeyType *p);
private:
	unsigned char m_pad04[0x4C];
	StringPayloadMap m_map50;
};

bool CreateAHeroData::GetStat(const AsciiString &key, unsigned int *out)
{
	if (out == 0)
		return false;
	StringPayloadMap::iterator it = m_map50.find(key);
	if (it != m_map50.end())
	{
		*out = (*it).second.value;
		return true;
	}
	return false;
}

unsigned int CreateAHeroData::GetStatValue(const NameKeyType *nameKeyType)
{
	if (nameKeyType == 0)
		return 0;
	AsciiString tmp = TheNameKeyGenerator->keyToName(*nameKeyType);
	unsigned int out = 0;
	GetStat(tmp, &out);
	return out;
}
