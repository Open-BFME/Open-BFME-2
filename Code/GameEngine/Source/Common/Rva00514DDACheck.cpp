// cl: /MD
//
// ?rva00514DDA@Rva00514DDA@@QAEXH@Z @0x00514DDA, 70B.
// Gate on this+0x288==8 and arg==3, then TheGameClient branch on this+0x282,
// TheMouse engine visibility false, clear 0x288.
// Evidence: __thiscall ret 4 void(int); callees rowed rva0023C322 rva00238FC0
// and Mouse::_bfme_setEngineVisibility; globals TheGameClient TheMouse in use;
// and [m],0 and push esi shape indicate /O1 like next sibling.

class ClientFrameSubsystem
{
public:
	char _pad[4];
};

class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva0023C322
{
public:
	void rva0023C322();
};

class Rva00238E1B
{
public:
	void rva00238FC0();
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

extern Mouse *TheMouse;

class Rva00514DDA
{
public:
	char _pad0[0x282];
	unsigned char m_0282;
	char _pad1[0x288 - 0x282 - 1];
	int m_0288;
	void rva00514DDA(int arg);
};

void Rva00514DDA::rva00514DDA(int arg)
{
	if (m_0288 != 8)
		return;
	if (arg != 3)
		return;
	if (m_0282 != 0)
		((Rva0023C322 *)((ClientFrameSubsystem *)TheGameClient))->rva0023C322();
	else
		((Rva00238E1B *)((ClientFrameSubsystem *)TheGameClient))->rva00238FC0();
	TheMouse->_bfme_setEngineVisibility(false);
	m_0288 = 0;
}
