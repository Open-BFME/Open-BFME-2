// ?rva002D7DD5@Radar@@UAEXXZ
// partial score=0.99 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva002D7DD5@Radar@@UAEXXZ, retail 0x002D7DD5, 147 bytes.
// Evidence: vslot lane slot 10 (offset 0x28) of vtable 0x00803604 (Radar second base);
// class proven by ??0Radar@@QAE@XZ ctor and neighbours reset/newMap; callees
// TheGameClient slot 0x7C, ?clearRef@RadarEventRefSlot@@QAEXXZ 0x002D7CC6,
// TheGameLogic+0x40 getFrame, TheTerrainLogic slot 0x10 refreshTerrain;
// globals TheGameClient TheGameLogic g_Va00DBA4E4 g_00BC7508 TheTerrainLogic.

class ClientFrameSubsystem
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual unsigned int getFrame();
};
extern ClientFrameSubsystem *TheGameClient;

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	char m_pad[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
extern float g_00BC7508;

class TerrainLogic;
class RadarPrimary
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void refreshTerrain(TerrainLogic *terrain);
};
extern TerrainLogic *TheTerrainLogic;

class RadarEventRef
{
public:
	virtual void m_spare0();
	virtual void m_deleter();
	void release();
private:
	int m_refCount;
};
class RadarEventRefSlot
{
public:
	void clearRef();
	RadarEventRef *m_ref;
};
struct RadarBody
{
	unsigned char m_state; // +0x00
	char m_pad00[3];
	int m_04; // +0x04
	unsigned int m_08; // +0x08
	char m_pad0C[0x48 - 0x0C];
	RadarEventRefSlot m_slot; // +0x48
};
struct RadarEvent
{
	int m_tag; // +0x00
	RadarBody m_body; // +0x04
};
class Radar
{
public:
	virtual void rva002D7DD5();
private:
	char m_pad04[0x0D - 0x04];
	bool m_flag; // +0x0D
	char m_pad0E[0x28 - 0x0E];
public:
	RadarEvent m_events[64]; // +0x28, bodies at +0x2C
private:
	char m_pad1428[0x145C - 0x1428];
	unsigned int m_lastFrame; // +0x145C (primary +0x1460)
};

// ?rva002D7DD5@Radar@@UAEXXZ present-unmatched
void Radar::rva002D7DD5()
{
	unsigned int curFrame = TheGameClient->getFrame();
	m_flag = true;
	RadarBody *body = &m_events[0].m_body;
	int left = 0x40;
	do {
		if (body->m_state == 1 && body->m_04 != 0 && curFrame > body->m_08) {
			RadarEventRefSlot *slot = &body->m_slot;
			body->m_state = 0;
			if (slot->m_ref != 0)
				slot->clearRef();
		}
		body = (RadarBody *)((char *)body + 0x50);
	} while (--left != 0);
	if (m_lastFrame == 0)
		return;
	unsigned int dt = TheGameLogic->getFrame() - m_lastFrame;
	float fdt = (float)dt;
	float limit = (float)g_Va00DBA4E4 * g_00BC7508;
	if (fdt > limit) {
		RadarPrimary *core = (RadarPrimary *)((char *)this - 4);
		core->refreshTerrain(TheTerrainLogic);
	}
}
