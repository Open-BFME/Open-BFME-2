// cl: /DNDEBUG /MD /GX
//
// STLport vector destructors, one per element type, with the shape of the rowed
// ??1?$vector@UPrereqUnitRec@ProductionPrerequisite@@... at 0x002D040C (63 bytes:
// destroy [start, finish) through the element range destructor, then the base
// frees the storage). Found by searching .text for that shape with call
// displacements and the EH handler record masked. Each copy calls __EH_prolog,
// one rowed range destructor and free (0x00030830). Copies of different
// element types can share an ICF-folded range destructor, so the vector itself
// is not identified and each keeps its own address.

extern "C" void __cdecl free(void *block);

namespace _STL
{
template <class I> void __cdecl _Destroy(I first, I last);
}

template <class E> struct RvaVectorFamilyBase
{
	E *m_start;
	E *m_finish;
	E *m_endOfStorage;
	~RvaVectorFamilyBase()
	{
		if (m_start)
			free(m_start);
	}
};

class Rva002DFC30;

// ??1Rva000C0417@@QAE@XZ @0x000C0417 63B -> ??$_Destroy@PAVRva002DFC30@@@_STL@@YAXPAVRva002DFC30@@0@Z
struct Rva000C0417 : RvaVectorFamilyBase<Rva002DFC30>
{
	~Rva000C0417();
};

Rva000C0417::~Rva000C0417()
{
	_STL::_Destroy(m_start, m_finish);
}

struct RvaPair0032C0CA;

void __cdecl Rva0032C0CADestroyPairs(RvaPair0032C0CA *, RvaPair0032C0CA *);

// ??1Rva000C0456@@QAE@XZ @0x000C0456 63B -> ?Rva0032C0CADestroyPairs@@YAXPAURvaPair0032C0CA@@0@Z
struct Rva000C0456 : RvaVectorFamilyBase<RvaPair0032C0CA>
{
	~Rva000C0456();
};

Rva000C0456::~Rva000C0456()
{
	Rva0032C0CADestroyPairs(m_start, m_finish);
}

class CameraMarker;

// ??1Rva000C0495@@QAE@XZ @0x000C0495 63B -> ??$_Destroy@PAVCameraMarker@@@_STL@@YAXPAVCameraMarker@@0@Z
struct Rva000C0495 : RvaVectorFamilyBase<CameraMarker>
{
	~Rva000C0495();
};

Rva000C0495::~Rva000C0495()
{
	_STL::_Destroy(m_start, m_finish);
}

void __cdecl Rva00405337Clear(void *, void *);

// ??1Rva000C04D4@@QAE@XZ @0x000C04D4 63B -> ?Rva00405337Clear@@YAXPAX0@Z
struct Rva000C04D4 : RvaVectorFamilyBase<void>
{
	~Rva000C04D4();
};

Rva000C04D4::~Rva000C04D4()
{
	Rva00405337Clear(m_start, m_finish);
}

struct RvaPair000BDCEF;

void __cdecl Rva000BDCEFDestroy(RvaPair000BDCEF *, RvaPair000BDCEF *);

// ??1Rva000C055C@@QAE@XZ @0x000C055C 63B -> ?Rva000BDCEFDestroy@@YAXPAURvaPair000BDCEF@@0@Z
struct Rva000C055C : RvaVectorFamilyBase<RvaPair000BDCEF>
{
	~Rva000C055C();
};

Rva000C055C::~Rva000C055C()
{
	Rva000BDCEFDestroy(m_start, m_finish);
}

class Rva000B9AAA;

void __cdecl Rva000BDD08Destroy(Rva000B9AAA *, Rva000B9AAA *);

// ??1Rva000C1BE1@@QAE@XZ @0x000C1BE1 63B -> ?Rva000BDD08Destroy@@YAXPAVRva000B9AAA@@0@Z
struct Rva000C1BE1 : RvaVectorFamilyBase<Rva000B9AAA>
{
	~Rva000C1BE1();
};

Rva000C1BE1::~Rva000C1BE1()
{
	Rva000BDD08Destroy(m_start, m_finish);
}

