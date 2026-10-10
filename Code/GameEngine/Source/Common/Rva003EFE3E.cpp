// cl: /MD
// ?rva003EFE3E@Rva003EFE3E@@QAEXH@Z, retail 0x003EFE3E, 37 bytes.
// Store int at +0x140, if global g_009FE1C8->m_268 non-null call its
// LivingWorldRegionEffectsManager::SyncRegion with this as int (pin takes int). Evidence: rowed
// pin 0x003EF08B, callers 0x0057DC8D 0x0057DCC6 0x0057DD25, prev/next /O1 /MD.
class LivingWorldRegionEffectsManager
{
public:
	void SyncRegion(int value);
};

class LivingWorldManager
{
public:
	char m_pad[0x268];
	LivingWorldRegionEffectsManager *m_268;
};

// 0x009FE1C8 under its data-ledger primary name (defined in Rva003FD7CEParse.cpp).
extern LivingWorldManager *TheLivingWorldManager;

class Rva003EFE3E
{
public:
	void rva003EFE3E(int value);
private:
	char m_pad[0x140];
	int m_140;
};

void Rva003EFE3E::rva003EFE3E(int value)
{
	m_140 = value;
	LivingWorldRegionEffectsManager *obj = TheLivingWorldManager->m_268;
	if (!obj)
		return;
	obj->SyncRegion((int)this);
}
