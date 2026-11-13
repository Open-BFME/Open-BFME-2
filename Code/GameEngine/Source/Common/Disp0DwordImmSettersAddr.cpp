// Members of the Disp0DwordImmSetters.cpp family split out while their vftable
// addresses lacked linkable names. Unnamed retail tables below are mapped from
// vftable_map slot targets and relocated to their matched bodies.
//
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
extern "C" const void *const __identifier("??_7Rva0052634F_Base@@6B@")[];  // vftable 0x00C67E3C

extern "C" const void *const __identifier("??_7Rva00082EF5Second@@6B@")[];  // vftable 0x00BC6EEC

extern "C" const void *const __identifier("??_7Rva00604A42@@6B@")[];  // vftable 0x00C7A974

extern "C" const void *const __identifier("??_7Rva00602645@@6B@")[];  // vftable 0x00C7A84C

extern "C" const void *const __identifier("??_7Rva005E9FA4@@6B@")[];  // vftable 0x00C780F4

extern "C" const void *const __identifier("??_7Rva005E567D@@6B@")[];  // vftable 0x00C77D30

extern "C" const void *const __identifier("??_7Rva005D1035@@6B@")[];  // vftable 0x00C7559C

extern "C" const void *const __identifier("??_7Rva005D078BSecond@@6B@")[];  // folded vftable 0x00C7528C (2 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva005D0C87Interface@@6B@")[];  // vftable 0x00C75284

extern "C" const void *const __identifier("??_7Rva005CF826@@6B@")[];  // folded vftable 0x00C75278 (3 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva005CE8F5@@6B@")[];  // vftable 0x00C751A8

extern "C" const void *const __identifier("??_7Rva0059EB41@@6B@")[];  // vftable 0x00C711BC

extern "C" const void *const __identifier("??_7VBase00C6EE28@@6B@")[];  // folded vftable 0x00C6EE28 (2 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Base3@@6B@")[];  // vftable 0x00C6EE20

extern "C" const void *const __identifier("??_7Rva005753E9@@6B@")[];  // vftable 0x00C6E5C4

extern "C" const void *const __identifier("??_7Rva0055057D@@6B@")[];  // vftable 0x00C6ABC0

extern "C" const void *const __identifier("??_7Rva00549C74@@6B@")[];  // vftable 0x00C6A68C

extern "C" const void *const __identifier("??_7Rva0052B668@@6B@")[];  // vftable 0x00C686BC

extern "C" const void *const __identifier("??_7Rva005D06CBB2@@6B@")[];  // vftable 0x00C62A14

extern "C" const void *const __identifier("??_7Rva003B7190Record@@6B@")[];  // folded vftable 0x00C619A0 (2 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva004BDA0C@@6B@")[];  // vftable 0x00C5AEB0

extern "C" const void *const __identifier("??_7Rva00468A46@@6B@")[];  // vftable 0x00C44890

extern "C" const void *const __identifier("??_7Rva0056B126B2@@6B@")[];  // vftable 0x00BFDF68

extern "C" const void *const __identifier("??_7Rva005EEF2FBase0@@6B@")[];  // vftable 0x00BFBC9C

extern "C" const void *const __identifier("??_7Rva0054F922@@6B@")[];  // vftable 0x00C6AB10

extern "C" const void *const __identifier("??_7BfmeBaseCC@@6B@")[];  // folded vftable 0x00BC64B0 (2 classes), by its data-ledger name

