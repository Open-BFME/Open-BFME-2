// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /EHsc /G7
//
// BFME2 Object module accessors, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/GameLogic/Object/Object.cpp).
// The behaviors and body getters are no longer defined here: retail's
// 7-byte getters at 0x00313E8C (+0x18C) and 0x00313E9A (+0x194) are
// GameWindow::winGetEnabledTextColor / winGetDisabledTextColor (every caller
// is a GameWindow gadget draw callback), and BFME 2's Object keeps its
// behavior list at +0x244 (the matched Object::findModule 0x0028B6D6).

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BehaviorModule;
class BodyModuleInterface;
class StealthUpdate;
class AIUpdateInterface;
class RadarObject;

typedef bool Bool;
typedef unsigned int UnsignedInt;
enum ObjectID;

// Bit indices only; the values live in the callers' headers. Opaque here so
// this TU claims no numbering it has not measured.
enum ObjectStatusTypes;
enum KindOfType;
enum WeaponSetType
{
	WEAPONSET_NONE = 0
};

class Object;
class ThingTemplate
{
public:
	unsigned char m_pad[0x64];
	const char *m_nameData64;
	unsigned char m_pad68[0x548 - 0x68];
	const char *getNameText() const { return m_nameData64 ? m_nameData64 + 8 : ""; }
	int m_val548;
};
template <int N> class BitFlags
{
public:
	bool any() const;

private:
	unsigned int m_words[(N + 31) / 32];
};
// The existing rowed 128-byte copy and STLport OR helpers used by the
// upgrade-module update sibling (ObjectUpdateUpgradeModules.cpp).
struct BfmeFixedStorage128
{
 BfmeFixedStorage128(const BfmeFixedStorage128 &);
 unsigned char bytes[128];
};
namespace _STL
{
 template<unsigned N> struct _Base_bitset;
 template<> struct _Base_bitset<32>
 {
  void _M_do_or(const _Base_bitset<32> &);
  unsigned long _M_w[32];
 };
}

class Player
{
public:
	void rva002AB8FB(Object *obj, bool flag);
	char m_pad00[0x38];
	const unsigned short *m_displayNameData38;
	char m_pad3C[0x54 - 0x3C];
	int m_playerIndex54;
	char m_pad58[0x13C - 0x58];
	const unsigned short *getPlayerDisplayNameText() const { return m_displayNameData38 ? m_displayNameData38 + 4 : (const unsigned short *)L""; }
	int getPlayerIndex() const { return m_playerIndex54; }
	BfmeFixedStorage128 m_upgradeMask13C;
};
class Rva004DF207
{
public:
	void rva004DF207(void *arg);
};
class Rva004DF231
{
public:
	void rva004DF231(void *arg);
};
struct Rva00293DACNode
{
	Rva00293DACNode *m_next;
	Rva00293DACNode *m_prev;
	Object *m_object;
};
struct Rva00293DACList
{
	Rva00293DACNode *m_head;
};
struct Rva00293DACRange
{
	int m_00;
	const Rva00293DACList *m_list;
};
template <int N> class Rva00293DACSlots : public Rva00293DACSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00293DACSlots<0>
{
};
class Rva00293DACIface : public Rva00293DACSlots<66>
{
public:
	virtual void rva00293DACSlot66(Rva00293DACRange *out) = 0;
};

enum CommandSourceType;
enum WeaponSlotType;
enum WeaponLockType;
class SpecialPowerTemplate;
class AICommandInterface
{
public:
 void aiIdle(CommandSourceType);
 void aiAttackPosition(const Coord3D *, int, CommandSourceType);
};
class Rva00295A0FCommands
{
public:
 void Rva00295A0FCommand(void *, int, int);
};
class Rva00297149AI
{
public:
 char m_pad00[0x20];
 AICommandInterface m_commands20;
};
class CommandButton
{
public:
 const ThingTemplate *rva0035B570() const;
 char m_pad00[0x14];
 int m_command14;
 char m_pad18[4];
 unsigned int m_options1C;
 char m_pad20[0x44 - 0x20];
 const SpecialPowerTemplate *m_power44;
 char m_pad48[0x80 - 0x48];
 WeaponSlotType m_weaponSlot80;
 char m_pad84[0xA0 - 0x84];
 int m_maxShotsA0;
};
class BuildAssistant
{
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04(); virtual void slot05();
 virtual void slot06(); virtual void slot07(); virtual void slot08();
 virtual void slot09(); virtual void slot10(); virtual void slot11();
 virtual void slot12(); virtual void slot13();
 virtual void buildObjectNow(Object *, const ThingTemplate *, const Coord3D *, float, Player *);
};
extern BuildAssistant *TheBuildAssistant;

