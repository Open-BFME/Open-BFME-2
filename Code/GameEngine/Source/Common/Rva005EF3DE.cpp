// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ?hideArmyName@Rva005EF3DE@@QAEXXZ retail 0x005EF3DE 8B
// Evidence: forwarder mov ecx,[ecx+4]; jmp 0x005EF283 RegionDetailsArmiesMovieClip::Impl::HideArmyName; caller 0x005E19FD.
#include "RegionDetailsArmiesClipImplView.h"

class Rva005EF3DE
{
public:
	void hideArmyName();
private:
	int m_pad00;
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr04;
};

void Rva005EF3DE::hideArmyName()
{
	return m_ptr04->HideArmyName();
}

// ?showCommandPoints@Rva005EF3E6@@QAEXHH@Z retail 0x005EF3E6 8B
// Evidence: mov ecx-[ecx+4] tail-jmp to rowed 0x005EF2BE ShowCommandPoints; adjacent forwarders 0x005EF3DE and 0x005EF3EE; caller 0x005E1A62; LINK BONUS via 0x005E19CA.
class Rva005EF3E6
{
public:
	void showCommandPoints(int currentCommandPoints, int maxCommandPoints);
private:
	int m_pad00;
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr04;
};

void Rva005EF3E6::showCommandPoints(int currentCommandPoints, int maxCommandPoints)
{
	return m_ptr04->ShowCommandPoints(currentCommandPoints, maxCommandPoints);
}

// ?hideCommandPoints@Rva005EF3EE@@QAEXXZ retail 0x005EF3EE 8B
// Evidence: mov ecx-[ecx+4] tail-jmp to rowed 0x005EF327 HideCommandPoints; adjacent forwarder 0x005EF3DE.
class Rva005EF3EE
{
public:
	void hideCommandPoints();
private:
	int m_pad00;
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr04;
};

void Rva005EF3EE::hideCommandPoints()
{
	return m_ptr04->HideCommandPoints();
}
