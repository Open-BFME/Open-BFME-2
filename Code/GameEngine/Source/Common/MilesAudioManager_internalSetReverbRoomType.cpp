// cl: /DNDEBUG /MD
// ?internalSetReverbRoomType@MilesAudioManager@@QAEXH@Z @ 0x000512C4 143B.
// WorldBuilder 0x0078DC90 names it (MilesAudioManager.cpp:6327);
// the full retail body shares its LOD gate, provider layout, AIL calls
// and reverb-enabled/dirty byte updates at +0x6A7/+0x6A8.
#include "../../Include/Common/GameLODManager.h"
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_room_type(int room, int unk);
extern "C" __declspec(dllimport) void __stdcall AIL_set_digital_master_room_type(void *driver, int unk);

#include "../../../GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h"

void MilesAudioManager::internalSetReverbRoomType(int a)
{
	int edi = a;
	if (edi != 0)
	{
		if (m_678 != 0)
			edi = 0;
		if (edi != 0)
		{
			GameLODManager *mgr = TheGameLODManager;
			if (mgr != 0)
			{
				int idx = mgr->m_1770;
				if (idx >= 0 && idx <= 2)
				{
					if (mgr->audioInfo[idx].allowReverb == 0)
						edi = 0;
				}
			}
		}
	}
	int cur = m_selectedProvider;
	if (cur != -1)
	{
		AIL_set_3D_room_type(m_provider3D[cur].id, edi);
		AIL_set_digital_master_room_type(m_digitalHandle, edi);
	}
	if (edi == 0)
	{
		if (m_6A7 != 0)
		{
			m_6A7 = 0;
			m_6A8 = 1;
		}
	}
	else
	{
		m_6A7 = 1;
		m_6A8 = 1;
	}
}
