// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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
// GameSpyLoginPreferences, reconciled from Zero Hour's
// GameSpyLoginPreferences_* donors (BFME1) with BFME 2's layout. Retail
// tells: the vtable at 0x00C74C48 keeps the thirteen UserPreferences slots
// (deleting dtor, wide load, by-ref load, write, accessors) and appends one
// virtual -- load(AsciiString BY VALUE) at slot 13. The object is 0x44
// bytes: the UserPreferences base (+0x00..+0x13) plus four STLport maps, the
// BFME1 password/nickname/date maps at +0x14/+0x20/+0x2c and BFME 2's added
// clan map at +0x38 (the load body walks pass_, date_, nick_ and clan_
// prefixes into +0x14/+0x20/+0x2c/+0x38 in order). The UserPreferences model
// is the one recovered in Code/GameEngine/Source/Common/UserPreferences.cpp.

#include <stdio.h>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <stdlib.h>
#include <string.h>
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);

void *operator new[](unsigned size);
void operator delete[](void *p);

struct _iobuf;
typedef struct _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *name, const unsigned short *mode);

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"
#include "unicode_string.h"
// Reuse the retail list erase at 0x000BC67A. This unit's allocator view
// otherwise emits a divergent copy that displaces the verified STL owner.
namespace _STL {
template <> list<AsciiString, allocator<AsciiString> >::iterator
list<AsciiString, allocator<AsciiString> >::erase(iterator);
}
// Retail 4EC36C allocates the 12-byte sentinel through the shared byte
// allocator. Keep the constructor visible so caller stack homes stay exact.
#include "../../Include/Common/BucketAlloc.h"
namespace _STL {
template <> inline _List_base<AsciiString, allocator<AsciiString> >::_List_base(const allocator_type &a)
    : _M_node(_STLP_CONVERT_ALLOCATOR(a, _Node), (_Node *)0)
{
    _Node *node = static_cast<_Node *>(BucketAlloc::allocate(sizeof(_Node), 0));
    node->_M_next = node;
    node->_M_prev = node;
    _M_node._M_data = node;
}
}

// bfme link decl-only begin
namespace _STL { template <> _List_node<AsciiString> * list<AsciiString, allocator<AsciiString> >::_M_create_node(AsciiString const &); }
// Bind node erasure to the byte-verified retail provider at RVA 0x000BC67A.
namespace _STL { template <> list<AsciiString, allocator<AsciiString> >::iterator list<AsciiString, allocator<AsciiString> >::erase(iterator); }
namespace _STL { template <> _List_node<AsciiString> * allocator<_List_node<AsciiString> >::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void allocator<_List_node<AsciiString> >::deallocate(_List_node<AsciiString> *, unsigned int) const; }
namespace _STL { template <> _List_node<AsciiString> * _STLP_alloc_proxy<_List_node<AsciiString> *, _List_node<AsciiString>, allocator<_List_node<AsciiString> > >::allocate(unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<_List_node<AsciiString> *, _List_node<AsciiString>, allocator<_List_node<AsciiString> > >::deallocate(_List_node<AsciiString> *, unsigned int); }
namespace _STL { template <> pair<AsciiString const, AsciiString>::~pair(); }
// bfme link decl-only end
// Both preference maps share retail's 24-byte tree header constructor at
// 0x001F0534. Preserve allocator-proxy construction, then use the established
// byte allocator with its explicit null hint, as the retail call does.
namespace _STL {
template <> inline
_Rb_tree_base<pair<const AsciiString, AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::_Rb_tree_base(const allocator_type &a)
    : _M_header(_STLP_CONVERT_ALLOCATOR(a, _Node), (_Node *)0)
{
    _M_header._M_data = static_cast<_Node *>(BucketAlloc::allocate(sizeof(_Node), 0));
}
template <> inline
_Rb_tree_base<pair<const AsciiString, list<AsciiString> >, allocator<pair<const AsciiString, list<AsciiString> > > >::_Rb_tree_base(const allocator_type &a)
    : _M_header(_STLP_CONVERT_ALLOCATOR(a, _Node), (_Node *)0)
{
    _M_header._M_data = static_cast<_Node *>(BucketAlloc::allocate(sizeof(_Node), 0));
}
}
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

// Declaration-only: the rowed map<AsciiString,AsciiString>::operator[] is bound,
// this TU emits no per-flag copy of it or of the tree internals it pulls in.
namespace _STL {
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &);
// The nick/clan map uses the rowed 0x5CAC49 subscript as well. Its generic
// copy here pulls in non-retail node construction and insertion helpers.
template <> list<AsciiString> &map<AsciiString, list<AsciiString>, less<AsciiString>, allocator<pair<const AsciiString, list<AsciiString> > > >::operator[](const AsciiString &);
}