// vftable_map identifies all 76 slots in these 14 retail tables; each points
// to one of eight matched bodies or the mapped __purecall runtime symbol.
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")(void);
extern "C" void __identifier("?Set_Animation@RenderObjClass@@UAEXPAVHAnimClass@@MH@Z")(void);
extern "C" void __identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")(void);
extern "C" void __identifier("?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z")(void);
extern "C" void __identifier("?rva001FF3A9@Rva001FF3A9@@UAEXXZ")(void);
extern "C" void __identifier("?rva005CB26A@Rva005CB26A@@QAEHXZ")(void);
extern "C" void __identifier("?rva005CC208@Rva005CC208@@UAEXXZ")(void);
extern "C" void bfmeDisp0Slot_Purecall(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_Purecall=__purecall")

#define BFME_DISP0_SLOT(FUNCTION) reinterpret_cast<const void *>(FUNCTION)

extern "C" const void *const __identifier("??_7LivingWorldPlayerObserver@@6B@")[];  // VA 0x00BFDF8C
extern "C" const void *const __identifier("??_7Rva008291DSecond@@6B@")[];  // VA 0x00BC6F04
extern "C" const void *const __identifier("??_7Rva0081FDDSecond@@6B@")[];  // VA 0x00BC6EC0
extern "C" const void *const __identifier("??_7RegionTurnObserverView@@6B@")[];  // VA 0x00C62A20
extern "C" const void *const __identifier("??_7TerrainLogicListenerRootA@@6B@")[];  // VA 0x00BC6F34
extern "C" const void *const __identifier("??_7Rva005E4AE2Base@@6B@")[];  // VA 0x00C77BE8
extern "C" const void *const __identifier("??_7LivingWorldObserver@@6B@")[];  // VA 0x00BE5114
extern "C" const void *const __identifier("??_7Rva003304A4AnimationVisitor@@6B@")[];  // VA 0x00C0DB24
extern "C" const void *const __identifier("??_7Rva003FE20FBase@@6B@")[];  // VA 0x00C37E18
extern "C" const void *const __identifier("??_7Rva0086CE84Observer@@6B@")[];  // VA 0x00C6CE84
extern "C" const void *const __identifier("??_7Rva005F3EE3@@6B@")[];  // VA 0x00C79428
extern "C" const void *const vtbl_00C75908[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall)
};
extern "C" const void *const __identifier("??_7Rva00574CC1Base10@@6B@")[];  // VA 0x00C6E344
extern "C" const void *const __identifier("??_7PalantirBase0@@6B@")[];  // VA 0x00C79760

#undef BFME_DISP0_SLOT

class Rva002B228DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002B228DDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7LivingWorldPlayerObserver@@6B@"));
}

class Rva0007DEA1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DEA1DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00082EF5Second@@6B@"));
}

class Rva0007DEA8DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DEA8DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva008291DSecond@@6B@"));
}

class Rva0007DE9ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DE9ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0081FDDSecond@@6B@"));
}

class Rva004EDFF8DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EDFF8DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005D06CBB2@@6B@"));
}

class Rva004EDFFFDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EDFFFDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7RegionTurnObserverView@@6B@"));
}

class Rva004EE006DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EE006DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7TerrainLogicListenerRootA@@6B@"));
}

class Rva0057A235DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A235DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Base3@@6B@"));
}

class Rva0057A243DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A243DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7VBase00C6EE28@@6B@"));
}

class Rva005CF843DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005CF843DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005D0C87Interface@@6B@"));
}

class Rva005CF84ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005CF84ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005D078BSecond@@6B@"));
}

class Rva005E394EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005E394EDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005E4AE2Base@@6B@"));
}

class Rva000723C0DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000723C0DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7BfmeBaseCC@@6B@"));
}

class Rva00210CC5DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00210CC5DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7LivingWorldObserver@@6B@"));
}

class Rva00330440DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00330440DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva003304A4AnimationVisitor@@6B@"));
}

class Rva00468A3FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00468A3FDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00468A46@@6B@"));
}

class Rva004BDA05DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004BDA05DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva004BDA0C@@6B@"));
}

class Rva004E14E1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004E14E1DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva003B7190Record@@6B@"));
}

class Rva0052AF77DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0052AF77DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva003FE20FBase@@6B@"));
}

class Rva005676F4DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005676F4DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0086CE84Observer@@6B@"));
}

class Rva0059EB3ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0059EB3ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0059EB41@@6B@"));
}

class Rva0005CF81FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CF81FDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005CF826@@6B@"));
}

class Rva000604A68DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000604A68DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00604A42@@6B@"));
}

class Rva00060263EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00060263EDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00602645@@6B@"));
}

class Rva0005F3EE3DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005F3EE3DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005F3EE3@@6B@"));
}

class Rva0005EA2ABDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005EA2ABDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005E9FA4@@6B@"));
}

class Rva0005E57C9DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E57C9DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005E567D@@6B@"));
}

class Rva000550576DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000550576DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0055057D@@6B@"));
}

class Rva00054F91BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00054F91BDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0054F922@@6B@"));
}

class Rva000549C6DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000549C6DDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00549C74@@6B@"));
}

class Rva00052B588DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00052B588DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0052B668@@6B@"));
}

class Rva000524F5ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000524F5ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0052634F_Base@@6B@"));
}

class Rva0005D387BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D387BDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C75908);
}

// Seven more vptr stores returning this, the 0x005D3882 shape: each writes
// one of this file's tables at this (the same table the named setter
// sibling stores) and returns this, the constructor shape of that base.
// 0x0007E0BD (9B): table VA 0x00BC6F04, setter sibling 0x0007DEA8.
class Rva0007E0BDAbstractBase
{
public:
	Rva0007E0BDAbstractBase *rva0007E0BD();

