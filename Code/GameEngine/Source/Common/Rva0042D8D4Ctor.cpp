// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0042D8D4@@QAE@XZ @ 0x0042D8D4 90B: ctor with no args (ret, returns this)
// setting m_0=-1 then m_0=TheRva00222A8BTarget virtual at +0x50 with
// "Apt\\" and "StrategicHUD.apt" plus two zero args. Caller at 0x0023A16C proves shape.
// ??1Rva0042D8D4@@QAE@XZ @ 0x0042D480 19B: when the Apt window manager
// g_bfmeAptWindowManager (the same global as TheRva00222A8BTarget, VA
// 0x00DFE4CC) is set, its pinned ?RemoveLevel@AptPlayer@@QAE_NH@Z 0x00224B7D
// is called with the handle m_0, as in Rva005EC09BDtor.cpp. Callers: the
// Rva0023A128 destructor 0x00239D7A (member at +0x14) and its ctor's unwind.
#include "ascii_string.h"
#include "../../Include/Common/Rva00222A8BTarget.h"
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class AptPlayer
{
public:
	bool RemoveLevel(int value);
};
class Rva0042D8D4
{
public:
	Rva0042D8D4();
	~Rva0042D8D4();
	int m_0;
};
Rva0042D8D4::Rva0042D8D4()
{
	m_0 = -1;
	m_0 = (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->v20(AsciiString("Apt\\"), AsciiString("StrategicHUD.apt"), 0, 0);
}
Rva0042D8D4::~Rva0042D8D4()
{
	if (g_bfmeAptWindowManager)
		((AptPlayer *)g_bfmeAptWindowManager)->RemoveLevel(m_0);
}
