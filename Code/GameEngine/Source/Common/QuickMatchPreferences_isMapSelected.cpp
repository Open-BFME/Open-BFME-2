// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common

#include <stdlib.h>
#include "ascii_string.h"

#include "../../Include/Common/ScalarTypes.h"


AsciiString AsciiStringToQuotedPrintable(AsciiString original);

class PreferenceMap;

namespace _STL
{
template <class _T1, class _T2> struct pair;
template <class _Pair> struct _Select1st;
template <class _Tp> struct less;
template <class _Tp> class allocator;
template <class _Value> struct _Rb_tree_node;

// The tree under the map: only its private key-search worker, the shared
// AsciiString-keyed _M_find rowed at 0x001F8437, is named here.
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree
{
	friend class ::PreferenceMap;

private:
	template <class _KT> _Rb_tree_node<_Value> *_M_find(const _KT &) const throw();
};
}

typedef _STL::pair<const AsciiString, AsciiString> PreferencePair;
typedef _STL::_Rb_tree<AsciiString, PreferencePair, _STL::_Select1st<PreferencePair>,
	_STL::less<AsciiString>, _STL::allocator<PreferencePair> > PreferenceTree;

struct PreferenceNode
{
	char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &key) const
	{
		return (PreferenceNode *)((const PreferenceTree *)this)->_M_find(key);
	}
	PreferenceNode *end() const
	{
		return m_end;
	}

private:
	PreferenceNode *m_end;
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class QuickMatchPreferences : public UserPreferences
{
public:
	Bool isMapSelected(const AsciiString &mapName);
};

// ?isMapSelected@QuickMatchPreferences@@QAE_NABVAsciiString@@@Z
Bool QuickMatchPreferences::isMapSelected(const AsciiString &mapName)
{
	Int ret;
	PreferenceNode *it = find(AsciiStringToQuotedPrintable(mapName));
	if (it == end())
	{
		return true;
	}

	ret = atoi(it->m_value.str());

	return (ret != 0);
}
