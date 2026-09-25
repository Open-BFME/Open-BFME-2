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
// UserPreferences, reconciled from Zero Hour's Common/UserPreferences.cpp.
// Retail tells: the vtable at 0x00C1EF0C lists thirteen slots -- the
// deleting destructor, load(UnicodeString), load(AsciiString), write, the
// four typed getters plus a name-table lookup, getAsciiString, three typed
// setters and setAsciiString -- so BFME 2 made every accessor virtual and
// passes keys by const reference. The file name is a UnicodeString at +0x10
// (the map occupies +4..+0xF); load(AsciiString) widens its leaf name and
// forwards to the wide overload.

#include <map>
#include <stdlib.h>

struct _iobuf;
typedef struct _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *name, const unsigned short *mode);
extern "C" __declspec(dllimport) int __cdecl fprintf(FILE *fp, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *fp);
extern "C" __declspec(dllimport) char *__cdecl fgets(char *buf, int n, FILE *fp);
extern "C" __declspec(dllimport) int __cdecl _wunlink(const unsigned short *path);

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
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
	void translate(const char *text);
	void translate(const AsciiString &text);
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

// BFME 2's user-data path getter (rowed by address at 0x002360FC).
class GlobalData
{
public:
	UnicodeString rva002360FC() const;
};

extern GlobalData *TheGlobalData;

