// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's time line (post-game graph) screen Apt callbacks
// "AptTimeLine::OnButtonContinue", 0x0051F6D7, and 0x0051E3C3, bound by
// those names as member pointers by the screen's registration; that binding
// is their only reference. The class is named for the strings' prefix.
// The per-player variables ("TimeLine:PlayerColor:%d" ...) are bound in a
// loop of the same registration (0x0051FEF5-0x0051FFC1).

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

// An award (0x40 bytes): its name and description labels and image name.
struct BfmePod40
{
	unsigned char m_pad00[0x10];
	AsciiString m_name; // +0x10
	AsciiString m_description; // +0x14
	AsciiString m_image; // +0x18
	unsigned char m_pad1c[0x40 - 0x1C];
};

// The award store (0x00E02F74) and its rowed lookup by id 0x0040AAD5.
class Rva0040AAD5
{
public:
	BfmePod40 *rva0040AAD5(int id);
};

extern Rva0040AAD5 *g_Va00E02F74;

// The ids of the awards earned this game (0x00E04920).
extern _STL::vector<int> g_Va00E04920;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

// The screen's Apt image table at +0x258 and its rowed setter 0x00524725.
class Rva00524306
{
public:
	void rva00524725(const AsciiString &key, const Image *image);
 void rva00524767(const AsciiString &key,const AsciiString &image);
};

// One player's row of the time line (0x50 bytes): the color at +0x08 and
// the faction name at +0x0C (read by the banked PlayerFaction 0x0051EC4E);
// the rest is not read here.
struct AptTimeLinePlayer
{
	unsigned char m_pad00[4];
	UnicodeString m_name; // +0x04
	int m_color; // +0x08
	AsciiString m_faction; // +0x0C
	unsigned char m_pad10[0x50 - 0x10];
};

// Rva00434160Init.cpp's 0x00434160 and Rva00433D3CClear.cpp's 0x00433D3C.
class AptSaveLoad
{
public:
	static void OpenScreen(int a, int b, bool c);
};
void Rva00433D3CClear();

class AptTimeLine
{
public:
	void OnButtonContinue(const char *unused);
	// Bound as "AptTimeLine::OnButtonSaveReplay" and "AptScoreScreen::Save":
	// one body or two folded, so it keeps its address.
	void rva0051E3C3(const char *unused);
	void GraphFocus(int index, const char *value, bool set);
	void PlayerColor(int index, char *value, bool set);
	void CaHAwardNumber(const char *value);
 void rva0051FA13();

	// Unrowed 0x0051ED7E (345 bytes), pinned by address.
	void rva0051ED7E();

private:
	unsigned char m_pad000[0x258];
	Rva00524306 m_images; // +0x258
	unsigned char m_pad259[0x288 - 0x259];
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
	unsigned char m_pad294[0x2B8 - 0x294];
	_STL::vector<float> m_focus; // +0x2B8, the per-player focus weights
};

// Retail 0x0051E3C3, 22 bytes: bound as "AptTimeLine::OnButtonSaveReplay"
// and "AptScoreScreen::Save".
void AptTimeLine::rva0051E3C3(const char *unused)
{
	AptSaveLoad::OpenScreen(3, 4, false);
	Rva00433D3CClear();
}

// Retail 0x0051F6D7, 8 bytes: "AptTimeLine::OnButtonContinue".
void AptTimeLine::OnButtonContinue(const char *unused)
{
	rva0051ED7E();
}

// Retail 0x0051EA7A, 86 bytes: "TimeLine:GraphFocus:%d" for each player,
// an Apt variable Apt writes: the value (a percentage) becomes the player's
// focus weight.
void AptTimeLine::GraphFocus(int index, const char *value, bool set)
{
	if (!set)
		return;
	if (m_focus.empty())
		return;
	if (index >= 0 && (unsigned int)index < m_focus.size())
		m_focus[index] = atoi(value) * 0.01f;
}

// Retail 0x0051E8C8, 113 bytes: "TimeLine:PlayerColor:%d" for each player,
// an Apt variable read as the player's color in hex ("0" when out of
// range).
void AptTimeLine::PlayerColor(int index, char *value, bool set)
{
	if (set)
		return;
	strcpy(value, "0");
	if (m_players.empty())
		return;
	if (index >= 0 && (unsigned int)index < m_players.size())
		sprintf(value, "%#x", m_players[index].m_color & 0xFFFFFF);
}

// Retail 0x0051EAD3, 350 bytes: "AptTimeLine::CaHAwardNumber" shows the
// given (1-based) earned award's name, description and image.
void AptTimeLine::CaHAwardNumber(const char *value)
{
	unsigned int index = atoi(value) - 1;
	if (index >= g_Va00E04920.size())
		return;
	BfmePod40 *award = g_Va00E02F74->rva0040AAD5(g_Va00E04920[index]);
	if (!award)
		return;
	if (((StringBase<char> *)&award->m_name)->isEmpty())
		return;
	{
		AsciiString name("APT:CaH_AwardEarned_Name");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch(award->m_name), false);
	}
	{
		AsciiString name("APT:CaH_AwardDescription");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch(award->m_description), false);
	}
	if (TheMappedImageCollection)
	{
		const Image *image = TheMappedImageCollection->findImageByName(award->m_image);
		m_images.rva00524725(AsciiString("TimeLine::CahAwardImage"), image);
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")

// Complete native51FA13..51FAFC updates each row's name and faction icon;
// WB's weak CollectAllPlayerData lead names a different larger body, so
// retain an address spelling. The twelve-byte concatenation node uses an
// empty default constructor to construct the returned expression in place.
struct Rva002226E5TextPlusString {
 Rva002226E5TextPlusString() {}
 const char *text;int length;const AsciiString *string;
 operator AsciiString();
};
Rva002226E5TextPlusString operator+(const char*,const AsciiString&);
void AptTimeLine::rva0051FA13() {
 for(_STL::vector<AptTimeLinePlayer>::iterator row=m_players.begin();row!=m_players.end();++row) {
  AsciiString key;
  key.format("TimeLine:PlayerName:%d",row-m_players.begin());
  g_bfmeAptWindowManager->bfmeSetText(key,row->m_name,false);
  key.format("TimeLine:PlayerFactionIcon:%d",row-m_players.begin());
  m_images.rva00524767(key,"AptIcon"+row->m_faction);
 }
}
