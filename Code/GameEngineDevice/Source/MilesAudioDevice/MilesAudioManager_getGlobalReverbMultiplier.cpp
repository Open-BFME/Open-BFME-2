// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?getGlobalReverbMultiplier@MilesAudioManager@@QAEMXZ @0x00052F4C 84B.
// Same this as createListener via provider count/selection at +0x9CC/+0x9D0
// plus provider id at +0x6D0 and flag at +0x6A7. Returns reverb level for
// the current 3D room type with 0..25 bounds. Table base at +0x10+0xC4.

extern "C" __declspec(dllimport) int __stdcall AIL_3D_room_type(unsigned int provider);

struct ReverbTable
{
	char m_pad[0xc4];
	float m_values[26];
};

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

float MilesAudioManager::getGlobalReverbMultiplier()
{
	unsigned int sel = m_selectedProvider;
	if (sel >= m_providerCount)
		return 0.0f;
	int room = AIL_3D_room_type(m_provider3D[sel].id);
	if (m_6A7 && room != -1)
	{
		if (room < 0 || (unsigned int)room >= 26)
			return 1.0f;
		return reinterpret_cast<ReverbTable *>(m_audioSettings)->m_values[room];
	}
	return 0.0f;
}