// ?boolAsStr@@YA?AVAsciiString@@_N@Z @0x3B194E
AsciiString boolAsStr(Bool val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

// ?realAsStr@@YA?AVAsciiString@@M@Z @0x3B19AA
AsciiString realAsStr(Real val)
{
	AsciiString ret;
	ret.format("%g", val);
	return ret;
}

// ?intAsStr@@YA?AVAsciiString@@H@Z @0x3B18F4
AsciiString intAsStr(Int val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

// ??0UserPreferences@@QAE@XZ @0x3B1FF1
UserPreferences::UserPreferences( void )
{
}

// ??1UserPreferences@@UAE@XZ @0x3B1F65
UserPreferences::~UserPreferences( void )
{
}

// ?load@UserPreferences@@UAE_NABVAsciiString@@@Z @0x3B1A09
Bool UserPreferences::load(const AsciiString &fname)
{
	UnicodeString wideName;
	wideName.translate(fname.str());
	return load(wideName);
}

#define LINE_LEN 2048

// ?load@UserPreferences@@UAE_NABVUnicodeString@@@Z @0x3B2026
// Zero Hour's load with a wide path: the leaf is appended to the user-data
// directory, and the map is cleared first.
Bool UserPreferences::load(const UnicodeString &fname)
{
	clear();

	m_filename = TheGlobalData->rva002360FC();
	m_filename.concat(fname);

	FILE *fp = _wfopen(m_filename.str(), L"r");
	if (fp)
	{
		char buf[LINE_LEN];
		while( fgets( buf, LINE_LEN, fp ) != NULL )
		{
			AsciiString line = buf;
			line.trim();

			AsciiString key, val;
			line.nextToken(&key, "=");
			val = line.str() + 1;

			key.trim();
			val.trim();

			if (key.isEmpty() || val.isEmpty())
				continue;

			AsciiString &slot = (*this)[key];
			slot = val;
		}  // end while
		fclose(fp);
		return true;
	}
	return false;
}

// ?write@UserPreferences@@UAE_NXZ @0x3B1BF3
Bool UserPreferences::write( void )
{
	if (m_filename.isEmpty())
		return false;

	FILE *fp = _wfopen(m_filename.str(), L"w");
	if (fp)
	{
		PreferenceMap::const_iterator it = begin();
		while (it != end())
		{
			fprintf(fp, "%s = %s\n", it->first.str(), it->second.str());
			++it;
		}
		fclose(fp);
		return true;
	}
	return false;
}

// ?getBool@UserPreferences@@UBE_NABVAsciiString@@_N@Z @0x3B1DBE
Bool UserPreferences::getBool(const AsciiString &key, Bool defaultValue) const
{
	AsciiString val = getAsciiString(key, AsciiString::TheEmptyString);
	if (val.isEmpty())
	{
		return defaultValue;
	}

	val.toLower();
	return (val == "1" || val == "t" || val == "true" || val == "y" || val == "yes" || val == "ok");
}

// ?getReal@UserPreferences@@UBEMABVAsciiString@@M@Z @0x3B1A67
Real UserPreferences::getReal(const AsciiString &key, Real defaultValue) const
{
	AsciiString val = getAsciiString(key, AsciiString::TheEmptyString);
	if (val.isEmpty())
	{
		return defaultValue;
	}

	return (Real)atof(val.str());
}

// ?getInt@UserPreferences@@UBEHABVAsciiString@@H@Z @0x3B1AC7
Int UserPreferences::getInt(const AsciiString &key, Int defaultValue) const
{
	AsciiString val = getAsciiString(key, AsciiString::TheEmptyString);
	if (val.isEmpty())
	{
		return defaultValue;
	}

	return atoi(val.str());
}

// ?getEnumIndex@UserPreferences@@UBEHPBDPAPBDHH@Z @0x3B1CEE
// Index of the stored value in a table of names (case-insensitive), or the
// default when the key is missing or the value names nothing.
Int UserPreferences::getEnumIndex(const char *key, const char **names, Int count, Int defaultValue) const
{
	AsciiString val = getAsciiString(key, AsciiString::TheEmptyString);
	if (!val.isEmpty())
	{
		for (Int i = 0; i < count; ++i)
		{
			if (val.compareNoCase(names[i]) == 0)
				return i;
		}
	}
	return defaultValue;
}

// ?getAsciiString@UserPreferences@@UBE?AVAsciiString@@ABV2@0@Z @0x3B1FA1
AsciiString UserPreferences::getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const
{
	UserPreferences::const_iterator it = find(key);
	if (it == end())
	{
		return defaultValue;
	}

	return it->second;
}

// ?setBool@UserPreferences@@UAEXABVAsciiString@@_N@Z @0x3B1B20
void UserPreferences::setBool(const AsciiString &key, Bool val)
{
	setAsciiString(key, boolAsStr(val));
}

// ?setReal@UserPreferences@@UAEXABVAsciiString@@M@Z @0x3B1B65
void UserPreferences::setReal(const AsciiString &key, Real val)
{
	setAsciiString(key, realAsStr(val));
}

// ?setInt@UserPreferences@@UAEXABVAsciiString@@H@Z @0x3B1BAE
void UserPreferences::setInt(const AsciiString &key, Int val)
{
	setAsciiString(key, intAsStr(val));
}

// ?setAsciiString@UserPreferences@@UAEXABVAsciiString@@0@Z @0x3B21A6
void UserPreferences::setAsciiString(const AsciiString &key, const AsciiString &val)
{
	AsciiString &slot = (*this)[key];
	slot = val;
}

// The GameSpy session info singleton (0x00E02320), as far as the ignore
// list reaches it: getLocalProfileID sits in vtable slot 0x7C.
class GameSpyInfoInterface
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual Int getLocalProfileID();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class IgnorePreferences : public UserPreferences
{
public:
	IgnorePreferences();
	virtual ~IgnorePreferences();
};

// ??0IgnorePreferences@@QAE@XZ @0x3B21C0
// Zero Hour's constructor with BFME 2's per-profile path under
// "Online Files".
IgnorePreferences::IgnorePreferences()
{
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\IgnorePref%d.ini", "Online Files", TheGameSpyInfo->getLocalProfileID());
	load(userPrefFilename);
}

// ?deleteFileInGlobalDataDir@@YA_NABVUnicodeString@@@Z @0x3B1C89
// Removes a file from the user-data directory: the leaf is appended to
// the GlobalData directory and unlinked. True when _wunlink succeeds.
// The profile stat loaders (0x53789A/0x537A78) call this to clear stale
// stats files.
Bool deleteFileInGlobalDataDir(const UnicodeString &name)
{
	UnicodeString path = TheGlobalData->rva002360FC();
	path.concat(name);
	Bool success = false;
	switch (_wunlink(path.str())) {
	case 0:
		success = true;
		break;
	}
	return success;
}

// ?deleteFileInGlobalDataDir@@YA_NABVAsciiString@@@Z @0x3B1D78
// Narrow spelling: widens through translate, then forwards to the wide
// worker above.
Bool deleteFileInGlobalDataDir(const AsciiString &name)
{
	UnicodeString wideName;
	wideName.translate(name);
	return deleteFileInGlobalDataDir(wideName);
}
