// cl: /MD /Oi-
// ?rva00431978@Rva00431978@@QAEHPAUICoord2D@@@Z @0x00431978 55B: proximity check abs(dx)<5 and abs(dy)<5 via abs import thunk. Evidence: unlock lane unblocks 0x00431BDD 0x00432038; rowed abs thunk 0x00629952 pin _abs; ICoord2D at this+0xc.
#include <stdlib.h>
#include "../../../Libraries/Include/Lib/ICoord2D.h"


class Rva00431978
{
	char m_pad[0x0c];
	ICoord2D m_0C;
public:
	int rva00431978(ICoord2D *p);
};

int Rva00431978::rva00431978(ICoord2D *p)
{
	if (abs(p->x - m_0C.x) < 5 && abs(p->y - m_0C.y) < 5)
		return 1;
	return 0;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?rva00431978@Rva00431978@@QAE_NPAUICoord2D@@@Z=?rva00431978@Rva00431978@@QAEHPAUICoord2D@@@Z")
