// cl: /O1 /DNDEBUG /MD
//
// ?rva0036E071@AIGroup@@QBE_NXZ, retail 0x0036E071, 69 bytes.
// AIGroup predicate walk like isIdle 0x0036DF4D. Evidence: same list loop,
// Object+0x258 AIUpdate plus +0x438 bit0 EFFECTIVELY_DEAD, AIUpdate virtual
// slot 113 (+0x1c4) predicate, all members must pass and be not-dead.
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

class AIUpdateInterface : public BfmeVirtualSlots<113>
{
public:
	virtual Bool pred113() const;
};

class Object
{
public:
	const AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	char m_pad258[0x258];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus; // +0x438
};

class AIGroup
{
public:
	Bool rva0036E071() const;

private:
	std::list<Object *> m_memberList;
};

Bool AIGroup::rva0036E071() const
{
	std::list<Object *>::const_iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (!obj)
			continue;
		const AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai)
			continue;
		if (!ai->pred113())
			return false;
		if (obj->isEffectivelyDead())
			return false;
	}
	return true;
}
