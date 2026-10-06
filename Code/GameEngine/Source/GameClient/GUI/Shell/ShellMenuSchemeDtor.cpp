// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva002006B0@@QAE@XZ @0x002006B0 196B.
// Two-list cleanup dtor with StringBase release. Evidence: EH prolog scope
// 0x0076C38D; rowed list<int> erase 0x00438539 and list_base dtor 0x004EC395;
// rowed StringBase<D> releaseBuffer 0x00036410 and delete 0x0002FD60;
// offsets +4 +8 payload +0x14; callers 0x0020078E 0x00200818 0x0020091D.
#include <list>

template <typename T>
class StringBase
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


class Payload002006B0 : public StringBase<char>
{
public:
	char m_pad[0x10];
	int m_14;
};

class Rva002006B0 : public StringBase<char>
{
public:
	~Rva002006B0();
private:
	_STL::list<int> m_4;
	_STL::list<int> m_8;
};

Rva002006B0::~Rva002006B0()
{
	for (_STL::list<int>::iterator it = m_4.begin(); it._M_node != m_4.end()._M_node; )
	{
		Payload002006B0 *p = (Payload002006B0 *)(int)*it;
		it = m_4.erase(it);
		if (p != 0)
		{
			p->m_14 = 0;
			delete p;
		}
	}
	for (_STL::list<int>::iterator it = m_8.begin(); it._M_node != m_8.end()._M_node; )
	{
		void *p = (void *)(int)*it;
		it = m_8.erase(it);
		if (p != 0)
			delete p;
	}
}

class Rva002007D5
{
public:
	Rva002007D5();
	~Rva002007D5();
private:
	_STL::list<int> m_0;
	int m_4;
};

Rva002007D5::Rva002007D5()
	: m_0()
	, m_4(0)
{
}

Rva002007D5::~Rva002007D5()
{
	m_4 = 0;
	for (_STL::list<int>::iterator it = m_0.begin(); it._M_node != m_0.end()._M_node; )
	{
		Rva002006B0 *p = (Rva002006B0 *)(int)*it;
		it = m_0.erase(it);
		if (p != 0)
			delete p;
	}
}

// ?forceRva002006B0Delete@@YAXPAVRva002006B0@@@Z absent-from-retail
void forceRva002006B0Delete(Rva002006B0 *p) { delete p; }

// ?forceRva002007D5Delete@@YAXPAVRva002007D5@@@Z absent-from-retail
void forceRva002007D5Delete(Rva002007D5 *p) { delete p; }
