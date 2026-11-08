// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Disp0 dword immediate setters: seven-byte __thiscall members with one shape:
//
//     mov dword ptr [ecx],<IMM32> / ret
//
// The dword at `this` itself is set to a hardcoded immediate and nothing is
// read back. The zero-displacement member of the disp8 family
// (Disp8DwordImmSetters.cpp) and the disp32 family
// (DispDwordImmSetters.cpp); MSVC 7.1 uses the C7-01 form when the offset is
// zero, so there is no lead array. Only the class names follow this tree's
// Disp* convention (address-derived Rva<addr>DwordImmSetter, identity
// unrecoverable from 7 bytes). Retail cleans none (`ret`, not `ret 4`), so
// the members take no parameters.
// No // cl: line (defaults match the frameless 7-byte shape).
extern "C" const void *const __identifier("??_7Rva00104DB0Base@@6B@")[];  // vftable 0x00BCF7E8

extern "C" const void *const __identifier("??_7Rva00051E4D@@6B@")[];  // vftable 0x00BC5128

extern "C" const void *const __identifier("??_7Rva000851F3@@6B@")[];  // vftable 0x00BC745C
extern "C" const void *const __identifier("??_7Rva0007DF07@@6B@")[];  // folded vftable 0x00BC6F20 (7 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7BfmeShadowBufferOwnerBase@@6B@")[];  // folded, 3 classes; via ??_7BfmeShadowBufferOwnerBase@@6B@
extern "C" const void *const __identifier("??_7DamageModuleInterface@@6B@")[];  // folded vftable 0x00BE2B78 (9 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7Rva00203E76@@6B@")[];  // folded, 2 classes; via ??_7Rva00203E76@@6B@
extern "C" const void *const __identifier("??_7Rva005F0584Base0@@6B@")[];  // folded vftable 0x00BFBCBC (2 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7BfmeCtorVirtualBase001B3A20@@6B@")[];  // folded vftable 0x00C078DC (4 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7Rva00575E4EBase2@@6B@")[];  // folded vftable 0x00C3702C (4 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@")[];  // folded vftable 0x00C4EF80 (7 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7Rva005754FF@@6B@")[];  // folded vftable 0x00C6E60C (2 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva000421C8@@6B@")[];  // vftable 0x00BC26E0
extern "C" const void *const __identifier("??_7Rva0030D346@@6B@")[];  // vftable 0x00C089EC
extern "C" const void *const __identifier("??_7Rva0054F434Base@@6B@")[];  // vftable 0x00C6A894
extern "C" const void *const __identifier("??_7Listener00576C4B@@6B@")[];  // vftable 0x00C6E788
extern "C" const void *const __identifier("??_7Rva005CF872@@6B@")[];  // vftable 0x00C75290

extern "C" const void *const __identifier("??_7Rva0086E330Base@@6B@")[];  // vftable 0x00C6E330

