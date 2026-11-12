// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// ?SetUnitCount@Rva005ED976@@QAEXHH@Z @ 0x005ED859, 8 bytes.
// Target bytes load the delegate pointer at +4 and tail-jump to the rowed unit-count method.

#include "unicode_string.h"

#include "../../../Include/GameClient/Rva005ED976.h"
namespace StrategicHUD {
}

class StrategicHUD::RegionAwardMovieClip::Impl
{
public:
	void rva005ED76A(int index, int num);
	void SelectPlayer(int newRow);
	void SetPlayerName(int index, const UnicodeString &text);
};

void Rva005ED976::SetUnitCount(int index, int value)
{
	m_impl->rva005ED76A(index, value);
}

void Rva005ED976::selectPlayer(int row)
{
	m_impl->SelectPlayer(row);
}

void Rva005ED976::setPlayerName(int index, const UnicodeString &name)
{
	m_impl->SetPlayerName(index, name);
}