class Object
{
public:
	friend AsciiString DescribeObject(const Object *);
	ObjectID getID() const { return m_id74; }
	StealthUpdate *getStealth() const;
	AIUpdateInterface *getAI();
	RadarObject *friend_getRadarData();
	void *rva00313EA8() const;
	Bool testStatus( ObjectStatusTypes bit ) const;
	Bool isKindOf( KindOfType kind ) const;
	Player *getControllingPlayer() const;
	void removeFromList(Object **head, Object **tail);
	void setReceivingDifficultyBonus(bool receive);
	void friend_adjustPowerForPlayer(bool incoming);
	Object *rva002931F5(bool flag);
	void *rva0028C197() const;
	__declspec(noinline) void rva0028C24C();
	bool setWeaponLock(WeaponSlotType, WeaponLockType);
	void doSpecialPowerAtLocation(const SpecialPowerTemplate *, const Coord3D *, unsigned int, bool);
	void rva00297149(const CommandButton *, const Coord3D *, int, int);
	void rva001E42F2(const int *x);
	void rva001E431E(const int *x);
	void rva0028CFB2(const int *a, const int *b);
	void rva0028CFF5(const int *a, bool b);
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
	void setWeaponSetFlagForHorde(WeaponSetType wst);
	void clearWeaponSetFlagForHorde(WeaponSetType wst);
	void clearModelConditionFlagsForHorde(const int *x);
	void setModelConditionFlagsForHorde(const int *x);
	void clearAndSetModelConditionFlagsForHorde(const int *a, const int *b);
	void replaceModelConditionFlagsForHorde(const int *a, bool b);

private:
	unsigned char m_pre000[4];		// +0x00..0x04
	ThingTemplate *m_template004;	// +0x04
	unsigned char m_pre008[0x74 - 0x08];
	ObjectID m_id74;
	unsigned char m_pad78[0x88 - 0x78];
	AsciiString m_name88;	// +0x08..0x8C
	Object *m_prev8C;			// +0x8C
	Object *m_next90;			// +0x90
	unsigned int m_statusBits[3];		// +0x94, ObjectStatus bits (86-bit per BFME1)
	unsigned char m_0A0[0x6C];		// +0xA0..0x10C
	unsigned int m_kindOfBits[14];		// +0x10C, KindOf bits (max observed bit 442)
	unsigned char m_144[0x48];		// +0x144..0x18C
	BehaviorModule **m_behaviors;	// +0x18C
	void *m_contain;			// +0x190
	BodyModuleInterface *m_body;	// +0x194
	StealthUpdate *m_stealth;	// +0x198
	AIUpdateInterface *m_ai;	// +0x19C
	void *m_1A0;			// +0x1A0
	void *m_1A4;			// +0x1A4
	RadarObject *m_radarData;	// +0x1A8
	unsigned char m_pad1AC[0x1C8 - 0x1AC];	// +0x1AC..0x1C8
	BitFlags<11> m_disabled1C8;		// +0x1C8
	unsigned char m_pad1CC[0x258 - 0x1CC];
	Rva00297149AI *m_commandAI258;
	unsigned char m_pad25C[0x43C - 0x25C];	// +0x1CC..0x43C
	bool m_receivingDifficultyBonus;	// +0x43C
	unsigned char m_pad43D[0x458 - 0x43D];
	int m_deadline458;
};

