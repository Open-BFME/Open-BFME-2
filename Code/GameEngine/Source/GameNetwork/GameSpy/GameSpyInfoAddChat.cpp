// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?addChat@GameSpyInfo@@UAEXVPlayerInfo@@VUnicodeString@@_N2@Z retail
// 0x001EF9A0..0x001EFC42 (674 bytes EH RET 0x40). It is slot 63 of the GameSpyInfo
// vtable 0x00819500 (slots 29 getLocalName / 77 isSavedIgnored / 83 isIgnored
// are the rowed GameSpyInfo members). The rowed slot-62 overload
// rva001EF90E (nick / profile ID) builds the PlayerInfo and forwards here.
// Zero Hour GameSpyInfo::addChat with BFME 2 changes:
// - The ignore checks run only for other players.
// - The private-message sound plays for non-public chat: canonical
//   BfmeAudioEventPrefix136 built from TheAudio slot 78 +0x78 with 2, then
//   slot 25.
// - The line goes to this object's slot 61 rather than a list box.
// - The colour indices are 0x0D..0x15.
// Kept from ZH:
// - the Asian / non-Asian text filters (+0x5CC / +0x5CD, characters >= 256);
// - buddy lookup through slot 24 (rowed map<int,int>::_M_find);
// - owner from player flag bit 5;
// - TheLanguageFilter->filterLine;
// - "%ls %ls" / "[%ls] %ls" through the rowed UnicodeString::format.
// The by-value PlayerInfo is destroyed through the pinned ??1PlayerInfo.
// The colour table at VA 0x00DB9198 is ZH's GameSpyColor array (the ledger
// currently lists it as the 8-byte g_00DB9198).
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;
typedef int Color;

enum GameSpyColors
{
	GSCOLOR_CHAT_NORMAL = 0x0D,
	GSCOLOR_CHAT_EMOTE = 0x0E,
	GSCOLOR_CHAT_OWNER = 0x0F,
	GSCOLOR_CHAT_OWNER_EMOTE = 0x10,
	GSCOLOR_CHAT_PRIVATE = 0x11,
	GSCOLOR_CHAT_PRIVATE_EMOTE = 0x12,
	GSCOLOR_CHAT_PRIVATE_OWNER = 0x13,
	GSCOLOR_CHAT_PRIVATE_OWNER_EMOTE = 0x14,
	GSCOLOR_CHAT_BUDDY = 0x15
};
extern Color GameSpyColor[];

class PlayerInfo
{
public:
	~PlayerInfo();
	AsciiString m_00;
	AsciiString m_name;									// +0x04
	AsciiString m_08;
	Int m_0C;
	Int m_10;
	Int m_profileID;									// +0x14
	unsigned int m_flags;								// +0x18
	Int m_1C;
	Int m_20;
	Int m_24;
	Int m_28;
	Int m_2C;
	Int m_30;
};

typedef _STL::map<Int, Int> BuddyInfoMap;

struct GameSpyMiscAudio
{
	char m_pad00[0x78];
	OpaqueRefElement4 m_privateMessage;					// +0x78
};

class AudioManager
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24)
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event);		// slot 25
	V(26) V(27) V(28) V(29) V10(3) V10(4) V10(5) V10(6)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77)
	virtual const GameSpyMiscAudio *getMiscAudio();							// slot 78
#undef V10
#undef V
};
extern AudioManager *TheAudio;

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};
extern LanguageFilter *TheLanguageFilter;

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSpyInfo
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23)
	virtual BuddyInfoMap *getBuddyMap();									// slot 24
	V(25) V(26) V(27) V(28)
	virtual AsciiString getLocalName();										// slot 29
	V10(3) V10(4) V10(5) V(60)
	virtual void addText(UnicodeString text, Color color);					// slot 61
	virtual void addChat(AsciiString nick, Int profileID, UnicodeString msg, Bool isPublic, Bool isAction);	// slot 62
	virtual void addChat(PlayerInfo p, UnicodeString msg, Bool isPublic, Bool isAction);					// slot 63
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76)
	virtual Bool isSavedIgnored(Int profileID);								// slot 77
	V(78) V(79) V(80) V(81) V(82)
	virtual Bool isIgnored(AsciiString nick);								// slot 83
#undef V10
#undef V
private:
	char m_pad004[0x5CC - 0x004];
	Bool m_disallowAsianText;												// +0x5CC
	Bool m_disallowNonAsianText;											// +0x5CD
};

void GameSpyInfo::addChat(PlayerInfo p, UnicodeString msg, Bool isPublic, Bool isAction)
{
	Int style;
	Bool isMe = p.m_name.compare(((GameSpyInfo *)TheGameSpyInfo)->getLocalName()) == 0;
	if (!isMe && (isSavedIgnored(p.m_profileID) || isIgnored(p.m_name)))
		return;

	Bool isOwner = (p.m_flags >> 5) & 1;
	Bool isBuddy = getBuddyMap()->find(p.m_profileID) != getBuddyMap()->end();

	if (!isMe)
	{
		if (m_disallowAsianText)
		{
			const WideChar *buff = msg.str();
			Int length = msg.getLength();
			for (Int i = 0; i < length; ++i)
			{
				if (buff[i] >= 256)
					return;
			}
		}
		else if (m_disallowNonAsianText)
		{
			const WideChar *buff = msg.str();
			Int length = msg.getLength();
			Bool hasUnicode = false;
			for (Int i = 0; i < length; ++i)
			{
				if (buff[i] >= 256)
				{
					hasUnicode = true;
					break;
				}
			}
			if (!hasUnicode)
				return;
		}
		if (!isPublic)
		{
			if (TheAudio)
			{
				BfmeAudioEventPrefix136 privMsgAudio(TheAudio->getMiscAudio()->m_privateMessage, 2);
				TheAudio->addAudioEvent(&privMsgAudio);
			}
		}
	}

	if (isBuddy)
		style = GSCOLOR_CHAT_BUDDY;
	else if (isPublic && isAction)
		style = isOwner ? GSCOLOR_CHAT_OWNER_EMOTE : GSCOLOR_CHAT_EMOTE;
	else if (isPublic)
		style = isOwner ? GSCOLOR_CHAT_OWNER : GSCOLOR_CHAT_NORMAL;
	else if (isAction)
		style = isOwner ? GSCOLOR_CHAT_PRIVATE_OWNER_EMOTE : GSCOLOR_CHAT_PRIVATE_EMOTE;
	else
		style = isOwner ? GSCOLOR_CHAT_PRIVATE_OWNER : GSCOLOR_CHAT_PRIVATE;

	UnicodeString name;
	name.translate(p.m_name);
	TheLanguageFilter->filterLine(msg);
	UnicodeString fullMsg;
	if (isAction)
		fullMsg.format(L"%ls %ls", name.str(), msg.str());
	else
		fullMsg.format(L"[%ls] %ls", name.str(), msg.str());
	addText(fullMsg, GameSpyColor[style]);
}
