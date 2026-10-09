// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ??4WeatherSetting@@QAEAAV0@ABV0@@Z @0x00201412 345B.
// BFME 2's WeatherSetting copy assignment (the compiler-generated one the
// override machinery calls): the same two-base shape as the streak module
// template assignment at 0x00200CB1 (the 0x10-byte base's assignment is the
// folded tiny body at 0x001FD28E, the DynamicAudio assignment 0x00200BC0 sits
// at +0x10), then the AsciiString texture at +0x18 (0x000366F0) and plain
// members to +0xB4. The members' types are only fixed as far as the copy
// shows: dwords, bytes and the 3-dword runs copied with movsd. Field offsets
// match the view SnowManager::updateIniSettings reads in Snow.cpp (+0x1C
// follows Zero Hour's snow fields in order); the ctor 0x00201618 builds the
// same object.
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

class WeatherSetting : public FXParticleSystem::StreakDrawModuleTemplate, public DynamicAudioEventRTS
{
public:
	WeatherSetting &operator=(const WeatherSetting &other);
private:
	AsciiString m_snowTexture;		// +0x18
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	unsigned char m_44;
	unsigned char m_45;
	unsigned char m_46;
	char m_pad47;
	int m_48;
	int m_4C;
	int m_50;
	unsigned char m_54;
	char m_pad55[3];
	ThreeInts m_58;
	int m_64;
	int m_68;
	unsigned char m_6C;
	char m_pad6D[3];
	int m_70;
	int m_74;
	int m_78;
	int m_7C;
	int m_80;
	int m_84;
	int m_88;
	ThreeInts m_8C;
	unsigned char m_98;
	char m_pad99[3];
	int m_9C;
	int m_A0;
	int m_A4;
	int m_A8;
	int m_AC;
	int m_B0;
};

WeatherSetting &WeatherSetting::operator=(const WeatherSetting &other)
{
	FXParticleSystem::StreakDrawModuleTemplate::operator=(other);
	DynamicAudioEventRTS::operator=(other);
	m_snowTexture = other.m_snowTexture;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3C = other.m_3C;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_45 = other.m_45;
	m_46 = other.m_46;
	m_48 = other.m_48;
	m_4C = other.m_4C;
	m_50 = other.m_50;
	m_54 = other.m_54;
	m_58 = other.m_58;
	m_64 = other.m_64;
	m_68 = other.m_68;
	m_6C = other.m_6C;
	m_70 = other.m_70;
	m_74 = other.m_74;
	m_78 = other.m_78;
	m_7C = other.m_7C;
	m_80 = other.m_80;
	m_84 = other.m_84;
	m_88 = other.m_88;
	m_8C = other.m_8C;
	m_98 = other.m_98;
	m_9C = other.m_9C;
	m_A0 = other.m_A0;
	m_A4 = other.m_A4;
	m_A8 = other.m_A8;
	m_AC = other.m_AC;
	m_B0 = other.m_B0;
	return *this;
}
