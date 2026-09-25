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
// cl: /O1 /EHsc
//
// The narrow half of BFME 2's expression-template string concatenation, and
// the AsciiString registry-path builder built on it. The wide half lives in
// Code/GameEngine/Source/Main/WinMainPairUnicode.cpp; the (pointer, length)
// text reference is the same Rva000B3F84Pair shape.
//
// A concatenation "name + '\\' + text" builds by-value nodes: a reference to
// the AsciiString operand (optionally followed by one char) and a text
// reference. Each node knows its length and writes itself into a buffer;
// operator AsciiString() sizes an AsciiString and fills it. The generic
// nodes are template-shared across the image, so their bodies sit far from
// the registry code that first used them here.

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);

class AsciiString;

template <typename T>
class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase &src);

public:
	StringBase() : m_data(0) {}
	~StringBase();
	T *getBufferForRead(int len);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

protected:
	Header *m_data;
};

class UnicodeString;

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &src) : StringBase<char>(src) {}
	AsciiString &operator=(const AsciiString &src);

	int getLength() const { return m_data ? m_data->length : 0; }
	const char *str() const { return m_data ? m_data->data : ""; }
	void translate(const UnicodeString &src);
};

// The wide string, as far as the registry readers reach it: its storage
// releases inline, and it converts from an AsciiString out of line.
template <>
class StringBase<unsigned short>
{
	friend class UnicodeString;
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }

private:
	void *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const AsciiString &src);
};

// The (pointer, length) text reference shared with the wide builders.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);
	int write(char *dst);

	const char *m_ptr;
	int m_len;
};

// A reference to an AsciiString operand.
struct AsciiStringRef
{
	int write(char *dst);

	const AsciiString *m_string;
};

// An AsciiString operand followed by one char.
struct AsciiStringRefWithChar : AsciiStringRef
{
	int write(char *dst);

	char m_char;
};

// "string + text"
struct AsciiStringPlusText : AsciiStringRef
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_right;
};

// "string + char + text"
struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_right;
};

// "string + string": two AsciiString operands. The length sums through the
// shared header-length fold pinned at 0x002198C8 (layout-compatible with
// the wide pair summer).
struct AsciiStringPlusString : AsciiStringRef
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	AsciiStringRef m_second;
};

// "string + string + char"
struct AsciiStringPlusStringChar : AsciiStringPlusString
{
	int write(char *dst);

	char m_char;
};

// "string + string + text"
struct AsciiStringPlusStringText : AsciiStringPlusString
{
	int write(char *dst);

	Rva000B3F84Pair m_text;
};

// ?write@Rva000B3F84Pair@@QAEHPAD@Z @0xB44F0
int Rva000B3F84Pair::write(char *dst)
{
	memcpy(dst, m_ptr, m_len);
	return m_len;
}

// ?write@AsciiStringRef@@QAEHPAD@Z @0x2C5B1
int AsciiStringRef::write(char *dst)
{
	int len = m_string->getLength();
	memcpy(dst, m_string->str(), len);
	return len;
}

// ?write@AsciiStringRefWithChar@@QAEHPAD@Z @0x2C7A7
int AsciiStringRefWithChar::write(char *dst)
{
	int n = AsciiStringRef::write(dst);
	dst[n] = m_char;
	return n + 1;
}

// ?length@AsciiStringPlusText@@QBEHXZ @0x2DBF50
int AsciiStringPlusText::length() const
{
	return m_string->getLength() + m_right.m_len;
}

// ?write@AsciiStringPlusText@@QAEHPAD@Z @0xBBD41
int AsciiStringPlusText::write(char *dst)
{
	int n = AsciiStringRef::write(dst);
	return n + m_right.write(dst + n);
}

// ??BAsciiStringPlusText@@QAE?AVAsciiString@@XZ @0xBC4F7
AsciiStringPlusText::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ?length@AsciiStringCharPlusText@@QBEHXZ @0x2347EB
int AsciiStringCharPlusText::length() const
{
	return m_string->getLength() + 1 + m_right.m_len;
}

