// cl: /DNDEBUG /MD /EHsc
// ??1Rva0021A0C2@@QAE@XZ @0x0021A0C2 (68B):
// Honest-address destructor: three narrow StringBase members at +0/+4/+8,
// each released via rowed StringBase<D>::releaseBuffer at 0x36410.
// Evidence: retail calls releaseBuffer thrice (esi+8 then esi+4 then esi),
// EH prolog with funclet, caller 0x0021AC81 is 28B deleting dtor shape.
// No donor; layout proven by the three immediates.

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

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

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva0021A0C2
{
public:
	~Rva0021A0C2();

private:
	StringBase<char> m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
};

Rva0021A0C2::~Rva0021A0C2()
{
}
