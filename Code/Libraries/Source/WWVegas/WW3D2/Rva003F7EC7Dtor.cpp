// cl: /EHsc /MD
//
// ??1Rva003F7EC7@@UAE@XZ retail 0x003F7EC7 105 bytes. Virtual dtor with EH
// storing derived then base vtables destroying pointer at +0x14 via slot0
// virtual plus operator delete AsciiString at +0x10 via releaseBuffer and
// ref at +0x08 via Release_Ref. Evidence is caller 0x003F845C deleting dtor
// plus rowed callees plus neighbour dtor flags.

void __cdecl operator delete(void *block);

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

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


class DeleteInner
{
public:
	virtual void *Delete(int flags) = 0;
};

class Holder08
{
public:
	~Holder08() { if (m_ptr != 0) m_ptr->Release_Ref(); }
	OpaqueRefCounted *m_ptr;
};

class Holder14
{
public:
	~Holder14()
	{
		void *toDelete = m_ptr != 0 ? m_ptr->Delete(0) : 0;
		::operator delete(toDelete);
		m_ptr = 0;
	}
	DeleteInner *m_ptr;
};

class RvaBase
{
public:
	virtual ~RvaBase() {}
protected:
	int m_04;
};

class Rva003F7EC7 : public RvaBase
{
public:
	virtual ~Rva003F7EC7();
protected:
	Holder08 m_08;
	int m_0C;
	StringBase<char> m_10;
	DeleteInner *m_14;
};

Rva003F7EC7::~Rva003F7EC7()
{
	void *toDelete = m_14 != 0 ? m_14->Delete(0) : 0;
	::operator delete(toDelete);
	m_14 = 0;
}
