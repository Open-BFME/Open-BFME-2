// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEXXZ
// partial score=0.79 date=2026-09-24
// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEXXZ
// partial score=0.79 date=2026-09-24
// cl: /O1 /DNDEBUG /MD
//
// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEXXZ, retail 0x00485975,
// 14 bytes. StatusBits-eldest frame cache over TheGameLogic plus 0x40
// (sole caller 0x004B4A55). 11/14 positional, sole wall is this-homing
// plus global-load form: retail moves this to eax first (8B C1) then
// loads the global into ecx (8B 0D) while every probed shape keeps this
// in ecx and loads the global into eax (A1 moffs). Refuted: direct,
// named-global-local, int-member, self-local, explicit-this, /O2, /Os,
// defaults, /G6, volatile member, volatile global, both-locals, frame
// temp, comma-duplicate. The A1 (mov eax moffs) vs 8B0D (mov ecx moffs)
// choice follows the home register; no probed shape homes this to eax
// first. Needs a this-to-eax lever. Zero new pins needed at landing
// (TheGameLogic global is DIR32-masked). t=30 model=peppy-penguin
// score=0.79 stash=reverse/attempts/0x00485975.cpp

class GameLogic
{
public:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};

#define TheGameLogic (*(GameLogic **)0x00DFE78C)

class StatusBitsEldestFrame
{
public:
	void cacheGameLogicFrame();

private:
	unsigned int m_frame; // +0x00
};

// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEXXZ @0x00485975
void StatusBitsEldestFrame::cacheGameLogicFrame()
{
	m_frame = TheGameLogic->m_frame;
}
