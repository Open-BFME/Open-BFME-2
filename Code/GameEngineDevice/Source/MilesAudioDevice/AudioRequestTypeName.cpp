// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?getNameOfRequestType@@YA?AVAsciiString@@H@Z, retail 0x000A870E, 206 bytes.
// AudioRequest type to AsciiString: 8 dense cases (AR_Play 0, AR_StopHandle 1,
// AR_StopMusic 2, AR_PushMusic 3, AR_PopMusic 4, AR_ActivateMusicSystem 5,
// AR_DeactivateMusicSystem 6, AR_ClearOutMusicSystem 7) via jump table at
// 0x004A87BC, default formats "<Unknown %d>" through AsciiString::format at
// 0x00038150 then copy-constructs the hidden return via StringBase copy at
// 0x000365F0 and tears the temp down through releaseBuffer at 0x00036410.
// Strings at 0x007C9300..0x007C9398. No callers. Honest address name; the
// AR_* spellings are retail rdata, the RequestType enum itself is unproven.

class AsciiString;

#include "ascii_string.h"


AsciiString getNameOfRequestType(int type)
{
	switch (type)
	{
	case 0:
		return AsciiString("AR_Play");
	case 1:
		return AsciiString("AR_StopHandle");
	case 2:
		return AsciiString("AR_StopMusic");
	case 3:
		return AsciiString("AR_PushMusic");
	case 4:
		return AsciiString("AR_PopMusic");
	case 5:
		return AsciiString("AR_ActivateMusicSystem");
	case 6:
		return AsciiString("AR_DeactivateMusicSystem");
	case 7:
		return AsciiString("AR_ClearOutMusicSystem");
	default:
		{
			AsciiString temp;
			temp.format("<Unknown %d>", type);
			return temp;
		}
	}
}

class Rva0073F4F3
{
public:
	~Rva0073F4F3();
};

class Rva000A87DC
{
public:
	void rva000A87DC();
};

void Rva000A87DC::rva000A87DC()
{
	((Rva0073F4F3 *)this)->~Rva0073F4F3();
}

