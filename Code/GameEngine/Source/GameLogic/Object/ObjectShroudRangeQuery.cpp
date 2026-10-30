// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva002941EA@Object@@UAEXPAHPAM11@Z retail 0x002941EA..0x0029439D (435 bytes, ret 0x10).
// Object override in the +0x64 interface vtable (slot entry at 0x007FC2E4,
// next to getGhostObject 0x00290EFE and ShroudHideIfFogged 0x0028E775; layout
// as ObjectPartitionShroudQueries.cpp and ObjectInterfaceSlots.cpp): fills a
// player mask and three ranges. All three ranges are -1 when the flag at
// Object+0x454 is clear, without a controlling player (rowed 0x0028AFA9),
// with no shroud clearing range (rowed 0x0028DE87), or when status 0x26
// (rowed testStatus 0x0004E536) holds and the related object (rowed
// 0x002931F5) is under 20*20 by the rowed 0x00263763 measure. The mask is
// 0xFFFFF for kind-of 87, else the players related by 3 to the owner
// (rowed PlayerList::getPlayersWithRelationship 0x002A7C70) or'd with the
// owner's own bit (rowed 0x002AA21C). The ranges are 0.1 when bit 0 of
// Object+0x94 or of the private status Object+0x438 is set; otherwise each is
// the shroud clearing range, the second and third scaled by the template's
// +0x4B4/+0x4B8 unless the module from the rowed 0x0028C197 supplies positive
// overrides (vslots +0x25C/+0x258). WorldBuilder twin 0x00CE0DD0 is an older
// unnamed variant; the slot name is not recovered.

typedef float Real;

enum KindOfType
{
	KINDOF_87 = 87
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_38 = 0x26,
	STATUS15 = 15, STATUS17 = 17
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the isKindOf copy loses to the first-in-order copy. No flags touched.
	__forceinline bool bfme_isKindOf_769ee(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
	unsigned char m_pad128[0x4B4 - 0x128];
	Real m_rangeScaleB; // +0x4B4
	Real m_rangeScaleC; // +0x4B8
};

class Team;
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	Relationship getRelationship(const Team *) const;

private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
	unsigned char m_pad058[0x2EC - 0x58];
public:
	Team *team; // +0x2EC, target relationship calls
};

class Rva002AA21CDwordField
{
public:
	int get() const;
};

class PlayerList
{
public:
	int getPlayersWithRelationship(int playerIndex, unsigned int relationships, bool includeSelf);
	Player *getNthPlayer(int);
};

extern PlayerList *ThePlayerList;

class Rva0028C197Module
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003();
	virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007();
	virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015();
	virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027();
	virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031();
	virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043();
	virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047();
	virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051();
	virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055();
	virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063();
	virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067();
	virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071();
	virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075();
	virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079();
	virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083();
	virtual void s084(); virtual void s085(); virtual void s086(); virtual void s087();
	virtual void s088(); virtual void s089(); virtual void s090(); virtual void s091();
	virtual void s092(); virtual void s093(); virtual void s094(); virtual void s095();
	virtual void s096(); virtual void s097(); virtual void s098(); virtual void s099();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110(); virtual void s111();
	virtual void s112(); virtual void s113(); virtual void s114(); virtual void s115();
	virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123();
	virtual void s124(); virtual void s125(); virtual void s126(); virtual void s127();
	virtual void s128(); virtual void s129(); virtual void s130(); virtual void s131();
	virtual void s132(); virtual void s133(); virtual void s134(); virtual void s135();
	virtual void s136(); virtual void s137(); virtual void s138(); virtual void s139();
	virtual void s140(); virtual void s141(); virtual void s142(); virtual void s143();
	virtual void s144(); virtual void s145(); virtual void s146(); virtual void s147();
	virtual void s148(); virtual void s149();
	virtual Real getRangeOverrideC(); // +0x258
	virtual Real getRangeOverrideB(); // +0x25C
};