struct Rva0052BF33Elem;

void __cdecl Rva005A6EDADestroyRange(Rva0052BF33Elem *, Rva0052BF33Elem *);

// ??1Rva001501CA@@QAE@XZ @0x001501CA 63B -> ?Rva005A6EDADestroyRange@@YAXPAURva0052BF33Elem@@0@Z
struct Rva001501CA : RvaVectorFamilyBase<Rva0052BF33Elem>
{
	~Rva001501CA();
};

Rva001501CA::~Rva001501CA()
{
	Rva005A6EDADestroyRange(m_start, m_finish);
}

class Rva0014F3E7;

void __cdecl Rva0014F8AEDestroy(Rva0014F3E7 *, Rva0014F3E7 *);

// ??1Rva00150209@@QAE@XZ @0x00150209 63B -> ?Rva0014F8AEDestroy@@YAXPAVRva0014F3E7@@0@Z
struct Rva00150209 : RvaVectorFamilyBase<Rva0014F3E7>
{
	~Rva00150209();
};

Rva00150209::~Rva00150209()
{
	Rva0014F8AEDestroy(m_start, m_finish);
}

struct BfmeStringRecord002199C8;

// ??1Rva0021DA18@@QAE@XZ @0x0021DA18 63B -> ??$_Destroy@PAUBfmeStringRecord002199C8@@@_STL@@YAXPAUBfmeStringRecord002199C8@@0@Z
struct Rva0021DA18 : RvaVectorFamilyBase<BfmeStringRecord002199C8>
{
	~Rva0021DA18();
};

Rva0021DA18::~Rva0021DA18()
{
	_STL::_Destroy(m_start, m_finish);
}

struct BfmeStringRecord00219A68;

// ??1Rva0021DA57@@QAE@XZ @0x0021DA57 63B -> ??$_Destroy@PAUBfmeStringRecord00219A68@@@_STL@@YAXPAUBfmeStringRecord00219A68@@0@Z
struct Rva0021DA57 : RvaVectorFamilyBase<BfmeStringRecord00219A68>
{
	~Rva0021DA57();
};

Rva0021DA57::~Rva0021DA57()
{
	_STL::_Destroy(m_start, m_finish);
}

// ??1Rva0021DB35@@QAE@XZ @0x0021DB35 63B -> ?Rva0032C0CADestroyPairs@@YAXPAURvaPair0032C0CA@@0@Z
struct Rva0021DB35 : RvaVectorFamilyBase<RvaPair0032C0CA>
{
	~Rva0021DB35();
};

Rva0021DB35::~Rva0021DB35()
{
	Rva0032C0CADestroyPairs(m_start, m_finish);
}

struct Rva0052BF9BElem;

void __cdecl Rva0022C8E3DestroyRange(Rva0052BF9BElem *, Rva0052BF9BElem *);

// ??1Rva0022CAC4@@QAE@XZ @0x0022CAC4 63B -> ?Rva0022C8E3DestroyRange@@YAXPAURva0052BF9BElem@@0@Z
struct Rva0022CAC4 : RvaVectorFamilyBase<Rva0052BF9BElem>
{
	~Rva0022CAC4();
};

Rva0022CAC4::~Rva0022CAC4()
{
	Rva0022C8E3DestroyRange(m_start, m_finish);
}

struct OpaqueRefElement4;

// ??1Rva00239E25@@QAE@XZ @0x00239E25 63B -> ??$_Destroy@PAUOpaqueRefElement4@@@_STL@@YAXPAUOpaqueRefElement4@@0@Z
struct Rva00239E25 : RvaVectorFamilyBase<OpaqueRefElement4>
{
	~Rva00239E25();
};

Rva00239E25::~Rva00239E25()
{
	_STL::_Destroy(m_start, m_finish);
}

struct BfmeStringRecord005DDD40;

// ??1Rva00260826@@QAE@XZ @0x00260826 63B -> ??$_Destroy@PAUBfmeStringRecord005DDD40@@@_STL@@YAXPAUBfmeStringRecord005DDD40@@0@Z
struct Rva00260826 : RvaVectorFamilyBase<BfmeStringRecord005DDD40>
{
	~Rva00260826();
};

