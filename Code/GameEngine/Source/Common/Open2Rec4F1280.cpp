// PlayerInfo::PlayerInfo(), retail 0x003822C4 (118 bytes): the default
// constructor of the 0x34-byte GameSpy PlayerInfo (three AsciiStrings and ten
// ints). Donor: BFME 1 0x004F1280 (WOLGameSetupMenu, beside the PlayerInfo
// copy constructor at BFME 1 0x004F1120 = BFME 2 0x001EF485).
//
// Identity from target evidence: PlayerInfoMap::operator[] (0x00385F29)
// default-constructs its mapped value here and destroys it through the
// pinned PlayerInfo destructor (0x001EF50E). The GameSpyInfo virtual at 0x00382D39
// and AptOnlineQuickMatch::OnMatched (0x005BAF35) build a local here, copy it
// through 0x001EF485 into the by-value PlayerInfo argument of vtable slot 0x4C
// (GameSpyInfo::updatePlayerInfo 0x00386EF8) and destroy it through
// 0x001EF50E. Member labels stay offset-named; only the class is identified.

// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/asciistring_thin /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include "ascii_string.h"

class PlayerInfo
{
public:
	PlayerInfo();

	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	int m_at24;
	int m_at28;
	int m_at2c;
	int m_at30;
};

// @??0PlayerInfo@@QAE@XZ 0x004F1280
PlayerInfo::PlayerInfo()
	: m_at00(), m_at04(), m_at08()
{
	m_at00 = m_at04 = m_at08 = AsciiString::TheEmptyString;
	m_at28 = m_at0c = m_at10 = m_at1c = m_at2c = m_at30 = m_at14 = m_at18 = 0;
	m_at20 = m_at24 = -1;
}