class Object;
struct ObjectNode {ObjectNode*next,*prev;Object*value;};
struct ObjectList {ObjectNode*head;};
struct ObjectListView {void*first;const ObjectList*list;};
#define OBJECT_CONTAIN_V(n) virtual void s##n();
#define OBJECT_CONTAIN_V10(n) OBJECT_CONTAIN_V(n##0) OBJECT_CONTAIN_V(n##1) OBJECT_CONTAIN_V(n##2) OBJECT_CONTAIN_V(n##3) OBJECT_CONTAIN_V(n##4) OBJECT_CONTAIN_V(n##5) OBJECT_CONTAIN_V(n##6) OBJECT_CONTAIN_V(n##7) OBJECT_CONTAIN_V(n##8) OBJECT_CONTAIN_V(n##9)
class ContainView {public:
 OBJECT_CONTAIN_V10(0) OBJECT_CONTAIN_V(10) OBJECT_CONTAIN_V(11) OBJECT_CONTAIN_V(12) OBJECT_CONTAIN_V(13) OBJECT_CONTAIN_V(14) OBJECT_CONTAIN_V(15) OBJECT_CONTAIN_V(16) OBJECT_CONTAIN_V(17) OBJECT_CONTAIN_V(18)
 virtual Player*playerFor(Player*);
 OBJECT_CONTAIN_V10(2) virtual ContainView*child();
 OBJECT_CONTAIN_V(31) OBJECT_CONTAIN_V(32) OBJECT_CONTAIN_V(33) OBJECT_CONTAIN_V(34) OBJECT_CONTAIN_V(35) OBJECT_CONTAIN_V(36) OBJECT_CONTAIN_V(37) OBJECT_CONTAIN_V(38) OBJECT_CONTAIN_V(39) OBJECT_CONTAIN_V10(4) OBJECT_CONTAIN_V10(5)
 OBJECT_CONTAIN_V(60) OBJECT_CONTAIN_V(61) OBJECT_CONTAIN_V(62) OBJECT_CONTAIN_V(63) OBJECT_CONTAIN_V(64) OBJECT_CONTAIN_V(65) virtual void listA(ObjectListView*);
 OBJECT_CONTAIN_V(67) OBJECT_CONTAIN_V(68) virtual int countFor(int);virtual void listB(ObjectListView*);OBJECT_CONTAIN_V(71) OBJECT_CONTAIN_V(72) virtual int count();
};

#undef OBJECT_CONTAIN_V10
#undef OBJECT_CONTAIN_V
class Rva00373EC6 { public: char m_pad00[0x38]; int playerIndex; int active; };

class ObjectThingBase
{
public:
	virtual ~ObjectThingBase();

protected:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x64 - 0x08];
};

// Compatibility surface of Object's native table at +0x64 (VA 00BFC2D8).
// This is not the complete original base: +0x68 is a vbptr, reserved separately.
// Original class identity and the empty slot's return type remain unknown;
// the opaque slot is never called through this query-only view.
class AsciiString;
#include "ObjectShroudClient.h"

// Partial storage view only: the native nonvirtual prefix has vfptr+vbptr.
// The actual lifetime implementations retain their virtual-base hierarchy.
class Rva007FC2D8ShroudStorageView : public ObjectShroudClient
{
private:
    unsigned char m_vbptrStorage[4];
};

class Object : public ObjectThingBase, public Rva007FC2D8ShroudStorageView
{
public:
	Player *getControllingPlayer() const;
	bool rva0028F518();
	int rva002933CD();
	Rva00373EC6 *rva0028F4BC();
	bool rva00294471(void *player, int mode);
	Real getShroudClearingRange() const;
	bool testStatus(ObjectStatusTypes status) const;
	Object *rva002931F5(bool flag);
	Real rva00263763(const void *other) const;
	void *rva0028C197() const;
	const ThingTemplate *getTemplate() const { return m_template; }

	virtual void rva002941EA(int *playerMask, Real *rangeA, Real *rangeB, Real *rangeC);

private:
	unsigned char m_pad06C[0x94 - 0x6C];
	unsigned char m_flags94; // +0x94
	unsigned char m_pad095[0x250 - 0x95];
	ContainView *contain; // +0x250, native virtual containment queries
	unsigned char m_pad254[0x438 - 0x254];
	unsigned char m_privateStatus; // +0x438
	unsigned char m_pad439[0x454 - 0x439];
	bool m_hasRanges; // +0x454
};