Rva00260826::~Rva00260826()
{
	_STL::_Destroy(m_start, m_finish);
}

// ??1Rva00317E7C@@QAE@XZ @0x00317E7C 63B -> ?Rva0032C0CADestroyPairs@@YAXPAURvaPair0032C0CA@@0@Z
struct Rva00317E7C : RvaVectorFamilyBase<RvaPair0032C0CA>
{
	~Rva00317E7C();
};

Rva00317E7C::~Rva00317E7C()
{
	Rva0032C0CADestroyPairs(m_start, m_finish);
}

class Rva0032A3A9Element;

// ??1Rva0032BE80@@QAE@XZ @0x0032BE80 63B -> ??$_Destroy@PAVRva0032A3A9Element@@@_STL@@YAXPAVRva0032A3A9Element@@0@Z
struct Rva0032BE80 : RvaVectorFamilyBase<Rva0032A3A9Element>
{
	~Rva0032BE80();
};

Rva0032BE80::~Rva0032BE80()
{
	_STL::_Destroy(m_start, m_finish);
}

class Rva00329D0E;

void __cdecl Rva0032AF56Destroy(Rva00329D0E *, Rva00329D0E *);

// ??1Rva0032C3A3@@QAE@XZ @0x0032C3A3 63B -> ?Rva0032AF56Destroy@@YAXPAVRva00329D0E@@0@Z
struct Rva0032C3A3 : RvaVectorFamilyBase<Rva00329D0E>
{
	~Rva0032C3A3();
};

Rva0032C3A3::~Rva0032C3A3()
{
	Rva0032AF56Destroy(m_start, m_finish);
}

// ??1Rva0032CA4E@@QAE@XZ @0x0032CA4E 63B -> ?Rva0032C0CADestroyPairs@@YAXPAURvaPair0032C0CA@@0@Z
struct Rva0032CA4E : RvaVectorFamilyBase<RvaPair0032C0CA>
{
	~Rva0032CA4E();
};

Rva0032CA4E::~Rva0032CA4E()
{
	Rva0032C0CADestroyPairs(m_start, m_finish);
}

// ??1Rva003321D8@@QAE@XZ @0x003321D8 63B -> ??$_Destroy@PAVRva002DFC30@@@_STL@@YAXPAVRva002DFC30@@0@Z
struct Rva003321D8 : RvaVectorFamilyBase<Rva002DFC30>
{
	~Rva003321D8();
};

Rva003321D8::~Rva003321D8()
{
	_STL::_Destroy(m_start, m_finish);
}

// ??1Rva00381AE0@@QAE@XZ @0x00381AE0 63B -> ??$_Destroy@PAUBfmeStringRecord005DDD40@@@_STL@@YAXPAUBfmeStringRecord005DDD40@@0@Z
struct Rva00381AE0 : RvaVectorFamilyBase<BfmeStringRecord005DDD40>
{
	~Rva00381AE0();
};

Rva00381AE0::~Rva00381AE0()
{
	_STL::_Destroy(m_start, m_finish);
}

// ??1Rva0039C151@@QAE@XZ @0x0039C151 63B -> ?Rva0022C8E3DestroyRange@@YAXPAURva0052BF9BElem@@0@Z
struct Rva0039C151 : RvaVectorFamilyBase<Rva0052BF9BElem>
{
	~Rva0039C151();
};

Rva0039C151::~Rva0039C151()
{
	Rva0022C8E3DestroyRange(m_start, m_finish);
}

class LivingWorldRegionConnection;

void __cdecl Rva003F0CA1_DestroyRange(LivingWorldRegionConnection *, LivingWorldRegionConnection *);

// ??1Rva003F1797@@QAE@XZ @0x003F1797 63B -> ?Rva003F0CA1_DestroyRange@@YAXPAVLivingWorldRegionConnection@@0@Z
struct Rva003F1797 : RvaVectorFamilyBase<LivingWorldRegionConnection>
{
	~Rva003F1797();
};

