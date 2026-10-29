// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// ?rva0031BAB1@ControlBar@@QAEXXZ @0x0031BAB1 18B ControlBar stage toggle via m_0024.
// Evidence: cmp +0x24 je then push 2 else push 0 then tail-call rowed switchControlBarStage 0x0031B99A; caller 0x004028C3; ControlBar m_0024 precedent Rva0031AE13.
typedef bool Bool;
#include "subsystem_interface.h"
enum ControlBarStages
{
	CONTROL_BAR_STAGE_DEFAULT = 0,
	CONTROL_BAR_STAGE_LOW = 2
};

class ControlBar : public SubsystemInterface
{
public:
	void switchControlBarStage(ControlBarStages stage);
	void rva0031BAB1();
private:
	char m_pad0C[0x24 - 0x0C];
	int m_0024;
};

void ControlBar::rva0031BAB1()
{
	if (m_0024 == 0)
		switchControlBarStage(CONTROL_BAR_STAGE_LOW);
	else
		switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
}