void Object::rva002941EA(int *playerMask, Real *rangeA, Real *rangeB, Real *rangeC)
{
	if (!m_hasRanges)
	{
		*rangeA = *rangeB = *rangeC = -1.0f;
		return;
	}
	bool valid = false;
	Player *player = getControllingPlayer();
	if (player && !(getShroudClearingRange() <= 0.0f)) {
	valid = true;
	if (testStatus(OBJECT_STATUS_38)) { Object*other=rva002931F5(false); if(other && rva00263763(other)<400.0f) valid=false; }
}
float fallback;
if(!valid)fallback=-1.0f;else{
	if (getTemplate()->bfme_isKindOf_769ee(KINDOF_87))
		*playerMask = 0xFFFFF;
	else { int allies = ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(), 3, false); int own = ((const Rva002AA21CDwordField *)player)->get();
		// Keep the relation mask in its stack home across the owner-bit call.
		*playerMask=*(volatile int*)&allies|own; }
	if ((m_flags94 & 1) || (m_privateStatus & 1))
	{
		fallback=0.1f;
	} else {
	*rangeA = *rangeB = *rangeC = getShroudClearingRange();
	Real scaleB = getTemplate()->m_rangeScaleB;
	Real scaleC = getTemplate()->m_rangeScaleC;
	Rva0028C197Module *module = (Rva0028C197Module *)rva0028C197();
	if (module)
	{
		Real overrideB = module->getRangeOverrideB();
		if (overrideB > 0.0f)
			scaleB = overrideB;
		Real overrideC = module->getRangeOverrideC();
		if (overrideC > 0.0f)
			scaleC = overrideC;
	}
	*rangeB *= scaleB;
	*rangeC *= scaleC;
	return;
}
}
*rangeA=*rangeB=*rangeC=fallback;
}

// Native 294471..2946AB, RET8: eligibility relative to a Player and mode.
// The original method name remains unknown. Owned Object callers establish
// the receiver; native getRelationship(Team) calls establish the player word.
// WB control flow supports allied early-out, active/effect-owner checks,
// child-container scan and first-rider relationship test. Target reads prove
// template bytes113/115, contain250, team2EC and effect38/3C; no donor layout
// or original virtual-slot names are inferred from byte matching.
// Preserve the explicit inactive-path else: it selects native's early shared
// false-return block, closing the saved 570-byte body's sole code-layout delta.
bool Object::rva00294471(void *arg, int mode)
{
	Player *player = (Player *)arg;
	if (mode == 1)
	{
		Player *owner = getControllingPlayer();
		if (owner && player->getRelationship(owner->team) == ALLIES)
			return false;
	}
	if (rva0028F518() || (testStatus(STATUS15) && !testStatus(STATUS17)))
	{
		if (!(m_template->m_kindOf[0x0B] & 1))
			return false;
		Rva00373EC6 *effect = rva0028F4BC();
		if (effect && effect->active)
		{
			Player *owner = ThePlayerList->getNthPlayer(effect->playerIndex);
			if (player && owner)
				return (unsigned char)(player->getRelationship(owner->team) == ENEMIES);
		}
		if (mode == 1)
		{
			Player *owner = getControllingPlayer();
			if (!owner || player->getRelationship(owner->team) != ENEMIES)
				return false;
		}
		return true;
	}
	else
	{
		if (mode == 1)
		{
			Player *owner = getControllingPlayer();
			if (!owner || player->getRelationship(owner->team) != ENEMIES)
				return false;
		}
		if (m_template->m_kindOf[0x0D] & 0x20)
		{
			ContainView *base = contain;
			if (base)
			{
				ContainView *sub = base->child();
				if (sub)
				{
					ObjectListView view;
					sub->listA(&view);
					bool any = false;
					ObjectNode *endNode = view.list->head;
					for (ObjectNode *objectNode = endNode->next; objectNode != endNode; objectNode = objectNode->next)
					{
						Object *obj = objectNode->value;
						if (obj)
						{
							if (!obj->rva0028F518() || !obj->testStatus(STATUS15))
								return true;
							if ((unsigned char)obj->rva002933CD() || obj->testStatus(STATUS17))
								return true;
							any = true;
						}
					}
					if (any)
						return false;
					return true;
				}
			}
		}
		ContainView *current = contain;
		if (current)
		{
			Player *owner = current->playerFor(player);
			if (current->count() == current->countFor(0))
			{
				ObjectListView view;
				current->listB(&view);
				ObjectNode *first = view.list->head->next;
				if (first != view.list->head)
				{
					Object *obj = first->value;
					if (obj && !(unsigned char)obj->rva002933CD() && !obj->testStatus(STATUS17) && owner && player->getRelationship(owner->team) == ENEMIES)
						return false;
				}
			}
		}
		return true;
	}
}
