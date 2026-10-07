// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// ?rva005ED859@Rva005ED976@@QAEXHH@Z @ 0x005ED859, 8 bytes.
// Target bytes load the delegate pointer at +4 and tail-jump to the rowed unit-count method.

#include "unicode_string.h"

namespace StrategicHUD {
class RegionAwardMovieClip {
public:
	class Impl;
};
}

class Rva005ED976
{
public:
	void rva005ED859(int index, int value);
	void rva005ED861(int row);
	void rva005ED986(int index, const UnicodeString &name);

private:
	char m_pad00[4];
	StrategicHUD::RegionAwardMovieClip::Impl *m_delegate;
};

class StrategicHUD::RegionAwardMovieClip::Impl
{
public:
	void rva005ED76A(int index, int num);
	void SelectPlayer(int newRow);
	void SetPlayerName(int index, const UnicodeString &text);
};

void Rva005ED976::rva005ED859(int index, int value)
{
	m_delegate->rva005ED76A(index, value);
}

void Rva005ED976::rva005ED861(int row)
{
	m_delegate->SelectPlayer(row);
}

void Rva005ED976::rva005ED986(int index, const UnicodeString &name)
{
	m_delegate->SetPlayerName(index, name);
}
