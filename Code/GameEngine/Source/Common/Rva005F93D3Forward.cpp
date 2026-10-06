// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F93D3@Rva005F93D3@@QAEX_N@Z @0x005F93D3 8B forwarder to 0x005F927A BattlePromptMovieClip::Impl::SetRealTimeButtonEnabled.
// Evidence: jmp to rowed 0x005F927A; callers 0x005E96B3 0x005E9E02; neighbour Rva005F93CBForward.
namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::BattlePromptMovieClip::Impl
{
public:
	void SetRealTimeButtonEnabled(bool flag);
};

class Rva005F93D3
{
public:
	void rva005F93D3(bool flag);
private:
	char m_pad[4];
	StrategicHUD::BattlePromptMovieClip::Impl *m_member04;
};

void Rva005F93D3::rva005F93D3(bool flag)
{
	m_member04->SetRealTimeButtonEnabled(flag);
}
