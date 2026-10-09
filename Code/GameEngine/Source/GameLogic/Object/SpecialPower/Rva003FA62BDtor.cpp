// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva003FA62B@@QAE@XZ, retail 0x003FA62B..0x003FA681 (86 bytes, EH): the
// destructor of the listener whose vtable is 0x00C378B4 (its other slots sit
// beside CashHackSpecialPower's code). It leaves the +0x10 owner's listener
// list at +0x1C (rowed removal 0x002B7250) and clears its +0x04 record vector
// (rowed clear 0x003FA5B9), whose storage the vector's own teardown then
// frees; the listener base restores its vtable 0x00C62A20. /EHs keeps the
// EH state store retail makes before the inlined free.

#include <vector>

struct BfmePod8
{
	int a;
	int b;
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

struct Rva003FA62BOwner
{
	unsigned char m_pad00[0x1C];
	Rva002B7250 m_listeners1C;				// +0x1C
};

class Rva003FA5B9
{
public:
	void clear();
};

class Rva003FA62BBase
{
public:
	~Rva003FA62BBase() {}
	virtual void b0();
	virtual void b1();
};

class Rva003FA62B : public Rva003FA62BBase
{
public:
	~Rva003FA62B();							// slot 0 of its table is 0x003FA464, not a destructor
private:
	_STL::vector<BfmePod8> m_records04;		// +0x04
	Rva003FA62BOwner *m_owner10;			// +0x10
};

Rva003FA62B::~Rva003FA62B()
{
	m_owner10->m_listeners1C.rva002B7250((CreateAHeroData *)this);
	reinterpret_cast<Rva003FA5B9 *>(this)->clear();
}
