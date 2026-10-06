// ?rva0058113D@Rva0058113D@@QAEPAVLANGameInfo@@I@Z
// partial score=0.97 date=2026-10-06
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0058113D@Rva0058113D@@QAEPAVLANGameInfo@@I@Z @0x0058113D 87B
// Evidence: pin name; callers unclaimed; callees rowed ctor 0x0058062B plus Sort 0x005810B6; container +0 begin +4 end +0x15 sorted flag; virtual +0x1c key.
#include <vector>
class LANGameInfo
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual unsigned int GetKey();
};

class Rva0058062B
{
public:
	Rva0058062B(void *a, unsigned int n);
private:
	void *m_00;
	_STL::vector<unsigned short> m_04;
};

class Rva000795C1Record
{
public:
	unsigned int key;
	void *first;
	void *last;
	void *end;
};

void __cdecl Rva005810B6Sort(void **first, void **last, Rva0058062B rec);

class Rva0058113D
{
public:
	LANGameInfo *rva0058113D(unsigned int index);
private:
	LANGameInfo **m_begin;
	LANGameInfo **m_end;
	LANGameInfo **m_alloc;
	char m_pad[9];
	bool m_sorted;
};

LANGameInfo *Rva0058113D::rva0058113D(unsigned int index)
{
	unsigned int count = (unsigned int)(m_end - m_begin);
	if (index >= count)
		return 0;
	if (!m_sorted)
	{
		unsigned int key = m_begin[index]->GetKey();
		Rva005810B6Sort((void **)m_begin, (void **)m_end, Rva0058062B(this, key));
		m_sorted = true;
	}
	return m_begin[index];
}
