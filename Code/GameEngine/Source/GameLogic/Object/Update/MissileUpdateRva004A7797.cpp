// cl: /MD /EHsc
// ?rva004A7797@MissileUpdate@@QAEXXZ @0x004A7797 33B
// MissileUpdate frame-threshold to state 2: cur-frame minus +0x8c vs the
// module data's ignition delay at +0xc8,
// else rowed Rva004A7530Set(2). Evidence: unlock packet (all callees rowed),
// prev ??1MissileUpdate dtor + next MissileUpdateModuleData ctor share /O1,
// callee MissileUpdate::Rva004A7530Set in MissileUpdateCtor.cpp, caller 0x004A7B48,
// TheGameLogic +0x40 frame via getFrame, module data +0xc8 threshold, jb unsigned compare.
class Thing;
class ModuleData;
class Object;
class MissileUpdateModuleData
{
public:
	unsigned char m_pad[0xC8];
	int m_ignitionDelay; // +0xC8
};

class BezierProjectileBehavior
{
protected:
	const void *m_vtable0; // +0
	const ModuleData *m_moduleData; // +4
	Object *m_object; // +8
	unsigned char m_pad0C[0x88 - 0x0C];
};

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class MissileUpdate : public BezierProjectileBehavior
{
public:
	void rva004A7797();
	void Rva004A7530Set(int val);

private:
	const MissileUpdateModuleData *getMissileUpdateModuleData() const
	{
		return (const MissileUpdateModuleData *)m_moduleData;
	}

	int m_88; // +0x88
	unsigned int m_frame; // +0x8C
};

void MissileUpdate::rva004A7797()
{
	unsigned int cur = TheGameLogic->getFrame();
	unsigned int diff = cur - m_frame;
	if (diff < getMissileUpdateModuleData()->m_ignitionDelay)
		return;
	Rva004A7530Set(2);
}
