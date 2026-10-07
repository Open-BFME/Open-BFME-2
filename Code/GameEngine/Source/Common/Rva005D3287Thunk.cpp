// cl: /O1 /arch:SSE /G7 /MD
// ?rva005D3287@Rva005D3287@@QAEX_N@Z @0x005D3287 7B
// Evidence: leaf tail-jmp to Impl SetVisibility 0x005D321D; caller 0x00578664; prev 0x005D321D next 0x005D328E.
namespace StrategicHUD
{
class RegionStatsTrayMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionStatsTrayMovieClip::Impl
{
public:
	void SetVisibility(bool flag);
};

class Rva005D3287
{
public:
	void rva005D3287(bool flag);
private:
	StrategicHUD::RegionStatsTrayMovieClip::Impl *m_impl00;
};

void Rva005D3287::rva005D3287(bool flag)
{
	return m_impl00->SetVisibility(flag);
}
