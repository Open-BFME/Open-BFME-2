// ?rva003B7647@Rva003B56A5@@QAEXXZ
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003B7647@Rva003B56A5@@QAEXXZ @0x003B7647 36B: reset via swap with a
// fresh temp: constructs a 0x20-byte Rva003B761E temp through rowed
// 0x003B761E, swaps it with this through rowed Rva003B56A5::swap at
// 0x003B56A5, then runs the pinned 0x003B7167 temp cleanup. Evidence: temp
// address flows to all three calls, no member access on this, plain frame
// Constructor761E/41B calls only vector-base211E58/29B, which calls
// allocator-proxy14F3C4/11B. The full leaf performs one pointer store;
// the chain allocates nothing and cannot throw a C++ exception. Its
// throw() declaration prevents placement-new rollback EH, while the
// placement result forwards the constructor EAX to swap exactly.
// Original type and method identity remain unresolved; these two class
// spellings are existing consumed-prefix views, not inferred inheritance.
#include <new>

class Rva003B56A5
{
public:
	void swap(Rva003B56A5 *other);
	void rva003B7647(void);

private:
	char m_opaque[0x20];
};

class Rva003B761E
{
public:
	Rva003B761E() throw();
	void rva003B7167();
private: char storage[0x20];
};

void Rva003B56A5::rva003B7647(void)
{
	char storage[sizeof(Rva003B761E)];
	Rva003B761E *tmp = new (storage) Rva003B761E;
	((Rva003B56A5*)tmp)->swap(this);
	((Rva003B761E*)storage)->rva003B7167();
}
