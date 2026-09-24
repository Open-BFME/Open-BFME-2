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
// Narrow-pair to wide-string helpers for the WinMain title builders,
// retail 0x0023428D (26 bytes), 0x0023436C (60 bytes) and 0x00234788
// (99 bytes). The (pointer, length) pair is the same TU-scoped shape
// WinMain.cpp snapshots through copyStringRef: its length sits at +4,
// which the converter below reads for the scratch allocation. The wide
// temporaries stay at the StringBase level the retail calls use, so the
// buffer, copy and release steps resolve to the pinned StringBase bodies
// with no extra pins beyond the two harvested below.

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;
	StringBase(const T *text);

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &src);
	~StringBase() { releaseBuffer(); }

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	void releaseBuffer();
	T *getBufferForRead(int len);
	void set(const StringBase &src);

protected:
	Header *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString &operator=(const UnicodeString &src) { set(src); return *this; }
	const unsigned short *str() const { return m_data ? m_data->data : L""; }
};

// A (pointer, length) string reference. The same shape holds narrow text
// (init) and wide text (initWide); the empty constructor keeps it non-POD,
// so by-value returns go through a hidden slot as retail shows.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);
	Rva000B3F84Pair *initWide(const unsigned short *src);
	void copyBytes(void *dst, int off, int len);
	void convertToWide(unsigned short *dst, int off, int len);
	int convertToWideBuffer(unsigned short *dst);
	int copyWchars(unsigned short *dst);
	operator UnicodeString();
	int length() const { return m_len; }

	const char *m_ptr;
	int m_len;
};

// Title segment behind 0x234803: a pair plus a trailing extra wchar at +8.
// convertToWideBufferWithExtra converts the pair, appends the extra wchar,
// and returns the total count; 0x234803 then appends the +0xC pair after it.
// A string reference followed by one wchar: the left half of
// "reference + L'\\' + text" built by the operator+ at 0x2342F7.
struct PairWithChar : Rva000B3F84Pair
{
	unsigned short m_extraChar;
};

struct Rva002343C3TitleSegment : PairWithChar
{
	int convertToWideBufferWithExtra(unsigned short *dst);
	int convertTitleSegments(unsigned short *dst);
	operator UnicodeString();
	int length() const { return extendedLength() + m_secondPair.length(); }
	int extendedLength() const { return Rva000B3F84Pair::length() + 1; }
	Rva000B3F84Pair m_secondPair;
};

// Double-pair title segment behind 0x234828: two back-to-back pairs at +0
// and +8 with no extra wchar. 0x234828 converts the first pair, appends the
// second pair after it, and returns the total count. Adjacent after the
// extra-char twin 0x234803, same shape with convertToWideBuffer first call
// and +8 second-pair offset; sole caller 0x2349A5 mirrors the 0x234803
// caller 0x234940 without the plus-one length.
struct WinMainTitlePair : Rva000B3F84Pair
{
	int convertTitlePair(unsigned short *dst);
	operator UnicodeString();
	int length() const { return firstLength() + m_secondPair.length(); }
	int firstLength() const { return Rva000B3F84Pair::length(); }
	Rva000B3F84Pair m_secondPair;
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short *s);
extern "C" unsigned int strlen(const char *s);
void *operator new[](unsigned int n);
void operator delete[](void *p);
int multiByteToWideChar(const char *src, int srcLen, unsigned short *dst, int dstLen);

// ?init@Rva000B3F84Pair@@QAEPAV1@PBD@Z @0xB3F84
Rva000B3F84Pair *Rva000B3F84Pair::init(const char *src)
{
	m_ptr = src;
	m_len = src != 0 ? strlen(src) : 0;
	return this;
}

// ?copyBytes@Rva000B3F84Pair@@QAEXPAXHH@Z @0x23428D
void Rva000B3F84Pair::copyBytes(void *dst, int off, int len)
{
	memcpy(dst, m_ptr + off, len);
}

// ?convertToWide@Rva000B3F84Pair@@QAEXPA_GHH@Z @0x23436C
void Rva000B3F84Pair::convertToWide(unsigned short *dst, int off, int len)
{
	int n = m_len;
	char *scratch = static_cast<char *>(operator new[](n + 1));
	copyBytes(scratch, off, n);
	multiByteToWideChar(scratch, n, dst, len);
	operator delete[](scratch);
}

// ??BRva000B3F84Pair@@QAE?AVUnicodeString@@XZ @0x234788
Rva000B3F84Pair::operator UnicodeString()
{
	UnicodeString tmp;
	convertToWide(tmp.getBufferForRead(m_len), 0, m_len);
	return tmp;
}

// ?convertToWideBuffer@Rva000B3F84Pair@@QAEHPA_G@Z @0x2343AB
int Rva000B3F84Pair::convertToWideBuffer(unsigned short *dst)
{
	convertToWide(dst, 0, m_len);
	return m_len;
}

// ?convertToWideBufferWithExtra@Rva002343C3TitleSegment@@QAEHPAG@Z @0x2343C3
int Rva002343C3TitleSegment::convertToWideBufferWithExtra(unsigned short *dst)
{
	int n = convertToWideBuffer(dst);
	dst[n] = m_extraChar;
	return n + 1;
}

// ?convertTitleSegments@Rva002343C3TitleSegment@@QAEHPAG@Z @0x234803
int Rva002343C3TitleSegment::convertTitleSegments(unsigned short *dst)
{
	int first = convertToWideBufferWithExtra(dst);
	int second = m_secondPair.copyWchars(dst + first);
	return first + second;
}

