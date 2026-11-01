// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?Show@Impl@PalantirCommandInterface@@QAEXXZ @0x00528C0C 36B evidence: same firer shape as 0x00528BDD via rva00222BCD ShowCommandInterface plus global g_bfmeAptWindowManager caller 0x00529E58
#include "../../Include/Common/Rva00222A8BTarget.h"
class BfmeAptWindowManager : public Rva00222A8BTarget
{
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class PalantirCommandInterface
{
public:
	class Impl;
};
class PalantirCommandInterface::Impl
{
public:
	void Show();
private:
	char m_pad00[4];
	void *m_04;
	char m_pad08[0x25];
	bool m_2D;
};
void PalantirCommandInterface::Impl::Show()
{
	g_bfmeAptWindowManager->rva00222BCD(m_04, "ShowCommandInterface", 0, 0, 0, 0, 0, 0);
	m_2D = true;
}