extern "C" const void *const __identifier("??_7_Messages@_STL@@6B@")[];  // vftable 0x00BBC8D4
extern "C" const void *const __identifier("??_7DebugCmdInterface@@6B@")[];  // vftable 0x00BBE7EC
extern "C" const void *const __identifier("??_7FileFactoryClass@@6B@")[];  // vftable 0x00BC6778
extern "C" const void *const __identifier("??_7Base@@6B@")[];  // vftable 0x00BC6F24
extern "C" const void *const __identifier("??_7SubsystemSlotBase@@6B@")[];  // vftable 0x00BE714C
extern "C" const void *const __identifier("??_7Rva0023A128Link@@6B@")[];  // vftable 0x00BED658
extern "C" const void *const __identifier("??_7DrawableLocoInfo@@6B@")[];  // vftable 0x00BFAD38
extern "C" const void *const __identifier("??_7LargeGroupAudioUpdate_B24@@6B@")[];  // vftable 0x00BFB698
extern "C" const void *const __identifier("??_7Rva004F5FD8@@6B@")[];  // vftable 0x00BFDC30
extern "C" const void *const __identifier("??_7?$DLListClass@USmudge@@@@6B@")[];  // vftable 0x00C02A58
extern "C" const void *const __identifier("??_7?$DLListClass@USmudgeSet@@@@6B@")[];  // vftable 0x00C02A5C
extern "C" const void *const __identifier("??_7GameSpyPeerMessageQueueInterface@@6B@")[];  // vftable 0x00C1980C
extern "C" const void *const __identifier("??_7Rva0057A2B0B1@@6B@")[];  // vftable 0x00C42518
extern "C" const void *const __identifier("??_7BaseA@@6B@")[];  // vftable 0x00C62888
extern "C" const void *const __identifier("??_7Rva00506B1B@@6B@")[];  // vftable 0x00C63F9C
extern "C" const void *const __identifier("??_7Rva0057E3DBBase@@6B@")[];  // vftable 0x00C6E350
extern "C" const void *const __identifier("??_7Rva0059675ABase@@6B@")[];  // vftable 0x00C70A5C
extern "C" const void *const __identifier("??_7Rva005DAA36@@6B@")[];  // vftable 0x00C70B80
extern "C" const void *const __identifier("??_7Rva005C1860@@6B@")[];  // vftable 0x00C743B8
extern "C" const void *const __identifier("??_7Rva005CBA04@@6B@")[];  // vftable 0x00C74DB8
extern "C" const void *const __identifier("??_7Rva005D6FCC@@6B@")[];  // vftable 0x00C75C38
extern "C" const void *const __identifier("??_7Rva005DBCD1@@6B@")[];  // vftable 0x00C767D4
extern "C" const void *const __identifier("??_7IconMouseObserver@@6B@")[];  // vftable 0x00C77E7C
extern "C" const void *const __identifier("??_7Rva0057605DSecond@@6B@")[];  // vftable 0x00C77F44
extern "C" const void *const __identifier("??_7Rva005E4AE2Listener@@6B@")[];  // vftable 0x00C79544
class Rva00238D97DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00238D97DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0023A128Link@@6B@"));
}

class Rva002B2294DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002B2294DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0057605DSecond@@6B@"));
}

class Rva0057428CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057428CDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0057E3DBBase@@6B@"));
}

class Rva0057A23CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A23CDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0057A2B0B1@@6B@"));
}

class Rva005E3947DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005E3947DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005E4AE2Listener@@6B@"));
}

class Rva000657ACDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000657ACDwordImmSetter::apply()
{
	m_value = 0;
}

class Rva0008523ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0008523ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva000851F3@@6B@"));
}

class Rva000E14BDDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000E14BDDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Base@@6B@"));
}

class Rva00104D73DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00104D73DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00104DB0Base@@6B@"));
}

// Complete destructor restoring the shared shadow-base table.
class __declspec(novtable) Rva00108B4D
{
public:
	virtual ~Rva00108B4D();
};

Rva00108B4D::~Rva00108B4D()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7BfmeShadowBufferOwnerBase@@6B@"));
}

// Complete destructor restoring its existing external table owner.
class __declspec(novtable) Rva0010EFCD
{
public:
	virtual ~Rva0010EFCD();
};

Rva0010EFCD::~Rva0010EFCD()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7Rva00051E4D@@6B@"));
}

class Rva00270158DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00270158DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7DrawableLocoInfo@@6B@"));
}

// Native 0x002A983D is the complete seven-byte array-element destructor,
// supplied alongside ctor 0x002B2508 to the EH vector constructor in
// RetreatArmiesForPlayer (3F6727) and AutoBattleResolver (2BD40D).
// The element is a 44-byte derived rank object; teardown only restores its
// base vptr. Keep this existing table symbol/relocation rather than emit a
// second private base-class vtable. This prefix view names the destructor
// already declared by those callers; the original class name is unknown.
class Rva002B2508
{
public:
	virtual ~Rva002B2508();
};

Rva002B2508::~Rva002B2508()
{
	*(const void *const **)this = __identifier("??_7Rva004F5FD8@@6B@");
}

class Rva002D24EFDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002D24EFDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7?$DLListClass@USmudge@@@@6B@"));
}

class Rva002D2507DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002D2507DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7?$DLListClass@USmudgeSet@@@@6B@"));
}

class Rva0030D353DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0030D353DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0030D346@@6B@"));
}

class Rva00388845DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00388845DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7GameSpyPeerMessageQueueInterface@@6B@"));
}

