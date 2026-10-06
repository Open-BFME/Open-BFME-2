// cl: /MD
// ?rva005EE250@Rva005EE250@@QAEXH@Z @0x005EE250 8B
// Ticker delegate: forwards to rowed SetPlayerCount through the
// pointer at +4. Evidence: mov ecx,[ecx+4] plus tail-jmp to rowed 0x005EE11E,
// caller 0x005D13F6.
namespace StrategicHUD {
class RegionAwardMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionAwardMovieClip::Impl
{
public:
	void SetPlayerCount(int count);
};

class Rva005EE250
{
public:
	void rva005EE250(int count);
private:
	char m_pad[4];
	StrategicHUD::RegionAwardMovieClip::Impl *m_04;	// +4
};

void Rva005EE250::rva005EE250(int count)
{
	return m_04->SetPlayerCount(count);
}
