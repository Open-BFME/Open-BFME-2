// cl: /O1
// ?teleportTo@Object@@QAEXPBUCoord3D@@_N@Z @0x0029660C 148B.
// Object thiscall (Coord3D*, bool, ret 8): re-emit position via Thing
// setPosition (rowed 0x0030AA80), notify twice through rowed 0x0023D3AF on
// the GameLogic +0x40 pointer, poke the +0x84 helper (pinned 0x002747F9),
// refresh partitions (rowed 0x0028C11A), run the +0x250 virtual pair
// (+0x7C then +0x1B8 with the position), and unless the bool flag is set,
// idle the +0x258 AI (+0x20) via rowed aiIdle 0x001E8A38 plus teardown via
// rowed destroyPath 0x00262A8A.
//
// Target evidence (game.dat, read-only, capstone): frameless thiscall
// (esi=this), TheGameLogic at 0x00DFE78C (+0x40 arg), Object layout:
// helper +0x84, vslot object +0x250, AI +0x258 (command member +0x20).
// Identity unproven: honest address-derived names; neighbour range bodies
// reuse this TU's views.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	Rva0029660C_SOURCE_2 = 2
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Rva002747F9
{
public:
	void rva002747F9(int mode);
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class AIUpdateInterface
{
public:
	void destroyPath();

public:
	unsigned char m_pad00[0x20];
	AICommandInterface m_ai20;
};

template <int N>
class Rva0029660CSlots : public Rva0029660CSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <>
class Rva0029660CSlots<0>
{
};

class Rva0029660CV250 : public Rva0029660CSlots<31>
{
public:
	virtual void *v7C() = 0;
};

class Rva0029660CV1B8 : public Rva0029660CSlots<110>
{
public:
	virtual void v1B8(const Coord3D *pos) = 0;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	void *m_40;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	void rva0023D3AF(void *p);
	void teleportTo(const Coord3D *pos, bool flag);
	void updateShroudNow();

private:
	unsigned char m_pad00[0x84];
	Rva002747F9 *m_84;
	unsigned char m_pad88[0x250 - 0x88];
	Rva0029660CV250 *m_250;
	void *m_254;
	AIUpdateInterface *m_ai258;
};

void Object::teleportTo(const Coord3D *pos, bool flag)
{
	((Thing *)this)->setPosition(pos);
	rva0023D3AF(TheGameLogic->m_40);
	rva0023D3AF(TheGameLogic->m_40);
	Rva002747F9 *helper = m_84;
	if (helper != 0)
		helper->rva002747F9(1);
	((Thing *)this)->setPosition(pos);
	updateShroudNow();
	Rva0029660CV250 *v = m_250;
	if (v != 0)
	{
		void *o = v->v7C();
		if (o != 0)
			((Rva0029660CV1B8 *)o)->v1B8(pos);
	}
	if (flag)
		return;
	AIUpdateInterface *ai = m_ai258;
	if (ai != 0)
	{
		ai->m_ai20.aiIdle(Rva0029660C_SOURCE_2);
		ai->destroyPath();
	}
}
