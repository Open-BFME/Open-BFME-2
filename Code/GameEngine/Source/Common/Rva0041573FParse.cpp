// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /D_STLP_USE_STATIC_LIB
// stlport
//
// Rva0041573F::rva00415218, retail 0x00415218 (163 B). INI field parse for the CrowdResponseTemplate
// container (56 eight-byte slots at +0 and a map at +0x1C0, the layout of the rowed copy 0x0041573F
// and dtor 0x004156BC): builds a MultiIniFieldParse from the rowed table getter 0x0033A495 and the
// table {UnitSpecificSounds} at VA 0x00C3A1F8, runs INI::initFromINIMulti on this, then refuses any slot or map entry whose
// EVA sound id was set. Evidence: target bytes and WorldBuilder twin 0x00C65490 (strings "You cannot
// use EVA: sound overrides in CrowdResponseTemplates"), rowed callees. Container name stays
// address-derived.
#include "Common/INIException.h"
#include <map>
// Keep typed iterator comparisons local; this unit's incidental tree-base
// comparison COMDAT differs from the selected library provider.
namespace _STL {
template <class Value, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<Value, LeftTraits> &a,
                              const _Rb_tree_iterator<Value, RightTraits> &b)
{ return a._M_node != b._M_node; }
// Tree stepping is fully inlined here. Keep its library implementation
// visible without emitting a competing external iterator increment.
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator++()
{ _M_node = _Rb_global_inst::_M_increment(_M_node); return *this; }
}

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *parseTable, unsigned int extraOffset);
private:
	unsigned char m_bytes[0x84];
};

class Rva0041573F;
#include "../../Include/Common/INI/INI.h"

int __cdecl Rva0033A495Get();
void Rva0033DC9CParse(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x0033DC9C

struct Rva00415218Slot { int id; int pad; };

class Rva0041573F
{
public:
	void rva00415218(INI *ini);
private:
	Rva00415218Slot m_slots[56];
	_STL::map<int, int> m_tree;
};

void Rva0041573F::rva00415218(INI *ini)
{
	// Retail's table at VA 0x00C3A1F8: one record and the zero sentinel.
	static const FieldParse table[] =
	{
		{ "UnitSpecificSounds", &Rva0033DC9CParse, 0, 0x1C0 },
		{ 0, 0, 0, 0 }
	};
	MultiIniFieldParse parse;
	parse.add(reinterpret_cast<const FieldParse *>(Rva0033A495Get()), 0);
	parse.add(table, 0);
	ini->initFromINIMulti(this, parse);
	for (unsigned i = 0; i < 56; ++i)
	{
		if (m_slots[i].id != -1)
			throw INIException(3, "You cannot use EVA: sound overrides in CrowdResponseTemplates");
	}
	_STL::map<int, int>::iterator last = m_tree.end();
	for (_STL::map<int, int>::iterator it = m_tree.begin(); it != last; ++it)
	{
		if ((*it).second != -1)
			throw INIException(3, "You cannot use EVA: sound overrides in CrowdResponseTemplates (UnitSpecificSound block)");
	}
}
