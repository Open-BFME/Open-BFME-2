// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?setControlBarScheme@ControlBar@@QAEXABVAsciiString@@@Z @0x0031BA80 49B chain: ControlBar set scheme via manager
// Evidence: donor BFME1 ControlBar setControlBarScheme pattern (manager+0x44 if non-null setControlBarScheme by-value then switchControlBarStage DEFAULT); caller none; callees rowed StringBase copy 0x365F0 setControlBarScheme 0x31FC6A switchStage 0x31B99A.
#include "ascii_string.h"

enum ControlBarStages
{
	CONTROL_BAR_STAGE_DEFAULT = 0
};

class ControlBarSchemeManager
{
public:
	void setControlBarScheme(AsciiString schemeName);
};

class ControlBar
{
public:
	void setControlBarScheme(const AsciiString &schemeName);
	void switchControlBarStage(ControlBarStages stage);
private:
	char _head[0x44];
	ControlBarSchemeManager *m_controlBarSchemeManager;
};

void ControlBar::setControlBarScheme(const AsciiString &schemeName)
{
	if (m_controlBarSchemeManager)
	{
		m_controlBarSchemeManager->setControlBarScheme(schemeName);
		switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
	}
}
