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
