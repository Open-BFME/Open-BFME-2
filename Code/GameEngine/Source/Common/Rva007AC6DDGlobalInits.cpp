// cl: /MD
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
class Rva005F0152;

class TerrainFXShaderParameterSourceNamespace
{
public:
	TerrainFXShaderParameterSourceNamespace();
};

class VegetationFXShaderParameterSourceNamespace
{
public:
	VegetationFXShaderParameterSourceNamespace();
};

class Rva000FA83B
{
public:
	Rva000FA83B *init();
};

class Rva001F4B01
{
public:
	Rva001F4B01();
};

class Rva004E5610
{
public:
	Rva004E5610();
};


class Rva00502EC6
{
public:
	Rva00502EC6();
};

class Rva005E2237
{
public:
	Rva005E2237();
};

class Rva005E3DE8
{
public:
	Rva005E3DE8();
};

class Rva005F00FB
{
public:
	Rva005F00FB();
};

class Rva003B6831
{
public:
	Rva003B6831();
};

struct AptActionInterpreter
{
	AptActionInterpreter();
};

class Rva000FB87B
{
public:
	Rva000FB87B();
};

class Rva000FB8B6
{
public:
	Rva000FB8B6();
};

class Rva00579731
{
public:
	Rva00579731();
};

class Rva0057A4E7
{
public:
	Rva0057A4E7();
};

extern unsigned g_Va00DEBC64;
void __cdecl rva007B6DFA();


extern unsigned g_Va00DEBC98;
void __cdecl rva007B6E18();

// ?rva007AC747@@YAXXZ @0x007AC747 22B: ctor 0x000E6350 on &g_Va00DEBC98, atexit(0x007B6E18).
void rva007AC747()
{
	new (&g_Va00DEBC98) VegetationFXShaderParameterSourceNamespace;
	atexit(rva007B6E18);
}

extern unsigned g_Va00DEC0E0;
void __cdecl rva007B6ED6();

// ?rva007AC910@@YAXXZ @0x007AC910 22B: init 0x000FA83B on &g_Va00DEC0E0, atexit(0x007B6ED6).
void rva007AC910()
{
	((Rva000FA83B *)&g_Va00DEC0E0)->init();
	atexit(rva007B6ED6);
}

extern unsigned g_Va00DFDD0C;
void __cdecl rva007B7588();

// ?rva007AD50B@@YAXXZ @0x007AD50B 22B: ctor 0x001F4A40 on &g_Va00DFDD0C, atexit(0x007B7588).
void rva007AD50B()
{
	new (&g_Va00DFDD0C) Rva001F4B01;
	atexit(rva007B7588);
}

extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
void __cdecl rva007B789C();

// ?rva007AE097@@YAXXZ @0x007AE097 22B: ctor 0x004E5610 on &BfmeUiResourceEntryCollectorState, atexit(0x007B789C).
void rva007AE097()
{
	new (&BfmeUiResourceEntryCollectorState) Rva004E5610;
	atexit(rva007B789C);
}

extern unsigned g_00E01E41;
void __cdecl rva007B7C72();


void __cdecl rva007B89C1();

// ?rva007B1CDC@@YAXXZ @0x007B1CDC 22B: ctor 0x004ABDC3 on &BfmeLargeGroupAudioRegistry, atexit(0x007B89C1).
void rva007B1CDC();

extern unsigned g_Va00E04508;
void __cdecl rva007B9049();

// ?rva007B342C@@YAXXZ @0x007B342C 22B: ctor 0x00502EC6 on &g_Va00E04508, atexit(0x007B9049).
void rva007B342C()
{
	new (&g_Va00E04508) Rva00502EC6;
	atexit(rva007B9049);
}

extern unsigned g_Va00E0669C;
void __cdecl rva007B993D();

// ?rva007B4FDA@@YAXXZ @0x007B4FDA 22B: ctor 0x005E2237 on &g_Va00E0669C, atexit(0x007B993D).
void rva007B4FDA()
{
	new (&g_Va00E0669C) Rva005E2237;
	atexit(rva007B993D);
}

