// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// ?rva0031AEC9@ControlBar@@QAEXXZ @ 0x0031AEC9 54B: ControlBar blink start at
// +0x290/+0x294/+0x298 via winGetStatus bit3 then winEnable(false).
// Evidence: neighbours 0x0031AE13 and 0x0031AEFF share +0x290/+0x294/+0x298
// layout plus rowed winEnable 0x00313BEC plus pinned winGetStatus 0x0030F45F.
typedef bool Bool;
#include "subsystem_interface.h"
class GameWindow
{
public:
	unsigned int winGetStatus();
	int winEnable(bool enable);
};

#include "ControlBarMemberTypes.h"
class ControlBar : public SubsystemInterface
{
public:
	void rva0031AEC9();

private:
	char m_pad0C[0x290 - 0x0C];
	unsigned char m_0290;
	char m_pad291[0x294 - 0x291];
	int m_0294;
	GameWindow *m_0298;
};

void ControlBar::rva0031AEC9()
{
	if (m_0298 == 0)
		return;
	m_0290 = 1;
	m_0294 = 0x96;
	if ((m_0298->winGetStatus() & 8) == 0)
		return;
	m_0298->winEnable(false);
}
