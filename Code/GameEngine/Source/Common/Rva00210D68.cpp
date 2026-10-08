// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// LivingWorldManager::SetUpRegionEffectsManager, retail 0x00210D68, 78B
// (WorldBuilder name, LivingWorldManager.cpp lines 495..503: release the old
// +0x268 manager, look the campaign's one up by name, store and start it).
// Evidence: __thiscall (reads ecx first into esi); clears +0x268 via rowed
// 0x003EF1B8 then AND-zero; chains g_009FEF10[+0xB0][+8] with null check;
// looks up key at +0x54 through rowed 0x003EF328 with table at g_00E02E60;
// stores result at +0x268 and tail-jmps to rowed 0x003EF2E0. Neighbour TUs
// Disp32DwordFieldClearers.cpp and Rva00210DC9Get.cpp both use /O1.
// No fallback paths.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class AsciiString;

class Rva003EF14A {
public:
	void rva003EF1B8();
};

class Rva003EF328 {
public:
	void *rva003EF328(const AsciiString *key);
};

class Rva003EF2E0 {
public:
	void rva003EF2E0();
};

struct Rva00210D68KeyHolder {
	char m_pad[0x54];
	char m_keyBytes[4];
};

struct Rva00210D68Mid {
	char m_pad[8];
	Rva00210D68KeyHolder *m_keyHolder;
};

class Rva002BA8F1Logic {
public:
	char m_pad[0xB0];
	Rva00210D68Mid *m_mid;
};

extern Rva003EF328 *g_00E02E60;

class LivingWorldManager {
public:
	void SetUpRegionEffectsManager();
private:
	char m_pad[0x268];
	Rva003EF14A *m_ptr268;
};

void LivingWorldManager::SetUpRegionEffectsManager()
{
	if (m_ptr268) {
		m_ptr268->rva003EF1B8();
		m_ptr268 = 0;
	}
	Rva00210D68KeyHolder *holder = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_mid->m_keyHolder;
	if (!holder)
		return;
	void *found = g_00E02E60->rva003EF328((const AsciiString *)((char *)holder + 0x54));
	m_ptr268 = (Rva003EF14A *)found;
	if (!found)
		return;
	((Rva003EF2E0 *)found)->rva003EF2E0();
}
