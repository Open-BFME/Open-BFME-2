// cl: /MD
// Split from Rva007AC6DDGlobalInits.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// File-scope object initializers from the 0x007AC6xx..0x007B67xx initializer
// strip. Each is the compiler's dynamic-initializer shape: ecx = &storage,
// call the rowed default constructor (or init member), then atexit() the
// rowed 10-byte cleanup thunk that destroys the same storage (in
// Rva007B6880Thunks.cpp / Rva007B6A00AtexitThunks.cpp). Same shape as the
// matched 0x007B6760/0x007B6780 and 0x007B6830. The owning TUs are
// unrecovered, so each keeps an honest address name and the storage keeps the
// global its cleanup thunk already names. Retail bytes give every operand.
#include <stdlib.h>

inline void *operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
	class ios_base
	{
	public:
		class _Loc_init
		{
		public:
			_Loc_init();
		};
	};
}

struct BfmeUiResourceEntryState;
class MappedImageCache;

class Rva0057A4E7
{
public:
	Rva0057A4E7();
};

void __cdecl rva007B6E18();
void rva007AC747();


void __cdecl rva007B6ED6();
void rva007AC910();


void __cdecl rva007B7588();
void rva007AD50B();


extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
void __cdecl rva007B789C();
void rva007AE097();


extern unsigned g_00E01E41;
void __cdecl rva007B7C72();

// ?rva007AEC8E@@YAXXZ @0x007AEC8E 22B: ctor 0x0000F740 on &g_00E01E41, atexit(0x007B7C72).
void rva007AEC8E()
{
	new (&g_00E01E41) _STL::ios_base::_Loc_init;
	atexit(rva007B7C72);
}

void __cdecl rva007B89C1();
void rva007B1CDC();


void __cdecl rva007B9049();
void rva007B342C();


void __cdecl rva007B993D();
void rva007B4FDA();


void __cdecl rva007B9947();
void rva007B5000();


extern MappedImageCache Rva00A06858;
void __cdecl rva007B99B5();
void rva007B51EB();


void __cdecl rva007B9A37();
void rva007B53D4();


void __cdecl rva007B9C50();
void rva007B67A0();


void __cdecl rva007B6A50();
void rva007ABB80();


void __cdecl rva007B6EEA();
void rva007AC940();


void __cdecl rva007B6EF4();
void rva007AC956();


void __cdecl rva007B94C8();
void rva007B4100();


extern unsigned int g_Va00E06360[9];
void __cdecl rva007B94D2();

// ?rva007B4116@@YAXXZ @0x007B4116 22B: ctor 0x0057AA45 on &g_Va00E06360, atexit(0x007B94D2).
void rva007B4116()
{
	new (&g_Va00E06360) Rva0057A4E7;
	atexit(rva007B94D2);
}

// Atexit-only initializers: a file-scope object whose constructor is trivial
// but whose destructor is not compiles to just atexit(cleanup thunk).

void __cdecl Rva007B6890();
void rva007AB8C0();


void __cdecl rva007B6B73();
void rva007ABE93();


void __cdecl rva007B700A();
void rva007ACC9A();


void __cdecl rva007B7230();
void rva007ACE70();


void __cdecl rva007B781A();
void rva007ADFB2();


void __cdecl rva007B7824();
void rva007ADFBE();


void __cdecl rva007B7CD7();
void rva007AEDCB();


void __cdecl rva007B92A2();
void rva007B3A22();


void __cdecl rva007B981A();
void rva007B4C64();


void __cdecl rva007B9BA0();
void rva007B6190();


void __cdecl rva007B9BB0();
void rva007B6600();


void __cdecl rva007B9BD0();
void rva007B6630();


void __cdecl rva007B9BE0();
void rva007B6670();


void __cdecl rva007B9C00();
void rva007B6680();


// PointGroupClass::transformed_loc (VA 0x00DF709C, read and resized by
// 0x0017E920) is a VectorClass<Vector3> built empty by the rowed
// (int, const Vector3 *) constructor 0x000F0D2F and destroyed by the rowed
// cleanup 0x007B73C0. Only the declarations the call sites need are given.
class Vector3;
template <class T> class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
};
void rva007ACF00();
class PointGroupClass
{
	friend void rva007ACF00();
	static VectorClass<Vector3> transformed_loc;
};
void __cdecl Rva007B73C0();

// ?rva007ACF00@@YAXXZ @0x007ACF00 26B: VectorClass<Vector3>(0, 0) on
// PointGroupClass::transformed_loc, atexit(0x007B73C0).
void rva007ACF00()
{
	new (&PointGroupClass::transformed_loc) VectorClass<Vector3>(0, 0);
	atexit(Rva007B73C0);
}

// ?rva007AE7FB@@YAXXZ @0x007AE7FB 11B: the initializer after
// Rva007AE7EFStaticInstance.cpp's 0x007AE7EF in the same unit stores the
// address of WorldMapObjects' +4 word (VA 0x00DBDF70) into the map-object
// list holder at VA 0x00E00940, which Rva000ABD70Clear.cpp reads.
class Rva0030D346;
extern Rva0030D346 WorldMapObjects;
class BfmeMapObjectListHolder;
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
void rva007AE7FB();


// ?rva007AE614@@YAXXZ @0x007AE614 22B: TechAndSupplyImages ctor 0x003015E7 on
// TheSupplyAndTechImageLocations (VA 0x00DFF14C), atexit(0x007B7A9B), right
// after the two MapUtil position-list initializers 0x007AE5DA/0x007AE5F7.
class TechAndSupplyImages
{
public:
	TechAndSupplyImages();
};
extern TechAndSupplyImages TheSupplyAndTechImageLocations;
void __cdecl rva007B7A9B();
void rva007AE614();


// ?rva007B6800@@YAXXZ @0x007B6800 15B: Vector3Randomizer::Randomizer (VA
// 0x00E1D070, v3_rnd.cpp) built as Random3Class(0, 0) through the pinned
// ctor 0x006200B0 (ICF-folded with a hashtable iterator ctor); no cleanup.
class Random3Class
{
public:
	Random3Class(unsigned int seed1 = 0, unsigned int seed2 = 0);
};
void rva007B6800();
class Vector3Randomizer
{
	friend void rva007B6800();
protected:
	static Random3Class Randomizer;
};
void rva007B6800();


// ?rva007B3E9E@@YAXXZ @0x007B3E9E 11B and ?rva007B3EA9@@YAXXZ @0x007B3EA9 11B:
// a second unit's copies of the DefaultModuleKey<6>/DefaultModuleName<6>
// VALUE initializers (FXParticleSystemDefaults.cpp rows the first copies at
// 0x007AF475/0x007AF480): store the rowed GetValue() result into VALUE.
void rva007B3E9E();
void rva007B3EA9();
namespace FXParticleSystem
{
	template <int CATEGORY>
	struct DefaultModuleKey
	{
		friend void ::rva007B3E9E();
	public:
		static const char *const VALUE;
	private:
		static const char *GetValue();
	};
	template <int CATEGORY>
	struct DefaultModuleName
	{
		friend void ::rva007B3EA9();
	public:
		static const char *const VALUE;
	private:
		static const char *GetValue();
	};
}
void rva007B3E9E();

void rva007B3EA9();

