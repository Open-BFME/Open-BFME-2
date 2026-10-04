// The members of the Disp0DwordImmSetters.cpp family whose immediate is an image
// address no unit defines yet (mostly vftables), split out so the rest of the
// family links; each moves back once its target has a definition to name.
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
extern "C" const void *const vtbl_00C601DC[];  // ??_7Rva004D376A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C601DC=??_7Rva004D376A@@6B@")

extern "C" const void *const vtbl_00BCF7E8[];  // ??_7Rva00104DB0Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCF7E8=??_7Rva00104DB0Base@@6B@")

extern "C" const void *const vtbl_00BC5128[];  // ??_7Rva001DA2D5Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC5128=??_7Rva001DA2D5Base@@6B@")

extern "C" const void *const vtbl_00BC745C[];  // ??_7Rva000851F3@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC745C=??_7Rva000851F3@@6B@")
extern "C" const void *const vtbl_00C6B090[];  // ??_7Rva00552C0FBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6B090=??_7Rva00552C0FBase@@6B@")

extern "C" const void *const vtbl_00BC0990[];  // folded, 2 classes; via ??_7DebugIOConBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC0990=??_7DebugIOConBase@@6B@")
extern "C" const void *const vtbl_00BC650C[];  // folded, 4 classes; via ??_7BfmeBaseVVE@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC650C=??_7BfmeBaseVVE@@6B@")
extern "C" const void *const vtbl_00BC6F20[];  // folded, 7 classes; via ??_7Rva0007DF07@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")
extern "C" const void *const vtbl_00BCEF94[];  // folded, 3 classes; via ??_7HashableClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCEF94=??_7HashableClass@@6B@")
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
extern "C" const void *const vtbl_00C3C970[];  // ??_7Rva004318C6@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3C970=??_7Rva004318C6@@6B@")
extern "C" const void *const vtbl_00C6A894[];  // ??_7Rva0054F434Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6A894=??_7Rva0054F434Base@@6B@")
extern "C" const void *const vtbl_00C6E788[];  // ??_7Listener00576C4B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E788=??_7Listener00576C4B@@6B@")
extern "C" const void *const vtbl_00C72B74[];  // ??_7Rva005B253F@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C72B74=??_7Rva005B253F@@6B@")
extern "C" const void *const vtbl_00C75290[];  // ??_7Rva005CF872@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75290=??_7Rva005CF872@@6B@")

extern "C" const void *const vtbl_00C6E330[];  // ??_7CreateAHeroData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E330=??_7CreateAHeroData@@6B@")

extern "C" const void *const vtbl_00BBC8D4[];  // ??_7_Messages@_STL@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBC8D4=??_7_Messages@_STL@@6B@")
extern "C" const void *const vtbl_00BBE7EC[];  // ??_7DebugCmdInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBE7EC=??_7DebugCmdInterface@@6B@")
extern "C" const void *const vtbl_00BC6730[];  // ??_7FileClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6730=??_7FileClass@@6B@")
extern "C" const void *const vtbl_00BC6778[];  // ??_7FileFactoryClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6778=??_7FileFactoryClass@@6B@")
extern "C" const void *const vtbl_00BC6F24[];  // ??_7Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F24=??_7Base@@6B@")
extern "C" const void *const vtbl_00BC93C8[];  // ??_7Rva00782CB0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC93C8=??_7Rva00782CB0@@6B@")
extern "C" const void *const vtbl_00BD4E24[];  // ??_7StaticSortListClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD4E24=??_7StaticSortListClass@@6B@")
extern "C" const void *const vtbl_00BD6CB4[];  // ??_7BFME2MotionChannel@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD6CB4=??_7BFME2MotionChannel@@6B@")
extern "C" const void *const vtbl_00BDBC10[];  // ??_7Rva001DBAA4@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BDBC10=??_7Rva001DBAA4@@6B@")
extern "C" const void *const vtbl_00BE09D0[];  // ??_7ObjectCreationNugget@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE09D0=??_7ObjectCreationNugget@@6B@")
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
extern "C" const void *const vtbl_00CE1E14[];  // ??_7Rva00CE1E14Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CE1E14=??_7Rva00CE1E14Base@@6B@")
extern "C" const void *const vtbl_00CEFD60[];  // ??_7CullSystemClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CEFD60=??_7CullSystemClass@@6B@")

class Rva002B228DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002B228DDwordImmSetter::apply()
{
	m_value = 0x00BFDF8C;
}

class Rva0007DEA1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DEA1DwordImmSetter::apply()
{
	m_value = 0x00BC6EEC;
}

class Rva0007DEA8DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DEA8DwordImmSetter::apply()
{
	m_value = 0x00BC6F04;
}

class Rva0007DE9ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DE9ADwordImmSetter::apply()
{
	m_value = 0x00BC6EC0;
}

class Rva004EDFF8DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EDFF8DwordImmSetter::apply()
{
	m_value = 0x00C62A14;
}

class Rva004EDFFFDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EDFFFDwordImmSetter::apply()
{
	m_value = 0x00C62A20;
}

class Rva004EE006DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EE006DwordImmSetter::apply()
{
	m_value = 0x00BC6F34;
}

class Rva0057A235DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A235DwordImmSetter::apply()
{
	m_value = 0x00C6EE20;
}

class Rva0057A243DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A243DwordImmSetter::apply()
{
	m_value = 0x00C6EE28;
}

class Rva005CF843DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005CF843DwordImmSetter::apply()
{
	m_value = 0x00C75284;
}

class Rva005CF84ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005CF84ADwordImmSetter::apply()
{
	m_value = 0x00C7528C;
}

class Rva005E394EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005E394EDwordImmSetter::apply()
{
	m_value = 0x00C77BE8;
}

