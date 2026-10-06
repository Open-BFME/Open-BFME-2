// cl: /DNDEBUG /MD

// ?rva0039D8D3@Team@@QAEXI@Z @0x0039D8D3 (40B).
// Team::rva0039D8D3(unsigned ms): deadline at +0x124 is (ms/1000)*fps plus
// TheGameLogic frame. Caller at 0x3A2EA0 passes 5000 with float at +0x120.
// Globals 0xDFE78C frame and 0xDBA4E4 fps. Neighbours share /O1.
extern int g_Va00DBA4E4;

class GameLogic
{
public:
	unsigned char m_pad[0x40];
	int m_frame;
};
extern GameLogic *TheGameLogic;

#define LogicFramesPerSecond g_Va00DBA4E4

class Team
{
public:
	void rva0039D8D3(unsigned int ms);

private:
	unsigned char m_pad[0x124];
	int m_deadline;
};

void Team::rva0039D8D3(unsigned int ms)
{
	m_deadline = (ms / 1000) * LogicFramesPerSecond + TheGameLogic->m_frame;
}
