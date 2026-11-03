// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Frameless (/Oy via /O1) EH pair sharing the 0xB5D851 __EH_prolog head with
// the 5C8BB cluster (same guard over +0x9D4, same fs:[0] shell):
//  ?rva0005CA03@MilesAudioManager@@QAEXPAXMH@Z @0x0005CA03 114B,
//  ?rva0005CA75@MilesAudioManager@@QAEXH@Z @0x0005CA75 109B.
// 5CA03 voices owner[idx] at +0x12C stride 0x1C4 through pinned rva0005A3FA,
// then the pinned 789B rva0005BE59 setup with (slot, float, idx). 5CA75 pokes
// the +0x1B8 sub-object of the same stride (address folds to +0x2E4 base)
// through pinned rva00057B74, then rva0005BE59 with (slot, g_00BBB9AC -1.0f,
// TheEmptyString at 0xDE0878). The g_ spellings mirror the landed TUs that
// verified them. Address-derived names; identities unproven.
// The +0x1B8 member is the rowed tree-clear owner Rva00056CF8 (0x00057B74).
class Rva00056CF8
{
public:
	void rva00057B74();
private:
	char m_data[4];
};

struct Rva0005CAElem
{
	char m_pad00[0x1B8];
	Rva00056CF8 m_sub1B8;
	char m_pad1BC[0x1C4 - 0x1B8 - 4];
};

#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"

extern const float g_00BBB9AC;
extern unsigned int g_Va00DE0878;

class MilesAudioManager
{
public:
	class GlobalVolumeData;
	virtual void rva0005CA03(void *a, float b, int idx);
	virtual void rva0005CA75(int a);
	void rva0005BE59(void *a, float b, void *c);
private:
	char m_pad00[0x12C - sizeof(void *)];
	Rva0005CAElem m_arr12C[1];
	char m_padAfter[0x9D4 - 0x12C - 0x1C4];
	int m_mutex9D4;
};

class MilesAudioManager::GlobalVolumeData
{
public:
	void rva0005A3FA(void *a, float b);
};

void MilesAudioManager::rva0005CA03(void *a, float b, int idx)
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	((GlobalVolumeData *)&m_arr12C[idx])->rva0005A3FA(a, b);
	rva0005BE59(a, b, (void *)idx);
}

void MilesAudioManager::rva0005CA75(int a)
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	m_arr12C[a].m_sub1B8.rva00057B74();
	rva0005BE59(&g_Va00DE0878, g_00BBB9AC, (void *)a);
}
