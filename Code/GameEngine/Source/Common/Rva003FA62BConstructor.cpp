// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva003FA62B@@QAE@PAURva003FA62BOwner@@@Z, retail 0x003FA6B4..0x003FA6FF
// (75 bytes, EH, ret 4). Constructor of the listener whose vtable 0x008378B4 the
// deleting destructor names Rva003FA62B: an empty vector at +4 (rowed unwind
// through the folded buffer destructor), the owner kept at +0x10 and the
// listener registered with the owner's list at +0x1C (rowed append 0x005A0B4C).
// The first base needs a polymorphic stand-in with an inline destructor (its
// out-of-line copy is the unwinding target 0x004EDFFF). Class name
// address-derived.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free

enum ObjectID { INVALID_ID = 0 };

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct Rva003FA62BOwner
{
	char m_pad00[0x1C];
	Rva005A0B4CList m_list; // +0x1C
};

class Gen_uwm_004edfff
{
public:
	virtual void slot00();
	~Gen_uwm_004edfff() {}
};

class Rva003FA62B : public Gen_uwm_004edfff
{
public:
	Rva003FA62B(Rva003FA62BOwner *owner);
	virtual ~Rva003FA62B();
private:
	_STL::vector<ObjectID> m_04;
	Rva003FA62BOwner *m_owner; // +0x10
};

Rva003FA62B::Rva003FA62B(Rva003FA62BOwner *owner)
	: m_owner(owner)
{
	owner->m_list.append((Rva002BA8F1Listener *)this);
}
