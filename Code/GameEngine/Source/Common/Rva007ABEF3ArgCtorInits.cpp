// cl: /MD
//
// Static-initializer strip: file-scope objects built by an already-rowed
// constructor that takes arguments, some followed by atexit() of the
// already-rowed cleanup thunk. The callee row names the class and argument
// list each call spells; the owning TUs are unrecovered, so each initializer
// keeps an honest address name and each object an address-named extern.

#include "../../Include/Common/Rva00041004Lock.h"

extern "C" int __cdecl atexit(void (__cdecl *)(void));

class Vector3;
class Vector4;

class Curve3DClass
{
public:
	class KeyClass;
};

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

template <int N> class BitFlags
{
public:
	enum BogusInitType { kInit };
	BitFlags(BogusInitType, int a);
	BitFlags(BogusInitType, int a, int b);
	BitFlags(BogusInitType, int a, int b, int c, int d);
};

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

class Dict
{
public:
	Dict(int numPairsToPreAllocate);
};

class Rva00559A11
{
public:
	Rva00559A11 *rva00559A11(int a);
};

class Rva00559AC1
{
public:
	Rva00559AC1 *rva00559A76(int a);
};

void __cdecl rva007B6B91();
void __cdecl rva007B6E54();
void __cdecl rva007B6E5E();
void __cdecl rva007B7280();
void __cdecl rva007B72C0();
void __cdecl rva007B7400();
void __cdecl rva007B70AB();
void __cdecl rva007B7B14();

extern unsigned g_Va00DB424C;
extern unsigned g_Va00DEBE0C;
extern unsigned g_Va00DEBE24;
extern unsigned g_Va00DF94D0;
extern unsigned g_Va00DF94B0;
extern unsigned g_Va00DF708C;
extern unsigned g_Va00E01E08;
extern unsigned g_Va00E02D64;
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
Rva00559D0CRankWeights g_00E05FCC;
Rva00559D0CRankWeights g_00E06000;
extern unsigned g_Va00E06034;
// g_rva005C1A8DDefault is the VA 0x00E06060 table: the getter at retail RVA
// 0x005C1A8D returns it as the default ("Default") when a slot has no override,
// and its two readers take its address or return it as a char*. An array and a
// pointer mangle alike in MSVC (??@@3PADA either way), so the one spelling
// serves the `char *` reader, the `char []` reader and this constructor.
char *g_rva005C1A8DDefault = 0;
extern unsigned g_Va00E0660C;
extern unsigned g_Va00E06610;
extern unsigned g_Va00E06614;
extern unsigned g_Va00E06618;
extern unsigned g_Va00E0661C;
extern unsigned g_Va00DF2984;
extern unsigned g_Va00E00944;

typedef DynamicVectorClass<Curve3DClass::KeyClass> KeyVector;
typedef VectorClass<Vector3> Vector3Vector;
typedef VectorClass<Vector4> Vector4Vector;
typedef BitFlags<11> Mask11;

struct Rva007ABEF3ArgCtorInits
{
	static void rva007ABEF3();
	static void rva007AC818();
	static void rva007AC832();
	static void rva007ACE90();
	static void rva007ACEB0();
	static void rva007ACF20();
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
	static void rva007AE806();
};

// 0x007ABEF3 (26B): 0x0006EFC8(0, -1) on VA 0x00DB424C, atexit(0x007B6B91 -> 0x001EAF7B)
void Rva007ABEF3ArgCtorInits::rva007ABEF3()
{
	( (Rva0006EFC8 *)&g_Va00DB424C )->rva0006EFC8( 0, -1 );
	atexit( rva007B6B91 );
}

// 0x007AC818 (26B): DynamicVectorClass<Curve3DClass::KeyClass>(0, 0) on VA 0x00DEBE0C, atexit(0x007B6E54 -> its dtor 0x000F1D19)
void Rva007ABEF3ArgCtorInits::rva007AC818()
{
	( (KeyVector *)&g_Va00DEBE0C )->KeyVector::DynamicVectorClass( 0, 0 );
	atexit( rva007B6E54 );
}

// 0x007AC832 (26B): DynamicVectorClass<Curve3DClass::KeyClass>(0, 0) on VA 0x00DEBE24, atexit(0x007B6E5E -> its dtor 0x000F1D19)
void Rva007ABEF3ArgCtorInits::rva007AC832()
{
	( (KeyVector *)&g_Va00DEBE24 )->KeyVector::DynamicVectorClass( 0, 0 );
	atexit( rva007B6E5E );
}

// 0x007ACE90 (26B): VectorClass<Vector3>(0, 0) on VA 0x00DF94D0, atexit(0x007B7280)
void Rva007ABEF3ArgCtorInits::rva007ACE90()
{
	( (Vector3Vector *)&g_Va00DF94D0 )->Vector3Vector::VectorClass( 0, 0 );
	atexit( rva007B7280 );
}

// 0x007ACEB0 (26B): VectorClass<Vector4>(0, 0) on VA 0x00DF94B0, atexit(0x007B72C0)
void Rva007ABEF3ArgCtorInits::rva007ACEB0()
{
	( (Vector4Vector *)&g_Va00DF94B0 )->Vector4Vector::VectorClass( 0, 0 );
	atexit( rva007B72C0 );
}

// 0x007ACF20 (26B): VectorClass<Vector3>(0, 0) on VA 0x00DF708C, atexit(0x007B7400)
void Rva007ABEF3ArgCtorInits::rva007ACF20()
{
	( (Vector3Vector *)&g_Va00DF708C )->Vector3Vector::VectorClass( 0, 0 );
	atexit( rva007B7400 );
}

// 0x007AEBB7 (21B): Rva00346BC0(0, 5, 0x17, 0x3C, 3) on VA 0x00E01E08
void Rva007ABEF3ArgCtorInits::rva007AEBB7()
{
	( (Rva00346BC0 *)&g_Va00E01E08 )->Rva00346BC0::Rva00346BC0( 0, 5, 0x17, 0x3C, 3 );
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
	( (Rva00559AC1 *)&g_Va00E06034 )->rva00559A76( 1 );
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

// 0x007AE806 (24B): Dict(0) on VA 0x00E00944, atexit(0x007B7B14 -> Dict releaseData)
void Rva007ABEF3ArgCtorInits::rva007AE806()
{
	( (Dict *)&g_Va00E00944 )->Dict::Dict( 0 );
	atexit( rva007B7B14 );
}