extern unsigned g_Va00E06710;
void __cdecl rva007B9947();

// ?rva007B5000@@YAXXZ @0x007B5000 22B: ctor 0x005E3D95 on &g_Va00E06710, atexit(0x007B9947).
void rva007B5000()
{
	new (&g_Va00E06710) Rva005E3DE8;
	atexit(rva007B9947);
}

extern Rva005F0152 Rva00A06858;
void __cdecl rva007B99B5();

// ?rva007B51EB@@YAXXZ @0x007B51EB 22B: ctor 0x005F005B on &Rva00A06858, atexit(0x007B99B5).
void rva007B51EB()
{
	new (&Rva00A06858) Rva005F00FB;
	atexit(rva007B99B5);
}

extern unsigned g_Va00E06E60;
void __cdecl rva007B9A37();

// ?rva007B53D4@@YAXXZ @0x007B53D4 22B: ctor 0x003B6831 on &g_Va00E06E60, atexit(0x007B9A37).
void rva007B53D4()
{
	new (&g_Va00E06E60) Rva003B6831;
	atexit(rva007B9A37);
}

// VA 0x00E182E0 is AptDate.cpp's ?g_aptDateInterpreter@@3UAptActionInterpreter@@A.
extern AptActionInterpreter g_aptDateInterpreter;
void __cdecl rva007B9C50();

// ?rva007B67A0@@YAXXZ @0x007B67A0 22B: ctor 0x006FE980 on &g_aptDateInterpreter (VA 0x00E182E0), atexit(0x007B9C50).
void rva007B67A0()
{
	new (&g_aptDateInterpreter) AptActionInterpreter;
	atexit(rva007B9C50);
}

extern unsigned g_Va00DDEF54;
void __cdecl rva007B6A50();

// ?rva007ABB80@@YAXXZ @0x007ABB80 22B: ctor 0x0000F740 on &g_Va00DDEF54, atexit(0x007B6A50).
void rva007ABB80()
{
	new (&g_Va00DDEF54) _STL::ios_base::_Loc_init;
	atexit(rva007B6A50);
}

extern unsigned g_Va00DEC140;
void __cdecl rva007B6EEA();

// ?rva007AC940@@YAXXZ @0x007AC940 22B: ctor 0x000FB87B on &g_Va00DEC140, atexit(0x007B6EEA).
void rva007AC940()
{
	new (&g_Va00DEC140) Rva000FB87B;
	atexit(rva007B6EEA);
}

extern unsigned g_Va00DEC174;
void __cdecl rva007B6EF4();

// ?rva007AC956@@YAXXZ @0x007AC956 22B: ctor 0x000FB8B6 on &g_Va00DEC174, atexit(0x007B6EF4).
void rva007AC956()
{
	new (&g_Va00DEC174) Rva000FB8B6;
	atexit(rva007B6EF4);
}

extern unsigned g_Va00E0631C;
void __cdecl rva007B94C8();

// ?rva007B4100@@YAXXZ @0x007B4100 22B: ctor 0x00579C52 on &g_Va00E0631C, atexit(0x007B94C8).
void rva007B4100()
{
	new (&g_Va00E0631C) Rva00579731;
	atexit(rva007B94C8);
}

extern unsigned g_Va00E06360;
void __cdecl rva007B94D2();


// Atexit-only initializers: a file-scope object whose constructor is trivial
// but whose destructor is not compiles to just atexit(cleanup thunk).

void __cdecl Rva007B6890();

// ?rva007AB8C0@@YAXXZ @0x007AB8C0 12B: atexit(0x007B6890).
void rva007AB8C0()
{
	atexit(Rva007B6890);
}

void __cdecl rva007B6B73();

// ?rva007ABE93@@YAXXZ @0x007ABE93 12B: atexit(0x007B6B73).
void rva007ABE93()
{
	atexit(rva007B6B73);
}

