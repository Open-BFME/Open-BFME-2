// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /O1 /Ob1 /EHsc /DNDEBUG /MD /arch:SSE /G7
//
// UnitRevivalTracker::productionSystemQueueCreateUnit, retail 0x0037EDE0
// (108B), from the WorldBuilder lead (UnitRevivalTracker.cpp): refuse a
// production id already queued (0x0037E451 finds an entry by its +0xA4 id);
// otherwise take the entry at the given index (0x0037E421, 0xD8-byte entries),
// set its +0xCC factor to 0.998, and when it is not already reviving (+0x98
// == -1) start it at the current logic frame (TheGameLogic +0x40) under the
// production id, optionally reporting its button image
// (UnitRevivalEntry::calcButtonImage with the tracker's +0x10 value).
//
// Target facts: entry fields beyond the ones used, the image type and the
// +0x10 value are not established.
//
// UnitRevivalEntry::revivalEntryCalcTimeToBuild, retail 0x0037E1FD (115B),
// from the WorldBuilder lead: the entry's template (name at +0xD4, found by
// ThingFactory::findTemplate) gives the build time for the player (0x0033AA1F
// with 0 and the entry's +0x9C value), scaled by the producer's factor when
// it has the interface from Object 0x0028BC94 (its vtable slot 0x74 with the
// entry's +0xA0 flag); no template gives 0.
//
// Compiler evidence: /G7 is what passes the +0xA0 byte as a bare mov cl /
// push ecx; the default and /G6 zero-extend it first. productionSystemQueue-
// CreateUnit compiles identically either way. 0x0033AA1F (pinned) is called
// on the template findTemplate returns; its name stays address-derived.

typedef bool Bool;
typedef int Int;

class Image;
class Player;
class Object;
class Team;
class Drawable;
struct Coord3D;
struct CreateMask { unsigned int words[4]; };
enum ScienceType { SCIENCE_INVALID=-1 };
class Player { public: bool hasScience(ScienceType) const; };



#include "ascii_string.h"
class ScienceStore { public: ScienceType getScienceFromInternalName(const AsciiString&) const; };
extern ScienceStore *TheScienceStore;

class ThingTemplate
{
public:
	Int rva0033AA1F(const Player *player, Int a, Int b) const;
	int rva0033B479() const;
	Int rva0033A69A(const Player *player, Int a, Int b) const;	// 0x0033A69A, build cost
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate*, Team*, const CreateMask*, bool);
};
extern ThingFactory *TheThingFactory;

class Rva0037E1FDFactor
{
public:
#define RF_SLOT(n) virtual void slot##n();
	RF_SLOT(0) RF_SLOT(1) RF_SLOT(2) RF_SLOT(3) RF_SLOT(4) RF_SLOT(5) RF_SLOT(6)
	RF_SLOT(7) RF_SLOT(8) RF_SLOT(9) RF_SLOT(10) RF_SLOT(11) RF_SLOT(12) RF_SLOT(13)
	RF_SLOT(14) RF_SLOT(15) RF_SLOT(16) RF_SLOT(17) RF_SLOT(18) RF_SLOT(19) RF_SLOT(20)
	RF_SLOT(21) RF_SLOT(22) RF_SLOT(23) RF_SLOT(24) RF_SLOT(25) RF_SLOT(26) RF_SLOT(27)
#undef RF_SLOT
	virtual float getCostFactor(Bool flag); // 0x70
	virtual float getFactor(Bool flag); // 0x74
};

#include "unicode_string.h"

#include "FixedStorage128.h"

struct Rva001EB15A
{
	int a, b, c;
	UnicodeString wide;
	AsciiString text;
	bool flag;
	Rva001EB15A(const Rva001EB15A &);
};

struct RevivalLevelValue
{
	char pad[0xC];
	int value;
};

class ExperienceTracker { public: void rva0039B315(float,bool,bool,bool,bool); };
class Rva0039B20C { public: void rva0039B227(int); };
class RevivalExperienceView
{
public:
	int rva000B49A1() const;
	float getExperienceValue() const { return experience; }
	int getLevelRank() const { return level; }
	char pad[0x10];
	float experience;
	char pad14[0x10];
	int level;
	char pad28[4];
	RevivalLevelValue *definition;
};

// Existing folded 7B body, owned by meshgeometry.cpp; no second body row.
// ?RevivalExperienceView::rva000B49A1 present-unmatched
int RevivalExperienceView::rva000B49A1() const
{
	return definition->value;
}

enum NameKeyType { INVALID_NAME_KEY = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
#define SLOT(n) virtual void v##n();
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6)
	SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual int v14();
};

