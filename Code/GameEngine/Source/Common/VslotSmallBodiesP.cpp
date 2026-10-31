// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes) in the /O2 library range, batch P. As in
// VslotSmallBodiesA-O, each class and method is address-derived and models
// only what its body touches; the comment above each gives the .rdata slot
// address(es) that reference it. Meanings are not recovered.

typedef int Int;
typedef bool Bool;

// slot at VA 0x00CE8C3C: stores the flag as bit 17 of the +0x5C word.
class Rva006CBEB0
{
public:
	void rva006CBEB0(Int enable);
private:
	char m_pad00[0x5C];
	unsigned int m_bits0 : 17;
	unsigned int m_bit17 : 1;
	unsigned int m_bits18 : 14;
};
void Rva006CBEB0::rva006CBEB0(Int enable)
{
	m_bit17 = (enable != 0);
}

// slots at VA 0x00CEA4C8/0x00CEA4E4, 0x00CEA568/0x00CEA584 and
// 0x00CEA608/0x00CEA624: push this object onto the free list headed at VA
// 0x00E18020 (resp. 0x00E18024 and 0x00E18028), linking through +0x08.
class Rva006D8670
{
public:
	void rva006D8670();
	void rva006D8810();
	void rva006D8A20();
private:
	char m_pad00[0x08];
	Rva006D8670 *m_next;
};
// The AptInteger, AptFloat and AptBoolean free lists (heads at VA 0x00E18020,
// 0x00E18024 and 0x00E18028), popped by their Create bodies and drained by
// AptScalarClearPoolsBFME2.cpp; defined here: nothing else owns them.
class AptInteger;
class AptFloat;
class AptBoolean;
AptInteger *g_aptIntegerFreeList;
AptFloat *g_aptFloatFreeList;
AptBoolean *g_aptBooleanFreeList;
void Rva006D8670::rva006D8670()
{
	m_next = (Rva006D8670 *)g_aptIntegerFreeList;
	g_aptIntegerFreeList = (AptInteger *)this;
}
void Rva006D8670::rva006D8810()
{
	m_next = (Rva006D8670 *)g_aptFloatFreeList;
	g_aptFloatFreeList = (AptFloat *)this;
}
void Rva006D8670::rva006D8A20()
{
	m_next = (Rva006D8670 *)g_aptBooleanFreeList;
	g_aptBooleanFreeList = (AptBoolean *)this;
}

// slot at VA 0x00CE8C4C: runs vslot 0 of the +0x4C object unless it is NULL
// or the 0xBAADF00D poison value.
class Rva006E0440Target
{
public:
	virtual void vslot00();
};
class Rva006E0440
{
public:
	void rva006E0440();
private:
	char m_pad00[0x4C];
	Rva006E0440Target *m_target;
};
void Rva006E0440::rva006E0440()
{
	if (m_target && m_target != (Rva006E0440Target *)0xBAADF00D)
		m_target->vslot00();
}

// slot at VA 0x00CEE988: copies the +0x10/+0x14 pair of the +0x30 object
// into the argument.
struct Rva00709BF0Pair
{
	Int m_00;
	Int m_04;
};
struct Rva00709BF0Inner
{
	char m_pad00[0x10];
	Rva00709BF0Pair m_10;
};
class Rva00709BF0
{
public:
	void rva00709BF0(Rva00709BF0Pair *out);
private:
	char m_pad00[0x30];
	Rva00709BF0Inner *m_30;
};
void Rva00709BF0::rva00709BF0(Rva00709BF0Pair *out)
{
	*out = m_30->m_10;
}

// slots at VA 0x00CEE91C, 0x00CEE98C and 0x00CEEB3C: hands out and clears the
// pointer held at VA 0x00E1835C; the second argument is unused.
#include "../../../Libraries/Source/Apt/AptObject/AptScriptFunction.h"
class Rva00709E50 : public AptScriptFunctionBase
{
public:
	void rva00709E50(void **out, Int unused);
};
void Rva00709E50::rva00709E50(void **out, Int unused)
{
	*out = spFrameStack;
	spFrameStack = 0;
}
