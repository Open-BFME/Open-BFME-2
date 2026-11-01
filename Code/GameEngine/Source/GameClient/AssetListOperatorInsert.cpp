// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Trimmed from Open-BFME-1
// (Code/GameEngine/Source/GameClient/AssetListOperatorInsert.cpp): only the
// placed AssetList::operator<<(const AssetList&) body is defined here. The
// AsciiString overload stays declared-only so the unmatched-definition gate
// passes. Layout is the donor's: prototype pointer set + layout pad + changed
// flag.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

struct Rva001408C0Target;

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

class AssetList
{
public:
	AssetList &operator <<(const AssetList &other);
	AssetList &operator <<(const AsciiString &name);

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

void *bfmeGoEMEb(void *name);
typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *name);

// ??6AssetList@@QAEAAV0@ABVAsciiString@@@Z
AssetList &AssetList::operator <<(const AsciiString &name)
{
	if (m_prototypes.insert(
		((FindPrototypeFn)bfmeGoEMEb)(name.str())).second)
	{
		m_changed = true;
	}
	return *this;
}

// ??6AssetList@@QAEAAV0@ABV0@@Z
AssetList &AssetList::operator <<(const AssetList &other)
{
	m_prototypes.insert(other.m_prototypes.begin(),
		other.m_prototypes.end());
	m_changed = true;
	return *this;
}

// ?rva000B937E@Rva000B937E@@QAEXPAVINI@@PAX@Z @0x000B937E 234B
// ModelCondition bitstring-list INI driver, same shape as the KindOf driver
// Rva00256499 (System/Rva00256499Parse.cpp): StringBase split plus
// join-append plus the single-token worker below, driven per token.
// The worker is the rowed ModelCondition worker 0x000B664E, so unlike the
// prototype this call resolves.
// The join-append is the shared Rva0049B6AE::append member (rowed, body
// ignores ecx); the string temporaries are the canonical AsciiString.
#include "../../Include/Common/INI/INI.h"

class Rva0049B6AE
{
public:
	void append(const char *s, StringBase<char> *b);
};

__forceinline const char *GetStr000B937E(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

class Rva000B664E
{
public:
	bool rva000B664E(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva000B937E : public Rva000B664E
{
public:
	void rva000B937E(INI *ini, void *extra);
};

void Rva000B937E::rva000B937E(INI *ini, void *extra)
{
	AsciiString *accum = (AsciiString *)extra;
	if (accum != 0)
		accum->clear();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			AsciiString tmp(token);
			AsciiString part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr000B937E(part);
				((Rva0049B6AE *)this)->append(s, (StringBase<char> *)accum);
				if (!rva000B664E(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!rva000B664E(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
