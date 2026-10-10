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
	unsigned char m_pad54C[0x5D8 - 0x54C];
	unsigned short m_5D8;
};
template <int N> class BitFlags
{
public:
	bool any() const;
	bool test(const void *other) const;
	bool anyIntersectionWith(const BitFlags &that) const { return test(&that); }

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
struct Rva00296749IntVector
{
 int size() const { return m_finish - m_start; }
 int *m_start;
 int *m_finish;
 int *m_endOfStorage;
};
class CommandButton
{
public:
 const ThingTemplate *rva0035B570() const;
 int getStance(int index);
 char m_pad00[0x10];
 AsciiString m_name10;
 int m_command14;
 char m_pad18[4];
 unsigned int m_options1C;
 char m_pad20[4];
 const void *m_upgrade24;
 char m_pad28[0x44 - 0x28];
 const SpecialPowerTemplate *m_power44;
 char m_pad48[0x80 - 0x48];
 WeaponSlotType m_weaponSlot80;
 char m_pad84[0xA0 - 0x84];
 int m_maxShotsA0;
 char m_padA4[0xC0 - 0xA4];
 int m_C0;
 char m_padC4[0x234 - 0xC4];
 Rva00296749IntVector m_stances234;
};

// Views for Object::doCommandButton (0x00296749). Offsets are retail facts
// read from that body; slot names stay neutral where WB gives none.
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
 NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
 virtual void rva00296749ModuleSlot00();
};

// The update interface sits at +0x10 of the auto-ability module; slot 1 is
// ZH UpdateModuleInterface::getDisabledTypesToProcess (hidden return slot).
class Rva00296749ModuleHead
{
public:
 virtual void rva00296749HeadSlot00();
 char m_pad04[0x0C];
};
class Rva00296749UpdateInterface
{
public:
 virtual void update();
 virtual BitFlags<11> getDisabledTypesToProcess() const;
};
class Rva00296749AutoAbility : public Rva00296749ModuleHead, public Rva00296749UpdateInterface
{
};

// Gate behaviors are reached through a Module base at +4.
class Rva00296749GateInterface
{
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02();
 virtual void slot03(); virtual void slot04(); virtual void slot05();
 virtual bool slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual bool slot10();
};
class Rva00296749Gate : public Rva00296749GateInterface, public Module
{
};

class Rva00296749Production
{
public:
 virtual void slot00(); virtual void slot01();
 virtual int requestUniqueUnitID(int a, int b, const AsciiString &name, int d);
 virtual void queueUpgrade(const void *upgrade);
 virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
 virtual bool queueCreateUnit(const ThingTemplate *unitType, int quantity, int productionID);
};

class Player;
class Rva00296749Toggle
{
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(int arg);
 virtual void slot05(); virtual void slot06();
 virtual bool slot07(Player *player);
 virtual bool slot08();
 virtual void slot09(); virtual void slot10(); virtual void slot11(); virtual void slot12();
 virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
 virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
 virtual void slot21(int arg);
 virtual bool slot22(Player *player);
 virtual void slot23(); virtual void slot24();
 virtual bool slot25();
 virtual void slot26();
};

class CastleBehavior
{
public:
 static NameKeyType rva0003955DA();
 void initiateUnpack(bool flag, const ThingTemplate *tt);
 void initiatePack();
};
class Rva0039567CCmpBoolField { public: bool get() const; };
class Rva00397F45 { public: bool rva00397F45(Player *player, int cmdSource); };
class Rva0039718B { public: bool rva0039718B(Player *player); };
class Rva00395F57 { public: bool canUnpack(bool flag); };
class Rva00395686 { public: bool rva00395686(Player *player, ThingTemplate *tt); };

class StancesBehavior { public: void rva0045F084(int stance); };
NameKeyType Rva0045EE2CGet();

class Rva0035B164 { public: int rva0035B164(int value); };

