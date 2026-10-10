// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
 bool rva0020E4C8();

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

class LivingWorldLogic {public:void AutoResolveBattle(int);};
extern LivingWorldLogic *TheLivingWorldLogic;
// Native0020E4C8..0020E501 complete57 RET0; WB B56850/134 supplies
// the restart flag. AutoResolveBattle mutates the pending vector, so restart
// directly after a zero-count battle; do not compare its invalidated iterator
// with the new end. The returned flag records whether any battle was handled.
// Both callees have whole providers; same vector14/18 as SelectPendingBattle.
bool LivingWorldRegionManager::rva0020E4C8()
{
 bool changed=false;
 bool restart;
 do {
  restart=false;
  for(LivingWorldBattle **it=m_begin;it!=m_end;++it) {
   LivingWorldBattle *battle=*it;
   if(battle->rva003F4831()==0) {
    TheLivingWorldLogic->AutoResolveBattle((int)battle);
    restart=true;
    changed=true;
    break;
   }
  }
 } while(restart);
 return changed;
}
