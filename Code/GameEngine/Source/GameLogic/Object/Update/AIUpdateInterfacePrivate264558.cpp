// cl: /O1 /DNDEBUG /MD
#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

// ?rva00264558@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z
// 0x00264558 97B: AIUpdateInterface order with state 0x3F. Guards +0x3BD and
// rva002907A1, runs Rva001E4147 copy from object+0x38 via +0x1F0, then clear,
// setGoalObject arg1, blocked+0x3B8 reset, source +0x48 and setState 0x3F.
// Vtable slot 18 of Siege/Deploy/Supply/Transport/Wander/HordeWorker AIUpdates.
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Rva001E4147Twelve { int a; int b; int c; };

class Rva001E4147
{
public:
	void rva001E4147(Rva001E4147Twelve *src);
};

class Object
{
public:
	Bool rva002907A1();
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(int state);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;

protected:
	virtual void rva00264558(Object *obj, CommandSourceType commandSource);

public:
	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[0x16C - 0x4C];
	int m_blockedFrames;
	unsigned char m_unmodelled_170[0x1F0 - 0x170];
	Rva001E4147 *m_1F0;
	unsigned char m_unmodelled_1F4[0x3B8 - 0x1F4];
	unsigned char m_bfmeByte3B8;
	unsigned char m_unmodelled_3B9[0x3BD - 0x3B9];
	unsigned char m_byte3BD;
};

void AIUpdateInterface::rva00264558(Object *obj, CommandSourceType commandSource)
{
	if (m_byte3BD != 0)
		return;
	if (!m_object->rva002907A1())
		return;
	Rva001E4147 *helper = m_1F0;
	if (helper == 0)
		goto doState;
	helper->rva001E4147((Rva001E4147Twelve *)m_object);
doState:
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((int)0x3F);
}
