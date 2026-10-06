// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva0044C277Wait@@YA_NXZ @0x0044C277 79B.
// Timed GameInfo readiness poll; packet proves the calls to the target readiness
// checks, timeout reset helper, and the TheGameInfo global.

class GameInfo
{
public:
	bool rva003FF457() const;
	bool isHeroDataReadyForSlot(unsigned short slot) const;
};

extern GameInfo *TheGameInfo;
void Rva0044C205Reset();
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

bool Rva0044C277Wait()
{
	unsigned long start = timeGetTime();
	for (;;)
	{
		if (TheGameInfo == 0 || TheGameInfo->rva003FF457())
			return true;
		Rva0044C205Reset();
		if (timeGetTime() > start + 0x4E20)
			break;
	}
	for (int slot = 0; slot < 8; ++slot)
		TheGameInfo->isHeroDataReadyForSlot(slot);
	return false;
}
