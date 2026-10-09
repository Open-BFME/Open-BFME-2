// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// Retail 0x00405E3D 3287 bytes RET4 (EH frame). Slot 3 of the help-source
// vftable 0x00838970 (deleting dtor 0x00406B1D first). WB twin 0x01078070
// OldSchoolHelpBoxContentSource::createContent in ControlBarPopupDescription.cpp
// gives the order: title / cost / time / description strings filled from the
// selected object's command button (science chain sciences upgrade object
// build cost command points prerequisites unit revival and castle unpack)
// then a 12-byte help record (rowed ctor 0x0056D5BD) returned through the
// reference-counted handle (ArmySummaryHelpSource pattern). Callee names are
// the ledger rows/pins at each address; offsets are read from retail.

// Vector storage is released through the pinned _STL::free (0x00030830).
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <vector>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned short WideChar;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct TargetRef00217D4C
{
	void *vtable;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr) ++m_ptr->references;
	}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr) ++m_ptr->references;
	}
	~TreeHintRef00217D4C()
	{
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

struct UnicodeHeaderView
{
	int refs;
	unsigned short length;
};

struct UnicodeView
{
	static __forceinline bool isEmpty(const UnicodeString &s)
	{
		const UnicodeHeaderView *h = *(const UnicodeHeaderView *const *)&s;
		return h == 0 || h->length == 0;
	}
};

class Player;
class Object;
class ThingTemplate;
class UpgradeTemplate;
class Module;
class CreateAHeroData;
struct UpgradeRange
{
	void *m_begin;
	void *m_end;
};

#define HELP_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define HELP_SLOTS16(p) HELP_SLOTS4(p##0) HELP_SLOTS4(p##1) HELP_SLOTS4(p##2) HELP_SLOTS4(p##3)

class GameTextInterface
{
public:
	HELP_SLOTS4(a) HELP_SLOTS4(b) HELP_SLOTS4(c)
	virtual void d0(); virtual void d1();
	virtual UnicodeString fetchA(const AsciiString &label, bool *exists);      // +0x38
	virtual UnicodeString fetchC(const char *label, bool *exists);             // +0x3C
	virtual UnicodeString *fetchPtrA(const AsciiString &label, bool *exists);  // +0x40
	virtual UnicodeString *fetchPtrC(const char *label, bool *exists);         // +0x44
};
extern GameTextInterface *TheGameText;

struct DrawableNode;
class Drawable
{
public:
	Object *getObject() const { return m_object; }

	char m_pad000[0xFC];
	Object *m_object;               // +0xFC
};

struct DrawableNode
{
	DrawableNode *next;
	DrawableNode *prev;
	Drawable *data;
};

struct DrawableList
{
	DrawableNode *m_node;
};

class InGameUI
{
public:
	HELP_SLOTS16(a) HELP_SLOTS16(b) HELP_SLOTS16(c) HELP_SLOTS16(d)
	HELP_SLOTS4(e0)
	virtual void e10(); virtual void e11();
	virtual int getSelectCount();                    // +0x118
	virtual void f1(); virtual void f2();
	virtual const DrawableList *getAllSelectedDrawables(); // +0x124
	virtual void f4();
	virtual Drawable *getFirstSelectedDrawable();    // +0x12C
};
extern InGameUI *TheInGameUI;

class BfmeMemberRV;
class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_local;                // +0x10
};
extern PlayerList *ThePlayerList;

class ScienceStore
{
public:
	bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
	int getSciencePurchaseCost(ScienceType science) const;
};
extern ScienceStore *TheScienceStore;

class UpgradeCenter
{
public:
	bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade, Object *obj, bool test);
};
extern UpgradeCenter *TheUpgradeCenter;

class UpgradeTemplate
{
public:
	unsigned int rva0026EF50(Player *player, Object *obj) const;
};

class Rva002D371DAddImm32Field
{
public:
	int get() const;
};
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Player
{
public:
	bool hasScience(ScienceType science) const;
	bool rva002AB82D(CreateAHeroData *data) const;
	bool rva002AB855(CreateAHeroData *data) const;
	bool rva002AA8EF(const UpgradeTemplate *upgrade) const;
	bool rva002AB87D(const UpgradeTemplate *upgrade) const;
	bool allowedToBuild(const ThingTemplate *thing) const;
};