class Rva003F3F7CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva003F3F7CDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00575E4EBase2@@6B@"));
}

// Native3F7BC5 is the registry base nondeleting destructor. Its full
// interface now lives with Rva0056AC26Base2; no address-table alias is needed.

class Rva00506B28DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00506B28DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00506B1B@@6B@"));
}

class Rva0054E796DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0054E796DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0054F434Base@@6B@"));
}

class Rva00596686DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00596686DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0059675ABase@@6B@"));
}

class Rva00019EC0DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00019EC0DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7_Messages@_STL@@6B@"));
}

// Native35780 is the scoped WideStrLenSource destructor; its complete C++
// definition now owns the row in StringBaseWideStrLenSet.cpp.

class Rva0005CF86BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CF86BDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005CF872@@6B@"));
}

class Rva0005D23FEDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D23FEDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7BfmeCtorVirtualBase001B3A20@@6B@"));
}

class Rva0006C5930DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0006C5930DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7DebugCmdInterface@@6B@"));
}

// 0x00610480 (vptr store of ??_7ThreadClass) is ThreadClass::~ThreadClass, rowed
// from ThreadClassLifecycle.cpp.

class Rva0005F686ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005F686ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005F0584Base0@@6B@"));
}

class Rva0005E211FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E211FDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7IconMouseObserver@@6B@"));
}

class Rva0005E186ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E186ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0086E330Base@@6B@"));
}

class Rva0005DB82BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005DB82BDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005DBCD1@@6B@"));
}

class Rva0005277B3DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005277B3DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@"));
}

class Rva0004EA016DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0004EA016DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7BaseA@@6B@"));
}

class Rva0004E84A4DwordImmSetter
{
public:
	__declspec(noinline) void apply();

	unsigned int m_value;
};

void Rva0004E84A4DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0007DF07@@6B@"));
}

class Rva00049C38ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00049C38ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva000421C8@@6B@"));
}

class Rva000419B8DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000419B8DDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7DebugCmdInterface@@6B@"));
}

class Rva0005D6FDEDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D6FDEDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005D6FCC@@6B@"));
}

class Rva0005D2EA1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D2EA1DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7DamageModuleInterface@@6B@"));
}

class Rva00078274DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00078274DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7FileFactoryClass@@6B@"));
}
class Rva0005CB9F3DwordImmSetter
{
public:
	__declspec(noinline) void apply();

	unsigned int m_value;
};

void Rva0005CB9F3DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005CBA04@@6B@"));
}
class Rva0005C1872DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005C1872DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005C1860@@6B@"));
}
class Rva0005970E6DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005970E6DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005DAA36@@6B@"));
}
class Rva00057571CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00057571CDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005754FF@@6B@"));
}
class Rva00028562EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00028562EDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7LargeGroupAudioUpdate_B24@@6B@"));
}
class Rva000225A55DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000225A55DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7SubsystemSlotBase@@6B@"));
}

class Rva00203611DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00203611DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00203E76@@6B@"));
}

class Rva00576456DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00576456DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Listener00576C4B@@6B@"));
}

// Native419E38 tail JMP610480; scalar deleting419E1C and retail vtable
// slots witness destruction. Pointer-only view: complete owner type unknown.
#include "../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"

class __declspec(novtable) Rva00419E38
{
public:
    virtual ~Rva00419E38();
};
Rva00419E38::~Rva00419E38()
{
    reinterpret_cast<ThreadClass *>(this)->ThreadClass::~ThreadClass();
}

// Native567A69 tail JMP4E84A4; scalar deleting53DAE6 witnesses cleanup.
// Original complete owner and semantic identity remain unknown.
class __declspec(novtable) Rva00567A69
{
public:
    virtual ~Rva00567A69();
};
Rva00567A69::~Rva00567A69()
{
    reinterpret_cast<Rva0004E84A4DwordImmSetter *>(this)->apply();
}

// Native576FCE tail JMP5CB9F3; scalar deleting5E5A66 witnesses cleanup.
// Original complete owner and semantic identity remain unknown.
class __declspec(novtable) Rva00576FCE
{
public:
    virtual ~Rva00576FCE();
};
Rva00576FCE::~Rva00576FCE()
{
    reinterpret_cast<Rva0005CB9F3DwordImmSetter *>(this)->apply();
}
