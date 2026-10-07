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

#include <map>
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
extern "C" __declspec(dllimport) int __cdecl fprintf(FILE *fp, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *fp);
extern "C" __declspec(dllimport) char *__cdecl fgets(char *buf, int n, FILE *fp);

typedef bool Bool;
typedef int Int;
typedef float Real;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"
#include "unicode_string.h"

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

protected:
	UnicodeString m_filename;
};

typedef _STL::map<AsciiString, AsciiString> PassMap;
typedef _STL::map<AsciiString, AsciiString> DateMap;
typedef _STL::map<AsciiString, _STL::list<AsciiString, _STL::allocator<AsciiString> > > NickMap;
typedef _STL::map<AsciiString, _STL::list<AsciiString, _STL::allocator<AsciiString> > > ClanMap;

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
extern const char g_Rva0107301CEmptyString[];
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
		GetStringFromRegistry(g_Rva0107301CEmptyString, "MemberName", result);
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
