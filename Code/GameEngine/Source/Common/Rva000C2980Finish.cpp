// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
//
// ??1Rva000C2980@@QAE@XZ, retail 0x000C2980 292B.
// Non-virtual dtor (mangled QAE, no vptr store in retail): AudioEventRTS* at
// +0xdc deleted then nulled, an owning pointer at +0xd0 whose inlined
// destructor is the null check plus the game's C++-linkage free, vector
// <Rva00B9AC2> at +0xc4, Rva000C1BE1 (12B) at +0xb8, list base at +0xb4,
// five vector<AsciiString> at +0xa8/+0x9c/+0x90/+0x84/+0x78, AsciiString at
// +0x74/+0x70, vector<Rva00B6CF1> at +0x64, AsciiString at +0x60/+0x5c/+0x58,
// vector<AsciiString> at +0x4c.
//
// Two facts carry the whole body. The +0xd0 member is NOT a raw void*: retail
// emits the unwind state 0xe immediately before its null check, and under
// /EHsc the only thing that produces a state store there is an inlined member
// destructor. Modelling it as a one-pointer owning type with the destructor
// defined in-class reproduces `mov eax,[esi+0xd0] / test / mov byte
// [ebp-4],0xe / je / push / call free` exactly, and it also lifts the whole
// state table from 0xe..0x0 to retail's 0xf..0x0 (one more action, which is
// why retail's initial store is `mov dword [ebp-4],0xf`).
//
// The free is the game's allocator wrapper at 0x00030830, reached through the
// C++-linkage _STL::free spelling -- NOT the extern "C" import, which reaches
// the thunk 0x00628F98 and carries no unwind state. The registry.cpp
// include-guard idiom (stdlib.h first, then the _STL declaration, then the
// `#define free _STL::free` around the STL headers) is what lets the STLport
// headers coexist with that second spelling.
//
// The two element vectors are declared-only specializations so their
// destructors stay out of line and resolve to the matched rows 0x000C1C20 and
// 0x000C03D8; defining them here would re-emit _Vector_base::~_Vector_base as
// an unresolved separate call that retail has inlined.
//
// Evidence: retail call chain, deleting dtor at 0x000C3808, EH funclet
// 0x0076204B. Identity is address-derived (Rva<dtor rva>); the class may carry
// a vptr at +0 in reality, but the dtor never touches +0x00..+0x4b so it is
// modelled as pad.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include "ascii_string.h"
#include <vector>
#include <list>
#undef free

struct Rva00B9AC2 { char _pad[0x18]; };
struct Rva00B6CF1 { char _pad[8]; };
struct Rva000C1BE1 { void *_p[3]; ~Rva000C1BE1(); };
class AudioEventRTS { public: ~AudioEventRTS(); };

// The +0xd0 member. Destructor defined in-class so /EHsc gives retail's
// unwind state around the null-checked free.
struct Rva000C2980OwningPtr
{
	void *p;
	~Rva000C2980OwningPtr()
	{
		if (p != 0)
			_STL::free(p);
	}
};

// Declared-only element vectors: ~vector() resolves to the matched rows
// (0x000C1C20 for Rva00B9AC2, 0x000C03D8 for Rva00B6CF1).
namespace _STL
{
template <> class vector<Rva00B9AC2, allocator<Rva00B9AC2> >
{
public:
	~vector();

private:
	Rva00B9AC2 *m_begin;
	Rva00B9AC2 *m_finish;
	Rva00B9AC2 *m_end;
};

template <> class vector<Rva00B6CF1, allocator<Rva00B6CF1> >
{
public:
	~vector();

private:
	Rva00B6CF1 *m_begin;
	Rva00B6CF1 *m_finish;
	Rva00B6CF1 *m_end;
};
}

class Rva000C2980
{
public:
	~Rva000C2980();

private:
	char _pad00[0x4c]; // +0x00..+0x4b
	_STL::vector<AsciiString> m_4c; // +0x4c
	AsciiString m_58; // +0x58
	AsciiString m_5c; // +0x5c
	AsciiString m_60; // +0x60
	_STL::vector<Rva00B6CF1> m_64; // +0x64
	AsciiString m_70; // +0x70
	AsciiString m_74; // +0x74
	_STL::vector<AsciiString> m_78; // +0x78
	_STL::vector<AsciiString> m_84; // +0x84
	_STL::vector<AsciiString> m_90; // +0x90
	_STL::vector<AsciiString> m_9c; // +0x9c
	_STL::vector<AsciiString> m_a8; // +0xa8
	_STL::_List_base<AsciiString, _STL::allocator<AsciiString> > m_b4; // +0xb4
	Rva000C1BE1 m_b8; // +0xb8
	_STL::vector<Rva00B9AC2> m_c4; // +0xc4
	Rva000C2980OwningPtr m_d0; // +0xd0
	char _padD4[8]; // +0xd4..+0xdb
	AudioEventRTS *m_dc; // +0xdc
};

// The +0xdc member and its null-out are explicit; everything from +0xd0 down
// runs through the implicit member destructors, which is where the remaining
// unwind states come from.
Rva000C2980::~Rva000C2980()
{
	if (m_dc != 0) {
		delete m_dc;
		m_dc = 0;
	}
}