enum WeaponStatus { WEAPON_STATUS_NONE = 0 };
struct Rva00296749WeaponTemplate
{
 char m_pad00[0x16A];
 bool m_16A;
};
class Weapon
{
public:
 WeaponStatus computeStatus(bool *out) const;
 void cacheStatus(WeaponStatus status) const;
 char m_pad00[4];
 const Rva00296749WeaponTemplate *m_template04;
 char m_pad08[0x18 - 0x08];
 mutable int m_18;
};

class FiringTracker
{
 friend class Object;
 void coolDown(bool flag);
};

class GameMessage
{
public:
 enum Type { MSG_RVA00296749_NONE = 0 };
 void appendObjectIDArgument(ObjectID id);
 void appendIntegerArgument(int value);
};
class MessageStream
{
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual void s16(); virtual void s17();
 virtual GameMessage *appendMessage(GameMessage::Type type);
};
extern MessageStream *TheMessageStream;

class DrawableList;
class PickAndPlayInfo;
void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type, PickAndPlayInfo *info);
class InGameUI
{
public:
#define RVA00296749_SLOT(N) virtual void s##N();
 RVA00296749_SLOT(00) RVA00296749_SLOT(01) RVA00296749_SLOT(02) RVA00296749_SLOT(03)
 RVA00296749_SLOT(04) RVA00296749_SLOT(05) RVA00296749_SLOT(06) RVA00296749_SLOT(07)
 RVA00296749_SLOT(08) RVA00296749_SLOT(09) RVA00296749_SLOT(10) RVA00296749_SLOT(11)
 RVA00296749_SLOT(12) RVA00296749_SLOT(13) RVA00296749_SLOT(14) RVA00296749_SLOT(15)
 RVA00296749_SLOT(16) RVA00296749_SLOT(17) RVA00296749_SLOT(18) RVA00296749_SLOT(19)
 RVA00296749_SLOT(20) RVA00296749_SLOT(21) RVA00296749_SLOT(22) RVA00296749_SLOT(23)
 RVA00296749_SLOT(24) RVA00296749_SLOT(25) RVA00296749_SLOT(26) RVA00296749_SLOT(27)
 RVA00296749_SLOT(28) RVA00296749_SLOT(29) RVA00296749_SLOT(30) RVA00296749_SLOT(31)
 RVA00296749_SLOT(32) RVA00296749_SLOT(33) RVA00296749_SLOT(34) RVA00296749_SLOT(35)
 RVA00296749_SLOT(36) RVA00296749_SLOT(37) RVA00296749_SLOT(38) RVA00296749_SLOT(39)
 RVA00296749_SLOT(40) RVA00296749_SLOT(41) RVA00296749_SLOT(42) RVA00296749_SLOT(43)
 RVA00296749_SLOT(44) RVA00296749_SLOT(45) RVA00296749_SLOT(46)
 virtual void slot47(void *arg);
 RVA00296749_SLOT(48) RVA00296749_SLOT(49) RVA00296749_SLOT(50) RVA00296749_SLOT(51)
 RVA00296749_SLOT(52) RVA00296749_SLOT(53) RVA00296749_SLOT(54) RVA00296749_SLOT(55)
 RVA00296749_SLOT(56) RVA00296749_SLOT(57) RVA00296749_SLOT(58) RVA00296749_SLOT(59)
 RVA00296749_SLOT(60) RVA00296749_SLOT(61) RVA00296749_SLOT(62) RVA00296749_SLOT(63)
 RVA00296749_SLOT(64) RVA00296749_SLOT(65) RVA00296749_SLOT(66) RVA00296749_SLOT(67)
 RVA00296749_SLOT(68) RVA00296749_SLOT(69) RVA00296749_SLOT(70) RVA00296749_SLOT(71)
 RVA00296749_SLOT(72)
#undef RVA00296749_SLOT
 virtual const DrawableList *getAllSelectedDrawables();
};
extern InGameUI *TheInGameUI;