void __cdecl rva007B700A();

// ?rva007ACC9A@@YAXXZ @0x007ACC9A 12B: atexit(0x007B700A).
void rva007ACC9A()
{
	atexit(rva007B700A);
}

// 0x007ACE70 (12B, atexit of 0x007B7230) is meshmdl_sidehash.cpp's
// compiler-emitted _$E8, SideHash's dynamic initializer; rowed there.

void __cdecl rva007B781A();

// ?rva007ADFB2@@YAXXZ @0x007ADFB2 12B: atexit(0x007B781A).
void rva007ADFB2()
{
	atexit(rva007B781A);
}

void __cdecl rva007B7824();

// ?rva007ADFBE@@YAXXZ @0x007ADFBE 12B: atexit(0x007B7824).
void rva007ADFBE()
{
	atexit(rva007B7824);
}

void __cdecl rva007B7CD7();

// ?rva007AEDCB@@YAXXZ @0x007AEDCB 12B: atexit(0x007B7CD7).
void rva007AEDCB()
{
	atexit(rva007B7CD7);
}

void __cdecl rva007B92A2();

// ?rva007B3A22@@YAXXZ @0x007B3A22 12B: atexit(0x007B92A2).
void rva007B3A22()
{
	atexit(rva007B92A2);
}

void __cdecl rva007B981A();

// ?rva007B4C64@@YAXXZ @0x007B4C64 12B: atexit(0x007B981A).
void rva007B4C64()
{
	atexit(rva007B981A);
}

void __cdecl rva007B9BA0();

// ?rva007B6190@@YAXXZ @0x007B6190 12B: atexit(0x007B9BA0).
void rva007B6190()
{
	atexit(rva007B9BA0);
}

void __cdecl rva007B9BB0();

// ?rva007B6600@@YAXXZ @0x007B6600 12B: atexit(0x007B9BB0).
void rva007B6600()
{
	atexit(rva007B9BB0);
}

void __cdecl rva007B9BD0();

// ?rva007B6630@@YAXXZ @0x007B6630 12B: atexit(0x007B9BD0).
void rva007B6630()
{
	atexit(rva007B9BD0);
}

void __cdecl rva007B9BE0();

// ?rva007B6670@@YAXXZ @0x007B6670 12B: atexit(0x007B9BE0).
void rva007B6670()
{
	atexit(rva007B9BE0);
}

void __cdecl rva007B9C00();

// ?rva007B6680@@YAXXZ @0x007B6680 12B: atexit(0x007B9C00).
void rva007B6680()
{
	atexit(rva007B9C00);
}

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


// ?rva007AE7FB@@YAXXZ @0x007AE7FB 11B: the initializer after
// Rva007AE7EFStaticInstance.cpp's 0x007AE7EF in the same unit stores the
// address of WorldMapObjects' +4 word (VA 0x00DBDF70) into the map-object
// list holder at VA 0x00E00940, which Rva000ABD70Clear.cpp reads.
class Rva0030D346;
extern Rva0030D346 WorldMapObjects;
class BfmeMapObjectListHolder;
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;

void rva007AE7FB()
{
	BfmeTheMapObjectListHolder = (BfmeMapObjectListHolder *)((char *)&WorldMapObjects + 4);
}

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

void rva007AE614()
{
	new (&TheSupplyAndTechImageLocations) TechAndSupplyImages;
	atexit(rva007B7A9B);
}

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

void rva007B6800()
{
	new (&Vector3Randomizer::Randomizer) Random3Class(0, 0);
}

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

void rva007B3E9E()
{
	*const_cast<const char **>(&FXParticleSystem::DefaultModuleKey<6>::VALUE) = FXParticleSystem::DefaultModuleKey<6>::GetValue();
}

void rva007B3EA9()
{
	*const_cast<const char **>(&FXParticleSystem::DefaultModuleName<6>::VALUE) = FXParticleSystem::DefaultModuleName<6>::GetValue();
}
