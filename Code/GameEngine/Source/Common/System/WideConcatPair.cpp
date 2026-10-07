// cl: /EHsc /MD
//
// Wide-string concat pair behind retail 0x0021C3F7 (98 bytes) with its
// helpers: length sum at 0x002198C8 (36 bytes), payload copy at 0x0021B8A0
// (37 bytes) and ref payload copy at 0x0021AC32 (56 bytes). Same family as
// Main/WinMainPairUnicode.cpp, but the two halves are nullable wide-string
// references (pointer plus header length) instead of inline (pointer,
// length) snapshots, so the materializer sizes through the header length
// word and copies UTF16 payloads through memcpy. The temporaries stay at
// the StringBase level so buffer, copy and release resolve to the pinned
// StringBase bodies.

template <typename T>
class StringBase
{
	friend class UnicodeString;
	friend struct BFME2WideStringRef;
	friend class BFME2WideConcatPair;
	StringBase(const T *text);
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &src);
	~StringBase() { releaseBuffer(); }
	int getLength() const { return m_data ? m_data->length : 0; }

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	T *getBufferForRead(int len);
	void set(const StringBase &src);

protected:
	Header *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &src) : StringBase<unsigned short>(src) {}
	const unsigned short *str() const { return m_data != 0 ? m_data->data : L""; }
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

// A nullable wide-string reference: the length and payload both come from
// the header behind m_data, with the empty literal as the null fallback.
struct BFME2WideStringRef
{
	const UnicodeString *m_ptr;

	__forceinline int length() const
	{
		StringBase<unsigned short>::Header *data = m_ptr->m_data;
		return data != 0 ? data->length : 0;
	}

	__forceinline const unsigned short *payload() const
	{
		StringBase<unsigned short>::Header *data = m_ptr->m_data;
		return data != 0 ? data->data : L"";
	}

	int copyPayloadTo(unsigned short *dst) const;
};

// @0x0021AC32 (56B): ref payload copy
int BFME2WideStringRef::copyPayloadTo(unsigned short *dst) const
{
	const UnicodeString *text = m_ptr;
	StringBase<unsigned short>::Header *lengthData = text->m_data;
	int len = lengthData != 0 ? lengthData->length : 0;
	StringBase<unsigned short>::Header *payloadData =
		*const_cast<StringBase<unsigned short>::Header * const volatile *>(&text->m_data);
	memcpy(dst, payloadData != 0 ? payloadData->data : L"", len * 2);
	return len;
}

class BFME2WideConcatPair
{
public:
	operator StringBase<unsigned short>();
	int totalLength() const;
	int copyPayloads(unsigned short *dst) const;

private:
	BFME2WideStringRef m_first;
	BFME2WideStringRef m_second;
};

// @0x002198C8 (36B): pair length sum
int BFME2WideConcatPair::totalLength() const
{
	return m_first.m_ptr->getLength() + m_second.m_ptr->getLength();
}

// @0x0021B8A0 (37B): pair payload copy
int BFME2WideConcatPair::copyPayloads(unsigned short *dst) const
{
	int first = m_first.copyPayloadTo(dst);
	int second = m_second.copyPayloadTo(dst + first);
	return first + second;
}


class Rva000B3F84Pair
{
public:
	int copyWchars(unsigned short *dst);
};

class Rva002DCD9A
{
public:
	int rva002dcd9a(unsigned short *dst);
private:
	BFME2WideStringRef m_first;
	Rva000B3F84Pair m_second;
};

// @0x002DCD9A (37B): copies two adjacent wide payloads. The retail call sites
// identify the first as BFME2WideStringRef and the second as Rva000B3F84Pair.
int Rva002DCD9A::rva002dcd9a(unsigned short *dst)
{
	int first = m_first.copyPayloadTo(dst);
	int second = m_second.copyWchars(dst + first);
	return first + second;
}

// ??BBFME2WideConcatPair@@QAE?AV?$StringBase@G@@XZ @0x0021C3F7 (98B)
BFME2WideConcatPair::operator StringBase<unsigned short>()
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
	operator StringBase<unsigned short>();
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

BFME2WideConcatTriple::operator StringBase<unsigned short>()
{
	UnicodeString tmp;
	copyPayloads(tmp.getBufferForRead(totalLength()));
	return tmp;
}
