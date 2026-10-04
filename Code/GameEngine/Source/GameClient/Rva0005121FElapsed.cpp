// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva0005121F@Rva0005121F@@QAEMXZ @0x0005121F 157B, a virtual whose table
// entry is at VA 0x00BC5764: seconds since the frame stamped at +0x94,
// using TheGameClient's frame (slot 0x7C, as DrawableFade.cpp has it) and
// the seconds-per-frame float at 0x00DBA4FC, clamped at zero, restamping
// +0x94. When +0x678 is set or the byte at +0x6A5 is, or there is no
// client, it only restamps (if it can) and returns one frame's worth.
// Retail tests the delta with fcompi, which MSVC 7.1 emits only under
// /arch:SSE. Class, method and global names are address-derived.
class ClientFrameSubsystem;
extern ClientFrameSubsystem *TheGameClient;
class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual unsigned int slot1F();
};
#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)
extern float g_Va00DBA4FC;

class Rva0005121F
{
public:
	float rva0005121F();
private:
	char m_pad000[0x94];
	unsigned int m_lastFrame;	// +0x94
	char m_pad098[0x678 - 0x98];
	int m_678;			// +0x678
	char m_pad67C[0x6A5 - 0x67C];
	bool m_6A5;			// +0x6A5
};

float Rva0005121F::rva0005121F()
{
	if (m_678 == 0 && !m_6A5) {
		if (TheRva00DFE77C) {
			float elapsed = ((float)TheRva00DFE77C->slot1F() - (float)m_lastFrame) * g_Va00DBA4FC;
			if (elapsed < 0.0f)
				elapsed = 0.0f;
			m_lastFrame = TheRva00DFE77C->slot1F();
			return elapsed;
		}
	} else if (TheRva00DFE77C) {
		m_lastFrame = TheRva00DFE77C->slot1F();
	}
	return g_Va00DBA4FC;
}
