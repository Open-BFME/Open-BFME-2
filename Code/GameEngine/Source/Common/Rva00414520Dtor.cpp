// cl: /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1Rva00414520@@UAE@XZ @ 0x00414520 78B
// Evidence: chain via 0x0055A91A Clear; vptr 0x00C3A08C own then 0x00BBB554 base; members +0x08 pool release via rowed 0x00360D26 and +0x18 list<int> via rowed List_base dtor 0x004EC395; callers 0x00414571 deleting dtor 0x00414D94 0x00414E13; layout like BfmeAssignRecord44 in Rva0055A91AClear.cpp.
#include <list>

struct Rva0039BCF8;

class Rva0055A91A
{
public:
	void rva0055A91A();
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};

class Xfer;

#include "Common/Snapshot.h"

class Rva00414520 : public Snapshot
{
public:
	virtual ~Rva00414520();
private:
	int m_04; // +0x04
	Rva00360D26Member m_08; // +0x08
	int m_0C; // +0x0C
	Rva0039BCF8 *m_10; // +0x10
	int m_14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_18; // +0x18
	int m_1C; // +0x1C
};

Rva00414520::~Rva00414520()
{
	((Rva0055A91A *)this)->rva0055A91A();
}
