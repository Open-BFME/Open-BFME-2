// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva004FA2E2@@QAE@XZ, retail 0x004FA2E2..0x004FA3C9 (231 bytes, EH): the
// pointee destructor the owning-pointer resets 0x002B430C/0x002B4326 call
// (pinned name). It ::deletes every object of its +0x48 list and empties it
// (rowed range erase 0x0031BD55); then its parts die in retail's unwind-map
// order: the +0x6C record vector (rowed 0x004F8832), the +0x60/+0x54/+0x48
// buffers (GameFree; unwind copies 0x0007FAB3), the +0x3C member (rowed
// 0x004F87F3), the two +0x24 and two +0xC 12-byte records (eh vector
// iterator; element destructors 0x004F9630 and 0x004F7D7F) and the +0
// element vector (rowed 0x002BBB18; its wrapper's unwind copy is the 5-byte
// thunk 0x002BBD4D). Identity not established.
#include "../../Include/Common/Rva004F69C3.h"

#include <vector>

void __cdecl Rva00030830GameFree(void *);

struct Rva002BBB96Element { int m_data[4]; };
namespace _STL {
template<> vector<Rva002BBB96Element, allocator<Rva002BBB96Element> >::~vector();
template<> vector<Rva004F69C3, allocator<Rva004F69C3> >::~vector();
}

struct Rva002BBD4D
{
	~Rva002BBD4D() {}
	_STL::vector<Rva002BBB96Element> m_elements;
};

// The +0xC pair is two vectors whose destructor is the rowed
// vector<Rva004F7D7FRecord> 0x004F7D7F; the +0x24 pair is the 12-byte map
// whose destructor is rowed as ~Rva004FA168Map 0x004F9630.
struct Rva004F7D7FRecord;
namespace _STL {
template<> vector<Rva004F7D7FRecord, allocator<Rva004F7D7FRecord> >::~vector();
}

class Rva004FA168Map
{
public:
	~Rva004FA168Map();
private:
	unsigned char m_data[0xC];
};

class Rva004F87F3
{
public:
	~Rva004F87F3();
private:
	unsigned char m_data[0xC];
};

class Rva004FA2E2Owned
{
public:
	virtual ~Rva004FA2E2Owned();
};

// vector<void *>::erase(first, last), rowed 0x0031BD55 (stlport_vector_voidptr_opt.cpp).
namespace _STL {
template<> void **vector<void *, allocator<void *> >::erase(void **first, void **last);
}

struct Gen_uw_0007fab3
{
	~Gen_uw_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	void **begin() { return (void **)m_begin; }
	void **end() { return (void **)m_end; }
	void clear() { reinterpret_cast<_STL::vector<void *> *>(this)->erase(begin(), end()); }
	Rva004FA2E2Owned **m_begin;
	Rva004FA2E2Owned **m_end;
	Rva004FA2E2Owned **m_capacity;
};

class Rva004FA2E2
{
public:
	~Rva004FA2E2();
private:
	Rva002BBD4D m_00;
	_STL::vector<Rva004F7D7FRecord> m_0C[2];
	Rva004FA168Map m_24[2];
	Rva004F87F3 m_3C;
	Gen_uw_0007fab3 m_48;
	Gen_uw_0007fab3 m_54;
	Gen_uw_0007fab3 m_60;
	_STL::vector<Rva004F69C3> m_6C;
};

Rva004FA2E2::~Rva004FA2E2()
{
	Rva004FA2E2Owned **end = m_48.m_end;
	for (Rva004FA2E2Owned **p = m_48.m_begin; p != end; ++p)
		::delete *p;
	m_48.clear();
}
