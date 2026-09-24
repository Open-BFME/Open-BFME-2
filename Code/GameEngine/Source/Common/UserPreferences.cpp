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
	void translate(const char *text);
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
