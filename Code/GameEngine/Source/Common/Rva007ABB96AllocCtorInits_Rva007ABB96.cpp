// Split from Rva007ABB96AllocCtorInits.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
#include <stdlib.h>
#include "../GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilderFarmLibrary.h"
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

// RVA 0x009DF580: Rva00200D38Ctor.cpp's _STL::vector<const ModuleData *> g_vec00200D38.
class ModuleData;
extern _STL::vector<const ModuleData *> g_vec00200D38;
extern unsigned g_Va00DF29A8;
extern unsigned int g_00DFE174;
extern unsigned int g_00DFE1AC;
unsigned g_00DFE358;	// retail RVA 0x009FE358 (.bss), defined here
class BfmeItemKA;
extern BfmeItemKA **g_bfmeBegKA;
extern unsigned g_Va00DFF134;
// RVA 0x00A04484: AIWallBuilder.cpp's RvaVector g_00E04484.
struct RvaVector;
extern RvaVector g_00E04484;
extern unsigned g_Va00E04920;
extern unsigned g_Va00E0657C;
extern unsigned g_Va00E06654;
extern unsigned g_Va00E06670;
extern unsigned g_Va00DE6194;
// RVA 0x00A01E68: the vector whose begin pointer ObjectFilterRelease.cpp defines
// as g_validityBegin (the data ledger's owner of the address).
extern unsigned char *g_validityBegin;
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

// 0x007ABB96 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00DDF580, atexit(0x007B6A64 -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007ABB96()
{
	( (E16Vector *)&g_vec00200D38 )->E16Vector::vector();
	atexit( rva007B6A64 );
}


// 0x007AD7C0 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00DFE174, atexit(0x007B75F6 -> 0x0002CC70)
void Rva007ABB96AllocCtorInits::rva007AD7C0()
{
	( (E16Vector *)&g_00DFE174 )->E16Vector::vector();
	atexit( rva007B75F6 );
}

// 0x007AD899 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00DFE1AC, atexit(0x007B760A -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007AD899()
{
	( (E16Vector *)&g_00DFE1AC )->E16Vector::vector();
	atexit( rva007B760A );
}

// 0x007ADAB5 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00DFE358, atexit(0x007B76DC -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007ADAB5()
{
	( (E16Vector *)&g_00DFE358 )->E16Vector::vector();
	atexit( rva007B76DC );
}

// 0x007ADE2F (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00DFEA44, atexit(0x007B77B9 -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007ADE2F()
{
	( (E16Vector *)&g_bfmeBegKA )->E16Vector::vector();
	atexit( rva007B77B9 );
}



// 0x007B31A8 (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00E04484, atexit(0x007B8F9F -> 0x0007FAB3)
void Rva007ABB96AllocCtorInits::rva007B31A8()
{
	( (E16Vector *)&g_00E04484 )->E16Vector::vector();
	atexit( rva007B8F9F );
}







// 0x007AED2A (29B): vector<BfmeE16> allocator ctor 0x004F710A on VA 0x00E01E68, atexit(0x007B7CAF -> 0x003615E5)
void Rva007ABB96AllocCtorInits::rva007AED2A()
{
	( (E16Vector *)&g_validityBegin )->E16Vector::vector();
	atexit( rva007B7CAF );
}


