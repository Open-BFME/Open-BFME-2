// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// VSlots 7/8/10/11/12 of vtable 0x0086FD90 (class of ??0HordeMeleeFormation@@QAE@PAX0@Z).
// Retail 0x00584F03 52B slot7 returns (vec[idx].m_00 == 1).
// Retail 0x00584F37 52B slot8 returns (vec[idx].m_00 == 2).
// Retail 0x00584FBF 44B slot10 sets vec[idx].m_00 = 2.
// Retail 0x00584FEB 44B slot11 sets vec[idx].m_00 = 3.
// Retail 0x0058619F 101B slot12 sets vec[idx].m_1c = 1 then via Held188 at
// m_held+0x188 checks Elem28[idx].m_18 < 0, reads ObjectArg+0x258 AI,
// returns if null or virtual slot110 true, else aiIdle(CMD_FROM_AI).
// All bounds-checked (idx<0 or idx>=size returns). Stride 0x54 proves
// 84-byte elements; BfmeV84 is the size-only stand-in (int at +0, byte at +0x1c).
// Callers: none. Vtable slot0 deleting dtor 0x00586E35.
#include <vector>

struct BfmeV84 { int m_00; char _pad1c[0x1c - 4]; unsigned char m_1c; char _pad2[84 - 0x1c - 1]; };

struct Elem28 { char _pad[0x18]; int m_18; };
struct Held188 { char _pad[0x188]; Elem28 *m_arr; };

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType src);
};

template <int N> class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <> class BfmeVirtualSlots<0> { };

class __declspec(novtable) AIUpdateInterface : public BfmeVirtualSlots<110>
{
public:
	virtual bool slot110() = 0;
	char _pad[0x1c];
	AICommandInterface m_commands; // +0x20
};

struct ObjectArg
{
	char _pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class HordeMeleeFormation : public Rva005D6FCC
{
public:
	virtual ~HordeMeleeFormation();
	virtual bool isUnitMoving(int idx);
	virtual bool isUnitRotating(int idx);
	virtual void setUnitRotating(int idx);
	virtual void setUnitArrived(int idx);
	virtual void setUnitNeedsNewAttackPos(void *arg, int idx);
private:
	_STL::vector<BfmeV84> m_vec; // +8
	bool m_flag; // +0x14
	void *m_other; // +0x18
};

bool HordeMeleeFormation::isUnitMoving(int idx)
{
	if (idx < 0 || (unsigned)idx >= m_vec.size())
		return false;
	return m_vec[idx].m_00 == 1;
}

bool HordeMeleeFormation::isUnitRotating(int idx)
{
	if (idx < 0 || (unsigned)idx >= m_vec.size())
		return false;
	return m_vec[idx].m_00 == 2;
}

void HordeMeleeFormation::setUnitRotating(int idx)
{
	if (idx < 0)
		return;
	if ((unsigned)idx >= m_vec.size())
		return;
	m_vec[idx].m_00 = 2;
}

void HordeMeleeFormation::setUnitArrived(int idx)
{
	if (idx < 0)
		return;
	if ((unsigned)idx >= m_vec.size())
		return;
	m_vec[idx].m_00 = 3;
}

void HordeMeleeFormation::setUnitNeedsNewAttackPos(void *arg, int idx)
{
	if (idx < 0)
		return;
	if ((unsigned)idx >= m_vec.size())
		return;
	m_vec[idx].m_1c = 1;
	Elem28 *arr = ((Held188 *)m_held)->m_arr;
	if (arr[idx].m_18 >= 0)
		return;
	AIUpdateInterface *ai = ((ObjectArg *)arg)->m_ai;
	if (!ai)
		return;
	if (ai->slot110())
		return;
	ai->m_commands.aiIdle(CMD_FROM_AI);
}
