// cl: /O1 /DNDEBUG /MD /G7 /arch:SSE
// ?onEnter@AIRampageState@@UAE?AW4StateReturnType@@XZ @0x0034BD1B 221B
// Slot 4 of vtable 0x00C11A08 (RVA 0x00811A08 class of Rva0033F80E ctor with
// Bool +0x20 and ints +0x24/+0x28). Mirrors onExit 0x0034BDF8: needs owner and
// AI validates destination via rowed 0x002EDE5B sets weapon flag 8 and AI
// bytes +0x3C5/+0x3C6 statuses 3 and 0x39 then fills +0x24/+0x28 from
// TheGameLogic+0x40 plus AI rva00264F3D and inner chain. Chain of 0x002EDE5B.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3,
	OBJECT_STATUS_BFME_39 = 0x39
};

enum WeaponSetType
{
	WEAPONSET_8 = 8
};

class Object;

template <int N> class AISlots : public AISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AISlots<0>
{
};

struct AIInner48
{
	unsigned char m_pad00[0x48];
	int m_48; // +0x48
};

class Rva00264F3D : public AISlots<142>
{
public:
	virtual void slot142(int value) = 0;
	int rva00264F3D();
	AIInner48 *m_04; // +0x04
	unsigned char m_pad008[0x3C5 - 0x08];
	bool m_flag3C5; // +0x3C5
	bool m_flag3C6; // +0x3C6
};

class Object
{
public:
	void rva0028AD32();
	void setWeaponSetFlag(WeaponSetType type);
	void setStatus(ObjectStatusTypes status, bool set);
	Rva00264F3D *getAI() { return m_ai; }
private:
	unsigned char m_pad000[0x04];
	void *m_04;
	unsigned char m_pad008[0x38 - 0x08];
public:
	Coord3D m_position; // +0x38
private:
	unsigned char m_pad044[0x258 - (0x38 + 12)];
	Rva00264F3D *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(int status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

class GameLogic
{
public:
	void deselectObject(Object *obj, unsigned int a, bool b);
	unsigned char m_pad00[0x40];
	int m_frame40; // +0x40
};

extern GameLogic *TheGameLogic;

int __cdecl Rva002EDE5B(void *obj, Coord3D *dest);

class AIRampageState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	bool m_20; // +0x20
	unsigned char m_pad21[0x24 - 0x21];
	int m_24; // +0x24
	int m_28; // +0x28
};

StateReturnType AIRampageState::onEnter()
{
	Object *owner = m_machine->getOwner();
	if (!owner)
		return STATE_FAILURE;
	Rva00264F3D *ai = owner->getAI();
	ai->slot142(8);
	Coord3D tmp;
	tmp.x = owner->m_position.x;
	tmp.y = owner->m_position.y;
	tmp.z = owner->m_position.z;
	owner->rva0028AD32();
	Rva002EDE5B(owner, &tmp);
	ai->m_flag3C6 = true;
	ai->m_flag3C5 = true;
	owner->setWeaponSetFlag(WEAPONSET_8);
	TheGameLogic->deselectObject(owner, 0xFFFFF, true);
	owner->setStatus(OBJECT_STATUS_3, true);
	owner->setStatus(OBJECT_STATUS_BFME_39, true);
	int v = ai->rva00264F3D();
	m_24 = TheGameLogic->m_frame40 + v;
	int c = ai->m_04->m_48;
	if (!c)
	{
		m_28 = -1;
		return STATE_CONTINUE;
	}
	if (v)
		m_28 = TheGameLogic->m_frame40 + c;
	else
		m_28 = TheGameLogic->m_frame40;
	return STATE_CONTINUE;
}