// ?write@AsciiStringCharPlusText@@QAEHPAD@Z @0x2349D8
int AsciiStringCharPlusText::write(char *dst)
{
	int n = AsciiStringRefWithChar::write(dst);
	return n + m_right.write(dst + n);
}

// ??BAsciiStringCharPlusText@@QAE?AVAsciiString@@XZ @0x234CA6
AsciiStringCharPlusText::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ?write@AsciiStringPlusString@@QAEHPAD@Z @0xBBD1C
int AsciiStringPlusString::write(char *dst)
{
	int n = AsciiStringRef::write(dst);
	return n + m_second.write(dst + n);
}

// ??BAsciiStringPlusString@@QAE?AVAsciiString@@XZ @0xBC495
AsciiStringPlusString::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ?write@AsciiStringPlusStringChar@@QAEHPAD@Z @0x50EE58
int AsciiStringPlusStringChar::write(char *dst)
{
	int n = AsciiStringPlusString::write(dst);
	dst[n] = m_char;
	return n + 1;
}

// ?write@AsciiStringPlusStringText@@QAEHPAD@Z @0x50F219
int AsciiStringPlusStringText::write(char *dst)
{
	int n = AsciiStringPlusString::write(dst);
	return n + m_text.write(dst + n);
}

// ??H@YA?AUAsciiStringPlusText@@ABVAsciiString@@PBD@Z @0xB49C5
AsciiStringPlusText operator+(const AsciiString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusText result;
	result.m_string = &left;
	result.m_right = text;
	return result;
}

// ??H@YA?AUAsciiStringCharPlusText@@ABUAsciiStringRefWithChar@@PBD@Z @0x109CFD
AsciiStringCharPlusText operator+(const AsciiStringRefWithChar &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringCharPlusText result;
	static_cast<AsciiStringRefWithChar &>(result) = left;
	result.m_right = text;
	return result;
}

inline AsciiStringRefWithChar operator+(const AsciiString &left, char c)
{
	AsciiStringRefWithChar result;
	result.m_string = &left;
	result.m_char = c;
	return result;
}

// ?makeAsciiString@@YA?AVAsciiString@@PBD@Z @0x2343DF
AsciiString makeAsciiString(const char *text)
{
	return AsciiString(text);
}

const char *GetRegistryGameRegPath();

// ?buildGameRegistryPath@@YA?AVAsciiString@@PBD@Z @0x234D08
// The narrow twin of the wide builder: roots a registry sub-path under the
// game's GameRegPath value, inserting the backslash separator unless the
// sub-path is empty or already has one.
AsciiString buildGameRegistryPath(const char *subPath)
{
	AsciiString path;
	if (subPath && *subPath && *subPath != '\\')
		path = makeAsciiString(GetRegistryGameRegPath()) + '\\' + subPath;
	else
		path = makeAsciiString(GetRegistryGameRegPath()) + subPath;
	return path;
}

struct HKEY__;
typedef HKEY__ *HKEY;
typedef unsigned long DWORD;
typedef long LONG;
#define ERROR_SUCCESS 0L
#define KEY_READ 0x20019L
#define HKEY_CURRENT_USER ((HKEY)0x80000001)
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)

extern "C" __declspec(dllimport) LONG __stdcall RegOpenKeyExA(
		HKEY hKey, const char *lpSubKey, DWORD ulOptions, DWORD samDesired, HKEY *phkResult);
extern "C" __declspec(dllimport) LONG __stdcall RegQueryValueExA(
		HKEY hKey, const char *lpValueName, DWORD *lpReserved, DWORD *lpType,
		unsigned char *lpData, DWORD *lpcbData);
extern "C" __declspec(dllimport) LONG __stdcall RegCloseKey(HKEY hKey);

bool getStringFromRegistry(HKEY root, UnicodeString path, UnicodeString key, UnicodeString &val);

