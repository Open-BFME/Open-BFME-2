// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /EHsc /G7
//
// BFME2 Object module accessors, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/GameLogic/Object/Object.cpp).
// Retail BFME2 keeps this run of module-cache fields at the same offsets:
// behaviors at +0x18C, body at +0x194, stealth at +0x198, ai at +0x19C,
// radar data at +0x1A8.

class BehaviorModule;
class BodyModuleInterface;
class StealthUpdate;
class AIUpdateInterface;
class RadarObject;

typedef bool Bool;
typedef unsigned int UnsignedInt;

// Bit indices only; the values live in the callers' headers. Opaque here so
// this TU claims no numbering it has not measured.
enum ObjectStatusTypes;
enum KindOfType;
enum WeaponSetType
{
	WEAPONSET_NONE = 0
};

class Object;
struct ThingTemplate
{
	unsigned char m_pad[0x548];
	int m_val548;
};
template <int N> class BitFlags
{
public:
	bool any() const;

private:
	unsigned int m_words[(N + 31) / 32];
};
class Player
{
public:
	void rva002AB8FB(Object *obj, bool flag);
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

class Object
{
public:
	BehaviorModule **getBehaviorModules() const;
	BodyModuleInterface *getBodyModule() const;
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
	unsigned char m_pre008[0x8C - 0x08];	// +0x08..0x8C
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
	unsigned char m_pad1CC[0x43C - 0x1CC];	// +0x1CC..0x43C
	bool m_receivingDifficultyBonus;	// +0x43C
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

// ?getBehaviorModules@Object@@QBEPAPAVBehaviorModule@@XZ
inline BehaviorModule **Object::getBehaviorModules() const
{
	return m_behaviors;
}

// ?getBodyModule@Object@@QBEPAVBodyModuleInterface@@XZ
inline BodyModuleInterface *Object::getBodyModule() const
{
	return m_body;
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
    o->getBehaviorModules();
    o->getBodyModule();
    o->getStealth();
    o->getAI();
    o->testStatus((ObjectStatusTypes)0);
    o->isKindOf((KindOfType)0);
}
#pragma inline_depth()
