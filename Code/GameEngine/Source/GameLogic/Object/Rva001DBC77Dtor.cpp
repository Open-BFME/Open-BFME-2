// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva001DBC77@@QAE@XZ retail 0x001DBC77 73B. Dtor with AsciiString at +0
// via rowed StringBase<char> releaseBuffer, int zero at +0xC, guarded virtual
// slot-0 call on ptr at +0x10 with rowed operator delete, then null. Evidence:
// deleting-dtor caller 0x001DBCC0 plus list-loop caller 0x001DC0EC plus rowed
// callees releaseBuffer 0x00036410 and delete 0x0002FD60. Honest address name.
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


class Rva001DBC77Ptr
{
public:
	virtual void *v0(int x);
};

void __cdecl operator delete(void *p);

class Rva001DBC77
{
public:
	~Rva001DBC77();
private:
	StringBase<char> m_00;
	unsigned char m_pad04[8];
	int m_0C;
	Rva001DBC77Ptr *m_10;
};

Rva001DBC77::~Rva001DBC77()
{
	m_0C = 0;
	if (m_10 != 0) {
		void *p = m_10->v0(0);
		::operator delete(p);
	}
	m_10 = 0;
}
