// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B04: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove.
//
//   wrapper     dtor        vtable#slot
//   0x001FF9E4  0x001FF909  0x00BE25B4#0
//   0x001FFE77  0x001FFE93  0x00BE25EC#0
//   0x00200E79  0x00200E95  0x00BE2BA4#0   (WaterTransparencySetting, Water.h; emitted by INI/WaterTransparencySettingCtor.cpp)
//   0x0020180F  0x0020182B  0x00BE3070#0
//   0x002035F5  0x00203EBA  0x00BD3B54#0
//   0x0020D9D0  0x0020D9EC  0x00BE3FF4#0
//   0x0020E6DF  0x0020E205  0x00BE4334#1
//   0x00210C17  0x00210B38  0x00BE4358#0
//   0x00211121  0x0021113D  0x00BE5118#0
//   0x00216DA0  0x00216BF5  0x00BE59E4#0
//   0x002201B9  0x0021FFEE  0x00BE648C#0
//   0x00224F50  0x00224A90  0x00BE6E80#0
//   0x00226317  0x00225A50  0x00BE70B0#0
//   0x0022DA4A  0x002E0427  0x00BE7628#0
//   0x0022DE4F  0x00413A24  0x00BE7660#0
//   0x00237CFD  0x002376CC  0x00BED1C4#0
//   0x0023BDBB  0x0023AE08  0x00BED850#0
//   0x0023FCEA  0x0023FD06  0x00BEDC94#0

#include "../../Include/GameClient/Water.h"

struct EmitVtableTag;

class Rva001FF909
{
public:
	Rva001FF909(EmitVtableTag *);
public:
	virtual ~Rva001FF909();
};

// ?<Rva001FF909::Rva001FF909> absent-from-retail
Rva001FF909::Rva001FF909(EmitVtableTag *)
{
}

class Rva001FFE93
{
public:
	Rva001FFE93(EmitVtableTag *);
public:
	virtual ~Rva001FFE93();
};

// ?<Rva001FFE93::Rva001FFE93> absent-from-retail
Rva001FFE93::Rva001FFE93(EmitVtableTag *)
{
}

class WeatherSetting
{
public:
	WeatherSetting(EmitVtableTag *);
public:
	virtual ~WeatherSetting();
};

// ?<WeatherSetting::WeatherSetting> absent-from-retail
WeatherSetting::WeatherSetting(EmitVtableTag *)
{
}

class Rva00203EBA
{
public:
	Rva00203EBA(EmitVtableTag *);
public:
	virtual ~Rva00203EBA();
};

// ?<Rva00203EBA::Rva00203EBA> absent-from-retail
Rva00203EBA::Rva00203EBA(EmitVtableTag *)
{
}

class Rva0020D9EC
{
public:
	Rva0020D9EC(EmitVtableTag *);
public:
	virtual ~Rva0020D9EC();
};

// ?<Rva0020D9EC::Rva0020D9EC> absent-from-retail
Rva0020D9EC::Rva0020D9EC(EmitVtableTag *)
{
}

// LargeGroupAudio now emits its own deleting wrapper and -0xC thunk.

#include "../../Include/Common/RegionArmyComparatorView.h"

// ?<Rva0020E205::Rva0020E205> absent-from-retail
Rva0020E205::Rva0020E205(EmitVtableTag *)
{
}

class LivingWorldRegionManager
{
public:
	LivingWorldRegionManager(EmitVtableTag *);
public:
	virtual ~LivingWorldRegionManager();
};

// ?<LivingWorldRegionManager::LivingWorldRegionManager> absent-from-retail
LivingWorldRegionManager::LivingWorldRegionManager(EmitVtableTag *)
{
}

class Rva0021113D
{
public:
	Rva0021113D(EmitVtableTag *);
public:
	virtual ~Rva0021113D();
};

// ?<Rva0021113D::Rva0021113D> absent-from-retail
Rva0021113D::Rva0021113D(EmitVtableTag *)
{
}

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva00216BF5
{
public:
	Rva00216BF5(EmitVtableTag *);
public:
	virtual ~Rva00216BF5();
};

// ?<Rva00216BF5::Rva00216BF5> absent-from-retail
Rva00216BF5::Rva00216BF5(EmitVtableTag *)
{
}

class Rva00224A90
{
public:
	Rva00224A90(EmitVtableTag *);
public:
	virtual ~Rva00224A90();
};

// ?<Rva00224A90::Rva00224A90> absent-from-retail
Rva00224A90::Rva00224A90(EmitVtableTag *)
{
}

class Rva00225A50
{
public:
	Rva00225A50(EmitVtableTag *);
public:
	virtual ~Rva00225A50();
};

// ?<Rva00225A50::Rva00225A50> absent-from-retail
Rva00225A50::Rva00225A50(EmitVtableTag *)
{
}

class Rva002E0427
{
public:
	Rva002E0427(EmitVtableTag *);
public:
	virtual ~Rva002E0427();
};

// ?<Rva002E0427::Rva002E0427> absent-from-retail
Rva002E0427::Rva002E0427(EmitVtableTag *)
{
}

class Rva00413A24
{
public:
	Rva00413A24(EmitVtableTag *);
public:
	virtual ~Rva00413A24();
};

// ?<Rva00413A24::Rva00413A24> absent-from-retail
Rva00413A24::Rva00413A24(EmitVtableTag *)
{
}

// GameClient's complete destructor uses the same two bases and +0xC thunk.
class Rva0023AE08 : public SubsystemInterface, public Snapshot
{
public:
	Rva0023AE08(EmitVtableTag *);
public:
	virtual ~Rva0023AE08();
};

// ?<Rva0023AE08::Rva0023AE08> absent-from-retail
Rva0023AE08::Rva0023AE08(EmitVtableTag *)
{
}

class Rva0023FD06
{
public:
	Rva0023FD06(EmitVtableTag *);
public:
	virtual ~Rva0023FD06();
	virtual int rva0023FCD3(float a, int b);
};

// ?<Rva0023FD06::Rva0023FD06> absent-from-retail
Rva0023FD06::Rva0023FD06(EmitVtableTag *)
{
}

// Complete destructors the deleting destructors above call, by retail target.
#pragma comment(linker, "/alternatename:??1Rva00203EBA@@UAE@XZ=??1FunctorNotSet@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0020D9EC@@UAE@XZ=??1Rva0020DXXX@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva00224A90@@UAE@XZ=??1AptPlayer@@UAE@XZ")
