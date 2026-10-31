// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /Ireference/shims/bfme2_dockupdate /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/shims/dockupdate /Ireference/open-bfme-1/inputs/reference/shims/moduledata /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /Ireference/shims/sweep -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Update/DockUpdate
// stlport
// ?update@DockUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00589F09 258B. DockUpdate::update via rowed vector bool operator[] 0x0006BE1F plus findObjectByID 0x00049DC5 plus overlap 0x00263546 plus bitset 0x0028F59A plus clear 0x001E42F2. Donor open-bfme-1 DockUpdateUpdateBfme.cpp plus ZH DockUpdate.cpp. Caller 0x004A111E.
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/Debug.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/DockUpdate.h"

struct DockUpdateTemplateView
{
	unsigned char m_pad[0x108];
	unsigned int m_kind0;
	unsigned char m_pad2[6];
	unsigned char m_supply;
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
private:
	int m_mask[19];
};

class DockUpdateObjectView
{
public:
	void *m_vft;
	DockUpdateTemplateView *m_template;
	unsigned char m_pad08[0x10c - 8];
	Rva00263546 m_flags;
};

// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

struct Rva0028F59A
{
public:
	Rva0028F59A(int unused, int bit);
	unsigned int m_bits[19]; // +0x00
};

class Rva001E42F2
{
public:
	void rva001E42F2(const int *x);
};

UpdateSleepTime DockUpdate::update()
{
	ObjectID positionIndex = m_activeDocker;
	if (positionIndex == INVALID_ID && !m_dockCrippled)
	{
		for (UnsignedInt i = 0; i < m_approachPositionReached.size(); ++i)
		{
			if (m_approachPositionReached[i])
			{
				m_activeDocker = m_approachPositionOwners[i];
				return UPDATE_SLEEP_NONE;
			}
		}
	}
	else
	{
		DockUpdateObjectView *object = (DockUpdateObjectView *)getObject();
		if ((object->m_template->m_supply & 0x40) != 0)
		{
			DockUpdateObjectView *docker = (DockUpdateObjectView *)TheGameLogic->findObjectByID(positionIndex);
			if (docker != 0 && (docker->m_template->m_kind0 & 0x4000) != 0 && (docker->m_template->m_kind0 & 0x10000) != 0)
			{
				Rva00263546 test;
				memset(&test, 0, 0x4c);
				((unsigned char *)&test)[10] |= 4;
				if (test.rva00263546(&docker->m_flags))
				{
					((Rva001E42F2 *)docker)->rva001E42F2((const int *)&Rva0028F59A(0, 0x3d));
				}
			}
		}
	}
	return UPDATE_SLEEP_NONE;
}