	unsigned int m_value;
};

Rva0007E0BDAbstractBase *Rva0007E0BDAbstractBase::rva0007E0BD()
{
	m_value = ((unsigned int)__identifier("??_7Rva008291DSecond@@6B@"));
	return this;
}

// 0x0007E0D9 (9B): table VA 0x00BC6EC0, setter sibling 0x0007DE9A.
class Rva0007E0D9AbstractBase
{
public:
	Rva0007E0D9AbstractBase *rva0007E0D9();

	unsigned int m_value;
};

Rva0007E0D9AbstractBase *Rva0007E0D9AbstractBase::rva0007E0D9()
{
	m_value = ((unsigned int)__identifier("??_7Rva0081FDDSecond@@6B@"));
	return this;
}

// 0x00210CE8 (9B): table VA 0x00BE5114, setter sibling 0x00210CC5.
class Rva00210CE8AbstractBase
{
public:
	Rva00210CE8AbstractBase *rva00210CE8();

	unsigned int m_value;
};

Rva00210CE8AbstractBase *Rva00210CE8AbstractBase::rva00210CE8()
{
	m_value = ((unsigned int)__identifier("??_7LivingWorldObserver@@6B@"));
	return this;
}

// 0x002B252C (9B): table VA 0x00BFDF8C, setter sibling 0x002B228D.
class Rva002B252CAbstractBase
{
public:
	Rva002B252CAbstractBase *rva002B252C();

	unsigned int m_value;
};

Rva002B252CAbstractBase *Rva002B252CAbstractBase::rva002B252C()
{
	m_value = ((unsigned int)__identifier("??_7LivingWorldPlayerObserver@@6B@"));
	return this;
}

// 0x005743B7 (9B): table VA 0x00C6E344, setter sibling 0x00574265.
class Rva005743B7AbstractBase
{
public:
	Rva005743B7AbstractBase *rva005743B7();

	unsigned int m_value;
};

Rva005743B7AbstractBase *Rva005743B7AbstractBase::rva005743B7()
{
	m_value = ((unsigned int)__identifier("??_7Rva00574CC1Base10@@6B@"));
	return this;
}

// 0x005F3EEA (9B): table VA 0x00C79428, setter sibling 0x005F3EE3.
class Rva005F3EEAAbstractBase
{
public:
	Rva005F3EEAAbstractBase *rva005F3EEA();

	unsigned int m_value;
};

Rva005F3EEAAbstractBase *Rva005F3EEAAbstractBase::rva005F3EEA()
{
	m_value = ((unsigned int)__identifier("??_7Rva005F3EE3@@6B@"));
	return this;
}

// 0x005F687A (9B): table VA 0x00C79760, setter sibling 0x0057851B.
class Rva005F687AAbstractBase
{
public:
	Rva005F687AAbstractBase *rva005F687A();

	unsigned int m_value;
};

Rva005F687AAbstractBase *Rva005F687AAbstractBase::rva005F687A()
{
	m_value = ((unsigned int)__identifier("??_7PalantirBase0@@6B@"));
	return this;
}

// 0x005D3882 (9B), right after 0x005D387B: the same store of the abstract
// table 0x00C75908 (eleven __purecall slots) at this, returning this: the
// constructor shape of that abstract base, written in this file's style.
class Rva005D3882AbstractBase
{
public:
	Rva005D3882AbstractBase *rva005D3882();

	unsigned int m_value;
};

Rva005D3882AbstractBase *Rva005D3882AbstractBase::rva005D3882()
{
	m_value = ((unsigned int)vtbl_00C75908);
	return this;
}

#include "../../Include/Common/Rva0005D10D6DwordImmSetter.h"

void Rva0005D10D6DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005D1035@@6B@"));
}

class Rva0005CE8EEDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CE8EEDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005CE8F5@@6B@"));
}
class Rva000579656DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000579656DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005EEF2FBase0@@6B@"));
}
class Rva000574265DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000574265DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva00574CC1Base10@@6B@"));
}

class Rva0002B221ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0002B221ADwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva0056B126B2@@6B@"));
}
class Rva005753E2DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005753E2DwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7Rva005753E9@@6B@"));
}

class Rva0057851BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057851BDwordImmSetter::apply()
{
	m_value = ((unsigned int)__identifier("??_7PalantirBase0@@6B@"));
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva005D6FCC@@UAE@XZ=?apply@Rva0005D6FDEDwordImmSetter@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00539926Base@@UAE@XZ=?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeTailSF@BfmeThingSF@@QAEXXZ=??1Rva001DBAA4@@UAE@XZ")
