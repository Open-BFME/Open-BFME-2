// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?Rva005D0100Get@@YA?AVUnicodeString@@H@Z @0x005D0100 46B: battle message fetch.
// Evidence: selects STRATEGICHUD SelectedAutoResolve vs SelectedRTS by flag==1 then rowed TheGameText fetch slot 0x3C with 0 exists; sret via hidden out pointer; callers in 0x005D015C 0x005D08FD.
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

UnicodeString Rva005D0100Get(int autoResolve)
{
	const char *msg = "STRATEGICHUD:SelectedAutoResolveBattleMessage";
	if (autoResolve != 1)
		msg = "STRATEGICHUD:SelectedRTSBattleMessage";
	return TheGameText->fetch(msg, 0);
}
