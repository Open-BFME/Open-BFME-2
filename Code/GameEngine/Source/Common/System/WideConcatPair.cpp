// cl: /EHsc /MD
//
// Wide-string concat pair behind retail 0x0021C3F7 (98 bytes) with its
// helpers: length sum at 0x002198C8 (36 bytes), payload copy at 0x0021B8A0
// (37 bytes) and ref payload copy at 0x0021AC32 (56 bytes). Same family as
// Main/WinMainPairUnicode.cpp, but the two halves are nullable wide-string
// references (pointer plus header length) instead of inline (pointer,
// length) snapshots, so the materializer sizes through the header length
// word and copies UTF16 payloads through memcpy. Both materializers return
// a UnicodeString, whose inline copy and destructor resolve to the
// StringBase bodies.

#include <string.h>

#include "../../../../../reference/shims/bfme2_ascii/unicode_string.h"

// A wide-string reference: the length and payload come through the inline
// getLength() and str(), whose null fallback is TheNullChr (retail loads
// 0x007BB5C4).
struct BFME2WideStringRef
{
	const UnicodeString *m_ptr;

	__forceinline int length() const { return m_ptr->getLength(); }

	int copyPayloadTo(unsigned short *dst) const;
};

// @0x0021AC32 (56B): ref payload copy
int BFME2WideStringRef::copyPayloadTo(unsigned short *dst) const
{
	int len = m_ptr->getLength();
	memcpy(dst, m_ptr->str(), len * 2);
	return len;
}

class BFME2WideConcatPair
{
public:
	operator UnicodeString();
	int totalLength() const;
	int copyPayloads(unsigned short *dst) const;

private:
	BFME2WideStringRef m_first;
	BFME2WideStringRef m_second;
};

// @0x002198C8 (36B): pair length sum
int BFME2WideConcatPair::totalLength() const
{
	return m_first.length() + m_second.length();
}

// @0x0021B8A0 (37B): pair payload copy
int BFME2WideConcatPair::copyPayloads(unsigned short *dst) const
{
	int first = m_first.copyPayloadTo(dst);
	int second = m_second.copyPayloadTo(dst + first);
	return first + second;
}


#include "../../../Include/Common/Rva000B3F84Pair.h"

class Rva002DCD9A
{
public:
	int copyToBuffer(unsigned short *dst);
private:
	BFME2WideStringRef m_first;
	Rva000B3F84Pair m_second;
};

// @0x002DCD9A (37B): copies two adjacent wide payloads. The retail call sites
// identify the first as BFME2WideStringRef and the second as Rva000B3F84Pair.
int Rva002DCD9A::copyToBuffer(unsigned short *dst)
{
	int first = m_first.copyPayloadTo(dst);
	int second = m_second.copyWchars(dst + first);
	return first + second;
}

// @0x0021C3F7 (98B): pair materializer
BFME2WideConcatPair::operator UnicodeString()
{
	UnicodeString tmp;
	copyPayloads(tmp.getBufferForRead(totalLength()));
	return tmp;
}

// Triple-wide twin: the pair above plus a third reference at +8. Same
// shape as the WinMainTitlePair/double-pair split: the sum adds the third
// length to the pair sum and the copy appends the third payload after the
// pair copy. Callers live in the 0x0037Dxxx subtitle/text cluster.

// @0x0037BAC2 (27B): triple length sum
// @0x0037BDF0 (37B): triple payload copy
// @0x0037D3C9 (98B): triple materializer
class BFME2WideConcatTriple : public BFME2WideConcatPair
{
public:
	operator UnicodeString();
	int totalLength() const;
	int copyPayloads(unsigned short *dst) const;

private:
	BFME2WideStringRef m_third;
};

int BFME2WideConcatTriple::totalLength() const
{
	int third = m_third.length();
	int pair = BFME2WideConcatPair::totalLength();
	return third + pair;
}

int BFME2WideConcatTriple::copyPayloads(unsigned short *dst) const
{
	int first = BFME2WideConcatPair::copyPayloads(dst);
	int second = m_third.copyPayloadTo(dst + first);
	return first + second;
}

BFME2WideConcatTriple::operator UnicodeString()
{
	UnicodeString tmp;
	copyPayloads(tmp.getBufferForRead(totalLength()));
	return tmp;
}
