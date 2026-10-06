// cl: /EHsc /MD
//
// ??1Rva000B7539@@QAE@XZ retail 0x000B7539 68 bytes. Non-virtual dtor with
// EH destroying three StringBase char at +0 +4 +8 via rowed releaseBuffer.
// Evidence is triple lea plus EH states plus caller Unwind plus neighbour
// StringRecordCopy flags.

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva000B7539
{
public:
	~Rva000B7539();
private:
	StringBase<char> m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
};

Rva000B7539::~Rva000B7539()
{
}
