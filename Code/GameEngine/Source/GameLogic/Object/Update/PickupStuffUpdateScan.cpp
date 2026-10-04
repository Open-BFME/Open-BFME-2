// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// PickupStuffUpdate::rva004920B5, retail 0x004920B5 (118 bytes), pinned by
// address from its caller PickupStuffUpdate::update (0x0049212B), which runs
// it on the primary `this` while the +0x20 flag is clear. Once the logic
// frame passes the last scan frame (+0x24) plus g_Va00DBA4E4 times the
// module data's float at +0x14, and the Object's +0x258 holder has a zero
// +0x34, it scans for the nearest candidate (0x00491FA6) and, when one is
// found, hands it to 0x00492089 and sets +0x20; either way it restamps the
// scan frame. Both callees are rowed under address class names, hence the
// casts. Retail compares with fcompi, which MSVC 7.1 emits only under
// /arch:SSE.
class Object;
class GameLogic
{
public:
	unsigned int getFrame() const { return m_40; }
	char m_pad000[0x40];
	unsigned int m_40;		// +0x40, the frame
};
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

struct PickupStuffAI
{
	unsigned char m_pad00[0x34];
	int m_34;
};
class Object
{
public:
	unsigned char m_pad000[0x258];
	PickupStuffAI *m_258;		// +0x258
};
struct PickupStuffUpdateModuleData
{
	unsigned char m_pad00[0x14];
	float m_scanDelay;		// +0x14
};
class Rva00491FA6
{
public:
	Object *rva00491FA6();
};
class Rva00492089
{
public:
	void rva00492089(void *obj);
};
class PickupStuffUpdate
{
public:
	void rva004920B5();
private:
	void *m_vptr;
	const PickupStuffUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
	bool m_20;			// +0x20
	unsigned int m_lastScanFrame;	// +0x24
};
void PickupStuffUpdate::rva004920B5()
{
	if ((float)TheGameLogic->getFrame() > (float)g_Va00DBA4E4 * m_moduleData->m_scanDelay + (float)m_lastScanFrame) {
		if (m_object->m_258->m_34 == 0) {
			Object *found = ((Rva00491FA6 *)this)->rva00491FA6();
			if (found) {
				((Rva00492089 *)this)->rva00492089(found);
				m_20 = true;
			}
		}
		m_lastScanFrame = TheGameLogic->getFrame();
	}
}
