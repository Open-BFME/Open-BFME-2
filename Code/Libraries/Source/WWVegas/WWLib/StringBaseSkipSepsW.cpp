// cl: /DNDEBUG /MD /EHs-c-
//
// File-static wchar skipSeps / skipNonSeps for StringBase<wchar_t>::nextToken.
// Retail calls them with the string in EAX and the separator set in EBX.

#include <string.h>

// Mirror of the StringBase members this body touches, TU-local for the same
// reason string_base_clear.cpp keeps one: the shared string_base.h models the
// class without nextToken, getBufferForRead or releaseBuffer. Access is part
// of the decoration both pins carry -- getBufferForRead public (QAE),
// releaseBuffer private (AAE).
template <typename T>
class StringBase
{
public:
	bool nextToken(StringBase<T> *out, const T *seps);
	T *getBufferForRead(int len);
	void set(const T *str, int len);

private:
	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

static unsigned short *skipSepsW(unsigned short *p, const unsigned short *seps);
static unsigned short *skipNonSepsW(unsigned short *p, const unsigned short *seps);

// Retail 0x00037830 (197 bytes): StringBase<unsigned short>::nextToken,
// destructive tokenize. The out string receives the next token, this string
// keeps the remainder, both are released when no token is found. Mirrors the
// narrow nextToken in StringBaseSkipSeps.cpp: the three validity checks
// joined by || share the far bare-false epilogue (three near je's; separate
// ifs lay the block out locally instead), the callee-saved pushes sink below
// the checks, the separators default to wide space LF CR TAB, the token
// copies through out->getBufferForRead plus the memcpy intrinsic's rep
// movsd/movsb pair with a trailing NUL, and the remainder length reloads
// m_data twice - the sub-then-sar needs the fresh eax load, reusing the
// first one colors it edx instead.
template <>
bool StringBase<unsigned short>::nextToken(StringBase<unsigned short> *out, const unsigned short *seps)
{
	Header *data = m_data;
	if (data == 0 || data->length == 0 || out == this)
		return false;
	if (seps == 0)
		seps = L" \n\r\t";
	unsigned short *start = skipSepsW(data->data, seps);
	unsigned short *end = skipNonSepsW(start, seps);
	if (end > start) {
		int len = (int)(end - start);
		unsigned short *dest = out->getBufferForRead(len);
		memcpy(dest, start, len * 2);
		dest[len] = 0;
		int total = m_data ? m_data->length : 0;
		set(end, total - ((int)((char *)end - (char *)m_data - 8) >> 1));
		return true;
	}
	releaseBuffer();
	out->releaseBuffer();
	return false;
}

static unsigned short *skipSepsW(unsigned short *p, const unsigned short *seps)
{
	unsigned short c = *p;
	if (!c)
		return p;
	while (c)
	{
		unsigned short first = *seps;
		const unsigned short *s = seps;
		if (!first)
			return p;
		unsigned short sc = first;
		do
		{
			if (sc == c)
				goto advance;
			sc = *++s;
		} while (sc);
		return p;
	advance:
		c = *++p;
	}
	return p;
}

static unsigned short *skipNonSepsW(unsigned short *p, const unsigned short *seps)
{
	unsigned short c = *p;
	if (!c)
		return p;
	for (;;)
	{
		unsigned short first = *seps;
		const unsigned short *s = seps;
		if (!first)
			goto advance;
		unsigned short sc = first;
		while (sc != c)
		{
			sc = *++s;
			if (!sc)
				goto advance;
		}
		return p;
	advance:
		c = *++p;
		if (!c)
			return p;
	}
}
