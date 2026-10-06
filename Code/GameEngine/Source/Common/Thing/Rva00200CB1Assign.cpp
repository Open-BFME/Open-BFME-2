// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ??4Rva00200CB1@@QAEAAV0@ABV0@@Z @0x00200CB1 135B.
// Operator= over StreakDrawModuleTemplate base +0x00 and DynamicAudioEventRTS
// base +0x10 then plain members. Evidence: rowed StreakDraw op= 0x001FD28E
// and DynamicAudio op= 0x00200BC0 and AsciiString op= 0x000366F0; movsd x3
// pairs at +0x20/+0x2C and bytes at +0x38/+0x50; caller 0x00200F71.
#include "ascii_string.h"

namespace FXParticleSystem
{
class StreakDrawModuleTemplate
{
public:
	StreakDrawModuleTemplate &operator=(const StreakDrawModuleTemplate &other);
private:
	char m_pad[0x10];
};
}

class DynamicAudioEventRTS
{
public:
	DynamicAudioEventRTS &operator=(const DynamicAudioEventRTS &other);
private:
	int m_00;
	AsciiString m_04;
};

struct ThreeInts
{
	int a;
	int b;
	int c;
};

class Rva00200CB1 : public FXParticleSystem::StreakDrawModuleTemplate, public DynamicAudioEventRTS
{
public:
	Rva00200CB1 &operator=(const Rva00200CB1 &other);
private:
	int m_18;
	int m_1C;
	ThreeInts m_20;
	ThreeInts m_2C;
	unsigned char m_38;
	char m_pad39[3];
	AsciiString m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	unsigned char m_50;
	char m_pad51[3];
	int m_54;
	int m_58;
};

Rva00200CB1 &Rva00200CB1::operator=(const Rva00200CB1 &other)
{
	FXParticleSystem::StreakDrawModuleTemplate::operator=(other);
	DynamicAudioEventRTS::operator=(other);
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_2C = other.m_2C;
	m_38 = other.m_38;
	m_3C = other.m_3C;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_4C = other.m_4C;
	m_50 = other.m_50;
	m_54 = other.m_54;
	m_58 = other.m_58;
	return *this;
}
