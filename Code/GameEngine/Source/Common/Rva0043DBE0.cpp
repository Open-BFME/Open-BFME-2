// cl: /DNDEBUG /MD
// ?rva0043DBE0@Rva0043DBE0@@QAEXXZ @0x0043DBE0 39B
// Chain from 0x0057E59B: reads TheGameInfo+0x7C type, enable is false for 1/2
// else true, then (this+0xD0)->rva0057E59B(8, enable) via rowed 0x0057E59B.
// Evidence: packet disasm with rowed callee, TheGameInfo extern in use,
// caller 0x00443EA8, prev/next rows.
class GameInfo
{
public:
	char m_pad0[0x7C]; // +0x00..+0x7B
	int m_7C; // +0x7C type 1/2 check
};
extern GameInfo *TheGameInfo;

class Rva0057E97A
{
public:
	void rva0057E59B(int index, bool enable);
};

class Rva0043DBE0
{
public:
	void rva0043DBE0();
private:
	char m_pad0[0xD0]; // +0x00..+0xCF
	class Rva0057E97A m_rva; // +0xD0
};

void Rva0043DBE0::rva0043DBE0()
{
	m_rva.rva0057E59B(8, TheGameInfo->m_7C != 1 && TheGameInfo->m_7C != 2);
}
