// cl: /DNDEBUG /MD /EHsc
// ?rva0028C0F2@Object@@QAEXI@Z @0x0028C0F2 40B
// Object millisecond-to-frame setter: m_448 = (v / 1000u) * rate + TheGameLogic->m_frame.
// Evidence: unsigned div by 0x3E8 plus imul with VA 0x00DBA4E4 and TheGameLogic VA 0x00DFE78C+0x40;
// sole caller 0x00295844; neighbours ObjectLeaveGroup and Object_bfmeRefreshPartitionCells are Object TUs.
extern int g_Va00DBA4E4;

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

#define BfmeLogicRate (*(unsigned int *)&g_Va00DBA4E4)

class Object
{
public:
	void rva0028C0F2(unsigned int v);

private:
	unsigned char m_pad[0x448];
	unsigned int m_448; // +0x448
};

void Object::rva0028C0F2(unsigned int v)
{
	m_448 = (v / 1000u) * BfmeLogicRate + TheGameLogic->m_frame;
}
