// cl: /MD
// TheGameLogic is the global at 0x00DFE78C; the banked attempt read it
// through a literal-address macro, which changed the load order.
// ?rva0049B303@Rva0049B303@@QAEHXZ, retail 0x0049B303, 13 bytes.
// Frame delta: m_20 minus TheGameLogic frame at +0x40 via global 0x00DFE78C.
// Evidence: caller 0x0053E310; prev ModuleNameGetters next OCLUpdatePoolKey; same TheGameLogic shape as ObjectRva002900E0.
class GameLogic
{
public:
	char m_pad[0x40];
	int m_frame;
};

extern GameLogic *TheGameLogic;
class Rva0049B303
{
public:
	int rva0049B303();
private:
	char m_pad[0x20];
	int m_20;
};

int Rva0049B303::rva0049B303()
{
	int t = m_20;
	GameLogic *g = TheGameLogic;
	return t - g->m_frame;
}