class ProductionInterface
{
public:
	HELP_SLOTS4(a) HELP_SLOTS4(b) HELP_SLOTS4(c)
	virtual float getCost1(Player *player);          // +0x30
	virtual void d1(); virtual void d2(); virtual void d3();
	HELP_SLOTS4(e)
	virtual float getCost2(Player *player);          // +0x50
};

class BodyModule
{
public:
	HELP_SLOTS4(a)
	virtual void b0();
	virtual float getHealthPercent() const;          // +0x14
};

class QueueModule
{
public:
	HELP_SLOTS16(a)
	virtual void b0();
	virtual int getQueueState();                     // +0x44
};

class Rva00395F57
{
public:
	bool canUnpack(bool force);
};

class Rva0039718B
{
public:
	int rva003970E7(Player *player);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void *rva0028BD17() const;
	bool rva0028D491() const;
	void *rva0028BC58(int which);
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	bool rva002940B9(const UpgradeTemplate *upgrade);
	Module *findModule(NameKeyType key) const;

	char m_pad000[0x254];
	BodyModule *m_body;             // +0x254
};

class ProductionPrerequisite
{
public:
	UnicodeString getRequiresList(const Player *player) const;

	char m_data[0x24];
};

class Rva0033AC7F
{
public:
	bool rva0033AC7F(StringBase<unsigned short> &out);
	bool rva0033ACA2(StringBase<unsigned short> &out);
	bool rva0033ACC5(AsciiString &out);
};

class ThingTemplate
{
public:
	int rva0033A69A(const Player *player, int obj, int which) const;

	char m_pad000[0x30];
	UnicodeString m_displayName;    // +0x30
	char m_pad034[0x11B - 0x34];
	unsigned char m_flags11B;       // +0x11B
	char m_pad11C[0x324 - 0x11C];
	ProductionPrerequisite *m_prereqBegin; // +0x324
	ProductionPrerequisite *m_prereqEnd;   // +0x328
	char m_pad32C[0x618 - 0x32C];
	int m_buildPoints;              // +0x618
};

class UnitRevivalEntry
{
public:
	void *getThingTemplate();

	char m_pad00[0x0C];
	int m_rank;                     // +0x0C
	char m_pad10[0xA0 - 0x10];
	bool m_isRevive;                // +0xA0
};

class Rva0037E421
{
public:
	void *rva0037E421(int index);
};

class Rva0037E6E8
{
public:
	int rva0037E649(int index, Object *obj);
};

class Rva0029FCB4
{
public:
	_STL::vector<ScienceType> rva0029FCB4();
};

class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;
	const AsciiString &rva0035B26F() const;
	const AsciiString &rva0035B1E9() const;

	char m_pad00[0x14];
	int m_commandType;              // +0x14
	char m_pad18[4];
	unsigned int m_options;         // +0x1C
	char m_pad20[4];
	const UpgradeTemplate *m_upgrade; // +0x24
	UpgradeRange m_requiredUpgrades;  // +0x28
	char m_pad30[4];
	bool m_requireAll;              // +0x34
	char m_pad35[0x44 - 0x35];
	Rva0029FCB4 *m_createAHero;     // +0x44
	char m_pad48[0x70 - 0x48];
	AsciiString m_alreadyUpgradedLabel;   // +0x70
	AsciiString m_conflictingLabel;       // +0x74
	AsciiString m_lacksPrereqLabel;       // +0x78
	char m_pad7C[0xA4 - 0x7C];
	_STL::vector<ScienceType> m_sciences; // +0xA4
	char m_padB0[0xC0 - 0xB0];
	int m_revivalIndex;             // +0xC0
};

class Rva0056D3FD
{
public:
	Rva0056D3FD(const AsciiString &title, const AsciiString &cost, const AsciiString &time, const AsciiString &description, const AsciiString &extra);

	char m_data[12];
};