// bfme link decl-only begin
// The list-valued nick/clan map internals (tree destructor and base
// destructor, map::operator[], _M_erase, the node allocator's deallocate,
// tree erase(iterator) and list erase(iterator)) are owned out of line by the
// stlport_string_list_* providers. Declaring them here suppresses this TU's
// per-TU copies, which would otherwise win link order ahead of retail's
// byte-owned copies; the same recipe as the map<AsciiString,AsciiString>
// operator[] above (the kept copies' bodies are byte-identical).
namespace _STL { template <> _Rb_tree<AsciiString,pair<AsciiString const,list<AsciiString,allocator<AsciiString> > >,_Select1st<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > >,less<AsciiString>,allocator<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_base<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > >,allocator<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > >::~_Rb_tree_base(); }
namespace _STL { template <> list<AsciiString,allocator<AsciiString> > & map<AsciiString,list<AsciiString,allocator<AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > >::operator[](AsciiString const &); }
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const,list<AsciiString,allocator<AsciiString> > >,_Select1st<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > >,less<AsciiString>,allocator<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > >::_M_erase(_Rb_tree_node<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > *); }
namespace _STL { template <> void allocator<_Rb_tree_node<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > >::deallocate(_Rb_tree_node<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > *,unsigned int) const; }
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const,list<AsciiString,allocator<AsciiString> > >,_Select1st<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > >,less<AsciiString>,allocator<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > >::erase(_Rb_tree_iterator<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > >,_Nonconst_traits<pair<AsciiString const,list<AsciiString,allocator<AsciiString> > > > >); }
namespace _STL { template <> _List_iterator<AsciiString,_Nonconst_traits<AsciiString> > list<AsciiString,allocator<AsciiString> >::erase(_List_iterator<AsciiString,_Nonconst_traits<AsciiString> >); }
// The two-string tree's destructor, _M_erase and erase(iterator) are the rowed
// stlport_string_pair_cleanup.cpp bodies; this TU only calls them.
namespace _STL { template <> _Rb_tree<AsciiString,pair<AsciiString const,AsciiString>,_Select1st<pair<AsciiString const,AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,AsciiString> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const,AsciiString>,_Select1st<pair<AsciiString const,AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,AsciiString> > >::_M_erase(_Rb_tree_node<pair<AsciiString const,AsciiString> > *); }
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const,AsciiString>,_Select1st<pair<AsciiString const,AsciiString> >,less<AsciiString>,allocator<pair<AsciiString const,AsciiString> > >::erase(_Rb_tree_iterator<pair<AsciiString const,AsciiString>,_Nonconst_traits<pair<AsciiString const,AsciiString> > >); }
// bfme link decl-only end

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

#include "../../Include/Common/UserPreferences.h"

typedef _STL::map<AsciiString, AsciiString> PassMap;
typedef _STL::map<AsciiString, AsciiString> DateMap;
typedef _STL::map<AsciiString, _STL::list<AsciiString, _STL::allocator<AsciiString> > > NickMap;
typedef _STL::map<AsciiString, _STL::list<AsciiString, _STL::allocator<AsciiString> > > ClanMap;
// Reuse the native list-base destructor shared by the existing list providers.
extern template _STL::_List_base<AsciiString,_STL::allocator<AsciiString> >::~_List_base();

// The list-pair teardown chain was instantiated here only as a side effect of
// the list-tree destructor declared-only above; keep the rows this TU owns
// (pair dtor 0x5C9ED3, its deleting dtor 0x5C9F6B and _Destroy 0x5CA16A) with
// explicit instantiations.
typedef _STL::pair<AsciiString const, _STL::list<AsciiString, _STL::allocator<AsciiString> > > NickPair;
template NickPair::~pair();
template void _STL::_Destroy(NickPair *);
// The two-string pair's _Destroy row (0x2C748) is kept the same way: its
// tree's erase helpers are declared-only above.
template void _STL::_Destroy(_STL::pair<AsciiString const, AsciiString> *);


