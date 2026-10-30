// cl: /DNDEBUG /MD
//
// PickupStuffUpdate::updateInactive, retail 0x004920B5 (118 bytes), pinned by
// address from its caller PickupStuffUpdate::update (0x0049212B), which runs
// it on the primary `this` while the +0x20 flag is clear. Once the logic
// frame passes the last scan frame (+0x24) plus BfmeLogicFramesPerSecond times the
// module data's float at +0x14, and the Object's +0x258 holder has a zero
// +0x34, it scans for the nearest candidate (0x00491FA6) and, when one is
// found, hands it to moveToStuff (0x00492089) and sets +0x20; either way it
// restamps the scan frame. Retail compares with fcompi, which MSVC 7.1 emits only under
// /arch:SSE.
class Object;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;

struct PickupStuffAI
{
	unsigned char m_pad00[0x34];
	int m_34;
};
class Object
{
public:
	unsigned char m_pad000[0x258];
	PickupStuffAI *m_ai;		// +0x258
};
struct PickupStuffUpdateModuleData
{
	unsigned char m_pad00[0x14];
	float m_scanIntervalSeconds;	// +0x14
};
class PickupStuffUpdate
{
public:
	void moveToStuff(void *obj);
	void updateInactive();
	Object *rva00491FA6();	// the nearest-candidate scan
private:
	const PickupStuffUpdateModuleData *getPickupStuffUpdateModuleData() const { return m_moduleData; }
	void *m_vptr;
	const PickupStuffUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
	bool m_20;			// +0x20
	unsigned int m_lastScanFrame;	// +0x24
};
void PickupStuffUpdate::updateInactive()
{
	if ((float)TheGameLogic->getFrame() > (float)BfmeLogicFramesPerSecond * getPickupStuffUpdateModuleData()->m_scanIntervalSeconds + (float)m_lastScanFrame) {
		if (m_object->m_ai->m_34 == 0) {
			Object *found = rva00491FA6();
			if (found) {
				moveToStuff(found);
				m_20 = true;
			}
		}
		m_lastScanFrame = TheGameLogic->getFrame();
	}
}
