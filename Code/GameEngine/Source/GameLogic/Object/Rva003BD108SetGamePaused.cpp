// cl: /MD /EHsc /DNDEBUG /O1 /arch:SSE /G7
// ?Rva003BD108SetGamePaused@@YAXXZ, retail 0x003BD108 14B. Identity is address-named; packet shows TheGameLogic followed by GameLogic::SetGamePaused(true).
class GameLogic
{
public:
	void rva0023D0E3(bool paused);
};
extern GameLogic *TheGameLogic;

void Rva003BD108SetGamePaused()
{
	TheGameLogic->rva0023D0E3(true);
}
