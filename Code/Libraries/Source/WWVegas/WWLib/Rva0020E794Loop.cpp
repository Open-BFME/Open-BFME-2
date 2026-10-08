// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?SelectPendingBattle@LivingWorldRegionManager@@QAEPAVLivingWorldBattle@@XZ, retail 0x0020E794, 41 bytes.
// Pointer scan at +0x14/+0x18 over LivingWorldBattle pointers via rowed 0x003F4831
// returning first element with positive count else NULL. Caller at 0x0020EC21.

class LivingWorldBattle
{
public:
	int rva003F4831();
};

class LivingWorldRegionManager
{
public:
	LivingWorldBattle *SelectPendingBattle();

private:
	unsigned char m_pad[0x14];
	LivingWorldBattle **m_begin;
	LivingWorldBattle **m_end;
};

LivingWorldBattle *LivingWorldRegionManager::SelectPendingBattle()
{
	LivingWorldBattle **begin = m_begin;
	LivingWorldBattle **end = m_end;
	for (; begin != end; ++begin) {
		LivingWorldBattle *elem = *begin;
		if (elem->rva003F4831() > 0)
			return elem;
	}
	return 0;
}
