// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
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
// prototype this call resolves; Append, Tok, INI and the empty string mirror
// the prototype TU (undefined externals, masked relocs).
class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
	bool nextToken(Rva0033B84ETok *out, const char *seps);
	void reset();

private:
	void *m_data;
};

extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr000B937E(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
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
	void rva000B937EAppend(const char *s, Rva0033B84ETok *b);
};

void Rva000B937E::rva000B937E(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr000B937E(part);
				rva000B937EAppend(s, accum);
				if (!rva000B664E(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			rva000B937EAppend(token, accum);
			if (!rva000B664E(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
