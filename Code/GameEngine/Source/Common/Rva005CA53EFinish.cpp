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
	// Erases one email key from nick/pass/date maps at +0x2c/+0x14/+0x20 (retail 0x005CABF9).
	void rva005CABF9(AsciiString email);
	AsciiString rva005C9FC4(void);

	// Sets the lastEmail preference (retail 0x005CA53E).
	void rva005CA53E(const AsciiString &email);
private:
	PassMap m_emailPasswordMap;
	DateMap m_emailDateMap;
	NickMap m_emailNickMap;
	ClanMap m_emailClanMap;
};
// ?rva005CA53E@GameSpyLoginPreferences@@QAEXABVAsciiString@@@Z 0x005CA53E 80B
// Evidence: hardcoded lastEmail key (string 0x874BC4) via rowed StringBase
// ctor 0x00037BA0; base-map subscript 0x002031FB plus AsciiString assign
// 0x000366F0; temp teardown via releaseBuffer 0x00036410; caller 0x005700A0.
// SHAPE: binding the subscript result to a reference before the assign keeps
// retail's push-email after the operator[] call; the one-liner hoists it.
void GameSpyLoginPreferences::rva005CA53E(const AsciiString &email)
{
	AsciiString key("lastEmail");
	AsciiString &slot = (*this)[key];
	slot = email;
}
