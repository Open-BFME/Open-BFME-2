// cl: /O1 /arch:SSE /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "CombineHordeSpecialPowerModuleData" (addModule
// pairs the name with this factory); formerly misnamed AIUpdateInterface.
// Trial: ??0CombineHordeSpecialPowerModuleData@@QAE@XZ.
// Default ctor over opaque intermediate base 0x004930A0 (pinned); vtable
// plus one trailing float. Factory stub order names it.
#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

class CombineHordeSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	CombineHordeSpecialPowerModuleData();
	virtual ~CombineHordeSpecialPowerModuleData();

	float m_f7C;
};

// Stands in for retail's 100.0f literal (__real@42c80000, .rdata 0x007C292C), the
// default the constructor loads into +0x7C.
static float kF7C = 100.0f;

CombineHordeSpecialPowerModuleData::CombineHordeSpecialPowerModuleData()
	: SpecialPowerModuleData()
{
	m_f7C = kF7C;
}

// ??1CombineHordeSpecialPowerModuleData@@ present-unmatched
CombineHordeSpecialPowerModuleData::~CombineHordeSpecialPowerModuleData()
{
}
