// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?rva0023CAD9@GameLogic@@QAEHXZ @0x0023CAD9, 14B.
// GameLogic counter at +0x10c post-increment returning old value.
// Target evidence: contiguous gap between rowed GameLogic methods 0x0023CAD2
// (getFirstObject 7B) and 0x0023CAE7 (friend_createObject 69B); body touches
// only ecx+0x10c; GameLogicInit.cpp lays out int m_10c at +0x10c with reset to 1.

class GameLogic
{
public:
	int rva0023CAD9();

private:
	char m_pad[0x10C];
	int m_10c; // +0x10C
};

int GameLogic::rva0023CAD9()
{
	return m_10c++;
}
