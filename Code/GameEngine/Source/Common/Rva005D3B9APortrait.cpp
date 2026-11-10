// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005D3B9A@Rva005D3B9A@@QAEXXZ @0x005D3B9A 109B
// Evidence: chain from rowed erase thunk 0x00223A94; AsciiString::format row 0x00038150;
// releaseBuffer row 0x00036410; default string VA 0x007BAC1C; table owner VA 0x009FE4CC;
// callers 0x005D3C56 0x005D3CE0 0x005D3D5B; neighbours share // cl: /O1 /MD /EHsc
template <typename T> class StringBase;

class AsciiString;

#include "ascii_string.h"


struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};

#include "../../Include/Common/Rva00223A94.h"

// The window-manager slot at VA 0xDFE4CC is the ledger's g_bfmeAptWindowManager;
// this unit calls it through its Rva00223A94 view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva005D3B9A
{
public:
	void rva005D3B9A();

	void *m_unused00;
	int m_level;
	Rva005D2FD0Inner *m_inner;
	char m_pad0C[0x14];
	int m_flag20;
};

void Rva005D3B9A::rva005D3B9A()
{
	if (g_bfmeAptWindowManager == 0)
		return;
	if (m_flag20 == 0)
		return;
	AsciiString tmp;
	const char *name = m_inner ? m_inner->m_name : "";
	tmp.format("_level%u.%s_Portrait", m_level, name);
	((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&tmp);
}
