// cl: /MD
// ?rva002B2AFD@Rva002B2AFD@@QAEHXZ, retail 0x002B2AFD, 48 bytes.
// Selector: if selection locked or TheGameLogic check fails, return
// TheWritableGlobalData field +0xe84, else TheGameLogic field +0x118.
// Evidence: call isSelectionLocked; jne alt; TheGameLogic->rva002034E9;
// jne alt; mov eax,[TheGameLogic]; mov eax,[eax+0x118]; ret; alt:
// mov eax,[TheWritableGlobalData]; mov eax,[eax+0xe84]; ret.
// Caller at 0x0038030D takes min with another int. Honest address name.
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};
class Rva002034E9Host
{
public:
	bool rva002034E9();
};
class GameLogic
{
public:
	char m_pad[0x118];
	int m_118;
};
extern GameLogic *TheGameLogic;
class GlobalData
{
public:
	char m_pad[0xe84];
	int m_e84;
};
extern GlobalData *TheWritableGlobalData;
class Rva002B2AFD
{
public:
	int rva002B2AFD();
};
int Rva002B2AFD::rva002B2AFD()
{
	if (((BfmeSelectionState *)this)->isSelectionLocked() || ((Rva002034E9Host *)TheGameLogic)->rva002034E9())
		return TheWritableGlobalData->m_e84;
	return TheGameLogic->m_118;
}
