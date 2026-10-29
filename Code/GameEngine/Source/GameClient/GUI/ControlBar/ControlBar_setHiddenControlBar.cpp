// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// ?setHiddenControlBar@ControlBar@@IAEXXZ @ 0x0031AE01 18B: ControlBar set +0x24 to 3
// then +0x48 window winHide(true). Evidence: gap between 0x0031AD48 and
// 0x0031AE13 sharing +0x24 layout plus caller 0x0031B99A plus rowed winHide.
typedef bool Bool;
#include "subsystem_interface.h"
class GameWindow
{
public:
	int winHide(bool hide);
};

class ControlBar : public SubsystemInterface
{
protected:
	void setHiddenControlBar();

private:
	char m_pad0C[0x24 - 0x0C];
	int m_0024;
	char m_pad28[0x48 - 0x28];
	GameWindow *m_p0048;
};

void ControlBar::setHiddenControlBar()
{
	m_0024 = 3;
	m_p0048->winHide(true);
}
