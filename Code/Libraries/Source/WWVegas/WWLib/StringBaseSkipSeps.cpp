// cl: /DNDEBUG /MD /EHs-c-
//
// File-static skipSeps / skipNonSeps for StringBase::nextToken.
// Retail calls them with the string in EAX and the separator set in EDI:
// MSVC 7.1's private convention for a static whose every call site it can
// see. The real nextToken below is the second such caller (it used to be a
// shape-only host method); both keep the convention. The StringBase members
// are mirrored below rather than added to string_base.h (getBufferForRead
// rides the 0x00036640 pin; set and releaseBuffer are ledger-matched).

#include <string.h>

// Mirror of the StringBase members this body touches, TU-local for the same
// reason string_base_clear.cpp keeps one: the shared string_base.h models the
// class without nextToken, getBufferForRead or releaseBuffer, and a mirror
// leaves it -- and every other unit that includes it -- untouched. Access
// matters here, not just the signature: getBufferForRead is public (QAE) and
// releaseBuffer private (AAE) in the retail decorations both pins carry.
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

static char *skipSeps(char *p, const char *seps);
static char *skipNonSeps(char *p, const char *seps);

// Retail 0x00036D90 (186 bytes): StringBase<char>::nextToken, destructive
// tokenize. The out string receives the next token, this string keeps the
// remainder, both are released when no token is found. Transferred from the
// BFME1 reconstruction (reference/open-bfme-1/.../string/StringBase.cpp),
// which survives there only as a naked lift; the C++ here is new.
//
// Shape, all retail-measured: the three validity checks joined by || share
// the far bare-false epilogue (three near je's; separate ifs lay the block
// out locally instead), the callee-saved pushes sink below the checks, the
// separators default to "space LF CR TAB", the token copies through
// out->getBufferForRead plus the memcpy intrinsic's rep movsd/movsb pair
// with a trailing NUL, and the remainder length reloads m_data twice - the
// sub-then-lea needs the fresh eax load, reusing the first one colors it
// edx instead.
template <>
bool StringBase<char>::nextToken(StringBase<char> *out, const char *seps)
{
	Header *data = m_data;
	if (data == 0 || data->length == 0 || out == this)
		return false;
	if (seps == 0)
		seps = " \n\r\t";
	char *start = skipSeps(data->data, seps);
	char *end = skipNonSeps(start, seps);
	if (end > start) {
		int len = (int)(end - start);
		char *dest = out->getBufferForRead(len);
		memcpy(dest, start, len);
		dest[len] = 0;
		int total = m_data ? m_data->length : 0;
		set(end, (int)((char *)m_data - end) + total + 8);
		return true;
	}
	releaseBuffer();
	out->releaseBuffer();
	return false;
}

// retail 0x00887720 (54 bytes): same shape as skipNonSeps -- the first
// separator is read into its own local, copied into the walking character,
// and the do/while leaves through a goto on a match so the loop re-enters at
// the compare and the miss exit falls into the return.
static char *skipSeps(char *p, const char *seps)
{
	char c = *p;
	while (c)
	{
		char first = *seps;
		const char *s = seps;
		if (!first)
			return p;
		char sc = first;
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

static char *skipNonSeps(char *p, const char *seps)
{
	char c = *p;
	if (!c)
		return p;
	for (;;)
	{
		char first = *seps;
		const char *s = seps;
		if (!first)
			goto advance;
		char sc = first;
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
