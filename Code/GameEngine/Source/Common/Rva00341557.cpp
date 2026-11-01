// cl: /MD
//
// ?onExit@Rva00341557@@QAEXH@Z,
// retail 0x00341557, 67 bytes. Dedicated TU.
// Chain of freshly landed ?setCurrentVictim@AIUpdateInterface@@QAEXPBVObject@@@Z:
// clears the current victim via the doubly indirect Object, clears +0x488,
// then frees the +0x20 slot via slot0 deleteInstance(0) fed to operator delete.
// Layout retail-proven: +0x18 -> +0x14 -> Object, AI at +0x258, flag at +0x488,
// owned deletable at +0x20 with deleteInstance at slot 0 (NetCommandMsg detach
// precedent). Single int arg is unused (ret 4).

class AIUpdateInterface;
class Object;

#include "../../Include/GameLogic/Module/AIUpdate.h"

class Object
{
public:
	char m_pad0[0x258];
	AIUpdateInterface *m_ai;
	char m_pad1[0x488 - 0x25C];
	int m_flag488;

public:
	AIUpdateInterface *getAI() const { return m_ai; }
};

struct Mid
{
	char m_pad[0x14];
	Object *m_obj;
};

class Deletable
{
public:
	virtual void *deleteInstance(int flags);
};

class Rva00341557
{
	char m_pad00[0x18];
	Mid *m_mid;
	char m_pad1C[4];
	Deletable *m_owned;

public:
	void onExit(int unused);
};

// ?onExit@Rva00341557@@QAEXH@Z
void Rva00341557::onExit(int unused)
{
	Object *obj = m_mid->m_obj;
	AIUpdateInterface *ai = obj->getAI();
	if (ai)
		ai->setCurrentVictim(0);
	m_mid->m_obj->m_flag488 = 0;
	if (m_owned)
	{
		::operator delete(m_owned->deleteInstance(0));
		m_owned = 0;
	}
}
