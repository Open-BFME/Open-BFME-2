#include "../GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilderFarmLibrary.h"
#include <stdlib.h>
// cl: /MD
//
// Dynamic initializers from the 0x007AB7DA strip that construct a file-scope
// STLport container through its allocator-taking constructor: the defaulted
// allocator_type() argument is the one-byte stack temporary (push ecx /
// lea eax,[esp+3]), then atexit() registers the already-rowed cleanup thunk.
// Each constructor is an out-of-line folded COMDAT, so the container type
// spelled for each call is the one the ledger names at that address; the
// cleanup thunk's tail-jump target is noted beside it. The owning TUs are
// unrecovered, so each initializer keeps an honest address name and its global
// an address-named extern.

struct BfmeE16;
struct BfmeE12;
struct BfmePod28;

namespace _STL
{
	template <class T> class allocator
	{
	public:
		allocator() {}
	};

	template <class T, class A = allocator<T> > class vector
	{
	public:
		explicit vector(const A &a = A());
	};

	template <class T, class A = allocator<T> > class deque
	{
	public:
		explicit deque(const A &a = A());
	};

	template <class T, class A = allocator<T> > class list
	{
	public:
		explicit list(const A &a = A());
	};
}

typedef _STL::vector<BfmeE16> E16Vector;
typedef _STL::deque<BfmeE12> E12Deque;
typedef _STL::list<BfmePod28> Pod28List;
typedef _STL::list<int> IntList;

void __cdecl rva007B6A64();
void __cdecl rva007B70C9();
void __cdecl rva007B75F6();
void __cdecl rva007B760A();
void __cdecl rva007B76DC();
void __cdecl rva007B77B9();
void __cdecl rva007B7A7D();
void __cdecl rva007B82E7();
void __cdecl rva007B8F9F();
void __cdecl rva007B8FBD();
void __cdecl rva007B91E4();
void __cdecl rva007B96BC();
void __cdecl rva007B982F();
void __cdecl rva007B9843();
void __cdecl rva007B6CE1();
void __cdecl rva007B7CAF();
void __cdecl rva007B839B();
void __cdecl rva007B8590();

extern unsigned g_Va00DF29A8;
extern unsigned int g_00DFE358[3];
extern unsigned g_Va00DFF134;
namespace _STL { template <class T> struct _Nonconst_traits; template <class T, class Traits> struct _Deque_iterator; }
extern unsigned int g_00E031A8[10];	// deque<BfmeE12>; stlport_deque_e12_findnode.cpp's view names its first iterator
extern unsigned g_Va00E04920[3];
extern unsigned g_Va00E0657C;
extern unsigned g_Va00E06654[3];
extern unsigned g_Va00E06670;
extern unsigned g_Va00DE6194;
extern unsigned g_Va00E032DC;
extern unsigned g_Va00E0362C;

struct Rva007ABB96AllocCtorInits
{
	static void rva007ABB96();
	static void rva007ACDC4();
	static void rva007AD7C0();
	static void rva007AD899();
	static void rva007ADAB5();
	static void rva007ADE2F();
	static void rva007AE5A5();
	static void rva007B02D9();
	static void rva007B31A8();
	static void rva007B31FA();
	static void rva007B38F4();
	static void rva007B4788();
	static void rva007B4C9E();
	static void rva007B4D03();
	static void rva007AC2FA();
	static void rva007AED2A();
	static void rva007B05DE();
	static void rva007B0D55();
};


// 0x007ACDC4 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00DF29A8, atexit(0x007B70C9 -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007ACDC4()
{
	( (E16Vector *)&g_Va00DF29A8 )->E16Vector::vector();
	atexit( rva007B70C9 );
}





// 0x007AE5A5 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00DFF134, atexit(0x007B7A7D -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007AE5A5()
{
	( (E16Vector *)&g_Va00DFF134 )->E16Vector::vector();
	atexit( rva007B7A7D );
}

// 0x007B02D9 (29B): deque<BfmeE12> allocator ctor 0x004226CE on VA 0x00E031A8, atexit(0x007B82E7 -> 0x005858F3)
void Rva007ABB96AllocCtorInits::rva007B02D9()
{
	( (E12Deque *)&g_00E031A8 )->E12Deque::deque();
	atexit( rva007B82E7 );
}


// 0x007B31FA (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00E04494, atexit(0x007B8FBD -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007B31FA()
{
	( (E16Vector *)&AIEconomyBuilder::m_farmList )->E16Vector::vector();
	atexit( rva007B8FBD );
}

// 0x007B38F4 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00E04920, atexit(0x007B91E4 -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007B38F4()
{
	( (E16Vector *)&g_Va00E04920 )->E16Vector::vector();
	atexit( rva007B91E4 );
}

// 0x007B4788 (29B): list<BfmePod28> allocator ctor 0x005BD5DC on VA 0x00E0657C, atexit(0x007B96BC -> 0x005BD5EE)
void Rva007ABB96AllocCtorInits::rva007B4788()
{
	( (Pod28List *)&g_Va00E0657C )->Pod28List::list();
	atexit( rva007B96BC );
}

// 0x007B4C9E (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00E06654, atexit(0x007B982F -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007B4C9E()
{
	( (E16Vector *)&g_Va00E06654 )->E16Vector::vector();
	atexit( rva007B982F );
}

// 0x007B4D03 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00E06670, atexit(0x007B9843 -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007B4D03()
{
	( (E16Vector *)&g_Va00E06670 )->E16Vector::vector();
	atexit( rva007B9843 );
}

// 0x007AC2FA (29B): list<int> allocator ctor 0x002C5309 on VA 0x00DE6194, atexit(0x007B6CE1 -> 0x00200667)
void Rva007ABB96AllocCtorInits::rva007AC2FA()
{
	( (IntList *)&g_Va00DE6194 )->IntList::list();
	atexit( rva007B6CE1 );
}


// 0x007B05DE (29B): list<int> allocator ctor 0x002C5309 on VA 0x00E032DC, atexit(0x007B839B -> 0x002B905D)
void Rva007ABB96AllocCtorInits::rva007B05DE()
{
	( (IntList *)&g_Va00E032DC )->IntList::list();
	atexit( rva007B839B );
}

// 0x007B0D55 (29B): list<int> allocator ctor 0x002C5309 on VA 0x00E0362C, atexit(0x007B8590 -> 0x00200667)
void Rva007ABB96AllocCtorInits::rva007B0D55()
{
	( (IntList *)&g_Va00E0362C )->IntList::list();
	atexit( rva007B8590 );
}
