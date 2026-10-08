// cl: /DNDEBUG /MD
// ?rva002D7DD5@Radar@@UAEXXZ, retail 0x002D7DD5, 147 bytes.
//
// Radar frame tick: reads the client frame counter, force-flags the radar, then
// walks the 64 radar-event slots retiring any that are marked, stamped and
// stale. If the last processed frame is non-zero it converts the elapsed frame
// count to float, compares it against a scaled global threshold, and asks the
// radar core to refresh the terrain when the interval has passed.
//
// Retail saves ecx/ebx/ebp/esi/edi but never builds a frame pointer, and holds
// the loop bound in a callee-saved register (`pop ebx` / `dec ebx`) rather than
// a frame slot -- both reproduced here. /Oy- is NOT used: it forces a frame
// pointer and costs 33 instruction diffs on this body.
//
// The state byte must be cleared AFTER the ref test and BEFORE the branch.
// Three spellings were measured, all at 147B/55 instructions:
//   * `slot->m_ref` test with `slot->clearRef()`   -> store before the cmp
//   * a bool local for the test                     -> setne/test, +5 bytes
//   * `body->m_slot.m_ref` test with
//     `body->m_slot.clearRef()` (USED HERE)         -> retail's exact order
// A store is sunk to its next use; re-reading the slot through `body` after the
// store puts that use between the test and the branch, which is where retail
// keeps the clear. Sunk elsewhere the store would also have to precede the
// `mov ecx,esi` that sets up the clearRef call.
//
// Identity and evidence:
//   callees: TheGameClient slot +0x7C, rowed
//            ?clearRef@RadarEventRefSlot@@QAEXXZ 0x002D7CC6, TheGameLogic slot
//            +0x40, rowed terrain refresh through vtable slot +0x10.
//   globals: TheGameClient, TheGameLogic, g_Va00DBA4E4 (int threshold),
//            g_00BC7508 (float scale), g_00BC26EC (float rounding constant that
//            retail's unsigned-to-float conversion adds when the count is
//            negative), TheTerrainLogic.
//   layout:  state +0x00, stamp +0x04, frame +0x08, ref slot +0x48, event
//            stride 0x50, events at +0x2C, last frame +0x145C. Bounded by the
//            rowed ?reset@Radar@@UAEXXZ at 0x002D7DB9 and the next body after
//            RET at 0x002D7E67.
//   the 147B body is 0x002D7DD5..0x002D7E67 inclusive, 0xCC-padded after.

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

class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

private:
	char m_pad[0x40];
	unsigned int m_frame;  // +0x40
};

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
extern float g_00BC26EC;

class TerrainLogic;

// Radar's second MI base, reached from this body as (Radar *)((char *)this - 4).
// refreshTerrain is the fifth vtable entry: retail calls through slot +0x10.
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
	unsigned char m_state;  // +0x00
	char m_pad00[3];
	int m_04;               // +0x04
	unsigned int m_08;      // +0x08
	char m_pad0C[0x48 - 0x0C];
	RadarEventRefSlot m_slot;  // +0x48
};

struct RadarEvent
{
	int m_tag;  // +0x00
	RadarBody m_body;  // +0x04
};

class Radar
{
public:
	virtual void rva002D7DD5();

private:
	char m_pad04[0x0D - 0x04];
	bool m_flag;  // +0x0D
	char m_pad0E[0x28 - 0x0E];

public:
	RadarEvent m_events[64];  // +0x28, bodies at +0x2C

private:
	char m_pad1428[0x145C - 0x1428];
	unsigned int m_lastFrame;  // +0x145C
};

void Radar::rva002D7DD5()
{
	unsigned int curFrame = ((ClientFrameSubsystem *)TheGameClient)->getFrame();
	m_flag = true;
	RadarBody *body = &m_events[0].m_body;
	int left = 0x40;
	do {
		if (body->m_state == 1 && body->m_04 != 0 && curFrame > body->m_08) {
			body->m_state = 0;
			if (body->m_slot.m_ref != 0)
				body->m_slot.clearRef();
		}
		body = (RadarBody *)((char *)body + 0x50);
	} while (--left != 0);
	if (m_lastFrame == 0)
		return;
	unsigned int dt = TheGameLogic->getFrame() - m_lastFrame;
	float fdt = (float)dt;
	float limit = (float)g_Va00DBA4E4 * 3.0f;
	if (fdt > limit) {
		RadarPrimary *core = (RadarPrimary *)((char *)this - 4);
		core->refreshTerrain(TheTerrainLogic);
	}
}
