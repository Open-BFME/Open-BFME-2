// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/shims/bfme2_riderchangecontain -Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Contain
// stlport
//
// ?isValidContainerFor@RiderChangeContain@@UAE_NPAVObject@@_N1@Z, retail
// 0x0047E520, 126 bytes: slot 38 of RiderChangeContain's +0x20 table
// (0x00847834 run), so `this` is the module +0x20 (module data at -0x1C, the
// owner at -0x18). Zero Hour's RiderChangeContain::isValidContainerFor: the
// base check is the rowed SiegeEngineContain-side 0x0047BA69 (address named;
// called on the same interface pointer, capacity not checked). BFME 2 returns
// that answer unchanged for a non-allied rider; for an ally it also needs the
// +0x140 slot clear and the rider's template to match one of the eight rider
// template names in the module data (+0x1B8, 0x18 apart).
// The +0x20 interface; its slot-38 base check is the rowed 0x0047BA69, named
// by address on this interface.
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"

#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/RiderChangeContain.h"

bool RiderChangeContain::isValidContainerFor(Object *rider, bool checkCapacity, bool testPath)
{
	//Don't check capacity because our rider will kick the other rider out!
	// The base takes the caller's test-path argument word as is (rowed with int parameters).
	bool valid = rva0047BA69(rider, 0, *(const int *)&testPath);
	if (m_object->getRelationship(rider) != ALLIES)
		return valid;
	if (valid && m_scuttledOnFrame == 0)
	{
		const RiderChangeContainModuleData *data = m_moduleData;
		for (int i = 0; i < 8; i++)
		{
			if (data->m_riders[i].m_templateName.isEmpty() == true)
				continue;
			const ThingTemplate *thing = TheThingFactory->findTemplate(data->m_riders[i].m_templateName);
			if (thing && thing->isEquivalentTo(rider->getTemplate()))
			{
				//We found a valid rider, so return true.
				return true;
			}
		}
	}
	return false;
}