// ?convertTitlePair@WinMainTitlePair@@QAEHPAG@Z @0x234828
int WinMainTitlePair::convertTitlePair(unsigned short *dst)
{
	int first = convertToWideBuffer(dst);
	int second = m_secondPair.copyWchars(dst + first);
	return first + second;
}

// ??BRva002343C3TitleSegment@@QAE?AVUnicodeString@@XZ @0x23490C
// Sizes the wide buffer for both pairs plus the extra wchar, then fills it.
Rva002343C3TitleSegment::operator UnicodeString()
{
	UnicodeString tmp;
	convertTitleSegments(tmp.getBufferForRead(length()));
	return tmp;
}

// ??BWinMainTitlePair@@QAE?AVUnicodeString@@XZ @0x234973
// The double-pair twin: both pair lengths, no extra wchar.
WinMainTitlePair::operator UnicodeString()
{
	UnicodeString tmp;
	convertTitlePair(tmp.getBufferForRead(length()));
	return tmp;
}

// ?makeStringRef@@YA?AVRva000B3F84Pair@@PBD@Z @0x2343F7
// Snapshots a C string as a (pointer, length) pair returned by value.
Rva000B3F84Pair makeStringRef(const char *src)
{
	Rva000B3F84Pair ref;
	ref.init(src);
	return ref;
}

// ?initWide@Rva000B3F84Pair@@QAEPAV1@PBG@Z @0x2342D5
Rva000B3F84Pair *Rva000B3F84Pair::initWide(const unsigned short *src)
{
	m_ptr = (const char *)src;
	m_len = src != 0 ? wcslen(src) : 0;
	return this;
}

// ??H@YA?AUPairWithChar@@ABVRva000B3F84Pair@@G@Z @0x2342F7
PairWithChar operator+(const Rva000B3F84Pair &left, unsigned short separator)
{
	PairWithChar result;
	static_cast<Rva000B3F84Pair &>(result) = left;
	result.m_extraChar = separator;
	return result;
}

// ??H@YA?AUWinMainTitlePair@@ABVRva000B3F84Pair@@PBG@Z @0x234324
WinMainTitlePair operator+(const Rva000B3F84Pair &left, const unsigned short *right)
{
	Rva000B3F84Pair wide;
	wide.initWide(right);
	WinMainTitlePair result;
	static_cast<Rva000B3F84Pair &>(result) = left;
	result.m_secondPair = wide;
	return result;
}

// ??H@YA?AURva002343C3TitleSegment@@ABUPairWithChar@@PBG@Z @0x513B5B
Rva002343C3TitleSegment operator+(const PairWithChar &left, const unsigned short *right)
{
	Rva000B3F84Pair wide;
	wide.initWide(right);
	Rva002343C3TitleSegment result;
	static_cast<PairWithChar &>(result) = left;
	result.m_secondPair = wide;
	return result;
}

const char *GetRegistryGameRegPath();

// ?buildGameRegistryPath@@YA?AVUnicodeString@@PBG@Z @0x2349FD
// Roots a registry sub-path under the game's GameRegPath value, inserting
// the backslash separator unless the sub-path is empty or already has one.
UnicodeString buildGameRegistryPath(const unsigned short *subPath)
{
	UnicodeString path;
	if (subPath && *subPath && *subPath != L'\\')
		path = makeStringRef(GetRegistryGameRegPath()) + L'\\' + subPath;
	else
		path = makeStringRef(GetRegistryGameRegPath()) + subPath;
	return path;
}

struct HKEY__;
typedef HKEY__ *HKEY;
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)

const char *GetRegistryGameName();
const char *GetRegistryInstallerRegPath();
bool getStringFromRegistry(HKEY root, UnicodeString path, UnicodeString key, UnicodeString &val);

// ?bfmeGetMainWindowTitle@@YA?AVUnicodeString@@XZ @0x23484D
// The main window title: the registry GameName, replaced by the installer
// key's DisplayName under HKEY_LOCAL_MACHINE when that value exists.
UnicodeString bfmeGetMainWindowTitle()
{
	UnicodeString title = makeStringRef(GetRegistryGameName());
	getStringFromRegistry(HKEY_LOCAL_MACHINE, makeStringRef(GetRegistryInstallerRegPath()),
		L"DisplayName", title);
	return title;
}

#define HKEY_CURRENT_USER ((HKEY)0x80000001)

// ?GetStringFromRegistry@@YA_NVUnicodeString@@0AAV1@@Z @0x234ADD
// Reads a wide value from the game's registry tree, machine-wide first and
// per-user second.
bool GetStringFromRegistry(UnicodeString path, UnicodeString key, UnicodeString &val)
{
	UnicodeString fullPath = buildGameRegistryPath(path.str());
	if (getStringFromRegistry(HKEY_LOCAL_MACHINE, fullPath.str(), key.str(), val))
		return true;
	return getStringFromRegistry(HKEY_CURRENT_USER, fullPath.str(), key.str(), val);
}

const char *GetRegistryUserDataLeafName();

// ?getUserDataLeafName@@YA?AVUnicodeString@@XZ @0x234BEC
// The user-data folder leaf: the registry's UserDataLeafName value when it
// is set, otherwise the built-in default from the registry block.
UnicodeString getUserDataLeafName()
{
	UnicodeString leafName;
	if (GetStringFromRegistry(L"", L"UserDataLeafName", leafName))
		return leafName;
	return makeStringRef(GetRegistryUserDataLeafName());
}