class Rva004AFB01
{
public:
	int rva004AFB01();
	int rva004AFB16();
};
class RespawnUpdate
{
public:
	void *rva004AF25D();
};
struct RevivalTemplateView
{
	char pad[0x64];
	AsciiString name;
};
class Rva001EAFC1 { public: Rva001EAFC1 &operator=(const Rva001EAFC1&); };
class ScriptEngine { public: void rva00357960(const AsciiString&,Object*); };
extern ScriptEngine *TheScriptEngine;
class CreateAHeroData;
class CreateAHeroManager { public: CreateAHeroData *rva002197A6(int); };
extern CreateAHeroManager *TheCreateAHeroManager;
class CreateAHeroHero { public: bool UpdateCommandSet(int); };
class Drawable { public: void rva00274176(bool); };
class Object
{
public:
	void *rva0028BC94();
    void teleportTo(const Coord3D*,bool);
    void rva0028BAAE(int);
    void updateShroudNow();
    Drawable *getDrawable() const;
    bool addAttributeModifierToPool(const AsciiString&,int);
    void rva0028B265() const;
	Module *findModule(NameKeyType) const;
	RevivalExperienceView *getExperience() const { return experience; }
	unsigned char pad00[4];
	RevivalTemplateView *thingTemplate;
	char pad08[0x264 - 8];
	RevivalExperienceView *experience;
	char pad268[0x284 - 0x268];
	BfmeFixedStorage128 upgrades;
	char pad304[0x438 - 0x304];
	unsigned char flags;
	char pad439[0x45C - 0x439];
	int field45c, field460;
	char pad464[4];
	Rva001EB15A record;
};

class UnitRevivalEntry
{
public:
	UnitRevivalEntry(Object *object);
	UnitRevivalEntry(const UnitRevivalEntry &other);
	~UnitRevivalEntry();
	void *getThingTemplate();
	const Image *calcButtonImage(Int value);
	Int revivalEntryCalcTimeToBuild(const Player *player, Object *producer);
	Int revivalEntryCalcCostToBuild(const Player *player, Object *producer);

	int m_moduleID;
	int m_unknown04;
	float m_experience;
	int m_rank;
	int m_level;
	BfmeFixedStorage128 m_upgrades;
	Int m_94;			// +0x94
	Int m_reviveStartFrame;		// +0x98
	Int m_9c;			// +0x9C
	Bool m_a0;			// +0xA0
	Bool m_a1;
	unsigned char m_padA2[2];
	Int m_productionID;		// +0xA4
	int m_a8;
	int m_ac;
	Rva001EB15A m_record;
	int m_c8;
	float m_factor;			// +0xCC
	AsciiString m_displayName;
	AsciiString m_templateName;	// +0xD4
};

class GameLogic
{
public:
	Int getFrame() const { return m_frame; }

private:
	unsigned char m_pad00[0x40];
	Int m_frame;
};
extern GameLogic *TheGameLogic;

class Rva0037E421
{
public:
	void *rva0037E421(Int index);
	void *rva0037E451(Int productionID);
};

class UnitRevivalTracker
{
public:
	Bool productionSystemQueueCreateUnit(Int index, Int productionID, const Image **outImage);
    Object *productionSystemNewObject(unsigned int productionID,const Coord3D *position);
    void rva0037EF2D(unsigned int);
    UnitRevivalEntry *begin() const { return *reinterpret_cast<UnitRevivalEntry* const*>(reinterpret_cast<const char*>(this)+4); }
    UnitRevivalEntry *end() const { return *reinterpret_cast<UnitRevivalEntry* const*>(reinterpret_cast<const char*>(this)+8); }

private:
	unsigned char m_pad00[0x10];
	Int m_10;
};

Bool UnitRevivalTracker::productionSystemQueueCreateUnit(Int index, Int productionID, const Image **outImage)
{
	if (!((Rva0037E421 *)this)->rva0037E451(productionID))
	{
		UnitRevivalEntry *entry = (UnitRevivalEntry *)((Rva0037E421 *)this)->rva0037E421(index);
		if (entry)
		{
			entry->m_factor = 0.998f;
			if (entry->m_reviveStartFrame == -1)
			{
				entry->m_reviveStartFrame = TheGameLogic->getFrame();
				entry->m_productionID = productionID;
				if (outImage)
					*outImage = entry->calcButtonImage(m_10);
				return true;
			}
		}
	}
	return false;
}

Int UnitRevivalEntry::revivalEntryCalcTimeToBuild(const Player *player, Object *producer)
{
	float factor = 1.0f;
	if (producer)
	{
		Rva0037E1FDFactor *f = (Rva0037E1FDFactor *)producer->rva0028BC94();
		if (f)
			factor = f->getFactor(m_a0);
	}
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(m_templateName);
	if (tmpl)
		return (Int)(tmpl->rva0033AA1F(player, 0, m_9c) * factor);
	return 0;
}

