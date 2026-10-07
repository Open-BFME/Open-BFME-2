// cl: /MD /EHsc
// ?rva005EF3DE@Rva005EF3DE@@QAEXXZ retail 0x005EF3DE 8B
// Evidence: forwarder mov ecx,[ecx+4]; jmp 0x005EF283 RegionDetailsArmiesMovieClip::Impl::HideArmyName; caller 0x005E19FD.
namespace StrategicHUD
{
class RegionDetailsArmiesMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionDetailsArmiesMovieClip::Impl
{
public:
	void HideArmyName();
	void ShowCommandPoints(int a, int b);
	void HideCommandPoints();
};

class Rva005EF3DE
{
public:
	void rva005EF3DE();
private:
	int m_pad00;
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr04;
};

void Rva005EF3DE::rva005EF3DE()
{
	return m_ptr04->HideArmyName();
}

// ?rva005EF3E6@Rva005EF3E6@@QAEXHH@Z retail 0x005EF3E6 8B
// Evidence: mov ecx-[ecx+4] tail-jmp to rowed 0x005EF2BE ShowCommandPoints; adjacent forwarders 0x005EF3DE and 0x005EF3EE; caller 0x005E1A62; LINK BONUS via 0x005E19CA.
class Rva005EF3E6
{
public:
	void rva005EF3E6(int a, int b);
private:
	int m_pad00;
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr04;
};

void Rva005EF3E6::rva005EF3E6(int a, int b)
{
	return m_ptr04->ShowCommandPoints(a, b);
}

// ?rva005EF3EE@Rva005EF3EE@@QAEXXZ retail 0x005EF3EE 8B
// Evidence: mov ecx-[ecx+4] tail-jmp to rowed 0x005EF327 HideCommandPoints; adjacent forwarder 0x005EF3DE.
class Rva005EF3EE
{
public:
	void rva005EF3EE();
private:
	int m_pad00;
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr04;
};

void Rva005EF3EE::rva005EF3EE()
{
	return m_ptr04->HideCommandPoints();
}
