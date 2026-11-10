// Rva003306B0 destructor, retail 0x00330789 (105B EH), the WB unnamed slot
// after the rowed clear 0x0033073C. It removes every CreateAHeroData in the
// vector at +0x10 through the rowed remove 0x003306B0, notifies the listener
// list at +0 through the rowed forEach 0x0033066D with the virtual listener
// callback (retail's slot +0x0C vcall thunk 0x005CB265), then lets the two
// member destructors free
// the vector storage and the list's pointer array. The compiler's
// member-destruction states (vector alive = 1, list only = 0) come out of the
// member declarations, so the body itself carries no explicit state handling.
// The method name is address-derived.
//
// The loop condition reads the vector's first word through a volatile pointer
// into a named local: _ReadWriteBarrier() also forces the reload but leaves the
// this-setup mov ecx,esi in the loop body, and a bare reload is CSE'd across the
// remove call. The named volatile local yields retail's begin load into eax,
// compare against end, and the shared ecx=esi in the latch for the forEach call.
// stlport
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
namespace _STL { void __cdecl free(void *block); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseListStorage(void *storage)
{
	_STL::free(storage);
}
#include <vector>

#include "../../Include/Common/Rva0053FA0A.h"

#include "../../Include/GameLogic/CreateAHeroData.h"

// Retail's member-pointer call goes through the slot +0x0C vcall thunk
// (0x005CB265, jmp [eax+0xC]), so the listener's vtable puts notify fourth;
// the three leading slots are the class's other callbacks, unnamed here.
class Rva0033066DListener
{
public:
	virtual void notify00(void *);
	virtual void notify04(void *);
	virtual void notify08(void *);
	virtual void notify(void *);
};

class Rva0033066DList
{
public:
	void forEach(void (Rva0033066DListener::*notify)(void *), void *arg);
	~Rva0033066DList()
	{
		if (m_begin)
			releaseListStorage(m_begin);
	}

private:
	Rva0033066DListener **m_begin;		// +0x00
	Rva0033066DListener **m_end;		// +0x04
	Rva0033066DListener **m_capacity;	// +0x08
	unsigned int m_index;			// +0x0C
};

struct Rva003306B0Entry;
namespace _STL {
template<> inline void allocator<Rva003306B0Entry *>::deallocate(Rva003306B0Entry **__p, size_type) const
{
	if (__p != 0) releaseListStorage((void *)__p);
}
}

class Rva003306B0
{
public:
	void rva003306B0(CreateAHeroData *key);	// 0x003306B0
	~Rva003306B0();				// 0x00330789

private:
	Rva0033066DList m_list;			// +0x00
	// Not vector<void *>: retail's unwind action for +0x10 jumps to the
	// 14-byte free-first-pointer body 0x0007FAB3, not vector<void *>'s /Od
	// destructor 0x00027370. A unit-local element spelling keeps its
	// instantiations apart from other units' vector<CreateAHeroData *>.
	_STL::vector<struct Rva003306B0Entry *> m_vec;	// +0x10
};

Rva003306B0::~Rva003306B0()
{
	for (;;) {
		Rva003306B0Entry **begin = *(Rva003306B0Entry **volatile *)&m_vec;
		if (begin == m_vec.end())
			break;
		rva003306B0((CreateAHeroData *)*m_vec.begin());
	}
	m_list.forEach(&Rva0033066DListener::notify, this);
}