class Rva000723C0DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000723C0DwordImmSetter::apply()
{
	m_value = 0x00BC64B0;
}

class Rva0011647BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0011647BDwordImmSetter::apply()
{
	m_value = 0x00BCFB24;
}

class Rva0020E205DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0020E205DwordImmSetter::apply()
{
	m_value = 0x00BE4318;
}

class Rva00210CC5DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00210CC5DwordImmSetter::apply()
{
	m_value = 0x00BE5114;
}

class Rva002BEDA4DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002BEDA4DwordImmSetter::apply()
{
	m_value = 0x00BFE4EC;
}

class Rva002D3354DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002D3354DwordImmSetter::apply()
{
	m_value = 0x00C02A84;
}

class Rva00330440DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00330440DwordImmSetter::apply()
{
	m_value = 0x00C0DB24;
}

class Rva0037F4C9DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0037F4C9DwordImmSetter::apply()
{
	m_value = 0x00C18DFC;
}

class Rva00381D71DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00381D71DwordImmSetter::apply()
{
	m_value = 0x00C19230;
}

class Rva003916A4DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva003916A4DwordImmSetter::apply()
{
	m_value = 0x00C1A074;
}

class Rva004059ACDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004059ACDwordImmSetter::apply()
{
	m_value = 0x00BE5838;
}

class Rva00468A3FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00468A3FDwordImmSetter::apply()
{
	m_value = 0x00C44890;
}

class Rva004BDA05DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004BDA05DwordImmSetter::apply()
{
	m_value = 0x00C5AEB0;
}

class Rva004E14E1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004E14E1DwordImmSetter::apply()
{
	m_value = 0x00C619A0;
}

class Rva000A8EEFDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000A8EEFDwordImmSetter::apply()
{
	m_value = 0x00BC93DC;
}

class Rva0052AF77DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0052AF77DwordImmSetter::apply()
{
	m_value = 0x00C37E18;
}

class Rva005676F4DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005676F4DwordImmSetter::apply()
{
	m_value = 0x00C6CE84;
}

class Rva0059EB3ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0059EB3ADwordImmSetter::apply()
{
	m_value = 0x00C711BC;
}

class Rva000141C30DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000141C30DwordImmSetter::apply()
{
	m_value = 0x00BD3338;
}

class Rva0005CF81FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CF81FDwordImmSetter::apply()
{
	m_value = 0x00C75278;
}

class Rva00066D580DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00066D580DwordImmSetter::apply()
{
	m_value = 0x00CE3B38;
}

class Rva000604A68DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000604A68DwordImmSetter::apply()
{
	m_value = 0x00C7A974;
}

class Rva00060263EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00060263EDwordImmSetter::apply()
{
	m_value = 0x00C7A84C;
}

class Rva0005F3EE3DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005F3EE3DwordImmSetter::apply()
{
	m_value = 0x00C79428;
}

class Rva0005EA2ABDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005EA2ABDwordImmSetter::apply()
{
	m_value = 0x00C780F4;
}

class Rva0005E57C9DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E57C9DwordImmSetter::apply()
{
	m_value = 0x00C77D30;
}

class Rva000550576DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000550576DwordImmSetter::apply()
{
	m_value = 0x00C6ABC0;
}

class Rva00054F91BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00054F91BDwordImmSetter::apply()
{
	m_value = 0x00C6AB10;
}

class Rva000549C6DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000549C6DDwordImmSetter::apply()
{
	m_value = 0x00C6A68C;
}

class Rva00052B588DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00052B588DwordImmSetter::apply()
{
	m_value = 0x00C686BC;
}

class Rva000524F5ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000524F5ADwordImmSetter::apply()
{
	m_value = 0x00C67E3C;
}

class Rva0005D387BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D387BDwordImmSetter::apply()
{
	m_value = 0x00C75908;
}

class Rva0005D10D6DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D10D6DwordImmSetter::apply()
{
	m_value = 0x00C7559C;
}

class Rva0007461FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007461FDwordImmSetter::apply()
{
	m_value = 0x00BC65A8;
}

class Rva0005CE8EEDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CE8EEDwordImmSetter::apply()
{
	m_value = 0x00C751A8;
}
class Rva000579656DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000579656DwordImmSetter::apply()
{
	m_value = 0x00BFBC9C;
}
class Rva000574265DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000574265DwordImmSetter::apply()
{
	m_value = 0x00C6E344;
}

class Rva00090771DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00090771DwordImmSetter::apply()
{
	m_value = 0x00BC7E94;
}
class Rva0002B221ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0002B221ADwordImmSetter::apply()
{
	m_value = 0x00BFDF68;
}
class Rva000A8E95DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000A8E95DwordImmSetter::apply()
{
	m_value = 0x00BC93BC;
}

class Rva0010846EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0010846EDwordImmSetter::apply()
{
	m_value = 0x00BCF994;
}

class Rva00108650DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00108650DwordImmSetter::apply()
{
	m_value = 0x00BCEF9C;
}

class Rva005753E2DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005753E2DwordImmSetter::apply()
{
	m_value = 0x00C6E5C4;
}

class Rva0057851BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057851BDwordImmSetter::apply()
{
	m_value = 0x00C79760;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva005D6FCC@@UAE@XZ=?apply@Rva0005D6FDEDwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva001DBAC3Base@@UAE@XZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00539926Base@@UAE@XZ=?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva001DBAC3@@UAE@XZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeDtorTVA@BfmeThingTVA@@QAEXXZ=?apply@Rva00065D180DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva00CE1E14Base@@UAE@XZ=?apply@Rva00065D180DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1BfmeModuleDataSnapshotBase@@UAE@XZ=?apply@Rva0011647BDwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1CountUpTransitionBase@@UAE@XZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeTailSF@BfmeThingSF@@QAEXXZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")