Rva003F1797::~Rva003F1797()
{
	Rva003F0CA1_DestroyRange(m_start, m_finish);
}

// ??1Rva00405350@@QAE@XZ @0x00405350 63B -> ?Rva00405337Clear@@YAXPAX0@Z
struct Rva00405350 : RvaVectorFamilyBase<void>
{
	~Rva00405350();
};

Rva00405350::~Rva00405350()
{
	Rva00405337Clear(m_start, m_finish);
}

struct DestroyElem0040B52E;

void __cdecl Rva0040B52EDestroy(DestroyElem0040B52E *, DestroyElem0040B52E *);

// ??1Rva0040B560@@QAE@XZ @0x0040B560 63B -> ?Rva0040B52EDestroy@@YAXPAUDestroyElem0040B52E@@0@Z
struct Rva0040B560 : RvaVectorFamilyBase<DestroyElem0040B52E>
{
	~Rva0040B560();
};

Rva0040B560::~Rva0040B560()
{
	Rva0040B52EDestroy(m_start, m_finish);
}

struct Rva004F69C3;

// ??1Rva0040E0EB@@QAE@XZ @0x0040E0EB 63B -> ??$_Destroy@PAURva004F69C3@@@_STL@@YAXPAURva004F69C3@@0@Z
struct Rva0040E0EB : RvaVectorFamilyBase<Rva004F69C3>
{
	~Rva0040E0EB();
};

Rva0040E0EB::~Rva0040E0EB()
{
	_STL::_Destroy(m_start, m_finish);
}

struct DynamicPortalLink;

// ??1Rva0042464E@@QAE@XZ @0x0042464E 63B -> ??$_Destroy@PAUDynamicPortalLink@@@_STL@@YAXPAUDynamicPortalLink@@0@Z
struct Rva0042464E : RvaVectorFamilyBase<DynamicPortalLink>
{
	~Rva0042464E();
};

Rva0042464E::~Rva0042464E()
{
	_STL::_Destroy(m_start, m_finish);
}

// ??1Rva00426B73@@QAE@XZ @0x00426B73 63B -> ?Rva0032C0CADestroyPairs@@YAXPAURvaPair0032C0CA@@0@Z
struct Rva00426B73 : RvaVectorFamilyBase<RvaPair0032C0CA>
{
	~Rva00426B73();
};

Rva00426B73::~Rva00426B73()
{
	Rva0032C0CADestroyPairs(m_start, m_finish);
}

// ??1Rva0045D137@@QAE@XZ @0x0045D137 63B -> ??$_Destroy@PAUOpaqueRefElement4@@@_STL@@YAXPAUOpaqueRefElement4@@0@Z
struct Rva0045D137 : RvaVectorFamilyBase<OpaqueRefElement4>
{
	~Rva0045D137();
};

Rva0045D137::~Rva0045D137()
{
	_STL::_Destroy(m_start, m_finish);
}

struct Elem00467DCD;

void __cdecl Rva00467DCDDestroy(Elem00467DCD *, Elem00467DCD *);

// ??1Rva00467FCC@@QAE@XZ @0x00467FCC 63B -> ?Rva00467DCDDestroy@@YAXPAUElem00467DCD@@0@Z
struct Rva00467FCC : RvaVectorFamilyBase<Elem00467DCD>
{
	~Rva00467FCC();
};

Rva00467FCC::~Rva00467FCC()
{
	Rva00467DCDDestroy(m_start, m_finish);
}

struct Rva0052BFB5Elem;

void __cdecl Rva0052C37ADestroyRange(Rva0052BFB5Elem *, Rva0052BFB5Elem *);

// ??1Rva004EE501@@QAE@XZ @0x004EE501 63B -> ?Rva0052C37ADestroyRange@@YAXPAURva0052BFB5Elem@@0@Z
struct Rva004EE501 : RvaVectorFamilyBase<Rva0052BFB5Elem>
{
	~Rva004EE501();
};

Rva004EE501::~Rva004EE501()
{
	Rva0052C37ADestroyRange(m_start, m_finish);
}

struct Rva004F6986;

