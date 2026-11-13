// cl: /O1 /G7 /MD /EHsc /Oi- /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// stlport
//
// rva00423FD8, retail 0x00423FD8 (429 B). INI block callback for a named "unit"
// definition (WorldBuilder twin 0x0113CF20 carries "Unit must have a name at
// %s:%d" and "Unit type defined more than once, 2nd definition at %s:%d"): reads
// the quoted name, builds a record {name key, filter member, preview selector}
// from a fresh Rva003623E5Member (initialised from two copies of
// KINDOFMASK_NONE) through the FieldParse table {ObjectFilter, PreviewObject},
// refuses a key that is already in the global map at 0x00A03168 and stores
// {member, selector} under it, the selector defaulting to the field at +0x0C of
// the object behind 0x00A03160 when PreviewObject was absent. Evidence: target
// bytes, the WorldBuilder twin and the rowed callees; the map value and the
// object behind 0x00A03160 keep address-derived views. The function name stays
// address-derived.
#include "ascii_string.h"
#include "../../Include/Common/INI/FieldParse.h"
#include <map>
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> bool less<int>::operator()(int const &, int const &) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> _Rb_tree_node<pair<const int, BfmePod8> > *_Rb_tree<int, pair<const int, BfmePod8>, _Select1st<pair<const int, BfmePod8> >, less<int>, allocator<pair<const int, BfmePod8> > >::_M_create_node(const pair<const int, BfmePod8> &); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHUBfmePod8@@@_STL@@@_STL@@@_STL@@QBEPAU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> _Rb_tree_node<pair<const int, BfmePod8> > *allocator<_Rb_tree_node<pair<const int, BfmePod8> > >::allocate(size_t, const void *) const; }
// The hinted insert is the rowed body 0x00422D9A; the dllimport tree helpers this
// unit's STLport configuration names would make its own copy non-retail.
namespace _STL { template <> _Rb_tree<int, pair<const int, BfmePod8>, _Select1st<pair<const int, BfmePod8> >, less<int>, allocator<pair<const int, BfmePod8> > >::iterator _Rb_tree<int, pair<const int, BfmePod8>, _Select1st<pair<const int, BfmePod8> >, less<int>, allocator<pair<const int, BfmePod8> > >::insert_unique(iterator, const pair<const int, BfmePod8> &); }

// Keep the already-inlined node comparison local instead of emitting the
// incompatible shared _Rb_tree_base_iterator::operator!= COMDAT.
namespace _STL {
template<class Value, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<Value, LeftTraits>& left,
                              const _Rb_tree_iterator<Value, RightTraits>& right)
{
	return left._M_node != right._M_node;
}
}

template <class T> __forceinline volatile T &r1_vwrite(T &value) { return *(volatile T *)&value; }

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../Include/Common/INI/INI.h"

void rva00421749(INI *ini, void *instance, void *store, const void *userData);

#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../Include/Common/BfmeFixedStorage0004543D.h"
#include "../../Include/Common/BitFlagsTemplate.h"
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../Include/GameLogic/Module/Rva003623E5Member.h"

class Rva0022AD10Subsystem
{
public:
	char m_pad00[0x0C];
	int m_0C;
};
extern Rva0022AD10Subsystem *TheFormationAssistant;

struct BfmePod8 { int a[2]; };
extern unsigned int g_Va00E03168;
typedef _STL::map<int, BfmePod8> UnitFilterMap;
// Retail shares one out-of-line int-keyed _M_find (0x00388F63) across the integer-keyed maps.
typedef _STL::map<int, _STL::vector<int> *> UnitFilterFindMap;

static __forceinline const char *GetStr00423FD8(const AsciiString &asciiString)
{
	char *t = *(char **)(void *)&asciiString;
	return t ? t + 8 : "";
}

struct Rva00423FD8Record
{
	int key;
	Rva003623E5Member *filter;
	int selector;
};

void rva00423FD8(INI *ini, void *instance, void *store, const void *userData)
{
	AsciiString name = ini->getNextQuotedAsciiString();
	if (name.isEmpty())
		throw INIException(3, "Unit must have a name at %s:%d", GetStr00423FD8(ini->getFilename()), ini->getLineNum());
	Rva00423FD8Record record;
	record.key = TheNameKeyGenerator->nameToKey(name);
	record.filter = new Rva003623E5Member;
	record.filter->initFromStorages(*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE, *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE);
	record.selector = 0;
	FieldParse table[] =
	{
		{ "ObjectFilter", rva00421749, 0, 4 },
		{ "PreviewObject", INI::parseThingTemplate, 0, 8 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(&record, table);
	UnitFilterMap *units = (UnitFilterMap *)&g_Va00E03168;
	UnitFilterFindMap::iterator found = ((UnitFilterFindMap *)units)->find(record.key);
	if (found != ((UnitFilterFindMap *)units)->end())
		throw INIException(3, "Unit type defined more than once, 2nd definition at %s:%d", GetStr00423FD8(ini->getFilename()), ini->getLineNum());
	Rva003623E5Member *kept = record.filter;
	int selector = record.selector ? record.selector : TheFormationAssistant->m_0C;
	BfmePod8 &slot = (*units)[record.key];
	r1_vwrite(slot.a[0]) = (int)kept;
	r1_vwrite(slot.a[1]) = selector;
}
