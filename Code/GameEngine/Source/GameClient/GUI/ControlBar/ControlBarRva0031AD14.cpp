// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// ?rva0031AD14@ControlBar@@QAEXHHHHH@Z @ 0x0031AD14 52B: ControlBar 5-dword
// store to +0x218..+0x228. Evidence: gap between 0x0031ACF5 and 0x0031AE13
// plus callers 0x0031E94C and 0x0031ED2C plus EBP frame with ret 0x14.
typedef bool Bool;
#include "subsystem_interface.h"
#include "ControlBarMemberTypes.h"
class ControlBar : public SubsystemInterface
{
public:
	void rva0031AD14(int a, int b, int c, int d, int e);

private:
	char m_pad0C[0x218 - 0x0C];
	int m_commandButtonBorderBuildColor;
	int m_commandButtonBorderActionColor;
	int m_commandButtonBorderUpgradeColor;
	int m_commandButtonBorderSystemColor;
	int m_commandButtonBorderBfme5Color;
};

void ControlBar::rva0031AD14(int a, int b, int c, int d, int e)
{
	m_commandButtonBorderBuildColor = a;
	m_commandButtonBorderActionColor = b;
	m_commandButtonBorderUpgradeColor = c;
	m_commandButtonBorderSystemColor = d;
	m_commandButtonBorderBfme5Color = e;
}