void __cdecl Rva004F8373Destroy(Rva004F6986 *, Rva004F6986 *);

// ??1Rva004F87F3@@QAE@XZ @0x004F87F3 63B -> ?Rva004F8373Destroy@@YAXPAURva004F6986@@0@Z
struct Rva004F87F3 : RvaVectorFamilyBase<Rva004F6986>
{
	~Rva004F87F3();
};

Rva004F87F3::~Rva004F87F3()
{
	Rva004F8373Destroy(m_start, m_finish);
}

struct Rva004F691E;

void __cdecl Rva004F838CDestroy(Rva004F691E *, Rva004F691E *);

// ??1Rva004F887C@@QAE@XZ @0x004F887C 63B -> ?Rva004F838CDestroy@@YAXPAURva004F691E@@0@Z
struct Rva004F887C : RvaVectorFamilyBase<Rva004F691E>
{
	~Rva004F887C();
};

Rva004F887C::~Rva004F887C()
{
	Rva004F838CDestroy(m_start, m_finish);
}

struct Rva004E1AD5Item;

void __cdecl Rva004E1FCCGet(Rva004E1AD5Item *, Rva004E1AD5Item *);

// ??1Rva004FABE2@@QAE@XZ @0x004FABE2 63B -> ?Rva004E1FCCGet@@YAXPAURva004E1AD5Item@@0@Z
struct Rva004FABE2 : RvaVectorFamilyBase<Rva004E1AD5Item>
{
	~Rva004FABE2();
};

Rva004FABE2::~Rva004FABE2()
{
	Rva004E1FCCGet(m_start, m_finish);
}

// ??1Rva0051211C@@QAE@XZ @0x0051211C 63B -> ?Rva0032C0CADestroyPairs@@YAXPAURvaPair0032C0CA@@0@Z
struct Rva0051211C : RvaVectorFamilyBase<RvaPair0032C0CA>
{
	~Rva0051211C();
};

Rva0051211C::~Rva0051211C()
{
	Rva0032C0CADestroyPairs(m_start, m_finish);
}

struct Rva0052BCE7Elem;

void __cdecl Rva0052C24EDestroyRange(Rva0052BCE7Elem *, Rva0052BCE7Elem *);

// ??1Rva0052CA2D@@QAE@XZ @0x0052CA2D 63B -> ?Rva0052C24EDestroyRange@@YAXPAURva0052BCE7Elem@@0@Z
struct Rva0052CA2D : RvaVectorFamilyBase<Rva0052BCE7Elem>
{
	~Rva0052CA2D();
};

Rva0052CA2D::~Rva0052CA2D()
{
	Rva0052C24EDestroyRange(m_start, m_finish);
}

struct Rva0052BF4DElem;

void __cdecl Rva0052C266DestroyRange(Rva0052BF4DElem *, Rva0052BF4DElem *);

// ??1Rva0052CA6C@@QAE@XZ @0x0052CA6C 63B -> ?Rva0052C266DestroyRange@@YAXPAURva0052BF4DElem@@0@Z
struct Rva0052CA6C : RvaVectorFamilyBase<Rva0052BF4DElem>
{
	~Rva0052CA6C();
};

Rva0052CA6C::~Rva0052CA6C()
{
	Rva0052C266DestroyRange(m_start, m_finish);
}

// ??1Rva0052CB26@@QAE@XZ @0x0052CB26 63B -> ?Rva005A6EDADestroyRange@@YAXPAURva0052BF33Elem@@0@Z
struct Rva0052CB26 : RvaVectorFamilyBase<Rva0052BF33Elem>
{
	~Rva0052CB26();
};

Rva0052CB26::~Rva0052CB26()
{
	Rva005A6EDADestroyRange(m_start, m_finish);
}

// ??1Rva0052CC25@@QAE@XZ @0x0052CC25 63B -> ?Rva0052C37ADestroyRange@@YAXPAURva0052BFB5Elem@@0@Z
struct Rva0052CC25 : RvaVectorFamilyBase<Rva0052BFB5Elem>
{
	~Rva0052CC25();
};

