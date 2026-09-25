// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase();
	Int compare(const char *other) const;
	Int compareNoCase(const char *other) const;
	void set(const T *text);
	void trim(void);
	Bool nextToken(StringBase *token, const char *seps);
	void concat(const char *text, Int len);
	void concat(const StringBase &other);
	void concat(char c) { concat(&c, 1); }

protected:
	BfmeStringData<T> *m_data;
};

template <> class StringBase<unsigned short>
{
	friend class UnicodeString;
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	bool isEmpty() const;
	void set(const StringBase &other);
	void concat(const StringBase &other);

protected:
	BfmeStringData<unsigned short> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	static const AsciiString TheEmptyString;

	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString &operator=(const AsciiString &other);
	AsciiString &operator=(const char *text) { set(text); return *this; }

	const char *str() const { return m_data ? &m_data->text[0] : ""; }
	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	void format(const char *fmt, ...);
	void toLower();
	Bool operator==(const char *other) const { return compare(other) == 0; }
	int getLength() const { return m_data ? m_data->length : 0; }
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
	void translate(const char *text);
	const unsigned short *str() const { return m_data ? &m_data->text[0] : L""; }
};

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
			nicks.concat(*listIt);
			nicks.concat(',');
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

// FUN @0x5C9CDE: retail copy of Zero Hour's WOLLoginMenu obfuscate()
AsciiString obfuscate( AsciiString in )
{
	char *buf = new char[in.getLength() + 1];
	strcpy(buf, in.str());
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
