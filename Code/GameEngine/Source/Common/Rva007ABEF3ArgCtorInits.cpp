// cl: /MD
//
// Static-initializer strip: file-scope objects built by an already-rowed
// constructor that takes arguments, some followed by atexit() of the
// already-rowed cleanup thunk. The callee row names the class and argument
// list each call spells; the owning TUs are unrecovered, so each initializer
// keeps an honest address name and each object an address-named extern.

#include "../../Include/Common/Rva00041004Lock.h"
#include "../../Include/Common/Rva002E8548Pool.h"

#include <stdlib.h>

class Vector3;
class Vector4;

template <class T> class VectorClass
{
public:
	VectorClass(int size, const T *array);
};

template <class T> class DynamicVectorClass
{
public:
	DynamicVectorClass(unsigned size, const T *array);
};

#include "../../Include/Common/BitFlagsTemplate.h"

class Rva0006EFC8
{
public:
	bool rva0006EFC8(int a, int b);
};

class Rva00346BC0
{
public:
	Rva00346BC0(unsigned a, unsigned b, unsigned c, unsigned d, unsigned e);
};

struct BfmePod4;

template <class T> class SimpleDynVecClass
{
public:
	SimpleDynVecClass(int size);
};

#include "../../Include/Common/Dict.h"

class Rva00559A11
{
public:
	Rva00559A11 *rva00559A11(int a);
};

class Rva00559AC1
{
public:
	Rva00559AC1 *rva00559A76(int a);
private:
	int m_vals[11];	// RankPointValue.cpp's layout: -1, 0, then the rank thresholds
};

void __cdecl rva007B6B91();
void __cdecl rva007B6E54();
void __cdecl rva007B6E5E();
void __cdecl rva007B7280();
void __cdecl rva007B72C0();
void __cdecl rva007B70AB();
void __cdecl rva007B6C2A();
void __cdecl rva007B75C4();
void __cdecl rva007B7A41();
void __cdecl rva007B7A37();
extern Rva002E8548 g_IntKeyedTreeNodePool; // defined in Rva007B6880Thunks.cpp (0x00DBD4B0)

extern Rva0006EFC8 g_BfmeSceneNodePool; // owned by Rva0006EFC8Grow.cpp
unsigned g_Va00DEBE0C;	// retail RVA 0x009EBE0C (.bss), defined here
unsigned g_Va00DEBE24;	// retail RVA 0x009EBE24 (.bss), defined here
// VA 0x00E01E08: the 16-byte Rva00346BC0 record rva007AEBB7 constructs at
// static-init time; defined here, its initializer's unit, so the burning-death
// state (AIBurningDeathStateUpdate.cpp) that passes it on resolves it.
// Retail's object extends 16 bytes; the mangled name stays the one its other users declare.
extern "C" { unsigned int __identifier("?g_Va00E01E08@@3IA")[4]; }
unsigned g_Va00E02D64;	// retail RVA 0x00A02D64 (.bss), defined here
// The two GameSpy rank-weight tables this unit's arg-ctor bodies build and the
// default rank table beside them. Retail's storage for all three is the zero
// tail of .data, so the file holds zeros and these constructors fill it in at
// static-init time.
//
// The class name is the ledger's canonical global spelling for VA 0x00E05FCC
// and VA 0x00E06000 (reverse/data_ledger.csv, 52 bytes each), which the two
// stats units already reference; the layout is the one Rva00559A11.cpp proves
// for this very class (int m_00 = -1, int m_04, int m_vals[9], float m_2C,
// float m_30 -- 0x34 = 52 bytes, and the constructor body below is
// Rva00559A11::rva00559A11). Six units spelled these two objects five
// different ways; they are now one spelling so the relocations place.
class Rva00559D0CRankWeights
{
public:
	int m_00;
	int m_04;
	int m_vals[9];
	float m_2C;
	float m_30;
};
// Not defined here: Rva005B8116Stats.cpp already defines both of them (the unit that
// reads their weights), and a second definition of the same symbol is a duplicate.
extern Rva00559D0CRankWeights g_00E05FCC;
extern Rva00559D0CRankWeights g_00E06000;
// VA 0x00E06034: the strategic rank table, which Rva005C18F0Ctor.cpp defines (44 bytes).
extern Rva00559AC1 g_00E06034;
// g_rva005C1A8DDefault is the VA 0x00E06060 rank-point table, 44 bytes (retail's
// extent in the data ledger): an Rva00559AC1 (RankPointValue.cpp, int m_vals[11]),
// built by the initializer 0x007B3DDF through 0x00559A76 (-1, 0, then 5 .. 1500).
// AptSkirmishStats::GetRankPointValue (0x005C1A8D) returns its address as the
// default, and AptLoadScreen::init (0x0043A5F6) looks rank images up in it. Declared
// as the class so its storage is the object's size: a 4-byte `char *` here let the
// initializer write 40 bytes into the next object in the image (P132).
Rva00559AC1 g_rva005C1A8DDefault;
unsigned g_Va00E0660C;	// retail RVA 0x00A0660C (.bss), defined here
unsigned g_Va00E06610;	// retail RVA 0x00A06610 (.bss), defined here
unsigned g_Va00E06614;	// retail RVA 0x00A06614 (.bss), defined here
unsigned g_Va00E06618;	// retail RVA 0x00A06618 (.bss), defined here
unsigned g_Va00E0661C;	// retail RVA 0x00A0661C (.bss), defined here
unsigned int g_Va00DF2984[9];	// retail RVA 0x009F2984 (.bss), defined here
// Owned by W3DFontCharsCache.cpp; the initializer uses the existing ABI view.
class FontCharsClass;
extern SimpleDynVecClass<FontCharsClass *> BfmeFontCharsCache;

