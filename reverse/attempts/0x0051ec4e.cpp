// ?PlayerFaction@AptTimeLine@@QAEXHPAD_N@Z
// partial score=0.85 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's time line (post-game graph) screen Apt callbacks
// "AptTimeLine::OnButtonContinue", 0x0051F6D7, and 0x0051E3C3, bound by
// those names as member pointers by the screen's registration; that binding
// is their only reference. The class is named for the strings' prefix.

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

#include <vector>

#include "ascii_string.h"

// One player's row of the time line (0x50 bytes): the color at +0x08 and
// the faction name at +0x0C; the rest is not read here.
struct AptTimeLinePlayer
{
	unsigned char m_pad00[0x8];
	int m_color; // +0x08
	AsciiString m_faction; // +0x0C
	unsigned char m_pad10[0x50 - 0x10];
};

// Rva00434160Init.cpp's 0x00434160 and Rva00433D3CClear.cpp's 0x00433D3C.
void __cdecl Rva00434160Init(int a, int b, bool c);
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
	void PlayerFaction(int index, char *value, bool set);

	// Unrowed 0x0051ED7E (345 bytes), pinned by address.
	void rva0051ED7E();

private:
	unsigned char m_pad000[0x288];
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
	unsigned char m_pad294[0x2B8 - 0x294];
	_STL::vector<float> m_focus; // +0x2B8, the per-player focus weights
};

// Retail 0x0051E3C3, 22 bytes: bound as "AptTimeLine::OnButtonSaveReplay"
// and "AptScoreScreen::Save".
void AptTimeLine::rva0051E3C3(const char *unused)
{
	Rva00434160Init(3, 4, false);
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

// Retail 0x0051EC4E, 117 bytes: "TimeLine:PlayerFaction:%d" for each
// player, an Apt variable read as the player's faction name.
void AptTimeLine::PlayerFaction(int index, char *value, bool set)
{
	if (set)
		return;
	strcpy(value, "");
	if (m_players.empty())
		return;
	if (index >= 0 && (unsigned int)index < m_players.size())
		strcpy(value, m_players[index].m_faction.str());
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
