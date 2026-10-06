// cl: /GX /DNDEBUG /MD /DWIN32 /D_WINDOWS
//
// DeletionUpdate::calcSleepDelay, retail 0x00488357 (52 bytes). Dedicated
// TU so DeletionUpdate.cpp keeps its two matched bodies untouched: retail
// pins __LINE__ 55 (push 0x37) for the random call, which this file meets
// by padding the call onto its own line 55, and reads the GameLogic frame
// at +0x40 (four past the reference header's +0x3C), so this TU carries a
// TU-local GameLogic view instead of editing the shared header. The
// "DeletionUpdate.cpp" file literal below is byte-copied from retail
// (VA 0xC4B370); the random helper resolves via its matched row.
typedef unsigned int UnsignedInt;

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40 (retail; reference header says +0x3C)
};

extern GameLogic *TheGameLogic;

class DeletionUpdate
{
protected:
	UnsignedInt calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames);

private:
	unsigned char m_pad[0x20];
	UnsignedInt m_dieFrame; // +0x20
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
// (padding to land the random call on line 55)
UnsignedInt DeletionUpdate::calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames)
{
	UnsignedInt delay = GetGameLogicRandomValue(minFrames, maxFrames, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\DeletionUpdate.cpp", __LINE__);
	if (delay < 1) delay = 1;
	m_dieFrame = TheGameLogic->getFrame() + delay;
	return delay;
}
