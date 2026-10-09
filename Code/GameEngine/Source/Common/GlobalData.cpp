// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// GlobalData.cpp -- GlobalData members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. Zero Hour's newOverride also copies the current data
// into the new override; BFME2's retail body only constructs a fresh
// GlobalData (0x1254 bytes, ctor 0x0023631C) and links it in front of the
// chain through m_next at +0x1250 (target evidence).

#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>

typedef bool Bool;
// Canonical BFME2 subsystem layout: flag4 and name8,12B total.
#include "subsystem_interface.h"
namespace _STL { template<> vector<AsciiString>::~vector(); }
class Rva00360D26Member { unsigned handle; public: ~Rva00360D26Member(); };
class Rva002362B4 { char words[32]; public: ~Rva002362B4(); };
class Version { char words[48]; public: ~Version(); };
struct Rva004216D3Coord { float x,y,z; ~Rva004216D3Coord() {} };
struct GlobalDataLightingView { Rva004216D3Coord ambient,diffuse,position; };


extern "C" __declspec(dllimport) int __stdcall SHGetSpecialFolderPathW(void *owner, unsigned short *path, int folder, int create);
extern "C" __declspec(dllimport) int __stdcall CreateDirectoryW(const unsigned short *path, void *security);

// TheGameText's vslot 15 (0x3C) looks a label up by its text.
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0;
	virtual void slot07() = 0; virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0; virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual UnicodeString fetchLabel(const AsciiString &label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class GlobalData:public SubsystemInterface {
public:
 GlobalData();
 virtual ~GlobalData();
 virtual void init();
 virtual void reset();
 virtual void update();
 virtual bool vslot04(int);
 virtual int vslot06();
 static GlobalData *newOverride();
 AsciiString getPicturePath() const;
private: static GlobalData *m_theOriginal;
 AsciiString m_000C;
 AsciiString m_0010;
 AsciiString m_0014;
 AsciiString m_0018;
 char unknown001C[0x70];
 AsciiString m_008C;
 char unknown0090[0x8C];
 AsciiString m_011C;
 char unknown0120[0x8];
 AsciiString m_0128;
 char unknown012C[0x14];
 GlobalDataLightingView m_0140[18];
 GlobalDataLightingView m_03C8[18];
 GlobalDataLightingView m_0650[18];
 char unknown08D8[0x48];
 Rva004216D3Coord m_0920[3];
 char unknown0944[0x98];
 AsciiString m_09DC;
 AsciiString m_09E0;
 char unknown09E4[0xC];
 AsciiString m_09F0;
 AsciiString m_09F4;
 char unknown09F8[0x4];
 AsciiString m_09FC;
 AsciiString m_0A00;
 char unknown0A04[0x4];
 AsciiString m_0A08;
 AsciiString m_0A0C;
 char unknown0A10[0x4];
 AsciiString m_0A14;
 AsciiString m_0A18;
 char unknown0A1C[0x4];
 AsciiString m_0A20;
 AsciiString m_0A24;
 char unknown0A28[0x4];
 AsciiString m_0A2C;
 AsciiString m_0A30;
 char unknown0A34[0x4];
 AsciiString m_0A38;
 AsciiString m_0A3C;
 char unknown0A40[0x78];
 AsciiString m_0AB8;
 AsciiString m_0ABC;
 AsciiString m_0AC0;
 char unknown0AC4[0xC];
 void * m_weaponBonusSet;
 char unknown0AD4[0x18];
 AsciiString m_0AEC;
 char unknown0AF0[0x18];
 Version m_0B08;
 char unknown0B38[0x6C];
 AsciiString m_0BA4;
 _STL::vector<AsciiString> m_0BA8;
 char unknown0BB4[0xA0];
 _STL::vector<AsciiString> m_0C54;
 char unknown0C60[0xA4];
 AsciiString m_0D04;
 AsciiString m_0D08;
 char unknown0D0C[0x24];
 AsciiString m_0D30;
 char unknown0D34[0x4];
 AsciiString m_0D38;
 AsciiString m_0D3C;
 char unknown0D40[0xC];
 AsciiString m_0D4C;
 char unknown0D50[0x160];
 Rva00360D26Member m_0EB0;
 Rva00360D26Member m_0EB4;
 Rva00360D26Member m_0EB8;
 Rva00360D26Member m_0EBC;
 Rva00360D26Member m_0EC0;
 char unknown0EC4[0x230];
 _STL::vector<AsciiString> m_10F4;
 char unknown1100[0x14];
 Rva002362B4 m_1114;
 char unknown1134[0x4];
 Rva002362B4 m_1138;
 char unknown1158[0x10];
 Rva00360D26Member m_1168;
 char unknown116C[0xD4];
 AsciiString m_1240;
 UnicodeString m_1244;
 AsciiString m_picturePath;
 AsciiString m_124C;
 GlobalData *m_next;
};

// TheWritableGlobalData, VA 0x00DFE758.
extern GlobalData *TheWritableGlobalData;

// GlobalData::newOverride, retail 0x00237A6B.
GlobalData *GlobalData::newOverride()
{
	GlobalData *override = new GlobalData;
	override->m_next = TheWritableGlobalData;
	TheWritableGlobalData = override;
	return override;
}

// GlobalData::getPicturePath, retail 0x0023611A: the folder the create-a-hero
// screen saves pictures to. The first call makes it, the user's My Pictures
// (CSIDL_MYPICTURES, 0x27) plus the localised "APPDATA:PictureFolder", and
// records it in TheWritableGlobalData.
AsciiString GlobalData::getPicturePath() const
{
	if (((const StringBase<char> *)&m_picturePath)->isEmpty() && TheGameText)
	{
		unsigned short path[260];
		if (SHGetSpecialFolderPathW(0, path, 0x27, 1))
		{
			UnicodeString folder = TheGameText->fetch("APPDATA:PictureFolder");
			if (path[wcslen(path) - 1] != L'\\')
				wcscat(path, L"\\");
			wcscat(path, folder.str());
			wcscat(path, L"\\");
			CreateDirectoryW(path, 0);
			TheWritableGlobalData->m_picturePath = UnicodeString(path);
		}
	}
	return m_picturePath;
}

// BFME1 donor2f243e26 GlobalDataDestructor.cpp supplies the cleanup purpose;
// WBBA5220 independently names the target destructor. Native2376CC..237A6B,
// 927B, has54 member cleanup states plus the12B subsystem base. Native array
// callbacks atB3FD0 are empty; the36B lighting shape is established separately
// by setTimeOfDay and ZH GlobalData::TerrainLighting. Unknown fields retain
// offset names and padding. No explicit member-destructor calls or vptr stores.
GlobalData *GlobalData::m_theOriginal=0;
GlobalData::~GlobalData()
{
 if(m_weaponBonusSet) ::operator delete(m_weaponBonusSet);
 m_weaponBonusSet=0;
 if(m_theOriginal==this) { m_theOriginal=0;TheWritableGlobalData=0; }
}

// Primary tableBED1C4 slot9 independently identifies reset. Native52B
// uses global delete so the virtual destructor receives flag0, then memory
// is released by the existing global operator delete.
void GlobalData::reset()
{
 while(TheWritableGlobalData!=m_theOriginal) {
  GlobalData *next=TheWritableGlobalData->m_next;
  ::delete TheWritableGlobalData;
  TheWritableGlobalData=next;
 }
}
