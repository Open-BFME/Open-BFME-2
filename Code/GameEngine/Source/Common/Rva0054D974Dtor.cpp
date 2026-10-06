// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0054D974@@QAE@XZ @0x0054D974 205B. Non-virtual dtor clearing three
// list<int> at +0x00/+0x04/+0x08 each holding Rva0054D8D8 pointers at node+8.
// For each list while not empty it deletes the front pointer via rowed dtor
// 0x0054D8D8 plus rowed operator delete then pop_front via rowed 0x0037BCF9,
// then destroys the three lists via rowed List_base 0x004EC395 with EH states
// 2 then 1/0/-1. Evidence: 3 loops plus 3 base destroys; unblocks 0x00381DE2.
#include <list>

class Rva0054D8D8
{
public:
	~Rva0054D8D8();
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
	int m20;
	int m24;
	int m28;
	int m2C;
	int m30;
	int m34;
	int m38;
};

class Rva0054D974
{
public:
	~Rva0054D974();
	Rva0054D8D8 *rva0054D6C8(int id);
private:
	_STL::list<int, _STL::allocator<int> > m00;
	_STL::list<int, _STL::allocator<int> > m04;
	_STL::list<int, _STL::allocator<int> > m08;
};

Rva0054D974::~Rva0054D974()
{
	_STL::list<int, _STL::allocator<int> >::iterator it;
	while ((it = m04.begin()) != m04.end()) {
		Rva0054D8D8 *p = (Rva0054D8D8 *)*it;
		if (p != 0)
			delete p;
		m04.pop_front();
	}
	while ((it = m08.begin()) != m08.end()) {
		Rva0054D8D8 *p = (Rva0054D8D8 *)*it;
		if (p != 0)
			delete p;
		m08.pop_front();
	}
	while ((it = m00.begin()) != m00.end()) {
		Rva0054D8D8 *p = (Rva0054D8D8 *)*it;
		if (p != 0)
			delete p;
		m00.pop_front();
	}
}

Rva0054D8D8 *Rva0054D974::rva0054D6C8(int id)
{
	if (id == 0)
		return 0;
	_STL::list<int, _STL::allocator<int> >::iterator it;
	for (it = m04.begin(); it != m04.end(); ++it) {
		Rva0054D8D8 *p = (Rva0054D8D8 *)*it;
		if (p->m38 == id)
			return p;
	}
	for (it = m08.begin(); it != m08.end(); ++it) {
		Rva0054D8D8 *p = (Rva0054D8D8 *)*it;
		if (p->m38 == id)
			return p;
	}
	for (it = m00.begin(); it != m00.end(); ++it) {
		Rva0054D8D8 *p = (Rva0054D8D8 *)*it;
		if (p->m38 == id)
			return p;
	}
	return 0;
}
