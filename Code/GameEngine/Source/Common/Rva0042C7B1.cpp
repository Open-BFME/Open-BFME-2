// cl: /EHsc /MD
// ?rva0042C7B1@Rva0042C7B1@@QAEHPBURva0042C083Param@@H@Z @0x0042C7B1 47B via mouse-gated setter forward
// Evidence: TheMouse at 0x009FDCA0 field +0x4FA4 slot 0x4C plus call 0x0042C083 via +0x8; caller 0x0042C8C6; chain from 0x0042C083
#include "../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;

#include "../../Include/Common/Rva0042C083Param.h"
#include "../../Include/Common/Rva0042C083.h"

class Rva0042C7B1
{
public:
	int rva0042C7B1(const Rva0042C083Param *p, int unused);
private:
	char m_pad00[8];
	Rva0042C083 *m_08;
};

int Rva0042C7B1::rva0042C7B1(const Rva0042C083Param *p, int unused)
{
	(void)unused;
	if (TheMouse && TheMouse->m_currentCursor != Mouse::ARROW)
		TheMouse->setCursor(Mouse::ARROW);
	m_08->rva0042C083(p);
	return 0;
}
