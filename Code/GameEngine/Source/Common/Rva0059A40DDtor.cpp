// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva0059A85C@@UAE@XZ @0x0059A40D 98B (the opaque pin spelling). Destructor
// of the class Rva0059A85CCtor.cpp constructs (vtable 0x00C70DE4, base
// Rva00506B1B restored out of line by 0x00506B28): the pointer vector at +8
// is cleared through the shared range erase 0x0031BD55 and the +0x18 set is
// destroyed by an explicit call to 0x002F0B52 -- retail tracks no unwind state
// for it (entry state 1), so this unit views it as raw storage; the vector
// buffer frees inline. Identity of the class is the ctor TU's.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free
class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
	virtual void v0();
	virtual void v1();
	bool m_04;
};
class Rva002EE9B7
{
public:
	~Rva002EE9B7();
	char m_data[25];
};
class Rva0059A85C : public Rva00506B1B
{
public:
	virtual ~Rva0059A85C();
private:
	_STL::vector<void *> m_vec;
	void *m_outer;
	char m_set[25];
};
Rva0059A85C::~Rva0059A85C()
{
	m_vec.clear();
	((Rva002EE9B7 *)m_set)->~Rva002EE9B7();
}