// Retail 0x0028B595 (89 bytes): unlink this Object from a doubly-linked list
// and update both the head and tail when this Object is at either end.
void Object::removeFromList(Object **a, Object **b)
{
	if (m_prev8C != 0)
		m_prev8C->m_next90 = m_next90;
	else
		*b = m_next90;
	if (m_next90 != 0)
		m_next90->m_prev8C = m_prev8C;
	else
		*a = m_prev8C;
	m_next90 = 0;
	m_prev8C = 0;
}

// Retail 0x0028B238 (45 bytes): update the Object's difficulty-bonus flag and
// notify its controlling Player when the value changes.
void Object::setReceivingDifficultyBonus(bool flag)
{
	if (flag == m_receivingDifficultyBonus)
		return;
	m_receivingDifficultyBonus = flag;
	Player *p = getControllingPlayer();
	if (p == 0)
		return;
	p->rva002AB8FB(this, m_receivingDifficultyBonus);
}

// Retail 0x0028D99A (75 bytes): update the Player's influence power state for
// an eligible Object. The disabled/energy guard matches Zero Hour's method.
void Object::friend_adjustPowerForPlayer(bool flag)
{
	if (m_disabled1C8.any() && m_template004->m_val548 > 0)
		return;
	Player *player = getControllingPlayer();
	if (!player)
		return;
	Rva004DF207 *power = (Rva004DF207 *)((char *)player + 0x1BC);
	if (!power)
		return;
	if (flag)
		power->rva004DF207(this);
	else
		((Rva004DF231 *)power)->rva004DF231(this);
}

// ?getStealth@Object@@QBEPAVStealthUpdate@@XZ
inline StealthUpdate *Object::getStealth() const
{
	return m_stealth;
}

// ?getAI@Object@@QAEPAVAIUpdateInterface@@XZ
inline AIUpdateInterface *Object::getAI()
{
	return m_ai;
}

// ?friend_getRadarData@Object@@QAEPAVRadarObject@@XZ
RadarObject *Object::friend_getRadarData()
{
	return m_radarData;
}

// ?rva00313EA8@Object@@QBEPAXXZ
// Retail 0x00313EA8. Unclaimed 7B getter in the Object module run at
// 0x313E8C..0x313EBD (behaviors/body/stealth/ai/radar all 7B here). Reads
// [ecx+0x1A4], the slot between m_1A0 and m_radarData. Same-Object evidence:
// FUN_004A03BF calls it on the same esi as the five proven getters and caches
// the result alongside radar/ai (0xA0440/0xA044A/0xA0454). Semantic identity
// (physics vs contain vs disabledMask vs partitionData) unproven, so the name
// keeps the address token per the opaque convention.
void *Object::rva00313EA8() const
{
	return m_1A4;
}

// ?testStatus@Object@@QBE_NW4ObjectStatusTypes@@@Z
// Retail 0x0004E536. Plain bit test over the status words at +0x94; the bit
// indices callers pass run past 70, so this is the ObjectStatus mask, and the
// same shape with the KindOf mask below is isKindOf.
inline Bool Object::testStatus( ObjectStatusTypes bit ) const
{
	return ( m_statusBits[(UnsignedInt)bit >> 5] & ( 1 << ( bit & 31 ) ) ) != 0;
}

// ?isKindOf@Object@@QBE_NW4KindOfType@@@Z
// Retail 0x0006F039. Same shape over the KindOf words at +0x10C; callers pass
// bits past 400, which only the KindOf mask spans.
inline Bool Object::isKindOf( KindOfType kind ) const
{
	return ( m_kindOfBits[(UnsignedInt)kind >> 5] & ( 1 << ( kind & 31 ) ) ) != 0;
}

// Retail 0x00293DAC (92 bytes): update this Object and each Object in its
// passenger list. The interface slot and list layout match the adjacent
// passenger operations in ObjectConditionAndPassengerWeaponSet.cpp.
void Object::setWeaponSetFlagForHorde(WeaponSetType wst)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->setWeaponSetFlag(wst);
			top->setWeaponSetFlag(wst);
		}
	}
}

