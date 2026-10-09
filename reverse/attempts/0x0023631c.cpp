// ??0GlobalData@@QAE@XZ
// partial score=0.8332 date=2026-10-09
// Banked target constructor: member offsets/defaults and order from native23631C..2376C6.
// ZH GlobalData constructor provides purpose/lighting loop/override defaults; exact target constants replace donor values.
// Original field names and byte-field Boolean types remain inference. Callback aliases still require explicit complete-body proof before production.
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
class Rva00360D26Member { unsigned handle; public: Rva00360D26Member(); ~Rva00360D26Member(); };
class Rva00236285 { char words[36]; public: Rva00236285(); };
class Rva002362B4 : public Rva00236285 { public: ~Rva002362B4(); };
class Version { char words[48]; public: Version(); ~Version(); };
struct Rva004216D3Coord { float x,y,z; Rva004216D3Coord(); ~Rva004216D3Coord() {} };
struct GlobalDataLightingView { Rva004216D3Coord ambient,diffuse,position; GlobalDataLightingView(); };


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


enum TimeOfDay { TIME_OF_DAY_INVALID=-1 };
extern int g_Va00DBA4E4;
extern "C" __declspec(dllimport) unsigned int __stdcall GetDoubleClickTime();
struct Rva00235A21 { char words[528]; Rva00235A21(); };
class Rva00235A37 { public: char words[48]; Rva00235A37 &operator=(const Rva00235A37&); };
extern Version *TheVersion;
struct MultiPlayMults { char words[480]; MultiPlayMults(); };
struct RvaGDNoCleanupCoord { float x,y,z; RvaGDNoCleanupCoord(); };
struct RvaGDConst3 { float x,y,z; RvaGDConst3(float v):x(v),y(v),z(v){} };
struct RvaGDConst2 { float x,y; RvaGDConst2(float v):x(v),y(v){} };
struct RGBColor { float red,green,blue; void setFromInt(int); };
struct RvaGDColor:RGBColor { RvaGDColor(int v) {setFromInt(v);} };

