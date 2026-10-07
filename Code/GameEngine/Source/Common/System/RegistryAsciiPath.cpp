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
// cl: /EHsc
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
	void set(const StringBase &src);

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
	~AsciiString();
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
	StringBase(const StringBase<unsigned short> &source);
	~StringBase() { releaseBuffer(); }
	unsigned short *getBufferForRead(int length);

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
class Rva002DCD9A
{
public:
	int rva002dcd9a(unsigned short *dst);
};

struct AsciiStringPlusText : AsciiStringRef
{
	int length() const;
	int write(char *dst);
	operator AsciiString();
	operator StringBase<unsigned short>();

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
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

// ?rva005EF5CA@Rva005EF5CA@@QAEHPAD@Z @0x005EF5CA 37B.
// Two part write via rowed registry path writer and AsciiStringRef writer;
// caller 0x005EF607 uses this output in the next path operation.
struct Rva005EF5CA : AsciiStringPlusStringText
{
	int write(char *dst);
	int length() const;
	operator AsciiString();
	AsciiStringRef m_fourth;
};

int Rva005EF5CA::write(char *dst)
{
	int n = AsciiStringPlusStringText::write(dst);
	return n + ((AsciiStringRef *)((char *)this + 0x10))->write(dst + n);
}

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

// ??BAsciiStringPlusText@@QAE?AV?$StringBase@G@@XZ @0x002DD111
AsciiStringPlusText::operator StringBase<unsigned short>()
{
	StringBase<unsigned short> tmp;
	Rva002DCD9A *pair = (Rva002DCD9A *)this;
	pair->rva002dcd9a(tmp.getBufferForRead(length()));
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

// ?length@AsciiStringPlusString@@QBEHXZ @0x2198C8 36B: both header lengths summed.
int AsciiStringPlusString::length() const
{
	return m_string->getLength() + m_second.m_string->getLength();
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

// ?write@Rva0050F23E@@QAEHPAD@Z @0x0050F23E 37B narrow concat node two-ref plus char plus trailing text: base PlusStringChar write 0x0050EE58 then Rva pair write 0x000B44F0; caller is materializer 0x0050F7B4.
struct Rva0050F23E : AsciiStringPlusStringChar
{
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

int Rva0050F23E::write(char *dst)
{
	int n = AsciiStringPlusStringChar::write(dst);
	return n + m_text.write(dst + n);
}

// ?write@Rva005D32EC@@QAEHPAD@Z @0x005D32EC 37B narrow concat node two-ref plus trailing text: base PlusStringText write 0x0050F219 then Rva pair write 0x000B44F0; caller materializer 0x005D3311.
struct Rva005D32EC : AsciiStringPlusStringText
{
	int write(char *dst);

	Rva000B3F84Pair m_text2;
};

int Rva005D32EC::write(char *dst)
{
	int n = AsciiStringPlusStringText::write(dst);
	return n + m_text2.write(dst + n);
}

// ?write@Rva005D3311@@QAEHPAD@Z @0x005D3311 37B narrow concat node: base Rva005D32EC write 0x005D32EC then Rva pair write 0x000B44F0 at +0x18; callers 0x005D3365 0x005F985C.
struct Rva005D3311 : Rva005D32EC
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_text3;
};

// 0x005D32D9..0x005D32EC: length counterpart to the verified writer below.
// The call is the existing two-string length at 0x002198C8; native additions
// read the three text-span lengths at +0x1C, +0x14, and +0x0C in that order.
int Rva005D3311::length() const
{
	return AsciiStringPlusString::length() + m_text3.m_len + m_text2.m_len + m_text.m_len;
}

int Rva005D3311::write(char *dst)
{
	int n = Rva005D32EC::write(dst);
	return n + m_text3.write(dst + n);
}

// ??BRva005D3311@@QAE?AVAsciiString@@XZ 0x005D3336 98B narrow concat materializer: sized getBufferForRead then Rva005D3311 write; same shape as Rva005F9852 0x005F9D69.
Rva005D3311::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ?write@Rva005F9852@@QAEHPAD@Z @0x005F9852 37B narrow concat node: base Rva005D3311 write 0x005D3311 then AsciiStringRef write 0x0002C5B1 at +0x20; caller 0x005F9D98.
struct Rva005F9852 : Rva005D3311
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	AsciiStringRef m_ref;
};

// 0x005F9791..0x005F97AC: the materializer at 0x005F9D69 calls this
// before the verified writer. It reads the trailing string at +0x20 and
// adds the three-span base length; no original template name is inferred.
int Rva005F9852::length() const
{
	int n = m_ref.m_string->getLength();
	return Rva005D3311::length() + n;
}

int Rva005F9852::write(char *dst)
{
	int n = Rva005D3311::write(dst);
	return n + m_ref.write(dst + n);
}

// 0x005F9D69..0x005F9DCB: same owning-string materialization as the
// other verified concat nodes, with this node's own length/write callees.
// RET4 consumes only the hidden result pointer; the drift queue's proposed
// GameState path getter would need an additional filename argument.
Rva005F9852::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ??BRva0050F23E@@QAE?AVAsciiString@@XZ @0x0050F7B4 107B narrow concat to AsciiString: sized getBufferForRead then Rva0050F23E write; length is base PlusString fold plus text len plus 1 for char.
Rva0050F23E::operator AsciiString()
{
	AsciiString tmp;
	int extra = m_text.m_len;
	write(tmp.getBufferForRead(extra + AsciiStringPlusString::length() + 1));
	return tmp;
}

// ??BAsciiStringPlusStringText@@QAE?AVAsciiString@@XZ @0x0050F74B 105B narrow concat node to AsciiString: sized getBufferForRead then write; length is base PlusString fold 0x002198C8 plus trailing text len; callers include 0x00510443.
AsciiStringPlusStringText::operator AsciiString()
{
	AsciiString tmp;
	int extra = m_text.m_len;
	write(tmp.getBufferForRead(extra + AsciiStringPlusString::length()));
	return tmp;
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

// ??H@YA?AURva002226E5TextPlusString@@PBDABVAsciiString@@@Z, retail 0x002226E5, 52 bytes.
// Char-text plus string node mirroring string-plus-text at 0xB49C5: pair from the left literal plus the right string ref. Builds "_nrm" plus extension in makeNrmTextureName 0x317D89 plus 24 other callers. No donor; honest address struct; shape mirrors the rowed sibling with swapped operands.
struct Rva002226E5TextPlusString
{
	int length() const;
	int write(char *dst);
	operator AsciiString();
	Rva000B3F84Pair m_left;
	AsciiStringRef m_right;
};

Rva002226E5TextPlusString operator+(const char *left, const AsciiString &right)
{
	Rva000B3F84Pair text;
	text.init(left);
	Rva002226E5TextPlusString result;
	result.m_left = text;
	result.m_right.m_string = &right;
	return result;
}

// ?length@Rva002226E5TextPlusString@@QBEHXZ @0x00513B94 23B: text-plus-string length (left len + right getLength); mirrors rowed string-plus-text length at 0x002DBF50 with swapped operands; callers 0x00513E03 0x005E366A 0x005F1B75 0x0022309D 0x0059B49E.
int Rva002226E5TextPlusString::length() const
{
	int left = m_left.m_len;
	return left + m_right.m_string->getLength();
}

int Rva002226E5TextPlusString::write(char *dst)
{
	int n = m_left.write(dst);
	return n + m_right.write(dst + n);
}

// ??BRva002226E5TextPlusString@@QAE?AVAsciiString@@XZ @0x0022309D 98B
// Narrow materializer for text-plus-string: sizes via length then fills
// through write; callers at 0x00223933 0x002AD3F1 0x0051FAAB.
Rva002226E5TextPlusString::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
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

// ??H@YA?AUAsciiStringPlusStringChar@@ABUAsciiStringPlusString@@D@Z @0x50EDD5
// "string + string + char"; the StatusPage constructor 0x005103A3 builds
// its "<level><name>_<query>" names with it.
AsciiStringPlusStringChar operator+(const AsciiStringPlusString &left, char c)
{
	AsciiStringPlusStringChar result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_char = c;
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
		((StringBase<char> *)&path)->set((const StringBase<char> &)(const AsciiString &)
			(makeAsciiString(GetRegistryGameRegPath()) + '\\' + subPath));
	else
		((StringBase<char> *)&path)->set((const StringBase<char> &)(const AsciiString &)
			(makeAsciiString(GetRegistryGameRegPath()) + subPath));
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

// ?write@Rva0002C9C2@@QAEHPAD@Z @0x0002C9C2 37B
// Narrow concat node "string + char + string": an AsciiString operand
// followed by one char, then a second AsciiString operand. Retail writes
// the first part through AsciiStringRefWithChar 0x0002C7A7 then the second
// through AsciiStringRef 0x0002C5B1, summing the lengths. Called from the
// unclaimed operator at 0x0002CB02. Honest address name; true type unknown.
struct Rva0002C9C2
{
	AsciiStringRefWithChar m_first;
	AsciiStringRef m_second;
	int write(char *dst);
};

int Rva0002C9C2::write(char *dst)
{
	int n = m_first.write(dst);
	return n + m_second.write(dst + n);
}

// ?write@Rva0020F58E@@QAEHPAD@Z @0x0020F58E 37B narrow concat node PlusText plus Ref via rowed writes 0xBBD41 plus 0x2C5B1.
// Evidence: unlock lane every callee rowed; callers 0x0020F741 0x00238C3E; same 37B shape as Rva0002C9C2.
struct Rva0020F58E
{
	AsciiStringPlusText m_first;
	AsciiStringRef m_second;
	int length() const;
	int write(char *dst);
	operator AsciiString();
};

// ??BRva0020F58E@@QAE?AVAsciiString@@XZ @0x0020F712 98B narrow materializer via length plus write plus getBufferForRead.
// Evidence: chain lane calls just-landed length 0x0020F0D3 plus write 0x0020F58E; same 98B shape as Rva002226E5TextPlusString materializer.
int Rva0020F58E::length() const
{
	return m_first.length() + m_second.m_string->getLength();
}

int Rva0020F58E::write(char *dst)
{
	int n = m_first.write(dst);
	return n + m_second.write(dst + n);
}

Rva0020F58E::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ??BWinMainTitlePair@@QAE?AVAsciiString@@XZ @0x0010BA9F 101B
// Narrow materializer for the double-pair title segment rowed at 0x00109D3A:
// sizes via both pair lengths then fills through that write; callers at
// 0x0010BCC8 0x0057A11F 0x0057A190; chain from 0x00109D3A.
struct WinMainTitlePair : Rva000B3F84Pair
{
	int write(char *dst);
	int firstLength() const { return m_len; }
	int length() const { return firstLength() + m_secondPair.m_len; }
	operator AsciiString();
	Rva000B3F84Pair m_secondPair;
};

WinMainTitlePair::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ?write@Rva00238C34@@QAEHPAD@Z @0x00238C34 37B narrow concat node: base Rva0020F58E write 0x0020F58E then Rva pair write 0x000B44F0 at +0x10; caller materializer 0x00238C59.
struct Rva00238C34 : Rva0020F58E
{
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_text2;
};

int Rva00238C34::write(char *dst)
{
	int n = Rva0020F58E::write(dst);
	return n + m_text2.write(dst + n);
}

// ??BRva00238C34@@QAE?AVAsciiString@@XZ @0x00238C59 105B narrow materializer: sized getBufferForRead via base length 0x0020F0D3 plus trailing text len then write 0x00238C34; caller 0x00238CC2.
Rva00238C34::operator AsciiString()
{
	AsciiString tmp;
	int extra = m_text2.m_len;
	write(tmp.getBufferForRead(extra + Rva0020F58E::length()));
	return tmp;
}

// Complete native 0x5EF449..0x5EF46B and 0x5EF607..0x5EF669 bodies.
// The existing writer proves two string refs, a text span, then the string
// ref at +0x10; the length body reads span length +0x0C and string +0x10,
// calls the matched two-string length at 0x2198C8, and adds both lengths.
// Materialization calls that length and the existing writer 0x5EF5CA,
// then returns an owning AsciiString through the established copy/release ABI.
// Source guide: the other verified concatenation nodes in this unit.
// The original expression-template name remains unknown.
int Rva005EF5CA::length() const
{
 int text = m_text.m_len;
 int fourth = m_fourth.m_string->getLength();
 int base = AsciiStringPlusString::length();
 return base + fourth + text;
}
Rva005EF5CA::operator AsciiString()
{
 AsciiString tmp;
 write(tmp.getBufferForRead(length()));
 return tmp;
}
