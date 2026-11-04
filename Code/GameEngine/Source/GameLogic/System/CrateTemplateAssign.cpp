// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4CrateTemplate@@QAEAAV0@ABV0@@Z, retail 0x0035CE52 (84B).
// CrateTemplate's implicit copy assignment (Zero Hour `*ct = *defaultCT` and
// `*newOverride = *crateToOverride`): its callers are CrateSystem's
// newCrateTemplateOverride 0x0035CEEB and newCrateTemplate 0x0035CF9E, on the
// object the CrateTemplate ctor 0x0035CC36 just built. Base assign 0x001FD28E
// (pinned as Overridable's, a 5-byte return-this) plus pinned AsciiString
// assign 0x000366F0 plus rowed crateCreationEntryList assign 0x0035CDDF.
#include "ascii_string.h"

// Zero Hour CrateSystem.h's record (AsciiString crateName; Real crateChance).
struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};
#include <list>
// The list assignment is CrateSystem.cpp's crateCreationEntryList::operator=.
// bfme link decl-only begin
namespace _STL { template <> list<crateCreationEntry, allocator<crateCreationEntry> > &list<crateCreationEntry, allocator<crateCreationEntry> >::operator=(const list<crateCreationEntry, allocator<crateCreationEntry> > &); }
// bfme link decl-only end
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
	_STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> > m_003C; // +0x3c
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
