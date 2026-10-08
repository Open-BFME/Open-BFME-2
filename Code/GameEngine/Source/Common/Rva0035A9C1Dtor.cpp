// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /arch:SSE /Ireference/shims/moduledata
// stlport
// ??1Rva0035A9C1@@UAE@XZ @0x0035A9C1 125B
// Evidence: vtable 0x00C153E0#0 via deleting dtor 0x0035ABA4; Snapshot base vtable 0x00BBB554; forEach 0x00359BE8 with callback 0x1FF3A9 (receiver virtual slot zero); list clear/dtor 0x0023DAA5/0x004EC395 at +0x14; array delete 0x0035A18D at +0x40; free 0x00030830 of +0x04 buffer.
#include <string>

namespace _STL
{
template <class T> class allocator;
template <class T, class Alloc> class _List_base
{
public:
	void clear();
	~_List_base();
};
}

extern "C" void __cdecl free(void *);

class Rva0035A18D
{
public:
	~Rva0035A18D();
private:
	_STL::basic_string<char> m_str;
	int m_x;
};

class Rva00359E04Owner;
class Rva00359E04Listener
{
public:
	virtual void notify00(Rva00359E04Owner *owner);
	virtual void notify04(Rva00359E04Owner *owner);
	virtual void notify08(Rva00359E04Owner *owner);
	virtual void notify0C(Rva00359E04Owner *owner);
};
class Rva00359BE8List
{
public:
	void forEach(void (Rva00359E04Listener::*notify)(Rva00359E04Owner *), Rva00359E04Owner *owner);
	~Rva00359BE8List() { if (m_buf) free(m_buf); }
private:
	void *m_buf;
	char m_pad[0x10 - sizeof(void *)];
};
class Rva00359E04Owner
{
public:
	char m_pad[4];
	Rva00359BE8List m_list;
};

#include "Common/Snapshot.h"

class Rva0035A9C1 : public Snapshot
{
public:
	virtual ~Rva0035A9C1();
private:
	Rva00359BE8List m_list04;
	_STL::_List_base<int, _STL::allocator<int> > m_list14;
	char m_pad18[0x40 - 0x18];
	Rva0035A18D *m_arr40;
};

Rva0035A9C1::~Rva0035A9C1()
{
	m_list04.forEach(&Rva00359E04Listener::notify00, (Rva00359E04Owner *)this);
	(((_STL::_List_base<int, _STL::allocator<int> > *)((char *)this + 0x14)))->clear();
	Rva0035A18D *arr = m_arr40;
	if (arr)
		delete[] arr;
	m_arr40 = 0;
}