class GlobalData:public SubsystemInterface {
public:
 GlobalData();
 bool setTimeOfDay(TimeOfDay);
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
 bool m_001C;
 bool m_001D;
 char unknown001E[2];
 int m_0020;
 bool m_0024;
 bool m_0025;
 bool m_0026;
 bool m_0027;
 int m_0028;
 bool m_002C;
 bool m_002D;
 char unknown002E[2];
 int m_0030;
 int m_0034;
 int m_0038;
 bool m_003C;
 bool m_003D;
 bool m_003E;
 bool m_003F;
 bool m_0040;
 bool m_0041;
 char unknown0042[2];
 int m_0044;
 bool m_0048;
 bool m_0049;
 bool m_004A;
 bool m_004B;
 bool m_004C;
 bool m_004D;
 bool m_004E;
 char unknown004F[1];
 int m_0050;
 bool m_0054;
 char unknown0055[3];
 int m_0058;
 bool m_005C;
 bool m_005D;
 bool m_005E;
 bool m_005F;
 bool m_0060;
 bool m_0061;
 bool m_0062;
 char unknown0063[1];
 int m_0064;
 bool m_0068;
 char unknown0069[3];
 float m_006C;
 float m_0070;
 float m_0074;
 float m_0078;
 float m_007C;
 int m_0080;
 bool m_0084;
 bool m_0085;
 bool m_0086;
 bool m_0087;
 bool m_0088;
 char unknown0089[3];
 AsciiString m_008C;
 int m_0090;
 float m_0094;
 float m_0098;
 float m_009C;
 float m_00A0;
 float m_00A4;
 float m_00A8;
 float m_00AC;
 float m_00B0;
 float m_00B4;
 float m_00B8;
 float m_00BC;
 float m_00C0;
 float m_00C4;
 float m_00C8;
 int m_00CC;
 bool m_00D0;
 char unknown00D1[3];
 float m_00D4;
 float m_00D8;
 RvaGDConst3 m_00DC;
 RvaGDConst3 m_00E8;
 RvaGDConst2 m_00F4;
 RvaGDConst2 m_00FC;
 float m_0104;
 float m_0108;
 int m_010C;
 int m_0110;
 int m_0114;
 int m_0118;
 AsciiString m_011C;
 float m_0120;
 float m_0124;
 AsciiString m_0128;
 float m_012C;
 float m_0130;
 int m_0134;
 int m_0138;
 bool m_013C;
 bool m_013D;
 bool m_013E;
 bool m_013F;
 GlobalDataLightingView m_0140[18];
 GlobalDataLightingView m_03C8[18];
 GlobalDataLightingView m_0650[18];
 RvaGDNoCleanupCoord m_08D8[3];
 RvaGDNoCleanupCoord m_08FC[3];
 Rva004216D3Coord m_0920[3];
 RvaGDConst3 m_0944;
 float m_0950;
 float m_0954[8];
 int m_0974;
 int m_0978;
 int m_097C;
 int m_0980;
 float m_0984;
 int m_0988;
 int m_098C;
 int m_0990;
 int m_0994;
 int m_0998;
 bool m_099C;
 bool m_099D;
 bool m_099E;
 bool m_099F;
 bool m_09A0;
 bool m_09A1;
 bool m_09A2;
 bool m_09A3;
 bool m_09A4;
 bool m_09A5;
 bool m_09A6;
 bool m_09A7;
 float m_09A8;
 bool m_09AC;
 bool m_09AD;
 bool m_09AE;
 bool m_09AF;
 bool m_09B0;
 bool m_09B1;
 char unknown09B2[2];
 int m_09B4;
 int m_09B8;
 bool m_09BC;
 bool m_09BD;
 bool m_09BE;
 bool m_09BF;
 bool m_09C0;
 bool m_09C1;
 bool m_09C2;
 bool m_09C3;
 bool m_09C4;
 bool m_09C5;
 bool m_09C6;
 bool m_09C7;
 bool m_09C8;
 char unknown09C9[3];
 int m_09CC;
 bool m_09D0;
 bool m_09D1;
 bool m_09D2;
 char unknown09D3[1];
 int m_09D4;
 bool m_09D8;
 char unknown09D9[3];
 AsciiString m_09DC;
 AsciiString m_09E0;
 bool m_09E4;
 char unknown09E5[3];
 int m_09E8;
 float m_09EC;
 AsciiString m_09F0;
 AsciiString m_09F4;
 int m_09F8;
 AsciiString m_09FC;
 AsciiString m_0A00;
 int m_0A04;
 AsciiString m_0A08;
 AsciiString m_0A0C;
 int m_0A10;
 AsciiString m_0A14;
 AsciiString m_0A18;
 int m_0A1C;
 AsciiString m_0A20;
 AsciiString m_0A24;
 int m_0A28;
 AsciiString m_0A2C;
 AsciiString m_0A30;
 int m_0A34;
 AsciiString m_0A38;
 AsciiString m_0A3C;
 int m_0A40;
 int m_0A44;
 int m_0A48;
 int m_0A4C;
 bool m_0A50;
 char unknown0A51[3];
 int m_0A54;
 unsigned short m_0A58;
 char unknown0A5A[2];
 int m_0A5C;
 int m_0A60;
 float m_0A64;
 float m_0A68;
 float m_0A6C;
 float m_0A70;
 float m_0A74;
 float m_0A78;
 float m_0A7C;
 float m_0A80;
 float m_0A84;
 int m_0A88;
 float m_0A8C;
 float m_0A90;
 int m_0A94;
 int m_0A98;
 float m_0A9C;
 float m_0AA0;
 float m_0AA4;
 int m_0AA8;
 float m_0AAC;
 float m_0AB0;
 bool m_0AB4;
 bool m_0AB5;
 char unknown0AB6[2];
 AsciiString m_0AB8;
 AsciiString m_0ABC;
 AsciiString m_0AC0;
 bool m_0AC4;
 bool m_0AC5;
 char unknown0AC6[2];
 int m_0AC8;
 int m_0ACC;
 Rva00235A21* m_weaponBonusSet;
 float m_0AD4[4];
 float m_0AE4;
 float m_0AE8;
 AsciiString m_0AEC;
 bool m_0AF0;
 bool m_0AF1;
 bool m_0AF2;
 bool m_0AF3;
 bool m_0AF4;
 bool m_0AF5;
 char unknown0AF6[2];
 float m_0AF8;
 float m_0AFC;
 bool m_0B00;
 bool m_0B01;
 char unknown0B02[2];
 int m_0B04;
 Version m_0B08;
 int m_0B38;
 int m_0B3C;
 float m_0B40;
 int m_0B44;
 float m_0B48;
 float m_0B4C;
 int m_0B50;
 float m_0B54;
 bool m_0B58;
 char unknown0B59[3];
 float m_0B5C;
 float m_0B60;
 int m_0B64;
 bool m_0B68;
 bool m_0B69;
 bool m_0B6A;
 bool m_0B6B;
 bool m_0B6C;
 bool m_0B6D;
 bool m_0B6E;
 bool m_0B6F;
 bool m_0B70;
 bool m_0B71;
 char unknown0B72[2];
 float m_0B74;
 float m_0B78;
 float m_0B7C;
 float m_0B80;
 float m_0B84;
 float m_0B88;
 float m_0B8C;
 float m_0B90;
 float m_0B94;
 float m_0B98;
 int m_0B9C;
 int m_0BA0;
 AsciiString m_0BA4;
 _STL::vector<AsciiString> m_0BA8;
 bool m_0BB4;
 char unknown0BB5[7];
 bool m_0BBC;
 bool m_0BBD;
 char unknown0BBE[2];
 int m_0BC0;
 float m_0BC4;
 int m_0BC8;
 float m_0BCC;
 int m_0BD0;
 bool m_0BD4;
 char unknown0BD5[3];
 int m_0BD8;
 RvaGDColor m_0BDC;
 unsigned char m_0BE8;
 unsigned char m_0BE9;
 bool m_0BEA;
 char unknown0BEB[1];
 RvaGDColor m_0BEC;
 char unknown0BF8[12];
 unsigned char m_0C04;
 char unknown0C05[3];
 int m_0C08;
 int m_0C0C;
 int m_0C10;
 int m_0C14;
 int m_0C18;
 int m_0C1C;
 int m_0C20;
 int m_0C24;
 int m_0C28;
 float m_0C2C;
 int m_0C30;
 int m_0C34;
 float m_0C38;
 int m_0C3C;
 int m_0C40;
 float m_0C44;
 float m_0C48;
 float m_0C4C;
 float m_0C50;
 _STL::vector<AsciiString> m_0C54;
 int m_0C60;
 bool m_0C64;
 bool m_0C65;
 bool m_0C66;
 bool m_0C67;
 bool m_0C68;
 bool m_0C69;
 bool m_0C6A;
 bool m_0C6B;
 bool m_0C6C;
 bool m_0C6D;
 bool m_0C6E;
 bool m_0C6F;
 int m_0C70;
 bool m_0C74;
 bool m_0C75;
 char unknown0C76[2];
 int m_0C78;
 bool m_0C7C;
 bool m_0C7D;
 char unknown0C7E[2];
 int m_0C80;
 char unknown0C84[4];
 int m_0C88;
 bool m_0C8C;
 char unknown0C8D[3];
 int m_0C90;
 int m_0C94;
 bool m_0C98;
 char unknown0C99[3];
 int m_0C9C;
 int m_0CA0;
 bool m_0CA4;
 char unknown0CA5[39];
 bool m_0CCC;
 char unknown0CCD[3];
 float m_0CD0;
 int m_0CD4;
 char unknown0CD8[32];
 bool m_0CF8;
 bool m_0CF9;
 bool m_0CFA;
 bool m_0CFB;
 bool m_0CFC;
 bool m_0CFD;
 bool m_0CFE;
 bool m_0CFF;
 bool m_0D00;
 bool m_0D01;
 char unknown0D02[2];
 AsciiString m_0D04;
 AsciiString m_0D08;
 int m_0D0C;
 int m_0D10;
 int m_0D14;
 int m_0D18;
 int m_0D1C;
 int m_0D20;
 bool m_0D24;
 char unknown0D25[3];
 int m_0D28;
 bool m_0D2C;
 bool m_0D2D;
 bool m_0D2E;
 bool m_0D2F;
 AsciiString m_0D30;
 bool m_0D34;
 bool m_0D35;
 bool m_0D36;
 char unknown0D37[1];
 AsciiString m_0D38;
 AsciiString m_0D3C;
 float m_0D40;
 bool m_0D44;
 bool m_0D45;
 bool m_0D46;
 char unknown0D47[1];
 int m_0D48;
 AsciiString m_0D4C;
 int m_0D50;
 int m_0D54;
 float m_0D58;
 float m_0D5C;
 char unknown0D60[4];
 int m_0D64;
 int m_0D68;
 float m_0D6C;
 float m_0D70;
 int m_0D74;
 float m_0D78;
 float m_0D7C;
 int m_0D80;
 float m_0D84;
 float m_0D88;
 int m_0D8C;
 float m_0D90;
 float m_0D94;
 int m_0D98;
 float m_0D9C;
 float m_0DA0;
 int m_0DA4;
 float m_0DA8;
 float m_0DAC;
 bool m_0DB0;
 char unknown0DB1[3];
 int m_0DB4;
 int m_0DB8;
 int m_0DBC;
 int m_0DC0;
 int m_0DC4;
 int m_0DC8;
 int m_0DCC;
 bool m_0DD0;
 bool m_0DD1;
 char unknown0DD2[2];
 float m_0DD4;
 float m_0DD8;
 bool m_0DDC;
 char unknown0DDD[3];
 float m_0DE0;
 float m_0DE4;
 bool m_0DE8;
 char unknown0DE9[3];
 int m_0DEC;
 int m_0DF0;
 int m_0DF4;
 int m_0DF8;
 int m_0DFC;
 int m_0E00;
 int m_0E04;
 int m_0E08;
 char unknown0E0C[88];
 int m_0E64;
 int m_0E68;
 int m_0E6C;
 int m_0E70;
 int m_0E74;
 int m_0E78;
 int m_0E7C;
 int m_0E80;
 int m_0E84;
 float m_0E88;
 int m_0E8C;
 int m_0E90;
 int m_0E94;
 float m_0E98;
 bool m_0E9C;
 bool m_0E9D;
 char unknown0E9E[2];
 int m_0EA0;
 bool m_0EA4;
 bool m_0EA5;
 bool m_0EA6;
 bool m_0EA7;
 float m_0EA8;
 float m_0EAC;
 Rva00360D26Member m_0EB0;
 Rva00360D26Member m_0EB4;
 Rva00360D26Member m_0EB8;
 Rva00360D26Member m_0EBC;
 Rva00360D26Member m_0EC0;
 MultiPlayMults m_0EC4;
 float m_10A4[20];
 _STL::vector<AsciiString> m_10F4;
 bool m_1100;
 char unknown1101[3];
 int m_1104;
 int m_1108;
 float m_110C;
 bool m_1110;
 bool m_1111;
 char unknown1112[2];
 Rva002362B4 m_1114;
 Rva002362B4 m_1138;
 int m_115C;
 int m_1160;
 int m_1164;
 Rva00360D26Member m_1168;
 float m_116C[20];
 bool m_11BC;
 char unknown11BD[3];
 int m_11C0;
 float m_11C4;
 bool m_11C8;
 bool m_11C9;
 bool m_11CA;
 bool m_11CB;
 int m_11CC;
 float m_11D0;
 float m_11D4;
 int m_11D8;
 int m_11DC;
 int m_11E0;
 float m_11E4;
 int m_11E8;
 int m_11EC;
 int m_11F0;
 int m_11F4;
 int m_11F8;
 int m_11FC;
 int m_1200;
 int m_1204;
 int m_1208;
 int m_120C;
 int m_1210;
 int m_1214;
 int m_1218;
 int m_121C;
 char unknown1220[4];
 float m_1224;
 int m_1228;
 int m_122C;
 int m_1230;
 int m_1234;
 int m_1238;
 bool m_123C;
 bool m_123D;
 char unknown123E[2];
 AsciiString m_1240;
 UnicodeString m_1244;
 AsciiString m_picturePath;
 AsciiString m_124C;
 GlobalData* m_next;
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

// Table BED1C4: reload notice slot4 and literal-preserving table getter slot6.
// Slots1 and10 are empty; original names of slots4/6 remain unknown.

class InGameUI { public:
 virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
 virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
 virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
 virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
 virtual void message(UnicodeString format,...);
};
extern InGameUI *TheInGameUI;
bool GlobalData::vslot04(int reason)
{
 if(loadIniFilesFromLegend()) {
  if(TheInGameUI) TheInGameUI->message(UnicodeString(L"RIF: GameData reloaded (changes are effective immediately)"));
  return true;
 }
 return false;
}

int GlobalData::vslot06() { return 0x00BE8520; }
void GlobalData::init() {}
void GlobalData::update() {}


GlobalData::GlobalData():
m_001C(1),
m_001D(0),
m_0020(1),
m_0024(0),
m_0025(1),
m_0026(0),
m_0027(0),
m_0028(0),
m_002C(0),
m_002D(0),
m_0030(0x400),
m_0034(0x300),
m_0038(0),
m_003C(0),
m_003D(1),
m_003E(1),
m_003F(1),
m_0040(0),
m_0041(0),
m_0044(1),
m_0048(0),
m_0049(1),
m_004A(1),
m_004B(0),
m_004C(0),
m_004D(0),
m_004E(0),
m_0050(8),
m_0054(1),
m_0058(0),
m_005C(1),
m_005D(0),
m_005E(0),
m_005F(0),
m_0060(0),
m_0061(0),
m_0062(0),
m_0064(0),
m_0068(1),
m_006C(0.0f),
m_0070(0.0f),
m_0074(0.0f),
m_0078(0.0f),
m_007C(0.0f),
m_0080(0),
m_0084(1),
m_0085(0),
m_0086(1),
m_0087(0),
m_0088(0),
m_0090(0),
m_0094(-0.785f),
m_0098(0.0f),
m_009C(100.0f),
m_00A0(300.0f),
m_00A4(37.5f),
m_00A8(0.0f),
m_00AC(1.0f),
m_00B0(0.0f),
m_00B4(0.5f),
m_00B8(0.1f),
m_00BC(0.5f),
m_00C0(0.5f),
m_00C4(-1.0f),
m_00C8(0.5f),
m_00CC((g_Va00DBA4E4*3)),
m_00D0(0),
m_00D4(0.0f),
m_00D8(0.0f),
m_00DC(0.0f),
m_00E8(0.0f),
m_00F4(0.0f),
m_00FC(0.0f),
m_0104(1.0f),
m_0108(1.0f),
m_010C(0),
m_0110(0x64),
m_0114(0x19),
m_0118(0x493e0),
m_0120(0.0f),
m_0124(0.0f),
m_012C(0.0f),
m_0130(0.0f),
m_0134(2),
m_0138(0),
m_013C(0),
m_013D(0),
m_013E(1),
m_013F(1),
m_0944(1.0f),
m_0950(1.0f),
m_0974(0x200),
m_0978(0x200),
m_097C(0x200),
m_0980(0x200),
m_0984(0.5f),
m_0988(3),
m_098C(0),
m_0990(0),
m_0994(0),
m_0998(0),
m_099C(1),
m_099D(1),
m_099E(1),
m_099F(1),
m_09A0(1),
m_09A1(1),
m_09A2(0),
m_09A3(1),
m_09A4(0),
m_09A5(1),
m_09A6(0),
m_09A7(0),
m_09A8(0.3f),
m_09AC(0),
m_09AD(0),
m_09AE(0),
m_09AF(1),
m_09B0(1),
m_09B1(0),
m_09B4(0),
m_09B8(0),
m_09BC(0),
m_09BD(1),
m_09BE(0),
m_09BF(1),
m_09C0(0),
m_09C1(0),
m_09C2(0),
m_09C3(0),
m_09C4(0),
m_09C5(1),
m_09C6(1),
m_09C7(0),
m_09C8(0),
m_09CC(1),
m_09D0(0),
m_09D1(0),
m_09D2(0),
m_09D4(0),
m_09D8(0),
m_09E4(0),
m_09E8(-1),
m_09EC(1.0f),
m_09F8(0),
m_0A04(0),
m_0A10(0),
m_0A1C(0),
m_0A28(0),
m_0A34(0),
m_0A40(0),
m_0A44(1),
m_0A48(0),
m_0A4C(0),
m_0A50(0),
m_0A54(0),
m_0A58(0),
m_0A5C(0x64),
m_0A60(1),
m_0A64(0.0f),
m_0A68(0.0f),
m_0A6C(0.0f),
m_0A70(0.0f),
m_0A74(0.0f),
m_0A78(0.0f),
m_0A7C(0.0f),
m_0A80(0.0f),
m_0A84(0.0f),
m_0A88(0xa),
m_0A8C(0.0f),
m_0A90(0.0f),
m_0A94(0x64),
m_0A98(0),
m_0A9C(1.0f),
m_0AA0(1.0f),
m_0AA4(1.0f),
m_0AA8(0x12c),
m_0AAC(10.0f),
m_0AB0(0.1f),
m_0AB4(1),
m_0AB5(0),
m_0AC4(0),
m_0AC5(0),
m_0AC8(0),
m_0ACC(0x1e),
m_weaponBonusSet(new Rva00235A21),
m_0AE4(1.0f),
m_0AE8(1.0f),
m_0AEC("Maps\\ShellMap1\\ShellMap1.map"),
m_0AF0(1),
m_0AF1(0),
m_0AF2(1),
m_0AF3(0),
m_0AF4(0),
m_0AF5(0),
m_0AF8(1.0f),
m_0AFC(1.0f),
m_0B00(1),
m_0B01(0),
m_0B04(0),
m_0B38(-1),
m_0B3C(2),
m_0B40(4.0f),
m_0B44(5),
m_0B48(0.5f),
m_0B4C(0.02f),
m_0B50(8),
m_0B54(0.5f),
m_0B58(0),
m_0B5C(500.0f),
m_0B60(1.0f),
m_0B64(0),
m_0B68(1),
m_0B69(0),
m_0B6A(0),
m_0B6B(0),
m_0B6C(0),
m_0B6D(0),
m_0B6E(0),
m_0B6F(0),
m_0B70(0),
m_0B71(0),
m_0B74(0.5f),
m_0B78(1.0f),
m_0B7C(2.5f),
m_0B80(5.0f),
m_0B84(8.0f),
m_0B88(12.0f),
m_0B8C(10.0f),
m_0B90(150.0f),
m_0B94(1.0f),
m_0B98(0.0f),
m_0B9C(0),
m_0BA0(0xffffff00),
m_0BB4(0),
m_0BBC(0),
m_0BBD(0),
m_0BC0(7),
m_0BC4(3.0f),
m_0BC8(5),
m_0BCC(1.0f),
m_0BD0(0x1e),
m_0BD4(0),
m_0BD8(GetDoubleClickTime()),
m_0BDC(0xFFFFFF),
m_0BE8(0xff),
m_0BE9(0x7f),
m_0BEA(0),
m_0BEC(0xFFFFFF),
m_0C04(0x80),
m_0C08(0x1e),
m_0C0C(0xc8),
m_0C10(0x1f4),
m_0C14(0xa),
m_0C18(0xa),
m_0C1C(0x14),
m_0C20(0x1388),
m_0C24(0xea60),
m_0C28(0x3a98),
m_0C2C(0.1f),
m_0C30(-1),
m_0C34(g_Va00DBA4E4),
m_0C38(30.0f),
m_0C3C(g_Va00DBA4E4),
m_0C40(0x64),
m_0C44(5.0f),
m_0C48(0.1f),
m_0C4C(0.25f),
m_0C50(0.5f),
m_0C60(-1),
m_0C64(0),
m_0C65(0),
m_0C66(0),
m_0C67(1),
m_0C68(1),
m_0C69(1),
m_0C6A(0),
m_0C6B(0),
m_0C6C(0),
m_0C6D(0),
m_0C6E(0),
m_0C6F(0),
m_0C70(-1),
m_0C74(0),
m_0C75(0),
m_0C78(0),
m_0C7C(0),
m_0C7D(0),
m_0C80(0x20),
m_0C88(g_Va00DBA4E4),
m_0C8C(0),
m_0C90(0x1388),
m_0C94(g_Va00DBA4E4),
m_0C98(0),
m_0C9C(0x2710),
m_0CA0(g_Va00DBA4E4),
m_0CA4(0),
m_0CCC(0),
m_0CD0(33.0f),
m_0CD4(0x4d),
m_0CF8(0),
m_0CF9(0),
m_0CFA(0),
m_0CFB(0),
m_0CFC(0),
m_0CFD(0),
m_0CFE(0),
m_0CFF(0),
m_0D00(0),
m_0D01(0),
m_0D04(".\\"),
m_0D08("MOTD.txt"),
m_0D0C(0),
m_0D10(0),
m_0D14(0),
m_0D18(0),
m_0D1C(0),
m_0D20(0),
m_0D24(1),
m_0D28(0x5a),
m_0D2C(1),
m_0D2D(0),
m_0D2E(0),
m_0D2F(0),
m_0D34(0),
m_0D35(0),
m_0D36(0),
m_0D40(1.0f),
m_0D44(0),
m_0D45(0),
m_0D46(1),
m_0D48(0),
m_0D50(0xa),
m_0D54(0),
m_0D58(0.0f),
m_0D5C(0.0f),
m_0D64(5),
m_0D68(0),
m_0D6C(0.0f),
m_0D70(0.0f),
m_0D74(0),
m_0D78(0.0f),
m_0D7C(0.0f),
m_0D80(0),
m_0D84(0.0f),
m_0D88(0.0f),
m_0D8C(0),
m_0D90(0.0f),
m_0D94(0.0f),
m_0D98(0),
m_0D9C(0.0f),
m_0DA0(0.0f),
m_0DA4(0),
m_0DA8(0.0f),
m_0DAC(0.0f),
m_0DB0(0),
m_0DB4(0xff),
m_0DB8(0),
m_0DBC(0),
m_0DC0(0xffffff6a),
m_0DC4(0xffffff60),
m_0DC8(0x80),
m_0DCC(0x80),
m_0DD0(0),
m_0DD1(1),
m_0DD4(250.0f),
m_0DD8(0.0f),
m_0DDC(0),
m_0DE0(0.2f),
m_0DE4(1.0f),
m_0DE8(0),
m_0DEC(0x3c),
m_0DF0(0x3c),
m_0DF4(0x7d),
m_0DF8(0x7d),
m_0DFC(0xa),
m_0E00(0x19),
m_0E04(0x64),
m_0E08(0x64),
m_0E64(0x37),
m_0E68(0x37),
m_0E6C(0x46),
m_0E70(0x46),
m_0E74(0x32),
m_0E78(0x32),
m_0E7C(0x3c),
m_0E80(0x3c),
m_0E84(2),
m_0E88(10.0f),
m_0E8C(0xc8),
m_0E90(0x258),
m_0E94(0xa),
m_0E98(4.0f),
m_0E9C(0),
m_0E9D(0),
m_0EA0(0),
m_0EA4(1),
m_0EA5(1),
m_0EA6(0),
m_0EA7(1),
m_0EA8(0.7f),
m_0EAC(0.0f),
m_1100(0),
m_1104(0),
m_1108(3),
m_110C(5.0f),
m_1110(1),
m_1111(0),
m_115C(0),
m_1160(0xff0b5ef2),
m_1164(0xffd92102),
m_11BC(1),
m_11C0(0),
m_11C4(40.0f),
m_11C8(0),
m_11C9(0),
m_11CA(1),
m_11CB(0),
m_11CC(0),
m_11D0(1.0f),
m_11D4(1.0f),
m_11D8(0xa),
m_11DC(5),
m_11E0(5),
m_11E4(10.0f),
m_11E8(0xfa0),
m_11EC(0x32),
m_11F0(0x190),
m_11F4(0xc8),
m_11F8(0x190),
m_11FC(0x190),
m_1200(0x190),
m_1204(0x190),
m_1208(0x190),
m_120C(0x7d0),
m_1210(0x3a98),
m_1214(0x9c4),
m_1218(0x9c4),
m_121C(0x61a8),
m_1224(-1.0f),
m_1228(-1),
m_122C(5),
m_1230(1),
m_1234(5),
m_1238(0),
m_123C(0),
m_123D(0) {
 if(!m_theOriginal) m_theOriginal=this;
 m_next=0;
 m_008C.clear(); m_000C.clear();m_0010.clear();m_0014.clear();m_0018.clear();
 for(int i=0;i<3;++i) {
  m_08D8[i].x=m_08D8[i].y=m_08D8[i].z=0.0f;
  m_08FC[i].x=m_08FC[i].y=m_08FC[i].z=0.0f;
  m_0920[i].x=m_0920[i].y=0.0f;m_0920[i].z=-1.0f;
  for(int j=0;j<6;++j) {
   m_0140[j*3+i].ambient.x=0.0f;
   m_0140[j*3+i].ambient.y=0.0f;
   m_0140[j*3+i].ambient.z=0.0f;
   m_0140[j*3+i].diffuse.x=0.0f;
   m_0140[j*3+i].diffuse.y=0.0f;
   m_0140[j*3+i].diffuse.z=0.0f;
   m_0140[j*3+i].position.x=0.0f;
   m_0140[j*3+i].position.y=0.0f;
   m_0140[j*3+i].position.z=-1.0f;
   m_03C8[j*3+i].ambient.x=0.0f;
   m_03C8[j*3+i].ambient.y=0.0f;
   m_03C8[j*3+i].ambient.z=0.0f;
   m_03C8[j*3+i].diffuse.x=0.0f;
   m_03C8[j*3+i].diffuse.y=0.0f;
   m_03C8[j*3+i].diffuse.z=0.0f;
   m_03C8[j*3+i].position.x=0.0f;
   m_03C8[j*3+i].position.y=0.0f;
   m_03C8[j*3+i].position.z=-1.0f;
   m_0650[j*3+i].ambient.x=0.0f;
   m_0650[j*3+i].ambient.y=0.0f;
   m_0650[j*3+i].ambient.z=0.0f;
   m_0650[j*3+i].diffuse.x=0.0f;
   m_0650[j*3+i].diffuse.y=0.0f;
   m_0650[j*3+i].diffuse.z=0.0f;
   m_0650[j*3+i].position.x=0.0f;
   m_0650[j*3+i].position.y=0.0f;
   m_0650[j*3+i].position.z=-1.0f;
  }
 }
m_09F0.clear();
m_09FC.clear();
m_0A08.clear();
m_0A14.clear();
m_0A20.clear();
m_0A2C.clear();
m_0A38.clear();
m_09F4.clear();
m_0A00.clear();
m_0A0C.clear();
m_0A18.clear();
m_0A24.clear();
m_0A30.clear();
m_0A3C.clear();
m_011C.clear();
m_0128.clear();
m_0BA4.clear();
m_0BA8.erase(m_0BA8.begin(),m_0BA8.end());setTimeOfDay((TimeOfDay)m_0134);
m_0ABC.clear();m_0AC0.clear();
for(int i=0;i<4;++i)m_0AD4[i]=1.0f;
for(int i=0;i<8;++i)m_0954[i]=1.0f;
if(TheVersion)*reinterpret_cast<Rva00235A37*>(&m_0B08)=*reinterpret_cast<Rva00235A37*>(TheVersion);
for(int i=0;i<20;++i)m_10A4[i]=1.0f;
for(int i=0;i<20;++i)m_116C[i]=1.0f;
m_116C[19]=0.1f;
}

typedef char S4GlobalDataSize[(sizeof(GlobalData)==0x1254)?1:-1];