bool rva00405B0A(const AsciiString &label, const Player *player, const ThingTemplate *thing, UnicodeString *out);

class OldSchoolHelpBoxContentSource
{
public:
	virtual ~OldSchoolHelpBoxContentSource();
	virtual void s1();
	virtual void s2();
	virtual TreeHintRef00217D4C createContent();

	bool allRequiredUpgradesComplete(Object *obj, UpgradeRange *range, bool requireAll);

	char m_pad04[8];
	CommandButton *m_commandButton; // +0x0C
};

TreeHintRef00217D4C OldSchoolHelpBoxContentSource::createContent()
{
	UnicodeString title;
	UnicodeString cost;
	UnicodeString time;
	UnicodeString description;

	Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
	Object *obj = draw ? draw->getObject() : 0;
	Player *localPlayer = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
	Player *player = obj ? obj->getControllingPlayer() : localPlayer;

	UnicodeString requiresList = UnicodeString::TheEmptyString;
	UnicodeString requiresString;
	bool firstRequirement = true;
	bool scienceLocked = false;

	if (m_commandButton)
	{
		const ThingTemplate *thing = m_commandButton->rva0035B570();
		ScienceType science = SCIENCE_INVALID;
		const UpgradeTemplate *upgrade = m_commandButton->m_upgrade;

		if (m_commandButton->m_sciences.size() > 1)
		{
			for (int i = 0; i < m_commandButton->m_sciences.size(); ++i)
			{
				science = m_commandButton->m_sciences[i];
				if (m_commandButton->m_commandType != 0x19)
				{
					if (player && !player->hasScience(science) && i > 0)
						science = m_commandButton->m_sciences[i - 1];
					scienceLocked = true;
					break;
				}
				if (player && !player->hasScience(science))
					break;
			}
		}
		else if (m_commandButton->m_sciences.size() == 1)
		{
			science = m_commandButton->m_sciences[0];
		}

		int type = m_commandButton->m_commandType;
		bool isUnitBuild = type == 6 || type == 7 || type == 8;

		if ((type == 0x33 || type == 0x3B) && obj)
		{
			ProductionInterface *production = (ProductionInterface *)obj->rva0028BD17();
			if (production)
			{
				float costValue = (type == 0x3B) ? production->getCost2(player) : production->getCost1(player);
				bool fullHealth = obj->m_body->getHealthPercent() == 1.0f;
				bool notBusy = !obj->rva0028D491();
				if (notBusy)
				{
					if (!fullHealth)
						cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), (int)costValue);
				}
				else if (obj->m_body->getHealthPercent() == 0.0f)
				{
					cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), (int)costValue);
				}
			}
		}

		description.clear();

		if (localPlayer && m_commandButton->m_commandType == 0x26 && m_commandButton->m_createAHero)
		{
			_STL::vector<ScienceType> sciences = m_commandButton->m_createAHero->rva0029FCB4();
			ScienceType heroScience = SCIENCE_INVALID;
			for (_STL::vector<ScienceType>::iterator it = sciences.begin(); it != sciences.end(); ++it)
			{
				if (localPlayer->hasScience(*it))
				{
					heroScience = *it;
					break;
				}
			}
			if (heroScience != SCIENCE_INVALID)
			{
				if (localPlayer->rva002AB82D((CreateAHeroData *)heroScience)
					|| localPlayer->rva002AB855((CreateAHeroData *)heroScience)
					|| !TheScienceStore->playerHasRootPrereqsForScience((const Player *)((char *)localPlayer + 4), heroScience))
				{
					description = TheGameText->fetchC("TOOLTIP:ScienceDisabled", 0);
				}
			}
		}

		if (UnicodeView::isEmpty(description) && !m_commandButton->rva0035B26F().isEmpty())
		{
			description = TheGameText->fetchA(m_commandButton->rva0035B26F(), 0);
			if (obj && upgrade && !player->rva002AA8EF(upgrade) && isUnitBuild)
			{
				QueueModule *queue = (QueueModule *)obj->rva0028BC58(0);
				if (queue && queue->getQueueState() == 0x14)
				{
					description.concat(L"\n\n");
					description.concat(TheGameText->fetchC("TOOLTIP:TooltipCannotPurchaseBecauseQueueFull", 0));
				}
				else if (!TheUpgradeCenter->rva0026F11A(ThePlayerList->m_local, upgrade, obj, false))
				{
					description.concat(L"\n\n");
					description.concat(TheGameText->fetchC("TOOLTIP:TooltipNotEnoughMoneyToBuild", 0));
				}
			}
		}

		title = TheGameText->fetchC(m_commandButton->rva0035B1E9().str(), 0);

		if (thing && !(upgrade && isUnitBuild) && m_commandButton->m_commandType != 0x19 && m_commandButton->m_commandType != 0x34)
		{
			int buildCost = (thing->m_flags11B & 0x20) ? 0 : thing->rva0033A69A(player, (int)obj, -1);
			if (buildCost <= 0)
				cost = TheGameText->fetchC("TOOLTIP:CostFree", 0);
			else
				cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), buildCost);

			int buildPoints = thing->m_buildPoints;
			if (buildPoints > 0)
				time.format(TheGameText->fetchPtrC("TOOLTIP:CommandPoints", 0), buildPoints);

			for (int p = 0; p < thing->m_prereqEnd - thing->m_prereqBegin; ++p)
			{
				requiresString = thing->m_prereqBegin[p].getRequiresList(player);
				if (requiresString.compare(UnicodeString::TheEmptyString) != 0)
				{
					if (firstRequirement)
						firstRequirement = false;
					else
						requiresList.concat(L", ");
				}
				requiresList.concat(requiresString);
			}

			if (!UnicodeView::isEmpty(requiresList))
			{
				UnicodeString requiresFormat = TheGameText->fetchC("CONTROLBAR:Requirements", 0);
				requiresList.format(requiresFormat.str(), requiresList.str());
				if (!UnicodeView::isEmpty(description))
					description.concat(L"\n");
				description.concat(requiresList);
			}

			if (localPlayer && !localPlayer->allowedToBuild(thing))
			{
				if (!UnicodeView::isEmpty(description))
					description.concat(L"\n");
				description.concat(TheGameText->fetchC("TOOLTIP:BuildDisabled", 0));
			}
		}
		else if (upgrade)
		{
			int upgradeType = m_commandButton->m_commandType;
			bool isType6 = upgradeType == 6;
			bool isType7 = upgradeType == 7;
			bool isType8 = upgradeType == 8;
			bool hasUpgrade = player->rva002AB87D(upgrade);
			bool canUpgrade = false;
			bool lacksPrereq = false;

			if (!hasUpgrade && obj)
			{
				if ((m_commandButton->m_options & 0x40) && !obj->rva00290D2B(upgrade)
					&& !allRequiredUpgradesComplete(obj, &m_commandButton->m_requiredUpgrades, m_commandButton->m_requireAll))
				{
					lacksPrereq = true;
				}
				else if (TheInGameUI->getSelectCount() == 1)
				{
					hasUpgrade = obj->rva00290D2B(upgrade);
					if (isType7)
						canUpgrade = !obj->rva002940B9(upgrade);
				}
				else
				{
					hasUpgrade = true;
					canUpgrade = true;
					const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
					for (DrawableNode *node = selected->m_node->next; node != selected->m_node; node = node->next)
					{
						Drawable *selDraw = node->data;
						if (selDraw)
						{
							Object *selObj = selDraw->getObject();
							if (selObj)
							{
								hasUpgrade = hasUpgrade && selObj->rva00290D2B(upgrade);
								canUpgrade = canUpgrade && !selObj->rva002940B9(upgrade);
							}
						}
						if (!hasUpgrade && !canUpgrade)
							break;
					}
				}
			}

			if (lacksPrereq)
			{
				if (!m_commandButton->m_lacksPrereqLabel.isEmpty())
					description = TheGameText->fetchA(m_commandButton->m_lacksPrereqLabel, 0);
				else
					description = TheGameText->fetchC("TOOLTIP:LacksPrerequisiteUpgradeDefault", 0);
			}
			else if (canUpgrade && !hasUpgrade)
			{
				if (!m_commandButton->m_conflictingLabel.isEmpty())
					description = TheGameText->fetchA(m_commandButton->m_conflictingLabel, 0);
				else
					description = TheGameText->fetchC("TOOLTIP:HasConflictingUpgradeDefault", 0);
			}
			else if (hasUpgrade && (isType6 || isType7 || isType8))
			{
				if (!m_commandButton->m_alreadyUpgradedLabel.isEmpty())
					description = TheGameText->fetchA(m_commandButton->m_alreadyUpgradedLabel, 0);
				else
					description = TheGameText->fetchC("TOOLTIP:AlreadyUpgradedDefault", 0);
			}

			if (!hasUpgrade)
			{
				int upgradeCost = upgrade->rva0026EF50(player, obj);
				if (upgradeCost > 0)
					cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), upgradeCost);
			}
		}
		else if (science != SCIENCE_INVALID && !scienceLocked)
		{
			cost.format(TheGameText->fetchPtrC("TOOLTIP:ScienceCost", 0), TheScienceStore->getSciencePurchaseCost(science));
		}
		else if (m_commandButton->m_commandType == 0x2E)
		{
			int index = m_commandButton->m_revivalIndex;
			Rva0037E421 *revival = (Rva0037E421 *)((char *)player + 0x738);
			UnitRevivalEntry *entry = (UnitRevivalEntry *)revival->rva0037E421(index);
			const ThingTemplate *revivalThing = entry ? (const ThingTemplate *)entry->getThingTemplate() : 0;
			if (entry && revivalThing)
			{
				AsciiString label;
				if (entry->m_isRevive)
				{
					label = "CONTROLBAR:GenericReviveHero";
					if (!((Rva0033AC7F *)revivalThing)->rva0033AC7F(description))
						description = TheGameText->fetchC("CONTROLBAR:ToolTipGenericReviveHero", 0);
				}
				else
				{
					label = "CONTROLBAR:GenericRecruitHero";
					if (!((Rva0033AC7F *)revivalThing)->rva0033ACA2(description))
						description = TheGameText->fetchC("CONTROLBAR:ToolTipGenericRecruitHero", 0);
				}

				if (!rva00405B0A(label, player, revivalThing, &title))
				{
					AsciiString nameLabel;
					if (((Rva0033AC7F *)revivalThing)->rva0033ACC5(nameLabel))
						title.format(TheGameText->fetchPtrA(label, 0), TheGameText->fetchA(nameLabel, 0).str());
					else
						title.format(TheGameText->fetchPtrA(label, 0), revivalThing->m_displayName.str());
				}

				description.concat(L"\n");
				UnicodeString rank;
				rank.format(TheGameText->fetchPtrC("APT:RankLabel", 0), entry->m_rank);
				description.concat(rank);

				cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), ((Rva0037E6E8 *)revival)->rva0037E649(index, obj));

				int buildPoints = revivalThing->m_buildPoints;
				if (buildPoints > 0)
					time.format(TheGameText->fetchPtrC("TOOLTIP:CommandPoints", 0), buildPoints);
			}
		}
		else if (m_commandButton->m_commandType == 0x21 && obj)
		{
			Module *castle = obj->findModule(CastleBehavior::rva0003955DA());
			if (castle && ((Rva00395F57 *)castle)->canUnpack(false))
				cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), ((Rva0039718B *)castle)->rva003970E7(player));
		}
	}

	AsciiString extra;
	if (theRadarWindowOverrideSource)
		extra = *(const AsciiString *)((Rva002D371DAddImm32Field *)theRadarWindowOverrideSource)->get();

	TreeHintRef00217D4C help((TargetRef00217D4C *)new Rva0056D3FD(
		reinterpret_cast<const AsciiString &>(title), reinterpret_cast<const AsciiString &>(cost),
		reinterpret_cast<const AsciiString &>(time), reinterpret_cast<const AsciiString &>(description), extra));
	return static_cast<const TreeHintRef00217D4C &>(help);
}