typedef DynamicVectorClass<Vector3> KeyVector;
typedef VectorClass<Vector3> Vector3Vector;
typedef VectorClass<Vector4> Vector4Vector;
// VA 0x00DF94D0 / 0x00DF94B0 are pointgr.cpp's private
// ?compressed_loc@PointGroupClass@@0V?$VectorClass@VVector3@@@@A and
// ?compressed_diffuse@PointGroupClass@@0V?$VectorClass@VVector4@@@@A, reached
// through a TU-scoped friend view instead of second datums at their addresses.
class PointGroupClass
{
	friend struct Rva007ABEF3ArgCtorInits;
	static Vector3Vector compressed_loc;
	static Vector4Vector compressed_diffuse;
};
typedef BitFlags<11> Mask11;
typedef SimpleDynVecClass<BfmePod4> Pod4Vector;

struct Rva007ABEF3ArgCtorInits
{
	static void rva007ABEF3();
	static void rva007AC818();
	static void rva007AC832();
	static void rva007ACE90();
	static void rva007ACEB0();
	static void rva007AEBB7();
	static void rva007AF7ED();
	static void rva007B3DB8();
	static void rva007B3DC5();
	static void rva007B3DD2();
	static void rva007B3DDF();
	static void rva007B4962();
	static void rva007B4971();
	static void rva007B4980();
	static void rva007B498F();
	static void rva007B499E();
	static void rva007ACDAC();
	static void rva007AC0FA();
	static void rva007AD5A9();
	static void rva007AE52D();
	static void rva007AE547();
};

// 0x007ABEF3 (26B): 0x0006EFC8(0, -1) on VA 0x00DB424C, atexit(0x007B6B91 -> 0x001EAF7B)
void Rva007ABEF3ArgCtorInits::rva007ABEF3()
{
	g_BfmeSceneNodePool.rva0006EFC8( 0, -1 );
	atexit( rva007B6B91 );
}

// 0x007AC818 (26B): DynamicVectorClass<Vector3>(0, 0) on VA 0x00DEBE0C, atexit(0x007B6E54 -> its dtor 0x000F1D19)
void Rva007ABEF3ArgCtorInits::rva007AC818()
{
	( (KeyVector *)&g_Va00DEBE0C )->KeyVector::DynamicVectorClass( 0, 0 );
	atexit( rva007B6E54 );
}

// 0x007AC832 (26B): DynamicVectorClass<Vector3>(0, 0) on VA 0x00DEBE24, atexit(0x007B6E5E -> its dtor 0x000F1D19)
void Rva007ABEF3ArgCtorInits::rva007AC832()
{
	( (KeyVector *)&g_Va00DEBE24 )->KeyVector::DynamicVectorClass( 0, 0 );
	atexit( rva007B6E5E );
}

// 0x007ACE90 (26B): VectorClass<Vector3>(0, 0) on VA 0x00DF94D0, atexit(0x007B7280)
void Rva007ABEF3ArgCtorInits::rva007ACE90()
{
	( &PointGroupClass::compressed_loc )->Vector3Vector::VectorClass( 0, 0 );
	atexit( rva007B7280 );
}

// 0x007ACEB0 (26B): VectorClass<Vector4>(0, 0) on VA 0x00DF94B0, atexit(0x007B72C0)
void Rva007ABEF3ArgCtorInits::rva007ACEB0()
{
	( &PointGroupClass::compressed_diffuse )->Vector4Vector::VectorClass( 0, 0 );
	atexit( rva007B72C0 );
}

// 0x007AEBB7 (21B): Rva00346BC0(0, 5, 0x17, 0x3C, 3) on VA 0x00E01E08
void Rva007ABEF3ArgCtorInits::rva007AEBB7()
{
	( (Rva00346BC0 *)__identifier("?g_Va00E01E08@@3IA") )->Rva00346BC0::Rva00346BC0( 0, 5, 0x17, 0x3C, 3 );
}