// ?getStringFromRegistry@@YA_NPAUHKEY__@@VAsciiString@@1AAV2@@Z @0x2344D5
// BFME 2 reads registry strings wide; the narrow reader converts the path
// and key, and translates the value back.
bool getStringFromRegistry(HKEY root, AsciiString path, AsciiString key, AsciiString &val)
{
	UnicodeString wideValue;
	bool result;
	if (getStringFromRegistry(root, path, key, wideValue))
	{
		val.translate(wideValue);
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

// ?getUnsignedIntFromRegistry@@YA_NPAUHKEY__@@VAsciiString@@1AAI@Z @0x234570
bool getUnsignedIntFromRegistry(HKEY root, AsciiString path, AsciiString key, unsigned int &val)
{
	HKEY handle;
	unsigned char buffer[4];
	DWORD size = sizeof(buffer);
	DWORD type;
	LONG returnValue;

	if ((returnValue = RegOpenKeyExA(root, path.str(), 0, KEY_READ, &handle)) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueExA(handle, key.str(), 0, &type, buffer, &size);
		RegCloseKey(handle);
	}

	if (returnValue == ERROR_SUCCESS)
	{
		val = *(unsigned int *)buffer;
		return true;
	}

	return false;
}

// ?GetStringFromRegistry@@YA_NVAsciiString@@0AAV1@@Z @0x234E0B
// Reads a string value from the game's registry tree, machine-wide first and
// per-user second.
bool GetStringFromRegistry(AsciiString path, AsciiString key, AsciiString &val)
{
	AsciiString fullPath = buildGameRegistryPath(path.str());
	if (getStringFromRegistry(HKEY_LOCAL_MACHINE, fullPath.str(), key.str(), val))
		return true;
	return getStringFromRegistry(HKEY_CURRENT_USER, fullPath.str(), key.str(), val);
}

// ?GetUnsignedIntFromRegistry@@YA_NVAsciiString@@0AAI@Z @0x234F1A
bool GetUnsignedIntFromRegistry(AsciiString path, AsciiString key, unsigned int &val)
{
	AsciiString fullPath = buildGameRegistryPath(path.str());
	if (getUnsignedIntFromRegistry(HKEY_LOCAL_MACHINE, fullPath.str(), key.str(), val))
		return true;
	return getUnsignedIntFromRegistry(HKEY_CURRENT_USER, fullPath.str(), key.str(), val);
}

const char *GetRegistryUserDataLeafName();

// ?getUserDataLeafNameAscii@@YA?AVAsciiString@@XZ @0x2350CB
// Narrow twin of the wide getUserDataLeafName: the registry's
// UserDataLeafName value when it is set, otherwise the registry-block default.
AsciiString getUserDataLeafNameAscii()
{
	AsciiString leafName;
	if (GetStringFromRegistry("", "UserDataLeafName", leafName))
		return leafName;
	return GetRegistryUserDataLeafName();
}

// Cached UseLocalUserMaps registry flag (0x00DBA41C); negative until read.
static int s_useLocalUserMaps = -1;

// ?GetRegistryUseLocalUserMaps@@YA_NXZ @0x235159
// Whether user maps live under the local user-data folder. Read once; a
// missing value means yes.
bool GetRegistryUseLocalUserMaps()
{
	if (s_useLocalUserMaps < 0)
	{
		unsigned int value;
		if (GetUnsignedIntFromRegistry("", "UseLocalUserMaps", value))
			s_useLocalUserMaps = value;
		else
			s_useLocalUserMaps = 1;
	}
	return s_useLocalUserMaps != 0;
}

// ?GetRegistryMapPackVersion@@YAIXZ @0x235228
// Zero Hour's map-pack version reader: 1.0 (0x10000) unless the registry
// says otherwise.
unsigned int GetRegistryMapPackVersion()
{
	unsigned int val = 0x10000;
	GetUnsignedIntFromRegistry("", "MapPackVersion", val);
	return val;
}
