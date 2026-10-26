// cl: /MD
// File-scope STLport container initializers from the 0x007ACxxx..0x007B3xxx
// initializer strip: ecx = &storage, call the rowed default constructor of
// the container instantiation, then atexit() the rowed cleanup thunk for the
// same storage (Rva007B6880Thunks.cpp). Same shape as the plain-object
// initializers in Rva007AC6DDGlobalInits.cpp. The container constructors are
// declared only (their bodies are rowed elsewhere), so this unit names the
// instantiations through bare template declarations instead of the STLport
// headers, whose inline constructors would be expanded here. The owning TUs
// and the original variable names are unrecovered; storage keeps the global
// the cleanup thunk already names. Retail bytes give every operand.
#include "../GameLogic/LargeGroupAudio/LargeGroupAudioKeyTreeStorage.h"

inline void *operator new(unsigned int, void *where)
{
	return where;
}

extern "C" int __cdecl atexit(void (__cdecl *callback)());

class DamageFX;
enum NameKeyType {};
struct BfmePod8;
struct Rva0030A101Element;

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;
}

namespace _STL
{
	template <class T> struct less;
	template <class T> struct equal_to;
	template <class T> struct hash;
	template <class A, class B> struct pair;
	template <class T> class allocator
	{
	public:
		allocator() {}
	};

	template <class K, class V, class C = less<K>, class A = allocator<pair<const K, V> > >
	class map
	{
	public:
		map();
	};

	template <class K, class V, class H, class E, class A = allocator<pair<const K, V> > >
	class hash_map
	{
	public:
		hash_map();
	};
	template <class T, class A = allocator<T> >
	class list
	{
	public:
		explicit list(const A &a);
	};

	template <class T, class A = allocator<T> >
	class deque
	{
	public:
		explicit deque(const A &a);
	};
}

typedef _STL::map<unsigned char, int> Rva0033C432Map;
typedef _STL::map<int, BfmePod8> Rva0024613CMap;
typedef _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > Rva00524ED5Map;
typedef _STL::hash_map<int, Rva0030A101Element, _STL::hash<int>, _STL::equal_to<int> > Rva0030A101Map;

extern unsigned int g_Va00DF29B4;
void __cdecl rva007B70D3();

// ?rva007ACDE1@@YAXXZ @0x007ACDE1 22B: map ctor 0x0033C432 on &g_Va00DF29B4, atexit(0x007B70D3).
void rva007ACDE1()
{
	new (&g_Va00DF29B4) Rva0033C432Map;
	atexit(rva007B70D3);
}

extern unsigned int g_Va00E0319C[3];
void __cdecl rva007B82DD();

// ?rva007B02C3@@YAXXZ @0x007B02C3 22B: map ctor 0x0033C432 on g_Va00E0319C, atexit(0x007B82DD).
void rva007B02C3()
{
	new (g_Va00E0319C) Rva0033C432Map;
	atexit(rva007B82DD);
}

void __cdecl rva007B80F1();

// ?rva007AF8CD@@YAXXZ @0x007AF8CD 22B: map ctor 0x0024613C on g_lgaKeyRecords, atexit(0x007B80F1).
void rva007AF8CD()
{
	new (g_lgaKeyRecords) Rva0024613CMap;
	atexit(rva007B80F1);
}

extern unsigned int g_Va00E03168;
void __cdecl rva007B82D3();

// ?rva007B0290@@YAXXZ @0x007B0290 22B: map ctor 0x0024613C on &g_Va00E03168, atexit(0x007B82D3).
void rva007B0290()
{
	new (&g_Va00E03168) Rva0024613CMap;
	atexit(rva007B82D3);
}

extern unsigned int g_Va00E04938;
void __cdecl rva007B91F8();

// ?rva007B3945@@YAXXZ @0x007B3945 22B: hash_map ctor 0x00524ED5 on &g_Va00E04938, atexit(0x007B91F8).
void rva007B3945()
{
	new (&g_Va00E04938) Rva00524ED5Map;
	atexit(rva007B91F8);
}

extern unsigned int g_Va00DFF494;
void __cdecl rva007B7AE1();

// ?rva007AE6E6@@YAXXZ @0x007AE6E6 22B: hash_map ctor 0x0030A101 on &g_Va00DFF494, atexit(0x007B7AE1).
void rva007AE6E6()
{
	new (&g_Va00DFF494) Rva0030A101Map;
	atexit(rva007B7AE1);
}

// Containers built from an explicit default allocator temporary: retail
// reserves the one-byte allocator in a pushed stack slot (push ecx; lea
// eax,[esp+3]) and passes it by reference to the rowed (const allocator &)
// constructor, then registers the cleanup and pops both slots.
struct Coord3D;
struct BfmeWordValue4;

extern unsigned int g_Va00E03174;
extern unsigned int g_Va00DFF144;
extern unsigned int g_Va00DFF148;
void __cdecl rva007B82C9();
void __cdecl rva007B7A87();
void __cdecl rva007B7A91();

// ?rva007B02A6@@YAXXZ @0x007B02A6 29B: deque ctor 0x002F0BE0 on &g_Va00E03174, atexit(0x007B82C9).
void rva007B02A6()
{
	new (&g_Va00E03174) _STL::deque<BfmeWordValue4>(_STL::allocator<BfmeWordValue4>());
	atexit(rva007B82C9);
}

// ?rva007AE5DA@@YAXXZ @0x007AE5DA 29B: list<Coord3D> ctor 0x0073F451 on &g_Va00DFF144 (MapUtil's supply positions), atexit(0x007B7A87).
void rva007AE5DA()
{
	new (&g_Va00DFF144) _STL::list<Coord3D>(_STL::allocator<Coord3D>());
	atexit(rva007B7A87);
}

// ?rva007AE5F7@@YAXXZ @0x007AE5F7 29B: list<Coord3D> ctor 0x0073F451 on &g_Va00DFF148 (MapUtil's tech positions), atexit(0x007B7A91).
void rva007AE5F7()
{
	new (&g_Va00DFF148) _STL::list<Coord3D>(_STL::allocator<Coord3D>());
	atexit(rva007B7A91);
}
