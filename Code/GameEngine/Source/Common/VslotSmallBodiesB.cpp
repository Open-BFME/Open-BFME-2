// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
//
// Small vtable-slot bodies with no ledger owner and no Ghidra size (sized from
// their bytes), batch B: bodies around one direct call. Each class and method
// is address-derived unless the ledger already names it, and models only what
// its body touches; the comment above each gives the vtable and slot. A
// callee's argument count is read from its own ret; unnamed callees are
// pinned by address. Meanings are not recovered.

#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>

typedef int Int;
typedef bool Bool;

// vtable 0x00BC4E34#6: raise the byte at +0x1464, then 0x002D7E68 on this.
class Rva0004E3A6
{
public:
	void rva0004E3A6(Int value);
	void rva002D7E68(Int value);
private:
	char m_pad00[0x1464];
	Bool m_1464;
};
void Rva0004E3A6::rva0004E3A6(Int value)
{
	m_1464 = true;
	rva002D7E68(value);
}

// vtable 0x00BCBC40#7: 0x000B5FE6 on this when the field at +0x50 is set.
class Rva000B7C18
{
public:
	void rva000B7C18();
	void rva000B5FE6();
private:
	char m_pad00[0x50];
	void *m_50;
};
void Rva000B7C18::rva000B7C18()
{
	if (m_50)
		rva000B5FE6();
}

// vtable 0x00BD3B1C#7: an empty body taking the reference-counted handle
// Rva00087A93 by value (its destructor 0x0007B724 runs on return).
class Rva00087A93
{
public:
	~Rva00087A93();
private:
	void *m_data;
};
class Rva001524BE
{
public:
	void rva001524BE(Rva00087A93 handle);
};
void Rva001524BE::rva001524BE(Rva00087A93) {}

// vtable 0x00BC4738#24: an empty body taking an AsciiString by value.
class Rva00239982
{
public:
	void rva00239982(AsciiString text);
};
void Rva00239982::rva00239982(AsciiString) {}

// vtable 0x00BC7C90#73: an empty body taking seven arguments, the second a
// UnicodeString by value.
class Rva00314C93
{
public:
	void rva00314C93(Int, UnicodeString text, Int, Int, Int, Int, Int);
};
void Rva00314C93::rva00314C93(Int, UnicodeString, Int, Int, Int, Int, Int) {}

// vtable 0x00C363C8#0: 0x003EF08B on this with the first of three arguments.
class Rva003EF13E
{
public:
	void rva003EF13E(Int value, Int, Int);
	void rva003EF08B(Int value);
	void rva003EF1D9(const _STL::vector<Int> &vec);
};
void Rva003EF13E::rva003EF13E(Int value, Int, Int) { rva003EF08B(value); }

void Rva003EF13E::rva003EF1D9(const _STL::vector<Int> &vec)
{
	for (unsigned i = 0; i < vec.size(); ++i)
		rva003EF08B(vec[i]);
}

// vtable 0x00BC57E0#18 and #19: hand the argument to two cdecl functions,
// the second the ledger's Rva000A8F64Set.
void __cdecl Rva000A90B0(Int value);
void __cdecl Rva000A8F64Set(bool enabled);
class Rva00062A1C
{
public:
	void rva00062A1C(Int value);
	void rva00062A29(bool enabled);
};
void Rva00062A1C::rva00062A1C(Int value) { Rva000A90B0(value); }
void Rva00062A1C::rva00062A29(bool enabled) { Rva000A8F64Set(enabled); }

// vtable 0x00BC64D8#4: the object at +0x44 runs the ledger's
// Rva000724AE::rva000724D7 on the field at +0x1C.
class Rva000724AE
{
public:
	void *rva000724D7(Int *value);
};
class Rva00072559
{
public:
	void rva00072559();
private:
	char m_pad00[0x1C];
	Int m_1C;
	char m_pad20[0x44 - 0x20];
	Rva000724AE *m_44;
};
void Rva00072559::rva00072559() { m_44->rva000724D7(&m_1C); }

// vtable 0x00BC7F74#0 and #1: allocate and free through operator new[] and
// delete[], each with an unused second argument.
class Rva000910E1
{
public:
	void *rva000910E1(unsigned int size, Int);
	void rva000910EE(void *block, Int);
};
void *Rva000910E1::rva000910E1(unsigned int size, Int) { return operator new[](size); }
void Rva000910E1::rva000910EE(void *block, Int) { operator delete[](block); }

// vtable 0x00C35B28#1: 0x00261C89 on the object at +4 of the argument.
class Rva00261C89
{
public:
	void rva00261C89();
};
struct Rva00261D01Holder
{
	void *m_00;
	Rva00261C89 *m_04;
};
class Rva00261D01
{
public:
	void rva00261D01(Rva00261D01Holder *holder);
};
void Rva00261D01::rva00261D01(Rva00261D01Holder *holder) { holder->m_04->rva00261C89(); }

// vtable 0x00BE25B4#1 (shared by five stores): clear the pointer vector at
// +0xC (STLport erase(begin, end), 0x0031BD55).
class Rva001FF8FB
{
public:
	void rva001FF8FB();
private:
	char m_pad00[0x0C];
	_STL::vector<void *> m_0C;
};
void Rva001FF8FB::rva001FF8FB() { m_0C.clear(); }

// vtable 0x00C0DB34#2 and #0: write the four-character code 'free' and
// 'look' through the ledger's DataChunkOutput::writeInt of the object at +4.
class DataChunkOutput
{
public:
	void writeInt(Int value);
};
class Rva00330484
{
public:
	void rva00330484(Int);
	void rva00330494(Int);
private:
	void *m_00;
	DataChunkOutput *m_04;
};
void Rva00330484::rva00330484(Int) { m_04->writeInt('free'); }
void Rva00330484::rva00330494(Int) { m_04->writeInt('look'); }
