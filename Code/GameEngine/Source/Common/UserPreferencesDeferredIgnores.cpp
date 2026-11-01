// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// UserPreferences, reconciled from Zero Hour's Common/UserPreferences.cpp.
// Retail tells: the vtable at 0x00C1EF0C lists thirteen slots -- the
// deleting destructor, load(UnicodeString), load(AsciiString), write, the
// four typed getters plus a name-table lookup, getAsciiString, three typed
// setters and setAsciiString -- so BFME 2 made every accessor virtual and
// passes keys by const reference. The file name is a UnicodeString at +0x10
// (the map occupies +4..+0xF); load(AsciiString) widens its leaf name and
// forwards to the wide overload.

#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <utility>
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <stdlib.h>

#include <stdio.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"
#include "unicode_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, AsciiString> > * _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::_M_clone_node(_Rb_tree_node<pair<int const, AsciiString> > *); }
namespace _STL { template <> _Rb_tree_node<pair<int const, AsciiString> > * _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::_M_create_node(pair<int const, AsciiString> const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::_Rb_tree(_Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > > const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHVAsciiString@@@_STL@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> void allocator<_Rb_tree_node<pair<int const ,AsciiString> > >::deallocate(_Rb_tree_node<pair<int const ,AsciiString> > *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBVAsciiString@@V1@@_STL@@V?$allocator@U?$pair@$$CBVAsciiStri:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Rb_tree_base<pair<AsciiString const ,AsciiString>,allocator<pair<AsciiString const ,AsciiString> > >::_Rb_tree_base(allocator<pair<AsciiString const ,AsciiString> > const &); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@U?$pair@$$CBVAsciiString@@V1@@_STL@@V?$allocator@U?$pair@$$CBVAsciiStri:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Rb_tree_base<pair<AsciiString const ,AsciiString>,allocator<pair<AsciiString const ,AsciiString> > >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@V1@@_STL@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Rb_tree_node<pair<AsciiString const ,AsciiString> > * allocator<_Rb_tree_node<pair<AsciiString const ,AsciiString> > >::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@V1@@_STL@@@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> void allocator<_Rb_tree_node<pair<AsciiString const ,AsciiString> > >::deallocate(_Rb_tree_node<pair<AsciiString const ,AsciiString> > *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBHVAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBHVAsciiStrin:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Rb_tree_base<pair<const int, AsciiString>, allocator<pair<const int, AsciiString> > >::_Rb_tree_base(const allocator<pair<const int, AsciiString> > &); }
// Nothing here calls the int-keyed tree base's destructor out of line, so this TU emits no copy of it.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_base<pair<const int, AsciiString>, allocator<pair<const int, AsciiString> > >::~_Rb_tree_base()
{ _M_header.deallocate(_M_header._M_data, 1); }
}
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

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

// The two-string tree's destructor, _M_erase, erase(iterator) and _M_create_node are the
// rowed stlport_string_pair_cleanup.cpp and stlport_rb_tree_hint_asciistring_pair.cpp bodies.
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<AsciiString,pair<AsciiString const,AsciiString>,_Select1st<pair<AsciiString const,AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,AsciiString> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const,AsciiString>,_Select1st<pair<AsciiString const,AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,AsciiString> > >::_M_erase(_Rb_tree_node<pair<AsciiString const,AsciiString> > *); }
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const,AsciiString>,_Select1st<pair<AsciiString const,AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,AsciiString> > >::erase(_Rb_tree_iterator<pair<AsciiString const,AsciiString>,_Nonconst_traits<pair<AsciiString const,AsciiString> > >); }
namespace _STL { template <> _Rb_tree_node<pair<AsciiString const,AsciiString> > * _Rb_tree<AsciiString,pair<AsciiString const,AsciiString>,_Select1st<pair<AsciiString const,AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,AsciiString> > >::_M_create_node(pair<AsciiString const,AsciiString> const &); }
// bfme link decl-only end

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();

	// MSVC lays overloaded virtuals out in reverse declaration order, so
	// load(UnicodeString) takes slot 1 and load(AsciiString) slot 2.
	virtual Bool load(const AsciiString &fname);
	virtual Bool load(const UnicodeString &fname);
	virtual Bool write(void);

	virtual Bool getBool(const AsciiString &key, Bool defaultValue) const;
	virtual Real getReal(const AsciiString &key, Real defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
	virtual Int getEnumIndex(const char *key, const char **names, Int count, Int defaultValue) const;
	virtual AsciiString getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const;

	virtual void setBool(const AsciiString &key, Bool val);
	virtual void setReal(const AsciiString &key, Real val);
	virtual void setInt(const AsciiString &key, Int val);
	virtual void setAsciiString(const AsciiString &key, const AsciiString &val);

	// Conditionally indexed setter (retail 0x003B2322): formats the index
	// with "%d" and either assigns or erases the slot by flag.
	void rva003B2322(const AsciiString &val, Int num, Bool flag);

protected:
	UnicodeString m_filename;
};

// BFME 2's user-data path getter (rowed by address at 0x002360FC).
#include "../../Include/Common/GlobalData.h"

extern class GlobalData *TheWritableGlobalData;

// The int-keyed map contracts are deferred here until their existing
// identity conflicts are repaired; independent string-keyed preferences stay
// in UserPreferences.cpp. Bodies and compiler settings are unchanged.

typedef _STL::map<Int, AsciiString> IgnorePrefMap;

class IgnorePreferences : public UserPreferences
{
public:
	IgnorePreferences();
	virtual ~IgnorePreferences();

	IgnorePrefMap getIgnores(void);
};

// ?getIgnores@IgnorePreferences@@QAE?AV?$map@HVAsciiString@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@3@@_STL@@XZ @0x3B224D
IgnorePrefMap IgnorePreferences::getIgnores(void)
{
	IgnorePrefMap ignores;

	IgnorePreferences::iterator it;
	for (it = begin(); it != end(); ++it)
	{
		AsciiString profileStr = it->first;
		AsciiString lastLoginStr = it->second;
		Int profileID = atoi(profileStr.str());

		ignores[profileID] = lastLoginStr;
	}

	return ignores;
}
