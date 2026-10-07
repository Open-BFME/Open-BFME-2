// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva002E54EA@OptionPreferences@@QAEXXZ, retail 0x002E54EA,
// 83 bytes. Dedicated TU.
//
// Erases the 9 enum-table keys at 0xDBD120 from the base map via rowed
// string-tree erase(key) 0x002E4ED1; table struct shared with
// OptionPreferences_enumDispatch.cpp; caller 0x005194F6. Banked 0.95 stash
// noted lea-edi scheduling early-vs-late plus loop branch jl-vs-jb.

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <stdlib.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

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

struct BfmeEnumTableEntry
{
	const char *m_key;
	const void *m_subtable;
	Int m_count;
};

// Retail enum-dispatch table at 0xDBD120, defined in
// OptionPreferences_enumDispatch.cpp; this TU only references it.
extern BfmeEnumTableEntry BfmeEnumTable[];

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();

	virtual Bool load(const AsciiString &fname);
	virtual Bool load(const class UnicodeString &fname);
	virtual Bool write(void);

	virtual Bool getBool(const AsciiString &key, Bool defaultValue) const;
	virtual float getReal(const AsciiString &key, float defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
	virtual Int getEnumIndex(const char *key, const char **names, Int count, Int defaultValue) const;
	virtual AsciiString getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const;

	virtual void setBool(const AsciiString &key, Bool val);
	virtual void setReal(const AsciiString &key, float val);
	virtual void setInt(const AsciiString &key, Int val);
	virtual void setAsciiString(const AsciiString &key, const AsciiString &val);
};

class OptionPreferences : public UserPreferences
{
public:
	virtual ~OptionPreferences();
	void rva002E54EA();
};

void OptionPreferences::rva002E54EA()
{
	char *base = (char *)this + 4;
	BfmeEnumTableEntry *it = BfmeEnumTable;
	do {
		((PreferenceMap *)base)->erase(it->m_key);
		++it;
	} while ((int)it < (int)(BfmeEnumTable + 9));
}