Rva0052CC25::~Rva0052CC25()
{
	Rva0052C37ADestroyRange(m_start, m_finish);
}

// ??1Rva0052CCC4@@QAE@XZ @0x0052CCC4 63B -> ?Rva0022C8E3DestroyRange@@YAXPAURva0052BF9BElem@@0@Z
struct Rva0052CCC4 : RvaVectorFamilyBase<Rva0052BF9BElem>
{
	~Rva0052CCC4();
};

Rva0052CCC4::~Rva0052CCC4()
{
	Rva0022C8E3DestroyRange(m_start, m_finish);
}

struct Rva0052BF67Elem;

void __cdecl Rva0052C3BFDestroyRange(Rva0052BF67Elem *, Rva0052BF67Elem *);

// ??1Rva0052CD03@@QAE@XZ @0x0052CD03 63B -> ?Rva0052C3BFDestroyRange@@YAXPAURva0052BF67Elem@@0@Z
struct Rva0052CD03 : RvaVectorFamilyBase<Rva0052BF67Elem>
{
	~Rva0052CD03();
};

Rva0052CD03::~Rva0052CD03()
{
	Rva0052C3BFDestroyRange(m_start, m_finish);
}

// ??1Rva0052CD42@@QAE@XZ @0x0052CD42 63B -> ?Rva003F0CA1_DestroyRange@@YAXPAVLivingWorldRegionConnection@@0@Z
struct Rva0052CD42 : RvaVectorFamilyBase<LivingWorldRegionConnection>
{
	~Rva0052CD42();
};

Rva0052CD42::~Rva0052CD42()
{
	Rva003F0CA1_DestroyRange(m_start, m_finish);
}

class Rva004E1A04;

void __cdecl Rva0052CEDDClear(Rva004E1A04 *, Rva004E1A04 *);

// ??1Rva0052D1CD@@QAE@XZ @0x0052D1CD 63B -> ?Rva0052CEDDClear@@YAXPAVRva004E1A04@@0@Z
struct Rva0052D1CD : RvaVectorFamilyBase<Rva004E1A04>
{
	~Rva0052D1CD();
};

Rva0052D1CD::~Rva0052D1CD()
{
	Rva0052CEDDClear(m_start, m_finish);
}

class Rva004E366E;

void __cdecl Rva0052CEF6Clear(Rva004E366E *, Rva004E366E *);

// ??1Rva0052D20C@@QAE@XZ @0x0052D20C 63B -> ?Rva0052CEF6Clear@@YAXPAVRva004E366E@@0@Z
struct Rva0052D20C : RvaVectorFamilyBase<Rva004E366E>
{
	~Rva0052D20C();
};

Rva0052D20C::~Rva0052D20C()
{
	Rva0052CEF6Clear(m_start, m_finish);
}

class Rva00585B16;

void __cdecl Rva00586B92Destroy(Rva00585B16 *, Rva00585B16 *);

// ??1Rva00586C17@@QAE@XZ @0x00586C17 63B -> ?Rva00586B92Destroy@@YAXPAVRva00585B16@@0@Z
struct Rva00586C17 : RvaVectorFamilyBase<Rva00585B16>
{
	~Rva00586C17();
};

Rva00586C17::~Rva00586C17()
{
	Rva00586B92Destroy(m_start, m_finish);
}

// ??1Rva005A7172@@QAE@XZ @0x005A7172 63B -> ?Rva005A6EDADestroyRange@@YAXPAURva0052BF33Elem@@0@Z
struct Rva005A7172 : RvaVectorFamilyBase<Rva0052BF33Elem>
{
	~Rva005A7172();
};

Rva005A7172::~Rva005A7172()
{
	Rva005A6EDADestroyRange(m_start, m_finish);
}

struct Rva005E74AA;

void __cdecl Rva005E7FB0Forward(Rva005E74AA *, Rva005E74AA *);

// ??1Rva005E8005@@QAE@XZ @0x005E8005 63B -> ?Rva005E7FB0Forward@@YAXPAURva005E74AA@@0@Z
struct Rva005E8005 : RvaVectorFamilyBase<Rva005E74AA>
{
	~Rva005E8005();
};