// 0x007AF7ED (17B): BitFlags<11>(kInit, 0, 4) on VA 0x00E02D64
void Rva007ABEF3ArgCtorInits::rva007AF7ED()
{
	( (Mask11 *)&g_Va00E02D64 )->Mask11::BitFlags( Mask11::kInit, 0, 4 );
}

// 0x007B3DB8 (13B): 0x00559A11(1) on VA 0x00E05FCC
void Rva007ABEF3ArgCtorInits::rva007B3DB8()
{
	( (Rva00559A11 *)&g_00E05FCC )->rva00559A11( 1 );
}

// 0x007B3DC5 (13B): 0x00559A11(0) on VA 0x00E06000
void Rva007ABEF3ArgCtorInits::rva007B3DC5()
{
	( (Rva00559A11 *)&g_00E06000 )->rva00559A11( 0 );
}

// 0x007B3DD2 (13B): 0x00559A76(1) on VA 0x00E06034
void Rva007ABEF3ArgCtorInits::rva007B3DD2()
{
	( (Rva00559AC1 *)&g_00E06034 )->rva00559A76( 1 );
}

// 0x007B3DDF (13B): 0x00559A76(0) on VA 0x00E06060, i.e. g_rva005C1A8DDefault
void Rva007ABEF3ArgCtorInits::rva007B3DDF()
{
	( (Rva00559AC1 *)&g_rva005C1A8DDefault )->rva00559A76( 0 );
}

// 0x007B4962 (15B): BitFlags<11>(kInit, 0) on VA 0x00E0660C
void Rva007ABEF3ArgCtorInits::rva007B4962()
{
	( (Mask11 *)&g_Va00E0660C )->Mask11::BitFlags( Mask11::kInit, 0 );
}

// 0x007B4971 (15B): BitFlags<11>(kInit, 1) on VA 0x00E06610
void Rva007ABEF3ArgCtorInits::rva007B4971()
{
	( (Mask11 *)&g_Va00E06610 )->Mask11::BitFlags( Mask11::kInit, 1 );
}

// 0x007B4980 (15B): BitFlags<11>(kInit, 2) on VA 0x00E06614
void Rva007ABEF3ArgCtorInits::rva007B4980()
{
	( (Mask11 *)&g_Va00E06614 )->Mask11::BitFlags( Mask11::kInit, 2 );
}

// 0x007B498F (15B): BitFlags<11>(kInit, 3) on VA 0x00E06618
void Rva007ABEF3ArgCtorInits::rva007B498F()
{
	( (Mask11 *)&g_Va00E06618 )->Mask11::BitFlags( Mask11::kInit, 3 );
}

// 0x007B499E (21B): BitFlags<11>(kInit, 0, 1, 2, 3) on VA 0x00E0661C
void Rva007ABEF3ArgCtorInits::rva007B499E()
{
	( (Mask11 *)&g_Va00E0661C )->Mask11::BitFlags( Mask11::kInit, 0, 1, 2, 3 );
}

// 0x007ACDAC (24B): Rva00041004(1) on VA 0x00DF2984, atexit(0x007B70AB -> its dtor)
void Rva007ABEF3ArgCtorInits::rva007ACDAC()
{
	( (Rva00041004 *)&g_Va00DF2984 )->Rva00041004::Rva00041004( 1 );
	atexit( rva007B70AB );
}

// 0x007AC0FA (24B): SimpleDynVecClass<BfmePod4>(0) on VA 0x00DE2084, atexit(0x007B6C2A -> its dtor 0x00090088)
void Rva007ABEF3ArgCtorInits::rva007AC0FA()
{
	( (Pod4Vector *)&BfmeFontCharsCache )->Pod4Vector::SimpleDynVecClass( 0 );
	atexit( rva007B6C2A );
}

// 0x007AD5A9 (26B): pool grow 0x002E8548(0, -1) on VA 0x00DB9440, atexit(0x007B75C4 -> 0x001EAF7B)
void Rva007ABEF3ArgCtorInits::rva007AD5A9()
{
	g_Va00DB9440.rva002E8548( 0, -1 );
	atexit( rva007B75C4 );
}

// 0x007AE52D (26B): pool grow 0x002E8548(0, -1) on VA 0x00DBD4B0, atexit(0x007B7A41 -> 0x001EAF7B)
void Rva007ABEF3ArgCtorInits::rva007AE52D()
{
	g_IntKeyedTreeNodePool.rva002E8548( 0, -1 );
	atexit( rva007B7A41 );
}

// 0x007AE547 (26B): pool grow 0x002E8548(0, -1) on VA 0x00DBD4C8, atexit(0x007B7A37 -> 0x001EAF7B)
void Rva007ABEF3ArgCtorInits::rva007AE547()
{
	g_Va00DBD4C8.rva002E8548( 0, -1 );
	atexit( rva007B7A37 );
}
