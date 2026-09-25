// ?totalLength@BFME2WideConcatPair@@QBEHXZ
// partial score=0.97 date=2026-09-25
// cl: /O1 /EHsc /MD
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
// ?copyPayloadTo@BFME2WideStringRef@@ present-unmatched
int BFME2WideStringRef::copyPayloadTo(unsigned short *dst) const
{
	int len = length();
	memcpy(dst, payload(), len * 2);
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
// ?totalLength@BFME2WideConcatPair@@ present-unmatched
int BFME2WideConcatPair::totalLength() const
{
	int first;
	{
		StringBase<unsigned short>::Header *data = m_first.m_ptr->m_data;
		first = data != 0 ? data->length : 0;
	}
	int second;
	{
		StringBase<unsigned short>::Header *data = m_second.m_ptr->m_data;
		second = data != 0 ? data->length : 0;
	}
	return first + second;
}

// @0x0021B8A0 (37B): pair payload copy
int BFME2WideConcatPair::copyPayloads(unsigned short *dst) const
{
	int first = m_first.copyPayloadTo(dst);
	int second = m_second.copyPayloadTo(dst + first);
	return first + second;
}

// ??BBFME2WideConcatPair@@QAE?AV?$StringBase@G@@XZ @0x0021C3F7 (98B)
BFME2WideConcatPair::operator StringBase<unsigned short>()
{
	UnicodeString tmp;
	copyPayloads(tmp.getBufferForRead(totalLength()));
	return tmp;
}
