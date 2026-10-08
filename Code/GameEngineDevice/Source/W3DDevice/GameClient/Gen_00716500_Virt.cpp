// cl: -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -DNDEBUG -DWIN32 -D_WINDOWS -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
#include "dx8wrapper.h"


// Retail 0x00716500. stdcall vtable slot 0x15C(self, arg), then increment a counter.

struct Gen_00716500_Obj;

struct Gen_00716500_Vtbl
{
	void *m_gap[0x15C / 4];
	void (__stdcall *call)(Gen_00716500_Obj *self, void *p);
};

struct Gen_00716500_Obj
{
	Gen_00716500_Vtbl *vtbl;
};

extern unsigned number_of_DX8_calls;	// 0x009EDA98, dx8wrapper.cpp's counter

// ?run_00716500@@YAXPAX@Z
void run_00716500(void *p)
{
	reinterpret_cast<Gen_00716500_Obj *>(DX8Wrapper::_Get_D3D_Device8())->vtbl->call(reinterpret_cast<Gen_00716500_Obj *>(DX8Wrapper::_Get_D3D_Device8()), p);
	++number_of_DX8_calls;
}
