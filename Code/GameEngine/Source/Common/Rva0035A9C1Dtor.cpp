// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /arch:SSE /Ireference/shims/moduledata
// stlport
// ??1Rva0035A9C1@@UAE@XZ @0x0035A9C1 125B
// Evidence: vtable 0x00C153E0#0 via deleting dtor 0x0035ABA4; Snapshot base vtable 0x00BBB554; forEach 0x00359BE8 with callback 0x1FF3A9 (receiver virtual slot zero); list clear/dtor 0x0023DAA5/0x004EC395 at +0x14; array delete 0x0035A18D at +0x40; free 0x00030830 of +0x04 buffer.
#include <stdlib.h>
#include <vector>
#include <list>

// TerrainResourceManager.cpp's cell view: an eight-byte-element vector plus a
// state word. Only the array delete 0x0035A18D is called here.
struct BfmePod8
{
public:
	int a[2]; // +0x00 +0x00
};

class Rva0035A18D {
public: Rva0035A18D();~Rva0035A18D();
 _STL::vector<BfmePod8> values; int state;
};

class Rva00359E04Owner;
class Rva00359E04Listener
{
public:
	virtual void notify00(Rva00359E04Owner *owner);
	virtual void notify04(Rva00359E04Owner *owner);
	virtual void notify08(Rva00359E04Owner *owner);
	virtual void notify0C(Rva00359E04Owner *owner);
	virtual void notify10(Rva00359E04Owner *owner);
};
struct Rva00359AECCall;
class Rva00359BE8List
{
public:
	void forEach(void (Rva00359E04Listener::*notify)(Rva00359E04Owner *), Rva00359E04Owner *owner);
	void apply(const Rva00359AECCall &call);
	~Rva00359BE8List() { if (m_begin) free(m_begin); }
private:
	Rva00359E04Listener **m_begin; // +0x00
	Rva00359E04Listener **m_end; // +0x04
	Rva00359E04Listener **m_capacity; // +0x08
	unsigned int m_index; // +0x0C
};
class Rva00359E04Owner
{
public:
	void rva00359E04();
private:
	char m_unmodelled_00[4]; // +0x00
public:
	Rva00359BE8List m_listeners; // +0x04 +0x04
};

#include "Common/Snapshot.h"

// Native20B cleanup guards null before adjusting to the16B listener base
// at4. Native11B cleanup at14 calls the full5B list destructor200667,
// then the23B list-base destructor4EC395; use real STLport rather than
// the old empty private list-base view. Full125B parent remains unchanged.
class Rva0035A9C1 : public Snapshot, private Rva00359BE8List
{
public:
	virtual ~Rva0035A9C1();
private:
	_STL::list<int> m_list14;
	char m_pad18[0x40 - 0x18];
	Rva0035A18D *m_arr40;
};

Rva0035A9C1::~Rva0035A9C1()
{
	static_cast<Rva00359BE8List *>(this)->forEach(&Rva00359E04Listener::notify00, (Rva00359E04Owner *)this);
	(((_STL::_List_base<int, _STL::allocator<int> > *)((char *)this + 0x14)))->clear();
	Rva0035A18D *arr = m_arr40;
	if (arr)
		delete[] arr;
	m_arr40 = 0;
}
