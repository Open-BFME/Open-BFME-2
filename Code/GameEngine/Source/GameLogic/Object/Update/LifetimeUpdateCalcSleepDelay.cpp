// cl: /GX /DNDEBUG /MD /DWIN32 /D_WINDOWS
//
// ?calcSleepDelay@LifetimeUpdate@@AAEIII@Z, retail 0x003A49F0 (55 bytes). Dedicated
// TU (DeletionUpdate_calcSleepDelay precedent): retail pins __LINE__ 118
// (push 0x76) for the random call, met by padding the call onto its own
// line 118, and reads the GameLogic frame at +0x40 (four past the reference
// header's +0x3C), so this TU carries a TU-local GameLogic view. Lifetime
// adds m_birthFrame at +0x24 beside m_dieFrame at +0x20 (cf. rowed xfer
// ?xfer@Rva003A49D1@@MAEXPAVXfer@@@Z at 0x003A4AFA which xfers +0x20/+0x24
// then bool +0x28). The "LifetimeUpdate.cpp" file literal below is the BFME2
// patch103 path (DeletionUpdate precedent). The random helper resolves via
// its matched row 0x00233FF4.
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

class LifetimeUpdate
{
private:
	UnsignedInt calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames);

private:
	unsigned char m_pad[0x20];
	UnsignedInt m_dieFrame; // +0x20
	UnsignedInt m_birthFrame; // +0x24
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
// (padding to land the random call on line 118)
UnsignedInt LifetimeUpdate::calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames)
{
	UnsignedInt delay = GetGameLogicRandomValue(minFrames, maxFrames, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\LifetimeUpdate.cpp", __LINE__);
	if (delay < 1) delay = 1;
	UnsignedInt frame = TheGameLogic->getFrame();
	m_birthFrame = frame;
	m_dieFrame = frame + delay;
	return delay;
}