class Debug
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34();
 virtual Debug &operator<<(const char *text);
 virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual void slot4C(int report);
 virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
 virtual void slot60();
 virtual void slot64(); virtual void slot68();
 virtual Debug &slot6C(int first, int second, int third);
};
template <class T> Debug &operator<<(Debug &debug, const StringBase<T> &text);
extern Debug *theDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

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
	void doCommandButton(const CommandButton *commandButton, int cmdSource, bool flags);
	void rva0028DF48(const SpecialPowerTemplate *power, unsigned int options, bool fromScript);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void releaseWeaponLock(WeaponLockType lock);
	void rva0028C20F(int value);
	int rva00294ADD(int entry);
	void *rva0028BC58(int index);
	void *rva0028BD17() const;
	bool rva00293926(KindOfType kind);
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

protected:
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pre000[4];		// +0x00..0x04
	ThingTemplate *m_template004;	// +0x04
	unsigned char m_pre008[0x38 - 0x08];
	Coord3D m_pos38;
	unsigned char m_pre044[0x74 - 0x44];
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
	unsigned char m_pad1CC[0x240 - 0x1CC];
	FiringTracker *m_firingTracker240;
	unsigned char m_pad244[0x258 - 0x244];
	Rva00297149AI *m_commandAI258;
	unsigned char m_pad25C[0x350 - 0x25C];
	int m_350;
	unsigned char m_pad354[0x370 - 0x354];
	unsigned int m_weaponSetFlags370[4];
	unsigned char m_pad380[0x43C - 0x380];	// +0x1CC..0x43C
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

