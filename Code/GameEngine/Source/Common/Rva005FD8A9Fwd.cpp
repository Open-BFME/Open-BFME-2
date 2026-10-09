// cl: /MD /EHsc
// ?rva005FD8A9@Rva005FD8A9@@QAEX_N@Z retail 0x005FD8A9 8B
// Evidence: chain via 0x005FD677 row; mov ecx [ecx+4] jmp tail; caller 0x005F5587; neighbours 0x005FD788/0x005FD8E5
namespace StrategicHUD { class ArmyUnitSwapperMovieClip { public: struct Impl; }; }
struct StrategicHUD::ArmyUnitSwapperMovieClip::Impl
{
	void SetMoveDownButtonEnabled(bool enabled);
};

struct Rva005FD8A9
{
	char m_pad0[4];
	StrategicHUD::ArmyUnitSwapperMovieClip::Impl *m_ptr4;
	void rva005FD8A9(bool enabled);
};

void Rva005FD8A9::rva005FD8A9(bool enabled)
{
	return m_ptr4->SetMoveDownButtonEnabled(enabled);
}