// Retail 0x00293E08 (92 bytes): clear the same flag on this Object and each
// Object in its passenger list.
void Object::clearWeaponSetFlagForHorde(WeaponSetType wst)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->clearWeaponSetFlag(wst);
			top->clearWeaponSetFlag(wst);
		}
	}
}

// Retail 0x00293BBF (92 bytes): clear the requested model-condition mask on
// this Object and every Object returned by the passenger interface.
void Object::clearModelConditionFlagsForHorde(const int *x)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva001E42F2(x);
			top->rva001E42F2(x);
		}
	}
}

// Retail 0x00293C1B (92 bytes): set the requested model-condition mask on
// this Object and every Object returned by the passenger interface.
void Object::setModelConditionFlagsForHorde(const int *x)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva001E431E(x);
			top->rva001E431E(x);
		}
	}
}

// Retail 0x00293C77 (98 bytes): clear one mask and set another on this
// Object and every Object returned by the passenger interface.
void Object::clearAndSetModelConditionFlagsForHorde(const int *a, const int *b)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva0028CFB2(a, b);
			top->rva0028CFB2(a, b);
		}
	}
}

// Retail 0x00293CD9 (98 bytes): replace this Object's mask and the mask of
// every Object returned by the passenger interface.
void Object::replaceModelConditionFlagsForHorde(const int *a, bool b)
{
	Object *top = rva002931F5(false);
	if (top)
	{
		Rva00293DACIface *iface = (Rva00293DACIface *)top->rva0028C197();
		if (iface)
		{
			Rva00293DACRange range;
			iface->rva00293DACSlot66(&range);
			for (Rva00293DACNode *node = range.m_list->m_head->m_next; node != range.m_list->m_head; node = node->m_next)
				node->m_object->rva0028CFF5(a, b);
			top->rva0028CFF5(a, b);
		}
	}
}

// These are header inlines that the units including the header emit as
// select-any copies, which plain definitions here collided with. The anchor
// keeps this unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeObjectAccessorInlineAnchor absent-from-retail
void _bfmeObjectAccessorInlineAnchor(Object *o)
{
    o->getStealth();
    o->getAI();
    o->testStatus((ObjectStatusTypes)0);
    o->isKindOf((KindOfType)0);
}
#pragma inline_depth()

// Native 28D680..28D6EB RET0: copy the Player mask, combine the Object
// mask, then visit already-upgraded modules and invoke their slot 5.
// WB CCF320 calls this refreshUpgradeModules (callsite-only score 1);
// retain the established address-qualified name rather than promote the lead.
// GameLogicRva0023D68EAndD6FA.cpp supplies Object-list receivers. Mask offsets
// 13C/284 and the behavior subobject at module+C agree independently with
// the matched ObjectUpdateUpgradeModules.cpp. Slot 5's precise name is unknown.
class Rva0028D680Upgrade
{
public:
 virtual bool isAlreadyUpgraded() const = 0;
 virtual void slot01() = 0;
 virtual void slot02() = 0;
 virtual void slot03() = 0;
 virtual void slot04() = 0;
 virtual void slot05() = 0;
};
class Rva0028D680Behavior
{
public:
 virtual void slot00() = 0;
 virtual void slot01() = 0;
 virtual void slot02() = 0;
 virtual void slot03() = 0;
 virtual void slot04() = 0;
 virtual void slot05() = 0;
 virtual void slot06() = 0;
 virtual void slot07() = 0;
 virtual void slot08() = 0;
 virtual void slot09() = 0;
 virtual Rva0028D680Upgrade *getUpgrade() = 0;
};
class Rva0028D680Module
{
public:
 char m_pad00[0x0C];
};
class Rva0028D680
{
public:
 void rva0028D680();
 char m_pad00[0x244];
 Rva0028D680Module **m_modules;
 char m_pad248[0x284 - 0x248];
 _STL::_Base_bitset<32> m_upgradeMask284;
};

