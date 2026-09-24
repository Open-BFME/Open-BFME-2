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
	Rva000B3F84Pair *init(const char *src);
	void copyBytes(void *dst, int off, int len);
	void convertToWide(unsigned short *dst, int off, int len);
	int convertToWideBuffer(unsigned short *dst);
	int copyWchars(unsigned short *dst);
	UnicodeString toUnicode();

	const char *m_ptr;
	int m_len;
};

// Title segment behind 0x234803: a pair plus a trailing extra wchar at +8.
// convertToWideBufferWithExtra converts the pair, appends the extra wchar,
// and returns the total count; 0x234803 then appends the +0xC pair after it.
struct Rva002343C3TitleSegment : Rva000B3F84Pair
{
	int convertToWideBufferWithExtra(unsigned short *dst);
	int convertTitleSegments(unsigned short *dst);
	unsigned short m_extraChar;
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
	Rva000B3F84Pair m_secondPair;
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);
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

// ?toUnicode@Rva000B3F84Pair@@QAE?AVUnicodeString@@XZ @0x234788
UnicodeString Rva000B3F84Pair::toUnicode()
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
