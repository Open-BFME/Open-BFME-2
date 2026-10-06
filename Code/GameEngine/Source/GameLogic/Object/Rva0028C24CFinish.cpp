// cl: /DNDEBUG /MD

// ?rva0028C24C@Object@@QAEXXZ @0x0028C24C, 24 bytes.
// Object deadline stamp: the +0x458 int is TheGameLogic's frame plus
// LogicFramesPerSecond (0x00DBA4E4) scaled by 10. Identity is the Object
// owner proven by the adjacent rowed rva0028C197/rva0028C1A9 pair in
// ObjectRva0028C197.cpp and the shared GameLogic frame layout at
// TheGameLogic (0x00DFE78C) +0x40 documented by TeamRva0039D8D3.cpp.
// The extern-global spelling (not an address macro) is what selects the
// retail register allocation: eax holds the scaled fps, edx the GameLogic
// base, then add eax,[edx+0x40].

extern int g_Va00DBA4E4;

class GameLogic
{
public:
	unsigned char m_pad[0x40];
	int m_frame;
};
extern GameLogic *TheGameLogic;

#define LogicFramesPerSecond g_Va00DBA4E4

class Object
{
public:
	void rva0028C24C();

private:
	unsigned char m_pad[0x458];
	int m_458;
};

void Object::rva0028C24C()
{
	m_458 = LogicFramesPerSecond * 10 + TheGameLogic->m_frame;
}
