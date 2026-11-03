// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Dump-lane range 5: null-gated twin init at 0x199FA5 (39B). Free cdecl
// function: returns false when the record's +0xC is null, otherwise runs
// two inits on it and returns true. Callee 0x15A800 reuses its rowed
// MeshMatDescClass name (second pin refused by gate); 0x15D5B0 restores the
// pass-0 state stored by MeshMatDescClass::Store_Pass0_State.

#include "../../../Libraries/Source/WWVegas/WW3D2/MeshMatDescClass.h"
class Rva00199FA5Rec
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

// ?rva00199FA5@@YA_NPAVRva00199FA5Rec@@@Z
bool rva00199FA5(Rva00199FA5Rec *p)
{
	if (p->m_0C == 0)
		return false;
	((MeshMatDescClass *)p)->Set_Single_Rva0015A800(0, 0);
	((MeshMatDescClass *)p)->Store_Pass0_State(false);
	return true;
}