// ?doCommandButton@Object@@QAEXPBVCommandButton@@H_N@Z retail 0x00296749
// 2231 bytes (ret 0xC). WB 0x00CDCAD0 Object::doCommandButton (Object.cpp)
// extends ZH's switch. The third argument gates on AutoAbilityBehavior's
// disabled types; the rest follows the WB cases. This body shares the
// rva0028C24C ECX knowledge with rva00297149 below.
// Target RET 0xC and flag-byte uses establish the bool third argument.
// The same-valued firing-tracker PHI preserves retail ESI=this / EDI=button.
void Object::doCommandButton(const CommandButton *commandButton, int cmdSource, bool flags)
{
	if (flags)
	{
		static NameKeyType autoAbilityKey = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
		Rva00296749AutoAbility *autoAbility = (Rva00296749AutoAbility *)findModule(autoAbilityKey);
		if (m_disabled1C8.any())
		{
			if (!autoAbility->getDisabledTypesToProcess().anyIntersectionWith(m_disabled1C8))
				return;
		}
	}
	else if (m_disabled1C8.any())
		return;

	Rva00297149AI *ai = m_commandAI258;
	if (!commandButton)
		return;

	switch (commandButton->m_command14)
	{
	case 24:
	case 38:
		if (commandButton->m_power44)
		{
			unsigned int options = commandButton->m_options1C | 0x40000;
			if (flags)
				options |= 0x20000000;
			rva0028DF48(commandButton->m_power44, options, cmdSource == 1);
		}
		break;

	case 14:
		if (ai)
			ai->m_commands20.aiIdle((CommandSourceType)cmdSource);
		break;

	case 27:
		setWeaponLock(commandButton->m_weaponSlot80, (WeaponLockType)2);
		break;

	case 49:
	{
		int value = 0;
		unsigned int options = commandButton->m_options1C;
		if (options & 0x2000)
			value = 1;
		else if (options & 0x4000)
			value = 2;
		else if (options & 0x8000)
			value = 3;
		rva0028C20F(value);
		break;
	}

	case 35:
	{
		const Weapon *weapon = getCurrentWeapon(0);
		WeaponSlotType slot = (WeaponSlotType)((Rva0035B164 *)commandButton)->rva0035B164(m_350);
		releaseWeaponLock((WeaponLockType)2);
		setWeaponLock(slot, (WeaponLockType)2);
		if (weapon && weapon->m_template04->m_16A && weapon->computeStatus(0))
		{
			const Weapon *current = getCurrentWeapon(0);
			current->m_18 = weapon->m_18;
			current->cacheStatus((WeaponStatus)1);
		}
		break;
	}

	case 45:
	{
		Object *top = rva002931F5(false);
		if (m_weaponSetFlags370[0] & (1 << 24))
		{
			if (top)
				clearWeaponSetFlagForHorde((WeaponSetType)24);
			else
				clearWeaponSetFlag((WeaponSetType)24);
		}
		else
		{
			if (top)
				setWeaponSetFlagForHorde((WeaponSetType)24);
			else
				setWeaponSetFlag((WeaponSetType)24);
		}
		if (ai)
		{
			if (rva00293926((KindOfType)0x25))
				ai->m_commands20.aiIdle((CommandSourceType)2);
			(this?m_firingTracker240:m_firingTracker240)->coolDown(true);
		}
		break;
	}

	case 23:
		rva0028C24C();
		setWeaponLock(commandButton->m_weaponSlot80, (WeaponLockType)1);
		if (ai)
			ai->m_commands20.aiAttackPosition(&m_pos38, 1, (CommandSourceType)cmdSource);
		break;

	case 6:
	case 7:
	case 8:
		if (rva00294ADD((int)commandButton) == 0)
		{
			const void *upgrade = commandButton->m_upgrade24;
			((Rva00296749Production *)rva0028BC58(0))->queueUpgrade(upgrade);
		}
		break;

	case 1:
	case 3:
	case 53:
	{
		const ThingTemplate *tt = commandButton->rva0035B570();
		Rva00296749Production *pu = (Rva00296749Production *)rva0028BC58(0);
		if (pu && tt)
			pu->queueCreateUnit(tt, -1, pu->requestUniqueUnitID(-1, 0, AsciiString::TheEmptyString, 0));
		break;
	}

	case 46:
	{
		Rva00296749Production *pu = (Rva00296749Production *)rva0028BC58(0);
		int quantity = commandButton->m_C0;
		if (pu && quantity != -1)
			pu->queueCreateUnit(0, quantity, pu->requestUniqueUnitID(-1, 0, AsciiString::TheEmptyString, 0));
		break;
	}

	case 34:
	{
		Module *castle = findModule(CastleBehavior::rva0003955DA());
		if (castle && ((Rva0039567CCmpBoolField *)castle)->get())
		{
			if (((Rva00397F45 *)castle)->rva00397F45(getControllingPlayer(), cmdSource) == 1)
				((CastleBehavior *)castle)->initiatePack();
		}
		break;
	}

	case 33:
	{
		Module *castle = findModule(CastleBehavior::rva0003955DA());
		if (castle && ((Rva00395F57 *)castle)->canUnpack(true))
		{
			if (((Rva00397F45 *)castle)->rva00397F45(getControllingPlayer(), cmdSource)
				&& ((Rva0039718B *)castle)->rva0039718B(getControllingPlayer()))
				((CastleBehavior *)castle)->initiateUnpack(false, 0);
		}
		break;
	}

	case 50:
	{
		const ThingTemplate *tt = commandButton->rva0035B570();
		Module *castle = findModule(CastleBehavior::rva0003955DA());
		if (tt && castle && ((Rva00395F57 *)castle)->canUnpack(true))
		{
			if (((Rva00397F45 *)castle)->rva00397F45(getControllingPlayer(), cmdSource)
				&& ((Rva00395686 *)castle)->rva00395686(getControllingPlayer(), const_cast<ThingTemplate *>(tt)))
				((CastleBehavior *)castle)->initiateUnpack(false, tt);
		}
		break;
	}

	case 51:
	{
		Rva00296749Toggle *toggle = (Rva00296749Toggle *)rva0028BD17();
		if (toggle && toggle->slot08() && toggle->slot07(getControllingPlayer()))
			toggle->slot04(0);
		break;
	}

	case 59:
	{
		Rva00296749Toggle *toggle = (Rva00296749Toggle *)rva0028BD17();
		if (toggle && toggle->slot08() && toggle->slot22(getControllingPlayer()))
			toggle->slot21(0);
		break;
	}

	case 60:
	{
		Rva00296749Toggle *toggle = (Rva00296749Toggle *)rva0028BD17();
		if (toggle && toggle->slot25())
			toggle->slot26();
		break;
	}

	case 42:
	{
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), (GameMessage::Type)0x439, 0);
		GameMessage *msg = TheMessageStream->appendMessage((GameMessage::Type)0x439);
		msg->appendObjectIDArgument(getID());
		break;
	}

	case 43:
	{
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), (GameMessage::Type)0x437, 0);
		GameMessage *msg = TheMessageStream->appendMessage((GameMessage::Type)0x437);
		msg->appendObjectIDArgument(getID());
		break;
	}

	case 44:
	{
		static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
		Rva00296749Gate *gate = static_cast<Rva00296749Gate *>(findModule(gateKey));
		if (!gate)
			gate = static_cast<Rva00296749Gate *>(findModule(TheNameKeyGenerator->nameToKey("GateProxyBehavior")));
		if (gate && gate->slot10())
		{
			if (gate->slot06())
			{
				pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), (GameMessage::Type)0x439, 0);
				gate->slot08();
			}
			else
			{
				pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), (GameMessage::Type)0x437, 0);
				gate->slot07();
			}
		}
		break;
	}

	case 17:
		TheInGameUI->slot47(0);
		if (!(commandButton->m_options1C & 0x20))
		{
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), (GameMessage::Type)0x41E, 0);
			TheMessageStream->appendMessage((GameMessage::Type)0x41E);
		}
		break;

	case 40:
		TheInGameUI->slot47(0);
		if (!(commandButton->m_options1C & 0x20))
		{
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), (GameMessage::Type)0x455, 0);
			TheMessageStream->appendMessage((GameMessage::Type)0x455);
		}
		break;

	case 36:
	{
		GameMessage *msg = TheMessageStream->appendMessage((GameMessage::Type)0x453);
		msg->appendObjectIDArgument(getID());
		break;
	}

	case 52:
		if (commandButton->rva0035B570())
		{
			GameMessage *msg = TheMessageStream->appendMessage((GameMessage::Type)0x460);
			msg->appendObjectIDArgument(getID());
			msg->appendIntegerArgument(commandButton->rva0035B570()->m_5D8);
		}
		break;

	case 39:
		TheMessageStream->appendMessage((GameMessage::Type)0x454);
		break;

	case 16:
	{
		GameMessage *msg = TheMessageStream->appendMessage((GameMessage::Type)0x41D);
		msg->appendObjectIDArgument((ObjectID)0);
		msg->appendObjectIDArgument(getID());
		break;
	}

	case 58:
	{
		StancesBehavior *stances = (StancesBehavior *)findModule(Rva0045EE2CGet());
		if (stances)
		{
			if (commandButton->m_stances234.size() < 1)
			{
				if (_bfme_debugReportingEnabled())
				{
					_bfme_debugRecordCallsite(1);
					theDebug->slot60();
					(theDebug->slot6C(0, 0, 0) << "No stance specified for CommandButton: "
						<< *(const StringBase<char> *)&commandButton->m_name10).slot4C(2);
				}
			}
			int stance = const_cast<CommandButton *>(commandButton)->getStance(0);
			if (stance < 0 || stance >= 6)
			{
				if (_bfme_debugReportingEnabled())
				{
					_bfme_debugRecordCallsite(1);
					theDebug->slot60();
					(theDebug->slot6C(0, 0, 0) << "Invalid stance specified form CommandButton: "
						<< *(const StringBase<char> *)&commandButton->m_name10).slot4C(2);
				}
			}
			stances->rva0045F084(stance);
		}
		break;
	}
	}
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
