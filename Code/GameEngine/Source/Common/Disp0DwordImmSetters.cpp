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
extern "C" const void *const vtbl_00BCF7E8[];  // ??_7Rva00104DB0Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCF7E8=??_7Rva00104DB0Base@@6B@")

extern "C" const void *const vtbl_00BC5128[];  // ??_7Rva001DA2D5Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC5128=??_7Rva001DA2D5Base@@6B@")

extern "C" const void *const vtbl_00BC745C[];  // ??_7Rva000851F3@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC745C=??_7Rva000851F3@@6B@")
extern "C" const void *const vtbl_00BC6F20[];  // folded, 7 classes; via ??_7Rva0007DF07@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")
extern "C" const void *const vtbl_00BCEFA0[];  // folded, 3 classes; via ??_7BfmeShadowBufferOwnerBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCEFA0=??_7BfmeShadowBufferOwnerBase@@6B@")
extern "C" const void *const vtbl_00BDBA74[];  // folded, 3 classes; via ??_7Base0_00576C4B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BDBA74=??_7Base0_00576C4B@@6B@")
extern "C" const void *const vtbl_00BE2B78[];  // folded, 9 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")
extern "C" const void *const vtbl_00BE3990[];  // folded, 2 classes; via ??_7BfmeDualVtableReleaseBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE3990=??_7BfmeDualVtableReleaseBase@@6B@")
extern "C" const void *const vtbl_00BFBCBC[];  // folded, 2 classes; via ??_7Rva005F6941Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFBCBC=??_7Rva005F6941Base@@6B@")
extern "C" const void *const vtbl_00C078DC[];  // folded, 4 classes; via ??_7BfmeCtor001B3A20@@6BBfmeCtorVirtualBase001B3A20@@@
#pragma comment(linker, "/alternatename:_vtbl_00C078DC=??_7BfmeCtor001B3A20@@6BBfmeCtorVirtualBase001B3A20@@@")
extern "C" const void *const vtbl_00C3702C[];  // folded, 4 classes; via ??_7Rva0056B0BFB2@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3702C=??_7Rva0056B0BFB2@@6B@")
extern "C" const void *const vtbl_00C37298[];  // folded, 2 classes; via ??_7Base003F8ED6@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C37298=??_7Base003F8ED6@@6B@")
extern "C" const void *const vtbl_00C4EF80[];  // folded, 7 classes; via ??_7ContainIface34@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4EF80=??_7ContainIface34@@6B@")
extern "C" const void *const vtbl_00C60130[];  // folded, 2 classes; via ??_7MemoryPoolObject@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C60130=??_7MemoryPoolObject@@6B@")
extern "C" const void *const vtbl_00C618CC[];  // folded, 2 classes; via ??_7Rva003A6F70@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C618CC=??_7Rva003A6F70@@6B@")
extern "C" const void *const vtbl_00C6E60C[];  // folded, 2 classes; via ??_7Rva00575E4EBase1@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E60C=??_7Rva00575E4EBase1@@6B@")

extern "C" const void *const vtbl_00BC26E0[];  // ??_7Rva000421C8@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC26E0=??_7Rva000421C8@@6B@")
extern "C" const void *const vtbl_00C089EC[];  // ??_7Rva0030D346@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C089EC=??_7Rva0030D346@@6B@")
extern "C" const void *const vtbl_00C6A894[];  // ??_7Rva0054F434Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6A894=??_7Rva0054F434Base@@6B@")
extern "C" const void *const vtbl_00C6E788[];  // ??_7Listener00576C4B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E788=??_7Listener00576C4B@@6B@")
extern "C" const void *const vtbl_00C75290[];  // ??_7Rva005CF872@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75290=??_7Rva005CF872@@6B@")

extern "C" const void *const vtbl_00C6E330[];  // ??_7CreateAHeroData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E330=??_7CreateAHeroData@@6B@")

