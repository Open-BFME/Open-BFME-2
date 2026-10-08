// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// GlobalData.cpp -- GlobalData members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. Zero Hour's newOverride also copies the current data
// into the new override; BFME2's retail body only constructs a fresh
// GlobalData (0x1254 bytes, ctor 0x0023631C) and links it in front of the
// chain through m_next at +0x1250 (target evidence).

#include "ascii_string.h"
#include "unicode_string.h"

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

class GlobalData
{
public:
	GlobalData();					// 0x0023631C

	static GlobalData *newOverride();
	AsciiString getPicturePath() const;

private:
	unsigned char m_data[0x1248];
	AsciiString m_picturePath;		// +0x1248, filled on first use
	unsigned char m_pad124c[4];
	GlobalData *m_next;				// +0x1250
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
