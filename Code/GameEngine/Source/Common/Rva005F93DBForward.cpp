// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F93DB@Rva005F93DB@@QAEX_N@Z @0x005F93DB 8B forwarder to 0x005F92D5 BattlePromptMovieClip::Impl::SetRetreatButtonEnabled.
// Evidence: jmp to rowed 0x005F92D5; callers 0x005E96C3 0x005E9E11; neighbour Rva005F93D3Forward.
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
	void SetRetreatButtonEnabled(bool flag);
};

class Rva005F93DB
{
public:
	void rva005F93DB(bool flag);
private:
	char m_pad[4];
	StrategicHUD::BattlePromptMovieClip::Impl *m_member04;
};

void Rva005F93DB::rva005F93DB(bool flag)
{
	m_member04->SetRetreatButtonEnabled(flag);
}