AsciiString AsciiStringToQuotedPrintable(AsciiString original);
AsciiString QuotedPrintableToAsciiString(AsciiString original);
AsciiString obfuscate(AsciiString in);

// Retail vtable 0x00C74C48: the thirteen UserPreferences slots with the
// deleting dtor and write overridden, plus the by-value load appended.
class GameSpyLoginPreferences : public UserPreferences
{
public:
	GameSpyLoginPreferences();
	virtual ~GameSpyLoginPreferences();
	virtual Bool write(void);
	virtual Bool load(AsciiString fname);

	// Writes one list-valued email map with the given key prefix; retail
	// factored the nick_ loop into this helper and reuses it for clan_.
	void Write_Rva005C9DA8(NickMap &emails, const char *prefix, FILE *fp);

	// Reads one list-valued email map entry with the given key prefix;
	// retail factored the nick_ tokenize loop into this helper and reuses
	// it for clan_.
	void ReadEmailList_Rva005CAEA3(NickMap &emails, const char *prefix, UserPreferences::iterator &upIt);

	// Removes one nick from one email's clan list; retail guards with find
	// before subscripting (sibling 0x005CADD3 is the nick-map twin at +0x2c).
	void deleteClan(const AsciiString &email, const AsciiString &nick);
	// Nick-map twin of deleteClan at +0x2c (retail 0x005CADD3).
	void deleteNick(const AsciiString &email, const AsciiString &nick);
	// Adds one nick to one email's clan list at +0x38 when absent (retail
	// 0x005CAE04, 110B); returns true when appended.
	bool rva005CAE04(const AsciiString &email, const AsciiString &nick);
	// Adds one nick to nick list at +0x2c when absent and sets pass/date at
	// +0x14/+0x20 (retail 0x005CACDE, 245B).
	void rva005CACDE(AsciiString email, AsciiString nick, AsciiString pass, AsciiString date);
	// Erases one email key from nick/pass/date maps at +0x2c/+0x14/+0x20 (retail 0x005CABF9).
	void rva005CABF9(AsciiString email);
	AsciiString rva005C9FC4(void);
	_STL::list<AsciiString> rva005CA07D();
	AsciiString rva005CA58E(AsciiString,AsciiString &,AsciiString &,AsciiString &);
	const _STL::list<AsciiString> &rva005CA201(const AsciiString &);
	const _STL::list<AsciiString> &rva005CA211(const AsciiString &);
	const _STL::list<AsciiString> &rva005CA1A0(const AsciiString &,NickMap &);

private:
	PassMap m_emailPasswordMap;
	DateMap m_emailDateMap;
	NickMap m_emailNickMap;
	ClanMap m_emailClanMap;
};

// ??0GameSpyLoginPreferences@@QAE@XZ @0x5CB1B3
GameSpyLoginPreferences::GameSpyLoginPreferences( void )
{
	load("GameSpyLogin.ini");
}

// ??1GameSpyLoginPreferences@@UAE@XZ @0x5CAB59
GameSpyLoginPreferences::~GameSpyLoginPreferences( void )
{
}

// Helper @0x5C9DA8: the nick_ loop from Zero Hour's write, factored out so
// the clan_ map reuses it with its own prefix.
void GameSpyLoginPreferences::Write_Rva005C9DA8(NickMap &emails, const char *prefix, FILE *fp)
{
	NickMap::iterator it = emails.begin();
	while (it != emails.end())
	{
		AsciiString nicks;
		NickMap::mapped_type::iterator listIt = it->second.begin();
		while (listIt != it->second.end())
		{
			((StringBase<char> *)&nicks)->concat(*(const StringBase<char> *)&*listIt);
			char comma = ',';	// operator+=(char), expanded in place as retail does
			((StringBase<char> *)&nicks)->concat(&comma, 1);
			++listIt;
		}
		fprintf(fp, "%s%s = %s\n", prefix, it->first.str(), nicks.str());
		++it;
	}
}

