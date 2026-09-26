// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// Opaque destructors deriving from FireWeaponWhenDeadBehavior (real base
// via the Zero Hour module header; the base destructor is defined in
// FireWeaponWhenDeadBehavior.cpp and only declared here so each tail-call
// resolves to the ledger address 0x0046089D instead of a same-TU
// definition). Each class below stores its own four vptrs (+0/+0x0C/+0x10/+0x18,
// DIR32 auto-patches) and tail-jumps to the base destructor. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor,
// landed one commit at a time.

#include "PreRTS.h"
#include "GameLogic/Module/FireWeaponWhenDeadBehavior.h"

class Rva004B362D : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B362D();
};

Rva004B362D::~Rva004B362D()
{
}

class Rva004B39FC : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B39FC();
};

Rva004B39FC::~Rva004B39FC()
{
}

class Rva004B3C0A : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B3C0A();
};

Rva004B3C0A::~Rva004B3C0A()
{
}

class Rva004B3D3B : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B3D3B();
};

Rva004B3D3B::~Rva004B3D3B()
{
}

class Rva004B46F9 : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B46F9();
};

Rva004B46F9::~Rva004B46F9()
{
}

class Rva004B48D3 : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B48D3();
};

Rva004B48D3::~Rva004B48D3()
{
}

class Rva004B4CDF : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B4CDF();
};

Rva004B4CDF::~Rva004B4CDF()
{
}

class Rva004B53DF : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B53DF();
};

Rva004B53DF::~Rva004B53DF()
{
}

class Rva004B55C8 : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B55C8();
};

Rva004B55C8::~Rva004B55C8()
{
}

class Rva004B568B : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B568B();
};

Rva004B568B::~Rva004B568B()
{
}

class Rva004B57CE : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B57CE();
};

Rva004B57CE::~Rva004B57CE()
{
}

class Rva004B6259 : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B6259();
};

Rva004B6259::~Rva004B6259()
{
}

class Rva004B63BD : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B63BD();
};

Rva004B63BD::~Rva004B63BD()
{
}

class Rva004B67DC : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B67DC();
};

Rva004B67DC::~Rva004B67DC()
{
}

class Rva004B79AD : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B79AD();
};

Rva004B79AD::~Rva004B79AD()
{
}

class Rva004B82A5 : public FireWeaponWhenDeadBehavior
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

class Rva004B5982 : public FireWeaponWhenDeadBehavior, public Rva004B5982_E
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

class Rva004B5D0B : public FireWeaponWhenDeadBehavior, public Rva004B5D0B_E
{
public:
	virtual ~Rva004B5D0B();
};

Rva004B5D0B::~Rva004B5D0B()
{
}

class Rva004B611C : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B611C();
};

Rva004B611C::~Rva004B611C()
{
}

class Rva004B66B3 : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~Rva004B66B3();
};

Rva004B66B3::~Rva004B66B3()
{
}

class CommandPointsUpgrade : public FireWeaponWhenDeadBehavior
{
public:
	virtual ~CommandPointsUpgrade();
};

CommandPointsUpgrade::~CommandPointsUpgrade()
{
}
