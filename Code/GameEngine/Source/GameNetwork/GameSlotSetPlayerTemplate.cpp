// cl: /DNDEBUG /MD /EHsc
// stlport
// ?setPlayerTemplate@GameSlot@@QAEXH@Z @0x00400E33 (108B):
// GameSlot::setPlayerTemplate. BFME1 GameInfo.h donor (inline setPlayerTemplate
// with m_startPos clear when <= PLAYERTEMPLATE_MIN) with BFME2 deltas proven
// by retail: faction remap via map<int int> at ThePlayerTemplateStore+0x18
// (empty check at +0x1C; find rowed 0x388F63; miss falls back to begin->first)
// plus GlobalData byte flag at +0x9D4 bits 3 remapping -1 (RANDOM) to
// begin->first, and clearing both +0x10 (startPos) and +0x14 (bfme14) when
// <= -2 (OBSERVER). Layout is GameSlotSetState (color@C startPos@10 bfme14@14
// template@18 team@1C). Callers pass -2/-1 at 0x43EF13/0x43EF68 in 0x43EDB4
// adjust path and format PlayerTemplate=%d from +0x18 at 0x445622; 0x4018DC
// and 0x401C19 gate the call on the inlined getPlayerTemplateCount
// ([0xDFE0D0]+0x10-[0xDFE0D0]+0x0C)/0x1DC. No new pins.
#include <map>

typedef int Int;

class GameSlot
{
public:
	void setPlayerTemplate(Int playerTemplate);
private:
	void *m_vtable;
	Int m_state;
	unsigned char m_isAccepted;
	unsigned char m_hasMap;
	unsigned char m_isMuted;
	char m_pad0B;
	Int m_color;
	Int m_startPos;
	Int m_bfme14;
	Int m_playerTemplate;
	Int m_teamNumber;
};

class PlayerTemplateStore
{
public:
	char m_pad[0x18];
	_STL::map<int, int> m_map;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class GlobalData
{
public:
	char m_pad[0x9d4];
	unsigned char m_flag9D4;
};

extern class GlobalData *TheWritableGlobalData;

inline void GameSlot::setPlayerTemplate(Int playerTemplate)
{
	_STL::map<int, int> &map = ThePlayerTemplateStore->m_map;
	if (!map.empty()) {
		if (playerTemplate >= 0) {
			_STL::map<int, int>::iterator it = map.find(playerTemplate);
			if (it == map.end())
				playerTemplate = map.begin()->first;
		}
		if ((TheWritableGlobalData->m_flag9D4 & 3) != 0 && playerTemplate == -1)
			playerTemplate = map.begin()->first;
		m_playerTemplate = playerTemplate;
		if (playerTemplate <= -2) {
			m_startPos = -1;
			m_bfme14 = -1;
		}
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (GameSlot::*_bfmeInlineAnchor_GameSlotSetPlayerTemplate_0)(Int playerTemplate) = &GameSlot::setPlayerTemplate;