// ?write@GameSpyLoginPreferences@@UAE_NXZ @0x5CA2B3
// Zero Hour's write plus BFME 2's clan_ map, whose loop shares the nick_
// helper above.
Bool GameSpyLoginPreferences::write( void )
{
	if (m_filename.isEmpty())
		return false;

	FILE *fp = _wfopen(m_filename.str(), L"w");
	if (fp)
	{
		fprintf(fp, "lastEmail = %s\n", ((*this)["lastEmail"].str()));
		fprintf(fp, "lastName = %s\n", ((*this)["lastName"].str()));
		fprintf(fp, "useProfiles = %s\n", ((*this)["useProfiles"].str()));

		PassMap::iterator passIt = m_emailPasswordMap.begin();
		while (passIt != m_emailPasswordMap.end())
		{
			AsciiString pass = obfuscate(passIt->second);
			AsciiString quoPass = AsciiStringToQuotedPrintable(pass);
			fprintf(fp, "pass_%s = %s\n", passIt->first.str(), quoPass.str());
			++passIt;
		}

		DateMap::iterator dateIt = m_emailDateMap.begin();
		while (dateIt != m_emailDateMap.end())
		{
			AsciiString date = AsciiStringToQuotedPrintable(dateIt->second);
			fprintf(fp, "date_%s = %s\n", dateIt->first.str(), date.str());
			++dateIt;
		}

		Write_Rva005C9DA8(m_emailNickMap, "nick_", fp);
		Write_Rva005C9DA8(m_emailClanMap, "clan_", fp);

		fclose(fp);
		return true;
	}
	return false;
}

// @0x5CAEA3: the nick_ tokenize loop from Zero Hour's load, factored out
// so the clan_ map reuses it with its own prefix.
void GameSpyLoginPreferences::ReadEmailList_Rva005CAEA3(NickMap &emails, const char *prefix, UserPreferences::iterator &upIt)
{
	const AsciiString &key = upIt->first;
	AsciiString email, nick, nicks;
	email = key.str() + strlen(prefix);
	nicks = upIt->second;
	while (nicks.nextToken(&nick, ","))
	{
		emails[email].push_back(nick);
	}
}

// ?load@GameSpyLoginPreferences@@UAE_NVAsciiString@@@Z @0x5CAF5F
// Zero Hour's load plus BFME 2's clan_ map: pass_ and date_ entries decode
// inline, while the nick_ and clan_ lists share the helper above.
Bool GameSpyLoginPreferences::load(AsciiString fname)
{
	if (!UserPreferences::load(fname))
		return false;

	UserPreferences::iterator upIt = begin();
	while (upIt != end())
	{
		AsciiString key = upIt->first;
		if (key.startsWith("pass_"))
		{
			AsciiString email, pass;
			email = key.str() + 5;
			pass = upIt->second;

			AsciiString quoPass = QuotedPrintableToAsciiString(pass);
			pass = obfuscate(quoPass);

			AsciiString &passSlot = m_emailPasswordMap[email];
			passSlot = pass;
		}
		if (key.startsWith("date_"))
		{
			AsciiString email, date;
			email = key.str() + 5;
			date = upIt->second;

			date = QuotedPrintableToAsciiString(date);

			AsciiString &dateSlot = m_emailDateMap[email];
			dateSlot = date;
		}
		else if (key.startsWith("nick_"))
		{
			ReadEmailList_Rva005CAEA3(m_emailNickMap, "nick_", upIt);
		}
		else if (key.startsWith("clan_"))
		{
			ReadEmailList_Rva005CAEA3(m_emailClanMap, "clan_", upIt);
		}
		++upIt;
	}

	return true;
}

// ?deleteNick@GameSpyLoginPreferences@@QAEXABVAsciiString@@0@Z 0x005CADD3 49B
// Evidence: nick-map (+0x2c) twin of clan remove 0x005CAE72; same find
// 0x001F8437 subscript 0x005CAC49 remove 0x005C9E90; caller 0x00571593.
void GameSpyLoginPreferences::deleteNick(const AsciiString &email, const AsciiString &nick)
{
	if (m_emailNickMap.find(email) != m_emailNickMap.end())
		m_emailNickMap[email].remove(nick);
}

