// cl: /MD /EHsc
// ?rva004A7797@MissileUpdate@@QAEXXZ @0x004A7797 33B
// MissileUpdate frame-threshold to state 2: cur-frame minus +0x8c vs Thing+0xc8,
// else rowed Rva004A7530Set(2). Evidence: unlock packet (all callees rowed),
// prev ??1MissileUpdate dtor + next MissileUpdateModuleData ctor share /O1,
// callee MissileUpdate::Rva004A7530Set in MissileUpdateCtor.cpp, caller 0x004A7B48,
// TheGameLogic +0x40 frame via getFrame, Thing+0xc8 threshold, jb unsigned compare.
class Thing
{
public:
	unsigned char m_pad[0xC8];
	unsigned int m_c8; // +0xC8
};

class BezierProjectileBehavior
{
protected:
	const void *m_vtable0; // +0
	Thing *m_thing; // +4
	const void *m_data; // +8
	unsigned char m_pad0C[0x88 - 0x0C];
};

class GameLogic
{
public:
	unsigned int getFrame() { return m_frame; }

private:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class MissileUpdate : public BezierProjectileBehavior
{
public:
	void rva004A7797();
	void Rva004A7530Set(int val);

private:
	int m_88; // +0x88
	unsigned int m_frame; // +0x8C
};

void MissileUpdate::rva004A7797()
{
	unsigned int cur = TheGameLogic->getFrame();
	unsigned int diff = cur - m_frame;
	if (diff < m_thing->m_c8)
		return;
	Rva004A7530Set(2);
}