extern "C" const void *const vtbl_00BBC8D4[];  // ??_7_Messages@_STL@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBC8D4=??_7_Messages@_STL@@6B@")
extern "C" const void *const vtbl_00BBE7EC[];  // ??_7DebugCmdInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBE7EC=??_7DebugCmdInterface@@6B@")
extern "C" const void *const vtbl_00BC6778[];  // ??_7FileFactoryClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6778=??_7FileFactoryClass@@6B@")
extern "C" const void *const vtbl_00BC6F24[];  // ??_7Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F24=??_7Base@@6B@")
extern "C" const void *const vtbl_00BE714C[];  // ??_7SubsystemSlotBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE714C=??_7SubsystemSlotBase@@6B@")
extern "C" const void *const vtbl_00BED658[];  // ??_7Rva0023A128Link@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BED658=??_7Rva0023A128Link@@6B@")
extern "C" const void *const vtbl_00BFAD38[];  // ??_7DrawableLocoInfo@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFAD38=??_7DrawableLocoInfo@@6B@")
extern "C" const void *const vtbl_00BFB698[];  // ??_7LargeGroupAudioUpdate_B24@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFB698=??_7LargeGroupAudioUpdate_B24@@6B@")
extern "C" const void *const vtbl_00BFDC30[];  // ??_7Rva004F5FD8@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFDC30=??_7Rva004F5FD8@@6B@")
extern "C" const void *const vtbl_00C02A58[];  // ??_7?$DLListClass@USmudge@@@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C02A58=??_7?$DLListClass@USmudge@@@@6B@")
extern "C" const void *const vtbl_00C02A5C[];  // ??_7?$DLListClass@USmudgeSet@@@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C02A5C=??_7?$DLListClass@USmudgeSet@@@@6B@")
extern "C" const void *const vtbl_00C1980C[];  // ??_7GameSpyPeerMessageQueueInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1980C=??_7GameSpyPeerMessageQueueInterface@@6B@")
extern "C" const void *const vtbl_00C363B8[];  // ??_7Mem04@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C363B8=??_7Mem04@@6B@")
extern "C" const void *const vtbl_00C3962C[];  // ??_7Rva0045EF90Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3962C=??_7Rva0045EF90Base@@6B@")
extern "C" const void *const vtbl_00C42518[];  // ??_7SpawnBehaviorInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C42518=??_7SpawnBehaviorInterface@@6B@")
extern "C" const void *const vtbl_00C62888[];  // ??_7BaseA@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C62888=??_7BaseA@@6B@")
extern "C" const void *const vtbl_00C63F9C[];  // ??_7Rva00506B1B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C63F9C=??_7Rva00506B1B@@6B@")
extern "C" const void *const vtbl_00C6E350[];  // ??_7Rva0057E3DBBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E350=??_7Rva0057E3DBBase@@6B@")
extern "C" const void *const vtbl_00C6E360[];  // ??_7Rva00575125Second@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E360=??_7Rva00575125Second@@6B@")
extern "C" const void *const vtbl_00C6E5B4[];  // ??_7Rva00575383@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E5B4=??_7Rva00575383@@6B@")
extern "C" const void *const vtbl_00C70A5C[];  // ??_7Rva0059675ABase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C70A5C=??_7Rva0059675ABase@@6B@")
extern "C" const void *const vtbl_00C70B80[];  // ??_7Rva005DAA36@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C70B80=??_7Rva005DAA36@@6B@")
extern "C" const void *const vtbl_00C743B8[];  // ??_7Rva005C18F0Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C743B8=??_7Rva005C18F0Base@@6B@")
extern "C" const void *const vtbl_00C74DB8[];  // ??_7Rva005CBA04@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C74DB8=??_7Rva005CBA04@@6B@")
extern "C" const void *const vtbl_00C75C38[];  // ??_7Rva005D6FCC@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75C38=??_7Rva005D6FCC@@6B@")
extern "C" const void *const vtbl_00C767D4[];  // ??_7Rva005DBCD1@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C767D4=??_7Rva005DBCD1@@6B@")
extern "C" const void *const vtbl_00C77E28[];  // ??_7Rva005E67FE@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C77E28=??_7Rva005E67FE@@6B@")
extern "C" const void *const vtbl_00C77E7C[];  // ??_7Rva005CCC07Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C77E7C=??_7Rva005CCC07Base@@6B@")
extern "C" const void *const vtbl_00C77F44[];  // ??_7Rva002BA8F1Listener@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C77F44=??_7Rva002BA8F1Listener@@6B@")
extern "C" const void *const vtbl_00C79544[];  // ??_7Rva005E4AE2Listener@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C79544=??_7Rva005E4AE2Listener@@6B@")
extern "C" const void *const vtbl_00C7B6AC[];  // ??_7ThreadClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7B6AC=??_7ThreadClass@@6B@")
class Rva00238D97DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00238D97DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BED658);
}