void Rva0028D680::rva0028D680()
{
 Player *player = ((Object *)this)->getControllingPlayer();
 if (!player)
  return;
 BfmeFixedStorage128 upgrades(player->m_upgradeMask13C);
 ((_STL::_Base_bitset<32> *)&upgrades)->_M_do_or(m_upgradeMask284);
 for (Rva0028D680Module **m = m_modules; *m; ++m)
 {
  Rva0028D680Behavior *behavior = (Rva0028D680Behavior *)((char *)*m + 0x0C);
  Rva0028D680Upgrade *upgrade = behavior->getUpgrade();
  if (upgrade && upgrade->isAlreadyUpgraded())
   upgrade->slot05();
 }
}

// DescribeObject: ZH/BFME1 Object.cpp supplies the semantic formatter.
// Native28F982..28FAD1 and WB CBA140 witness the two formats and null-owner
// additions. Object ID74/name88/template4->name64 and Player display38/index54
// are target facts; pointer fields denote the existing StringBase storage.
// The access views preserve the witnessed header+8 payload/empty literals.
AsciiString DescribeObject(const Object *obj)
{
 if (!obj)
  return "<No Object>";
 Player *owner = obj->getControllingPlayer();
 AsciiString result;
 if (!((const StringBase<char> *)&obj->m_name88)->isEmpty())
 {
  result.format("Object %d (%s) [%s, owned by player %d (%ls)]",
   obj->getID(), obj->m_name88.str(), obj->m_template004->getNameText(),
   owner ? owner->getPlayerIndex() : 0,
   owner ? owner->getPlayerDisplayNameText() : (const unsigned short *)L"<unknown>");
 }
 else
 {
  result.format("Object %d [%s, owned by player %d (%ls)]",
   obj->getID(), obj->m_template004->getNameText(),
   owner ? obj->getControllingPlayer()->getPlayerIndex() : 0,
   owner ? obj->getControllingPlayer()->getPlayerDisplayNameText() : (const unsigned short *)L"<unknown>");
 }
 return result;
}

// Consolidated from Rva0028C24CFinish.cpp. The native24B helper leaves ECX
// unchanged; the dispatcher below relies on the compiler seeing this body.
// Keep its established global owner (data ledger RVA9BA4E4), frame40 and
// deadline458. No inline expansion: retail still calls the separate helper.
extern int g_Va00DBA4E4;
extern GameLogic *TheGameLogic;

void Object::rva0028C24C()
{
 m_deadline458 = g_Va00DBA4E4 * 10 + TheGameLogic->getFrame();
}

// ZH Object::doCommandButtonAtPosition is the semantic guide. WB CDDF80
// and native297149..29725B RET16 establish the BFME2 cases and fourth byte
// flag:24/38 power commands;10 attack-move;14 idle;53 build;23 weapon fire.
// The build virtual's five arguments are pushed around the const template
// getter (its RET0 takes no arguments). Deadline helper28C24C is visible and
// preserves ECX; do not duplicate the original separate provider unit.
void Object::rva00297149(const CommandButton *button, const Coord3D *position, int source, int flag)
{
 if (m_disabled1C8.any())
  return;
 Rva00297149AI *ai = m_commandAI258;
 if (!button)
  return;
 switch (button->m_command14)
 {
 case 24:
 case 38:
  if (button->m_power44)
  {
   unsigned int options = button->m_options1C | 0x40000;
   if ((unsigned char)flag)
    options |= 0x20000000;
   doSpecialPowerAtLocation(button->m_power44, position, options, source == 1);
  }
  break;
 case 10:
  if (ai)
   ((Rva00295A0FCommands *)&ai->m_commands20)->Rva00295A0FCommand((void *)position, button->m_maxShotsA0, source);
  break;
 case 14:
  if (ai)
   ai->m_commands20.aiIdle((CommandSourceType)source);
  break;
 case 53:
  TheBuildAssistant->buildObjectNow(this, button->rva0035B570(), position, 0.0f, getControllingPlayer());
  break;
 case 23:
  rva0028C24C();
  setWeaponLock(button->m_weaponSlot80, (WeaponLockType)1);
  if (ai)
   ai->m_commands20.aiAttackPosition(position, 1, (CommandSourceType)source);
  break;
 }
}
