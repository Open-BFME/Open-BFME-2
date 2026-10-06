// cl: /DNDEBUG /MD
//
// ?isIdle@AIGroup@@QBE_NXZ, retail 0x0036DF4D, 69B.
// BFME1 AIGroupStatePredicates donor isIdle (0x151280 73B) via ZH AIGroup.
// Evidence: same list loop as groupAttackTeam/groupHunt in AIGroupAttackTeam;
// Object+0x258 AIUpdate (existing) plus +0x438 bit0 EFFECTIVELY_DEAD (Turret
// precedent); AIUpdateInterface::isIdle virtual slot 110 (+0x1b8) for BFME2
// (BFME1 slot 96); callers at 0x20C9E0 0x20CCAF 0x2624DF 0x372C08 0x378A38.

#include <list>

typedef bool Bool;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<110>
{
public:
	virtual Bool isIdle() const;
};

class Object
{
public:
	const AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	char m_pad258[0x258];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;
};

class AIGroup
{
public:
	Bool isIdle() const;

private:
	std::list<Object *> m_memberList;
};

Bool AIGroup::isIdle() const
{
	Bool isIdle = true;
	std::list<Object *>::const_iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		Object *obj = *i;
		if (!obj) {
			continue;
		}

		const AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}

		isIdle = ai->isIdle() || obj->isEffectivelyDead();
		if (!isIdle) {
			return false;
		}
	}

	return isIdle;
}
