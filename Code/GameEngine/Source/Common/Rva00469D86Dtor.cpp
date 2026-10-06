// cl: /MD /EHsc
// ??1Rva00469D86@@QAE@XZ @ 0x00469D86 72B dtor with OpaqueRef plus two StringBase.
// Evidence: copy-ctor neighbour Rva00469BEA /O1 /MD; callees rowed Release_Ref 0x00050ED3 plus releaseBuffer 0x00036410 twice; EH prolog with scopetable; unblocks 0x0046AA4D 28B plus 0x00475942; no vptr so non-virtual QAE.
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva00469D86Holder0C
{
	OpaqueRefCounted *m_ptr;
	~Rva00469D86Holder0C()
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}
};

class Rva00469D86 : private StringBase<char>
{
public:
	~Rva00469D86();
private:
	StringBase<char> m_04;
	int m_08;
	Rva00469D86Holder0C m_0C;
};

Rva00469D86::~Rva00469D86()
{
}
