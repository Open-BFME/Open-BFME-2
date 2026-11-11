// cl: /MD
// ??1RegionDetailsTerritoryMovieClip@StrategicHUD@@UAE@XZ @0x005F1CE8 14B (was Rva005F1CE8): virtual dtor sets vtable g_00C79138 then tail-jmps to rowed holder clear 0x005F1B90.
// Evidence: vtable store plus add ecx 4 plus jmp to rowed 0x005F1B90; caller deleting dtor 0x005F1D2B plus thunk 0x005E3585.
class Rva005F1B90
{
public:
	void rva005F1B90();
private:
	void *m_00;
};
extern const void *const g_00C79138[];
// Vtable 0x00C79138 is the one RegionDetailsTerritoryMovieClip's ctor
// 0x005F207C stores, so this is that clip's destructor; its +4 member is the
// ctor's Impl holder.
namespace StrategicHUD {
class RegionDetailsTerritoryMovieClip
{
public:
	__declspec(noinline) virtual ~RegionDetailsTerritoryMovieClip();
private:
	Rva005F1B90 m_04;
};
}

StrategicHUD::RegionDetailsTerritoryMovieClip::~RegionDetailsTerritoryMovieClip()
{
	m_04.rva005F1B90();
}

// Native005E3585 five-byte JMP to the owned provider; address-derived dtor
// spelling is the existing deleting-caller pin, original class unknown.
#include "../../Include/Common/Rva005E3585.h"
Rva005E3585::~Rva005E3585()
{
    reinterpret_cast<StrategicHUD::RegionDetailsTerritoryMovieClip *>(this)->StrategicHUD::RegionDetailsTerritoryMovieClip::~RegionDetailsTerritoryMovieClip();
}
