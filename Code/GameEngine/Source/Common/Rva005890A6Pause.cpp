// cl: /MD
//
// ?rva005890A6@Rva005890A6@@QAEX_N@Z retail 0x005890A6 71B pause-like helper
// operating on the +0x24 subobject (whole+0x28 available +0x2C count +0x30
// onframe +0x34 percent). Evidence: single caller at 0x00589628 in pinned
// ??0WeaponModeSpecialPowerUpdateBase@@QAE@PAVThing@@PBVModuleData@@@Z passes
// whole+0x24 with push 1; vcall slot 2 returns float stored to +0x10 matching
// 0x005892F6 getPercentReady shape; TheGameLogic frame at +0x40; no EH frame.
// Donor: SpecialPowerModule::pauseCountdown logic in
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp.
// Identity stays honest address name; class groups the subobject fields.

class GameLogic
{
	char m_pad[0x40];
public:
	unsigned int m_frame;
	unsigned int getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class Rva005890A6
{
public:
	virtual void f0();
	virtual void f1();
	virtual float getPercentReady() const;
	void rva005890A6(bool pause);
private:
	unsigned int m_availableOnFrame;
	int m_pausedCount;
	unsigned int m_pausedOnFrame;
	float m_pausedPercent;
};

void Rva005890A6::rva005890A6(bool pause)
{
	if (pause)
	{
		if (m_pausedCount == 0)
		{
			m_pausedOnFrame = TheGameLogic->getFrame();
			m_pausedPercent = getPercentReady();
		}
		++m_pausedCount;
	}
	else if (m_pausedCount > 0)
	{
		--m_pausedCount;
		if (m_pausedCount == 0)
		{
			m_availableOnFrame += (TheGameLogic->getFrame() - m_pausedOnFrame);
		}
	}
}
