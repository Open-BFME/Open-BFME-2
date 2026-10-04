// cl: /O1 /DNDEBUG /MD
// ?rva0031BAB1@ControlBar@@QAEXXZ @0x0031BAB1 18B ControlBar stage toggle via m_0024.
// Evidence: cmp +0x24 je then push 2 else push 0 then tail-call rowed switchControlBarStage 0x0031B99A; caller 0x004028C3; ControlBar m_0024 precedent Rva0031AE13.
enum ControlBarStages
{
	CONTROL_BAR_STAGE_DEFAULT = 0,
	CONTROL_BAR_STAGE_LOW = 2
};

class ControlBar
{
public:
	void switchControlBarStage(ControlBarStages stage);
	void rva0031BAB1();
private:
	char m_pad00[0x24];
	int m_0024;
};

void ControlBar::rva0031BAB1()
{
	if (m_0024 == 0)
		switchControlBarStage(CONTROL_BAR_STAGE_LOW);
	else
		switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
}