// UnitRevivalEntry::revivalEntryCalcCostToBuild, retail 0x0037E18A (115B),
// the cost twin of revivalEntryCalcTimeToBuild (WB names both and asserts at
// UnitRevivalTracker.cpp:162 when the template is missing): the template's
// build cost for the player (0x0033A69A with 0 and the entry's +0x94 value),
// scaled by the producer's cost factor (slot 0x70); no template gives 0.
Int UnitRevivalEntry::revivalEntryCalcCostToBuild(const Player *player, Object *producer)
{
	float factor = 1.0f;
	if (producer)
	{
		Rva0037E1FDFactor *f = (Rva0037E1FDFactor *)producer->rva0028BC94();
		if (f)
			factor = f->getCostFactor(m_a0);
	}
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(m_templateName);
	if (tmpl)
		return (Int)(tmpl->rva0033A69A(player, 0, m_94) * factor);
	return 0;
}

// stlport
#include <vector>
struct Rva002E2D10Record {
    Rva002E2D10Record(const ThingTemplate *);
    ~Rva002E2D10Record();
    unsigned char pad00[0x0C];
    int rank;
    unsigned char pad10[0xD8-0x10];
};
namespace _STL {
    template<> void vector<Rva002E2D10Record>::push_back(const Rva002E2D10Record &);
}
class Rva0037F32F {
public:
    void rva0037F32F(const ThingTemplate *, Player *);
private:
    unsigned char pad00[4];
    _STL::vector<Rva002E2D10Record> entries;
};
// WB 0x00F5FC20 names addInitialBuildUnit; native 0x0037F32F..0x0037F38F
// independently establishes a complete 96-byte EH body (ret 8). It constructs
// the existing 0xD8 record from the template, puts template rank at +0x0C,
// and appends it to the tracker vector at +4. Retain the established caller
// symbol and pointer ABI; the WB ownership assertion is absent in retail.
void Rva0037F32F::rva0037F32F(const ThingTemplate *thingTemplate, Player *player) {
    Rva002E2D10Record entry(thingTemplate);
    entry.rank = thingTemplate->rva0033B479();
    entries.push_back(entry);
}

// Native 37E94A..37EACA, complete 386-byte constructor from Object*.
// BFME1 ba7ddda7 UnitRevivalTracker.cpp (Rva000FB210Element::ctor) supplies
// the same experience/upgrades/record/RespawnUpdate sequence. BFME2's
// 0xD8 record adds the +A1 flag, +AC value, +C8/+CC state and +D0 display
// string; all offsets and constructor calls are established by retail.
// WB lead and the paired constructor at 00EFE320 support this revival
// record identity through the same calls and fields. The folded
// experience-level getter has the exact 2C->C access, same 7 bytes and
// no relocations as the meshgeometry-owned body. Its address name does
// not assert an original member name. /Ob1 keeps that verified call.
UnitRevivalEntry::UnitRevivalEntry(Object *object)
	: m_moduleID(0)
	, m_unknown04(0)
	, m_experience(object->getExperience()->getExperienceValue())
	, m_rank(object->getExperience()->getLevelRank())
	, m_level(object->getExperience()->rva000B49A1())
	, m_upgrades(object->upgrades)
	, m_94(0)
	, m_reviveStartFrame(-1)
	, m_9c(0)
	, m_a0(true)
	, m_a1((object->flags & 0x10)!=0)
	, m_productionID(0)
	, m_a8(object->field45c)
	, m_ac(object->field460)
	, m_record(object->record)
	, m_c8(0)
	, m_factor(1.0f)
	, m_displayName(*reinterpret_cast<const AsciiString*>(reinterpret_cast<const char*>(object)+0x88))
	, m_templateName()
{
 RevivalTemplateView *t = object->thingTemplate;
 static NameKeyType respawnUpdateKey = TheNameKeyGenerator->nameToKey("RespawnUpdate");
 Module *module = object->findModule(respawnUpdateKey);
 if (module) {
  m_moduleID = module->v14();
  m_94 = reinterpret_cast<Rva004AFB01*>(module)->rva004AFB01();
  m_9c = reinterpret_cast<Rva004AFB01*>(module)->rva004AFB16();
  t = static_cast<RevivalTemplateView*>(reinterpret_cast<RespawnUpdate*>(module)->rva004AF25D());
 }
 m_templateName.setCopyInline(t ? t->name : AsciiString::TheEmptyString);
}

// Native2E134C..2E1451 complete261B copy of the same D8 revival record.
UnitRevivalEntry::UnitRevivalEntry(const UnitRevivalEntry &other)
	: m_moduleID(other.m_moduleID)
	, m_unknown04(other.m_unknown04)
	, m_experience(other.m_experience)
	, m_rank(other.m_rank)
	, m_level(other.m_level)
	, m_upgrades(other.m_upgrades)
	, m_94(other.m_94)
	, m_reviveStartFrame(other.m_reviveStartFrame)
	, m_9c(other.m_9c)
	, m_a0(other.m_a0)
	, m_a1(other.m_a1)
	, m_productionID(other.m_productionID)
	, m_a8(other.m_a8)
	, m_ac(other.m_ac)
	, m_record(other.m_record)
	, m_c8(other.m_c8)
	, m_factor(other.m_factor)
	, m_displayName(other.m_displayName)
	, m_templateName(other.m_templateName)
{
}

