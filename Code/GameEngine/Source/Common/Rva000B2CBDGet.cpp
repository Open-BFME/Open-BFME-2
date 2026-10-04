// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?Rva000B2CBDGet@@YAHXZ @0x000B2CBD 40B GameLogic/GameState flag check.
// Evidence: TheGameLogic+0x70 then TheGameState+0xE18 then 1 else 0; callers 0x000BBED5/0x000BE26F/0x000BE798/0x000C389E.
class GameLogic
{
public:
	char m_pad00[0x70];
	unsigned char m_70;
};
extern GameLogic *TheGameLogic;
class GameState
{
public:
	char m_pad00[0xE18];
	unsigned char m_E18;
};
extern GameState *TheGameState;
int __cdecl Rva000B2CBDGet()
{
	GameLogic *logic = TheGameLogic;
	if (logic != 0 && logic->m_70 != 0)
		return 1;
	GameState *state = TheGameState;
	if (state == 0 || state->m_E18 == 0)
		return 0;
	return 1;
}
