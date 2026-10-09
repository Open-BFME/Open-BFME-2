// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// CampaignInGameUIResolveBattlesBehavior.cpp -- CampaignInGameUI's
// resolve-battles behaviour at its WorldBuilder home (WB names the click
// handler CampaignInGameUI::ResolveBattlesBehavior::Impl::OnMouseLeftClick,
// CampaignInGameUIResolveBattlesBehavior.cpp:89..117, WB 0x014C8410).
//
// Target facts (retail 0x005777A0, 152 bytes, ret 8): a click that is not a
// drag (the four-int region has no width or height) and is the first one
// (byte +0x0C) picks the point through the behaviour's viewer (+0x08; rowed
// 0x002C025A with kind 1), maps the picked object's key (+0x10) to a region
// index through TheLivingWorldManager's rowed reverse lookup 0x00212728, and
// asks the living-world region manager (TheLivingWorldLogic +0xB0) for that
// region's pending battle (rowed 0x0020E501). A battle marks the click taken
// and posts message 0x6B5 carrying the battle's +0x30 word. The second stack
// word is unused. WB's extra 0x6B6 branch (a global flag at +0x88 and the
// modifier mask 0x430) is absent from retail.
//
// The pick, lookup and parameter ABI follow the strategic twin
// StrategicInGameUI::ResolveBattlesBehavior::Impl 0x00576946
// (StrategicInGameUIResolveBattlesBehavior.cpp), which makes the same calls.

class Rva002C025AViewer
{
public:
	void *rva002C025A(void *point, unsigned kind, bool flag);	// 0x002C025A
};

class Rva00212728
{
public:
	void *rva00212728(void *key);		// 0x00212728, index or -1
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class LivingWorldPendingBattle;
class LivingWorldRegionManager
{
public:
	LivingWorldPendingBattle *rva0020E501(int index);	// 0x0020E501
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct ResolveClickWorldView
{
	char m_pad00[0xB0];
	LivingWorldRegionManager *m_regionManager;	// +0xB0
};

struct ResolveClickBattleView
{
	char m_pad00[0x30];
	int m_30;							// +0x30, the message argument
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);	// +0x48
};
extern MessageStream *TheMessageStream;

struct ResolveClickPoint
{
	int x;
	int y;
};

struct ResolveClickRegion
{
	int x;
	int y;
	int right;
	int bottom;
};

struct ResolveClickObject
{
	char m_pad00[0x10];
	void *m_key;						// +0x10
};

namespace CampaignInGameUI
{
class ResolveBattlesBehavior
{
public:
	class Impl;
};
}

class CampaignInGameUI::ResolveBattlesBehavior::Impl
{
public:
	int OnMouseLeftClick(void *regionWord, unsigned unused);

private:
	char m_pad00[0x08];
	Rva002C025AViewer *m_viewer;		// +0x08
	bool m_clicked;						// +0x0C
};

// CampaignInGameUI::ResolveBattlesBehavior::Impl::OnMouseLeftClick, retail
// 0x005777A0.
int CampaignInGameUI::ResolveBattlesBehavior::Impl::OnMouseLeftClick(void *regionWord, unsigned unused)
{
	ResolveClickRegion *region = (ResolveClickRegion *)regionWord;
	if (region->right - region->x > 0 || region->bottom - region->y > 0)
		return 0;
	if (m_clicked)
		return 0;

	ResolveClickPoint point;
	point.x = region->x;
	point.y = region->y;
	ResolveClickObject *object = (ResolveClickObject *)m_viewer->rva002C025A(&point, 1, false);
	if (!object)
		return 0;
	int index = (int)((Rva00212728 *)TheLivingWorldManager)->rva00212728(object->m_key);
	if (index < 0)
		return 0;
	LivingWorldRegionManager *manager = ((ResolveClickWorldView *)TheLivingWorldLogic)->m_regionManager;
	ResolveClickBattleView *battle = (ResolveClickBattleView *)manager->rva0020E501(index);
	if (!battle)
		return 0;

	m_clicked = true;
	GameMessage *msg = TheMessageStream->appendMessage(0x6B5);
	msg->appendIntegerArgument(battle->m_30);
	return 1;
}
