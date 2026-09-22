// ?bfmeGetMainWindowTitle@@YA?AVUnicodeString@@XZ
// partial score=0.93 date=2026-09-22
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

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &src);
	StringBase(const T *text);
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

private:
	Header *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
};

class Rva000B3F84Pair
{
public:
	void init(const char *src);
	void copyBytes(void *dst, int off, int len);
	void convertToWide(unsigned short *dst, int off, int len);
	UnicodeString toUnicode();

	const char *m_ptr;
	int m_len;
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);
void *operator new[](unsigned int n);
void operator delete[](void *p);
int multiByteToWideChar(const char *src, int srcLen, unsigned short *dst, int dstLen);

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

// ?toUnicode@Rva000B3F84Pair@@QAE?AVUnicodeString@@XZ @0x234788
UnicodeString Rva000B3F84Pair::toUnicode()
{
	UnicodeString tmp;
	convertToWide(tmp.getBufferForRead(m_len), 0, m_len);
	return tmp;
}

// ?bfmeGetMainWindowTitle@@YA?AVUnicodeString@@XZ @0x23484D
struct HKEY__ { int unused; };
typedef struct HKEY__ *HKEY;
typedef unsigned short wchar_t;
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)

void copyStringRef(void *dst, const char *src);
const char *GetRegistryGameName();
const char *GetRegistryInstallerRegPath();
bool getStringFromRegistry(HKEY root, UnicodeString path, UnicodeString key, UnicodeString &val);

UnicodeString bfmeGetMainWindowTitle()
{
	Rva000B3F84Pair gamePair;
	copyStringRef(&gamePair, GetRegistryGameName());
	UnicodeString title(gamePair.toUnicode());

	Rva000B3F84Pair pathPair;
	copyStringRef(&pathPair, GetRegistryInstallerRegPath());
	getStringFromRegistry(HKEY_LOCAL_MACHINE, pathPair.toUnicode(),
		(UnicodeString &)StringBase<wchar_t>(L"DisplayName"), title);
	return title;
}
