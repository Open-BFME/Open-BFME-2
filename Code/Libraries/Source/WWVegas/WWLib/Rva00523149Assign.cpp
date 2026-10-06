// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00523149@Rva00523149@@QAEAAU1@PBU1@@Z @0x00523149 47B:
// __thiscall assign from pointer (returns *this, ret 4): copies rb_tree
// <AsciiString,AsciiString> at +4 via rowed 0x0052274D with null-checked
// other (neg/sbb/and ternary per ScriptListSwap precedent) and UnicodeString
// at +0x10 via pin 0x00037150. Caller 0x005232D9 in 0x005231B0/282.
#include "unicode_string.h"
#include <utility>
#include <map>
class AsciiString : private StringBase<char> { public: AsciiString(const AsciiString &); };
typedef _STL::pair<const AsciiString, AsciiString> StringPair;
typedef _STL::_Rb_tree<AsciiString, StringPair, _STL::_Select1st<StringPair>, _STL::less<AsciiString>, _STL::allocator<StringPair> > StringPairTree;
struct Rva00523149 {
	char pad0[4];
	StringPairTree m_tree;
	UnicodeString m_str;
	Rva00523149 &rva00523149(const Rva00523149 *other);
};
Rva00523149 &Rva00523149::rva00523149(const Rva00523149 *other)
{
	const StringPairTree *ptree = other ? &other->m_tree : 0;
	m_tree = *ptree;
	m_str.set(other->m_str);
	return *this;
}