// ?deleteClan@GameSpyLoginPreferences@@QAEXABVAsciiString@@0@Z 0x005CAE72 49B
// Evidence: chain from landed list remove 0x005C9E90; find 0x001F8437 and
// list-map operator[] 0x005CAC49 rowed; map at +0x38 is m_emailClanMap;
// caller 0x0057F920; sibling 0x005CADD3 is the +0x2c nick twin.
void GameSpyLoginPreferences::deleteClan(const AsciiString &email, const AsciiString &nick)
{
	if (m_emailClanMap.find(email) != m_emailClanMap.end())
		m_emailClanMap[email].remove(nick);
}

// ?rva005CAE04@GameSpyLoginPreferences@@QAE_NABVAsciiString@@0@Z 0x005CAE04 110B
// Evidence: gap between 0x005CADD3 and 0x005CAE72 in same TU with same flags;
// four list-map operator[] 0x005CAC49 plus list find 0x001FD9C5 and push_back
// rowed; map at +0x38 is m_emailClanMap; caller 0x0057FA6D; unblocks 0x0057FA1C.
bool GameSpyLoginPreferences::rva005CAE04(const AsciiString &email, const AsciiString &nick)
{
	if (_STL::find(m_emailClanMap[email].begin(), m_emailClanMap[email].end(), nick) == m_emailClanMap[email].end())
	{
		m_emailClanMap[email].push_back(nick);
		return true;
	}
	return false;
}

// ?rva005CACDE@GameSpyLoginPreferences@@QAEXVAsciiString@@000@Z 0x005CACDE 245B
// Evidence: nick map +0x2c plus pass +0x14 date +0x20 same TU same flags;
// four list-map operator[] 0x005CAC49 plus list find 0x001FD9C5 push_back
// 0x001FD868 plus scalar map operator[] 0x002031FB plus set 0x000366F0;
// callers 0x00570387 0x00571F04; unblocks 0x005700A0.
void GameSpyLoginPreferences::rva005CACDE(AsciiString email, AsciiString nick, AsciiString pass, AsciiString date)
{
	if (_STL::find(m_emailNickMap[email].begin(), m_emailNickMap[email].end(), nick) == m_emailNickMap[email].end())
		m_emailNickMap[email].push_back(nick);
	m_emailPasswordMap[email].setCopyInline(pass);
	m_emailDateMap[email].setCopyInline(date);
}

void GameSpyLoginPreferences::rva005CABF9(AsciiString email)
{
	m_emailNickMap.erase(email);
	m_emailPasswordMap.erase(email);
	m_emailDateMap.erase(email);
}

// ?rva005C9FC4@GameSpyLoginPreferences@@QAE?AVAsciiString@@XZ @0x005C9FC4 185B
// Evidence: caller 0x0057F486 constructs GameSpyLoginPreferences at +0x58 and
// calls this for its +0xAC member; finds lastEmail else registry MemberName;
// donor BfmeAptScreenOnlineLoginRefreshState find-lastEmail-else-MemberName;
// lookup via throw() shim (shape-lever: no EH state across find) pinned to
// shared _M_find worker 0x001F8437 like SkirmishPreferences.
bool GetStringFromRegistry(AsciiString path, AsciiString key, AsciiString &val);
struct SkirmishFindNode
{
	unsigned char m_pad[0x14];
	AsciiString m_value;
};
class SkirmishFindMap
{
public:
	SkirmishFindNode *find(const AsciiString &key) const throw();
	SkirmishFindNode *end() const { return m_end; }

private:
	SkirmishFindNode *m_end;
	unsigned char m_unreconstructed[8];
};
AsciiString GameSpyLoginPreferences::rva005C9FC4(void)
{
	AsciiString result;
	const SkirmishFindMap *map;
	SkirmishFindNode *rawIt;
	{
		AsciiString key("lastEmail");
		map = (const SkirmishFindMap *)((const char *)this + 4);
		rawIt = map->find(key);
	}
	PreferenceMap::iterator it = *(PreferenceMap::iterator *)&rawIt;
	if (it == this->end())
		GetStringFromRegistry("", "MemberName", result);
	else
		result = it->second;
	return result;
}