#include <bitset>
namespace _STL { template<> void _Base_bitset<32>::_M_do_or(const _Base_bitset<32>&); }
struct RevivalLogicFlags { char pad[0x98]; bool flag; bool getFlag() const { return flag; } void setFlag(bool b) { flag=b; } };
// WB F60270 names the complete native 37EF5D..37F26D body. All D8
// record accesses and the creation/revival/science calls below are native.
Object *UnitRevivalTracker::productionSystemNewObject(unsigned int productionID,const Coord3D *position)
{
    for (UnitRevivalEntry *it=begin(); it!=end(); ++it) {
        if (it->m_productionID==productionID) {
            UnitRevivalEntry entry(*it);
            const ThingTemplate *thingTemplate=static_cast<const ThingTemplate*>(entry.getThingTemplate());
            if (!thingTemplate) return 0;
            CreateMask mask;
            memset(&mask,0,sizeof(mask));
            Player *player=reinterpret_cast<Player*>(m_10);
            Team *team=*reinterpret_cast<Team**>(reinterpret_cast<char*>(player)+0x2EC);
            Object *object=TheThingFactory->newObject(thingTemplate,team,&mask,false);
            object->teleportTo(position,false);
            object->rva0028BAAE(entry.m_a8);
            object->field460=entry.m_ac;
            *reinterpret_cast<Rva001EAFC1*>(&object->record)=*reinterpret_cast<const Rva001EAFC1*>(&entry.m_record);
            TheScriptEngine->rva00357960(entry.m_displayName,object);
            if (entry.m_a1) object->flags|=0x10;
            object->updateShroudNow();
            int level=1;
            if (entry.m_a0 || entry.m_experience>1.0f) {
                bool oldFlag=reinterpret_cast<RevivalLogicFlags*>(TheGameLogic)->getFlag();
                reinterpret_cast<RevivalLogicFlags*>(TheGameLogic)->setFlag(false);
                reinterpret_cast<ExperienceTracker*>(object->getExperience())->rva0039B315(entry.m_experience-1.0f,false,false,false,false);
                reinterpret_cast<Rva0039B20C*>(object->getExperience())->rva0039B227(entry.m_level);
                *reinterpret_cast<bool*>(reinterpret_cast<char*>(object->getExperience())+0x20)=entry.m_record.flag;
                reinterpret_cast<_STL::_Base_bitset<32>*>(&object->upgrades)->_M_do_or(*reinterpret_cast<const _STL::_Base_bitset<32>*>(&entry.m_upgrades));
                level=entry.m_rank;
                reinterpret_cast<RevivalLogicFlags*>(TheGameLogic)->setFlag(oldFlag);
            }
            if (reinterpret_cast<const unsigned char*>(object->thingTemplate)[0x11F]&0x40) {
                int objectID=*reinterpret_cast<const int*>(reinterpret_cast<const char*>(object)+0x74);
                CreateAHeroData *hero=TheCreateAHeroManager->rva002197A6(objectID);
                if (hero) reinterpret_cast<CreateAHeroHero*>(hero)->UpdateCommandSet(level);
            }
            static NameKeyType respawnUpdateKey=TheNameKeyGenerator->nameToKey("RespawnUpdate");
            Module *module=object->findModule(respawnUpdateKey);
            if (module) reinterpret_cast<unsigned char*>(module)[0x41]=!entry.m_a0;
            if (object->getDrawable()) object->getDrawable()->rva00274176(true);
            ScienceType science=TheScienceStore->getScienceFromInternalName(AsciiString("SCIENCE_GandalftheWhite"));
            if (reinterpret_cast<Player*>(m_10)->hasScience(science) && (reinterpret_cast<const unsigned char*>(object->thingTemplate)[0x11D]&1)) {
                object->addAttributeModifierToPool(AsciiString("SpellBookGandalfWhite"),-1);
                object->rva0028B265();
            }
            science=TheScienceStore->getScienceFromInternalName(AsciiString("SCIENCE_Anduril"));
            if (reinterpret_cast<Player*>(m_10)->hasScience(science) && (reinterpret_cast<const unsigned char*>(object->thingTemplate)[0x11D]&2)) {
                object->addAttributeModifierToPool(AsciiString("SpellBookAnduril"),-1);
            }
            rva0037EF2D(productionID);
            return object;
        }
    }
    return 0;
}