class Rva002B2294DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002B2294DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C77F44);
}

class Rva0057428CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057428CDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E350);
}

class Rva00574293DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00574293DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E360);
}

class Rva0057A23CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A23CDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C42518);
}

class Rva005E3947DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005E3947DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C79544);
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
	m_value = ((unsigned int)vtbl_00BC745C);
}

class Rva000E14BDDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000E14BDDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC6F24);
}

class Rva00104D73DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00104D73DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BCF7E8);
}

class Rva00108B4DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00108B4DDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BCEFA0);
}

class Rva0010EFCDDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0010EFCDDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC5128);
}

class Rva00270158DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00270158DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BFAD38);
}

class Rva002A983DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002A983DDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BFDC30);
}

class Rva002D24EFDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002D24EFDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C02A58);
}

class Rva002D2507DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002D2507DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C02A5C);
}

class Rva0030D353DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0030D353DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C089EC);
}

class Rva00388845DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00388845DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C1980C);
}

class Rva003F3F7CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva003F3F7CDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C3702C);
}

class Rva003F7BC5DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva003F7BC5DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C37298);
}

class Rva004102A4DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004102A4DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C3962C);
}

class Rva004CEE78DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004CEE78DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C60130);
}

class Rva004E1416DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004E1416DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C618CC);
}

class Rva00506B28DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00506B28DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C63F9C);
}

class Rva0054E796DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0054E796DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6A894);
}

class Rva00596686DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00596686DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C70A5C);
}

class Rva00019EC0DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00019EC0DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BBC8D4);
}

class Rva00035780DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00035780DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BE2B78);
}

class Rva0005CF86BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CF86BDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C75290);
}

class Rva0005D23FEDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D23FEDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C078DC);
}

class Rva0006C5930DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0006C5930DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BBE7EC);
}

class Rva000610480DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000610480DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C7B6AC);
}

class Rva0005F686ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005F686ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BFBCBC);
}

class Rva0005E6810DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E6810DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C77E28);
}

class Rva0005E211FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E211FDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C77E7C);
}

class Rva0005E186ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E186ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E330);
}

class Rva0005DB82BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005DB82BDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C767D4);
}

class Rva000575395DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000575395DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E5B4);
}

class Rva0005277B3DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005277B3DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C4EF80);
}

class Rva0004EA016DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0004EA016DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C62888);
}

class Rva0004E84A4DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0004E84A4DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC6F20);
}

class Rva00049C38ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00049C38ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC26E0);
}

class Rva000429191DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000429191DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BDBA74);
}

class Rva000419B8DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000419B8DDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BBE7EC);
}

class Rva0005D6FDEDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D6FDEDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C75C38);
}

class Rva0005D2EA1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D2EA1DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BE2B78);
}

class Rva00078274DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00078274DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC6778);
}
class Rva0005CB9F3DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CB9F3DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C74DB8);
}
class Rva0005C1872DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005C1872DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C743B8);
}
class Rva0005970E6DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005970E6DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C70B80);
}
class Rva00057C51EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00057C51EDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C363B8);
}
class Rva00057571CDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00057571CDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E60C);
}
class Rva00028562EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00028562EDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BFB698);
}
class Rva000225A55DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000225A55DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BE714C);
}

class Rva00203611DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00203611DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BE3990);
}

class Rva00576456DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00576456DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E788);
}
