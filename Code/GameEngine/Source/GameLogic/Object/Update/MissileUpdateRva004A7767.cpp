// cl: /MD /EHsc
// ?rva004A7767@MissileUpdate@@QAEXXZ @0x004A7767 48B
// MissileUpdate frame gate to state 5: cur-frame minus 3 vs +0x8c, then
// destroyObject([+0x08]) when [+0x40] nonzero, else rowed Rva004A7530Set(5).
// Evidence: unlock packet (all callees rowed), prev ??1MissileUpdate dtor and
// next rva004A7797 share /O1 /MD /EHsc, callee MissileUpdate::Rva004A7530Set
// in MissileUpdateCtor.cpp, caller 0x004A7B48, TheGameLogic +0x40 frame via
// getFrame, ja unsigned compare.
class Thing;
class Object;
class GameLogic
{
public:
	__declspec(dllimport) __forceinline unsigned int getFrame() { return m_frame; } // Native +0x40 inline frame load.
	void destroyObject(Object *obj);
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class BezierProjectileBehavior
{
protected:
	const void *m_vtable0; // +0
	Thing *m_thing; // +4
	Object *m_obj08; // +8 (passed to GameLogic::destroyObject)
	unsigned char m_pad0C[0x40 - 0x0C]; // +0x0C..+0x3F
	int m_40; // +0x40 (checked nonzero)
	unsigned char m_pad44[0x88 - 0x44]; // +0x44..+0x87
};
class MissileUpdate : public BezierProjectileBehavior
{
public:
	void Rva004A7530Set(int val);
	void rva004A7767();
private:
	int m_88; // +0x88
	unsigned int m_frame; // +0x8C
};
void MissileUpdate::rva004A7767()
{
	unsigned int cur = TheGameLogic->getFrame();
	if (m_frame > cur - 3)
		return;
	if (m_40 != 0)
		TheGameLogic->destroyObject(m_obj08);
	Rva004A7530Set(5);
}
