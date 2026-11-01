// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva004185E4HitpointsAtLevel@@YAXPAVINI@@PAX1PBX@Z @0x004185E4 123B.
// Target evidence: the HitpointsAtLevel table entry parses Hitpoints then Level; retail inserts into the supplied int map and throws on duplicate keys.
// Structural inference: the float payload is stored as its four-byte representation in the int-valued map entry, matching the target stores.
#include <map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline pair<_Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > >,bool>::pair(_Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > > const &a,bool const &b) : first(a), second(b) {} }
// Inline the iterator step as retail's speed-form insert_unique does.
namespace _STL { template <> __declspec(dllimport) __forceinline _Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > & _Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator--() { _M_node = _Rb_global_inst::_M_decrement(_M_node); return *this; } }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_create_node(pair<int const, int> const &); }
// bfme link decl-only end

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../../../GameEngine/Include/Common/INI/INI.h"

#include "../../../../GameEngine/Include/Common/INI/FieldParse.h"

void Rva004185E4HitpointsAtLevel(INI *ini, void *, void *store, const void *)
{
	union
	{
		float real;
		int bits;
	} hitpoints;
	hitpoints.real = ini->scanReal(ini->getNextSubToken("Hitpoints"));
	int level = ini->scanInt(ini->getNextSubToken("Level"));
	_STL::map<int, int> *entries = (_STL::map<int, int> *)store;
	_STL::pair<int, int> entry;
	entry.first = level;
	entry.second = hitpoints.bits;
	_STL::pair<_STL::map<int, int>::iterator, bool> inserted = entries->insert(entry);
	if (!inserted.second)
		throw INIException(1, "Duplicate hitpoint entries for level %d", level);
}
