// cl: /O1 /MD
// Dynamic initializers of three file-scope screen filter objects, each
// registered for destruction with atexit. Target evidence: game.dat's __xc_a
// table points at 0x007AC9B0, 0x007AC9C6 and 0x007AC9F6 (0x009A2F24,
// 0x009A2F28, 0x009A2F38); each
// loads the object's address into ecx, calls its rowed constructor and
// registers the cleanup thunk that runs on the same global:
//   0x007AC9B0: base filter ??0Rva000FC63DFilter (0x000FC946) on 0x00DEC1CC,
//               cleanup rva007B6F08 (texture release dtor 0x000FC5AA);
//   0x007AC9C6: DOT3 filter ??0Rva000FCF54Filter (0x000FD4A5) on 0x00DEC1DC,
//               cleanup rva007B6F12 (the same dtor);
//   0x007AC9F6: ??0Rva000FD58A (0x000FD58A, vftable 0x00BCF410) on
//               0x00DEC1F0, cleanup 0x007B6F27, a lone `ret` (empty dtor).
// The owning TU and the objects' names are not established; the RVA names
// stand in for them, and the objects keep their ledger globals.

#include <stdlib.h>

class Rva000FC63DFilter
{
public:
	Rva000FC63DFilter();
};

class Rva000FCF54Filter
{
public:
	Rva000FCF54Filter();
};

class Rva000FD58A
{
public:
	Rva000FD58A();
};

void __cdecl rva007B6F08();
void __cdecl rva007B6F12();

extern unsigned g_Va00DEC1CC;
extern unsigned g_Va00DEC1DC;

// g_Va00DEC1F0: the 0x1C-byte Rva000FD58A object the third initializer
// builds (zero-filled .bss in retail).
extern unsigned g_Va00DEC1F0[7];
unsigned g_Va00DEC1F0[7];

// ?rva007B6F27@@YAXXZ @ 0x007B6F27 (1B): the cleanup the third initializer
// registers; the object's destructor leaves nothing to run.
void __cdecl rva007B6F27()
{
}

struct Rva007AC9B0FilterInits
{
	static void __cdecl initBaseFilter();
	static void __cdecl initDot3Filter();
	static void __cdecl rva007AC9F6();
};

void __cdecl Rva007AC9B0FilterInits::initBaseFilter()
{
	( (Rva000FC63DFilter *)&g_Va00DEC1CC )->Rva000FC63DFilter::Rva000FC63DFilter();
	atexit( rva007B6F08 );
}

void __cdecl Rva007AC9B0FilterInits::initDot3Filter()
{
	( (Rva000FCF54Filter *)&g_Va00DEC1DC )->Rva000FCF54Filter::Rva000FCF54Filter();
	atexit( rva007B6F12 );
}

void __cdecl Rva007AC9B0FilterInits::rva007AC9F6()
{
	( (Rva000FD58A *)g_Va00DEC1F0 )->Rva000FD58A::Rva000FD58A();
	atexit( rva007B6F27 );
}
