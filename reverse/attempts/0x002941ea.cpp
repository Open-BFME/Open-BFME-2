// ?rva002941EA@Object@@UAEXPAHPAM11@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// NEAR (helper draft, not under Code/): every instruction matches except
// block placement: retail keeps the second "-1" block inline right after the
// 20*20 distance test (movss -1; jmp to the 0.1 block's shared stores), cl
// sinks it next to the stores at the end (three short jumps become near
// jumps: 444 vs 435 bytes). Tried combined/inverted conditions, goto into
// the block, value-then-store and pure if/else; all sink it.
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
	OBJECT_STATUS_38 = 0x26
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
	unsigned char m_pad128[0x4B4 - 0x128];
	Real m_rangeScaleB; // +0x4B4
	Real m_rangeScaleC; // +0x4B8
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
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

class ObjectThingBase
{
public:
	virtual ~ObjectThingBase();

protected:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x64 - 0x08];
};

class ObjectShroudClient
{
public:
	virtual void rva002941EA(int *playerMask, Real *rangeA, Real *rangeB, Real *rangeC) = 0;

private:
	unsigned char m_pad04[0x08 - 0x04];
};

class Object : public ObjectThingBase, public ObjectShroudClient
{
public:
	Player *getControllingPlayer() const;
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
	unsigned char m_pad095[0x438 - 0x95];
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
	Player *player = getControllingPlayer();
	if (player == 0 || getShroudClearingRange() <= 0.0f)
	{
		*rangeA = *rangeB = *rangeC = -1.0f;
		return;
	}
	if (testStatus(OBJECT_STATUS_38))
	{
		Object *other = rva002931F5(false);
		if (other && rva00263763(other) < (Real)(20 * 20))
		{
			*rangeA = *rangeB = *rangeC = -1.0f;
			return;
		}
	}
	if (getTemplate()->isKindOf(KINDOF_87))
		*playerMask = 0xFFFFF;
	else
		*playerMask = ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(), 3, false)
			| ((const Rva002AA21CDwordField *)player)->get();
	if ((m_flags94 & 1) || (m_privateStatus & 1))
	{
		*rangeA = *rangeB = *rangeC = 0.1f;
		return;
	}
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
}
