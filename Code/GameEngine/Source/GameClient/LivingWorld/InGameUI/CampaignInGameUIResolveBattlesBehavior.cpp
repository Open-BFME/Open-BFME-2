// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// CampaignInGameUIResolveBattlesBehavior.cpp -- CampaignInGameUI's
// resolve-battles behaviour at its WorldBuilder home (WB names the click
// handler CampaignInGameUI::ResolveBattlesBehavior::Impl::OnMouseLeftClick,
// CampaignInGameUIResolveBattlesBehavior.cpp:89..117, WB 0x014C8410).
//
// Target facts (retail 0x005777A0, 152 bytes, ret 8): a click that is not a
// drag (the pixel region has no width or height) and is the first one
// (byte +0x0C) picks the point through the behaviour's viewer (+0x08; rowed
// 0x002C025A with kind 1), maps the picked object's key (+0x10) to a region
// index through TheLivingWorldManager's rowed reverse lookup 0x00212728, and
// asks the living-world region manager (TheLivingWorldLogic +0xB0) for that
// region's pending battle (rowed 0x0020E501). A battle marks the click taken
// and posts message 0x6B5 carrying the battle's +0x30 word. The second stack
// word is unused. WB's extra 0x6B6 branch (a global flag at +0x88 and the
// modifier mask 0x430) is absent from retail.
//
// The handler is a virtual: nothing calls it directly, and it fills slot 18
// (+0x48) of the Impl vftable 0x00C6E980, which the Impl ctor 0x00577846
// installs at +0 (it also stores the owner at +4, the viewer at +8 and
// clears +0x0C). Slot 0 there is the base UserInputTranslator::
// translateGameMessage 0x005CBC95 (WB name), whose WB body dispatches a
// message to slot +0x48 with argument 0's record (the pixel region) and
// argument 1's integer and returns the slot's result. The default for that
// slot in the base table 0x00C6E430 is the two-argument stub 0x005748B2;
// the strategic twin 0x00576946 fills the same slot of 0x00C6E7F0, and WB's
// own table for this class (0x01F475F0, installed by WB 0x014C81BE, slot 0
// UserInputTranslator::translateGameMessage) holds WB 0x014C8410 in slot 18.
// WB calls IRegion2D::width/height on the first argument, so it is the
// region (pointer or reference: the codegen is the same; WB's dispatcher
// passes the argument record itself).

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

struct ICoord2D
{
	int x;
	int y;
};

// WB calls IRegion2D::width/height here; retail inlines both (the region.cpp
// rows 0x00004D4B/0x00004D51 are the out-of-line copies), so the extents are
// spelled out below rather than defining second copies of those members.
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct ResolveClickObject
{
	char m_pad00[0x10];
	void *m_key;						// +0x10
};

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

// The translator base (WB UserInputTranslator.cpp): translateGameMessage in
// slot 0, a deleting dtor in slot 1, then the input handlers, whose
// defaults are the shared stubs 0x005748B2 (slot 2 and slots 18..25) and
// 0x005748AD (slots 3..17). Only the slots this unit needs are named.
class UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);	// slot 0
	virtual ~UserInputTranslator();										// slot 1
	virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17();
	virtual int OnMouseLeftClick(const IRegion2D &region, unsigned modifiers);	// slot 18 (+0x48)
};

class Rva00577838;

namespace CampaignInGameUI
{
class ResolveBattlesBehavior
{
public:
	class Impl;
};
}

class CampaignInGameUI::ResolveBattlesBehavior::Impl : public UserInputTranslator
{
public:
	virtual int OnMouseLeftClick(const IRegion2D &region, unsigned modifiers);

private:
	Rva00577838 *m_owner;				// +0x04
	Rva002C025AViewer *m_viewer;		// +0x08
	bool m_clicked;						// +0x0C
};

// CampaignInGameUI::ResolveBattlesBehavior::Impl::OnMouseLeftClick, retail
// 0x005777A0.
int CampaignInGameUI::ResolveBattlesBehavior::Impl::OnMouseLeftClick(const IRegion2D &region, unsigned modifiers)
{
	if (region.hi.x - region.lo.x > 0 || region.hi.y - region.lo.y > 0)
		return 0;
	if (m_clicked)
		return 0;

	ICoord2D point;
	point.x = region.lo.x;
	point.y = region.lo.y;
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
