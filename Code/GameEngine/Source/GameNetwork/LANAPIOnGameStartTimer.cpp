// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// LANAPI::OnGameStartTimer, retail 0x00248F6E (157B), vtable 0x00C3E680
// slot 44. Zero Hour's body (GameNetwork/LANAPICallbacks.cpp): the singular
// or plural "LAN:GameStartTimer*" label formatted with the seconds, sent to
// OnChat as a SYSTEM line. BFME2 deltas read off the target: the label comes
// from TheGameText's slot 17 (+0x44) as a pointer straight into
// UnicodeString::format (as ControlBarUpdateConstruction.cpp has it); OnChat
// is slot 40 (+0xA0) and takes both strings by reference; the local address
// comes from the virtual at slot 64 (+0x100) where Zero Hour reads m_localIP.
// LANCHAT_SYSTEM is 3 as upstream.

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, Bool *exists);
};
extern GameTextInterface *TheGameText;

struct BfmeNetAddress;

enum ChatType
{
	LANCHAT_NORMAL = 0,
	LANCHAT_EMOTE,
	LANCHAT_SYSTEM = 3
};

#define BFME_VSLOT(n) virtual void slot##n();

class LANAPI
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	virtual void OnChat(const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, ChatType format);	// slot 40 (+0xA0)
	BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43)
	virtual void OnGameStartTimer(Int seconds);			// slot 44 (+0xB0)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47) BFME_VSLOT(48) BFME_VSLOT(49)
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53) BFME_VSLOT(54)
	BFME_VSLOT(55) BFME_VSLOT(56) BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	BFME_VSLOT(60) BFME_VSLOT(61) BFME_VSLOT(62) BFME_VSLOT(63)
	virtual const BfmeNetAddress *getLocalIP() const;	// slot 64 (+0x100)
};

#undef BFME_VSLOT

void LANAPI::OnGameStartTimer(Int seconds)
{
	UnicodeString text;
	if (seconds == 1)
		text.format(TheGameText->slot44("LAN:GameStartTimerSingular", 0), seconds);
	else
		text.format(TheGameText->slot44("LAN:GameStartTimerPlural", 0), seconds);
	OnChat(L"SYSTEM", getLocalIP(), text, LANCHAT_SYSTEM);
}
