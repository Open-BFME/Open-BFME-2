// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// Destructors of modules deriving from the verified UpgradeModule base
// at 0x0046089D (UpgradeModuleDtor.cpp). Retail restores four tables at
// +0/+0x0C/+0x10/+0x18 before calling the base. Derived identities remain
// opaque except where separately established; a shared destructor shape
// does not identify them. The former FireWeaponWhenDeadBehavior base name
// was refuted by that class's verified five-table UpdateModule ctor.

#include "../../../../Include/GameLogic/Module/UpgradeModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

// ?loadPostProcess@Rva004B4CDF@@MAEXXZ @0x004B4D05 (25B, slot 1 of primary
// vtable 0x00857C40) tail-jumps to 0x0058B03E, the ICF-shared empty
// ?loadPostProcess@UpgradeModule@@MAEXXZ (also UpdateModule's).
// Retail: if (byte at +0x20) ((Member10*)(this+0x10))->s10();
// UpgradeModule::loadPostProcess(). The indirect call is slot 10 (0x28) of the
// UpgradeMux-side vtable 0x00857BF8 (18 slots; per-derived slots 8/10 are
// 0x004B5101/0x004B5020 for this class). Primary slot layout (dtor/name/xfer/
// poolkey/empty) matches HijackerUpdate vtable 0x008525E4 whose slot 1 is the
// rowed ?loadPostProcess@HijackerUpdate@@MAEXXZ.
class Rva004B4CDFMember10
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
};

// BaseUpgrade's destructor 0x004B362D: its constructor 0x004B371C installs the
// same four tables. The class is BaseUpgrade.h's, so this unit's copies of its
// vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/BaseUpgrade.h"

BaseUpgrade::~BaseUpgrade()
{
}

// CommandSetUpgrade's destructor 0x004B39FC: its constructor 0x004B3AB2
// installs the same four tables. The class is CommandSetUpgrade.h's, so this
// unit's copies of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/CommandSetUpgrade.h"

CommandSetUpgrade::~CommandSetUpgrade()
{
}

// DelayedUpgrade's destructor 0x004B3C0A: its constructor 0x004B3C75 installs
// the same four tables. The class is DelayedUpgrade.h's, so this unit's copies
// of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/DelayedUpgrade.h"

DelayedUpgrade::~DelayedUpgrade()
{
}

class Rva004B3D3B : public UpgradeModule
{
public:
	virtual ~Rva004B3D3B();
};

Rva004B3D3B::~Rva004B3D3B()
{
}

// RadarUpgrade's destructor 0x004B46F9: its constructor 0x004B478E installs
// the same four tables. The class is RadarUpgrade.h's, so this unit's copies
// of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/RadarUpgrade.h"

RadarUpgrade::~RadarUpgrade()
{
}

// StatusBitsUpgrade's destructor 0x004B48D3: its constructor 0x004B4960
// installs the same four tables. The class is StatusBitsUpgrade.h's, so this
// unit's copies of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/StatusBitsUpgrade.h"

StatusBitsUpgrade::~StatusBitsUpgrade()
{
}

class Rva004B4CDF : public UpgradeModule
{
public:
	virtual ~Rva004B4CDF();
protected:
	virtual void loadPostProcess();
};

void Rva004B4CDF::loadPostProcess()
{
	// +0x20 is an unidentified bool past the 0x1C-byte UpgradeModule base
	// (UpgradeMux lives at +0x10 with its bool at +0x14). +0x10 is the UpgradeMux-side base whose vtable is
	// 0x00857BF8; v10 is slot 10 (0x28), retail target 0x004B5020.
	if (*reinterpret_cast<bool*>(reinterpret_cast<char*>(this) + 0x20))
		reinterpret_cast<Rva004B4CDFMember10*>(reinterpret_cast<char*>(this) + 0x10)->v10();
	UpgradeModule::loadPostProcess();
}

Rva004B4CDF::~Rva004B4CDF()
{
}

class Rva004B53DF : public UpgradeModule
{
public:
	virtual ~Rva004B53DF();
};

Rva004B53DF::~Rva004B53DF()
{
}

// WeaponBonusUpgrade's destructor 0x004B55C8: its constructor 0x004B5633
// installs the same four tables. The class is WeaponBonusUpgrade.h's, so this
// unit's copies of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/WeaponBonusUpgrade.h"

WeaponBonusUpgrade::~WeaponBonusUpgrade()
{
}

class Rva004B568B : public UpgradeModule
{
public:
	virtual ~Rva004B568B();
};

Rva004B568B::~Rva004B568B()
{
}

class Rva004B57CE : public UpgradeModule
{
public:
	virtual ~Rva004B57CE();
};

Rva004B57CE::~Rva004B57CE()
{
}

class Rva004B6259 : public UpgradeModule
{
public:
	virtual ~Rva004B6259();
};

Rva004B6259::~Rva004B6259()
{
}

// ModelConditionUpgrade's destructor 0x004B63BD: its constructor 0x004B64E5
// installs the same four tables. The class is ModelConditionUpgrade.h's, so this
// unit's copies of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/ModelConditionUpgrade.h"

ModelConditionUpgrade::~ModelConditionUpgrade()
{
}

// CastleUpgrade's destructor 0x004B67DC: its constructor 0x004B6869 installs
// the same four tables. The class is CastleUpgrade.h's, so this unit's copies
// of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/CastleUpgrade.h"

CastleUpgrade::~CastleUpgrade()
{
}

// TooltipUpgrade's destructor 0x004B79AD: its constructor 0x004B7A50 installs
// the same four tables. The class is TooltipUpgrade.h's, so this unit's copies
// of its vftables equal the constructor unit's.
#include "../../../../Include/GameLogic/Module/TooltipUpgrade.h"

TooltipUpgrade::~TooltipUpgrade()
{
}

class Rva004B82A5 : public UpgradeModule
{
public:
	virtual ~Rva004B82A5();
};

Rva004B82A5::~Rva004B82A5()
{
}

class Rva004B5982_E
{
public:
	virtual void fe();
};

class Rva004B5982 : public UpgradeModule, public Rva004B5982_E
{
public:
	virtual ~Rva004B5982();
};

Rva004B5982::~Rva004B5982()
{
}

class Rva004B5D0B_E
{
public:
	virtual void fe();
};

class Rva004B5D0B : public UpgradeModule, public Rva004B5D0B_E
{
public:
	virtual ~Rva004B5D0B();
};

Rva004B5D0B::~Rva004B5D0B()
{
}

class Rva004B611C : public UpgradeModule
{
public:
	virtual ~Rva004B611C();
};

Rva004B611C::~Rva004B611C()
{
}

class Rva004B66B3 : public UpgradeModule
{
public:
	virtual ~Rva004B66B3();
};

Rva004B66B3::~Rva004B66B3()
{
}

class CommandPointsUpgrade : public UpgradeModule
{
public:
	virtual ~CommandPointsUpgrade();
};

CommandPointsUpgrade::~CommandPointsUpgrade()
{
}

class Rva004B554FTarget
{
public:
	unsigned char m_pad[0x118];
	int m_val; // +0x118
};

class Rva004B554FHolder
{
public:
	int rva004B554F() const;

private:
	unsigned char m_pad[4];
	Rva004B554FTarget *m_ptr; // +4
};

int Rva004B554FHolder::rva004B554F() const
{
	int ret = 0;
	Rva004B554FTarget *p = m_ptr;
	if (p != 0)
		ret = p->m_val;
	return ret;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?fe@Rva004B5982_E@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?fe@Rva004B5D0B_E@@UAEXXZ=??1Coord2D@@QAE@XZ")
