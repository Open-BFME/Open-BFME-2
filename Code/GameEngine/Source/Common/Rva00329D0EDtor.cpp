// cl: /DNDEBUG /MD
// ??1Rva00329D0E@@QAE@XZ @0x00329D0E 8B
// Container dtor forwarding to Dict member at +0xC.
// Evidence: retail add ecx 0xC jmp to rowed ?releaseData@Dict@@AAEXXZ
// @0x0031339C; caller @0x00329D9B is ??_G-shaped deleting dtor
// (calls here then operator delete and ret 4).
#include "../../Include/Common/Dict.h"

class Rva00329D0E
{
	char m_pad[0xC];
	Dict m_dict;

public:
	~Rva00329D0E();
};

Rva00329D0E::~Rva00329D0E()
{
}
