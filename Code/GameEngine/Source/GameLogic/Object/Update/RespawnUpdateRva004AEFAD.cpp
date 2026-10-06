// cl: /DNDEBUG /MD /GX
//
// ?rva004AEFAD@RespawnUpdate@@UAEMPAH@Z, retail 0x004AEFAD, 94 bytes.
// Vslot 13 (offset 0x34) of vtable 0x008556B0 (VA 0x00C556B0), class of
// ??0RespawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z in
// Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdateCtor.cpp.
// Layout follows that TU: UpdateModule base 0x20 (secondaries at +0x0C/+0x10),
// RespawnUpdate m_20 at +0x20, state m_2C at +0x2C, start m_34 at +0x34,
// duration m_38 at +0x38, out m_3C at +0x3C. No callers. Global
// TheGameLogic at 0x00DFE78C (+0x40 frame) via GameLogicFrame::getFrame.
// Pooled floats 0.0 at 0x007BAEAC, 1.0 at 0x007BB8D8, 2^32 at 0x007C26EC.
// Retail dec-chain (sub 0 plus four decs) proves six consecutive states
// 0..5: 0/2/4/5/default return 0.0, 1 returns 1.0, 3 computes
// (frame - m_34) / m_38 with unsigned frame conversion (fild plus 2^32
// fixup) and jle zero guard. Honest address name; identity is class plus slot.

extern class GameLogic *TheGameLogic;

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

struct GameLogicFrame
{
	char m_pad00[0x40];
	unsigned int m_frame;
	unsigned int getFrame() const { return m_frame; }
};

#define TheGameLogic (*(GameLogicFrame **)&TheGameLogic)

class RespawnUpdate : public UpdateModule
{
public:
	virtual float rva004AEFAD(int *out);
private:
	float m_20;
	unsigned int m_24;
	int m_28;
	int m_2C;
	unsigned int m_30;
	int m_34;
	int m_38;
	int m_3C;
	unsigned char m_40;
	unsigned char m_41;
};

float RespawnUpdate::rva004AEFAD(int *out)
{
	if (out)
		*out = m_3C;
	switch (m_2C)
	{
	case 0:
		return 0.0f;
	case 1:
		return 1.0f;
	case 2:
		return 0.0f;
	case 3:
		break;
	case 4:
		return 0.0f;
	case 5:
		return 0.0f;
	default:
		return 0.0f;
	}
	int total = m_38;
	if (total <= 0)
		return 0.0f;
	unsigned int frame = TheGameLogic->getFrame();
	return ((float)frame - m_34) / total;
}
