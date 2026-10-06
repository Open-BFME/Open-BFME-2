// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva002D9622Get@@YAPBVAsciiString@@H@Z @ 0x002D9622 100B
// Evidence: honest free-function name; switch on int arg cases 0..4 plus default empty; TheAudio at 0x009FE6E8 slot 0x134 plus byte adds 4/8/12/16; default AsciiString::TheEmptyString; callers at 0x002DA723 0x002DA99F 0x002DAA63; neighbours Rva002D9608AudioCheck and stringtailrecord144 dtor.
#include "ascii_string.h"

struct AudioData
{
	char m_pad[4];
	AsciiString m_4;
	AsciiString m_8;
	AsciiString m_C;
	AsciiString m_10;
};

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void _pad27() = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual void _pad52() = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual AudioData *slot134() = 0;
};

extern AudioManager *TheAudio;

const AsciiString *Rva002D9622Get(int v)
{
	switch (v) {
	case 0:
		return &TheAudio->slot134()->m_8;
	case 1:
		return &TheAudio->slot134()->m_C;
	case 2:
	case 4:
		return &TheAudio->slot134()->m_4;
	case 3:
		return &TheAudio->slot134()->m_10;
	case 5:
		return &AsciiString::TheEmptyString;
	default:
		return &AsciiString::TheEmptyString;
	}
}