// FUN @0x5C9CDE: retail copy of Zero Hour's WOLLoginMenu obfuscate()
AsciiString obfuscate( AsciiString in )
{
	char *buf = new char[in.getLength() + 1];
	_mbscpy(buf, in.str());
	static const char *xor = "1337Munkee";
	char *c = buf;
	const char *c2 = xor;
	while (*c)
	{
		if (!*c2)
			c2 = xor;
		if (*c != *c2)
			*c = *c++ ^ *c2++;
		else
			c++, c2++;
	}
	AsciiString out = buf;
	delete[] buf;
	return out;
}

// Native 5CA1A0..5CA201 returns a borrowed map value or its lazily
// initialized empty list. The original method spelling is unproven.
const _STL::list<AsciiString> &GameSpyLoginPreferences::rva005CA1A0(const AsciiString &email,NickMap &map)
{
    NickMap::iterator it=map.find(email);
    if(it==map.end()) {
        static _STL::list<AsciiString> empty;
        return empty;
    }
    return it->second;
}
// Native 5CA201..5CA211 and WB15CA7C0 return the helper's borrowed list.
// The nickname map is at +2C; native 5709D1 copies this list via 54D800.
// BFME1 34f59164 getNicksForEmail is a semantic lead; target returns a
// reference here rather than the donor's by-value list and email argument.
const _STL::list<AsciiString> &GameSpyLoginPreferences::rva005CA201(const AsciiString &email)
{
    return rva005CA1A0(email,m_emailNickMap);
}

// Native 5CA211..5CA221 and WB15CA7E0 independently prove the +38
// list-map sibling. Existing load/write establish that map's clan purpose.
// Original accessor spelling is unproven; preserve the address-derived name.
const _STL::list<AsciiString> &GameSpyLoginPreferences::rva005CA211(const AsciiString &email)
{
    return rva005CA1A0(email,m_emailClanMap);
}

// BFME1 34f59164 GameSpyLoginPreferences_getDateForEmail_Thunk.cpp is
// the semantic donor. Native 5CA58E..5CA70E independently establishes
// date-map +20, an eight-character value, and three formatted outputs.
// The original target method spelling is unknown.
struct LoginDateStringView
{
    BfmeStringData<char> *data;
    // ?LoginDateStringView::getCharAt absent-from-retail
    __forceinline char getCharAt(int index) const
    {
        return data ? data->text[index] : 0;
    }
};
AsciiString GameSpyLoginPreferences::rva005CA58E(AsciiString email,
    AsciiString &month,AsciiString &day,AsciiString &year)
{
    if(m_emailDateMap.find(email)==m_emailDateMap.end())
        return AsciiString::TheEmptyString;
    AsciiString fullDate=m_emailDateMap[email];
    if(fullDate.getLength()!=8)
        return AsciiString::TheEmptyString;
    const LoginDateStringView &view=*(const LoginDateStringView *)&fullDate;
    month.format("%c%c",view.getCharAt(0),view.getCharAt(1));
    day.format("%c%c",view.getCharAt(2),view.getCharAt(3));
    year.format("%c%c%c%c",view.getCharAt(4),view.getCharAt(5),
        view.getCharAt(6),view.getCharAt(7));
    return m_emailDateMap[email];
}



// BFME1 34f59164 email-list donor; reviewed against current575ba2b04.
// Native 5CA07D..5CA16A walks nick-map+2C keys, falls back to MemberName,
// and returns a copied AsciiString list. The target method name is unknown.
static __forceinline void emailAppend(_STL::list<AsciiString> &emails,
    _STL::list<AsciiString>::iterator position, const AsciiString &value)
{
    emails.insert(position, value);
}
_STL::list<AsciiString> GameSpyLoginPreferences::rva005CA07D()
{
    _STL::list<AsciiString> emails;
    for (NickMap::iterator it = m_emailNickMap.begin(); it != m_emailNickMap.end(); ++it)
        emails.push_back(it->first);
    if (emails.size() == 0) {
        _STL::list<AsciiString>::iterator position;
        position._M_node = emails.end()._M_node;
        AsciiString memberName;
        GetStringFromRegistry("", AsciiString("MemberName"), memberName);
        emailAppend(emails, position, memberName);
    }
    return emails;
}

// Native cleanup 0x007A0FF9 is the complete 25B state-guarded lifetime cleanup
// of the returned email list. Its internal RET label belongs to this body;
// the full 237B getter and exact native exception graph prove ownership.