Rva005E8005::~Rva005E8005()
{
	Rva005E7FB0Forward(m_start, m_finish);
}

struct Rva005EC594;

void __cdecl Rva005EC594Clear(Rva005EC594 *, Rva005EC594 *);

// ??1Rva005EC9BA@@QAE@XZ @0x005EC9BA 63B -> ?Rva005EC594Clear@@YAXPAURva005EC594@@0@Z
struct Rva005EC9BA : RvaVectorFamilyBase<Rva005EC594>
{
	~Rva005EC9BA();
};

Rva005EC9BA::~Rva005EC9BA()
{
	Rva005EC594Clear(m_start, m_finish);
}

class Rva0040B77E;

// ??1Rva0040BEBA@@QAE@XZ @0x0040BEBA 63B -> ??$_Destroy@PAVRva0040B77E@@@_STL@@YAXPAVRva0040B77E@@0@Z
struct Rva0040BEBA : RvaVectorFamilyBase<Rva0040B77E>
{
	~Rva0040BEBA();
};

Rva0040BEBA::~Rva0040BEBA()
{
	_STL::_Destroy(m_start, m_finish);
}

struct Rva0040AFF3;

// ??1Rva0040B59F@@QAE@XZ @0x0040B59F 63B -> ??$_Destroy@PAURva0040AFF3@@@_STL@@YAXPAURva0040AFF3@@0@Z
struct Rva0040B59F : RvaVectorFamilyBase<Rva0040AFF3>
{
	~Rva0040B59F();
};

Rva0040B59F::~Rva0040B59F()
{
	_STL::_Destroy(m_start, m_finish);
}

struct BfmeVectorRecord00319C84;

// ??1Rva0052CDE1@@QAE@XZ @0x0052CDE1 63B -> ??$_Destroy@PAUBfmeVectorRecord00319C84@@@_STL@@YAXPAUBfmeVectorRecord00319C84@@0@Z
struct Rva0052CDE1 : RvaVectorFamilyBase<BfmeVectorRecord00319C84>
{
	~Rva0052CDE1();
};

Rva0052CDE1::~Rva0052CDE1()
{
	_STL::_Destroy(m_start, m_finish);
}

struct Rva004FFE81;

void __cdecl Rva00500CB8Destroy(Rva004FFE81 *, Rva004FFE81 *);

// ??1Rva005011DA@@QAE@XZ @0x005011DA 63B -> ?Rva00500CB8Destroy@@YAXPAURva004FFE81@@0@Z
// Vector dtor shape (destroy [start finish) then free): caller 0x00501776 holds
// vectors at +0x14/+0x20 and calls here twice; callees rowed 0x00500CB8 and 0x00030830.
struct Rva005011DA : RvaVectorFamilyBase<Rva004FFE81>
{
	~Rva005011DA();
};

Rva005011DA::~Rva005011DA()
{
	Rva00500CB8Destroy(m_start, m_finish);
}

struct Rva004FABE2;

void __cdecl Rva00500AF8Destroy(Rva004FABE2 *, Rva004FABE2 *);

// ??1Rva00500E3D@@QAE@XZ @0x00500E3D 63B -> ?Rva00500AF8Destroy@@YAXPAURva004FABE2@@0@Z
// Vector dtor shape (destroy [start finish) then free with EH): callers
// 0x00503450 0x005034ED 0x00503511 in 0x00502FE9; callees rowed 0x00500AF8 and 0x00030830.
struct Rva00500E3D : RvaVectorFamilyBase<Rva004FABE2>
{
	~Rva00500E3D();
};

Rva00500E3D::~Rva00500E3D()
{
	Rva00500AF8Destroy(m_start, m_finish);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1BfmeVector0022C55B@@QAE@XZ=??1Rva0022CAC4@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1SlowDeathSoundVec@@QAE@XZ=??1Rva0045D137@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva0039C151Subobject@@QAE@XZ=??1Rva0039C151@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva004EE501Subobject@@QAE@XZ=??1Rva004EE501@@QAE@XZ")
