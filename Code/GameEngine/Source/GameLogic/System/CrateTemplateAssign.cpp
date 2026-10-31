// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4CrateTemplate@@QAEAAV0@ABV0@@Z, retail 0x0035CE52 (84B).
// CrateTemplate's implicit copy assignment (Zero Hour `*ct = *defaultCT` and
// `*newOverride = *crateToOverride`): its callers are CrateSystem's
// newCrateTemplateOverride 0x0035CEEB and newCrateTemplate 0x0035CF9E, on the
// object the CrateTemplate ctor 0x0035CC36 just built. Base assign 0x001FD28E
// (pinned as Overridable's, a 5-byte return-this) plus pinned AsciiString
// assign 0x000366F0 plus rowed list assign 0x0035CDDF. The list view keeps
// the record spelling the folded list assignment is rowed under.
#include "ascii_string.h"

struct BfmeStringRecord000B757D
{
	unsigned int word0, word1;
	AsciiString text;
	unsigned int word2;
	unsigned char tail;
	BfmeStringRecord000B757D();
	BfmeStringRecord000B757D(const BfmeStringRecord000B757D &o);
	BfmeStringRecord000B757D &operator=(const BfmeStringRecord000B757D &o);	// out of line: pinned 0x001D9990
};
#include <list>
// bfme link decl-only begin
namespace _STL { template <> _List_iterator<BfmeStringRecord000B757D, _Nonconst_traits<BfmeStringRecord000B757D> > list<BfmeStringRecord000B757D, allocator<BfmeStringRecord000B757D> >::insert(_List_iterator<BfmeStringRecord000B757D, _Nonconst_traits<BfmeStringRecord000B757D> >, BfmeStringRecord000B757D const &); }
// bfme link decl-only end

// Retail's list assignment (0x0035CDDF) erases its tail through the range erase
// at 0x002FECD3, the row ?erase of list<AsciiString>; the call goes there by that name.
namespace _STL {
template <> list<AsciiString, allocator<AsciiString> >::iterator list<AsciiString, allocator<AsciiString> >::erase(iterator, iterator);
template <> __declspec(dllimport) __forceinline
list<BfmeStringRecord000B757D, allocator<BfmeStringRecord000B757D> >::iterator
list<BfmeStringRecord000B757D, allocator<BfmeStringRecord000B757D> >::erase(iterator __first, iterator __last)
{
	typedef list<AsciiString, allocator<AsciiString> > _StringList;
	return iterator((_Node *)((_StringList *)this)->erase(
		_StringList::iterator((_List_node<AsciiString> *)__first._M_node),
		_StringList::iterator((_List_node<AsciiString> *)__last._M_node))._M_node);
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "../../../Include/Common/Overridable.h"

struct SevenInts00035CE52
{
	int v[7];
};

class CrateTemplate : public Overridable
{
public:
	CrateTemplate &operator=(const CrateTemplate &that);
private:
	AsciiString m_0010; // +0x10
	int m_0014; // +0x14
	int m_0018; // +0x18
	SevenInts00035CE52 m_001C; // +0x1c..+0x37 rep movsd 7
	int m_0038; // +0x38
	_STL::list<BfmeStringRecord000B757D, _STL::allocator<BfmeStringRecord000B757D> > m_003C; // +0x3c
	unsigned char m_0040; // +0x40
};

CrateTemplate &CrateTemplate::operator=(const CrateTemplate &that)
{
	Overridable::operator=(that);
	m_0010 = that.m_0010;
	m_0014 = that.m_0014;
	m_0018 = that.m_0018;
	m_001C = that.m_001C;
	m_0038 = that.m_0038;
	m_003C = that.m_003C;
	m_0040 = that.m_0040;
	return *this;
}
