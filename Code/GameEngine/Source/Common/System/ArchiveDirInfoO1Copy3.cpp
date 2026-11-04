// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00382BF0@@QAE@ABU0@@Z, retail 0x00382BF0, 61 bytes.
// Copy ctor with AsciiString at +0 via pinned StringBase<D> copy then
// PlayerInfo at +4 via its rowed copy. Identity from unlock (makes
// 0x0038353A ready) and caller 0x00383556; the record is
// pair<const AsciiString PlayerInfo> (the PlayerInfoMap node value).
#include "ascii_string.h"


#include "../../../Include/GameNetwork/PlayerInfo.h"

struct Rva00382BF0
{
	AsciiString m_00;
	PlayerInfo m_04;

	Rva00382BF0(const Rva00382BF0 &other);
};

Rva00382BF0::Rva00382BF0(const Rva00382BF0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
{
}
